/*
 * $Id: VpnClientConnection.cpp 50 2012-05-21 07:32:02Z wejaeger $
 *
 * File:   VpnClientConnection.cpp
 * Author: Werner Jaeger
 *
 * Created on August 26, 2010, 8:26 AM
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
#include <fcntl.h>
#include <pwd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <unistd.h>

#include <QCoreApplication>
#include <QLocalSocket>
#include <QFile>

#include "VpnClientConnection.h"

enum CommandType { PROCESS, PIPE, INTERNAL };

static const char* const SYSLOGUSERNAME = "syslog";
static const QFile XL2TPCONTROLPIPE("/var/run/xl2tpd/l2tp-control");
static const QFile CONNECTIONNAMEINFO("/var/run/L2tpIPsecVpnControlDaemon/connectionName.info");
static const QFile DEFAULTGATEWAYINFO("/var/run/L2tpIPsecVpnControlDaemon/defaultgateway.info");

struct
{
    QString strCommand;
    quint8 iArgc;
    CommandType iType;
    QFile* pPipe;
}
/*
   static COMMANDS[] =
   {
   {"service pcscd start", 0, PROCESS, NULL},
   {"service pcscd stop", 0, PROCESS, NULL},
   {"ipsec setup start", 0, PROCESS, NULL},
   {"ipsec setup stop", 0, PROCESS, NULL},
   {"service xl2tpd start", 0, PROCESS, NULL},
   {"service xl2tpd stop", 0, PROCESS, NULL},
   {"service rsyslog start", 0, PROCESS, NULL},
   {"service rsyslog stop", 0, PROCESS, NULL},
   {"ipsec auto --ready", 0, PROCESS, NULL},
   {"ipsec auto --up", 1, PROCESS, NULL},
   {"ipsec auto --down", 1, PROCESS, NULL},
   {"ipsec auto --rereadall", 0, PROCESS, NULL},
   {"c", 1, PIPE, const_cast<QFile*>(&XL2TPCONTROLPIPE)},
   {"d", 1, PIPE, const_cast<QFile*>(&XL2TPCONTROLPIPE)},
   {"createVpnLogPipe", 1, INTERNAL, NULL},
   {"writeConnectionNameImfo", 1, INTERNAL, const_cast<QFile*>(&CONNECTIONNAMEINFO)},
   {"writeDefaultGatewayImfo", 1, INTERNAL, const_cast<QFile*>(&DEFAULTGATEWAYINFO)},
   {"quit", 0, INTERNAL, NULL},
   };
   */
static COMMANDS[] =
{
    {"service pcscd start", 0, PROCESS, NULL},
    {"service pcscd stop", 0, PROCESS, NULL},
    //{"strongswan start", 0, PROCESS, NULL},
    //{"strongswan stop", 0, PROCESS, NULL},
    {"ipsec start", 0, PROCESS, NULL},
    {"ipsec stop", 0, PROCESS, NULL},
    {"service xl2tpd start", 0, PROCESS, NULL},
    {"service xl2tpd stop", 0, PROCESS, NULL},
    {"service rsyslog start", 0, PROCESS, NULL},
    {"service rsyslog stop", 0, PROCESS, NULL},
    // {"strongswan status", 0, PROCESS, NULL},
    // {"strongswan up", 1, PROCESS, NULL},
    // {"strongswan down", 1, PROCESS, NULL},
    // {"strongswan rereadall", 0, PROCESS, NULL},
    {"ipsec status", 0, PROCESS, NULL},
    {"ipsec up", 1, PROCESS, NULL},
    {"ipsec down", 1, PROCESS, NULL},
    {"ipsec rereadall", 0, PROCESS, NULL},
    {"c", 1, PIPE, const_cast<QFile*>(&XL2TPCONTROLPIPE)},
    {"d", 1, PIPE, const_cast<QFile*>(&XL2TPCONTROLPIPE)},
    {"createVpnLogPipe", 1, INTERNAL, NULL},
    {"writeConnectionNameImfo", 1, INTERNAL, const_cast<QFile*>(&CONNECTIONNAMEINFO)},
    {"writeDefaultGatewayImfo", 1, INTERNAL, const_cast<QFile*>(&DEFAULTGATEWAYINFO)},
    {"quit", 0, INTERNAL, NULL},
};


static const size_t NOOFCOMMANDS = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

VpnClientConnection::VpnClientConnection(QLocalSocket* pSocket, QObject* pParent) : QObject(pParent), m_pStream(new QTextStream),
    m_pSocket(pSocket), m_pProcess(new QProcess), m_strActiveCommand(QString::null)
{
    if (m_pSocket)
    {
        ::syslog(LOG_DEBUG|LOG_DAEMON, "%s", "Opening client connection");

        m_pSocket->setParent(this);
        connect(m_pSocket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(m_pSocket, SIGNAL(disconnected()), SLOT(deleteLater()));
        m_pStream->setDevice(m_pSocket);

        m_pProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(m_pProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(m_pProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onCommandError(QProcess::ProcessError)));
        connect(m_pProcess, SIGNAL(finished(int)), this, SLOT(onCommandFinished(int)));
    }
    else
        deleteLater();
}

VpnClientConnection::~VpnClientConnection()
{

    ::syslog(LOG_DEBUG|LOG_DAEMON, "%s", "Closing client connection");

    if (m_pSocket && m_pSocket->state() == QLocalSocket::ConnectedState && send(INFORMATION, CLOSED))
        m_pSocket->close();

    delete m_pProcess;
    delete m_pStream;
}

void VpnClientConnection::readyRead()
{
    if (m_pSocket->canReadLine())
    {
        QString strResponseLine;
        while ((strResponseLine = m_pStream->readLine()).length() > 0)
        {
            QStringList strCommandParts(strResponseLine.split(' ', QString::SkipEmptyParts));
            const int iParts(strCommandParts.count());

            if (iParts > 0)
            {
                bool fIsCommand;
                const unsigned int iCommand = strCommandParts[0].toUInt(&fIsCommand);
                if (fIsCommand && iCommand < NOOFCOMMANDS)
                {
                    QString strCommand(COMMANDS[iCommand].strCommand);
                    for (int i = 1; i < iParts; i++)
                        strCommand.append(" " + strCommandParts[i]);

                    if (COMMANDS[iCommand].iArgc == (iParts - 1))
                    {
                        switch (COMMANDS[iCommand].iType)
                        {
                            case PROCESS:
                                m_strActiveCommand = strCommand;
                                ::syslog(LOG_DEBUG|LOG_DAEMON, "Executing command %s", m_strActiveCommand.toLatin1().constData());
                                m_pProcess->start(m_strActiveCommand, QProcess::ReadOnly);
                                break;

                            case PIPE:
                                if (COMMANDS[iCommand].pPipe->open(QIODevice::WriteOnly))
                                {
                                    if (COMMANDS[iCommand].pPipe->write(strCommand.toLatin1().constData()) == strCommand.length())
                                        send(RESULT, OK, strCommand);
                                    else
                                        send(RESULT, ERR_WRITE_PIPE, strCommand);

                                    COMMANDS[iCommand].pPipe->close();
                                }
                                else
                                    send(RESULT, ERR_OPEN_PIPE, strCommand);
                                break;

                            case INTERNAL:
                                switch (iCommand)
                                {
                                    case CMD_CREATE_VPN_LOGPIPE:
                                        {
                                            ResponseResult result(OK);

                                            QProcess::execute(COMMANDS[CMD_STOP_RSYSLOGD].strCommand);
                                            if (::mkfifo(strCommandParts[1].toLatin1().constData(), DEFFILEMODE) == 0)
                                            {
                                                const int iChmodResult(::chmod(strCommandParts[1].toLatin1().constData(), DEFFILEMODE));
                                                if (iChmodResult)
                                                    result = ERR_CHMOD_VPN_LOG_PIPE;

                                                struct passwd* const pPwdInfo = ::getpwnam(SYSLOGUSERNAME);
                                                if (pPwdInfo)
                                                {
                                                    const int iChownResult(::chown(strCommandParts[1].toLatin1().constData(), pPwdInfo->pw_uid, pPwdInfo->pw_gid));
                                                    if (iChownResult)
                                                        result = ERR_CHOWN_VPN_LOG_PIPE;
                                                }
                                            }
                                            else
                                                result = ERR_CREATE_VPN_LOG_PIPE;

                                            const int iStartResult(QProcess::execute(COMMANDS[CMD_START_RSYSLOGD].strCommand));
                                            if (iStartResult)
                                                result = ERR_START_SYSLOG_DAEMON;

                                            send(RESULT, result, strCommand);
                                        }
                                        break;

                                    case CMD_WRITE_CONNECTIONNAME_INFO:
                                    case CMD_WRITE_DEFAULT_GATEWAY_INFO:
                                        {
                                            if (COMMANDS[iCommand].pPipe->open(QIODevice::WriteOnly | QIODevice::Truncate))
                                            {
                                                bool fOk(true);
                                                for (int i = 1; fOk && i < iParts; i++)
                                                {
                                                    const QString str(strCommandParts[i].replace('\3', '\n'));
                                                    if (COMMANDS[iCommand].pPipe->write(str.toLatin1().constData()) != str.length())
                                                        fOk = false;

                                                    if (fOk && i < iParts -1)
                                                    {
                                                        if (COMMANDS[iCommand].pPipe->write(" ") != 1)
                                                            fOk = false;
                                                    }
                                                }

                                                if (fOk)
                                                    send(RESULT, OK, strCommand);
                                                else
                                                    send(RESULT, ERR_WRITE_PIPE, strCommand);

                                                COMMANDS[iCommand].pPipe->close();
                                            }
                                            else
                                                send(RESULT, ERR_OPEN_PIPE, strCommand);
                                        }
                                        break;

                                    case CMD_QUIT:
                                        QCoreApplication::quit();
                                        break;

                                    default:
                                        Q_ASSERT(false);
                                }
                                break;

                            default:
                                Q_ASSERT(false);
                        }
                    }
                    else
                        send(RESULT, ERR_INALID_NO_OF_ARGUMENTS, strCommand);
                }
                else
                    send(RESULT, ERR_UNKNOWN_CMD, "unknown");
            }
        }
    }
}

void VpnClientConnection::readyReadStandardOutput()
{
    while (m_pProcess->canReadLine())
    {
        const QByteArray bytes(m_pProcess->readLine());
        if (bytes.count() > 0)
            send(OUTPUT, bytes.data());
    }
}

void VpnClientConnection::onCommandError(QProcess::ProcessError iError)
{
    ::syslog(LOG_DEBUG|LOG_DAEMON, "Command %s finished with error code %d", m_strActiveCommand.toLatin1().constData(), ERR_COMMAND_FAILED_TO_START + iError);

    send(RESULT, static_cast<ResponseResult>(ERR_COMMAND_FAILED_TO_START + iError), m_strActiveCommand);
}

void VpnClientConnection::onCommandFinished(int iExitCode)
{
    ::syslog(LOG_DEBUG|LOG_DAEMON, "Command %s finished with exit code %d", m_strActiveCommand.toLatin1().constData(), iExitCode);

    send(RESULT, static_cast<ResponseResult>(iExitCode), m_strActiveCommand);
}

bool VpnClientConnection::send(ResponseType responseType, ResponseResult resultCode, const QString& strCommand)
{
    bool fRet = false;

    if (m_pSocket->state() == QLocalSocket::ConnectedState)
    {
        m_pSocket->write((QString::number(responseType) + " " + QString::number(resultCode) + " " + strCommand + '\n').toLatin1().constData());
        fRet = true;
    }

    return(fRet);
}

bool VpnClientConnection::send(ResponseType responseType, ResponseInformation responseInformation)
{
    bool fRet = false;

    if (m_pSocket->state() == QLocalSocket::ConnectedState)
    {
        m_pSocket->write((QString::number(responseType) + " " + QString::number(responseInformation) + '\n').toLatin1().constData());
        fRet = true;
    }

    return(fRet);
}

bool VpnClientConnection::send(ResponseType responseType, const QString& strOutputline)
{
    bool fRet = false;

    if (m_pSocket->state() == QLocalSocket::ConnectedState)
    {
        m_pSocket->write((QString::number(responseType) + " " + strOutputline).toLatin1().constData());
        fRet = true;
    }

    return(fRet);
}
