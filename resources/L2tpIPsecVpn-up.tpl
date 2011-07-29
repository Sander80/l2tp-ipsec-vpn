#!/bin/sh -e
#
# {{FILENAME}}
# $Id$
#
# This script is called by /etc/ppp/ip-up after pppd has established the link
# to add routes for given connections.
#
# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!
#
#
# exit if PPP_IPPARAM is not set or does not start with "{{OBJECTNAME}}"
if [ ! `echo $PPP_IPPARAM | grep "{{OBJECTNAME}}"` ]; then
  exit 0
fi

. {{GETIPSECINFOLIB}}

if test ! -d /var/run/L2tpIPsecVpn ; then
	 mkdir /var/run/L2tpIPsecVpn
fi

# remember remote PPP address for given connection name
echo "${PPP_IPPARAM}" | cut -d'-' -f2 > /var/run/L2tpIPsecVpn/${PPP_REMOTE}

case $PPP_IPPARAM in
{{#CONN_SECTION}}  "{{IPPARAM}}" )
    # direct tunneled packets to the tunnel server
    /sbin/route add -host {{GATEWAY}} gw ${DFLT_GWY} dev ${EXT_INTF}{{#ROUTE_SECTION}}
    /sbin/route add -net {{IPADDRESS}} netmask {{IPNETMASK}} dev ${PPP_IFACE}{{/ROUTE_SECTION}}{{#DEFAULT_GATEWAY_SECTION}}
    /sbin/route add -net 0.0.0.0 dev ${PPP_IFACE}
    /sbin/route add -net 0.0.0.0 gw ${DFLT_GWY} metric 100 dev ${EXT_INTF}
    /sbin/route del -net 0.0.0.0 gw ${DFLT_GWY} metric 0 dev ${EXT_INTF}{{/DEFAULT_GATEWAY_SECTION}}
	 ;;

{{/CONN_SECTION}}
esac
