/*
 * $Id: SmartCardInfo.cpp 36 2011-01-28 08:23:14Z werner $
 *
 * File:   SmartCardInfo.cpp
 * Author: Werner Jaeger
 *
 * Created on August 1, 2010, 2:13 PM
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

#include <QStringList>

#include <openssl/bn.h>
#include <openssl/crypto.h>

#include "util/CertificateInfo.h"
#include "util/ErrorEx.h"
#include "Pkcs11.h"
#include "SmartCardInfo.h"

SmartCardInfo::SmartCardInfo(const Pkcs11& p11, CK_OBJECT_HANDLE ulObjectHandle) : m_pCertificateInfo(NULL)
{
   loadToken(p11, ulObjectHandle);
}

SmartCardInfo::~SmartCardInfo()
{
   if (m_pCertificateInfo)
      delete m_pCertificateInfo;
}

const CertificateInfo& SmartCardInfo::certificateInfo() const
{
   return(*m_pCertificateInfo);
}

void SmartCardInfo::loadToken(const Pkcs11& p11, CK_OBJECT_HANDLE ulObjectHandle)
{
   const QStringList tokenInfoList(p11.tokenInfo());
   m_strCardLabel = tokenInfoList[0];
   m_strManufacturer = tokenInfoList[1];
   m_strSerialNo = tokenInfoList[2];

   try
   {
      Pkcs11AttrUlong bitLengthAttribute(CKA_MODULUS_BITS);
      p11.loadAttribute(bitLengthAttribute, ulObjectHandle);
      m_strBitLength.setNum(bitLengthAttribute.getValue());
   }
   catch (ErrorEx &e)
   {
      // ignore
   }

   Pkcs11AttrData idAttribute(CKA_ID);
   p11.loadAttribute(idAttribute, ulObjectHandle);
   m_strObjectId = BNOneLine(idAttribute.getBignum());

   try
   {
      Pkcs11AttrData objectLabelAttribute(CKA_LABEL);
      p11.loadAttribute(objectLabelAttribute, ulObjectHandle);
      m_strObjectLabel = objectLabelAttribute.getText();
   }
   catch (ErrorEx &e)
   {
      // ignore
   }

   m_strSlotId.setNum(p11.slotId());

   Pkcs11AttrData x509ValueAttribute(CKA_VALUE);
   p11.loadAttribute(x509ValueAttribute, ulObjectHandle);
   const unsigned char* pcValue;

   const unsigned long ulLen(x509ValueAttribute.getValue(&pcValue));

   if (m_pCertificateInfo)
      delete m_pCertificateInfo;

   m_pCertificateInfo = new CertificateInfo(QByteArray::fromRawData(reinterpret_cast<const char*>(pcValue), ulLen));
}

QString SmartCardInfo::BNOneLine(const BIGNUM* pBigNumber)
{
   QString strRet;
   if (pBigNumber)
   {
      char* pcHex = ::BN_bn2hex(pBigNumber);
      strRet = pcHex;
      ::CRYPTO_free(pcHex);
   }
   return(strRet);
}
