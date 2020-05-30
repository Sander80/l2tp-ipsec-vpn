/*
 * $Id: ConnectionManager.cpp 165 2017-12-30 14:12:45Z wejaeger $
 *
 * File:   ConnectionManager.cpp
 * Author: Werner Jaeger
 *
 * Created on July 7, 2010, 5:44 PM
 *
 * Copyright 2010 Werner Jaeger.
 *
 * Upgraded and maintained since 2020 by Alexander Smirnov.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>

#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QTimer>
#include <QtWidgets/QMessageBox>
//#include <QDebug>

#include "pkcs11/SmartCardState.h"
#include "util/NetworkInterfaceMonitor.h"
#include "util/SecretsChecker.h"
#include "dialogs/ConnectionEditorDialog.h"
#include "dialogs/ConnectionInformationDialog.h"
#include "settings/ConnectionSettings.h"
#include "L2tpIPsecVpnApplication.h"
#include "ConnectionState.h"
#include "VPNControlTask.h"
#include "ConnectionManager.h"

/*!
  \class ConnectionManager

  \brief The ConnectionManager class manages L2TP over IPsec VPN connections.
  */

/*!
  Creates a new ConnectionManager object.
  */

static const int PTPINTERFACE_CHECK_UP_TIME(30000);
static const int PTPINTERFACE_CHECK_DOWN_TIME(30000);
static const int VPN_TASK_TIMOUT(300000);
static const int AUTO_CONNECT_DELAY_TIME(2000);

static const QString strRuntimePath("/var/run/L2tpIPsecVpnControlDaemon/");
static const char* const strAbout(
        "<p><center><small>Copyright &copy; 2010-2012 Werner Jaeger</small></center></p>"
        "<p><center><small>Upgrade and maintenance in 2020 by Alexander Smirnov</small></center></p>"
        "<p><center><dda href='http://wiki.l2tpipsecvpn.tuxfamily.org/'>Help</a></center></p>"
        "<p><center><a href='https://launchpad.net/l2tp-ipsec-vpn'>Website</a></center></p>"
        );

ConnectionManager::ConnectionManager(L2tpIPsecVpnApplication& application, QObject* pParent) : QObject(pParent), m_pConnectionInformation(new ConnectionInformationDialog()),
    m_pTimeout(new QTimer), m_pActions(new ActionList()), m_Application(application), m_pState(new NotConnected(NULL)), m_fIsExecuting(false)
{
    connect(&m_Application, SIGNAL(connectionAdded(const QString&)), SLOT(onConnectionAdded(const QString&)));
    connect(&m_Application, SIGNAL(connectionRemoved(const QString&)), SLOT(onConnectionRemoved(const QString&)));

    m_pTimeout->setInterval(VPN_TASK_TIMOUT);
    m_pTimeout->setSingleShot(true);
    connect(m_pTimeout, SIGNAL(timeout()), SLOT(onVpnTaskTimeout()));


    createActions();

    m_pVPNControlTask = new VPNControlTask(this);
    connect(m_pVPNControlTask, SIGNAL(commandOutputReceived(const QString&)), SLOT(onVpnTaskOutput(const QString&)));
    connect(m_pVPNControlTask, SIGNAL(readyReadLog()), SLOT(onVpnTaskReadyReadLog()));
    connect(m_pVPNControlTask, SIGNAL(errorMessageEmited(int)), SLOT(onVpnTaskErrorMsg(int)));
    connect(m_pVPNControlTask, SIGNAL(finished()), SLOT(onVpnTaskFinished()));
    connect(this, SIGNAL(autoConnect(const QString&)), SLOT(vpnConnect(const QString&)), Qt::QueuedConnection);
}

/*!
  Frees the resources associated with this ConnectionManager object.
  */
ConnectionManager::~ConnectionManager()
{
    NetworkInterfaceMonitor::instance()->stop();

    delete m_pConnectionInformation;

    while (!m_pActions->isEmpty())
        delete m_pActions->takeFirst();

    delete m_pTimeout;
    delete m_pActions;
    delete m_pState;
    delete m_pTrayIcon;
    delete m_pTrayIconMenu;
    delete m_pVPNControlTask;
}

int ConnectionManager::exec()
{
    int iRet(1);
    // at startup it might last few seconds until a tray is available, lets try a view times before giving up
    for (int i = 0; iRet != 0 && i < 30; i++)
    {
        if (QSystemTrayIcon::isSystemTrayAvailable())
            iRet = 0;
        else
            ::sleep(1);
    }

    if (iRet == 0)
    {
        createTrayIcon();

        const ConnectionSettings settings;
        const int iSize = settings.connections();
        for (int i = 0; i < iSize; i++)
            onConnectionAdded(settings.connection(i));

        updateContextMenu(true);
        m_pTrayIcon->show();

        QTimer::singleShot(100, this, SLOT(detectConnectionState()));

        iRet = m_Application.exec();
    }
    else
        QMessageBox::critical(NULL, m_Application.applicationName(), QObject::tr("I couldn't detect any system tray on this system."));

    return(iRet);
}

void ConnectionManager::createActions()
{
    m_pActions->insert(DISC, new QAction(tr("&Disconnect"), this));
    m_pActions->insert(EDIT, new QAction(tr("&Edit Connections ..."), this));
    m_pActions->insert(INFO, new QAction(tr("Connection &Information"), this));
    m_pActions->insert(ABOUT, new QAction(tr("&About"), this));
    m_pActions->insert(QUIT, new QAction(tr("&Quit"), this));

    connect(action(DISC), SIGNAL(triggered()), SLOT(vpnDisconnect()));
    connect(action(EDIT), SIGNAL(triggered()), SLOT(editConnections()));
    connect(action(INFO), SIGNAL(triggered()), SLOT(showConnectionInformation()));
    connect(action(ABOUT), SIGNAL(triggered()), SLOT(about()));
    connect(action(QUIT), SIGNAL(triggered()), &m_Application, SLOT(quit()));
}

void ConnectionManager::createTrayIcon()
{
    m_pTrayIconMenu = new QMenu();
    m_pTrayIconMenu->addAction(action(DISC));
    m_pTrayIconMenu->addSeparator();
    m_pTrayIconMenu->addAction(action(EDIT));
    m_pTrayIconMenu->addAction(action(INFO));
    m_pTrayIconMenu->addSeparator();
    m_pTrayIconMenu->addAction(action(ABOUT));
    m_pTrayIconMenu->addSeparator();
    m_pTrayIconMenu->addAction(action(QUIT));

    m_pTrayIcon = new QSystemTrayIcon(this);
    m_pTrayIcon->setContextMenu(m_pTrayIconMenu);

    m_pState = new NotConnected(m_pTrayIcon);

    connect(m_pTrayIconMenu, SIGNAL(triggered(QAction*)), SLOT(vpnConnect(QAction*)));
    connect(m_pTrayIcon, SIGNAL(messageClicked()), SLOT(messageClicked()));
    connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void ConnectionManager::updateContextMenu(bool fStatusChanged)
{
    if (m_pState->isState(ConnectionState::Connected))
    {
        enableAllConnections(false);
        action(DISC)->setEnabled(true);
    }
    else if (m_pState->isState(ConnectionState::Connecting))
    {
        enableAllConnections(false);
        action(DISC)->setEnabled(false);
    }
    else if (m_pState->isState(ConnectionState::Disconnecting))
    {
        enableAllConnections(false);
        action(DISC)->setEnabled(false);
    }
    else if (m_pState->isState(ConnectionState::Error))
    {
        enableAllConnections(NetworkInterface::defaultGateway().size() == 1);
        action(DISC)->setEnabled(false);
    }
    else
    {
        enableAllConnections(NetworkInterface::defaultGateway().size() == 1);
        action(DISC)->setEnabled(false);
    }

    if (fStatusChanged)
    {
        m_pConnectionInformation->onConectionStateChanged(m_pState, m_pVPNControlTask->connectionName());
        showMessage();
    }
}

void ConnectionManager::vpnConnect(const QString& strConnectionName)
{
    //   qDebug() << "ConnectionManager::vpnConnect(const QString&" << strConnectionName << ")";

    //    QTextStream(stdout) << "vpnConnect" << endl;

    if (!m_fIsExecuting)
    {
        const SecretsChecker secrets(strConnectionName);

        if (secrets.check())
        {
            const PppSettings pppSettings(ConnectionSettings().pppSettings(strConnectionName));
            const bool fUseSmartCard = !pppSettings.refuseEap() && pppSettings.eapSettings().useSmartCard();

            m_pConnectionInformation->clearLog();

            SmartCardState sc;

            if (fUseSmartCard && sc.readersAvailable() <= 0)
                m_pVPNControlTask->restartPcscDaemon();

            if (!fUseSmartCard || sc.readersAvailable() > 0)
            {
                if (!fUseSmartCard || sc.waitForCardPresent() > 0)
                {
                    const QString strGateway(ConnectionSettings().gateway(strConnectionName));

                    delete m_pState;
                    m_pState = new Connecting(m_pTrayIcon, strGateway);
                    updateContextMenu(true);

                    m_pVPNControlTask->setConnectionName(strConnectionName);
                    m_pVPNControlTask->setAction(VPNControlTask::Connect);
                    m_pVPNControlTask->start();
                    m_fIsExecuting = true;
                    m_pTimeout->start();
                    QTimer::singleShot(PTPINTERFACE_CHECK_UP_TIME, this, SLOT(onCheckPtpInterfaceIsUp()));
                }
            }
            else
                QMessageBox::critical(NULL, qApp->applicationName(), QObject::tr("No smart card reader found."));
        }
    }

    //   qDebug() << "ConnectionManager::vpnConnect(const QString&" << strConnectionName << ") -> finished";
}


void ConnectionManager::vpnConnect(QAction* pAction)
{
    if (m_pTrayIconMenu && pAction)
    {
        if (!pAction->data().isNull())
            vpnConnect(pAction->data().toString());
    }
}

void ConnectionManager::vpnDisconnect(bool fDontChangeStatus)
{
    //   qDebug() << "ConnectionManager::vpnDisconnect(bool" << fDontChangeStatus << ")";

    if (!m_fIsExecuting)
    {
        if (!fDontChangeStatus)
        {
            const ConnectionSettings settings;
            const QString strGateway(settings.gateway(m_pVPNControlTask->connectionName()));

            delete m_pState;
            m_pState = new Disconnecting(m_pTrayIcon, strGateway);

            updateContextMenu(true);
        }

        m_pVPNControlTask->setAction(VPNControlTask::Disconnect);
        m_pVPNControlTask->start();
        m_fIsExecuting = true;
        m_pTimeout->start();
        QTimer::singleShot(PTPINTERFACE_CHECK_DOWN_TIME, this, SLOT(onCheckPtpInterfaceIsDown()));
    }

    //   qDebug() << "ConnectionManager::vpnDisconnect(bool" << fDontChangeStatus << ") -> finished";
}

void ConnectionManager::editConnections() const
{
    m_Application.startConnectionEditorDialog();
}

void ConnectionManager::showConnectionInformation() const
{
    m_pConnectionInformation->show();

    if (!m_pConnectionInformation->isActiveWindow())
    {
        m_pConnectionInformation->activateWindow();
        m_pConnectionInformation->raise();
    }
}

void ConnectionManager::about() const
{
    QIcon logo;
    logo.addFile(QString::fromUtf8(":/images/logo"), QSize(), QIcon::Normal, QIcon::Off);

    QMessageBox about;
    about.setWindowIcon(logo);
    about.setWindowTitle(tr("About %1").arg(L2tpIPsecVpnApplication::applicationName()));
    about.setText("<big><b>" + L2tpIPsecVpnApplication::applicationName() + " " + L2tpIPsecVpnApplication::applicationVersion() + "</b></big>");
    about.setInformativeText("<p><center>" + tr("Notification area applet for managing your L2tp over IPsec virtual private network connections.") + "</center></p>" + strAbout);
    about.setStandardButtons(QMessageBox::Close);
    about.exec();
}

void ConnectionManager::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::MiddleClick:
            showMessage();
            break;

        case QSystemTrayIcon::Context:
            updateContextMenu(false);
            break;

        case QSystemTrayIcon::Trigger:
            updateContextMenu(false);
            m_pTrayIconMenu->popup(QCursor::pos());
            break;

        default:
            ;
    }
}

void ConnectionManager::showMessage()
{
    m_pTrayIcon->showMessage(m_pState->msgTitle(), m_pState->msgBody(), m_pState->msgIcon(), 5 * 1000);
}

void ConnectionManager::messageClicked()
{
    showConnectionInformation();
}

void ConnectionManager::detectConnectionState()
{

    const ConnectionInfo connectionInfo(connectionNameOfUpAndRunningPtpInterface());
    if (!connectionInfo.first.isNull())
    {
        if (NetworkInterface::writeDefaultGatewayInfo())
            connected(connectionInfo.first, connectionInfo.second);
        else
            vpnDisconnect(true);
    }
    else
        onRouteAdded(NetworkInterface::null, 0);

    NetworkInterfaceMonitor::instance()->subscribe(this);
    NetworkInterfaceMonitor::instance()->start();
}

void ConnectionManager::onVpnTaskOutput(const QString& strOutputLine)
{
    //   qDebug() << "ConnectionManager::onVpnTaskOutput(const QString&" << strOutputLine << ")";

    if (strOutputLine.trimmed().length() > 0)
        m_pConnectionInformation->appendLogPlainText((strOutputLine + '\n').toLatin1().constData());

    //   qDebug() << "ConnectionManager::onVpnTaskOutput(const QString&" << strOutputLine << ") -> finished";
}

void ConnectionManager::onVpnTaskReadyReadLog()
{
    //   qDebug() << "ConnectionManager::onVpnTaskReadyReadLog()";

    char acBuf[1024];

    qint64 iRet;
    do
    {
        iRet = m_pVPNControlTask->readLogLine(acBuf, sizeof(acBuf));
        if (iRet > 0)
            m_pConnectionInformation->appendLogPlainText(acBuf);

    } while (iRet != -1);

    //   qDebug() << "ConnectionManager::onVpnTaskReadyReadLog() -> finished";
}

void ConnectionManager::onVpnTaskErrorMsg(int iErrorCode)
{
    //   qDebug() << "ConnectionManager::onVpnTaskErrorMsg(int" << iErrorCode << ")";

    char acBuf[1024];

    const qint64 iLineLength(m_pVPNControlTask->readErrorLine(acBuf, sizeof(acBuf)));
    if (iLineLength > 0)
    {
        m_pConnectionInformation->appendLogColorText(QColor(255, 0, 0), acBuf);
        error(iErrorCode);
    }

    //   qDebug() << "ConnectionManager::onVpnTaskErrorMsg(int" << iErrorCode << ") -> finished";
}

void ConnectionManager::onVpnTaskTimeout()
{
    //   qDebug() << "ConnectionManager::onVpnTaskTimeout()";

    if (m_fIsExecuting)
    {
        m_pConnectionInformation->appendLogColorText(QColor(255, 0, 0), "Last command timed out\n");

        m_fIsExecuting = !m_pVPNControlTask->stop(1000);

        if ((m_pState->isState(ConnectionState::Connecting) || m_pState->isState(ConnectionState::Disconnecting)))
            error(500);
    }

    //   qDebug() << "ConnectionManager::onVpnTaskTimeout() -> finished";
}

void ConnectionManager::onVpnTaskFinished()
{
    //   qDebug() << "ConnectionManager::onVpnTaskFinished()";

    m_pTimeout->stop();
    m_fIsExecuting = false;

    //   qDebug() << "ConnectionManager::onVpnTaskFinished() -> finished";
}

void ConnectionManager::onConnectionAdded(const QString& strName)
{
    //   qDebug() << "ConnectionManager::onConnectionAdded(const QString&" << strName << ")";

    if (m_pTrayIconMenu && m_pActions)
    {
        m_pActions->append(new QAction(strName, this));
        m_pActions->last()->setData(strName);
        m_pActions->last()->setToolTip(tr("Click to establish a vpn connection to '%1'").arg(strName));

        if (m_pState->isState(ConnectionState::NotConnected) || m_pState->isState(ConnectionState::Error))
            m_pActions->last()->setEnabled(true);
        else
            m_pActions->last()->setEnabled(false);

        m_pTrayIconMenu->insertAction(action(DISC), m_pActions->last());
    }

    //   qDebug() << "ConnectionManager::onConnectionAdded(const QString&" << strName << ") -> finished";
}

void ConnectionManager::onConnectionRemoved(const QString& strName)
{
    //   qDebug() << "ConnectionManager::onConnectionRemoved(const QString&" << strName << ")";

    if (m_pTrayIconMenu && m_pActions)
    {
        QAction* pAction(NULL);
        for (int i = QUIT + 1; !pAction && i < m_pActions->size(); i++)
        {
            if (m_pActions->at(i)->text() == strName)
                pAction = m_pActions->at(i);
        }

        if (pAction)
        {
            m_pTrayIconMenu->removeAction(pAction);
            m_pActions->removeAll(pAction);
            delete pAction;
        }
    }

    //   qDebug() << "ConnectionManager::onConnectionRemoved(const QString&" << strName << ") -> finished";
}

void ConnectionManager::onRouteAdded(NetworkInterface interface, unsigned int iPriority)
{
    //   qDebug() << "ConnectionManager::onRouteAdded(" << interface.name().c_str() << ", " << iPriority << ")";

    if (interface.isNull() || (!interface.isPtP() && iPriority != 100))
    {
        bool fHasDefaultGateway(false);
        if (!interface.isNull())
            fHasDefaultGateway = interface.hasDefaultGateway();
        else
            fHasDefaultGateway = NetworkInterface::defaultGateway().size() == 1;

        if (m_pState && (m_pState->isState(ConnectionState::NotConnected) || m_pState->isState(ConnectionState::Error)) && fHasDefaultGateway)
        {
            //               qDebug() << "ConnectionManager::onRouteAdded: found default gateway";

            enableAllConnections(true);

            ConnectionSettings settings;
            const int iConnections(settings.connections());

            bool fDone(false);
            for (int i = 0; !fDone && i < iConnections; i++)
            {
                const QString strName(settings.connection(i));
                if (settings.commonSettings(strName).autoConnect())
                {
                    fDone = true;
                    emit autoConnect(strName);
                }
            }
        }
    }

    //   qDebug() << "ConnectionManager::onRouteAdded(" << interface.name().c_str() << ", " << iPriority << ") -> finished";
}

void ConnectionManager::onRouteDeleted(NetworkInterface interface, unsigned int iPriority)
{
    //   qDebug() << "ConnectionManager::onRouteDeleted(" << interface.name().c_str() << ", " << iPriority << ")";

    if (!interface.isPtP() && iPriority != 100)
    {
        if (interface.isDefaultGateway() && (*interface.routeEntries().begin()).ip().toIPv4Address() == 0)
        {
            const bool fHasDefGateway(NetworkInterface::defaultGateway().size() == 1);
            if (!fHasDefGateway)
            {
                enableAllConnections(false);
                if (m_pState && m_pState->isState(ConnectionState::Connected))
                    vpnDisconnect();
            }
        }
    }

    //   qDebug() << "ConnectionManager::onRouteDeleted(" << interface.name().c_str() << ") -> finished";
}

void ConnectionManager::onAddressAdded(NetworkInterface interface)
{
    //   qDebug() << "ConnectionManager::onPtpInterfaceIsUpAnRunning(" << interface.name().c_str() << ")";

    if (interface.isPtP() && (m_pState->isState(ConnectionState::Connecting) || m_pState->isState(ConnectionState::NotConnected) || m_pState->isState(ConnectionState::Error)))
    {
        const QString strConnectionName(ConnectionManager::connectionName(interface, 5));
        if (!strConnectionName.isNull())
            connected(strConnectionName, interface);
    }

    //   qDebug() << "ConnectionManager::onPtpInterfaceIsUpAnRunning(" << interface.name().c_str() << ", " << iPriority << ") -> finished";
}

void ConnectionManager::onPtpInterfaceIsDeleted(NetworkInterface interface)
{
    //   qDebug() << "ConnectionManager::onPtpInterfaceIsDeleted(" << interface.name().c_str() << ")";
    if (!m_pState) return;
    if ((m_pState->isState(ConnectionState::Connected) || m_pState->isState(ConnectionState::Disconnecting)))
    {
        const QString strConnectionName(ConnectionManager::connectionName(interface));
        if (!strConnectionName.isNull())
            disConnected();
    }
    if (m_pState && m_pState->isState(ConnectionState::Connected) && interface.isDefaultGateway())
        vpnDisconnect();

    //   qDebug() << "ConnectionManager::onPtpInterfaceIsDeleted(" << interface.name().c_str() << ") -> finished";
}

void ConnectionManager::onCheckPtpInterfaceIsUp()
{
    if (!m_fIsExecuting && m_pState->isState(ConnectionState::Connecting))
    {
        const ConnectionInfo connectionInfo(connectionNameOfUpAndRunningPtpInterface());
        if (connectionInfo.first.isNull())
            disConnected();
        else
            connected(connectionInfo.first, connectionInfo.second);
    }
}

void ConnectionManager::onCheckPtpInterfaceIsDown()
{
    if (!m_fIsExecuting && m_pState->isState(ConnectionState::Disconnecting))
    {
        const ConnectionInfo connectionInfo(connectionNameOfUpAndRunningPtpInterface());
        if (connectionInfo.first.isNull())
            disConnected();
        else
            connected(connectionInfo.first, connectionInfo.second);
    }
}

QAction* ConnectionManager::action(ActionType type) const
{
    return(m_pActions != NULL ? m_pActions->at(type) : NULL);
}

void ConnectionManager::enableAllConnections(bool fEnable) const
{
    for (int i = QUIT + 1; i < m_pActions->size(); i++)
        m_pActions->at(i)->setEnabled(fEnable);
}

void ConnectionManager::connected(const QString& strConnectionName, const NetworkInterface& ptpInterface)
{
    const QString strGateway(ConnectionSettings().gateway(strConnectionName));

    m_pVPNControlTask->setConnectionName(strConnectionName);

    delete m_pState;

    m_pState = new Connected(m_pTrayIcon, strGateway, ptpInterface);

    updateContextMenu(true);
}

void ConnectionManager::disConnected()
{
    delete m_pState;

    m_pState = new NotConnected(m_pTrayIcon);

    updateContextMenu(true);
}

void ConnectionManager::error(int iErrorCode)
{
    if (!m_pState->isState(ConnectionState::NotConnected))
    {
        const ConnectionSettings settings;
        const QString strGateway(settings.ipsecSettings(m_pVPNControlTask->connectionName()).gateway());
        const bool fDisconnecting(!m_pState->isState(ConnectionState::Connecting));

        delete m_pState;
        m_pState = new Error(m_pTrayIcon, strGateway, iErrorCode, fDisconnecting);
        updateContextMenu(true);

        vpnDisconnect(true);
    }
}

ConnectionManager::ConnectionInfo ConnectionManager::connectionNameOfUpAndRunningPtpInterface() const
{

    QString strConnectionName;

    NetworkInterface::InterfaceMap interfaces(NetworkInterface::pointToPointInterfaces());


    NetworkInterface::InterfaceMap::const_iterator itInterfaces = interfaces.begin();
    for (; strConnectionName.isNull() && itInterfaces != interfaces.end(); ++itInterfaces)
    {
        strConnectionName = ConnectionManager::connectionName((*itInterfaces).second);

    }
    return(ConnectionInfo(strConnectionName, strConnectionName.isNull() ? NetworkInterface::null : (*--itInterfaces).second));
}

QString ConnectionManager::connectionName(const NetworkInterface& interface, int iRetry)
{
    QString strConnectionName;

    const NetworkInterface::AddressEntries addressEntries(interface.addressEntries());
    NetworkInterface::AddressEntries::const_iterator addressIterator(addressEntries.begin());
    for (bool fFound = false; !fFound && addressIterator != addressEntries.end(); addressIterator++)
    {
        // QFile connectionNameMap(strRuntimePath + (*addressIterator).broadcast().toString());
        QFile connectionNameMap(strRuntimePath + "connectionName.info");


        for (int i = 0; !fFound && i < iRetry; i++)
        {
            if (connectionNameMap.exists())
            {
                if (connectionNameMap.open(QFile::ReadOnly))
                {
                    strConnectionName = connectionNameMap.readLine();
                    if (!strConnectionName.isEmpty())
                        fFound = true;

                    connectionNameMap.close();
                }
            }
            else
                ::sleep(1);
        }
    }

    return(strConnectionName.trimmed());
}
