#
# $Id: Makefile 104 2011-08-05 07:50:33Z werner $
#
# File:   Makefile
# Author: Werner Jaeger
#
# Created on August 4, 2011, 3:17 PM
#
# Copyright 2011 Werner Jaeger.
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

QMAKE = qmake-qt4

# default configuration is release
CONF ?= Release

# various directories
BUILDDIR = build/${CONF}
GENDIR = src/generated
DISTDIR = dist/${CONF}
TESTDIR = build/TestFiles

# build
build: nbproject/qt-${CONF}.mk
	make -f nbproject/qt-${CONF}.mk dist/${CONF}/L2tpIPsecVpn

# install
install: nbproject/qt-${CONF}.mk
	make -f nbproject/qt-${CONF}.mk install

# clean
clean:
	rm -rf ${BUILDDIR}/*
	rm -rf ${GENDIR}/*
	rm -rf ${DISTDIR}/*
	rm -rf ${TESTDIR}/*
	rm -f nbproject/qt-EncSecretsTests.mk
	rm -f nbproject/qt-LibtoolTests.mk
	rm -f nbproject/qt-Pkcs12Tests.mk
	rm -f nbproject/qt-${CONF}.mk

# run tests
test: build build-tests
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/f2 || true; \
	    ${TESTDIR}/f3 || true; \
	    ${TESTDIR}/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# help
help:
	@echo "This makefile supports the following configurations:"
	@echo "    Release, Debug"
	@echo ""
	@echo "and the following targets:"
	@echo "    build  (default target)"
	@echo "    clean"
	@echo "    install"
	@echo "    test"
	@echo "    help"
	@echo ""
	@echo "Makefile Usage:"
	@echo "    make [CONF=<CONFIGURATION>] build"
	@echo "    make [CONF=<CONFIGURATION>] clean"
	@echo "    make [CONF=<CONFIGURATION>] [INSTALL_ROOT=<Base directory to intall in>] install"
	@echo "    make test"
	@echo "    make help"
	@echo ""
	@echo "Target 'build' will build a specific configuration."
	@echo "Target 'clean' will clean a specific configuration."
	@echo "Target 'install' will install a specific configuration of the program."
	@echo "    in [INSTALL_ROOT]/usr/lib/l2tp-ipsec-vpn-daemon/"
	@echo "Target 'test' will run the test suite."
	@echo "Target 'help' prints this message."
	@echo ""

build-tests: nbproject/qt-EncSecretsTests.mk nbproject/qt-LibtoolTests.mk nbproject/qt-Pkcs12Tests.mk
	make -f nbproject/qt-EncSecretsTests.mk ${TESTDIR}/f1
	make -f nbproject/qt-LibtoolTests.mk ${TESTDIR}/f2
	make -f nbproject/qt-Pkcs12Tests.mk ${TESTDIR}/f3

nbproject/qt-EncSecretsTests.mk: tests/EncSecretsTests.pro
	${QMAKE} -o qttmp-EncSecretsTests.mk "BUILDDIR=${BUILDDIR}" "OBJECTS_DIR=${TESTDIR}" "DESTDIR=${TESTDIR}" tests/EncSecretsTests.pro
	mv -f qttmp-EncSecretsTests.mk nbproject/qt-EncSecretsTests.mk

nbproject/qt-LibtoolTests.mk: tests/EncSecretsTests.pro
	${QMAKE} -o qttmp-LibtoolTests.mk "BUILDDIR=${BUILDDIR}" "OBJECTS_DIR=${TESTDIR}" "DESTDIR=${TESTDIR}" tests/LibtoolTests.pro
	mv -f qttmp-LibtoolTests.mk nbproject/qt-LibtoolTests.mk

nbproject/qt-Pkcs12Tests.mk: tests/Pkcs12Tests.pro
	${QMAKE} -o qttmp-Pkcs12Tests.mk "BUILDDIR=${BUILDDIR}" "OBJECTS_DIR=${TESTDIR}" "DESTDIR=${TESTDIR}" tests/Pkcs12Tests.pro
	mv -f qttmp-Pkcs12Tests.mk nbproject/qt-Pkcs12Tests.mk

nbproject/qt-${CONF}.mk: nbproject/qt-${CONF}.pro
	${QMAKE} -o qttmp-${CONF}.mk -after "OBJECTS_DIR=${BUILDDIR}" nbproject/qt-${CONF}.pro
	mv -f qttmp-${CONF}.mk nbproject/qt-${CONF}.mk

