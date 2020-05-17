/*
 * $Id: ConnectionSettings.h 165 2017-12-30 14:12:45Z wejaeger $
 *
 * File:   ConnectionSettings.h
 * Author: Werner Jaeger
 *
 * Created on July 22, 2010, 10:14 AM
 *
 * Copyright 2010 Werner Jaeger.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONNECTIONSETTINGS_H
#define	CONNECTIONSETTINGS_H

#include "Settings.h"

class QHostAddress;
class CommonSettings;
class IPSecSettings;
class L2tpSettings;
class PppSettings;
class PppEapSettings;
class PppIpSettings;

static const QString ROUTES = "Routes";
static const QString NOROUTES = "NoRoutes";

class ConnectionSettings : public Settings
{
public:
   typedef enum { Ok, InvalidName, DuplicateName, ReadOnly } Result;

   ConnectionSettings();
   virtual ~ConnectionSettings();

   int connections() const;
   QString connection(int iConnectionNo) const;
   Result addConnection(const QString& strName) const;
   bool removeConnection(int iConnectionNo) const;
   QString gateway(const QString& strName) const;

   CommonSettings commonSettings(const QString& strName) const;
   IPSecSettings ipsecSettings(const QString& strName) const;
   L2tpSettings l2tpSettings(const QString& strName) const;
   PppSettings pppSettings(const QString& strName) const;

   int deleteAllConfFiles();

protected:
   explicit ConnectionSettings(int iConnectionNo);
   ConnectionSettings(const ConnectionSettings& orig);

   int connectionNo() const { return(m_iConnectionNo); }
   bool setValue(const QString& strValue, const QString& strPath) const;
   QString getStringValue(const QString& strPath) const;
   bool setSecret(const QString& strValue, const QString& strPath) const;
   QString getSecret(const QString& strPath) const;
   bool setValue(int iValue, const QString& strPath) const;
   int getIntValue(const QString& strPath, int iDefault = 0) const;
   bool setValue(bool fValue, const QString& strPath) const;
   bool getBoolValue(const QString& strPath, bool fDefault = false) const;
   bool setRouteProperty(const QString& strRouteSectionName, const QString& strValue, int iRow, const QString& strPropertyName) const;
   QString routeProperty(const QString& strRouteSectionName, int iRow, const QString& strPropertyName) const;

private:
   ConnectionSettings& operator=(const ConnectionSettings& orig);

   int connection(const QString& strName) const;
   bool containsConnection(const QString& strName) const;
   Result validateName(const QString& strName) const;

   const int m_iConnectionNo;
};

class CommonSettings : public ConnectionSettings
{
public:
   virtual ~CommonSettings() {}

   bool setAutoConnect(bool fAutoConnect) const;
   bool autoConnect() const;

   bool setDisableIPSecEncryption(bool fDisableIPSecEncryption) const;
   bool disableIPSecEncryption() const;

private:
   explicit CommonSettings(int iConnectionNo) : ConnectionSettings(iConnectionNo) {}
   CommonSettings& operator=(const CommonSettings& orig);

   friend class ConnectionSettings;
};

class IPSecSettings : public ConnectionSettings
{
public:
   virtual ~IPSecSettings() {}

   bool setGateway(const QString& strGateway) const;
   QString gateway() const;
   bool setIdentity(const QString& strIdentity) const;
   QString identity() const;
   bool setPreSharedKey(const QString& strPsk) const;
   QString preSharedKey() const;
   bool setCertificateFileName(const QString& strFileName) const;
   QString certificateFileName() const;
   bool setPrivateKeyFilePath(const QString& strFilePath) const;
   QString privateKeyFilePath() const;
   bool setPrivateKeyPassphrase(const QString& strPassphrase) const;
   QString privateKeyPassphrase() const;
   bool setAuthBy(const QString& strAuthBy) const;
   QString authBy() const;

private:
   explicit IPSecSettings(int iConnectionNo) : ConnectionSettings(iConnectionNo) {}
   IPSecSettings& operator=(const IPSecSettings& orig);

   friend class ConnectionSettings;
};

class L2tpSettings : public ConnectionSettings
{
public:
   virtual ~L2tpSettings() {}

   bool setLengthBit(bool fEnable) const;
   bool lengthBit() const;
   bool setRedial(bool fEnable) const;
   bool redial() const;
   bool setRedialTimeout(int iTimeout) const;
   int redialTimeout() const;
   bool setRedialAttempts(int iAttempts) const;
   int redialAttempts() const;

private:
   explicit L2tpSettings(int iConnectionNo) : ConnectionSettings(iConnectionNo) {}
   L2tpSettings& operator=(const L2tpSettings& orig);

   friend class ConnectionSettings;
};

class PppSettings : public ConnectionSettings
{
public:
   virtual ~PppSettings() {}

   PppEapSettings eapSettings() const;
   PppIpSettings ipSettings() const;
   bool setRefuseChap(bool fRefuse) const;
   bool refuseChap() const;
   bool setRefuseMsChap(bool fRefuse) const;
   bool refuseMsChap() const;
   bool setRefuseMsChapV2(bool fRefuse) const;
   bool refuseMsChapV2() const;
   bool setRefuseEap(bool fRefuse) const;
   bool refuseEap() const;
   bool setRefusePap(bool fRefuse) const;
   bool refusePap() const;
   bool setUserName(const QString& strUserName) const;
   QString userName() const;
   bool setPassword(const QString& strPassword) const;
   QString password() const;

   bool setRemoteName(const QString& strRemoteName) const;
   QString remoteName() const;

   // advanced settings
   bool setNoBSDCompression(bool fSet) const;
   bool noBSDCompression() const;
   bool setNoDeflate(bool fSet) const;
   bool noDeflate() const;
   bool setNoVj(bool fSet) const;
   bool noVj() const;
   bool setLcpEchoInterval(int iInterval) const;
   int lcpEchoInterval() const;

private:
   explicit PppSettings(int iConnectionNo) : ConnectionSettings(iConnectionNo) {}
   PppSettings& operator=(const PppSettings& orig);

   friend class PppEapSettings;
   friend class PppIpSettings;
   friend class ConnectionSettings;
};

class PppEapSettings : public PppSettings
{
public:
   virtual ~PppEapSettings() {}

   bool setUseSmartCard(bool fUse) const;
   bool useSmartCard() const;
   bool setCertificatePath(const QString& strCertificatePath) const;
   QString certificatePath() const;
   bool setPrivateKeyPath(const QString& strPrivateKeyPath) const;
   QString privateKeyPath() const;
   bool setPrivateKeyPassword(const QString& strPrivateKeyPassword) const;
   QString privateKeyPassword() const;
   bool setCaCertificatePath(const QString& strCaCertificatePath) const;
   QString caCertificatePath() const;

private:
   explicit PppEapSettings(int iConnectionNo) : PppSettings(iConnectionNo) {}
   PppEapSettings& operator=(const PppEapSettings& orig);

   friend class PppSettings;
};

class PppIpSettings : public PppSettings
{
public:
   virtual ~PppIpSettings() {}

   bool setUsePeerDns(bool fUse) const;
   bool usePeerDns() const;
   bool setPreferredDnsServerAddress(const QString& strPreferredDnsServerAddress) const;
   QString preferredDnsServerAddress() const;
   bool setAlternateDnsServerAddress(const QString& strAlternateDnsServerAddress) const;
   QString alternateDnsServerAddress() const;
   bool setSearchDomains(const QString& strSearchDomains) const;
   QString searchDomains() const;

   bool setUseDefaultGateway(bool fUse) const;
   bool useDefaultGateway() const;

   int routes() const { return(routes(ROUTES)); }
   bool setRouteAddress(int iRow, const QString& strAddress) const { return(setRouteAddress(ROUTES, iRow, strAddress)); }
   QString routeAddress(int iRow) const { return(routeAddress(ROUTES, iRow)); }
   bool setRouteNetmask(int iRow, const QString& strNetMask) const { return(setRouteNetmask(ROUTES, iRow, strNetMask)); }
   QString routeNetmask(int iRow) const { return(routeNetmask(ROUTES, iRow)); }
   bool setRouteComment(int iRow, const QString& strComment) const { return(setRouteComment(ROUTES, iRow, strComment)); }
   QString routeComment(int iRow) const { return(routeComment(ROUTES, iRow)); }
   bool addRoute() const { return(addRoute(ROUTES)); }
   bool removeRoute(int iRow) const { return(removeRoute(ROUTES, iRow)); }

   int noRoutes() const { return(routes(NOROUTES)); }
   bool setNoRouteAddress(int iRow, const QString& strAddress) const { return(setRouteAddress(NOROUTES, iRow, strAddress)); }
   QString noRouteAddress(int iRow) const { return(routeAddress(NOROUTES, iRow)); }
   bool setNoRouteNetmask(int iRow, const QString& strNetMask) const { return(setRouteNetmask(NOROUTES, iRow, strNetMask)); }
   QString noRouteNetmask(int iRow) const { return(routeNetmask(NOROUTES, iRow)); }
   bool setNoRouteComment(int iRow, const QString& strComment) const { return(setRouteComment(NOROUTES, iRow, strComment)); }
   QString noRouteComment(int iRow) const { return(routeComment(NOROUTES, iRow)); }
   bool addNoRoute() const { return(addRoute(NOROUTES)); }
   bool removeNoRoute(int iRow) const { return(removeRoute(NOROUTES, iRow)); }

private:
   explicit PppIpSettings(int iConnectionNo) : PppSettings(iConnectionNo) {}
   PppIpSettings& operator=(const PppIpSettings& orig);

   int routes(const QString& strRouteSectionName) const;
   bool setRouteAddress(const QString& strRouteSectionName, int iRow, const QString& strAddress) const;
   QString routeAddress(const QString& strRouteSectionName, int iRow) const;
   bool setRouteNetmask(const QString& strRouteSectionName, int iRow, const QString& strNetMask) const;
   QString routeNetmask(const QString& strRouteSectionName, int iRow) const;
   bool setRouteComment(const QString& strRouteSectionName, int iRow, const QString& strComment) const;
   QString routeComment(const QString& strRouteSectionName, int iRow) const;
   bool addRoute(const QString& strRouteSectionName) const;
   bool removeRoute(const QString& strRouteSectionName, int iRow) const;

   friend class PppSettings;
};

#endif	/* CONNECTIONSETTINGS_H */

