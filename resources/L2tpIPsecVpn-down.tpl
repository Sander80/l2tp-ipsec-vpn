#!/bin/sh -e
#
# {{FILENAME}}
# $Id$
#
# This script is called by /etc/ppp/ip-down after pppd has brought down the link
# to delete connection specific routes.
#
# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!
#
#

PPP_IFACE="$IFNAME"
PPP_TTY="$DEVICE"
PPP_SPEED="$SPEED"
PPP_LOCAL="$IPLOCAL"
PPP_REMOTE="$IPREMOTE"
PPP_IPPARAM="$6"

if test -f /var/run/L2tpIPsecVpnControlDaemon/connectionName.info; then
   PPP_IPPARAM={{OBJECTNAME}}-$(cat /var/run/L2tpIPsecVpnControlDaemon/connectionName.info)
fi

echo "{{FILENAME}} called with PPP_IPPARAM=$PPP_IPPARAM"

# exit if PPP_IPPARAM is not set or does not start with "{{OBJECTNAME}}"
if [ ! `echo $PPP_IPPARAM | grep "{{OBJECTNAME}}"` ]; then
  exit 0
fi

. {{GETIPSECINFOLIB}}

if test -f /var/run/L2tpIPsecVpnControlDaemon/${PPP_REMOTE} ; then
	rm -f /var/run/L2tpIPsecVpnControlDaemon/${PPP_REMOTE}
fi

case $PPP_IPPARAM in
{{#CONN_SECTION}}  "{{IPPARAM}}" )
    /sbin/route del -host {{GATEWAY}} gw ${DFLT_GWY} ${EXT_INTF} || true{{#DEFAULT_GATEWAY_SECTION}}
    /sbin/route del -net 0.0.0.0 gw ${DFLT_GWY} metric 100 dev ${EXT_INTF} || true
    /sbin/route add -net 0.0.0.0 gw ${DFLT_GWY} metric 0 dev ${EXT_INTF}{{/DEFAULT_GATEWAY_SECTION}}{{#NOROUTE_SECTION}}
    /sbin/route del -net {{IPADDRESS}} netmask {{IPNETMASK}} gw ${DFLT_GWY} dev ${EXT_INTF} || true {{/NOROUTE_SECTION}}
	 ;;

{{/CONN_SECTION}}
esac

# copied from http://www.ussg.iu.edu/hypermail/lin...02.1/0146.html
# uncomment for CentOS
#if [ -n "$USEPEERDNS" -a -f /etc/ppp/resolv.conf ]; then
#	if [ -f /etc/ppp/resolv.prev ]; then
#		cp -f /etc/ppp/resolv.prev /etc/resolv.conf
#	else
#		rm -f /etc/resolv.conf
#	fi
#	chmod 644 /etc/resolv.conf
#
#	rm -f /etc/ppp/resolv.prev
#fi 
