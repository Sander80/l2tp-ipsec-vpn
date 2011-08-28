/*
 * $Id: TestRunner.cpp 105 2011-08-16 00:56:38Z werner $
 *
 * File:   TestRunner.cpp
 * Author: wejaeger
 *
 * Created on Feb 10, 2011, 3:47:52 aM
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

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

int main()
{
   // Create the event manager and test controller
   CPPUNIT_NS::TestResult controller;

   // Add a listener that collects test result
   CPPUNIT_NS::TestResultCollector result;
   controller.addListener(&result);

   // Add a listener that print dots as test run.
   CPPUNIT_NS::BriefTestProgressListener progress;
   controller.addListener(&progress);

   // Add the top suite to the test runner
   CPPUNIT_NS::TestRunner runner;
   runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
   runner.run(controller);

   // Print test in a compiler compatible format.
   CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
   outputter.write();

   return(result.wasSuccessful() ? 0 : 1);
}
