/*
 * $Id: ConnectionState.cpp 132 2012-04-24 06:04:01Z wejaeger $
 *
 * File:   ConnectionState.cpp
 * Author: Werner Jaeger
 *
 * Created on July 8, 2010, 10:35 AM
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

#include <QSystemTrayIcon>
#include <QMovie>

#include "ConnectionManager.h"
#include "ConnectionState.h"

ConnectionState::ConnectionState(QSystemTrayIcon* pTrayIcon, const QString& strHostName, const QString& strMsgTitle, const QString& strMsgBody, const QIcon& icon, const QSystemTrayIcon::MessageIcon& msgIcon, const NetworkInterface& ptpInterface) : m_pTrayIcon(pTrayIcon), m_strHostName(strHostName), m_strMsgTitle(strMsgTitle), m_strMsgBody(strMsgBody), m_Icon(icon), m_MsgIcon(msgIcon), m_PtpInterface(ptpInterface)
{
   if (pTrayIcon)
   {
      pTrayIcon->setIcon(icon);
      pTrayIcon->setToolTip(strMsgTitle);
   }
}

ConnectionState::~ConnectionState()
{
}

const QString& ConnectionState::hostName() const
{
   return(m_strHostName);
}

const QString& ConnectionState::msgTitle() const
{
   return(m_strMsgTitle);
}

const QString& ConnectionState::msgBody() const
{
   return(m_strMsgBody);
}

const QIcon& ConnectionState::icon() const
{
   return(m_Icon);
}

const QSystemTrayIcon::MessageIcon& ConnectionState::msgIcon() const
{
   return(m_MsgIcon);
}

const NetworkInterface& ConnectionState::ptpInterface() const
{
   return(m_PtpInterface);
}

NotConnected::NotConnected(QSystemTrayIcon* pTrayIcon) : ConnectionState(pTrayIcon, "", QObject::tr("Not Connected"), QObject::tr("Click to show details"), QIcon(":/images/connectNo"), QSystemTrayIcon::Warning)
{
}

NotConnected::~NotConnected()
{
}

Connecting::Connecting(QSystemTrayIcon* pTrayIcon, const QString& strHostName) : ConnectionState(pTrayIcon, strHostName, QObject::tr("Connecting to ") + strHostName + " ...", QObject::tr("Click to show details"), QIcon(":/images/busy"), QSystemTrayIcon::Information), m_pMovie(new QMovie(":/images/busy"))
{
   connect(m_pMovie, SIGNAL(frameChanged(int)), SLOT(onFrameChanged()));

   if (m_pMovie->isValid())
      m_pMovie->start();
}

Connecting::~Connecting()
{
   delete m_pMovie;
}

void Connecting::onFrameChanged() const
{
   if (trayIcon())
      trayIcon()->setIcon(QIcon(m_pMovie->currentPixmap()));
}

Disconnecting::Disconnecting(QSystemTrayIcon* pTrayIcon, const QString& strHostName) : ConnectionState(pTrayIcon, strHostName, QObject::tr("Disconnecting from ") + strHostName + " ...", QObject::tr("Click to show details"), QIcon(":/images/busy"), QSystemTrayIcon::Information), m_pMovie(new QMovie(":/images/busy"))
{
   connect(m_pMovie, SIGNAL(frameChanged(int)), SLOT(onFrameChanged()));

   if (m_pMovie->isValid())
      m_pMovie->start();
}

Disconnecting::~Disconnecting()
{
   delete m_pMovie;
}

void Disconnecting::onFrameChanged() const
{
   if (trayIcon())
      trayIcon()->setIcon(QIcon(m_pMovie->currentPixmap()));
}

Connected::Connected(QSystemTrayIcon* pTrayIcon, const QString& strHostName, const NetworkInterface& ptpInterface) : ConnectionState(pTrayIcon, strHostName, QObject::tr("Connected to ") + strHostName, QObject::tr("Click to show details"), QIcon(":/images/connectEstablished"), QSystemTrayIcon::Information, ptpInterface)
{
}

Connected::~Connected()
{
}

Error::Error(QSystemTrayIcon* pTrayIcon, const QString& strHostName, int iReturnCode, bool fDisconnecting) : ConnectionState(pTrayIcon, strHostName, (fDisconnecting ? QObject::tr("Error %1 occurred when disconnecting from ").arg(iReturnCode) : QObject::tr("Error %1 occurred when connecting to ").arg(iReturnCode)) + strHostName, QObject::tr("Click to show details"), QIcon(":/images/connectError"), QSystemTrayIcon::Critical)
{
}

Error::~Error()
{
}
