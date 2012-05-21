/*
 * $Id: LocalPeer.cpp 146 2012-05-28 11:37:01Z wejaeger $
 *
 * File:   LocalPeer.cpp
 * Author:  Werner Jaeger
 *
 * Created on September 2, 2010, 5:47 PM
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

#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDir>

#include "LocalPeer.h"

static const char* const APPNAME("L2tpIPsecVpn");

const char* LocalPeer::m_pcAck = "ack";

LocalPeer::LocalPeer(QObject* pParent, const QString& strAppId) : QObject(pParent), m_strApplicationId(strAppId), m_pServer(new QLocalServer())
{
   QString strPrefix(m_strApplicationId);
   if (m_strApplicationId.isEmpty())
   {
      m_strApplicationId = QCoreApplication::applicationFilePath();
      strPrefix = m_strApplicationId.section(QLatin1Char('/'), -1);
   }

   strPrefix.remove(QRegExp("[^a-zA-Z]"));
   strPrefix.truncate(6);

   QByteArray abApplicationId(m_strApplicationId.toUtf8());
   quint16 iNum = qChecksum(abApplicationId.constData(), abApplicationId.size());
   m_strSocketName = QLatin1String(APPNAME) + "-" + strPrefix + QLatin1Char('-') + QString::number(iNum, 16) + QLatin1Char('-') + hexUid();

   QString strLockName(QDir(QDir::tempPath()).absolutePath() + QLatin1Char('/') + m_strSocketName + QLatin1String("-lockfile"));
   m_LockedFile.setFileName(strLockName);
   m_LockedFile.open(QIODevice::ReadWrite);
}

LocalPeer::~LocalPeer()
{
   delete m_pServer;
}

bool LocalPeer::isClient()
{
   bool fRet(false);

   if (!m_LockedFile.isLocked())
   {
      if (m_LockedFile.lock(LockedFile::WriteLock, false))
      {
         bool fIsListening(m_pServer->listen(m_strSocketName));

         // ### Workaround
         if (!fIsListening && m_pServer->serverError() == QAbstractSocket::AddressInUseError)
         {
            QFile::remove(QDir::cleanPath(QDir::tempPath())+QLatin1Char('/') + m_strSocketName);
            fIsListening = m_pServer->listen(m_strSocketName);
         }

         if (!fIsListening)
            qWarning() << APPNAME << ": listen on local socket failed; " << qPrintable(m_pServer->errorString());

         QObject::connect(m_pServer, SIGNAL(newConnection()), SLOT(receiveConnection()));
      }
      else
         fRet = true;
   }

   return(fRet);
}

QString LocalPeer::applicationId() const
{
   return (m_strApplicationId);
}

bool LocalPeer::sendMessage(const QString& strMessage, int iTimeout)
{
   bool fRet(false);

   if (isClient())
   {
      QLocalSocket socket;

      for (int i = 0; i < 2; i++)
      {
         // Try twice, in case the other instance is just starting up
         socket.connectToServer(m_strSocketName);
         fRet = socket.waitForConnected(iTimeout / 2);
         if (fRet || i)
            break;

         const int iMiliSeconds = 250;
         const struct timespec ts = { iMiliSeconds / 1000, (iMiliSeconds % 1000) * 1000 * 1000 };
         nanosleep(&ts, NULL);
      }

      if (fRet)
      {
         QByteArray abMsg(strMessage.toUtf8());
         QDataStream ds(&socket);
         ds.writeBytes(abMsg.constData(), abMsg.size());
         fRet = socket.waitForBytesWritten(iTimeout);
         fRet &= socket.waitForReadyRead(iTimeout);   // wait for ack
         fRet &= (socket.read(qstrlen(m_pcAck)) == m_pcAck);
      }
   }

   return(fRet);
}

void LocalPeer::receiveConnection()
{
   QLocalSocket* const pSocket = m_pServer->nextPendingConnection();

   if (pSocket)
   {
      while (pSocket->bytesAvailable() < static_cast<int>(sizeof(quint32)))
        pSocket->waitForReadyRead();

      QDataStream ds(pSocket);
      QByteArray abMsg;
      quint32 iRemaining;
      ds >> iRemaining;
      abMsg.resize(iRemaining);
      int iGot(0);
      char* pcMsgBuf = abMsg.data();

      do
      {
         iGot = ds.readRawData(pcMsgBuf, iRemaining);
         iRemaining -= iGot;
         pcMsgBuf += iGot;
      } while (iRemaining && iGot >= 0 && pSocket->waitForReadyRead(2000));

      if (iGot >= 0)
      {
         QString strMessage(QString::fromUtf8(abMsg));
         pSocket->write(m_pcAck, qstrlen(m_pcAck));
         pSocket->waitForBytesWritten(1000);
         delete pSocket;
         emit messageReceived(strMessage); //### (might take a long time to return)
      }
      else
      {
         qWarning() << APPNAME << ": Message reception failed" << pSocket->errorString();
         delete pSocket;
      }
   }
}

QString LocalPeer::hexUid()
{
   QString strHexUid(QString::number(::getuid(), 16));

   const char* const pcSudoUid(::getenv("SUDO_UID"));

   if (pcSudoUid)
   {
      const int uiSudoUid(::strtol(pcSudoUid, NULL, 0));
      if (uiSudoUid)
         strHexUid = QString::number(uiSudoUid, 16);
   }
   else
   {
      const char* const pcUser(::getenv("USER"));
      if (pcUser)
      {
         const struct passwd* pPasswd(::getpwnam(pcUser));
         if (pPasswd)
            strHexUid = QString::number(pPasswd->pw_uid, 16);
      }
   }

   return(strHexUid);
}
