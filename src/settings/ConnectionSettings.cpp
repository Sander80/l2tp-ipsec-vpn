/*
 * $Id: ConnectionSettings.cpp 153 2012-10-11 04:47:46Z wejaeger $
 *
 * File:   ConnectionSettings.cpp
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

#include <QSettings>
#include <QFile>
#include <QRegExp>
#include <QHostAddress>
#include <QCoreApplication>

#include "conf/ConfWriter.h"
#include "models/ConnectionsModel.h"
#include "util/EncSecrets.h"
#include "ConnectionSettings.h"

static unsigned char const KEY[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
static unsigned char const IV[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

static const char* const VALIDNAMEPATTERN = "^[a-zA-Z][0-9a-zA-Z\\-\\._]{0,29}$";

/** Arrays*/
static const QString CONNECTIONS = "Connections";
static const QString ROUTES = "Routes";

/** Groups */
static const QString COMMON = "Common";
static const QString IPSEC = "IPSec";
static const QString L2TP = "L2tp";
static const QString PPP = "Ppp";
static const QString EAP = "Ppp/Eap";
static const QString IP = "Ppp/Ip";

/** properties */
static const QString NAME = "name";
static const QString AUTOCONNECT = "auoConnect";
static const QString DISABLEIPSECENCRYPTION = "disableIPSecEncryption";
static const QString GATEWAY = "gateway";
static const QString IDENTITY = "identity";
static const QString USERNAME = "userName";
static const QString PASSWORD = "password";
static const QString REQUIREAUTH = "requireAuthentication";
static const QString CHAP = "chap";
static const QString PAP = "pap";
static const QString LENGTHBIT = "lengthBit";
static const QString REDIAL = "redial";
static const QString REDIALTIMEOUT = "redialTimeout";
static const QString REDIALATTEMPTS = "redialAttempts";
static const QString PSK = "psk";
static const QString CERTFN = "certFileName";
static const QString PRIVATEKEYFILEPATH = "privateKeyFilePath";
static const QString PRIVATEKEYPASSPHRASE = "privateKeyPassphrase";
static const QString AUTHBY = "authBy";
static const QString REFUSECHAP = "refuseChap";
static const QString REFUSEMSCHAP = "refuseMsChap";
static const QString REFUSEMSCHAPV2 = "refuseMsChapV2";
static const QString REFUSEEAP = "refuseEap";
static const QString REFUSEPAP = "refusePap";
static const QString REMOTENAME = "remoteName";
static const QString NODSDCOMP = "nobsdcomp";
static const QString NODEFLATE = "nodeflate";
static const QString NOVJ = "novj";
static const QString LCPECHOINTERVAL = "lcpEchoInterval";
static const QString USESMARTCARD = "useSmartCard";
static const QString CERTIFICATEPATH = "certificatePath";
static const QString PRIVATEKEYPATH = "privateKeyPath";
static const QString PRIVATEKEYPASSWORD = "privateKeyPassword";
static const QString CACERTIFICATEPATH = "caCertificatePath";
static const QString IPADDRESS = "ipAddress";
static const QString IPNETMASK = "ipNetMask";
static const QString COMMENT = "comment";
static const QString USEPEERDNS = "usePeerDns";
static const QString PREFERREDDNSSERVERADDRESS = "preferredDnsServerAddress";
static const QString ALTERNATEDNSSERVERADDRESS = "alternateDnsServerAddress";
static const QString SEARCHDOMAINS = "searchDomains";
static const QString USEDEFAULTGATEWAY = "useDefaultGateway";

ConnectionSettings::ConnectionSettings() : m_iConnectionNo(-1)
{
}

ConnectionSettings::ConnectionSettings(int iConnectionNo) : m_iConnectionNo(iConnectionNo)
{
}

ConnectionSettings::ConnectionSettings(const ConnectionSettings& orig) : Settings(), m_iConnectionNo(orig.connectionNo())
{
}

ConnectionSettings::~ConnectionSettings()
{
}

int ConnectionSettings::connections() const
{
   const int iSize(qSettings()->beginReadArray(CONNECTIONS));
   qSettings()->endArray();

   return(iSize);
}

ConnectionSettings::Result ConnectionSettings::addConnection(const QString& strName) const
{
   const Result result(qSettings()->isWritable() ? validateName(strName): ReadOnly);

   if (result == Ok)
   {
      const int iSize(connections());

      qSettings()->beginWriteArray(CONNECTIONS);
      qSettings()->setArrayIndex(iSize);
      qSettings()->setValue(NAME, strName);
      qSettings()->endArray();
   }

   return(result);
}

bool ConnectionSettings::removeConnection(int iConnectionNo) const
{
   bool fRet(iConnectionNo < connections() && qSettings()->isWritable());

   if (fRet)
   {
      QFile pppOptFile(ConfWriter::fileName(ConfWriter::PPP, connection(iConnectionNo)));
      if (pppOptFile.exists())
         pppOptFile.remove();

      QFile pppDnsFile(ConfWriter::fileName(ConfWriter::PPPDNSCONF, QCoreApplication::instance()->objectName() + "-" + connection(iConnectionNo)));
      if (pppDnsFile.exists())
         pppDnsFile.remove();

      fRet = ConnectionSettings::removeArrayItem(CONNECTIONS, iConnectionNo);
   }

   return(fRet);
}

QString ConnectionSettings::gateway(const QString& strName) const
{
   return(ipsecSettings(strName).gateway());
}

CommonSettings ConnectionSettings::commonSettings(const QString& strName) const
{
   return(CommonSettings(connection(strName)));
}

IPSecSettings ConnectionSettings::ipsecSettings(const QString& strName) const
{
   return(IPSecSettings(connection(strName)));
}

L2tpSettings ConnectionSettings::l2tpSettings(const QString& strName) const
{
   return(L2tpSettings(connection(strName)));
}

PppSettings ConnectionSettings::pppSettings(const QString& strName) const
{
   return(PppSettings(connection(strName)));
}

int ConnectionSettings::deleteAllConfFiles()
{
   int iRet(0);

   if (ConnectionsModel().isWriteable())
   {
      for (int i = 0; i < ConfWriter::END; i++)
      {
         const ConfWriter::Conf conf(static_cast<ConfWriter::Conf>(i));

         if (conf != ConfWriter::IPsec && conf != ConfWriter::L2TP && conf != ConfWriter::IPsecSECRET)
         {
            const QString strConfFile(ConfWriter::fileName(conf));
            if (QFile::exists(strConfFile))
               QFile::remove(strConfFile);
         }
      }

      const int iConnections(connections());

      for (int i = 0; i < iConnections; i++)
      {
         const QString strConnectionName(connection(i));
         QFile::remove(ConfWriter::fileName(ConfWriter::PPP, strConnectionName));

         const QString strDNSConfInstance(QCoreApplication::instance()->objectName() + "-" +strConnectionName);
         QFile::remove(ConfWriter::fileName(ConfWriter::PPPDNSCONF, strDNSConfInstance));
      }
   }
   else
      iRet = -1;

   return(iRet);
}

QString ConnectionSettings::connection(int iConnectionNo) const
{
   QString strRet;

   const int iSize(qSettings()->beginReadArray(CONNECTIONS));
   if (iConnectionNo < iSize)
   {
      qSettings()->setArrayIndex(iConnectionNo);
      strRet = qSettings()->value(NAME).toString();
   }
   qSettings()->endArray();

   return(strRet);
}

int ConnectionSettings::connection(const QString& strName) const
{
   int iRet;
   bool fFound(false);
   const int iSize(qSettings()->beginReadArray(CONNECTIONS));
   for (iRet = 0; !fFound && iRet < iSize; iRet++)
   {
      qSettings()->setArrayIndex(iRet);
      if (qSettings()->value(NAME, "") == strName)
         fFound = true;
   }
   qSettings()->endArray();

   return(fFound ? iRet - 1 : -1);
}

ConnectionSettings::Result ConnectionSettings::validateName(const QString& strName) const
{
   Result result(connection(strName) >=0 ? DuplicateName : Ok);
   if (result == Ok)
   {
      QRegExp rx(VALIDNAMEPATTERN);
      if (!rx.exactMatch(strName))
         result = InvalidName;
   }

   return(result);
}

/*********** helpers ***************/
bool ConnectionSettings::setValue(const QString& strValue, const QString& strPath) const
{
   const bool fRet(m_iConnectionNo >= 0 && qSettings()->isWritable());

   if (fRet)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      if  (qSettings()->value(strPath) != strValue.trimmed())
         qSettings()->setValue(strPath, strValue.trimmed());
      qSettings()->endArray();
   }

   return(fRet);
}

QString ConnectionSettings::getStringValue(const QString& strPath) const
{
   QString strRet;

   if (m_iConnectionNo >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      strRet = qSettings()->value(strPath, "").toString();
      qSettings()->endArray();
   }

   return(strRet);
}

bool ConnectionSettings::setSecret(const QString& strValue, const QString& strPath) const
{
   const bool fRet(m_iConnectionNo >= 0 && qSettings()->isWritable());

   if (fRet)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      EncSecrets secrets(KEY, IV, strValue.trimmed().toAscii().constData());
      if  (qSettings()->value(strPath) != secrets.getbuf())
         qSettings()->setValue(strPath, secrets.getbuf());
      qSettings()->endArray();
   }

   return(fRet);
}

QString ConnectionSettings::getSecret(const QString& strPath) const
{
   QString strRet;

   if (m_iConnectionNo >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      strRet = qSettings()->value(strPath, "").toString();
      EncSecrets secrets(strRet.toAscii().constData());
      strRet = secrets.retrieve(KEY, IV);
      qSettings()->endArray();
   }

   return(strRet);
}

bool ConnectionSettings::setValue(int iValue, const QString& strPath) const
{
   const bool fRet(m_iConnectionNo >= 0 && qSettings()->isWritable());

   if (fRet)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      if  (qSettings()->value(strPath) != iValue)
         qSettings()->setValue(strPath, iValue);
      qSettings()->endArray();
   }

   return(fRet);
}

int ConnectionSettings::getIntValue(const QString& strPath, int iDefault) const
{
   int iRet(0);

   if (m_iConnectionNo >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      iRet = qSettings()->value(strPath, iDefault).toInt(NULL);
      qSettings()->endArray();
   }

   return(iRet);
}

bool ConnectionSettings::setValue(bool fValue, const QString& strPath) const
{
   const bool fRet(m_iConnectionNo >= 0 && qSettings()->isWritable());

   if (fRet)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      if  (qSettings()->value(strPath) != fValue)
         qSettings()->setValue(strPath, fValue);
      qSettings()->endArray();
   }

   return(fRet);
}

bool ConnectionSettings::getBoolValue(const QString& strPath, bool fDefault) const
{
   bool fRet(false);

   if (m_iConnectionNo >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      fRet = qSettings()->value(strPath, fDefault).toBool();
      qSettings()->endArray();
   }

   return(fRet);
}

bool ConnectionSettings::setRouteProperty(const QString& strValue, int iRow, const QString& strPropertyName) const
{
   bool fRet(m_iConnectionNo >= 0 && qSettings()->isWritable());

   if (fRet)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      qSettings()->beginGroup(IP);

      const int iSize(qSettings()->beginReadArray(ROUTES));
      if (iRow < iSize)
      {
         qSettings()->setArrayIndex(iRow);
         if  (qSettings()->value(strPropertyName) != strValue)
            qSettings()->setValue(strPropertyName, strValue);
      }
      else
         fRet = false;

      qSettings()->endArray();

      qSettings()->endGroup();
      qSettings()->endArray();
   }

   return(fRet);
}

QString ConnectionSettings::routeProperty(int iRow, const QString& strPropertyName) const
{
   QString strRet;

   if (m_iConnectionNo >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(m_iConnectionNo);
      qSettings()->beginGroup(IP);

      const int iSize(qSettings()->beginReadArray(ROUTES));
      if (iRow < iSize)
      {
         qSettings()->setArrayIndex(iRow);
         strRet = qSettings()->value(strPropertyName).toString();
      }
      qSettings()->endArray();

      qSettings()->endGroup();
      qSettings()->endArray();
  }

   return(strRet);
}

/********** Common settings ************/

bool CommonSettings::setAutoConnect(bool fAutoConnect) const
{
   return(setValue(fAutoConnect, COMMON + '/' + AUTOCONNECT));
}

bool CommonSettings::autoConnect() const
{
   return(getBoolValue(COMMON + '/' + AUTOCONNECT));
}

bool CommonSettings::setDisableIPSecEncryption(bool fDisableIPSecEncryption) const
{
   return(setValue(fDisableIPSecEncryption, COMMON + '/' + DISABLEIPSECENCRYPTION));
}

bool CommonSettings::disableIPSecEncryption() const
{
   return(getBoolValue(COMMON + '/' + DISABLEIPSECENCRYPTION));
}


/********** IPsec ************/

bool IPSecSettings::setGateway(const QString& strGateway) const
{
   return(setValue(strGateway, IPSEC + '/' + GATEWAY));
}

QString IPSecSettings::gateway() const
{
   return(getStringValue(IPSEC + '/' + GATEWAY));
}

bool IPSecSettings::setIdentity(const QString& strIdentity) const
{
   return(setValue(strIdentity, IPSEC + '/' + IDENTITY));
}

QString IPSecSettings::identity() const
{
   return(getStringValue(IPSEC + '/' + IDENTITY));
}

bool IPSecSettings::setPreSharedKey(const QString& strPsk) const
{
   return(setSecret(strPsk, IPSEC + '/' + PSK));
}

QString IPSecSettings::preSharedKey() const
{
   return(getSecret(IPSEC + '/' + PSK));
}

bool IPSecSettings::setCertificateFileName(const QString& strFileName) const
{
   return(setValue(strFileName, IPSEC + '/' + CERTFN));
}

QString IPSecSettings::certificateFileName() const
{
   return(getStringValue(IPSEC + '/' + CERTFN));
}

bool IPSecSettings::setPrivateKeyFilePath(const QString& strFilePath) const
{
   return(setValue(strFilePath, IPSEC + '/' + PRIVATEKEYFILEPATH));
}

QString IPSecSettings::privateKeyFilePath() const
{
   return(getStringValue(IPSEC + '/' + PRIVATEKEYFILEPATH));
}

bool IPSecSettings::setPrivateKeyPassphrase(const QString& strPassphrase) const
{
   return(setSecret(strPassphrase, IPSEC + '/' + PRIVATEKEYPASSPHRASE));
}

QString IPSecSettings::privateKeyPassphrase() const
{
   return(getSecret(IPSEC + '/' + PRIVATEKEYPASSPHRASE));
}

bool IPSecSettings::setAuthBy(const QString& strAuthBy) const
{
   return(setValue(strAuthBy, IPSEC + '/' + AUTHBY));
}

QString IPSecSettings::authBy() const
{
   return(getStringValue(IPSEC + '/' + AUTHBY));
}

/********** L2tp ************/

bool L2tpSettings::setLengthBit(bool fEnable) const
{
   return(setValue(fEnable, L2TP + '/' + LENGTHBIT));
}

bool L2tpSettings::lengthBit() const
{
   return(getBoolValue(L2TP + '/' + LENGTHBIT));
}

bool L2tpSettings::setRedial(bool fEnable) const
{
   return(setValue(fEnable, L2TP + '/' + REDIAL));
}

bool L2tpSettings::redial() const
{
   return(getBoolValue(L2TP + '/' + REDIAL));
}

bool L2tpSettings::setRedialTimeout(int iTimeout) const
{
   return(setValue(iTimeout, L2TP + '/' + REDIALTIMEOUT));
}

int L2tpSettings::redialTimeout() const
{
   return(getIntValue(L2TP + '/' + REDIALTIMEOUT));
}

bool L2tpSettings::setRedialAttempts(int iAttempts) const
{
   return(setValue(iAttempts, L2TP + '/' + REDIALATTEMPTS));
}

int L2tpSettings::redialAttempts() const
{
   return(getIntValue(L2TP + '/' + REDIALATTEMPTS));
}

/********** PPP ************/
 PppEapSettings PppSettings::eapSettings() const
 {
    return(PppEapSettings(connectionNo()));
 }

 PppIpSettings PppSettings::ipSettings() const
 {
   return(PppIpSettings(connectionNo()));
 }

bool PppSettings::setRefuseChap(bool fRefuse) const
{
   return(setValue(fRefuse, PPP + '/' + REFUSECHAP));
}

bool PppSettings::refuseChap() const
{
   return(getBoolValue(PPP + '/' + REFUSECHAP));
}

bool PppSettings::setRefuseMsChap(bool fRefuse) const
{
   return(setValue(fRefuse, PPP + '/' + REFUSEMSCHAP));
}

bool PppSettings::refuseMsChap() const
{
   return(getBoolValue(PPP + '/' + REFUSEMSCHAP));
}
bool PppSettings::setRefuseMsChapV2(bool fRefuse) const
{
   return(setValue(fRefuse, PPP + '/' + REFUSEMSCHAPV2));
}

bool PppSettings::refuseMsChapV2() const
{
   return(getBoolValue(PPP + '/' + REFUSEMSCHAPV2));
}
bool PppSettings::setRefuseEap(bool fRefuse) const
{
   return(setValue(fRefuse, PPP + '/' + REFUSEEAP));
}

bool PppSettings::refuseEap() const
{
   return(getBoolValue(PPP + '/' + REFUSEEAP));
}
bool PppSettings::setRefusePap(bool fRefuse) const
{
   return(setValue(fRefuse, PPP + '/' + REFUSEPAP));
}

bool PppSettings::refusePap() const
{
   return(getBoolValue(PPP + '/' + REFUSEPAP));
}

bool PppSettings::setUserName(const QString& strUserName) const
{
   return(setValue(strUserName, PPP + '/' + USERNAME));
}

QString PppSettings::userName() const
{
   return(getStringValue(PPP + '/' + USERNAME));
}

bool PppSettings::setPassword(const QString& strPassword) const
{
   return(setSecret(strPassword, PPP + '/' + PASSWORD));
}

QString PppSettings::password() const
{
   return(getSecret(PPP + '/' + PASSWORD));
}

bool PppSettings::setRemoteName(const QString& strRemoteName) const
{
   return(setValue(strRemoteName, PPP + '/' + REMOTENAME));
}

QString PppSettings::remoteName() const
{
   return(getStringValue(PPP + '/' + REMOTENAME));
}

bool PppSettings::setNoBSDCompression(bool fSet) const
{
   return(setValue(fSet, PPP + '/' + NODSDCOMP));
}

bool PppSettings::noBSDCompression() const
{
   return(getBoolValue(PPP + '/' + NODSDCOMP));
}

bool PppSettings::setNoDeflate(bool fSet) const
{
   return(setValue(fSet, PPP + '/' + NODEFLATE));
}

bool PppSettings::noDeflate() const
{
   return(getBoolValue(PPP + '/' + NODEFLATE));
}

bool PppSettings::setNoVj(bool fSet) const
{
   return(setValue(fSet, PPP + '/' + NOVJ));
}

bool PppSettings::noVj() const
{
   return(getBoolValue(PPP + '/' + NOVJ));
}

bool PppSettings::setLcpEchoInterval(int iInterval) const
{
   return(setValue(iInterval, PPP + '/' + LCPECHOINTERVAL));
}

int PppSettings::lcpEchoInterval() const
{
   return(getIntValue(PPP + '/' + LCPECHOINTERVAL, -1));
}

/********** EAP ************/
bool PppEapSettings::setUseSmartCard(bool fUse) const
{
   return(setValue(fUse, EAP + '/' + USESMARTCARD));
}

bool PppEapSettings::useSmartCard() const
{
   return(getBoolValue(EAP + '/' + USESMARTCARD));
}

bool PppEapSettings::setCertificatePath(const QString& strCertificatePath) const
{
   return(setValue(strCertificatePath, EAP + '/' + CERTIFICATEPATH));
}

QString PppEapSettings::certificatePath() const
{
   return(getStringValue(EAP + '/' + CERTIFICATEPATH));
}

bool PppEapSettings::setPrivateKeyPath(const QString& strPrivateKeyPath) const
{
   return(setValue(strPrivateKeyPath, EAP + '/' + PRIVATEKEYPATH));
}

QString PppEapSettings::privateKeyPath() const
{
   return(getStringValue(EAP + '/' + PRIVATEKEYPATH));
}

bool PppEapSettings::setPrivateKeyPassword(const QString& strPrivateKeyPassword) const
{
   return(setSecret(strPrivateKeyPassword, EAP + '/' + PRIVATEKEYPASSWORD));
}

QString PppEapSettings::privateKeyPassword() const
{
   return(getSecret(EAP + '/' + PRIVATEKEYPASSWORD));
}

bool PppEapSettings::setCaCertificatePath(const QString& strCaCertificatePath) const
{
   return(setValue(strCaCertificatePath, EAP + '/' + CACERTIFICATEPATH));
}

QString PppEapSettings::caCertificatePath() const
{
   return(getStringValue(EAP + '/' + CACERTIFICATEPATH));
}

/*********** IP *************/
bool PppIpSettings::setUsePeerDns(bool fUse) const
{
   return(setValue(fUse, IP + '/' + USEPEERDNS));
}

bool PppIpSettings::usePeerDns() const
{
   return(getBoolValue(IP + '/' + USEPEERDNS));
}

bool PppIpSettings::setPreferredDnsServerAddress(const QString& strPreferredDnsServerAddress) const
{
   return(setValue(strPreferredDnsServerAddress, IP + '/' + PREFERREDDNSSERVERADDRESS));
}

QString PppIpSettings::preferredDnsServerAddress() const
{
   return(getStringValue(IP + '/' + PREFERREDDNSSERVERADDRESS));
}

bool PppIpSettings::setAlternateDnsServerAddress(const QString& strAlternateDnsServerAddress) const
{
   return(setValue(strAlternateDnsServerAddress, IP + '/' + ALTERNATEDNSSERVERADDRESS));
}

QString PppIpSettings::alternateDnsServerAddress() const
{
   return(getStringValue(IP + '/' + ALTERNATEDNSSERVERADDRESS));
}

bool PppIpSettings::setSearchDomains(const QString& strSearchDomains) const
{
   return(setValue(strSearchDomains, IP + '/' + SEARCHDOMAINS));
}

QString PppIpSettings::searchDomains() const
{
   return(getStringValue(IP + '/' + SEARCHDOMAINS));
}

bool PppIpSettings::setUseDefaultGateway(bool fUse) const
{
   return(setValue(fUse, IP + '/' + USEDEFAULTGATEWAY));
}

bool PppIpSettings::useDefaultGateway() const
{
   return(getBoolValue(IP + '/' + USEDEFAULTGATEWAY, true));
}

int PppIpSettings::routes() const
{
   int iSize(0);

   if (connectionNo() >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(connectionNo());
      qSettings()->beginGroup(IP);
      iSize = qSettings()->beginReadArray(ROUTES);
      qSettings()->endArray();
      qSettings()->endGroup();
      qSettings()->endArray();
   }

   return(iSize);
}

bool PppIpSettings::setRouteAddress(int iRow, const QString& strAddress) const
{
   return(setRouteProperty(strAddress, iRow, IPADDRESS));
}

QString PppIpSettings::routeAddress(int iRow) const
{
   return(routeProperty(iRow, IPADDRESS));
}

bool PppIpSettings::setRouteNetmask(int iRow, const QString& strNetMask) const
{
   return(setRouteProperty(strNetMask, iRow, IPNETMASK));
}

QString PppIpSettings::routeNetmask(int iRow) const
{
   return(routeProperty(iRow, IPNETMASK));
}

bool PppIpSettings::setRouteComment(int iRow, const QString& strComment) const
{
   return(setRouteProperty(strComment, iRow, COMMENT));
}

QString PppIpSettings::routeComment(int iRow) const
{
   return(routeProperty(iRow, COMMENT));
}

bool PppIpSettings::addRoute() const
{
   bool fAdded(false);

   if (connectionNo() >= 0)
   {
      const int iSize(routes());

      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(connectionNo());
      qSettings()->beginGroup(IP);

      qSettings()->beginWriteArray(ROUTES);
      qSettings()->setArrayIndex(iSize);
      qSettings()->setValue(IPADDRESS, "");
      qSettings()->setValue(IPNETMASK, "");
      qSettings()->endArray();

      qSettings()->endGroup();
      qSettings()->endArray();
      fAdded = true;
   }

   return(fAdded);
}

bool PppIpSettings::removeRoute(int iRow) const
{
   bool fRemoved(false);

   if (connectionNo() >= 0)
   {
      qSettings()->beginReadArray(CONNECTIONS);
      qSettings()->setArrayIndex(connectionNo());
      qSettings()->beginGroup(IP);

      fRemoved = ConnectionSettings::removeArrayItem(ROUTES, iRow);

      qSettings()->endGroup();
      qSettings()->endArray();
   }

   return(fRemoved);
}
