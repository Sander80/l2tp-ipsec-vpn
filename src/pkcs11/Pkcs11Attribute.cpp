/*
 * $Id: Pkcs11Attribute.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   Pkcs11Attribute.cpp
 * Author: Werner Jaeger
 *
 * Created on July 31, 2010, 12:20 PM
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

#include "util/ErrorEx.h"
#include "Pkcs11.h"
#include "Pkcs11Attribute.h"

Pkcs11Attribute::Pkcs11Attribute(unsigned long ulType)
{
   ::memset(&m_Attr, 0, sizeof(m_Attr));
   m_Attr.type = ulType;
}

Pkcs11Attribute::~Pkcs11Attribute()
{
}

void Pkcs11Attribute::load(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle)
{
	const CK_RV rv = Pkcs11::m_p11->C_GetAttributeValue(ulSessionHandle, ulObjectHandle, &m_Attr, 1);
	if (rv != CKR_OK)
		Pkcs11::pk11error("C_GetAttribute()", rv);
}

void Pkcs11Attribute::store(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle)
{
	const CK_RV rv = Pkcs11::m_p11->C_SetAttributeValue(ulSessionHandle, ulObjectHandle, &m_Attr, 1);
	if (rv != CKR_OK)
		Pkcs11::pk11error("C_SetAttributeValue", rv);
}

void Pkcs11AttrData::load(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle)
{
	if (m_Attr.pValue)
   {
		::free(m_Attr.pValue);
		m_Attr.pValue = NULL;
	}

	m_Attr.ulValueLen = 0;

	CK_RV rv = Pkcs11::m_p11->C_GetAttributeValue(ulSessionHandle, ulObjectHandle, &m_Attr, 1);

	if (rv == CKR_OK)
   {
		m_Attr.pValue = ::malloc(m_Attr.ulValueLen +1);
		ErrorEx::checkOutOfMemory(m_Attr.pValue);
		rv = Pkcs11::m_p11->C_GetAttributeValue(ulSessionHandle, ulObjectHandle, &m_Attr, 1);
		if (rv != CKR_OK)
			Pkcs11::pk11error("C_GetAttributeValue(data)", rv);
	}
   else
      Pkcs11::pk11error("C_GetAttributeValue(data)", rv);
}

void Pkcs11AttrData::setValue(const unsigned char *pc, unsigned long ulLen)
{
	if (m_Attr.pValue)
		::free(m_Attr.pValue);

	m_Attr.pValue = ::malloc(ulLen);
	ErrorEx::checkOutOfMemory(m_Attr.pValue);
	::memcpy(m_Attr.pValue, pc, ulLen);
	m_Attr.ulValueLen = ulLen;
}

Pkcs11Attlist::Pkcs11Attlist(const Pkcs11Attlist &attrList)
{
	m_ulAttrLen = attrList.m_ulAttrLen;
	m_ulAllocLen = attrList.m_ulAllocLen;

	if (m_ulAllocLen)
   {
		m_pAttributes = reinterpret_cast<CK_ATTRIBUTE*>(::malloc(m_ulAllocLen * sizeof(*m_pAttributes)));
		ErrorEx::checkOutOfMemory(m_pAttributes);
		::memcpy(m_pAttributes, attrList.m_pAttributes, m_ulAttrLen * sizeof(*m_pAttributes));
	}

	for (unsigned long ul = 0; ul < m_ulAttrLen; ul++)
   {
		void* p = ::malloc(m_pAttributes[ul].ulValueLen);
		ErrorEx::checkOutOfMemory(p);
		::memcpy(p, m_pAttributes[ul].pValue, m_pAttributes[ul].ulValueLen);
	}
}

Pkcs11Attlist::~Pkcs11Attlist()
{
	for (unsigned long ul = 0; ul < m_ulAttrLen; ul++)
		::free(m_pAttributes[ul].pValue);

	if (m_pAttributes)
		::free(m_pAttributes);
}

void Pkcs11Attlist::addAttribute(const Pkcs11Attribute& attribute)
{
	if (m_ulAttrLen == m_ulAllocLen)
   {
		m_ulAllocLen = m_ulAllocLen ? m_ulAllocLen * 2 : 16;
		m_pAttributes = reinterpret_cast<CK_ATTRIBUTE*>(::realloc(m_pAttributes, m_ulAllocLen * sizeof(*m_pAttributes)));
		ErrorEx::checkOutOfMemory(m_pAttributes);
	}

	CK_ATTRIBUTE* const pAttr = m_pAttributes + m_ulAttrLen++;
	pAttr->type = attribute.m_Attr.type;
	pAttr->ulValueLen = attribute.m_Attr.ulValueLen;
	pAttr->pValue = ::malloc(pAttr->ulValueLen);
	::memcpy(pAttr->pValue, attribute.m_Attr.pValue, pAttr->ulValueLen);
}

void Pkcs11Attlist::reset()
{
	for (unsigned long ul = 0; ul < m_ulAttrLen; ul++)
		::free(m_pAttributes[ul].pValue);

	m_ulAttrLen = 0;
}




