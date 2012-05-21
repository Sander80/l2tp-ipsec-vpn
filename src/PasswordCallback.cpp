/*
 * $Id: PasswordCallback.cpp 144 2012-05-21 07:31:37Z wejaeger $
 *
 * File:   PasswordCallback.cpp
 * Author: Werner Jaeger
 *
 * Created on September 1, 2010, 4:20 PM
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

#include <stdlib.h>
// #include <syslog.h>
#include <unistd.h>

#include <QObject>

#include "settings/ConnectionSettings.h"
#include "util/SecretsChecker.h"
#include "L2tpIPsecVpnApplication.h"
#include "PasswordCallback.h"

PasswordCallback::PasswordCallback(L2tpIPsecVpnApplication& application) : m_Application(application)
{
}

PasswordCallback::~PasswordCallback()
{
}

int PasswordCallback::exec() const
{
//   ::syslog(LOG_DEBUG|LOG_AUTH, "%s", "Executing password callback");

   int iRet(1);

   const QString strPassword(SecretsChecker::getSecret(m_Application.argv()[1]));

   if (!strPassword.isNull())
   {
      const int iPwdLength = strPassword.length();
      const int iPwdFileDescriptor = ::atoi(m_Application.argv()[3]);
      if (iPwdFileDescriptor >= 0)
      {
         const int iWritten = ::write(iPwdFileDescriptor, strPassword.toAscii().constData(), iPwdLength);
         if (iWritten == iPwdLength)
         {
//            ::syslog(LOG_DEBUG|LOG_AUTH, "%s", "Password found");
            iRet = 0;
         }
      }
   }

   return(iRet);
}
