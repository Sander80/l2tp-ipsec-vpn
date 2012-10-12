/*
 * $Id: SmartCardObjectListModel.cpp 151 2012-08-03 16:42:07Z wejaeger $
 *
 * File:   SmartCardObjectListModel.cpp
 * Author: Werner Jaeger
 *
 * Created on August 2, 2010, 5:11 PM
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
#include <QFile>

#include "pkcs11/Pkcs11.h"
#include "util/CertificateInfo.h"

#include "pkcs11/SmartCardInfo.h"
#include "settings/Preferences.h"
#include "SmartCardObjectListModel.h"

SmartCardObjectListModel::SmartCardObjectListModel(ObjectType objectType) : m_ObjectType(objectType), m_pSmartCardObjects(new QList<SmartCardInfo*>())
{
   readTokens();
}

SmartCardObjectListModel::~SmartCardObjectListModel()
{
   if (m_pSmartCardObjects)
      delete m_pSmartCardObjects;
}

int SmartCardObjectListModel::rowCount(const QModelIndex& /* parent */) const
{
   return(m_pSmartCardObjects->count());
}

QVariant SmartCardObjectListModel::data(const QModelIndex& index, int iRole) const
{
   QVariant ret;

   if (index.isValid())
   {
      switch (iRole)
      {
         case Qt::DisplayRole:
            ret = value(index.row()).toAscii().constData();
            break;

         case Qt::ToolTipRole:
            if (m_ObjectType == Certificate)
            {
               const QString strEmail = m_pSmartCardObjects->at(index.row())->certificateInfo().email();
               const QString strCN = m_pSmartCardObjects->at(index.row())->certificateInfo().cn();
               const QString strSN = m_pSmartCardObjects->at(index.row())->certificateInfo().serialNumber();
               ret = (strSN.isEmpty() ? "" : "SN=" + strSN + ", ") + (strEmail.isEmpty() ? (strCN.isEmpty() ? "" : "CN=" + strCN) : "User=" + strEmail);
            }
            break;

         case Qt::UserRole:
            ret = idValue(index.row()).toAscii().constData();
            break;

         case Qt::UserRole + 1:
            ret = m_pSmartCardObjects->at(index.row())->certificateInfo().email();
            break;
      }
    }

   return(ret);
}

bool SmartCardObjectListModel::storeCert(const QModelIndex& index) const
{
   bool fRet(m_ObjectType == Certificate);

   if (fRet)
      fRet = m_pSmartCardObjects->at(index.row())->certificateInfo().toPem(idValue(index.row()));

   return(fRet);
}

void SmartCardObjectListModel::readTokens()
{
   if (Pkcs11::loaded())
   {
      Pkcs11 p11;

      const QList<unsigned long> slotList(p11.slotList());
      if (slotList.count() > 0)
      {
         for (int iSlotId = 0; iSlotId < slotList.count(); iSlotId++)
         {
            p11.startSession(slotList.at(iSlotId));

            switch (m_ObjectType)
            {
               case PublicKey:
               {
                  const Pkcs11Attlist publicKeyAttributeList(Pkcs11AttrUlong(CKA_CLASS, CKO_PUBLIC_KEY));
                  const QList<CK_OBJECT_HANDLE> publicKeyObjectHandleList(p11.objectList(publicKeyAttributeList));

                  for (int iObjectHandle = 0; iObjectHandle < publicKeyObjectHandleList.count(); iObjectHandle++)
                     m_pSmartCardObjects->append(new SmartCardInfo(p11, publicKeyObjectHandleList[iObjectHandle]));
               }
               break;

               case Certificate:
               {
                  Pkcs11Attlist certificateAttributeList(Pkcs11AttrUlong(CKA_CLASS, CKO_CERTIFICATE));
                  certificateAttributeList << Pkcs11AttrUlong(CKA_CERTIFICATE_TYPE, CKC_X_509);
                  const QList<CK_OBJECT_HANDLE> certificateObjectHandleList(p11.objectList(certificateAttributeList));

                  for (int iObjectHandle = 0; iObjectHandle < certificateObjectHandleList.count(); iObjectHandle++)
                     m_pSmartCardObjects->append(new SmartCardInfo(p11, certificateObjectHandleList[iObjectHandle]));
               }
               break;
            }
         }
      }
   }
}

QString SmartCardObjectListModel::value(int i) const
{
   QString strRet;

   if (i < m_pSmartCardObjects->count())
   {
      strRet.append(m_pSmartCardObjects->at(i)->cardLabel());
      strRet.append(", " + m_pSmartCardObjects->at(i)->manufacturer());
      strRet.append(", " + m_pSmartCardObjects->at(i)->slotId());
      strRet.append(", " + m_pSmartCardObjects->at(i)->objectId());
      strRet.append(", " + m_pSmartCardObjects->at(i)->objectLabel());
   }

   return(strRet);
}

QString SmartCardObjectListModel::idValue(int i) const
{
   QString strRet;

   if (i < m_pSmartCardObjects->count())
   {
      if (objectType() == Certificate)
         strRet = "/etc/ipsec.d/certs/" + m_pSmartCardObjects->at(i)->objectLabel() + ".pem";
      else
         strRet = Preferences().openSSLSettings().engineId() + ":" + m_pSmartCardObjects->at(i)->slotId() + ":" + m_pSmartCardObjects->at(i)->objectId();
   }


   return(strRet);
}