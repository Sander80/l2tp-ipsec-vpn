/*
 * $Id: SmartCardInfo.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   SmartCardInfo.h
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

#ifndef SMARTCARDINFO_H
#define	SMARTCARDINFO_H

#include <QString>

class CertificateInfo;

class SmartCardInfo
{
public:
   SmartCardInfo(const Pkcs11& p11, CK_OBJECT_HANDLE ulObjectHandle);
   virtual ~SmartCardInfo();

   const QString& serialNo() const { return(m_strSerialNo); }
   const QString& manufacturer() const { return(m_strManufacturer); }
   const QString& bitLength() const { return(m_strBitLength); }
   const QString& cardLabel() const { return(m_strCardLabel); }
   const QString& slotId() const { return(m_strSlotId); }
   const QString& objectLabel() const { return(m_strObjectLabel); }
   const QString& objectId() const { return(m_strObjectId); }
   const CertificateInfo& certificateInfo() const;

private:
   SmartCardInfo(const SmartCardInfo& orig);
   SmartCardInfo& operator=(const SmartCardInfo& orig);

   void loadToken(const Pkcs11& p11, CK_OBJECT_HANDLE ulObjectHandle);

   static QString BNOneLine(const BIGNUM* pBigNumber);

   QString m_strSerialNo;
   QString m_strManufacturer;
   QString m_strBitLength;
   QString m_strCardLabel;
   QString m_strSlotId;
   QString m_strObjectLabel;
   QString m_strObjectId;

   CertificateInfo* m_pCertificateInfo;
};

#endif	/* SMARTCARDINFO_H */

