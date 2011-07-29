/*
 * $Id: Pkcs11Attribute.h 97 2011-08-01 07:29:28Z werner $
 *
 * File:   Pkcs11Attribute.h
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

#ifndef PKCS11ATTRIBUTE_H
#define	PKCS11ATTRIBUTE_H

#include <QString>
#include <stdlib.h>
#include <openssl/bn.h>

#include "pkcs11.h"

class Pkcs11Attlist;

class Pkcs11Attribute
{
public:
   explicit Pkcs11Attribute(unsigned long ulType);
   virtual ~Pkcs11Attribute();

	const CK_ATTRIBUTE* getAttribute() const { return(&m_Attr);	}
	virtual void store(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle);
	virtual void load(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle);

protected:
	CK_ATTRIBUTE m_Attr;

private:
   Pkcs11Attribute(const Pkcs11Attribute& orig);
   Pkcs11Attribute& operator=(const Pkcs11Attribute& orig);

	friend class Pkcs11Attlist;
};

class Pkcs11AttrBool: public Pkcs11Attribute
{
public:
	Pkcs11AttrBool(unsigned long ulType, bool fValue = false) : Pkcs11Attribute(ulType)
	{
		m_Attr.pValue = &m_cValue;
		m_Attr.ulValueLen = sizeof(m_cValue);
		setValue(fValue);
	}

	bool getValue() const { return(m_cValue ? true : false);	}

	void setValue(unsigned long ulValue) {	m_cValue = ulValue ? 1 : 0; }

protected:
	unsigned char m_cValue;

private:
   Pkcs11AttrBool(const Pkcs11AttrBool& orig);
   Pkcs11AttrBool& operator=(const Pkcs11AttrBool& orig);
};

class Pkcs11AttrUlong: public Pkcs11Attribute
{
public:
	Pkcs11AttrUlong(unsigned long ulType, unsigned long ulValue = 0) : Pkcs11Attribute(ulType)
	{
		m_Attr.pValue = &m_ulValue;
		m_Attr.ulValueLen = sizeof(m_ulValue);
		setValue(ulValue);
	}

	unsigned long getValue() const { return(m_ulValue); }

	void setValue(unsigned long ulValue) {	m_ulValue = ulValue;	}

protected:
	unsigned long m_ulValue;

private:
   Pkcs11AttrUlong(const Pkcs11AttrBool& orig);
   Pkcs11AttrUlong& operator=(const Pkcs11AttrBool& orig);
};



class Pkcs11AttrData: public Pkcs11Attribute
{

public:
	Pkcs11AttrData(unsigned long ulType, const unsigned char* pcValue = NULL,	unsigned long ulLen = 0) : Pkcs11Attribute(ulType)
	{
		setValue(pcValue, ulLen);
	}

	Pkcs11AttrData(unsigned long ulType, QByteArray ba) : Pkcs11Attribute(ulType)
	{
		setValue(reinterpret_cast<const unsigned char*>(ba.constData()), ba.size());
	}

	virtual ~Pkcs11AttrData()
	{
		if (m_Attr.pValue)
			::free(m_Attr.pValue);
	}

	unsigned long getValue(const unsigned char** ppChar) const
	{
		*ppChar = static_cast<unsigned char*>(m_Attr.pValue);
		return(m_Attr.ulValueLen);
	}

	QString getText() const	{ return(::utf82QString(m_Attr.pValue, m_Attr.ulValueLen)); }

	BIGNUM* getBignum() const { return(::BN_bin2bn(static_cast<unsigned char*>(m_Attr.pValue), m_Attr.ulValueLen, NULL)); }

	void load(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle);
	void setValue(const unsigned char *pc, unsigned long ulLen);

private:
   Pkcs11AttrData(const Pkcs11AttrData& orig);
   Pkcs11AttrData& operator=(const Pkcs11AttrData& orig);
};

class Pkcs11Attlist
{
public:
   Pkcs11Attlist() { init(); }
   explicit Pkcs11Attlist(const Pkcs11Attlist& attrList);
   explicit Pkcs11Attlist(const Pkcs11Attribute& attr)
   {
      init();
      addAttribute(attr);
   }

   ~Pkcs11Attlist();

   unsigned long get(CK_ATTRIBUTE** ppAttributes) const
   {
      *ppAttributes = m_pAttributes;
      return(m_ulAttrLen);
   }

   void addAttribute(const Pkcs11Attribute& attribute);
   void reset();

   Pkcs11Attlist &operator << (const Pkcs11Attribute& attribute)
   {
      addAttribute(attribute);
      return(*this);
   }

private:
   Pkcs11Attlist(const Pkcs11AttrData& orig);
   Pkcs11Attlist& operator=(const Pkcs11AttrData& orig);

   void init()
   {
      m_ulAttrLen = 0;
      m_ulAllocLen = 0;
      m_pAttributes = NULL;
   }

   CK_ATTRIBUTE* m_pAttributes;
   unsigned long m_ulAttrLen;
   unsigned long m_ulAllocLen;
};

#endif	/* PKCS11ATTRIBUTE_H */

