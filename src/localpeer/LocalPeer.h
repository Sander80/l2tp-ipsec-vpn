/*
 * $Id: LocalPeer.h 75 2011-04-15 08:00:25Z werner $
 *
 * File:   LocalPeer.h
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

#ifndef LOCALPEER_H
#define	LOCALPEER_H

#include <QObject>

#include "LockedFile.h"

class QLocalServer;

class LocalPeer : public QObject
{
   Q_OBJECT

public:
   LocalPeer(QObject* pParent = NULL, const QString& strAppId = QString());
   virtual ~LocalPeer();

   bool isClient();
   QString applicationId() const;
   bool sendMessage(const QString &strMessage, int iTimeout);

signals:
   void messageReceived(const QString& strMessage);

protected slots:
   void receiveConnection();

protected:
private:
   LocalPeer(const LocalPeer& orig);
   LocalPeer& operator=(const LocalPeer& orig);

   static QString hexUid();

   QString m_strApplicationId;
   QString m_strSocketName;
   QLocalServer* const m_pServer;
   LockedFile m_LockedFile;

   static const char* m_pcAck;
};

#endif	/* LOCALPEER_H */

