/*
 * $Id: LockedFile.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   LockedFile.h
 * Author:  Werner Jaeger
 *
 * Created on September 2, 2010, 6:42 PM
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

#include <QFile>

#ifndef LOCKEDFILE_H
#define	LOCKEDFILE_H

class LockedFile : public QFile
{
public:
   enum LockMode { NoLock = 0, ReadLock, WriteLock };

   LockedFile();
   LockedFile(const QString &strName);
   virtual ~LockedFile();

   bool open(OpenMode mode);

   bool lock(LockMode mode, bool fBlock = true);
   bool unlock();
   bool isLocked() const;
   LockMode lockMode() const;

private:
   LockedFile(const LockedFile& orig);
   LockedFile& operator=(const LockedFile& orig);

   LockMode m_LockMode;
};

#endif	/* LOCKEDFILE_H */

