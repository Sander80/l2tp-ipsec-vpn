#  L2TP over IPsec virtual private network connections

Fork of https://github.com/gdm85/l2tp-ipsec-vpn by Werner Jaeger

Many upgrades were made to get this code working on modern Linux distributions (including Ubuntu 20.04) by Alexander Smirnov.
- upgrade from QT4 to QT5
- upgrade from OpenSSL 1.0 to OpenSSL 1.1
- upgrade to pkexec calls for sudo password requests
- the code does no longer depend on any gui-based build environment
- option to decrease security level to 1 (in case your server does not support level 2 which is default in Ubuntu 20.04)
- no more storing password in temporary files in case it is not saved in the configuration

Special thanks to Vasily Shokov and Mikhalicin Peter.

To get the code working, you need some libraries

sudo apt-get install build-essential automake cmake libtool libltdl-dev libssl-dev libcrypto++-dev pkg-config libpcsclite-dev debhelper qt5-qmake qt5-default strongswan xl2tpd libctemplate3 libctemplate-dev libpam0g-dev libpcap0.8-dev

Then simply run make to get it compiled and sudo make install to install. More instructions are coming!

# License
Licensed under [GNU GPL version 3](GPL)
