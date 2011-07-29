/*
 * $Id: LibtoolTests.h 45 2011-02-12 00:25:26Z werner $
 *
 * File:   LibtoolTests.h
 * Author: wejaeger
 *
 * Created on Feb 8, 2011, 1:06:29 PM
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

#ifndef LIBTOOLTESTS_H
#define	LIBTOOLTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class Libtool;

class LibtoolTests : public CPPUNIT_NS::TestFixture
{
   CPPUNIT_TEST_SUITE(LibtoolTests);

   CPPUNIT_TEST(testValidOpenSSLLibrary);
   CPPUNIT_TEST(testInvalidOpenSSLLibrary);

   CPPUNIT_TEST_SUITE_END();

public:
   LibtoolTests();
   virtual ~LibtoolTests();
   void setUp();
   void tearDown();

private:
   void testValidOpenSSLLibrary();
   void testInvalidOpenSSLLibrary();

   const Libtool* m_pOpenSSLLibrary;
   const Libtool* m_pNonOpenSSLLibrary;
};

#endif	/* LIBTOOLTESTS_H */

