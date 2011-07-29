/*
 * $Id: VpnControlDaemonClient.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   VpnControlDaemonClient.cpp
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
#include <QLocalSocket>
#include <QStringList>

#include "VpnControlDaemonClient.h"
#include "VPNControlTask.h"

static const char* const KEY = "L2tpIPsecVpnControlDaemon";

VpnControlDaemonClient::VpnControlDaemonClient(QObject* pParent) : QObject(pParent), m_pStream(new QTextStream), m_pSocket(new QLocalSocket)
{
   m_pStream->setDevice(m_pSocket);
   connect(m_pSocket, SIGNAL(connected()), SLOT(onConnected()));
   connect(m_pSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), SLOT(onDisconnected()));
   connect(m_pSocket, SIGNAL(disconnected()), SLOT(onDisconnected()));
   connect(m_pSocket, SIGNAL(readyRead()), SLOT(onReadyRead()));
}

VpnControlDaemonClient::VpnControlDaemonClient(bool /* fSynchronous */) : QObject(NULL), m_pStream(new QTextStream), m_pSocket(new QLocalSocket)
{
   m_pStream->setDevice(m_pSocket);
   connect(m_pSocket, SIGNAL(connected()), SLOT(onConnected()));
   connect(m_pSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), SLOT(onDisconnected()));
   connect(m_pSocket, SIGNAL(disconnected()), SLOT(onDisconnected()));
}

VpnControlDaemonClient::~VpnControlDaemonClient()
{
   delete m_pSocket;
   delete m_pStream;
}

void VpnControlDaemonClient::connectToServer()
{
   m_pSocket->abort();
   m_pSocket->connectToServer(KEY);
}

bool VpnControlDaemonClient::waitForConnected(int iMiliSeconds)
{
   return(m_pSocket->waitForConnected(iMiliSeconds));
}

bool VpnControlDaemonClient::start(VpnClientConnection::Command iCommand, const QString& strArguments)
{
   bool fRet(false);

   if (m_pSocket->state() == QLocalSocket::ConnectedState)
   {
      if (strArguments.isNull())
         m_pSocket->write((QString::number(iCommand) + '\n').toAscii().constData());
      else
         m_pSocket->write((QString::number(iCommand) + " " + strArguments + '\n').toAscii().constData());

      fRet = true;
   }

   return(fRet);
}

int VpnControlDaemonClient::execute(VpnClientConnection::Command iCommand, const QString& strArguments)
{
   int iRet(1);

   VpnControlDaemonClient client(true);

   client.connectToServer();

   if (client.waitForConnected())
   {
      if (client.start(iCommand, strArguments))
         iRet = client.waitForResult();
   }

   return(iRet);
}

void VpnControlDaemonClient::exit()
{
   if (start(VpnClientConnection::CMD_QUIT))
   {
      m_pSocket->waitForBytesWritten();
      m_pSocket->disconnectFromServer();
   }
}

void VpnControlDaemonClient::leave()
{
  m_pSocket->disconnectFromServer();
}

void VpnControlDaemonClient::onConnected()
{
   emit notifyConnected();
}

void VpnControlDaemonClient::onDisconnected()
{
   emit notifyDisconnected();
}

void VpnControlDaemonClient::onReadyRead()
{
   readResponse();
}

int VpnControlDaemonClient::waitForResult()
{
   int iRet(500);

   while (m_pSocket->waitForReadyRead())
   {
      const Result result = readResponse();
      if (result.type == VpnClientConnection::RESULT)
      {
         iRet = result.iReturnCode;
         break;
      }
   }

   return(iRet);
}

VpnControlDaemonClient::Result VpnControlDaemonClient::readResponse()
{
   Result result;
   result.type = VpnClientConnection::UNKNOWN;

   if (m_pSocket->canReadLine())
   {
      QString strResponseLine;
      while ((strResponseLine = m_pStream->readLine()).length() > 0)
      {
         const QStringList strResponseParts(strResponseLine.split(' ', QString::SkipEmptyParts));
         const int iParts(strResponseParts.count());
         if (iParts > 1)
         {
            bool fIsResponseType;
            const unsigned int iResponseType = strResponseParts[0].toUInt(&fIsResponseType);
            Q_ASSERT(fIsResponseType);

            if (fIsResponseType)
            {
               switch (iResponseType)
               {
                  case VpnClientConnection::RESULT:
                  {
                     bool fIsReturnCode;
                     const int iReturnCode(strResponseParts[1].toUInt(&fIsReturnCode));
                     Q_ASSERT(fIsReturnCode);
                     Q_ASSERT(iParts > 2);
                     if (fIsReturnCode)
                     {
                        const QString strCommand(strResponseLine.mid(strResponseLine.indexOf(strResponseParts[2])));
                        emit notifyResult(iReturnCode, strCommand);
                        result.iReturnCode = iReturnCode;
                        result.type = VpnClientConnection::RESULT;
                     }
                  }
                  break;

                  case VpnClientConnection::OUTPUT:
                     emit notifyCommandOutput(strResponseLine.mid(strResponseLine.indexOf(' ') + 1));
                     result.iReturnCode = 0;
                     result.type = VpnClientConnection::OUTPUT;
                     break;

                  case VpnClientConnection::INFORMATION:
                  {
                     bool fIsInformation;
                     const int iInformation(strResponseParts[1].toUInt(&fIsInformation));
                     Q_ASSERT(fIsInformation);
                     if (fIsInformation && iInformation == VpnClientConnection::CLOSED)
                         m_pSocket->disconnectFromServer();

                     result.iReturnCode = VpnClientConnection::CLOSED;
                     result.type = VpnClientConnection::INFORMATION;
                  }
                  break;

                  default:
                     // either server changed protocol and we missed this or a malicious software sends us messages
                     Q_ASSERT(false);
               }
            }
         }
      }
   }

   return(result);
}