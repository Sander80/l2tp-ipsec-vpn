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
# exit if PPP_IPPARAM is not set or does not start with "{{OBJECTNAME}}"
if [ ! `echo $PPP_IPPARAM | grep "{{OBJECTNAME}}"` ]; then
  exit 0
fi

. {{GETIPSECINFOLIB}}

if test -f /var/run/L2tpIPsecVpn/${PPP_REMOTE} ; then
	rm -f /var/run/L2tpIPsecVpn/${PPP_REMOTE}
fi

case $PPP_IPPARAM in
{{#CONN_SECTION}}  "{{IPPARAM}}" )
    /sbin/route del -host {{GATEWAY}} gw ${DFLT_GWY} ${EXT_INTF}{{#DEFAULT_GATEWAY_SECTION}}
    /sbin/route del -net 0.0.0.0 gw ${DFLT_GWY} metric 100 dev ${EXT_INTF}
    /sbin/route add -net 0.0.0.0 gw ${DFLT_GWY} metric 0 dev ${EXT_INTF}{{/DEFAULT_GATEWAY_SECTION}}
	 ;;

{{/CONN_SECTION}}
esac
