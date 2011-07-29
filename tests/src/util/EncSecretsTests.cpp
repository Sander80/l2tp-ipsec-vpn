/*
 * $Id: EncSecretsTests.cpp 45 2011-02-12 00:25:26Z werner $
 *
 * File:   EncSecretsTests.cpp
 * Author: wejaeger
 *
 * Created on Jul 28, 2010, 1:05:52 PM
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

#include "util/EncSecrets.h"
#include "EncSecretsTests.h"

static unsigned char const KEY[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
static unsigned char const IV[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

CPPUNIT_TEST_SUITE_REGISTRATION(EncSecretsTests);

EncSecretsTests::EncSecretsTests()
{
}

EncSecretsTests::~EncSecretsTests()
{
}

void EncSecretsTests::setUp()
{
}

void EncSecretsTests::tearDown()
{
}

void EncSecretsTests::testEncryption()
{
   EncSecrets encSecrets(KEY, IV, "Text to encrypt");
   CPPUNIT_ASSERT(::strcmp(encSecrets.getbuf(), "kj87Mrf0GmkMZ3GYIrBkPQ==\\n"));
}

void EncSecretsTests::testDecryption()
{
   EncSecrets encSecrets("kj87Mrf0GmkMZ3GYIrBkPQ==\n");
   CPPUNIT_ASSERT(encSecrets.retrieve(KEY, IV) == "Text to encrypt");
}


