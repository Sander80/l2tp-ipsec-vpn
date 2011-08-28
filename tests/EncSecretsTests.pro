# $Id$
#
# File:   EncSecretsTests.pro
# Author: Werner Jaeger
#
# Created on Feb 10, 2011, 4:45 AM
#
# Copyright 2010 Werner Jaeger.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Build Unit Tests for EncSecrets class
#
TARGET = EncSecretsTests
CONFIG += debug
QT = core
INCLUDEPATH=../src
SOURCES += tests/src/TestRunner.cpp tests/src/util/EncSecretsTests.cpp
OBJECTS += $$BUILDDIR/EncSecrets.o
LIBS += -lcppunit -lcrypto
