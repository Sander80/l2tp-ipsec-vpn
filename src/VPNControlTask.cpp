/*
 * $Id: VPNControlTask.cpp 143 2012-05-11 10:33:15Z wejaeger $
 *
 * File:   VPNControlTask.cpp
 * Author: Werner Jaeger
 *
 * Created on July 8, 2010, 5:09 PM
  *
 * Copyright 2010 Werner Jaeger.
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

#include <QProcess>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QTextStream>
#include <QSocketNotifier>
#include <QMessageBox>
//#include <QDebug>

#include <unistd.h>
#include <fcntl.h>

#include "conf/ConfWriter.h"
#include "settings/ConnectionSettings.h"
#include "util/VpnControlDaemonClient.h"

#include "VPNControlTask.h"
#include "ConnectionManager.h"

static const QFile xl2tpdPid("/var/run/xl2tpd.pid");

static const char* const strVpnLogPipeName("/var/log/l2tpipsecvpn.pipe");
static const char* const PROCDIR("/proc/");

static const QRegExp RE_LOG_SPLITLINE("\\s(?=\\w+\\[\\d+\\]\\:\\s)");
static const QRegExp RE_LOG_CAP_CERTIFICATEID("\\'(\\d\\:\\d{1,3})\\'");

static const QString STR_LOG_MATCH_IPSEC_CONNECTIONADDED("added connection description ");
static const char* const STR_LOG_MATCH_IPSECSAESTABLISHED("IPsec SA established");

static const char* const STR_LOG_MATCH_CERTIFICATELOADERROR("Error loading certificate");
static const char* const STR_LOG_MATCH_AUTHFAILURE("Authentication failure");
static const char* const STR_LOG_MATCH_AUTHFAILED("LCP terminated by peer (Authentication failed)");
static const char* const STR_LOG_MATCH_NO_DATA("No data from BIO_read");
static const char* const STR_LOG_MATCH_PEERAUTHFAILED("but I couldn't find any suitable secret (password) for it to use to do so.");
static const char* const STR_CONNECT_TIMEOUT("(Timeout)");

static const int ERR_INTERRUPTED(98);
static const int ERR_CONNECTING_TO_CONTROL_DAEMON(99);
static const int ERR_FAILED_TO_SET_DEFAULT_GATEWAY_INFO(230);
static const int ERR_IPSEC_SA_NOT_ESTABLISHED(300);
static const int ERR_LOADING_CERTIFICATE(400);
static const int ERR_AUTHENTICATION_FAILED(404);
static const int ERR_WRONG_CERTIFICATE(405);
static const int ERR_NO_SECRET_FOUND(406);
static const int ERR_CONNECT_TIMEOUT(410);

QFile VPNControlTask::m_vpnLogPipe(strVpnLogPipeName);

VPNControlTask::VPNControlTask(QObject* pParent) : QThread(pParent), m_pControlClient(new VpnControlDaemonClient), m_Action(Connect), m_iReturnCode(0),
   m_fIPSecConnectionAdded(false), m_fIPSecConnectionIsUp(false), m_pByteArray(new QByteArray()), m_pErrorStream(new QTextStream(m_pByteArray))
{
   clearVpnLogPipe();

   if (!m_vpnLogPipe.open(QIODevice::ReadWrite | QIODevice::Text))
      qWarning("Warning: VPNControlTask: Failed to open pipe %s", strVpnLogPipeName);

   ::fcntl(m_vpnLogPipe.handle(), F_SETFL, O_NONBLOCK);

   m_pVpnLogPipeNotifier = new QSocketNotifier(m_vpnLogPipe.handle(), QSocketNotifier::Read, pParent);

   connect(m_pVpnLogPipeNotifier, SIGNAL(activated(int)), SLOT(readyReadVpnLogPipe()));
}

VPNControlTask::~VPNControlTask()
{
   deleteControlClient();
   delete m_pErrorStream;
   delete m_pByteArray;
   delete m_pVpnLogPipeNotifier;
   m_vpnLogPipe.close();

}

void VPNControlTask::setConnectionName(const QString& strConnectionName)
{
   m_strConnectionName = strConnectionName;
}

const QString& VPNControlTask::connectionName() const
{
   return(m_strConnectionName);
}

VPNControlTask::Action VPNControlTask::action() const
{
   return(m_Action);
}

void VPNControlTask::setAction(Action action)
{
   m_Action = action;
}

int VPNControlTask::restartPcscDaemon()
{
//   qDebug() << "VPNControlTask::restartPcscDaemon()";connectionName

   if (createControlClient())
   {
      m_iReturnCode = 0;

      runAndWait(VpnClientConnection::CMD_START_PCSCD);
      runAndWait(VpnClientConnection::CMD_STOP_PCSCD);
      sleep(2);
   }


   deleteControlClient();

//   qDebug() << "VPNControlTask::restartPcscDaemon() -> finished";

   return(m_iReturnCode);
}

void VPNControlTask::run()
{
//   qDebug() << "VPNControlTask::run()";

   if (createControlClient())
   {
      m_pByteArray->clear();
      m_pErrorStream->reset();
      m_pErrorStream->resetStatus();
      m_iReturnCode = 0;
      m_fIPSecConnectionAdded = false;
      m_fIPSecConnectionIsUp = false;

      switch (m_Action)
      {
         case Connect:
            runConnect();
            break;

         case Disconnect:
            runDisconnect();
            break;
      }
   }

   deleteControlClient();

//   qDebug() << "VPNControlTask::run() -> finished";
}

/*!
 * \brief Tries to stop this running thread.
 *
 * \param iWaitMiliSeconds wait at most this time.
 * \return true if the thread was stopped successfully, false otherwise.
 */
bool VPNControlTask::stop(unsigned long iWaitMiliSeconds)
{
   m_iReturnCode = ERR_INTERRUPTED;
   exit(ERR_INTERRUPTED);
   return(wait(iWaitMiliSeconds));
}

bool VPNControlTask::createControlClient()
{
   deleteControlClient();
   m_pControlClient = new VpnControlDaemonClient;
   connect(m_pControlClient, SIGNAL(notifyResult(int, const QString&)), SLOT(onResult(int, const QString&)));
   connect(m_pControlClient, SIGNAL(notifyCommandOutput(const QString&)), SLOT(onCommandOutput(const QString&)));

   m_pControlClient->connectToServer();

   const bool fConnected(m_pControlClient->waitForConnected());

   if (!fConnected)
   {
      m_iReturnCode = ERR_CONNECTING_TO_CONTROL_DAEMON;
      emitErrorMsg("");
   }

   return(fConnected);
}

void VPNControlTask::deleteControlClient()
{
   if (m_pControlClient != NULL)
   {
      m_pControlClient->leave();
      m_pControlClient->deleteLater();
      m_pControlClient = NULL;
   }
}

void VPNControlTask::runConnect()
{
//   qDebug() << "VPNControlTask::runConnect()";

   const CommonSettings commonSettings(ConnectionSettings().commonSettings(m_strConnectionName));

   if (VPNControlTask::plutoIsRunning())
   {
      runAndWait(VpnClientConnection::CMD_STOP_IPSECD);

      while (VPNControlTask::plutoIsRunning())
         sleep(1);
   }

   if (xl2tpdPid.exists())
      runAndWait(VpnClientConnection::CMD_STOP_L2TPD);

   if (!NetworkInterface::writeDefaultGatewayInfo())
   {
      m_iReturnCode = ERR_FAILED_TO_SET_DEFAULT_GATEWAY_INFO;
      emitErrorMsg("");
   }
   else if (!commonSettings.disableIPSecEncryption())
      runAndWait(VpnClientConnection::CMD_START_IPSECD);

   if (m_iReturnCode == 0)
      runAndWait(VpnClientConnection::CMD_WRITE_CONNECTIONNAME_INFO, m_strConnectionName);

   if (m_iReturnCode == 0)
   {
      runAndWait(VpnClientConnection::CMD_START_L2TPD);

      if (m_iReturnCode == 0)
      {
         if (!commonSettings.disableIPSecEncryption())
         {
            if (!m_fIPSecConnectionAdded)
               exec();

            // avoid need --listen before --initiate error
            runAndWait(VpnClientConnection::CMD_IPSEC_READY);

            if (m_iReturnCode == 0)
            {
               runAndWait(VpnClientConnection::CMD_IPSEC_UP, m_strConnectionName);

               if (m_iReturnCode == 0 && !m_fIPSecConnectionIsUp)
               {
                  m_iReturnCode = ERR_IPSEC_SA_NOT_ESTABLISHED;
                  emitErrorMsg("IPsec");
               }

               if (m_iReturnCode == 0)
               {
                  sleep(1);
                  runAndWait(VpnClientConnection::CMD_L2TP_CONNECT, m_strConnectionName);
               }
            }
         }
         else
         {
            sleep(1);
            runAndWait(VpnClientConnection::CMD_L2TP_CONNECT, m_strConnectionName);
         }
      }
   }
//   qDebug() << "VPNControlTask::runConnect() -> finished";
}

void VPNControlTask::runDisconnect()
{
//   qDebug() << "VPNControlTask::runDisconnect()";

   const CommonSettings commonSettings(ConnectionSettings().commonSettings(m_strConnectionName));

   if (xl2tpdPid.exists())
      runAndWait(VpnClientConnection::CMD_STOP_L2TPD);

   if (m_iReturnCode == 0 && !commonSettings.disableIPSecEncryption())
      runAndWait(VpnClientConnection::CMD_STOP_IPSECD);

//   qDebug() << "VPNControlTask::runDisconnect() -> finished";
}

void VPNControlTask::runAndWait(VpnClientConnection::Command iCommand, const QString strArguments)
{
//   qDebug() << "VPNControlTask::runAndWait(Command" << iCommand << ", const QString&" <<  strArguments << ")";

   if (!m_pControlClient->start(iCommand, strArguments))
   {
      m_iReturnCode = ERR_CONNECTING_TO_CONTROL_DAEMON;
      emitErrorMsg("");
   }
   else
      exec();

//   qDebug() << "VPNControlTask::runAndWait(Command" << iCommand << ", const QString&" <<  strArguments << ") -> finished";
}

qint64 VPNControlTask::readLogLine(char* data, qint64 iMaxSize)
{
//   qDebug() << "VPNControlTask::readLogLine()";

   qint64 iRet(m_vpnLogPipe.readLine(data, iMaxSize));

   if (iRet > 0)
   {
      const QString strLine(data);
      const QStringList astrParts(strLine.split(RE_LOG_SPLITLINE));
      ::strcpy(data, astrParts.last().toAscii().data());
      iRet = ::strlen(data);

      if (::strstr(data, STR_LOG_MATCH_CERTIFICATELOADERROR) != NULL)
      {
         m_iReturnCode = ERR_LOADING_CERTIFICATE;
         if (RE_LOG_CAP_CERTIFICATEID.indexIn(data) > 0)
            emitErrorMsg(RE_LOG_CAP_CERTIFICATEID.cap(1));
         else
            emitErrorMsg("unknown");
      }
      if (::strstr(data, STR_LOG_MATCH_AUTHFAILED) != NULL || ::strstr(data, STR_LOG_MATCH_AUTHFAILURE) != NULL)
      {
         m_iReturnCode = ERR_AUTHENTICATION_FAILED;
         emitErrorMsg(connectionName());
      }
      else if (::strstr(data, STR_LOG_MATCH_NO_DATA))
      {
         m_iReturnCode = ERR_WRONG_CERTIFICATE;
         emitErrorMsg(connectionName());
      }
      else if (::strstr(data, STR_LOG_MATCH_PEERAUTHFAILED))
      {
         m_iReturnCode = ERR_NO_SECRET_FOUND;
         emitErrorMsg(connectionName());
      }
      else if (::strstr(data, STR_CONNECT_TIMEOUT))
      {
         m_iReturnCode = ERR_CONNECT_TIMEOUT;
         emitErrorMsg(connectionName());
      }
      else if (!m_fIPSecConnectionAdded)
      {
         m_fIPSecConnectionAdded = strLine.contains(STR_LOG_MATCH_IPSEC_CONNECTIONADDED + "\"" + connectionName() + "\"");
         if (m_fIPSecConnectionAdded) onResult(0, "");
      }
   }

//   qDebug() << "VPNControlTask::readLogLine() -> finished with" << iRet;

   return(iRet);
}

qint64 VPNControlTask::readErrorLine(char* data, qint64 iMaxSize)
{
//   qDebug() << "VPNControlTask::readErrorLine()";

   qint64 iRet(-1);

   QString strLine(m_pErrorStream->readLine(iMaxSize));
   if (!strLine.isNull())
   {
      strLine.append("\n");
      ::strcpy(data, strLine.toAscii().data());
      iRet = ::strlen(data);
   }

//   qDebug() << "VPNControlTask::readErrorLine() -> finished with" << iRet;

   return(iRet);
}

void VPNControlTask::readyReadVpnLogPipe()
{
   emit readyReadLog();
}

void VPNControlTask::onResult(int iReturnCode, const QString& strCommand)
{
//   qDebug() << "VPNControlTask::onResult(int" << iReturnCode << ", const String&" << strCommand << ")";

   m_iReturnCode = iReturnCode;

   exit(iReturnCode);

   if (iReturnCode != 0)
      emitErrorMsg(strCommand);

//   qDebug() << "VPNControlTask::onResult(int" << iReturnCode << ", const String&" << strCommand << ") -> finished";
}

void VPNControlTask::onCommandOutput(const QString& strOutputLine)
{
//   qDebug() << "VPNControlTask::onCommandOutput(const String&" << strOutputLine << ")";

   if (!m_fIPSecConnectionIsUp)
      m_fIPSecConnectionIsUp = strOutputLine.contains(STR_LOG_MATCH_IPSECSAESTABLISHED);

   emit commandOutputReceived(strOutputLine);

//   qDebug() << "VPNControlTask::onCommandOutput(const String&" << strOutputLine << ") --> finished";
}

void VPNControlTask::emitErrorMsg(const QString& strErrorContext)
{
//   qDebug() << "VPNControlTask::emitErrorMsg(const QString&" << strErrorContext << ")";

   const qint64 iPos(m_pErrorStream->pos());

   *m_pErrorStream << "[ERROR" << qSetFieldWidth(5) << right << m_iReturnCode << reset << "]   ";

   switch (m_iReturnCode)
   {
      case VpnClientConnection::CMD_UNKNOWN:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon did not recognize the command sent";
         break;

      case VpnClientConnection::ERR_INALID_NO_OF_ARGUMENTS:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon is complained about the number of arguments in command '" << strErrorContext << "'";
         break;

      case VpnClientConnection::ERR_COMMAND_FAILED_TO_START:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon: command '" << strErrorContext << "' failed to start";
         break;

      case VpnClientConnection::ERR_COMMAND_CRASHED_AFTER_START:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon: command '" << strErrorContext << "' crashed after starting successfully";
         break;

      case VpnClientConnection::ERR_COMMAND_TIMEDOUT:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon: command '" << strErrorContext << "' timed out";
         break;

      case VpnClientConnection::ERR_COMMAND_FAILED_TO_READ_FROM_PROCESS:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon: command '" << strErrorContext << "' an error occurred when attempting to read from the process";
         break;

      case VpnClientConnection::ERR_COMMAND_FAILED_TO_WRITE_TO_PROCESS:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon: command '" << strErrorContext << "' an error occurred when attempting to write to the process";
         break;

      case VpnClientConnection::ERR_COMMAND_FAILED_WITH_UNKNOW_ERROR:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon: command '" << strErrorContext << "' an unknown error occurred";
         break;

      case ERR_CONNECTING_TO_CONTROL_DAEMON:
         *m_pErrorStream << "L2tpIPsecVpnControlDaemon is either not started or connection to it failed";
         break;

      case VpnClientConnection::ERR_WRITE_PIPE:
         *m_pErrorStream << "Failed to write command '" << strErrorContext << "' to l2tp-control";
         break;

      case VpnClientConnection::ERR_OPEN_PIPE:
         *m_pErrorStream << "Failed to open l2tp control file '" << strErrorContext << "'";
         break;

      case VpnClientConnection::ERR_CREATE_VPN_LOG_PIPE:
      case VpnClientConnection::ERR_CHMOD_VPN_LOG_PIPE:
      case VpnClientConnection::ERR_CHOWN_VPN_LOG_PIPE:
         *m_pErrorStream << "Failed to open l2tp ipsec vpn log file '" << strErrorContext << "'";
         break;

      case VpnClientConnection::ERR_START_SYSLOG_DAEMON:
         *m_pErrorStream << "Failed to start syslog daemon '" << strErrorContext << "'";
         break;

      case ERR_FAILED_TO_SET_DEFAULT_GATEWAY_INFO:
         *m_pErrorStream << "No default gateway found or failed to write default gateway information '" << strErrorContext << "'";
         break;

      case ERR_IPSEC_SA_NOT_ESTABLISHED:
         *m_pErrorStream << "'" << strErrorContext << "' failed to negotiate or establish security associations";
         break;

      case ERR_LOADING_CERTIFICATE:
         *m_pErrorStream << "Error loading certificate with id '" << strErrorContext << "'";
         break;

      case ERR_AUTHENTICATION_FAILED:
         *m_pErrorStream << "Authentication failed: closing connection to '" << strErrorContext << "'";
         break;

      case ERR_WRONG_CERTIFICATE:
         *m_pErrorStream << "Peer did not accept certificate sent from smart card: closing connection to '" << strErrorContext << "'";
         break;

      case ERR_NO_SECRET_FOUND:
         *m_pErrorStream << "No secret found to authenticate  '" << strErrorContext << "'";
         break;

      case ERR_CONNECT_TIMEOUT:
         *m_pErrorStream << "Connection attempt to '" << strErrorContext << "' timed out";
         break;

      default:
         *m_pErrorStream << "Command '" << strErrorContext << "' failed and exited with given error code";
         break;
   }
   m_pErrorStream->flush();
   m_pErrorStream->seek(iPos);
   emit errorMessageEmited(m_iReturnCode);
//   qDebug() << "VPNControlTask::emitErrorMsg(const QString&" << strErrorContext << ") -> finished";
}

void VPNControlTask::clearVpnLogPipe()
{
   const int iVpnPipeFileDescriptor(::open(m_vpnLogPipe.fileName().toAscii().data(), O_RDONLY | O_NONBLOCK));

   if (iVpnPipeFileDescriptor != -1)
   {
      char* buf[1024];
      int iNoRead;

      do
         iNoRead = ::read(iVpnPipeFileDescriptor, buf, sizeof(buf));
      while (iNoRead > 0);

      ::close(iVpnPipeFileDescriptor);
   }
   else
   {
      const int iResult(VpnControlDaemonClient::execute(VpnClientConnection::CMD_CREATE_VPN_LOGPIPE, m_vpnLogPipe.fileName()));
      if (iResult != VpnClientConnection::OK)
      {
         if (iResult == 1)
            QMessageBox::critical(NULL, tr("A critical error occurred"), tr("L2tpIPsecVpnControlDaemon is not started"));
         else
            QMessageBox::critical(NULL, tr("A critical error occurred"), tr("Create vpn syslog pipe command failed with exit code: %1").arg(iResult));
      }
   }
}

/**
 * Lookup /proc to see if pluto is running
 **/
bool VPNControlTask::plutoIsRunning()
{
   const uint uiUid(0);

   QFileInfoList procList(QDir(PROCDIR).entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot));

   bool fDone(false);
   for (QFileInfoList::const_iterator procIt(procList.constBegin()); !fDone && procIt != procList.constEnd(); procIt++)
   {
      bool fOk(false);
      QString strPid((*procIt).fileName());
      strPid.toUInt(&fOk);

      if (fOk) // pid must be numeric, ignore every thing else
      {
         // is this process owned by the user
         if (uiUid == (*procIt).ownerId())
         {
            // we have a valid pid
            // open the cmdline file to determine what's the name of the process running
            QFile cmdLineFile(PROCDIR + strPid + "/cmdline");
            if (cmdLineFile.open(QFile::ReadOnly))
            {
               const QString strCli(cmdLineFile.readAll());
               if (strCli.startsWith("pluto"))
                  fDone = true;
            }
            else
               qWarning() << "Failed to open proc command line file" << cmdLineFile.fileName();
         }
      }
   }
   return(fDone);
}
