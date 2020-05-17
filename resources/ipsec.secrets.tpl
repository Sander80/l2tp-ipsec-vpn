# {{FILENAME}} - secrets for IKE/IPsec authentication

# Manual: ipsec.secrets(5)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!
#
#
# This file holds shared secrets or RSA private keys for inter-Pluto
# authentication.  See ipsec_pluto(8) manpage, and HTML documentation.

# RSA private key for this host, authenticating it to any other host
# which knows the public part.  Suitable public keys, for ipsec.conf, DNS,
# or configuration of other implementations, can be extracted conveniently
# with "ipsec showhostkey".
#
{{#CONN_SECTION}}{{INDICES}} : {{KEYTYPE}} {{KEY}} {{PASSPHRASE}}
{{/CONN_SECTION}}
