/*
 * $Id: Pkcs12Tests.cpp 105 2011-08-16 00:56:38Z werner $
 *
 * File:   Pkcs12Tests.cpp
 * Author: wejaeger
 *
 * Created on Apr 8, 2011, 7:41:51 PM
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

#include <QTemporaryFile>
#include <QSslCertificate>
#include <QSslKey>

#include "util/Pkcs12.h"
#include "Pkcs12Tests.h"

static const char* const VALIDPKCS12FILE("tests/data/test.p12");
static const char* const INVALIDPKCS12FILE("tests/data/invalid.p12");
static const char* const NONEXISTINGPKCS12FILE("tests/data/test2.p12");
static const char* const GOODPASSPHRASE("test");
static const char* const WRONGPASSPHRASE("invalid");

CPPUNIT_TEST_SUITE_REGISTRATION(Pkcs12Tests);

Pkcs12Tests::Pkcs12Tests()
{
}

Pkcs12Tests::~Pkcs12Tests()
{
}

void Pkcs12Tests::setUp()
{
   m_pTmpFile = new QTemporaryFile();
   if (m_pTmpFile->open())
   {
      m_strTmpFileName = m_pTmpFile->fileName();
      m_pTmpFile->close();
   }

   m_pValidPkcs12GoodPassphrase = new Pkcs12(VALIDPKCS12FILE, GOODPASSPHRASE);
   m_pValidPkcs12WrongPassphrase = new Pkcs12(VALIDPKCS12FILE, WRONGPASSPHRASE);
   m_pInvalidPkcs12 = new Pkcs12(INVALIDPKCS12FILE, GOODPASSPHRASE);
   m_pNonExistingPkcs12 = new Pkcs12(NONEXISTINGPKCS12FILE, GOODPASSPHRASE);
}

void Pkcs12Tests::tearDown()
{
   delete m_pTmpFile;
   delete m_pValidPkcs12GoodPassphrase;
   delete m_pValidPkcs12WrongPassphrase;
   delete m_pInvalidPkcs12;
   delete m_pNonExistingPkcs12;
}

void Pkcs12Tests::testParseValidPkcs11GoodPassphrase()
{
   CPPUNIT_ASSERT_MESSAGE(m_pValidPkcs12GoodPassphrase->error().toStdString(), m_pValidPkcs12GoodPassphrase->error().isNull());
   CPPUNIT_ASSERT_EQUAL(std::string("Test"), m_pValidPkcs12GoodPassphrase->cn().toStdString());
   CPPUNIT_ASSERT_EQUAL(std::string("Test CA"), m_pValidPkcs12GoodPassphrase->issuer().toStdString());
   CPPUNIT_ASSERT_EQUAL(std::string("cc:00:6f:2d:f5:fe:7d:dd"), m_pValidPkcs12GoodPassphrase->serialNumber().toStdString());
}

void Pkcs12Tests::testParseValidPkcs11WrongPassphrase()
{
   CPPUNIT_ASSERT_EQUAL(std::string("Wrong passphrase"), m_pValidPkcs12WrongPassphrase->error().toStdString());
}

void Pkcs12Tests::testParseInvalidPkcs11()
{
   CPPUNIT_ASSERT_EQUAL(std::string("The file tests/data/invalid.p12 is not a valid PKCS#12 certificate bundle"), m_pInvalidPkcs12->error().toStdString());
}

void Pkcs12Tests::testParseNonExistingPkcs11()
{
   CPPUNIT_ASSERT_EQUAL(QString(NONEXISTINGPKCS12FILE).toStdString() + std::string(": No such file or directory"), m_pNonExistingPkcs12->error().toStdString());
}

void Pkcs12Tests::testCert2Pem()
{
   const bool fSuccess(m_pValidPkcs12GoodPassphrase->cert2Pem(m_strTmpFileName));
   CPPUNIT_ASSERT_MESSAGE(m_pValidPkcs12GoodPassphrase->error().toStdString(), fSuccess);

   if (fSuccess)
   {
      m_pTmpFile->open();
      const QSslCertificate cert(m_pTmpFile);
      m_pTmpFile->close();

      CPPUNIT_ASSERT(!cert.isNull());
      CPPUNIT_ASSERT_MESSAGE(cert.serialNumber().constData(), cert.serialNumber() == "cc:00:6f:2d:f5:fe:7d:dd");
   }
}

void Pkcs12Tests::testCaChain2Pem()
{
   CPPUNIT_ASSERT(m_pValidPkcs12GoodPassphrase->caCerts() == 2);
   const int iWritten(m_pValidPkcs12GoodPassphrase->caChain2Pem(m_strTmpFileName));
   CPPUNIT_ASSERT_MESSAGE(m_pValidPkcs12GoodPassphrase->error().toStdString(), iWritten == m_pValidPkcs12GoodPassphrase->caCerts());
}

void Pkcs12Tests::testPrivateKey2Pem()
{
   const bool fSuccess(m_pValidPkcs12GoodPassphrase->privateKey2Pem(m_strTmpFileName, GOODPASSPHRASE));
   CPPUNIT_ASSERT_MESSAGE(m_pValidPkcs12GoodPassphrase->error().toStdString(), fSuccess);

   if (fSuccess)
   {
      m_pTmpFile->open();
      const QSslKey key(m_pTmpFile, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, QByteArray(GOODPASSPHRASE));
      m_pTmpFile->close();

      CPPUNIT_ASSERT(!key.isNull());
      CPPUNIT_ASSERT(key.length() == 1024);
   }
}

