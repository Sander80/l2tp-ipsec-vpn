# {{FILENAME}} - PPP provider specific static DNS configuration file containing
#                the nameservers and search list for host-name lookup
# $Id$

# Manual: resolv.conf(5)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!
#
{{#DNS_SECTION}}nameserver {{IPADDRESS}}
{{/DNS_SECTION}}{{#SEARCH_SECTION}}search {{SEARCHLIST}}
{{/SEARCH_SECTION}}