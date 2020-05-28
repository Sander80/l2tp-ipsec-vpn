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

#include <stdlib.h>
// #include <syslog.h>
#include <unistd.h>

#include <QObject>
#include <QtWidgets/QInputDialog>
#include "settings/ConnectionSettings.h"
#include "util/SecretsChecker.h"
#include "L2tpIPsecVpnApplication.h"
#include "PasswordCallback.h"
#include <QtWidgets/QMessageBox>
#include <QDir>
#include <sys/types.h>
#include <unistd.h>

PasswordCallback::PasswordCallback(L2tpIPsecVpnApplication& application) : m_Application(application)
{
}

//PasswordCallback::PasswordCallback(QCoreApplication& application) : m_Application(application)
//{
//}

PasswordCallback::~PasswordCallback()
{
}

int PasswordCallback::exec() const
{
    int iRet(1);
    bool fok = true;
    pid_t ppid = getppid();
    char buf[16];
    char buf_file[16];
    std::string filename = QDir(QDir::tempPath()).absolutePath().toStdString() + "/l2tp-ipsec-vpn.tmp";
    if (ppid) {
        sprintf(buf, "%d", ppid);
        FILE *fp = fopen(filename.c_str(), "r");
        if (fp) {
            if (fgets(buf_file,16,fp)) {
                if (!strncmp(buf,buf_file,16)) {
                    return 1;
                    // same pid requesting for answer again, but we already hit cancel
                }
            }
            fclose(fp);
        }
    }
    
    const QString strPassword(SecretsChecker::getSecret(m_Application.arguments()[1].toStdString().c_str(), &fok));

    if (fok)
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
        // we have an answer, let us remove the bad pid file
        unlink(filename.c_str());
    }
    else {
        // we hit cancel, should save bad pid
        if (ppid) {
            FILE *fpw = fopen(filename.c_str(), "w");
            if (fpw) {
                fputs(buf, fpw);
                fclose(fpw);
            }
        }
    }
    return(iRet);
}
