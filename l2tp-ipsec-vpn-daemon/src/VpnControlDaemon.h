/*
 * $Id: VpnControlDaemon.h 10 2010-09-17 09:13:01Z werner $
 *
 * File:   VpnControlDaemon.h
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

#ifndef VPNCONTROLDAEMON_H
#define	VPNCONTROLDAEMON_H

#include <QObject>

class QLocalServer;

class VpnControlDaemon : public QObject
{
  Q_OBJECT

public:
   VpnControlDaemon(const QString& strKey, QObject* pParent = NULL);
   virtual ~VpnControlDaemon();

   bool start();

private slots:
   void incomingLocalConnection();

private:
   VpnControlDaemon(const VpnControlDaemon& orig);
   VpnControlDaemon& operator=(const VpnControlDaemon& orig);

   QString const m_strKey;
   QLocalServer* const m_pServer;
};

#endif	/* VPNCONTROLDAEMON_H */

