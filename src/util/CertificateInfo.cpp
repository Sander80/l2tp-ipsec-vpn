/*
 * $Id: CertificateInfo.cpp 151 2012-08-03 16:42:07Z wejaeger $
 *
 * File:   CertificateInfo.cpp
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

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QMultiMap>
#include <QSslCertificate>
#include <openssl/x509.h>

#include "CertificateInfo.h"

CertificateInfo::CertificateInfo(const QString& strFilePath) : m_strFilePath(strFilePath), m_pQSslCertificate(readCert(strFilePath))
{
}

CertificateInfo::CertificateInfo(const QByteArray& data) : m_strFilePath(""), m_pQSslCertificate(new QSslCertificate(data, QSsl::Der))
{
}

CertificateInfo::~CertificateInfo()
{
   if (m_pQSslCertificate)
      delete m_pQSslCertificate;
}

QString CertificateInfo::path() const
{
   return(QFileInfo(m_strFilePath).path());
}

QString CertificateInfo::fileName() const
{
   return(QFileInfo(m_strFilePath).fileName());
}

QString CertificateInfo::filePath() const
{
   return(m_strFilePath);
}

bool CertificateInfo::isReadable() const
{
   return(m_pQSslCertificate && !m_pQSslCertificate->isNull());
}

QString CertificateInfo::serialNumber() const
{
   QString strRet;

   if (isReadable())
      strRet = m_pQSslCertificate->serialNumber();

   return(strRet);
}

QString CertificateInfo::cn() const
{
   QString strRet;

   if (isReadable())
      strRet = m_pQSslCertificate->subjectInfo(QSslCertificate::CommonName);

   return(strRet);
}

QString CertificateInfo::issuer() const
{
   QString strRet;

   if (isReadable())
      strRet = m_pQSslCertificate->issuerInfo(QSslCertificate::CommonName);

   return(strRet);
}

QString CertificateInfo::email() const
{
   QString strRet;

   if (isReadable())
   {
      const QByteArray tag("emailAddress");
      strRet = m_pQSslCertificate->subjectInfo(tag);
      if (strRet.isNull())
         strRet = alternateSubjectName(QSsl::EmailEntry);
   }

   return(strRet);
}

bool CertificateInfo::toPem(const QString& strPemFilePath) const
{
   QFile pemFile(strPemFilePath);
   bool fRet(pemFile.open(QFile::WriteOnly));


   if (fRet)
   {
      fRet = (pemFile.write(m_pQSslCertificate->toPem()) != -1);
      pemFile.close();
   }

   return(fRet);
}

QString CertificateInfo::alternateSubjectName(const QSsl::AlternateNameEntryType type) const
{
   QString strRet;

   if (isReadable())
   {
      const QMultiMap<QSsl::AlternateNameEntryType, QString> alternateSubjectNames(m_pQSslCertificate->alternateSubjectNames());

      const QMultiMap<QSsl::AlternateNameEntryType, QString>::iterator it(alternateSubjectNames.constFind(type));

      if (it != alternateSubjectNames.end())
         strRet = it.value();
   }

   return(strRet);
}

QSslCertificate* CertificateInfo::readCert(const QString& strFilePath)
{
   QFile file(strFilePath);
   file.open(QFile::ReadOnly);

   QSslCertificate* pQSslCertificate(new QSslCertificate(&file));

   file.close();

   return(pQSslCertificate);
}