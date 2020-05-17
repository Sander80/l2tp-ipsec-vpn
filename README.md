#  L2TP over IPsec virtual private network connections

Fork of https://github.com/gdm85/l2tp-ipsec-vpn by Werner Jaeger

Many upgrades were made to get this code working on modern Linux distributions (including Ubuntu 20.04)
- upgrade from QT4 to QT5
- upgrade from OpenSSL 1.0 to OpenSSL 1.1
- upgrade to pkexec calls for sudo password requests

Some files were brought in by some other developer (the "generated files folder" sources, now they are a part of the distribution).
The code does no longer depend on any gui-based build environment.

To get the code working, you need some libraries

sudo apt-get install build-essential automake cmake libtool libltdl-dev libssl-dev libcrypto++-dev pkg-config libpcsclite-dev debhelper qt5-qmake qt5-default strongswan xl2tpd libctemplate3 libctemplate-dev libpam0g-dev libpcap0.8-dev

Then simply run make to get it compiled and sudo make install to install. More instructions are coming!

# License
Licensed under [GNU GPL version 3](GPL)
