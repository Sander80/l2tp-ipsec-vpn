#
# $Id: Makefile 50 2012-05-21 07:32:02Z wejaeger $
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

# default configuration is release
DEFAULTCONF=Release

# Active Configuration
CONF ?= ${DEFAULTCONF}

# All Configurations
ALLCONFS=Debug Release

# various directories
BUILDDIR = build/${CONF}
GENDIR = src/generated
DISTDIR = dist/${CONF}

# Distribution specific configurations
QMAKE      := $(firstword $(wildcard /usr/bin/qmake /usr/bin/qmake-qt4))
CHKCONFIG  := $(wildcard /sbin/chkconfig)
UPDATE_RCD := $(wildcard /usr/sbin/update-rc.d)

ifneq (,$(CHKCONFIG))
   ADD_INITD := $(CHKCONFIG) --add l2tp-ipsec-vpn-daemon
   REMOVE_INITD := $(CHKCONFIG) --del l2tp-ipsec-vpn-daemon
else
	ifndef (,$(UPDATE_RCD))
      ADD_INITD := $(UPDATE_RCD) l2tp-ipsec-vpn-daemon defaults
      REMOVE_INITD := $(UPDATE_RCD) -f l2tp-ipsec-vpn-daemon remove
   endif
endif

INITRD_DIR  := $(firstword $(wildcard /etc/rc.d/init.d /etc/init.d))
ISDEBIAN    := $(wildcard /etc/debian_version)
ifneq (,$(ISDEBIAN))
   DEFAULT_DIR := $(wildcard /etc/default)
endif

.PHONY: build

# build
build: 
	rm -f qttmp-${CONF}.mk
	${QMAKE} -o qttmp-${CONF}.mk -after "OBJECTS_DIR=${BUILDDIR}" "DESTDIR=${DISTDIR}" nbproject/qt-${CONF}.pro
	mv -f qttmp-${CONF}.mk nbproject/qt-${CONF}.mk
	make -f nbproject/qt-${CONF}.mk ${DISTDIR}/L2tpIPsecVpnControlDaemon

# install
install: nbproject/qt-${CONF}.mk
	make -f nbproject/qt-${CONF}.mk install
	mkdir -p $(INSTALL_ROOT)$(INITRD_DIR)
	cp etc/l2tp-ipsec-vpn-daemon.init $(INSTALL_ROOT)$(INITRD_DIR)/l2tp-ipsec-vpn-daemon
	chmod +x $(INSTALL_ROOT)$(INITRD_DIR)/l2tp-ipsec-vpn-daemon
ifneq (,$(DEFAULT_DIR))
	mkdir -p $(INSTALL_ROOT)$(DEFAULT_DIR)
	cp etc/l2tp-ipsec-vpn-daemon.default $(INSTALL_ROOT)$(DEFAULT_DIR)/l2tp-ipsec-vpn-daemon
endif

ifneq (,$(ADD_INITD))
ifeq ($(strip $(INSTALL_ROOT)),)
		$(ADD_INITD) >/dev/null
		service l2tp-ipsec-vpn-daemon start
endif
endif

# uninstall
uninstall: nbproject/qt-${CONF}.mk
	@if [ -x "$(INITRD_DIR)/l2tp-ipsec-vpn-daemon" ]; then \
		service l2tp-ipsec-vpn-daemon stop; \
		$(REMOVE_INITD) >/dev/null; \
		rm -f $(INITRD_DIR)/l2tp-ipsec-vpn-daemon; \
	fi
ifneq (,$(DEFAULT_DIR))
	rm -f $(DEFAULT_DIR)/l2tp-ipsec-vpn-daemon
endif
	rm -rf $(INSTALL_ROOT)/var/run/L2tpIPsecVpnControlDaemon
	make -f nbproject/qt-${CONF}.mk uninstall

# clean
clean:
	rm -rf ${BUILDDIR}/*
	rm -rf ${GENDIR}/*
	rm -rf ${DISTDIR}/*
	rm -f nbproject/*.mk
	rm -f nbproject/*.bash
	rm -f *.mk

# clobber
clobber:
	@for CONF in ${ALLCONFS}; \
	do \
	    make CONF=$${CONF} clean; \
	done

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
	@echo "    help"
	@echo ""
	@echo "Makefile Usage:"
	@echo "    make [CONF=<CONFIGURATION>] build"
	@echo "    make [CONF=<CONFIGURATION>] clean"
	@echo "    make clobber"
	@echo "    make [CONF=<CONFIGURATION>] [INSTALL_ROOT=<Base directory to install in>] install"
	@echo "    make [INSTALL_ROOT=<Base directory to uninstall from>] uninstall"
	@echo "    make help"
	@echo ""
	@echo "Target 'build' will build a specific configuration."
	@echo "Target 'clean' will remove all built files from a specific configuration."
	@echo "Target 'clobber' will remove all built files from all configurations"
	@echo "Target 'srccheck' performs a static source code check using cppcheck"
	@echo "Target 'install' will install a specific configuration of the program"
	@echo "       in [INSTALL_ROOT]/usr/lib/l2tp-ipsec-vpn-daemon/"
	@echo "Target 'uninstall' will uninstall the program from [INSTALL_ROOT]/usr/lib/l2tp-ipsec-vpn-daemon/"
	@echo "Target 'help' prints this message"
	@echo ""

nbproject/qt-${CONF}.mk: nbproject/qt-${CONF}.pro
	${QMAKE} -o qttmp-${CONF}.mk -after "OBJECTS_DIR=${BUILDDIR}" "DESTDIR=${DISTDIR}" nbproject/qt-${CONF}.pro
	mv -f qttmp-${CONF}.mk nbproject/qt-${CONF}.mk

