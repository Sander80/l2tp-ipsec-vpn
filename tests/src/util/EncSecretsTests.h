/*
 * $Id: EncSecretsTests.h 45 2011-02-12 00:25:26Z werner $
 *
 * File:   EncSecretsTests.h
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

#ifndef ENCSECRETSTESTS_H
#define	ENCSECRETSTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class EncSecretsTests : public CPPUNIT_NS::TestFixture
{
   CPPUNIT_TEST_SUITE(EncSecretsTests);

   CPPUNIT_TEST(testEncryption);
   CPPUNIT_TEST(testDecryption);

   CPPUNIT_TEST_SUITE_END();

public:
   EncSecretsTests();
   virtual ~EncSecretsTests();
   void setUp();
   void tearDown();

private:
   void testEncryption();
   void testDecryption();
};

#endif	/* ENCSECRETSTESTS_H */

