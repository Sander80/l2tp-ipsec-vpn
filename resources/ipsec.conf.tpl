# {{FILENAME}} - Strongswan IPsec configuration file

# Manual: ipsec.conf(5)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!

config setup
	strictcrlpolicy=no
	

conn %default
	ikelifetime=60m
	keylife=20m
	rekeymargin=3m
	rekey=yes
	keyingtries=1
	keyexchange=ikev1
	authby=secret
	ike=aes128-sha1-modp1024,3des-sha1-modp1024!
	esp=aes128-sha1-modp1024,3des-sha1-modp1024!
	left=%defaultroute
	leftprotoport=17/1701
	rightprotoport=17/1701
	type=transport

{{#CONN_SECTION}}
conn {{NAME}}
   authby={{AUTHBY}}
   {{LEFTCERT}}
	right={{GATEWAY}}
	rightid=%any
	auto=add
{{/CONN_SECTION}}
