/*
 * $Id: NetworkInterface.h 129 2012-04-07 10:15:46Z wejaeger $
 *
 * File:   NetworkInterface.h
 * Author: Werner Jaeger
 *
 * Created on July 12, 2010, 9:10 PM
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

#ifndef NETWORKINTERFACE_H
#define	NETWORKINTERFACE_H

#include <QObject>
#include <QNetworkAddressEntry>
#include <QStringList>

#include <map>
#include <vector>
#include <string>

class NetworkInterface
{
public:

   class Statistic
   {
   private:
      typedef std::vector<std::string> Headers;
      typedef std::map<std::string, long long> Values;

   public:

      class ReceivedData
      {
      public:
         long long bytes() const { return(m_ReceivedValues.count("bytes") ? m_ReceivedValues.at("bytes") : 0); }
         long long packets() const { return(m_ReceivedValues.count("packets") ? m_ReceivedValues.at("packets") : 0); }
         long long errs() const { return(m_ReceivedValues.count("errs") ? m_ReceivedValues.at("errs") : 0); }
         long long drop() const { return(m_ReceivedValues.count("drop") ? m_ReceivedValues.at("drop") : 0); }
         long long fifo() const { return(m_ReceivedValues.count("fifo") ? m_ReceivedValues.at("fifo") : 0); }
         long long frame() const { return(m_ReceivedValues.count("frame") ? m_ReceivedValues.at("frame") : 0); }
         long long compressed() const { return(m_ReceivedValues.count("compressed") ? m_ReceivedValues.at("compressed") : 0); }
         long long multicast() const { return(m_ReceivedValues.count("multicast") ? m_ReceivedValues.at("multicast") : 0); }

      private:
         ReceivedData(const Values& receivedValues) : m_ReceivedValues(receivedValues) {}
         ReceivedData(const ReceivedData& orig);
         ReceivedData& operator=(const ReceivedData& orig);

         const Values m_ReceivedValues;

         friend class Statistic;
      };

      class TransmittedData
      {
      public:
         long long bytes() const { return(m_TransmittedValues.count("bytes") ? m_TransmittedValues.at("bytes") : 0); }
         long long packets() const { return(m_TransmittedValues.count("packets") ? m_TransmittedValues.at("packets") : 0); }
         long long errs() const { return(m_TransmittedValues.count("errs") ? m_TransmittedValues.at("errs") : 0); }
         long long drop() const { return(m_TransmittedValues.count("drop") ? m_TransmittedValues.at("drop") : 0); }
         long long fifo() const { return(m_TransmittedValues.count("fifo") ? m_TransmittedValues.at("fifo") : 0); }
         long long colls() const { return(m_TransmittedValues.count("colls") ? m_TransmittedValues.at("colls") : 0); }
         long long carrier() const { return(m_TransmittedValues.count("carrier") ? m_TransmittedValues.at("carrier") : 0); }
         long long compressed() const { return(m_TransmittedValues.count("compressed") ? m_TransmittedValues.at("compressed") : 0); }

      private:
         TransmittedData(const Values& transmittedValues) : m_TransmittedValues(transmittedValues) {}
         TransmittedData(const TransmittedData& orig);
         TransmittedData& operator=(const TransmittedData& orig);

         const Values m_TransmittedValues;

         friend class Statistic;
      };

      const ReceivedData& received() const { return(m_ReceivedData); }
      const TransmittedData& transmitted() const  { return(m_TransmittedData); }

   private:
      Statistic(const Values& receivedValues, const Values& transmittedValues) : m_ReceivedData(receivedValues), m_TransmittedData(transmittedValues) {}
      Statistic& operator=(const Statistic& orig);

      const ReceivedData m_ReceivedData;
      const TransmittedData m_TransmittedData;

      friend class NetworkInterface;
   };

   class DefaultGatewayInfo
   {
   public:
      DefaultGatewayInfo(const std::string& strInterfaceName, const std::string& strGateway, const std::string& strIPAddress) : m_strInterfaceName(strInterfaceName), m_strGateway(strGateway), m_strIPAddress(strIPAddress) {}

      const std::string& interfaceName() const { return(m_strInterfaceName); }
      const std::string& gateway() const { return(m_strGateway); }
      const std::string& ipAddress() const { return(m_strIPAddress); }

   private:
      const std::string m_strInterfaceName;
      const std::string m_strGateway;
      const std::string m_strIPAddress;
   };

   typedef std::map<std::string, NetworkInterface> InterfaceMap;
   typedef std::pair<std::string, NetworkInterface> InterfaceMapEntry;
   typedef std::vector<QNetworkAddressEntry> AddressEntries;
   typedef std::vector<QNetworkAddressEntry> RouteEntries;
   typedef unsigned long uint32;

   enum InterfaceFlag
   {
     IsUp = 0x1,
     IsRunning = 0x2,
     CanBroadcast = 0x4,
     IsLoopBack = 0x8,
     IsPointToPoint = 0x10,
     CanMulticast = 0x20
   };
   Q_DECLARE_FLAGS(InterfaceFlags, InterfaceFlag)

   NetworkInterface() : m_strName(""), m_iIndex(0), m_Flags(0), m_AddressEntries(std::vector<QNetworkAddressEntry>()), m_RouteEntries(std::vector<QNetworkAddressEntry>()) {}
   NetworkInterface(const NetworkInterface& orig);
   bool operator==(const NetworkInterface& other) const;

   virtual ~NetworkInterface() {}

   const std::string& name() const { return(m_strName); }
   unsigned int index() const { return(m_iIndex); }
   InterfaceFlags flags() const { return(m_Flags); }
   bool isNull() const { return(m_strName.empty()); }
   bool isPtP() const { return(m_Flags & IsPointToPoint); }
   bool hasDefaultGateway() const;
   bool isDefaultGateway() const;

   const AddressEntries& addressEntries() const { return(m_AddressEntries); }
   void clearAddressEntries(void) { m_AddressEntries.clear(); }
   const AddressEntries& routeEntries() const { return(m_RouteEntries); }
   void clearRouteEntries(void) { m_RouteEntries.clear(); }

   static InterfaceMap pointToPointInterfaces(void);
   static InterfaceMap defaultGateway(void);
   static QStringList dns(void);
   static Statistic statistic(const std::string& strInterfaceName);
   static DefaultGatewayInfo defaultGatewayInfo();
   static bool writeDefaultGatewayInfo();

   static const NetworkInterface null;

private:
   NetworkInterface(const char* const cstrName, int iIndex, uint iRawFlags) : m_strName(cstrName), m_iIndex(iIndex), m_Flags(convertFlags(iRawFlags)), m_AddressEntries(std::vector<QNetworkAddressEntry>()), m_RouteEntries(std::vector<QNetworkAddressEntry>()) {}
   NetworkInterface& operator=(const NetworkInterface& orig);

   void addAddressEntry(const QNetworkAddressEntry& addressEntry) { m_AddressEntries.push_back(addressEntry); }
   bool removeAddressEntry(const QNetworkAddressEntry& addressEntry);
   void addRouteEntry(const QNetworkAddressEntry& routeEntry) { m_RouteEntries.push_back(routeEntry); }
   bool removeRouteEntry(const QNetworkAddressEntry& routeEntry);

   void setFlags(uint iRawFlags) { m_Flags = convertFlags(iRawFlags); }

   static InterfaceFlags convertFlags(uint iRawFlags);
   static std::string ipAddress(const std::string& strInterfaceName);

   const std::string m_strName;
   const unsigned int m_iIndex;
   InterfaceFlags m_Flags;

   std::vector<QNetworkAddressEntry> m_AddressEntries;
   std::vector<QNetworkAddressEntry> m_RouteEntries;

   friend class NetworkInterfaceMonitor;
};

#endif	/* NETWORKINTERFACE_H */

