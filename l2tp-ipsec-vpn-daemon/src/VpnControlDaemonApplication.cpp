/*
 * $Id: VpnControlDaemonApplication.cpp 50 2012-05-21 07:32:02Z wejaeger $
 *
 * File:   VpnControlDaemonApplication.cpp
 * Author: Werner Jaeger
 *
 * Created on August 25, 2010, 4:57 PM
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

#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <unistd.h>

#include <QFile>
#include <QByteArray>
#include <QProcess>

#include "VpnControlDaemon.h"
#include "VpnControlDaemonApplication.h"

static const char* const KEY = "L2tpIPsecVpnControlDaemon";
static const char* const DEVNULL = "/dev/null";

static QFile pidFile("/var/run/L2tpIPsecVpnControlDaemon.pid");


static void terminationSignalhandler(int iSig)
{
   if (iSig == SIGTERM || iSig == SIGINT)
   {
      qApp->quit();
   }
}

VpnControlDaemonApplication::VpnControlDaemonApplication(int iArgc, char** ppArgv) : QCoreApplication(iArgc, ppArgv), m_pDaemon(new VpnControlDaemon(KEY))
{
}

VpnControlDaemonApplication::~VpnControlDaemonApplication()
{
   delete m_pDaemon;
}

int VpnControlDaemonApplication::daemonize() const
{
   int iRet(-1);

   const pid_t pid(::fork());
   if (pid >= 0)
   {
      if (pid == 0)
      {
         ::syslog(LOG_INFO|LOG_DAEMON, "Starting %s", KEY);

         if (createPidFile())
         {
            iRet = ::chdir("/");
            if (iRet >= 0)
            {
               ::close(STDIN_FILENO);
               if (::open(DEVNULL, O_RDWR) == STDIN_FILENO)
               {
                  if (::dup2(STDIN_FILENO, STDOUT_FILENO) == -1)
                     ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to redirect stdout to %s", DEVNULL);

                  if (::dup2(STDIN_FILENO, STDERR_FILENO) == -1)
                     ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to redirect stderr to %s", DEVNULL);
               }
               else
                  ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to redirect stdin to %s", DEVNULL);

               if (m_pDaemon->start())
               {
                  // Workaround: process needs to be started once otherwise no finished signal is emitted
                  QProcess process;
                  process.start("echo");

                  ::signal(SIGTERM, terminationSignalhandler);
                  ::signal(SIGINT, terminationSignalhandler);
                  ::syslog(LOG_INFO|LOG_DAEMON, "%s started", KEY);

                  iRet = exec();

                  ::syslog(LOG_INFO|LOG_DAEMON, "Stopping %s", KEY);

                  if (pidFile.exists())
                     pidFile.remove();

                  ::syslog(LOG_INFO|LOG_DAEMON, "%s stopped", KEY);
               }
               else
               {
                  ::syslog(LOG_CRIT|LOG_DAEMON, "%s", "Failed to start daemon");
                  iRet = 3;
               }
            }
            else
               ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to change to root directory: %m");
         }
         else
            iRet = 1;
      }
      else // parent
         iRet = 0;
   }
   else
      ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to fork daemon: %m");

   return(iRet);
}

bool VpnControlDaemonApplication::createPidFile()
{
   bool fRet(false);

   if (pidFile.open(QIODevice::ReadWrite))
   {
      const QByteArray abPid(pidFile.readAll());
      pidFile.close();

      const int iPid(abPid.count() == 0 ? 0 : abPid.toInt());

      if (!iPid || iPid == ::getpid() || ::kill(iPid, 0) != 0)
      {
         if (::setsid() >= 0)
         {
            if (pidFile.remove())
            {
               if (pidFile.open(QIODevice::WriteOnly))
               {
                  pidFile.write((QString::number(::getpid()) + '\n').toLatin1());
                  pidFile.close();
                  fRet = true;
               }
               else
                  ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to open pid file: %s", pidFile.fileName().toLatin1().constData());
            }
            else
               ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to unlink pid file: %s", pidFile.fileName().toLatin1().constData());
         }
         else
            ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to set SID: %m");
      }
      else
         ::syslog(LOG_CRIT|LOG_DAEMON, "There's already a %s running", KEY);
   }
   else
      ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to read pid file %s", pidFile.fileName().toLatin1().constData());

   return(fRet);
}
