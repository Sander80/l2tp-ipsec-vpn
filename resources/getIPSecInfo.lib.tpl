# {{FILENAME}}
# $Id$

# Read file /var/run/L2tpIPsecVpnControlDaemon/defaultgateway.info and assign two shell variables
#   EXT_INTF   (network interface e.g. eth0 or wlan0)
#   DFLT_GWY   (default gateway e.g. 192.168.178.1)
#
# used by shell scripts /etc/ppp/ip-up.d/L2tpIPsecVpn-up and
# /etc/ppp/ip-down.d/L2tpIPsecVpn-down

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!
#
exec 3</var/run/L2tpIPsecVpnControlDaemon/defaultgateway.info
while read l <&3
do
{
	IFS="="
	set -- $l
	case "$1" in
		"defaultroutephys" )
			EXT_INTF=$2
			;;

		"defaultroutenexthop" )
			DFLT_GWY=$2
			;;
	esac
}
done
exec 3>&-

