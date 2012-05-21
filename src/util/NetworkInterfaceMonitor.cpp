/*
 * $Id: NetworkInterfaceMonitor.cpp 144 2012-05-21 07:31:37Z wejaeger $
 *
 * File:   NetworkInterfaceMonitor.cpp
 * Author: Werner Jaeger
 *
 * Created on August 13, 2010, 8:01 AM
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

#include <arpa/inet.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <unistd.h>

#include "NetworkInterfaceMonitor.h"
#include "NetworkInterface.h"

NetworkInterfaceMonitor* NetworkInterfaceMonitor::m_pInstance = 0;

NetworkInterfaceMonitor::NetworkInterfaceMonitor() : m_iSocket(-1)
{
}

NetworkInterfaceMonitor::~NetworkInterfaceMonitor()
{
   if (m_pInstance)
      delete m_pInstance;
}

NetworkInterfaceMonitor* NetworkInterfaceMonitor::instance()
{
   if (!m_pInstance)
      m_pInstance = new NetworkInterfaceMonitor();

   return (m_pInstance);
}

void NetworkInterfaceMonitor::subscribe(const QObject* pSubscriber)
{
   if (pSubscriber && !m_Subscribers.contains(pSubscriber))
   {
      m_Subscribers.append(pSubscriber);
      connect(this, SIGNAL(routeAdded(NetworkInterface, unsigned int)), pSubscriber, SLOT(onRouteAdded(NetworkInterface, unsigned int)));
      connect(this, SIGNAL(routeDeleted(NetworkInterface, unsigned int)), pSubscriber, SLOT(onRouteDeleted(NetworkInterface, unsigned int)));
      connect(this, SIGNAL(ptpInterfaceIsUpAnRunning(NetworkInterface)), pSubscriber, SLOT(onPtpInterfaceIsUpAnRunning(NetworkInterface)));
      connect(this, SIGNAL(ptpInterfaceIsGoingDown(NetworkInterface)), pSubscriber, SLOT(onPtpInterfaceIsGoingDown(NetworkInterface)));
   }
}

void NetworkInterfaceMonitor::unSubscribe(const QObject* pSubscriber)
{
   if (pSubscriber)
   {
      if (m_Subscribers.removeOne(pSubscriber))
      {
         disconnect(this, SIGNAL(routeAdded(NetworkInterface, unsigned int)), pSubscriber, SLOT(onRouteAdded(NetworkInterface, unsigned int)));
         disconnect(this, SIGNAL(routeDeleted(NetworkInterface, unsigned int)), pSubscriber, SLOT(onRouteDeleted(NetworkInterface, unsigned int)));
         disconnect(this, SIGNAL(ptpInterfaceIsUpAnRunning(NetworkInterface)), pSubscriber, SLOT(onPtpInterfaceIsUpAnRunning(NetworkInterface)));
         disconnect(this, SIGNAL(ptpInterfaceIsGoingDown(NetworkInterface)), pSubscriber, SLOT(onPtpInterfaceIsGoingDown(NetworkInterface)));
      }
   }
}

void NetworkInterfaceMonitor::run()
{
//   qDebug() << "Starting NetworkInterfaceMonitor thread";

   m_iSocket = ::socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

   if (m_iSocket != -1)
   {
//      qDebug() << "Socket" << m_iSocket << "created.";

      struct sockaddr_nl addr;
      ::bzero(&addr, sizeof(addr));
      addr.nl_family = AF_NETLINK;
      addr.nl_pid = ::getpid();
      addr.nl_groups = RTMGRP_IPV4_ROUTE | RTMGRP_IPV6_ROUTE | RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR;

      if (::bind(m_iSocket, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr)) != -1)
      {
         m_Interfaces = NetworkInterface::pointToPointInterfaces();

         ssize_t iLen;
         char acBuffer[1024];

         while (m_iSocket != -1)
         {
            struct nlmsghdr* pNetLinkMessageHeader = reinterpret_cast<struct nlmsghdr*>(acBuffer);
            if ((iLen = ::recv(m_iSocket, pNetLinkMessageHeader, sizeof(acBuffer), 0)) > 0)
            {
               // outer loop: loops thru all the NETLINK headers
               for (bool fStop = false; !fStop && NLMSG_OK(pNetLinkMessageHeader, static_cast<__u32>(iLen)); pNetLinkMessageHeader = NLMSG_NEXT(pNetLinkMessageHeader, iLen))
               {
//                  qDebug() << "Netlink message received:" << "size =" << iLen << "type =" << pNetLinkMessageHeader->nlmsg_type;
                  switch (pNetLinkMessageHeader->nlmsg_type)
                  {
                     case NLMSG_DONE:
//                        qDebug() << "Netlink multipart message DONE";
                        fStop = true;
                        break;

                     case NLMSG_ERROR:
//                        qDebug() << "Netlink message ERROR";
                        fStop = true;
                        break;

                     default:
                        if (pNetLinkMessageHeader->nlmsg_type == RTM_NEWROUTE || pNetLinkMessageHeader->nlmsg_type == RTM_DELROUTE)
                           handleRoutingMessage(pNetLinkMessageHeader);
                        else if (pNetLinkMessageHeader->nlmsg_type == RTM_NEWLINK || pNetLinkMessageHeader->nlmsg_type == RTM_DELLINK)
                           handleInterfaceInfoMessage(pNetLinkMessageHeader);
                        else if (pNetLinkMessageHeader->nlmsg_type == RTM_NEWADDR || pNetLinkMessageHeader->nlmsg_type == RTM_DELADDR)
                           handleAddressMessage(pNetLinkMessageHeader);
                        break;
                  }
               }
//               qDebug() << "Netlink message DONE";
               pNetLinkMessageHeader = reinterpret_cast<struct nlmsghdr*>(acBuffer);
            }
//            else
//               qDebug() << "recv returned" << iLen;
         }
//         qDebug() << "Leaving receive loop";
      }
      else
         qCritical("Failed to bind netlink socket");
   }
   else
      qCritical("Failed to create a new netlink socket.");

//   qDebug() << "Leaving NetworkInterfaceMonitor thread";
}

void NetworkInterfaceMonitor::stop()
{
   if (m_iSocket != -1)
   {
//      qDebug() << "Stopping NetworkInterfaceMonitor thread";
      ::shutdown(m_iSocket, SHUT_RDWR);
      m_iSocket = -1;
      terminate();
      wait();
   }
}

void NetworkInterfaceMonitor::handleRoutingMessage(struct nlmsghdr* pNetLinkMessageHeader)
{
   // get route entry header
   struct rtmsg * const pRouteMessage = reinterpret_cast<struct rtmsg*>(NLMSG_DATA(pNetLinkMessageHeader));

//   qDebug() << "Routing message:" << "dst len =" << pRouteMessage->rtm_dst_len << "family =" << pRouteMessage->rtm_family << "flags =" << pRouteMessage->rtm_flags << "protocol =" << pRouteMessage->rtm_protocol << "scope =" << pRouteMessage->rtm_scope << "src len =" << pRouteMessage->rtm_src_len << "table =" << pRouteMessage->rtm_table << "tos =" << pRouteMessage->rtm_tos << "type =" << pRouteMessage->rtm_type;

   // we are only concerned about the main route table
   if (pRouteMessage->rtm_table == RT_TABLE_MAIN)
   {
      // fields to hold content of an entry of the route table
      char acInterfaceName[IFNAMSIZ], acDsts[INET6_ADDRSTRLEN], acGws[INET6_ADDRSTRLEN];
      uint32_t iPriority = 0;

      // init all the field
      ::bzero(acInterfaceName, sizeof (acInterfaceName));
      ::bzero(acDsts, sizeof(acDsts));
      ::bzero(acGws, sizeof(acGws));

      // inner loop: loop thru all the attributes of one route entry
      struct rtattr* pRoutingAttributes = RTM_RTA(pRouteMessage);
      int iPayloadLength = RTM_PAYLOAD(pNetLinkMessageHeader);
      while (iPayloadLength && RTA_OK(pRoutingAttributes, iPayloadLength))
      {
//         qDebug() << "Routing attribute: type =" << pRoutingAttributes->rta_type << "len =" << pRoutingAttributes->rta_len;

         switch (pRoutingAttributes->rta_type)
         {
            case RTA_DST: // destination IPv4 or IPv6 address
               ::inet_ntop(pRouteMessage->rtm_family, RTA_DATA(pRoutingAttributes), acDsts, INET6_ADDRSTRLEN);
               break;

            case RTA_GATEWAY: // next hop IPv4 or IPv6 address
               ::inet_ntop(pRouteMessage->rtm_family, RTA_DATA(pRoutingAttributes), acGws, INET6_ADDRSTRLEN);
               break;

            case RTA_PRIORITY: // metric
               iPriority = *reinterpret_cast<uint32_t*>(RTA_DATA(pRoutingAttributes));
               break;

            case RTA_OIF: // unique ID associated with the network interface
               ::if_indextoname(*reinterpret_cast<unsigned int*>(RTA_DATA(pRoutingAttributes)), acInterfaceName);
               break;

            default:
               break;
         }
         pRoutingAttributes = RTA_NEXT(pRoutingAttributes, iPayloadLength);
      }

      NetworkInterface::InterfaceMap::iterator itInterfaces = m_Interfaces.find(acInterfaceName);
      if (itInterfaces == m_Interfaces.end())
      {
         const NetworkInterface::InterfaceMapEntry entry(std::make_pair(acInterfaceName, NetworkInterface(acInterfaceName, ::if_nametoindex(acInterfaceName), IFF_UP | IFF_RUNNING)));
         itInterfaces = m_Interfaces.insert(entry).first;
      }

      QNetworkAddressEntry routeEntry;
      routeEntry.setIp(QHostAddress(acDsts));
      routeEntry.setPrefixLength(pRouteMessage->rtm_dst_len);
      routeEntry.setBroadcast(QHostAddress(acGws));

      (*itInterfaces).second.clearRouteEntries();
      (*itInterfaces).second.addRouteEntry(routeEntry);

      if (pNetLinkMessageHeader->nlmsg_type == RTM_NEWROUTE)
      {
//         qDebug() << "Route added:" << "IF =" << acInterfaceName << "DST =" << acDsts << "GW =" << acGws << "Priority =" << iPriority;
         emit routeAdded((*itInterfaces).second, iPriority);
      }
      else
      {
//         qDebug() << "Route deleted:" << "IF =" << acInterfaceName << "DST =" << acDsts << "GW =" << acGws << "Priority =" << iPriority;
         emit routeDeleted((*itInterfaces).second, iPriority);
      }
   }
}

void NetworkInterfaceMonitor::handleInterfaceInfoMessage(struct nlmsghdr* pNetLinkMessageHeader)
{
   // get interface info header
   struct ifinfomsg * const pInterfaceInfoMessage = reinterpret_cast<struct ifinfomsg*>(NLMSG_DATA(pNetLinkMessageHeader));

   // strings to hold content of an entry of the route table
   char acInterfaceName[IFNAMSIZ];

   // init all the strings
   ::bzero(acInterfaceName, sizeof (acInterfaceName));

   ::if_indextoname(pInterfaceInfoMessage->ifi_index, acInterfaceName);

//   qDebug() << "Interface info message:" << "name =" << acInterfaceName << "family =" << pInterfaceInfoMessage->ifi_family << "device type =" << pInterfaceInfoMessage->ifi_type << "interface index =" << pInterfaceInfoMessage->ifi_index << "device flags =" << pInterfaceInfoMessage->ifi_flags << "change mask =" << pInterfaceInfoMessage->ifi_change;
#ifndef QT_NO_DEBUG
//   debugFlags(pInterfaceInfoMessage->ifi_flags);
#endif

   // inner loop: loop thru all the attributes of one interface info entry
   struct rtattr* pInterfaceAttributes = IFLA_RTA(pInterfaceInfoMessage);
   int iPayloadLength = IFLA_PAYLOAD(pNetLinkMessageHeader);
   while (iPayloadLength && RTA_OK(pInterfaceAttributes, iPayloadLength))
   {
//      qDebug() << "Interface attribute: type =" << pInterfaceAttributes->rta_type << "len =" << pInterfaceAttributes->rta_len;

      const int iAddressLen = RTA_PAYLOAD(pInterfaceAttributes);
//      qDebug() << "Payload length =" << iAddressLen;

      switch (pInterfaceAttributes->rta_type)
      {
         case IFLA_ADDRESS: // MAC address
            break;

         case IFLA_BROADCAST: //2
            struct sockaddr_ll addr;
            ::bzero(&addr, sizeof(addr));
            ::memcpy(addr.sll_addr, RTA_DATA(pInterfaceAttributes), iAddressLen);
            addr.sll_family = AF_PACKET;
            addr.sll_ifindex = pInterfaceInfoMessage->ifi_family;
            addr.sll_halen = iAddressLen;
            addr.sll_hatype = pInterfaceInfoMessage->ifi_type;
            break;

         case IFLA_IFNAME:       //  3
            if (::strlen(acInterfaceName) == 0)
               ::strcpy(acInterfaceName, reinterpret_cast<const char*>(RTA_DATA(pInterfaceAttributes)));
            break;

         case IFLA_MTU:          //  4
         case IFLA_QDISC:        //  6
         case IFLA_STATS:        //  7
         case IFLA_PROTINFO:     // 12
         case IFLA_TXQLEN:       // 13
         case IFLA_MAP:          // 14
         case IFLA_OPERSTATE:    // 16
         case IFLA_LINKMODE:     // 17
            break;
      }
      pInterfaceAttributes = RTA_NEXT(pInterfaceAttributes, iPayloadLength);
   }

   if (pNetLinkMessageHeader->nlmsg_type == RTM_NEWLINK && (pInterfaceInfoMessage->ifi_flags & IFF_POINTOPOINT))
   {
      const NetworkInterface::InterfaceMap::iterator itInterfaces = m_Interfaces.find(acInterfaceName);
      if (itInterfaces != m_Interfaces.end())
      {
         const NetworkInterface::InterfaceFlags oldFlags((*itInterfaces).second.flags());

         (*itInterfaces).second.setFlags(pInterfaceInfoMessage->ifi_flags);

         if ((pInterfaceInfoMessage->ifi_flags & IFF_UP) && (pInterfaceInfoMessage->ifi_flags & IFF_RUNNING) && !(oldFlags.testFlag(NetworkInterface::IsUp) && oldFlags.testFlag(NetworkInterface::IsRunning)))
         {
//            qDebug() << "Interface" << acInterfaceName << "is up and running";
            emit ptpInterfaceIsUpAnRunning((*itInterfaces).second);
         }

         if (oldFlags.testFlag(NetworkInterface::IsUp) && oldFlags.testFlag(NetworkInterface::IsRunning) && !((pInterfaceInfoMessage->ifi_flags & IFF_UP) && (pInterfaceInfoMessage->ifi_flags & IFF_RUNNING)))
         {
//            qDebug() << "Interface" << acInterfaceName << "is going down";
            emit ptpInterfaceIsGoingDown((*itInterfaces).second);
         }
      }
      else
      {
//         qDebug() << "Interface" << acInterfaceName << "added";
         const NetworkInterface::InterfaceMapEntry entry(std::make_pair(acInterfaceName, NetworkInterface(acInterfaceName, pInterfaceInfoMessage->ifi_index, pInterfaceInfoMessage->ifi_flags)));
         m_Interfaces.insert(entry);
      }
   }
   else if (pNetLinkMessageHeader->nlmsg_type == RTM_DELLINK && pInterfaceInfoMessage->ifi_flags & IFF_POINTOPOINT)
   {
      const NetworkInterface::InterfaceMap::iterator itInterfaces = m_Interfaces.find(acInterfaceName);
      if (itInterfaces != m_Interfaces.end())
      {
//         qDebug() << "Interface" << acInterfaceName << "deleted";
         m_Interfaces.erase(itInterfaces);
      }
   }
}

void NetworkInterfaceMonitor::handleAddressMessage(struct nlmsghdr* pNetLinkMessageHeader)
{
   struct ifaddrmsg* const pInterfaceAddressMessage = reinterpret_cast<struct ifaddrmsg*>(NLMSG_DATA(pNetLinkMessageHeader));
//   qDebug() << "Address message: family =" << pInterfaceAddressMessage->ifa_family << "flags =" << pInterfaceAddressMessage->ifa_flags << "index =" << pInterfaceAddressMessage->ifa_index << "prefix len =" << pInterfaceAddressMessage->ifa_prefixlen << "scope =" << pInterfaceAddressMessage->ifa_scope;

   // strings to hold content of an entry of the route table
   char acInterfaceName[IFNAMSIZ], acIp[INET6_ADDRSTRLEN], acBroadcast[INET6_ADDRSTRLEN];

   // init all the strings
   ::bzero(acInterfaceName, sizeof (acInterfaceName));
   ::bzero(acIp, sizeof(acIp));
   ::bzero(acBroadcast, sizeof(acBroadcast));

   ::if_indextoname(pInterfaceAddressMessage->ifa_index, acInterfaceName);

   // inner loop: loop thru all the attributes of one address entry
   struct rtattr* pAddressAttributes = IFA_RTA(pInterfaceAddressMessage);
   int iPayloadLength = IFA_PAYLOAD(pNetLinkMessageHeader);
   while (iPayloadLength && RTA_OK(pAddressAttributes, iPayloadLength))
   {
//      qDebug() << "Address attribute: type =" << pAddressAttributes->rta_type << "len =" << pAddressAttributes->rta_len;

      switch (pAddressAttributes->rta_type)
      {
         case IFA_ADDRESS:       // 1
            ::inet_ntop(pInterfaceAddressMessage->ifa_family, RTA_DATA(pAddressAttributes), acBroadcast, INET6_ADDRSTRLEN);
            break;
         case IFA_LOCAL:         // 2
            ::inet_ntop(pInterfaceAddressMessage->ifa_family, RTA_DATA(pAddressAttributes), acIp, INET6_ADDRSTRLEN);
            break;
         case IFA_LABEL:         // 3
            break;
         case IFA_BROADCAST:     // 4
            break;
         case IFA_ANYCAST:       // 5
            break;
         case IFA_CACHEINFO:     // 6
            break;
         case IFA_MULTICAST:     // 7
            break;
      }
      pAddressAttributes = RTA_NEXT(pAddressAttributes, iPayloadLength);
   }

   NetworkInterface::InterfaceMap::iterator itInterfaces = m_Interfaces.find(acInterfaceName);
   if (itInterfaces == m_Interfaces.end())
   {
      const NetworkInterface::InterfaceMapEntry entry(std::make_pair(acInterfaceName, NetworkInterface(acInterfaceName, ::if_nametoindex(acInterfaceName), IFF_UP | IFF_RUNNING)));
      itInterfaces = m_Interfaces.insert(entry).first;
   }

   QNetworkAddressEntry addressEntry;
   addressEntry.setIp(QHostAddress(acIp));
   addressEntry.setPrefixLength(pInterfaceAddressMessage->ifa_prefixlen);
   addressEntry.setBroadcast(QHostAddress(acBroadcast));

   (*itInterfaces).second.clearAddressEntries();
   (*itInterfaces).second.addAddressEntry(addressEntry);

//   if (pNetLinkMessageHeader->nlmsg_type == RTM_NEWADDR)
//      qDebug() << "Address added:" << "IF =" << acInterfaceName << "IP =" << acIp << "Broadcast =" << acBroadcast;
//   else
//      qDebug() << "Address deleted:" << "IF =" << acInterfaceName << "IP =" << acIp << "Broad =" << acBroadcast;
}


#ifndef QT_NO_DEBUG
void NetworkInterfaceMonitor::debugFlags(unsigned iFlags)
{
   if (iFlags & IFF_UP)
      qDebug() << "Interface"  << "is Up";
   if (iFlags & IFF_BROADCAST)
      qDebug() << "Interface"  << "broadcast address is valid";
   if (iFlags & IFF_DEBUG)
      qDebug() << "Interface"  << "debug is turned on";
   if (iFlags & IFF_LOOPBACK)
      qDebug() << "Interface"  << "is loop back";
   if (iFlags & IFF_POINTOPOINT)
      qDebug() << "Interface"  << "is Ptp";
   if (iFlags & IFF_NOTRAILERS)
      qDebug() << "Interface"  << "avoid trailers";
   if (iFlags & IFF_RUNNING)
      qDebug() << "Interface"  << "is running";
   if (iFlags & IFF_NOARP)
      qDebug() << "Interface"  << "has no address resolution protocol";
   if (iFlags & IFF_PROMISC)
      qDebug() << "Interface"  << "is in promiscous mode";
   if (iFlags & IFF_ALLMULTI)
      qDebug() << "Interface"  << "receives all multicast packets";
   if (iFlags & IFF_MASTER)
      qDebug() << "Interface"  << "is master of a load balancer";
   if (iFlags & IFF_SLAVE)
      qDebug() << "Interface"  << "is slave of a load balancer";
   if (iFlags & IFF_MULTICAST)
      qDebug() << "Interface"  << "supports multicast";
   if (iFlags & IFF_PORTSEL)
      qDebug() << "Interface"  << "can set media type";
   if (iFlags & IFF_AUTOMEDIA)
      qDebug() << "Interface"  << "auto media select is active";
   if (iFlags & IFF_DYNAMIC)
      qDebug() << "Interface"  << "is a dialup device with changing addresses";
}
#endif
