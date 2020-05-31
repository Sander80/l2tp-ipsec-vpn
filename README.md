#  L2TP over IPsec virtual private network connections

This code was originally created by [Werner Jaeger](https://code.launchpad.net/~werner-jaeger/l2tp-ipsec-vpn/gui) in 2010.
Then it was brought to github by [gdm85](https://github.com/gdm85/l2tp-ipsec-vpn).
The code was modified and used for VPN connections with the use of [Rutoken](https://www.rutoken.ru/) smart cards by Vasily Shokov.
Then I got access to the code and used in for VPN connections at Ubuntu 18.04, however it was a whole mess to get things work properly.
Later I decided to update the code to a modern state and also contacted the Rutoken team, so now the code was improved with the help of Mikhalicin Peter from Rutoken.
Since gdm85 is not planning to maintain the l2tp-ipsec-vpn code, I asked the github team to switch the repository to a stand-alone mode, so it is not a fork any longer and will be developed independently.

Many upgrades were made to get this code working on modern Linux distributions (including Ubuntu 20.04).
- upgrade from QT4 to QT5
- upgrade from OpenSSL 1.0 to OpenSSL 1.1
- upgrade to pkexec calls for sudo password requests
- the code does no longer depend on any gui-based build environment
- option to decrease security level to 1 (in case your server does not support level 2 which is default in Ubuntu 20.04)
- no more storing password in temporary files in case it is not saved in the configuration

The code is currently maintained by Alexader Smirnov. Special thanks to Vasily Shokov and Mikhalicin Peter.

To get the code working, you need some libraries

sudo apt-get install build-essential automake cmake libtool libltdl-dev libssl-dev libcrypto++-dev pkg-config libpcsclite-dev debhelper qt5-qmake qt5-default strongswan xl2tpd libctemplate3 libctemplate-dev libpam0g-dev libpcap0.8-dev

Then simply run make to get it compiled and sudo make install to install.

In order to have the code working, you will need a version of ppp (point to point protocol) that supports eap-tls. 
Currently it is available in the repository of [jjkeijser](https://github.com/jjkeijser/ppp), but we hope to get it into the [main ppp repository](https://github.com/paulusmack/ppp).

Have a look at our wiki for more instructions. 

# License
Licensed under [GNU GPL version 3](LICENSE) 
