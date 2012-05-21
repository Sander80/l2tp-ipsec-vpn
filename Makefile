#
# $Id: Makefile 144 2012-05-21 07:31:37Z wejaeger $
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

QMAKE := $(shell if [ -f /usr/bin/qmake ]; then echo "qmake"; else echo "qmake-qt4"; fi)

# default configuration is release
DEFAULTCONF=Release

# Active Configuration
CONF ?= ${DEFAULTCONF}

# All Configurations
ALLCONFS=Debug Release

# various directories
BUILDDIR = build/${CONF}
GENDIR = src/generated
DOCDIR = docs/api
DISTDIR = dist/${CONF}
TESTDIR = build/TestFiles

QMAKE_TARGET = L2tpIPsecVpn

# build
build: nbproject/qt-${CONF}.mk
	make -f nbproject/qt-${CONF}.mk ${DISTDIR}/$(QMAKE_TARGET)

# install
install: nbproject/qt-${CONF}.mk
	make -f nbproject/qt-${CONF}.mk QMAKE_TARGE=$(QMAKE_TARGET) install

	@if [ "$${INSTALL_ROOT}" = "" ]; then \
	   $(QMAKE_TARGET) applySettings || true; \
	   service rsyslog restart; \
	fi

# uninstall
uninstall: nbproject/qt-${CONF}.mk
   # if applet is running try to terminate it
	@PIDS=$$(pidof ${QMAKE_TARGET} || true); \
	if [ -n "$${PIDS}" ]; then \
		echo "Trying to terminate ${QMAKE_TARGET} applet" >&2; \
		kill $${PIDS} || true; \
	fi

   # Remove all generated configuration files
	@echo "Trying to delete all generated config files" >&2
	$(QMAKE_TARGET) deleteAllConfFiles || true

   # Remove lock files and sockets
	rm -f $(INSTALL_ROOT)/tmp/$(QMAKE_TARGET)-*

	# Remove syslog pipe and restart syslog service
	rm -f $(INSTALL_ROOT)/var/log/l2tpipsecvpn.pipe
	service rsyslog restart

	make -f nbproject/qt-${CONF}.mk QMAKE_TARGE=$(QMAKE_TARGET) uninstall

lupdate:
	mv nbproject/qt-${DEFAULTCONF}.pro .
	lupdate qt-${DEFAULTCONF}.pro
	mv qt-${DEFAULTCONF}.pro nbproject

lrelease:
	mv nbproject/qt-${DEFAULTCONF}.pro .
	lrelease -compress -nounfinished -removeidentical qt-${DEFAULTCONF}.pro
	mv qt-${DEFAULTCONF}.pro nbproject

ts2pot:
	lconvert -if ts -of pot -o nls/nls.pot nls/L2tpIPsecVpn_de.ts

ts2po:
	lconvert -if ts -of po -o nls/de.po nls/L2tpIPsecVpn_de.ts

po2ts:
	lconvert -if po -of ts -o nls/L2tpIPsecVpn_de.ts nls/de.po

# clean
clean:
	rm -rf ${BUILDDIR}/*
	rm -rf ${GENDIR}/*
	rm -rf ${DOCDIR}
	rm -rf ${DISTDIR}/*
	rm -rf ${TESTDIR}/*
	rm -f nbproject/*.mk
	rm -f nbproject/*.bash
	rm -f *.mk

# clobber
clobber:
	@for CONF in ${ALLCONFS}; \
	do \
	    make CONF=$${CONF} clean; \
	done

# run tests
test: build build-tests
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/LibtoolTests || true; \
	    ${TESTDIR}/Pkcs12Tests || true; \
	    ${TESTDIR}/EncSecretsTests || true; \
	else  \
	    ./${TEST} || true; \
	fi

srccheck:
	cppcheck -q -I src -I ${GENDIR} --enable=all src

# help
help:
	@echo "This makefile supports the following configurations:"
	@echo "    ${ALLCONFS} (default = ${DEFAULTCONF})"
	@echo ""
	@echo "and the following targets:"
	@echo "    build  (default target)"
	@echo "    clean"
	@echo "    clobber"
	@echo "    srccheck"
	@echo "    install"
	@echo "    uninstall"
	@echo "    lupdate"
	@echo "    lrelease"
	@echo "    ts2pot"
	@echo "    ts2po"
	@echo "    po2ts"
	@echo "    test"
	@echo "    help"
	@echo ""
	@echo "Makefile Usage:"
	@echo "    make [CONF=<CONFIGURATION>] build"
	@echo "    make [CONF=<CONFIGURATION>] clean"
	@echo "    make clobber"
	@echo "    make [CONF=<CONFIGURATION>] [INSTALL_ROOT=<Base directory to install in>] install"
	@echo "    make [INSTALL_ROOT=<Base directory to uninstall from>] uninstall"
	@echo "    make lupdate"
	@echo "    make lrelease"
	@echo "    make ts2pot"
	@echo "    make ts2po"
	@echo "    make po2ts"
	@echo "    make test"
	@echo "    make help"
	@echo ""
	@echo "Target 'build' will build a specific configuration."
	@echo "Target 'clean' will remove all built files from a specific configuration."
	@echo "Target 'clobber' will remove all built files from all configurations"
	@echo "Target 'srccheck' performs a static source code check using cppcheck"
	@echo "Target 'install' will install a specific configuration of the program"
	@echo "       in [INSTALL_ROOT]/usr/bin/"
	@echo "Target 'uninstall' will uninstall the program from [INSTALL_ROOT]/usr/bin/"
	@echo "Target 'lupdate' reads the project file, finds the translatable strings in the specified source, header and interface files, and updates the translation files (.ts files) specified in it."
	@echo "Target 'lrelease' reads the project file and converts the translation files (.ts files) specified in it into Qt message files (.qm files) used by the application to translate."
	@echo "Target 'ts2pot' converts a translation file (.ts file) to a GNU Portable Object Template File (.pot file)."
	@echo "Target 'ts2po'  converts all translation files (.ts files) to GNU Portable Object Files (.po files)."
	@echo "Target 'po2ts' converts all GNU Portable Object Files (.po files) to translation files (.ts files)."
	@echo "Target 'test' will run the test suite."
	@echo "Target 'help' prints this message"
	@echo ""

build-tests: nbproject/qt-EncSecretsTests.mk nbproject/qt-LibtoolTests.mk nbproject/qt-Pkcs12Tests.mk
	make -f nbproject/qt-EncSecretsTests.mk ${TESTDIR}/EncSecretsTests
	make -f nbproject/qt-LibtoolTests.mk ${TESTDIR}/LibtoolTests
	make -f nbproject/qt-Pkcs12Tests.mk ${TESTDIR}/Pkcs12Tests

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
	${QMAKE} -o qttmp-${CONF}.mk -after "OBJECTS_DIR=${BUILDDIR}" "DESTDIR=${DISTDIR}" nbproject/qt-${CONF}.pro
	mv -f qttmp-${CONF}.mk nbproject/qt-${CONF}.mk

