/*
 * $Id: NetworkInterface.cpp 129 2012-04-07 10:15:46Z wejaeger $
 *
 * File:   NetworkInterface.cpp
 * Author: Werner Jaeger
 *
 * Created on July 12, 2010, 6:07 PM
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

//#include <QDebug>

#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sstream>
#include <fstream>

#include "util/VpnControlDaemonClient.h"

#include "NetworkInterface.h"

const char* const pcProcNetDevPath("/proc/net/dev");
const char* const pcDefaultGatewayInfoPath("/var/run/L2tpIPsecVpnControlDaemon/defaultgateway.info");
const NetworkInterface NetworkInterface::null(NetworkInterface("", 0, 0));

NetworkInterface::NetworkInterface(const NetworkInterface& orig) : m_strName(orig.m_strName), m_iIndex(orig.m_iIndex), m_Flags(orig.m_Flags), m_AddressEntries(orig.m_AddressEntries), m_RouteEntries(orig.m_RouteEntries)
{
}

bool NetworkInterface::operator==(const NetworkInterface& other) const
{
   return(m_strName.compare(other.m_strName) == 0);
}

bool NetworkInterface::hasDefaultGateway() const
{
   bool fRet = false;

   AddressEntries::const_iterator it(m_RouteEntries.begin());

   for (; !fRet && it != m_RouteEntries.end(); it++)
      fRet = (*it).ip().isNull();// && !(*it).broadcast().isNull();

   return(fRet);
}

bool NetworkInterface::isDefaultGateway() const
{
   return(NetworkInterface::defaultGatewayInfo().interfaceName().compare(m_strName) == 0);
}

bool NetworkInterface::removeAddressEntry(const QNetworkAddressEntry& addressEntry)
{
   bool fFound = false;
   AddressEntries::iterator it(m_AddressEntries.begin());
   while (!fFound && it != m_AddressEntries.end())
   {
      if ((*it++) == addressEntry)
      {
         fFound = true;
         it = m_AddressEntries.erase(it);
      }
   }
   return(fFound);
}

bool NetworkInterface::removeRouteEntry(const QNetworkAddressEntry& routeEntry)
{
   bool fFound = false;
   AddressEntries::iterator it(m_RouteEntries.begin());
   while (!fFound && it != m_RouteEntries.end())
   {
      if ((*it++) == routeEntry)
      {
         fFound = true;
         it = m_RouteEntries.erase(it);
      }
   }
   return(fFound);
}

NetworkInterface::InterfaceMap NetworkInterface::pointToPointInterfaces(void)
{
   InterfaceMap interfaces;

   struct ifaddrs* pInterfaceAddresses;

   if (::getifaddrs(&pInterfaceAddresses) == 0)
   {
      for (const struct ifaddrs* pIter = pInterfaceAddresses; pIter != NULL; pIter = pIter->ifa_next)
      {
         if (pIter->ifa_addr && (pIter->ifa_addr->sa_family == AF_INET || pIter->ifa_addr->sa_family == AF_INET6) && pIter->ifa_flags & IFF_POINTOPOINT && pIter->ifa_flags & IFF_RUNNING)
         {
            const InterfaceMapEntry entry(std::make_pair(pIter->ifa_name, NetworkInterface(pIter->ifa_name, ::if_nametoindex(pIter->ifa_name), pIter->ifa_flags)));
            std::pair<InterfaceMap::iterator, bool> ret = interfaces.insert(entry);

            QNetworkAddressEntry addressEntry;
            addressEntry.setIp(QHostAddress(pIter->ifa_addr));

            if (pIter->ifa_netmask != NULL)
               addressEntry.setNetmask(QHostAddress(pIter->ifa_netmask));

            if (pIter->ifa_dstaddr)
               addressEntry.setBroadcast(QHostAddress(pIter->ifa_dstaddr));

            (*ret.first).second.addAddressEntry(addressEntry);
         }
      }
      ::freeifaddrs(pInterfaceAddresses);
   }
   return(interfaces);
}

NetworkInterface::InterfaceMap NetworkInterface::defaultGateway(void)
{
   InterfaceMap interfaces;

   using namespace std;

   string strInterfaceName;
   uint32 iDestinationAddress = -1;
   uint32 iGatewayAddress = -1;

   ifstream route("/proc/net/route", ios::in);
   while (iDestinationAddress && route)
   {
      string strLine;
      getline(route, strLine);

//      qDebug() << "NetworkInterface::defaultGateway: route entry:" << strLine.c_str();

      istringstream strFormat(strLine);
      strFormat >> strInterfaceName >> hex >> iDestinationAddress >> hex >> iGatewayAddress ;
      if (!strFormat.good() || iGatewayAddress == 0)
         iDestinationAddress = -1;
   }

   if (iDestinationAddress == 0 && !strInterfaceName.empty())
   {
//      qDebug() << "NetworkInterface::defaultGateway: found default gateway on interface" << strInterfaceName.c_str() << "dest Addr =" << iDestinationAddress << "gateway =" << iGatewayAddress;

      const InterfaceMapEntry entry(std::make_pair(strInterfaceName, NetworkInterface(strInterfaceName.c_str(), ::if_nametoindex(strInterfaceName.c_str()), IFF_UP | IFF_RUNNING)));
      std::pair<InterfaceMap::iterator, bool> ret = interfaces.insert(entry);

      QNetworkAddressEntry routeEntry;
      routeEntry.setIp(QHostAddress(be32toh(iDestinationAddress)));
      routeEntry.setNetmask(QHostAddress());
      routeEntry.setBroadcast(QHostAddress(be32toh(iGatewayAddress)));

      (*ret.first).second.addRouteEntry(routeEntry);
   }

   return(interfaces);
}

QStringList NetworkInterface::dns(void)
{
   using namespace std;

   QStringList list;

   ifstream resolv("/etc/resolv.conf", ios::in);
   while (resolv)
   {
      string strLine;
      getline(resolv, strLine);

      if (strLine.length() > 0)
      {
         istringstream strFormat(strLine);

         string strKey;
         string strValue;
         strFormat >> strKey >> strValue;

         if (strKey == "nameserver")
            list.append(strValue.c_str());
      }
   }

   return(list);
}

NetworkInterface::Statistic NetworkInterface::statistic(const std::string& strInterfaceName)
{
   using namespace std;

   Statistic::Values receivedValues;
   Statistic::Values transmittedValues;

   ifstream statStream(pcProcNetDevPath, ios::in);
   string strLine;

   // read first header line
   if (statStream)
      getline(statStream, strLine);

   // read second header line
   if (statStream)
   {
      getline(statStream, strLine);

      string::size_type firstPipe(strLine.find('|') + 1);
      string::size_type secondPipe(strLine.rfind('|'));

      // there must be two pipe characters separating received part from transmitted part
      if (firstPipe != string::npos && secondPipe != string::npos)
      {
         Statistic::Headers receivedHeaders;

         string strReceivedHeaders(strLine.substr(firstPipe, secondPipe -firstPipe));
         istringstream formatReceived(strReceivedHeaders);

         while (formatReceived)
         {
            string strText;
            formatReceived >> strText;

            if (!strText.empty())
               receivedHeaders.push_back(strText);
         }

         Statistic::Headers transmittedHeaders;

         string strTransmittedHeaders(strLine.substr(secondPipe + 1));
         istringstream formatTransmitted(strTransmittedHeaders);

         while (formatTransmitted)
         {
            string strText;
            formatTransmitted >> strText;
            if (!strText.empty())
               transmittedHeaders.push_back(strText);
         }

         bool fDone(false);
         while (statStream && !fDone)
         {
            getline(statStream, strLine);

            string::size_type colonFound(strLine.find(':'));

            // there must be a colon as separator for the interface name
            if (colonFound != string::npos)
            {
               istringstream format(strLine.replace(colonFound, 1, " "));

               string strName;
               format >> strName;

               if (strName == strInterfaceName)
               {
                  long long lVal;

                  for (Statistic::Headers::size_type i = 0; i < receivedHeaders.size() && format; i++)
                  {
                     format >> lVal;
                     receivedValues.insert(std::make_pair(receivedHeaders.at(i), lVal));
                  }

                  for (Statistic::Headers::size_type i = 0; i < transmittedHeaders.size() && format; i++)
                  {
                     format >> lVal;
                     transmittedValues.insert(std::make_pair(transmittedHeaders.at(i), lVal));
                  }

                  fDone = true;
               }
            }
         }
      }
   }

   return(Statistic(receivedValues, transmittedValues));
}

NetworkInterface::DefaultGatewayInfo NetworkInterface::defaultGatewayInfo()
{
   using namespace std;

   string strInterfaceName;
   string strGateway;
   string strIPAddress;

   ifstream defaultGatewayInfo(pcDefaultGatewayInfoPath, ios::in);
   while (defaultGatewayInfo)
   {
      string strLine;
      getline(defaultGatewayInfo, strLine);

      if (strLine.length() > 0)
      {
         istringstream strFormat(strLine.replace(strLine.find('='), 1, " "));

         string strKey;
         string strValue;
         strFormat >> strKey >> strValue;

         if (strKey == "defaultroutephys")
            strInterfaceName = strValue;
         else if (strKey == "defaultrouteaddr")
            strIPAddress = strValue;
         else if (strKey == "defaultroutenexthop")
            strGateway = strValue;
      }
   }

   return(DefaultGatewayInfo(strInterfaceName, strGateway, strIPAddress));
}

bool NetworkInterface::writeDefaultGatewayInfo()
{
   bool fRet(false);

   const InterfaceMap defInterfaces(defaultGateway());

   if (defInterfaces.size() > 0)
   {
      const NetworkInterface nif((*defInterfaces.begin()).second);

      if (nif.routeEntries().size() > 0)
      {
         using namespace std;

         const QNetworkAddressEntry ae(nif.routeEntries()[0]);

         stringstream strDefaultGatewayInfo;

         strDefaultGatewayInfo << "defaultroutephys=" << nif.m_strName << '\3';
         strDefaultGatewayInfo << "defaultroutevirt=none" << '\3';
         strDefaultGatewayInfo << "defaultrouteaddr=" << ipAddress(nif.m_strName) << '\3';
         strDefaultGatewayInfo << "defaultroutenexthop=" << ae.broadcast().toString().toStdString() << '\3';
         if (!strDefaultGatewayInfo.fail())
         {
            int iRet(VpnControlDaemonClient::execute(VpnClientConnection::CMD_WRITE_DEFAULT_GATEWAY_INFO, QString::fromStdString(strDefaultGatewayInfo.str())));
            fRet = (iRet == 0);
         }
      }
   }

   return(fRet);
}

NetworkInterface::InterfaceFlags NetworkInterface::convertFlags(uint iRawFlags)
{
   InterfaceFlags flags = InterfaceFlag(0);
   flags |= (iRawFlags & IFF_UP) ? IsUp : InterfaceFlag(0);
   flags |= (iRawFlags & IFF_RUNNING) ? IsRunning : InterfaceFlag(0);
   flags |= (iRawFlags & IFF_BROADCAST) ? CanBroadcast : InterfaceFlag(0);
   flags |= (iRawFlags & IFF_LOOPBACK) ? IsLoopBack : InterfaceFlag(0);
   flags |= (iRawFlags & IFF_POINTOPOINT) ? IsPointToPoint : InterfaceFlag(0);
   flags |= (iRawFlags & IFF_MULTICAST) ? CanMulticast : InterfaceFlag(0);
   return(flags);
}

std::string NetworkInterface::ipAddress(const std::string& strInterfaceName)
{
   std::string strIpAddress;

   struct ifaddrs* pInterfaceAddresses;

   if (::getifaddrs(&pInterfaceAddresses) == 0)
   {
      for (const struct ifaddrs* pIter = pInterfaceAddresses; pIter != NULL && strIpAddress.empty(); pIter = pIter->ifa_next)
      {
         if (pIter->ifa_addr && (pIter->ifa_addr->sa_family == AF_INET || pIter->ifa_addr->sa_family == AF_INET6))
         {
            if (strInterfaceName.compare(pIter->ifa_name) == 0)
               strIpAddress = QHostAddress(pIter->ifa_addr).toString().toStdString();
         }
      }
      ::freeifaddrs(pInterfaceAddresses);
   }
   return(strIpAddress);
}
