/*
 * $Id: ConnectionManager.h 161 2017-12-25 10:26:31Z wejaeger $
 *
 * File:   ConnectionManager.h
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

#ifndef _CONNECTIONMANAGER_H
#define	_CONNECTIONMANAGER_H

#include <QObject>
#include <QtWidgets/QSystemTrayIcon>
#include <QPair>

#include "util/NetworkInterface.h"

class QSystemTrayIcon;
class ConnectionState;
class VPNControlTask;
class ConnectionInformationDialog;
class QAction;
class QTimer;
class L2tpIPsecVpnApplication;

class ConnectionManager : public QObject
{
   Q_OBJECT

public:
   explicit ConnectionManager(L2tpIPsecVpnApplication& application, QObject* pParent = 0);
   virtual ~ConnectionManager();

   int exec();

private slots:
   void vpnConnect(QAction* pAction);
   void vpnConnect(const QString& strConnectionName);
   void vpnDisconnect(bool fDontChangeStatus = false);
   void editConnections() const;
   void showConnectionInformation() const;
   void about() const;
   void iconActivated(QSystemTrayIcon::ActivationReason reason);
   void showMessage();
   void messageClicked();
   void detectConnectionState();
   void onVpnTaskOutput(const QString& strOutputLine);
   void onVpnTaskReadyReadLog();
   void onVpnTaskErrorMsg(int iErrorCode);
   void onVpnTaskTimeout();
   void onVpnTaskFinished();
   void onConnectionAdded(const QString& strName);
   void onConnectionRemoved(const QString& strName);
   void onRouteAdded(NetworkInterface interface, unsigned int iPriority);
   void onRouteDeleted(NetworkInterface interface, unsigned int iPriority);
   void onAddressAdded(NetworkInterface interface);
   void onPtpInterfaceIsDeleted(NetworkInterface interface);
   void onCheckPtpInterfaceIsUp();
   void onCheckPtpInterfaceIsDown();

signals:
   void autoConnect(const QString& strConnectionName);

private:
   typedef QList<QAction*> ActionList;
   typedef QPair<const QString, const NetworkInterface> ConnectionInfo;
   typedef enum { DISC, EDIT, INFO, ABOUT, QUIT } ActionType;

   ConnectionManager(const ConnectionManager& orig);
   ConnectionManager& operator=(const ConnectionManager& orig);

   void createActions();
   void createTrayIcon();
   void updateContextMenu(bool fStatusChanged);
   void enableAllConnections(bool fEnable) const;
   void connected(const QString& strConnectionName, const NetworkInterface& ptpInterface);
   void disConnected();
   void error(int iErrorCode);
   ConnectionInfo connectionNameOfUpAndRunningPtpInterface() const;

   QAction* action(ActionType type) const;

   static QString connectionName(const NetworkInterface& interface, int iRetry = 1);

   ConnectionInformationDialog* const m_pConnectionInformation;
   QTimer* const m_pTimeout;
   ActionList* const m_pActions;
   L2tpIPsecVpnApplication& m_Application;

   ConnectionState* m_pState;
   QSystemTrayIcon* m_pTrayIcon;
   QMenu* m_pTrayIconMenu;
   VPNControlTask* m_pVPNControlTask;
   volatile bool m_fIsExecuting;
};

#endif	/* _CONNECTIONMANAGER_H */
