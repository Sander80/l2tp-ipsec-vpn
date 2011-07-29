/*
 * $Id: Pkcs12.h 76 2011-04-16 07:11:33Z werner $
 *
 * File:   Pkcs12.h
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

#ifndef PKCS12_H
#define	PKCS12_H

#include <openssl/pkcs12.h>

#include <QObject>
#include <QString>

class CertificateInfo;

class Pkcs12 : public QObject
{
public:
   Pkcs12(const QString& strFilenamePath, const QString& strPassphrase);
   virtual ~Pkcs12();
   const QString& error() const { return(m_strError); }
   const QString issuer() const;
   const QString cn() const;
   const QString serialNumber() const;
   bool hasPrivateKey() const { return(m_pKey); }
   int caCerts() const { return(::sk_num(reinterpret_cast<const stack_st*>(m_pAdditionalCerts))); }
   bool cert2Pem(const QString& strFilenamePath);
   int caChain2Pem(const QString& strFilenamePath);
   bool privateKey2Pem(const QString& strFilenamePath, const QString& strPassphrase);

private:
   Pkcs12(const Pkcs12& orig);
   Pkcs12& operator=(const Pkcs12& orig);

   void parse(const QString& strFilenamePath, const QString& strPassphrase);

   PKCS12* m_p12Cert;
   EVP_PKEY* m_pKey;
   X509*  m_pX509Cert;
   STACK_OF(X509)* m_pAdditionalCerts;
   QString m_strError;
   const CertificateInfo* m_pCertificateInfo;
};

#endif	/* PKCS12_H */

