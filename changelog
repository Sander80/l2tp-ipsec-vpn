1.0.9
 - fixed bug removes files that were installed by another package 
   (Closes: #684962)

1.0.8
 - fixed bug wrong email address choosen as username in EAP TLS authentication
 - now caching EAP-TLS autentication certificate in /etc/ipsec.d/certs
   directory

1.0.7
 - to be compatible with more linux distributions use service command
   instead of invoke-rc.d command to start and stop runlevel services
 - corrected wrong desktop check
 - corrected platform specific qt includes
 - in Makefile configure the appropriate qmake command (qmake or qmake-qt4)
 - fixed FTBFS because gcc-4.7 no longer includes unistd.h
 - fixed bug connection editor crashes on selecting a certificate or private
   key from smart card (LP: #975822)
 - fixed bug trayicon doesn't scale properly (LP: #98616)
 - provided a separate error status icon

1.0.6
 - transfered writing files connectionName.info and defaultgateway.info to
   L2tpIPsecVpnControlDaemon

1.0.5
 - unified runtime path, no longer using /var/tmp/L2tpIPsecVpn
 - enhanced install Makefile to create a world writable runtime directory
 - enhanced uninstall Makefile to remove runtime files and directories
 - chanaged debian copyright file to conform to the new official 1.0 Format
 - debian watch file is now working correct

1.0.4
 - pure L2TP VPN without IPSEC encryption is now possible
 - disable connection names in context menu when there is no default gateway
 - enabled i18n and added German translation
 - enabled size grip for all dialogs
 - check which graphical su command (gksudo, beesu or kdesudo) is available
   when starting connection editor
 - added postrm maintainer script to delete all configuration and runtime files
   on purge
 - fixed bug unable to add static routes (LP: #932591)
 - fixed bug If no smartcard is inserted the insert smartcard dialog is not
   shown (LP: ##941740)
 - fixed bug Smartcard inserted event is not detected (LP: #941741)
 - fixed bug Invalid private key file is written when importing PKCS#12
   certificate bundle (LP: #941743)
 - fixed bug Running Pluto is not detected (LP: #941746)
 - fixed bug xl2tpd overrides and ipparam settings (LP: #95152)

1.0.3
 - added timestamp to connection information log
 - fixed bug pre-shared key containing double quote not handled properly
      (LP: #881987)
1.0.2
 - fixed bug No connection names in context menu when using unity desktop
   (LP: #877083)
 - fixed bug Unable to successfully install/upgrade (LP: #818294)
 - fixed bug L2tpIPsecVpn core dumps (LP: #845845)
 - fixed bug copy and paste pre-shared key does not truncate trailing CR/LF
   (LP: #853020)
 - fixed bug System tray icon disappears sometimes (LP: #791471)

1.0.1
 - Makefile:
   * clean target did not delete all generated files
   * added clobber and uninstall target

 - Renamed targets in Qt test project files

1.0.0
 - fixed bug when connecting ipsec auto --up is occasionally started before
   pluto is running or has added the connection (LP: #781498)
 - fixed bug ipsec setup start failed (LP: #793542)
 - added menu entry to start applet
 - Debian Mainainer scrips
   * added VCS fields to control file
   * changed long description in control file
   * added gksu dependency in control file
   * corrected format link in copyright file
   * made url of Source file in copyright file version independent
   * used user owning the old PID to restart applet in postinst file
   * removed postrm file

0.9.9
 - added help button to all dialogs
 - added a tab to the ConnectionInformation dialog to show various connection information and
   connection statistics
 - Animated system tray icon when connecting or disconnecting
 - Certificates to be used for IPsec rsasig authentication can now be imported from a
   PKCS#12 certificate bundle
 - Debian package installer: start / restart applet after installation or upgrade
 - Spitted context menu. Now connection specific action are in a separate connection
   menu which is activated by a left click on the system tray icon
 - fixed bug dial-up to network interfaces (PPPn) are not automatically detected (LP: #741430)
 - fixed bug disconnection of physical network interface not detected if
   'Use default gateway on the remote network' is selected in PPP -> IP setting -> Routes
   configuration for the VPN connection (LP: #750000)
 - fixed bug manager applet no longer started automatically after
   upgrading it (LP: #750174)
 - fixed bug connection editor has wrong button layout (LP: #759510)
 - fixed bug invalid version string in .desktop files (LP: #759515)
 - fixed bug network interface monitor does not set netmask for
   address and route entries (LP: #761036)
 - fixed bug icon not available to other users (LP: #761216)

0.9.8
 - no longer depends on ppp-2.4.5-eaptls-mppe package. It is optional and only needed if
   one wants to use PPP EAP-TLS authentication
 - No longer depends on OpenSC, any PKCS11 library can be used and is dynamically loaded
 - Increased retry attempts to detect a system tray from 10 to 30
 - Use QT's QSslCertificate class instead of OpenSSL library calls
 - Show also certificate serial number in tool tips of certificate selection dialogs
 - Added preferences button in connection editor dialog
 - Removed apply button  in connection editor dialog
 - Fixed bug don't insist on overwriting /etc/resolv.conf

0.9.7
 - When connecting, now calling 'ipsec auto --ready' before calling 'ipsec auto --up' to
   avoid occasional need --listen before --initiate error

0.9.6
 - Fixed missing execute rights for L2tpIPsecVpn-down script
 - Now using /var/run/pluto/ipsec.info instead of /var/run/pluto/pluto.pid for
   testing if ipsec service is started
 - Fixed delayed display of disconnected status

0.9.5
 - Fixed bug successful connection not recognized by client if ip address of
   ipsec gateway and ip address of remote PPP are different

0.9.4
 - Less restrictive IPsec default configuration
   removed esp=3des-sha1, ikelifetime=8h, ike=3des-sha1-modp1024, keylife=24h
 - Increased PPP interface is up check time from 20 to 30 seconds
 - Ensuring a clean starting state before every connection attempt
 - A domain name is now allowed as Remote Server (IPsec peer)
 - Fixed looping packets bug, in cases where ip addresses of remote IPsec
   server and PPP server are different

0.9.3
 - Fixed broken password callback in Maverick series
 - Fixed asking to insert smart card for non EAP authentications
 - Fixed read only edit field for private key passphrase
   in connection editor (PPP tab, EAP properties)
 - Fixed missing host's ID when writing ipsec PSK secrets
 - Connection Information dialog is now modeless
 - Enabled password callback for CHAP authentication

0.9.2
 - Start of l2tp-ipsec-vpn project.
