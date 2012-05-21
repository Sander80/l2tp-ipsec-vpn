/*
 * $Id: main.cpp 149 2012-05-29 08:42:45Z wejaeger $
 *
 * File:   main.cpp
 * Author: Werner Jaeger
 *
 * Created on July 7, 2010, 5:40 PM
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

#include <pwd.h>
#include <syslog.h>
#include <unistd.h>

#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QFile>
#include <QTranslator>

#include "pkcs11/Pkcs11.h"
#include "settings/ConnectionSettings.h"
#include "settings/Preferences.h"
#include "ConnectionManager.h"
#include "ConnectionEditor.h"
#include "PasswordCallback.h"
#include "L2tpIPsecVpnApplication.h"

static const char* const DESKTOP_SESSION("DESKTOP_SESSION");
static const char* const PROCDIR("/proc/");

static void checkDesktop();
static uint effectiveUid();
void messageOutput(QtMsgType type, const char* pcMsg);

int main(int iArgc, char* pcArgv[])
{
   qInstallMsgHandler(messageOutput);

   const L2tpIPsecVpnApplication::APPLICATIONMODE mode(L2tpIPsecVpnApplication::parseCmdLine(iArgc, pcArgv));

   if (mode != L2tpIPsecVpnApplication::PASSWORD_CALLBACK && mode != L2tpIPsecVpnApplication::APPLYSETTINGS && mode != L2tpIPsecVpnApplication::DELETEALLCONFFILES)
      checkDesktop();

   L2tpIPsecVpnApplication app(iArgc, pcArgv, mode);

   const QString strLocale(QLocale::system().name());
   QTranslator translator;
   translator.load(QString(":/nls/") + strLocale);
   app.installTranslator(&translator);

   int iRet(0);

   if (app.mode() == L2tpIPsecVpnApplication::CONNECTION_EDITOR || app.mode() == L2tpIPsecVpnApplication::CONNECTION_EDITOR_STARTER || app.mode() == L2tpIPsecVpnApplication::APPLYSETTINGS || app.mode() == L2tpIPsecVpnApplication::DELETEALLCONFFILES || app.mode() == L2tpIPsecVpnApplication::PASSWORD_CALLBACK || !app.isRunning())
   {
      Q_INIT_RESOURCE(L2tpIPsecVpn);

      const QString strPkcs11Lib(Preferences().openSSLSettings().pkcs11Path());

      if (!Pkcs11::loaded())
      {
         if (!strPkcs11Lib.isEmpty())
            iRet = Pkcs11::loadLibrary(strPkcs11Lib, true) ? 0 : 2;
      }

      if (iRet == 0)
      {
         switch (app.mode())
         {
            case L2tpIPsecVpnApplication::CONNECTION_MANAGER:
            {
               ConnectionManager manager(app);
               iRet = manager.exec();
            }
            break;

            case L2tpIPsecVpnApplication::APPLYSETTINGS:
            case L2tpIPsecVpnApplication::CONNECTION_EDITOR:
            {
               ConnectionEditor connectionEditor(app);
               iRet = connectionEditor.exec();
            }
            break;

            case L2tpIPsecVpnApplication::PASSWORD_CALLBACK:
            {
               PasswordCallback callback(app);
               iRet = callback.exec();
            }
            break;

            case L2tpIPsecVpnApplication::CONNECTION_EDITOR_STARTER:
               iRet = app.startConnectionEditorDialog(true);
               break;

            case L2tpIPsecVpnApplication::DELETEALLCONFFILES:
               iRet = ConnectionSettings().deleteAllConfFiles();
               break;

            default:
               Q_ASSERT(false);
               break;
         }
         Pkcs11::closeLibrary(strPkcs11Lib, true);
      }
      else
         QMessageBox::critical(NULL, app.applicationName(), QObject::tr("I couldn't load PKCS11 library %1.").arg(Preferences().openSSLSettings().pkcs11Path()));
   }

   return(iRet);
}

void messageOutput(QtMsgType type, const char* pcMsg)
{
   switch (type)
   {
     case QtDebugMsg:
#ifndef QT_NO_DEBUG
        ::syslog(LOG_DEBUG, "%s", pcMsg);
#endif
         break;

     case QtWarningMsg:
        ::syslog(LOG_WARNING, "%s", pcMsg);
         break;

     case QtCriticalMsg:
        ::syslog(LOG_CRIT, "%s", pcMsg);
         break;

     case QtFatalMsg:
        ::syslog(LOG_EMERG, "%s", pcMsg);
         abort();
     }
 }

/**
 * If no windows manager is set,
 * probe the environment to automatically guess one.
 **/
static void checkDesktop()
{
   // if no desktop is given, look if one is passed via command line
   const char* const pcDesktopSession(::getenv(DESKTOP_SESSION));
   if (!pcDesktopSession)
   {
      // no desktop is set and no desktop is given on the command line.
      // most likely we are called via sudo
      // try to test for at least very well known running desktop managers
      const uint uiUid(effectiveUid());

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
               QFile cmdLineFile(PROCDIR + strPid + "/comm");
               if (cmdLineFile.open(QFile::ReadOnly))
               {
                  const QString strCli(cmdLineFile.readAll());
                  if (strCli.startsWith("gnome-session"))
                  {
                    fDone = true;
                    ::setenv(DESKTOP_SESSION, "gnome", 0);
                  }
                  else if (strCli.startsWith("ksmserver"))
                  {
                     fDone = true;
                     ::setenv(DESKTOP_SESSION, "kde", 0);
                  }
                  else if (strCli.startsWith("xfce4-session"))
                  {
                     fDone = true;
                     ::setenv(DESKTOP_SESSION, "xfce", 0);
                  }
               }
               else
                  qWarning() << "Failed to open proc command line file" << cmdLineFile.fileName();
            }
         }
      }
   }
}

static uint effectiveUid()
{
   uint uiUid(::getuid());

   const char* const pcSudoUid(::getenv("SUDO_UID"));
   if (pcSudoUid)
   {
      const uid_t uiSudoUid(::strtol(pcSudoUid, NULL, 0));
      if (uiSudoUid)
         uiUid = uiSudoUid;
   }
   else
   {
      const char* const pcUser(::getenv("USER"));
      if (pcUser)
      {
         const struct passwd* pPasswd(::getpwnam(pcUser));
         if (pPasswd)
            uiUid = pPasswd->pw_uid;
      }
   }

   return(uiUid);
}
