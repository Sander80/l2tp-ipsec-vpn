/*
 * $Id: LibtoolTests.cpp 105 2011-08-16 00:56:38Z werner $
 *
 * File:   LibtoolTests.cpp
 * Author: wejaeger
 *
 * Created on Feb 8, 2011, 1:06:28 PM
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

#include <QString>

#include "util/Libtool.h"
#include "LibtoolTests.h"

const char* const VALIDOPENSSLENGINELIB("/usr/lib/engines/engine_pkcs11.so");
const char* const INVALIDOPENSSLENGINELIB("/usr/lib/libc.so");
const QString VALIDOPENSSLENGINELIBSYMBOL("ENGINE_init");

CPPUNIT_TEST_SUITE_REGISTRATION(LibtoolTests);

LibtoolTests::LibtoolTests()
{
}

LibtoolTests::~LibtoolTests()
{
}

void LibtoolTests::setUp()
{
   m_pOpenSSLLibrary = new Libtool(VALIDOPENSSLENGINELIB);
   m_pNonOpenSSLLibrary = new Libtool(INVALIDOPENSSLENGINELIB);
}

void LibtoolTests::tearDown()
{
   delete m_pOpenSSLLibrary;
   delete m_pNonOpenSSLLibrary;
}

void LibtoolTests::testValidOpenSSLLibrary()
{
   CPPUNIT_ASSERT(m_pOpenSSLLibrary->hasSymbol(VALIDOPENSSLENGINELIBSYMBOL));
}

void LibtoolTests::testInvalidOpenSSLLibrary()
{
   CPPUNIT_ASSERT(!m_pNonOpenSSLLibrary->hasSymbol(VALIDOPENSSLENGINELIBSYMBOL));
}

