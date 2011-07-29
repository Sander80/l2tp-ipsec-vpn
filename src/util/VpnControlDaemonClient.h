/*
 * $Id: VpnControlDaemonClient.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   VpnControlDaemonClient.h
 * Author: Werner Jaeger
 *
 * Created on August 26, 2010, 12:48 PM
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

#ifndef VPNCONTROLDAEMONCLIENT_H
#define	VPNCONTROLDAEMONCLIENT_H

#include <QPointer>

#include "VpnClientConnection.h"

class QTextStream;
class QLocalSocket;

class VpnControlDaemonClient : public QObject
{
   Q_OBJECT

public:
   explicit VpnControlDaemonClient(QObject* pParent = NULL);
   virtual ~VpnControlDaemonClient();

   void connectToServer();
   bool waitForConnected(int iMiliSeconds = 30000);
   bool start(VpnClientConnection::Command iCommand, const QString& strArguments = QString::null);
   static int execute(VpnClientConnection::Command iCommand, const QString& strArguments = QString::null);

signals:
   void notifyConnected();
   void notifyDisconnected();
   void notifyResult(int iReturnCode, const QString& strCommand);
   void notifyCommandOutput(const QString& strOutputLine);

public slots:
   void exit();
   void leave();

private slots:
   void onConnected();
   void onDisconnected();
   void onReadyRead();

private:
   explicit VpnControlDaemonClient(bool fSynchronous);
   VpnControlDaemonClient(const VpnControlDaemonClient& orig);
   VpnControlDaemonClient& operator=(const VpnControlDaemonClient& orig);

   int waitForResult();

   struct Result
   {
      int iReturnCode;
      VpnClientConnection::ResponseType type;
   };

   Result readResponse();

   QTextStream* const m_pStream;
   QPointer<QLocalSocket> const m_pSocket;
};

#endif	/* VPNCONTROLDAEMONCLIENT_H */

