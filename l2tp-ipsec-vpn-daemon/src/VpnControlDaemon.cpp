/*
 * $Id: VpnControlDaemon.cpp 10 2010-09-17 09:13:01Z werner $
 *
 * File:   VpnControlDaemon.cpp
 * Author: Werner Jaeger
 *
 * Created on August 26, 2010, 5:35 AM
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
#include <QLocalServer>

#include <sys/stat.h>

#include "VpnClientConnection.h"
#include "VpnControlDaemon.h"

VpnControlDaemon::VpnControlDaemon(const QString& strKey, QObject* pParent) : QObject(pParent), m_strKey(strKey), m_pServer(new QLocalServer)
{
}

VpnControlDaemon::~VpnControlDaemon()
{
   delete m_pServer;
}

bool VpnControlDaemon::start()
{
   QLocalServer::removeServer(m_strKey);

   // makes sure, sockets are world read/writable
   const int iUMask(::umask(0));

   const bool fStarted(m_pServer->listen(m_strKey));
   if (fStarted)
      connect(m_pServer, SIGNAL(newConnection()), SLOT(incomingLocalConnection()));

   ::umask(iUMask);

   return(fStarted);
}

void VpnControlDaemon::incomingLocalConnection()
{
   if (m_pServer->hasPendingConnections())
      new VpnClientConnection(m_pServer->nextPendingConnection(), this);
}
