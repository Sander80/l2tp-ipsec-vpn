# {{FILENAME}} - Openswan IPsec configuration file
# $Id$

# Manual: ipsec.conf(5)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!

version	2.0	# conforms to second version of ipsec.conf specification

config setup
	# plutodebug="parsing emitting control private"
	plutodebug=none
	strictcrlpolicy=no
	nat_traversal=yes
	interfaces=%defaultroute
	oe=off
	# which IPsec stack to use. netkey,klips,mast,auto or none
	protostack=netkey

conn %default
	keyingtries=3
	pfs=no
	rekey=yes
	type=transport
	left=%defaultroute
	leftprotoport=17/1701
	rightprotoport=17/1701

# Add connections here.

{{#CONN_SECTION}}
conn {{NAME}}
   authby={{AUTHBY}}
   {{LEFTCERT}}
	right={{GATEWAY}}
	rightid="{{IDENTITY}}"
	auto=add
{{/CONN_SECTION}}