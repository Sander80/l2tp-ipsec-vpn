/*
 * $Id: L2tpIPsecVpnApplication.cpp 95 2011-07-29 00:37:43Z werner $
 *
 * File:   L2tpIPsecVpnApplication.cpp
 * Author: Werner Jaeger
 *
 * Created on August 9, 2010, 2:29 PM
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

#include <QMetaType>
#include <QLocalSocket>
#include <QProcess>
#include <QStyle>

#include "localpeer/LocalPeer.h"
#include "ConnectionManager.h"
#include "L2tpIPsecVpnApplication.h"
#include "ConnectionEditor.h"

static const char* const DESKTOP_SESSION("DESKTOP_SESSION");
static const char* const CONNECTIONEDITOR_CMD_SWITCH("connectionEditor");
static const char* const START_CONNECTIONEDITOR_CMD_SWITCH("startConnectionEditor");
static const char* const APPLYSETTINGS_CMD_SWITCH("applySettings");
static QString const DESKTOP_SESSION_CMD_SWITCH("desktopSession");
static QString const APPLICATIONNAME("L2TP IPsec VPN Manager");
static QString const GKSUDO_CMD("gksudo -D \"" + APPLICATIONNAME + "\" ");
static QString const CONNECTION_ADDED_MSG_PREFIX("connectionAdded:");
static QString const CONNECTION_REMOVED_MSG_PREFIX("connectionRemoved:");

L2tpIPsecVpnApplication::L2tpIPsecVpnApplication(int& iArgc, char** ppArgv, APPLICATIONMODE appMode) : QApplication(iArgc, ppArgv, appMode != PASSWORD_CALLBACK && appMode != APPLYSETTINGS), m_Mode(appMode), m_pProcess(new QProcess), m_pLocalPeer(new LocalPeer())
{
   setOrganizationName("WernerJaeger");
   setOrganizationDomain("wejaeger.com");
   setApplicationName(APPLICATIONNAME);
   setApplicationVersion("1.0.0");
   setObjectName("L2tpIPsecVpn");
   qRegisterMetaType<NetworkInterface>("NetworkInterface");
   qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");

   connect(m_pLocalPeer, SIGNAL(messageReceived(const QString&)), SLOT(onMessageReceived(const QString&)));
   connect(m_pProcess, SIGNAL(finished(int)), this, SLOT(onConnectionEditorDialogClosed(int)));

   if (mode() == CONNECTION_MANAGER)
      setQuitOnLastWindowClosed(false);
}

L2tpIPsecVpnApplication::~L2tpIPsecVpnApplication()
{
   delete m_pLocalPeer;
   delete m_pProcess;
}

bool L2tpIPsecVpnApplication::isRunning()
{
   return(m_pLocalPeer->isClient());
}

L2tpIPsecVpnApplication::APPLICATIONMODE L2tpIPsecVpnApplication::mode() const
{
   return(m_Mode);
}

bool L2tpIPsecVpnApplication::sendConnectionAddedMessage(const QString& strConnectionName)
{
   return(m_pLocalPeer->sendMessage(CONNECTION_ADDED_MSG_PREFIX + strConnectionName, 5000));
}

bool L2tpIPsecVpnApplication::sendConnectionRemovedMessage(const QString& strConnectionName)
{
   return(m_pLocalPeer->sendMessage(CONNECTION_REMOVED_MSG_PREFIX + strConnectionName, 5000));
}

int L2tpIPsecVpnApplication::startConnectionEditorDialog(bool fDetached) const
{
   int iRet(0);

   const char* const pcDesktopSession(::getenv(DESKTOP_SESSION));
   const QString strProgram(GKSUDO_CMD + arguments()[0] + " " + CONNECTIONEDITOR_CMD_SWITCH + " " + (pcDesktopSession ? DESKTOP_SESSION_CMD_SWITCH + " " + pcDesktopSession : ""));

   if (fDetached)
      iRet = !QProcess::startDetached(strProgram);
   else
      m_pProcess->start(strProgram);

   return(iRet);
}

void L2tpIPsecVpnApplication::onMessageReceived(const QString& strMessage)
{
   if (strMessage.startsWith(CONNECTION_ADDED_MSG_PREFIX))
      emit connectionAdded(strMessage.mid(strMessage.indexOf(':') + 1));
   else if (strMessage.startsWith(CONNECTION_REMOVED_MSG_PREFIX))
      emit connectionRemoved(strMessage.mid(strMessage.indexOf(':') + 1));
}

void L2tpIPsecVpnApplication::onConnectionEditorDialogClosed(int iExitCode)
{
   emit connectionEditorDialogClosed(iExitCode);
}

L2tpIPsecVpnApplication::APPLICATIONMODE L2tpIPsecVpnApplication::parseCmdLine(int& iArgc, char* pcArgv[])
{
   APPLICATIONMODE retMode(CONNECTION_MANAGER);

   int iQtArgs(0);
   bool fDone(false);
   for (int i(1); !fDone && i < iArgc; i++)
   {
      if (::strcmp(pcArgv[i], CONNECTIONEDITOR_CMD_SWITCH) == 0)
      {
         retMode = CONNECTION_EDITOR;
         fDone = true;
      }
      else if (::strcmp(pcArgv[i], START_CONNECTIONEDITOR_CMD_SWITCH) == 0)
      {
         retMode = CONNECTION_EDITOR_STARTER;
         fDone = true;
      }
      else if (::strcmp(pcArgv[i], APPLYSETTINGS_CMD_SWITCH) == 0)
      {
         retMode = APPLYSETTINGS;
         fDone = true;
      }
      else if (i + 1 < iArgc && DESKTOP_SESSION_CMD_SWITCH == pcArgv[i])
         ::setenv(DESKTOP_SESSION, pcArgv[i + 1], 0);
      else if (pcArgv[i][0] == '-')
         iQtArgs++;
   }

   if ((iArgc - iQtArgs) == 4 && retMode == CONNECTION_MANAGER)
      retMode = PASSWORD_CALLBACK;

   return(retMode);
}
