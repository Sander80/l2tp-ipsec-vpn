/*
 * $Id: SecretsChecker.h 24 2010-10-07 12:35:00Z werner $
 *
 * File:   SecretsChecker.h
 * Author: wejaeger
 *
 * Created on October 3, 2010, 8:50 AM
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

#ifndef SECRETSCHECKER_H
#define	SECRETSCHECKER_H

#include <QString>
#include <QFile>

class PppSettings;
class PppEapSettings;

class SecretsChecker
{
public:
   explicit SecretsChecker(const QString& strConnectionName);
   virtual ~SecretsChecker();

   bool check() const;

   static QString getSecret(const QString& strIdentity);

private:
   SecretsChecker(const SecretsChecker& orig);
   SecretsChecker& operator=(const SecretsChecker& orig);

   static bool promptAndStoreSecret(const QString& strTitle, const QString& strLabel, const PppSettings& pppSettings);

   static QString readSecret(const PppSettings& pppSettings);

   static QString getSecretsFilePath(const PppSettings& pppSettings);

   const QString& m_strConnectionName;
};

#endif	/* SECRETSCHECKER_H */

