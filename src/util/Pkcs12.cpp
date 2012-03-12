/*
 * $Id: Pkcs12.cpp 119 2012-03-02 10:11:22Z werner $
 *
 * File:   Pkcs12.cpp
 * Author: wejaeger
 *
 * Created on April 8, 2011, 11:48 AM
 *
 * Copyright 2011 Werner Jaeger.
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

#include <stdio.h>
#include <errno.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include "pkcs11/Pkcs11.h"
#include "CertificateInfo.h"
#include "Pkcs12.h"

/*!
    \class Pkcs12

    \brief The Pkcs12 class is for manipulating certificate bundles in PKCS#12 fomat.

    A PKCS#12 file contains the certificate, private key and all the intermediate
    certificate's in a certificate chain and is encrypted with a password.
*/

static int passwordCallback(char* pcBuf, int iSize, int /* iRwFlag */, void* pvPassword)
{
   ::strncpy(pcBuf, reinterpret_cast<char*>(pvPassword), iSize);
   pcBuf[iSize - 1] = '\0';
   return(::strlen(pcBuf));
}


Pkcs12::Pkcs12(const QString& strFilenamePath, const QString& strPassphrase) : m_p12Cert(NULL), m_pKey(NULL), m_pX509Cert(NULL), m_pAdditionalCerts(NULL), m_strError(QString::null), m_pCertificateInfo(NULL)
{
   parse(strFilenamePath, strPassphrase);
}

Pkcs12::~Pkcs12()
{
   ::sk_X509_pop_free(m_pAdditionalCerts, ::X509_free);
   ::X509_free(m_pX509Cert);
   ::EVP_PKEY_free(m_pKey);
   ::PKCS12_free(m_p12Cert);

   if (m_pCertificateInfo)
      delete m_pCertificateInfo;
}

const QString Pkcs12::issuer() const
{
   QString strIssuer;

   if (m_pCertificateInfo)
      strIssuer = m_pCertificateInfo->issuer();

   return(strIssuer);
}

const QString Pkcs12::cn() const
{
   QString strCN;

   if (m_pCertificateInfo)
      strCN = m_pCertificateInfo->cn();

   return(strCN);
}

const QString Pkcs12::serialNumber() const
{
   QString strSN;

   if (m_pCertificateInfo)
      strSN = m_pCertificateInfo->serialNumber();

   return(strSN);
}

bool Pkcs12::cert2Pem(const QString& strFilenamePath)
{
   bool fRet(false);

   if (m_pX509Cert)
   {
      FILE* const pPemFile(::fopen(strFilenamePath.toUtf8().constData(), "wb"));

      if (pPemFile)
      {
         if (::PEM_write_X509(pPemFile, m_pX509Cert))
            fRet = true;
         else
            m_strError = tr("Writing certificate to") + "" + strFilenamePath + "" + tr("failed");

         ::fclose(pPemFile);
      }
      else
         m_strError = strFilenamePath + ": " + ::strerror(errno);
   }
   else
      m_strError = tr("No certificate found");

   return(fRet);
}

int Pkcs12::caChain2Pem(const QString& strFilenamePath)
{
   int iRet(0);

   const int iNoOfRootCerts(caCerts());

   if (iNoOfRootCerts > 0)
   {
      FILE* const pPemFile(::fopen(strFilenamePath.toUtf8().constData(), "wb"));

      if (pPemFile)
      {
         for (X509* pX509 = sk_X509_value(m_pAdditionalCerts, iRet); iRet != -1 && pX509; iRet++)
         {
            if (!::PEM_write_X509(pPemFile, pX509))
            {
               iRet = -1;
               m_strError = tr("Writing root certificate to") + "" + strFilenamePath + "" + tr("failed");
            }

            pX509 = sk_X509_value(m_pAdditionalCerts, iRet + 1);
         }

         ::fclose(pPemFile);
      }
      else
      {
         iRet = -1;
         m_strError = strFilenamePath + ": " + ::strerror(errno);
      }
   }

   return(iRet);
}

bool Pkcs12::privateKey2Pem(const QString& strFilenamePath, const QString& strPassphrase)
{
   bool fRet(false);

   if (m_pKey)
   {
      FILE* const pPemFile(::fopen(strFilenamePath.toUtf8().constData(), "wb"));

      if (pPemFile)
      {
         if (::PEM_write_RSAPrivateKey(pPemFile, m_pKey->pkey.rsa, ::EVP_des_ede3_cbc(), NULL, 0, passwordCallback, strPassphrase.toUtf8().data()))
            fRet = true;
         else
            m_strError = tr("Writing private key to") + "" + strFilenamePath + "" + tr("failed");

         ::fclose(pPemFile);
      }
      else
         m_strError = strFilenamePath + ": " + ::strerror(errno);
   }
   else
      m_strError = tr("No private key found");

   return(fRet);
}

void Pkcs12::parse(const QString& strFilenamePath, const QString& strPassphrase)
{
   FILE* const pP12File(::fopen(strFilenamePath.toUtf8().constData(), "rb"));

   if (pP12File)
   {
      ::ERR_clear_error();
      ::OPENSSL_add_all_algorithms_noconf();

      m_p12Cert = ::d2i_PKCS12_fp(pP12File, NULL);
      ::fclose(pP12File);

      if (m_p12Cert)
      {
         if (!::PKCS12_parse(m_p12Cert, strPassphrase.toUtf8().constData(), &m_pKey, &m_pX509Cert, &m_pAdditionalCerts))
         {
            m_pAdditionalCerts = NULL;

            const unsigned long lErr(::ERR_get_error());
            if (ERR_GET_LIB(lErr) == ERR_LIB_PKCS12 &&  ERR_GET_FUNC(lErr) == PKCS12_F_PKCS12_PARSE && ERR_GET_REASON(lErr) == PKCS12_R_MAC_VERIFY_FAILURE)
               m_strError = tr("Wrong passphrase");
            else
               m_strError = tr("Parse PKCS#12 file") + " " + strFilenamePath + " " + tr("failed");
         }
         else if (m_pX509Cert)
         {
            unsigned char* pcCert = NULL;
            const int iLen(::i2d_X509(m_pX509Cert, &pcCert));

            if (iLen >= 0)
               m_pCertificateInfo = new CertificateInfo(QByteArray::fromRawData(reinterpret_cast<const char*>(pcCert), iLen));

            ::OPENSSL_free(pcCert);
         }
      }
      else
         m_strError = tr("The file") + " " + strFilenamePath + " " + tr("is not a valid PKCS#12 certificate bundle");
   }
   else
      m_strError = strFilenamePath + ": " + ::strerror(errno);
}

