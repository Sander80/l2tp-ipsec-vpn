/*
 * $Id: InterfaceStatisticsDialog.cpp 133 2012-05-02 09:13:26Z wejaeger $
 *
 * File:   InterfaceStatisticsDialog.cpp
 * Author: wejaeger
 *
 * Created on April 7, 2011, 11:52 AM
 *
 * Copyright 2010-2011 Werner Jaeger.
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

#include <QTimer>
#include <QLocale>
#include <QFileInfo>
#include <QDateTime>

#include "util/NetworkInterface.h"
#include "InterfaceStatisticsDialog.h"

static const long long KILO(1024);
static const long long MEGA(KILO * KILO);
static const long long GIGA(MEGA * MEGA);

InterfaceStatisticsDialog::InterfaceStatisticsDialog(const QString& strInterfaceName,QWidget* pParent) : QDialog(pParent), m_strInterfaceName(strInterfaceName), m_iConectedSince(InterfaceStatisticsDialog::connectedSince(strInterfaceName)), m_pTimer(new QTimer())
{
   m_Widget.setupUi(this);

   connect(m_pTimer, SIGNAL(timeout()), SLOT(onUpdateStatistic()));

   if (m_iConectedSince > 0)
   {
      QDateTime connectedSince;
      connectedSince.setTime_t(m_iConectedSince);
      m_Widget.m_pSince->setText(QLocale::system().toString(connectedSince, QLocale::ShortFormat));
   }

   onUpdateStatistic();
   m_pTimer->start(1000);
}

InterfaceStatisticsDialog::~InterfaceStatisticsDialog()
{
   m_pTimer->stop();
   delete m_pTimer;
}

void InterfaceStatisticsDialog::onUpdateStatistic() const
{
   const NetworkInterface::Statistic statistic(NetworkInterface::statistic(m_strInterfaceName.toStdString()));

   m_Widget.m_pTransmittedBytes->setText(InterfaceStatisticsDialog::formatBytes(statistic.transmitted().bytes()));
   m_Widget.m_pTransmittedPackets->setText(QString::number(statistic.transmitted().packets()));
   m_Widget.m_pTransmissionErrors->setText(QString::number(statistic.transmitted().errs()));
   m_Widget.m_pCollisions->setText(QString::number(statistic.transmitted().colls()));

   m_Widget.m_pReceivedBytes->setText(InterfaceStatisticsDialog::formatBytes(statistic.received().bytes()));
   m_Widget.m_pReceivedPackets->setText(QString::number(statistic.received().packets()));
   m_Widget.m_pReceptionErrors->setText(QString::number(statistic.received().errs()));

   m_Widget.m_pConnectionTime->setText(connectionTime());
}

const QString InterfaceStatisticsDialog::connectionTime() const
{
   QString strRet;

   if (m_iConectedSince > 0)
   {
      const qint64 lElapsed(QDateTime::currentDateTime().toTime_t() - m_iConectedSince);

      const QString strSeconds(QString::number((lElapsed) % 60));
      const QString strMinutes(QString::number((lElapsed / 60) % 60));
      const QString stHours(QString::number((lElapsed / 3600) % 24));
      const QString stHDays(QString::number(lElapsed / 86400));

      strRet = (stHDays.toLong() > 0 ? stHDays + " " + tr("Days") + " " : "") +
               (stHours.length() == 1 ? "0" + stHours : stHours) + ":" +
               (strMinutes.length() == 1 ? "0" + strMinutes : strMinutes) + ":" +
               (strSeconds.length() == 1 ? "0" + strSeconds : strSeconds);
   }

   return(strRet);
}

const QString InterfaceStatisticsDialog::formatBytes(const long long lBytes)
{
   QString strRet;

   const QLocale locale(QLocale::system());

   if (lBytes < KILO)
      strRet = locale.toString(lBytes);
   else if (lBytes < MEGA)
      strRet = locale.toString(static_cast<double>(lBytes) / KILO, 'f', 3) + " KB";
   else if (lBytes < GIGA)
      strRet = locale.toString(static_cast<double>(lBytes) / MEGA, 'f', 3) + " MB";
   else
      strRet = locale.toString(static_cast<double>(lBytes) / GIGA, 'f', 3) + " GB";

   return(strRet);
}

qint64 InterfaceStatisticsDialog::connectedSince(const QString& strInterfaceName)
{
   const QFileInfo info("/var/run/" + strInterfaceName + ".pid");

   return(info.exists() ? info.lastModified().toTime_t() : 0);
}