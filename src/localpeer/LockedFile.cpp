/*
 * $Id: LockedFile.cpp 146 2012-05-28 11:37:01Z wejaeger $
 *
 * File:   LockedFile.cpp
 * Author:  Werner Jaeger
 *
 * Created on September 2, 2010, 6:42 PM
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

#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

#include "LockedFile.h"

LockedFile::LockedFile() : QFile(), m_LockMode(NoLock)
{
}

LockedFile::LockedFile(const QString& strName) : QFile(strName), m_LockMode(NoLock)
{
}

LockedFile::~LockedFile()
{
   if (isOpen())
      unlock();
}

bool LockedFile::open(OpenMode mode)
{
   bool fRet(false);

   if (!(mode & QIODevice::Truncate))
   {
      fRet = QFile::open(mode);

      const char* const pcSudoUid(::getenv("SUDO_UID"));
      if (fRet && pcSudoUid)
      {
         const uid_t uiUid(::strtol(pcSudoUid, NULL, 0));
         if (uiUid)
         {
            const char* const pcSudoGid(::getenv("SUDO_GID"));
            const uid_t uiGid(pcSudoGid ? ::strtol(pcSudoGid, NULL, 0) : 0);

            if (::chown(fileName().toUtf8().constData(), uiUid, uiGid) != 0)
            {
               fRet = false;
               qWarning("LockedFile::open(): Failed to chown() lock file with uid %d and gid %d.", uiUid, uiGid);
            }
         }
      }
      else if (fRet)
      {
         const char* const pcUser(::getenv("USER"));
         if (pcUser)
         {
            const struct passwd* pPasswd(::getpwnam(pcUser));
            if (pPasswd)
            {
               if (::chown(fileName().toUtf8().constData(), pPasswd->pw_uid, pPasswd->pw_gid) != 0)
               {
                  fRet = false;
                  qWarning("LockedFile::open(): Failed to chown() lock file with uid %d and gid %d.", pPasswd->pw_uid, pPasswd->pw_gid);
               }
            }
         }
      }
   }
   else
      qWarning("LockedFile::open(): Truncate mode not allowed.");

   return(fRet);
}

bool LockedFile::lock(LockMode mode, bool fBlock)
{
   bool fRet(false);

   if (isOpen())
   {
      if (mode != NoLock)
      {
         if (mode != m_LockMode)
         {
            if (m_LockMode != NoLock)
               unlock();

            struct flock fl;
            fl.l_whence = SEEK_SET;
            fl.l_start = 0;
            fl.l_len = 0;
            fl.l_type = (mode == ReadLock) ? F_RDLCK : F_WRLCK;

            if (::fcntl(handle(),  fBlock ? F_SETLKW : F_SETLK, &fl) != -1)
            {
               m_LockMode = mode;
               fRet = true;
            }
            else
            {
               if (errno != EINTR && errno != EAGAIN)
                  qWarning("LockedFile::lock(): fcntl: %s", ::strerror(errno));
            }
         }
         else
            fRet = true;
      }
      else
         fRet = unlock();
   }
   else
      qWarning("LockedFile::lock(): file is not opened");

   return(fRet);
}

bool LockedFile::unlock()
{
   bool fRet(false);

   if (isOpen())
   {
      if (isLocked())
      {
         struct flock fl;
         fl.l_whence = SEEK_SET;
         fl.l_start = 0;
         fl.l_len = 0;
         fl.l_type = F_UNLCK;

         if (::fcntl(handle(), F_SETLKW, &fl) != -1)
         {
            m_LockMode = NoLock;
            fRet = true;
         }
         else
            qWarning("LockedFile::lock(): fcntl: %s", ::strerror(errno));
      }
      else
         fRet = true;
   }
   else
      qWarning("LockedFile::unlock(): file is not opened");

   return(fRet);
}

bool LockedFile::isLocked() const
{
   return(m_LockMode != NoLock);
}

LockedFile::LockMode LockedFile::lockMode() const
{
   return(m_LockMode);
}