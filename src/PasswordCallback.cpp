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
#include <QtWidgets/QInputDialog>
#include "settings/ConnectionSettings.h"
#include "util/SecretsChecker.h"
#include "L2tpIPsecVpnApplication.h"
#include "PasswordCallback.h"

PasswordCallback::PasswordCallback(L2tpIPsecVpnApplication& application) : m_Application(application)
{
}

PasswordCallback::PasswordCallback(QCoreApplication& application) : m_Application(application)
{
}

PasswordCallback::~PasswordCallback()
{
}

int PasswordCallback::exec() const
{
   int iRet(1);
   const QString strPassword(SecretsChecker::getSecret(m_Application.arguments()[1].toStdString().c_str()));
   if (!strPassword.isNull())
   {
      const int iPwdLength = strPassword.length();
      const int iPwdFileDescriptor = m_Application.arguments()[3].toInt();
      if (iPwdFileDescriptor >= 0)
      {
         const int iWritten = ::write(iPwdFileDescriptor, strPassword.toLatin1().constData(), iPwdLength);
         if (iWritten == iPwdLength)
         {
            iRet = 0;
            return iRet;
         }
      }
   }
   return(iRet);
}
