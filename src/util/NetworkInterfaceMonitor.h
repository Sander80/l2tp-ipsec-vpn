/*
 * $Id: NetworkInterfaceMonitor.h 163 2017-12-29 10:44:44Z wejaeger $
 *
 * File:   NetworkInterfaceMonitor.h
 * Author: Werner Jaeger
 *
 * Created on August 13, 2010, 8:01 AM
 *
 * Copyright 2010 Werner Jaeger.
 *
 * Upgraded and maintained since 2020 by Alexander Smirnov.
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

#ifndef NETWORKINTERFACEMONITOR_H
#define	NETWORKINTERFACEMONITOR_H

#include <QThread>
#include <QList>

#include "NetworkInterface.h"

class NetworkInterfaceMonitor : public QThread
{
   Q_OBJECT

public:
   virtual ~NetworkInterfaceMonitor();

   void run();
   void stop();
   void subscribe(const QObject* pSubscriber);
   void unSubscribe(const QObject* pSubscriber);

   static NetworkInterfaceMonitor* instance();

protected:
   NetworkInterfaceMonitor();

signals:
   void routeAdded(NetworkInterface interface, unsigned int iPriority) const;
   void routeDeleted(NetworkInterface interface, unsigned int iPriority) const;
   void addressAdded(NetworkInterface interface) const;
   void ptpInterfaceIsDeleted(NetworkInterface interface) const;

private:
   NetworkInterfaceMonitor(const NetworkInterfaceMonitor& orig);
   NetworkInterfaceMonitor& operator=(const NetworkInterfaceMonitor& orig);

   void handleRoutingMessage(struct nlmsghdr* pNetLinkMessageHeader);
   void handleInterfaceInfoMessage(struct nlmsghdr* pNetLinkMessageHeader);
   void handleAddressMessage(struct nlmsghdr* pNetLinkMessageHeader);
   static int getInterfaceFlagByIndex(const int iIndex);


#ifndef QT_NO_DEBUG
   static void debugFlags(unsigned iFlags);
#endif

   QList<const QObject*> m_Subscribers;
   int m_iSocket;

   NetworkInterface::InterfaceMap m_Interfaces;

   static NetworkInterfaceMonitor* m_pInstance;
};

#endif	/* NETWORKINTERFACEMONITOR_H */

