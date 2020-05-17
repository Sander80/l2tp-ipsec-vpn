# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release
TARGET = L2tpIPsecVpn
VERSION = 1.1.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui network
SOURCES += src/ConnectionEditor.cpp src/ConnectionManager.cpp src/ConnectionState.cpp src/L2tpIPsecVpnApplication.cpp src/PasswordCallback.cpp src/VPNControlTask.cpp src/conf/AbstractConfWriter.cpp src/conf/ConfWriter.cpp src/conf/GetIPsecInfoScriptWriter.cpp src/conf/IPsecConfWriter.cpp src/conf/IPsecSecretsConfWriter.cpp src/conf/L2tpConfWriter.cpp src/conf/OpensslConfWriter.cpp src/conf/PPPConfWriter.cpp src/conf/PppDnsConfWriter.cpp src/conf/PppDownScriptWriter.cpp src/conf/PppUpScriptWriter.cpp src/conf/RSysLogConfWriter.cpp src/dialogs/AdvancedSettingsDialog.cpp src/dialogs/CertificateImportDialog.cpp src/dialogs/ConnectionEditorDialog.cpp src/dialogs/ConnectionInformationDialog.cpp src/dialogs/ConnectionSettingsDialog.cpp src/dialogs/EapSettingsDialog.cpp src/dialogs/InterfaceStatisticsDialog.cpp src/dialogs/IpSettingsDialog.cpp src/dialogs/PeerAuthenticationDialog.cpp src/dialogs/PreferencesEditorDialog.cpp src/dialogs/RouteSettingsDialog.cpp src/dialogs/SmartCardObjectsDialog.cpp src/localpeer/LocalPeer.cpp src/localpeer/LockedFile.cpp src/main.cpp src/models/ConnectionsModel.cpp src/models/IPsecCertificateListModel.cpp src/models/PppRoutesModel.cpp src/models/SmartCardObjectListModel.cpp src/pkcs11/Pkcs11.cpp src/pkcs11/Pkcs11Attribute.cpp src/pkcs11/SmartCardInfo.cpp src/pkcs11/SmartCardInsertWaitTask.cpp src/pkcs11/SmartCardState.cpp src/settings/ConnectionSettings.cpp src/settings/Preferences.cpp src/settings/Settings.cpp src/util/CertificateInfo.cpp src/util/EncSecrets.cpp src/util/GlobalFunctions.cpp src/util/Libtool.cpp src/util/NetworkInterface.cpp src/util/NetworkInterfaceMonitor.cpp src/util/Pkcs12.cpp src/util/SecretsChecker.cpp src/util/VpnControlDaemonClient.cpp
HEADERS += src/ConnectionEditor.h src/ConnectionManager.h src/ConnectionState.h src/L2tpIPsecVpnApplication.h src/PasswordCallback.h src/VPNControlTask.h src/conf/AbstractConfWriter.h src/conf/ConfWriter.h src/conf/GetIPsecInfoScriptWriter.h src/conf/IPsecConfWriter.h src/conf/IPsecSecretsConfWriter.h src/conf/L2tpConfWriter.h src/conf/OpensslConfWriter.h src/conf/PPPConfWriter.h src/conf/PppDnsConfWriter.h src/conf/PppDownScriptWriter.h src/conf/PppUpScriptWriter.h src/conf/RSysLogConfWriter.h src/dialogs/AdvancedSettingsDialog.h src/dialogs/CertificateImportDialog.h src/dialogs/ConnectionEditorDialog.h src/dialogs/ConnectionInformationDialog.h src/dialogs/ConnectionSettingsDialog.h src/dialogs/EapSettingsDialog.h src/dialogs/InterfaceStatisticsDialog.h src/dialogs/IpSettingsDialog.h src/dialogs/PeerAuthenticationDialog.h src/dialogs/PreferencesEditorDialog.h src/dialogs/RouteSettingsDialog.h src/dialogs/SmartCardObjectsDialog.h src/localpeer/LocalPeer.h src/localpeer/LockedFile.h src/models/ConnectionsModel.h src/models/IPsecCertificateListModel.h src/models/PppRoutesModel.h src/models/SmartCardObjectListModel.h src/pkcs11/Pkcs11.h src/pkcs11/Pkcs11Attribute.h src/pkcs11/SmartCardInfo.h src/pkcs11/SmartCardInsertWaitTask.h src/pkcs11/SmartCardState.h src/pkcs11/pkcs11.h src/settings/ConnectionSettings.h src/settings/Preferences.h src/settings/Settings.h src/util/CertificateInfo.h src/util/EncSecrets.h src/util/ErrorEx.h src/util/GlobalFunctions.h src/util/Libtool.h src/util/NetworkInterface.h src/util/NetworkInterfaceMonitor.h src/util/Pkcs12.h src/util/SecretsChecker.h src/util/VpnControlDaemonClient.h
FORMS += src/dialogs/AdvancedSettingsDialog.ui src/dialogs/CertificateImportDialog.ui src/dialogs/ConnectionEditorDialog.ui src/dialogs/ConnectionInformationDialog.ui src/dialogs/ConnectionSettingsDialog.ui src/dialogs/EapSettingsDialog.ui src/dialogs/InterfaceStatisticsDialog.ui src/dialogs/IpSettingsDialog.ui src/dialogs/PeerAuthenticationDialog.ui src/dialogs/PreferencesEditorDialog.ui src/dialogs/RouteSettingsDialog.ui src/dialogs/SmartCardObjectsDialog.ui
RESOURCES += resources/L2tpIPsecVpn.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux
MOC_DIR = src/generated
RCC_DIR = src/generated
UI_DIR = src/generated
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += src 
LIBS += 
LIBS+=-lctemplate
LIBS+=-lcrypto
LIBS+=-lltdl
target.path = /usr/bin
INSTALLS += target
data.path = /usr/share/L2tpIPsecVpn
data.files = resources/logo.png
INSTALLS += data
startupmenu.path = /etc/xdg/autostart
startupmenu.files = resources/L2tpIPsecVpn.desktop
INSTALLS += startupmenu
preferencesmenu.path = /usr/share/applications
preferencesmenu.files = resources/L2TP-Ipsec-VPN-Manager.desktop
INSTALLS += preferencesmenu
networkmenu.path=/usr/share/applications
networkmenu.files = resources/L2tpIPsecVpn-Applet.desktop
INSTALLS += networkmenu
TRANSLATIONS = nls/L2tpIPsecVpn_de.ts
QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_CFLAGS += -std=gnu++11