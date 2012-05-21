/*
 * $Id: Pkcs11.cpp 130 2012-04-08 06:18:04Z wejaeger $
 *
 * File:   Pkcs11.cpp
 * Author: Werner Jaeger
 *
 * Created on July 31, 2010, 12:10 PM
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
#include "util/ErrorEx.h"
#include "Pkcs11.h"

CK_FUNCTION_LIST* Pkcs11::m_p11(NULL);
lt_dlhandle Pkcs11::m_pLoadedModuleHandle(NULL);

Pkcs11::Pkcs11() : m_ulSessionHandle(CK_INVALID_HANDLE), m_ulSlotId(0), m_ulObjectHandle(CK_INVALID_HANDLE)
{
}

Pkcs11::~Pkcs11()
{
   if (m_ulSessionHandle != CK_INVALID_HANDLE && m_p11)
      m_p11->C_CloseSession(m_ulSessionHandle);
}

void Pkcs11::startSession(unsigned long ulSlot, bool fRW)
{
   CK_RV rv;
   const unsigned long ulFlags(CKF_SERIAL_SESSION | (fRW ? CKF_RW_SESSION : 0));

   if (m_ulSessionHandle != CK_INVALID_HANDLE)
   {
      rv = m_p11->C_CloseSession(m_ulSessionHandle);
      if (rv != CKR_OK)
         pk11error("C_CloseSession", rv);
   }

   rv = m_p11->C_OpenSession(ulSlot, ulFlags, NULL, NULL, &m_ulSessionHandle);
   if (rv != CKR_OK)
      pk11error("C_OpenSession", rv);

   m_ulSlotId = ulSlot;
}

unsigned long Pkcs11::slotsAvailable() const
{
   unsigned long ulNumSlots(0L);

   const CK_RV rv(m_p11->C_GetSlotList(CK_FALSE, NULL_PTR, &ulNumSlots));

   if (rv != CKR_OK)
      pk11error("C_GetSlotList", rv);

   return(ulNumSlots);
}

QList<unsigned long> Pkcs11::slotList() const
{
   CK_RV rv;
   CK_SLOT_ID* p11Slots(NULL);
   QList<unsigned long> slotList;
   unsigned long ulNumSlots(0L);

   /* This one helps to avoid errors.
    * Fist time it fails, 2nd time it works */
   m_p11->C_GetSlotList(CK_TRUE, p11Slots, &ulNumSlots);
   while (true)
   {
      rv = m_p11->C_GetSlotList(CK_TRUE, p11Slots, &ulNumSlots);
      if (rv != CKR_OK && rv != CKR_BUFFER_TOO_SMALL)
         pk11error("C_GetSlotList", rv);

      if (ulNumSlots == 0)
         break;

      if ((rv == CKR_OK) && p11Slots)
         break;

      p11Slots = reinterpret_cast<CK_SLOT_ID*>(::realloc(p11Slots, ulNumSlots * sizeof (CK_SLOT_ID)));
      ErrorEx::checkOutOfMemory(p11Slots);
   }

   for (unsigned long ul = 0; ul < ulNumSlots; ul++)
   {
      CK_SLOT_INFO slotInfo;
      rv = m_p11->C_GetSlotInfo(p11Slots[ul], &slotInfo);

      if (rv == CKR_OK)
      {
         if ((slotInfo.flags & CKF_TOKEN_PRESENT) == CKF_TOKEN_PRESENT)
            slotList << p11Slots[ul];
      }
   }

   if (p11Slots)
      ::free(p11Slots);

   return(slotList);
}

QList<CK_MECHANISM_TYPE> Pkcs11::mechanismList(unsigned long ulSlot) const
{
   QList<CK_MECHANISM_TYPE> mechanismList;

   unsigned long ulCount;
   CK_RV rv(m_p11->C_GetMechanismList(ulSlot, NULL, &ulCount));

   if (ulCount != 0)
   {
      CK_MECHANISM_TYPE* const pMechanismType(reinterpret_cast<CK_MECHANISM_TYPE*>(::malloc(ulCount * sizeof(*pMechanismType))));
      ErrorEx::checkOutOfMemory(pMechanismType);

      rv = m_p11->C_GetMechanismList(ulSlot, pMechanismType, &ulCount);
      if (rv != CKR_OK)
         pk11error("C_GetMechanismList", rv);

      for (unsigned ul = 0; ul < ulCount; ul++)
         mechanismList << pMechanismType[ul];
   }
   return(mechanismList);
}

void Pkcs11::logout() const
{
   const CK_RV rv(m_p11->C_Logout(m_ulSessionHandle));
   if (rv != CKR_OK && rv != CKR_USER_NOT_LOGGED_IN)
      pk11error("C_Logout", rv);
}

bool Pkcs11::needsLogin(bool fAsSecurityOfficer) const
{
   bool fRet(true);

   CK_SESSION_INFO sinfo;

   const CK_RV rv(m_p11->C_GetSessionInfo(m_ulSessionHandle, &sinfo));
   if (rv != CKR_OK)
      pk11error("C_GetSessionInfo", rv);

   switch (sinfo.state)
   {
      case CKS_RO_PUBLIC_SESSION:
      case CKS_RW_PUBLIC_SESSION:
         fRet =  true;
         break;

      case CKS_RW_SO_FUNCTIONS:
         if (!fAsSecurityOfficer)
         {
            logout();
            fRet =  true;
         }
         else
            fRet = false;

         break;

      case CKS_RO_USER_FUNCTIONS:
      case CKS_RW_USER_FUNCTIONS:
         if (fAsSecurityOfficer)
         {
            logout();
            fRet =  true;
         }
         else
            fRet =  false;

         break;
   }

   return(fRet);
}

void Pkcs11::login(const unsigned char* pcPin, unsigned long ulPinlen, bool fAsSecurityOfficer) const
{
   const unsigned long ulUser(fAsSecurityOfficer ? CKU_SO : CKU_USER);

   const CK_RV rv(m_p11->C_Login(m_ulSessionHandle, ulUser, const_cast<unsigned char*>(pcPin), ulPinlen));
   if (rv != CKR_OK && rv != CKR_USER_ALREADY_LOGGED_IN)
      pk11error("C_Login", rv);
}

void Pkcs11::setPin(const unsigned char* pcOldPin, unsigned long ulOldPinLen, const unsigned char* pcPin, unsigned long ulPinLen) const
{
   const CK_RV rv(m_p11->C_SetPIN(m_ulSessionHandle, const_cast<unsigned char*>(pcOldPin), ulOldPinLen, const_cast<unsigned char*>(pcPin), ulPinLen));
   if (rv != CKR_OK)
      pk11error("C_SetPIN", rv);
}

void Pkcs11::initPin(const unsigned char* pcPin, unsigned long ulPinLen) const
{
   const CK_RV rv(m_p11->C_InitPIN(m_ulSessionHandle, const_cast<unsigned char*>(pcPin), ulPinLen));
   if (rv != CKR_OK)
      pk11error("C_InitPIN", rv);
}

QStringList Pkcs11::tokenInfo(CK_SLOT_ID ulSlotId) const
{
   CK_TOKEN_INFO tokenInfo;

   const CK_RV rv(m_p11->C_GetTokenInfo(ulSlotId, &tokenInfo));
   if (rv != CKR_OK)
      pk11error("C_GetTokenInfo", rv);

   QStringList tokeInfoList;
   tokeInfoList << ::utf82QString(tokenInfo.label, 32);
   tokeInfoList << ::utf82QString(tokenInfo.manufacturerID, 32);
   tokeInfoList << ::utf82QString(tokenInfo.serialNumber, 16);

   return(tokeInfoList);
}

QStringList Pkcs11::tokenInfo() const
{
   return(tokenInfo(m_ulSlotId));
}

bool Pkcs11::protectedAuthenticationPath(CK_SLOT_ID ulSlotId) const
{
   CK_TOKEN_INFO tokenInfo;
   const CK_RV rv(m_p11->C_GetTokenInfo(ulSlotId, &tokenInfo));

   if (rv != CKR_OK)
      pk11error("C_GetTokenInfo", rv);

   return(!!(tokenInfo.flags & CKF_PROTECTED_AUTHENTICATION_PATH));
}

bool Pkcs11::protectedAuthenticationPath() const
{
   return(protectedAuthenticationPath(m_ulSlotId));
}

void Pkcs11::loadAttribute(Pkcs11Attribute& attribute, CK_OBJECT_HANDLE ulObjectHandle) const
{
   attribute.load(m_ulSessionHandle, ulObjectHandle);
}

void Pkcs11::storeAttribute(Pkcs11Attribute& attribute, CK_OBJECT_HANDLE ulObjectHandle) const
{
   attribute.store(m_ulSessionHandle, ulObjectHandle);
}

CK_OBJECT_HANDLE Pkcs11::createObject(const Pkcs11Attlist& attrs) const
{
   CK_ATTRIBUTE *pAttributes;
   CK_OBJECT_HANDLE ulObjectHandle;

   const unsigned long ulNum(attrs.get(&pAttributes));
   const CK_RV rv(m_p11->C_CreateObject(m_ulSessionHandle, pAttributes, ulNum, &ulObjectHandle));
   if (rv != CKR_OK)
      pk11error("C_CreateObject", rv);

   return(ulObjectHandle);
}

QList<CK_OBJECT_HANDLE> Pkcs11::objectList(const Pkcs11Attlist& atts) const
{
   QList<CK_OBJECT_HANDLE> objectHandleList;

   CK_ATTRIBUTE* pAttribute;
   const unsigned long ulNoOfAttributes(atts.get(&pAttribute));
   CK_RV rv(m_p11->C_FindObjectsInit(m_ulSessionHandle, pAttribute, ulNoOfAttributes));

   if (rv != CKR_OK)
      pk11error("C_FindObjectsInit", rv);

   CK_OBJECT_HANDLE aObjectHandles[256];
   unsigned long ulLen;

   do
   {
      rv = m_p11->C_FindObjects(m_ulSessionHandle, aObjectHandles, 256, &ulLen);
      if (rv != CKR_OK)
         pk11error("C_FindObjects", rv);

      for (unsigned long ul = 0; ul < ulLen; ul++)
         objectHandleList += aObjectHandles[ul];
   }
   while (ulLen);

   rv = m_p11->C_FindObjectsFinal(m_ulSessionHandle);
   if (rv != CKR_OK)
      pk11error("C_FindObjectsFinal", rv);

   return(objectHandleList);
}

bool Pkcs11::loadLibrary(const QString& strFilePath, bool fSilent)
{
   if (!Pkcs11::closeLibrary(strFilePath, fSilent))
      return(false);

   CK_RV(*c_get_function_list)(CK_FUNCTION_LIST_PTR_PTR);

   ::lt_dlinit();

   if (m_pLoadedModuleHandle)
   {
      if (::lt_dlclose(m_pLoadedModuleHandle) < 0)
      {
         if (fSilent)
            return(false);

         throw ErrorEx("Failed to close PKCS11 library: " + strFilePath);
      }
   }

   if (strFilePath.isEmpty())
   {
      if (fSilent)
         return(false);

      throw ErrorEx("PKCS11 library filename empty");
   }

   m_pLoadedModuleHandle = ::lt_dlopen(::string2FileName(strFilePath));
   if (m_pLoadedModuleHandle == NULL)
   {
      if (fSilent)
         return(false);

      throw ErrorEx("Failed to open PKCS11 library: " + strFilePath);
   }

   /* Get the list of function pointers */
   c_get_function_list = (CK_RV(*)(CK_FUNCTION_LIST_PTR_PTR))lt_dlsym(m_pLoadedModuleHandle, "C_GetFunctionList");

   if (c_get_function_list)
   {
      if (c_get_function_list(&m_p11) == CKR_OK)
      {
         const CK_RV rv(m_p11->C_Initialize(NULL_PTR));

         if (rv != CKR_OK)
         {
            if (fSilent)
               return(false);

            pk11error("C_Initialize", rv);
         }

         return(true);
      }
   }

   /* This state is always worth an error ! */
   if (::lt_dlclose(m_pLoadedModuleHandle) == 0)
      m_pLoadedModuleHandle = NULL;

   if (!fSilent)
      throw ErrorEx("Failed to open PKCS11 library: " + strFilePath);

   return(false);
}

bool Pkcs11::closeLibrary(const QString& strFilePath, bool fSilent)
{
   bool fRet(true);

   if (m_pLoadedModuleHandle)
   {
      m_p11->C_Finalize(NULL_PTR);

      if (::lt_dlclose(m_pLoadedModuleHandle) < 0)
      {
         fRet =false;

         if (!fSilent)
            throw ErrorEx("Failed to close PKCS11 library: " + strFilePath);
      }
   }

   m_p11 = NULL;
   m_pLoadedModuleHandle = NULL;

   return(fRet);
}

static const char* CKR2Str(unsigned long ulReturnValue)
{
#define PK11_ERR(x) case x : return #x;

   switch (ulReturnValue)
   {
         PK11_ERR(CKR_OK)
         PK11_ERR(CKR_CANCEL)
         PK11_ERR(CKR_HOST_MEMORY)
         PK11_ERR(CKR_SLOT_ID_INVALID)
         PK11_ERR(CKR_GENERAL_ERROR)
         PK11_ERR(CKR_FUNCTION_FAILED)
         PK11_ERR(CKR_ARGUMENTS_BAD)
         PK11_ERR(CKR_NO_EVENT)
         PK11_ERR(CKR_NEED_TO_CREATE_THREADS)
         PK11_ERR(CKR_CANT_LOCK)
         PK11_ERR(CKR_ATTRIBUTE_READ_ONLY)
         PK11_ERR(CKR_ATTRIBUTE_SENSITIVE)
         PK11_ERR(CKR_ATTRIBUTE_TYPE_INVALID)
         PK11_ERR(CKR_ATTRIBUTE_VALUE_INVALID)
         PK11_ERR(CKR_DATA_INVALID)
         PK11_ERR(CKR_DATA_LEN_RANGE)
         PK11_ERR(CKR_DEVICE_ERROR)
         PK11_ERR(CKR_DEVICE_MEMORY)
         PK11_ERR(CKR_DEVICE_REMOVED)
         PK11_ERR(CKR_ENCRYPTED_DATA_INVALID)
         PK11_ERR(CKR_ENCRYPTED_DATA_LEN_RANGE)
         PK11_ERR(CKR_FUNCTION_CANCELED)
         PK11_ERR(CKR_FUNCTION_NOT_PARALLEL)
         PK11_ERR(CKR_FUNCTION_NOT_SUPPORTED)
         PK11_ERR(CKR_KEY_HANDLE_INVALID)
         PK11_ERR(CKR_KEY_SIZE_RANGE)
         PK11_ERR(CKR_KEY_TYPE_INCONSISTENT)
         PK11_ERR(CKR_KEY_NOT_NEEDED)
         PK11_ERR(CKR_KEY_CHANGED)
         PK11_ERR(CKR_KEY_NEEDED)
         PK11_ERR(CKR_KEY_INDIGESTIBLE)
         PK11_ERR(CKR_KEY_FUNCTION_NOT_PERMITTED)
         PK11_ERR(CKR_KEY_NOT_WRAPPABLE)
         PK11_ERR(CKR_KEY_UNEXTRACTABLE)
         PK11_ERR(CKR_MECHANISM_INVALID)
         PK11_ERR(CKR_MECHANISM_PARAM_INVALID)
         PK11_ERR(CKR_OBJECT_HANDLE_INVALID)
         PK11_ERR(CKR_OPERATION_ACTIVE)
         PK11_ERR(CKR_OPERATION_NOT_INITIALIZED)
         PK11_ERR(CKR_PIN_INCORRECT)
         PK11_ERR(CKR_PIN_INVALID)
         PK11_ERR(CKR_PIN_LEN_RANGE)
         PK11_ERR(CKR_PIN_EXPIRED)
         PK11_ERR(CKR_PIN_LOCKED)
         PK11_ERR(CKR_SESSION_CLOSED)
         PK11_ERR(CKR_SESSION_COUNT)
         PK11_ERR(CKR_SESSION_HANDLE_INVALID)
         PK11_ERR(CKR_SESSION_PARALLEL_NOT_SUPPORTED)
         PK11_ERR(CKR_SESSION_READ_ONLY)
         PK11_ERR(CKR_SESSION_EXISTS)
         PK11_ERR(CKR_SESSION_READ_ONLY_EXISTS)
         PK11_ERR(CKR_SESSION_READ_WRITE_SO_EXISTS)
         PK11_ERR(CKR_SIGNATURE_INVALID)
         PK11_ERR(CKR_SIGNATURE_LEN_RANGE)
         PK11_ERR(CKR_TEMPLATE_INCOMPLETE)
         PK11_ERR(CKR_TEMPLATE_INCONSISTENT)
         PK11_ERR(CKR_TOKEN_NOT_PRESENT)
         PK11_ERR(CKR_TOKEN_NOT_RECOGNIZED)
         PK11_ERR(CKR_TOKEN_WRITE_PROTECTED)
         PK11_ERR(CKR_UNWRAPPING_KEY_HANDLE_INVALID)
         PK11_ERR(CKR_UNWRAPPING_KEY_SIZE_RANGE)
         PK11_ERR(CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT)
         PK11_ERR(CKR_USER_ALREADY_LOGGED_IN)
         PK11_ERR(CKR_USER_NOT_LOGGED_IN)
         PK11_ERR(CKR_USER_PIN_NOT_INITIALIZED)
         PK11_ERR(CKR_USER_TYPE_INVALID)
         PK11_ERR(CKR_USER_ANOTHER_ALREADY_LOGGED_IN)
         PK11_ERR(CKR_USER_TOO_MANY_TYPES)
         PK11_ERR(CKR_WRAPPED_KEY_INVALID)
         PK11_ERR(CKR_WRAPPED_KEY_LEN_RANGE)
         PK11_ERR(CKR_WRAPPING_KEY_HANDLE_INVALID)
         PK11_ERR(CKR_WRAPPING_KEY_SIZE_RANGE)
         PK11_ERR(CKR_WRAPPING_KEY_TYPE_INCONSISTENT)
         PK11_ERR(CKR_RANDOM_SEED_NOT_SUPPORTED)
         PK11_ERR(CKR_RANDOM_NO_RNG)
         PK11_ERR(CKR_DOMAIN_PARAMS_INVALID)
         PK11_ERR(CKR_BUFFER_TOO_SMALL)
         PK11_ERR(CKR_SAVED_STATE_INVALID)
         PK11_ERR(CKR_INFORMATION_SENSITIVE)
         PK11_ERR(CKR_STATE_UNSAVEABLE)
         PK11_ERR(CKR_CRYPTOKI_NOT_INITIALIZED)
         PK11_ERR(CKR_CRYPTOKI_ALREADY_INITIALIZED)
         PK11_ERR(CKR_MUTEX_BAD)
         PK11_ERR(CKR_MUTEX_NOT_LOCKED)
         PK11_ERR(CKR_VENDOR_DEFINED)
   }

   return ("unknown PKCS11 error");
}

void Pkcs11::pk11error(const QString& strfunc, int iReturnValue)
{
   ErrorEx err("PKCS#11 function " + strfunc + " failed: " + ::CKR2Str(iReturnValue) + "\n");
   throw err;
}
