; {{FILENAME}} - configuration file for use with L2TP over IPsec.
; $Id$

; Manual: xl2tpd.conf(5)

; Created: {{CREATIONDATE}}
;      by: The {{APPNAME}} application version {{APPVERSION}}
;
; WARNING! All changes made in this file will be lost!

[global]
; listen-addr = 192.168.178.28
debug avp = no
debug network = no
debug packet = no
debug state = no
debug tunnel = no

{{#LAC_SECTION}}
[lac {{NAME}}]
lns = {{GATEWAY}}
pppoptfile = {{PPPOPTFILE}}
length bit = {{LENGTHBIT}}
redial = {{REDIAL}}
{{REDIALTIMEOUT}}
{{REDIALATTEMPTS}}
{{/LAC_SECTION}}
