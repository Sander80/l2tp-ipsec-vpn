# {{FILENAME}} - Openssl configuration file
# $Id$

# Manual: config(5)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!
#
openssl_conf = openssl_def

[ openssl_def ]
engines = engine_section
ssl_conf = ssl_sect

[ engine_section ]
{{ENGINEID}} = {{ENGINEID}}_section

[ {{ENGINEID}}_section ]
engine_id = {{ENGINEID}}
dynamic_path = {{DYNAMICPATH}}
MODULE_PATH = {{MODULEPATH}}
init=0

[ssl_sect]
system_default = ssl_default_sect

[ssl_default_sect]
CipherString = DEFAULT:@SECLEVEL=1
