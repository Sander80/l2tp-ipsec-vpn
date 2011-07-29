# {{FILENAME}} - Options used by PPP when a connection is made by an L2TP daemon
# $Id$

# Manual: PPPD(8)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!

#debug
#dump
#record /var/log/pppd

plugin passprompt.so
ipcp-accept-local
ipcp-accept-remote
idle 72000
ktune
noproxyarp
asyncmap 0
noauth
crtscts
lock
hide-password
modem
noipx

ipparam {{IPPARAM}}

promptprog "{{APPPFILEPATH}}"

{{#REFUSE_SECTION}}{{REFUSEPROTOCOL}}
{{/REFUSE_SECTION}}
remotename "{{REMOTENAME}}"
name "{{NAME}}"

{{#CERT_SECTION}}{{CERTENTRY}}
{{/CERT_SECTION}}
{{USEPEERDNS}}
{{NOBSDCOMP}}
{{NODEFLATE}}
{{NOVJ}}
{{LCPECHOINTERVAL}}
