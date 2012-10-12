/*
 * $Id: CertificateInfo.h 151 2012-08-03 16:42:07Z wejaeger $
 *
 * File:   CertificateInfo.h
 * Author: Werner Jaeger
 *
 * Created on July 27, 2010, 6:09 PM
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

#ifndef CERTIFICATEINFO_H
#define	CERTIFICATEINFO_H

#include <QSsl>

class QSslCertificate;

class CertificateInfo
{
public:
   explicit CertificateInfo(const QString& strFilePath);
   explicit CertificateInfo(const QByteArray& data);
   virtual ~CertificateInfo();

   QString path() const;
   QString fileName() const;
   QString filePath() const;
   bool isReadable() const;
   QString serialNumber() const;
   QString cn() const;
   QString issuer() const;
   QString email() const;
   bool toPem(const QString& strPemFilePath) const;

private:
   CertificateInfo(const CertificateInfo& orig);
   CertificateInfo& operator=(const CertificateInfo& orig);

   QString alternateSubjectName(const QSsl::AlternateNameEntryType type) const;

   static QSslCertificate* readCert(const QString& strFilePath);

   QString m_strFilePath;
   QSslCertificate* const m_pQSslCertificate;
};

#endif	/* CERTIFICATEINFO_H */

