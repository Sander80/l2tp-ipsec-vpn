/*
 * $Id: Pkcs12Tests.h 69 2011-04-12 04:33:22Z werner $
 *
 * File:   Pkcs12Tests.h
 * Author: wejaeger
 *
 * Created on Apr 8, 2011, 7:41:52 PM
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

#ifndef PKCS12TESTS_H
#define	PKCS12TESTS_H

#include <QString>

#include <cppunit/extensions/HelperMacros.h>

class Pkcs12;
class QTemporaryFile;

class Pkcs12Tests : public CPPUNIT_NS::TestFixture
{
   CPPUNIT_TEST_SUITE(Pkcs12Tests);

   CPPUNIT_TEST(testParseValidPkcs11GoodPassphrase);
   CPPUNIT_TEST(testParseValidPkcs11WrongPassphrase);
   CPPUNIT_TEST(testParseInvalidPkcs11);
   CPPUNIT_TEST(testParseNonExistingPkcs11);
   CPPUNIT_TEST(testCert2Pem);
   CPPUNIT_TEST(testCaChain2Pem);
   CPPUNIT_TEST(testPrivateKey2Pem);

   CPPUNIT_TEST_SUITE_END();

public:
   Pkcs12Tests();
   virtual ~Pkcs12Tests();
   void setUp();
   void tearDown();

private:
   void testParseValidPkcs11GoodPassphrase();
   void testParseValidPkcs11WrongPassphrase();
   void testParseInvalidPkcs11();
   void testParseNonExistingPkcs11();
   void testCert2Pem();
   void testCaChain2Pem();
   void testPrivateKey2Pem();

   QTemporaryFile* m_pTmpFile;
   QString m_strTmpFileName;
   Pkcs12* m_pValidPkcs12GoodPassphrase;
   const Pkcs12* m_pValidPkcs12WrongPassphrase;
   const Pkcs12* m_pInvalidPkcs12;
   const Pkcs12* m_pNonExistingPkcs12;
};

#endif	/* NEWTESTCLASS_H */

