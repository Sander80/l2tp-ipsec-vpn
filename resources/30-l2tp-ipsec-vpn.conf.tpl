# {{FILENAME}} - Rsyslogd configuration file
# $Id$

# Manual: rsyslog.conf(5)

# Created: {{CREATIONDATE}}
#      by: The {{APPNAME}} application version {{APPVERSION}}
#
# WARNING! All changes made in this file will be lost!

# Log xl2tpd pppd and ipsec generated log messages to a pipe
:syslogtag,contains,"xl2tpd[" |/var/log/l2tpipsecvpn.pipe
:syslogtag,contains,"pppd[" |/var/log/l2tpipsecvpn.pipe
:syslogtag,contains,"ipsec__plutorun:" |/var/log/l2tpipsecvpn.pipe

# Uncomment the following to stop logging anything that matches the last rule.
# Doing this will stop logging messages to the file
#& ~
