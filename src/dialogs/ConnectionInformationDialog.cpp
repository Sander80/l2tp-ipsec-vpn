/*
 * $Id: ConnectionInformationDialog.cpp 129 2012-04-07 10:15:46Z wejaeger $
 *
 * File:   ConnectionInformationDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on July 18, 2010, 3:37 PM
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

#include <QDateTime>

#include "ConnectionState.h"
#include "ConnectionManager.h"
#include "InterfaceStatisticsDialog.h"
#include "ConnectionInformationDialog.h"

ConnectionInformationDialog::ConnectionInformationDialog(QWidget* pParent) : QDialog(pParent)
{
   m_Widget.setupUi(this);

   connect(m_Widget.m_pStatisticsPushButton, SIGNAL(clicked()), SLOT(onStatistics()));
}

ConnectionInformationDialog::~ConnectionInformationDialog()
{
}

void ConnectionInformationDialog::appendLogPlainText(const char* pcText)
{
   const QString strText(pcText);
   const int iPos(strText.indexOf("ipsec__plutorun"));

   m_Widget.m_pTextEdit->insertPlainText(QDateTime::currentDateTime().toString("MMM dd hh:mm:ss.zzz") + " " + strText.mid((iPos == -1 ? 0 : iPos)));
}

void ConnectionInformationDialog::appendLogColorText(const QColor& color, const char* pcText)
{
   const QColor currentColor(m_Widget.m_pTextEdit->textColor());

   if (pcText)
   {
      m_Widget.m_pTextEdit->setTextColor(color);
      appendLogPlainText(pcText);
      m_Widget.m_pTextEdit->setTextColor(currentColor);
   }
}

void ConnectionInformationDialog::onConectionStateChanged(const ConnectionState* pNewState, const QString& strConnectionName)
{
   if (pNewState)
   {
      setWindowIcon(pNewState->icon());

      if (pNewState->isState(ConnectionState::Connected))
      {
         const NetworkInterface interface(pNewState->ptpInterface());
         const NetworkInterface::AddressEntries addressEntries(interface.addressEntries());
         const NetworkInterface::DefaultGatewayInfo internetInterfaceInfo(NetworkInterface::defaultGatewayInfo());

         m_Widget.m_pTabWidget->setCurrentIndex(0);
         m_Widget.m_pTabWidget->setTabEnabled(0, true);
         m_Widget.m_pTabWidget->setTabText(0, strConnectionName);
         m_Widget.m_pGateway->setText(pNewState->hostName());
         m_Widget.m_pInternetInterfaceName->setText(internetInterfaceInfo.interfaceName().c_str());
         m_Widget.m_pInternetInterfaceGateway->setText(internetInterfaceInfo.gateway().c_str());
         m_Widget.m_pInterfaceName->setText(interface.name().c_str());

         if (!addressEntries.empty())
         {
            m_Widget.m_pRemoteHost->setText(addressEntries[0].broadcast().toString());
            m_Widget.m_pIPAddress->setText(addressEntries[0].ip().toString());
            m_Widget.m_pSubnetMask->setText(addressEntries[0].netmask().toString());
         }
         else
         {
            m_Widget.m_pRemoteHost->setText("");
            m_Widget.m_pIPAddress->setText("");
            m_Widget.m_pSubnetMask->setText("");
         }

         const QStringList dns(NetworkInterface::dns());
         if (dns.size() > 0)
         {
            m_Widget.m_pPrimaryDNS->setText(dns.at(0));
            if (dns.size() > 1)
            {
               m_Widget.m_pSecondaryDNS->setText(dns.at(1));
               if (dns.size() > 2)
                  m_Widget.m_pTenaryDNS->setText(dns.at(2));
            }
         }
      }
      else
      {
         m_Widget.m_pTabWidget->setCurrentIndex(1);
         m_Widget.m_pTabWidget->setTabEnabled(0, false);
         m_Widget.m_pTabWidget->setTabText(0, pNewState->msgTitle());
      }
   }
}

void ConnectionInformationDialog::onStatistics() const
{
   InterfaceStatisticsDialog interfaceStatistics(m_Widget.m_pInterfaceName->text());
   interfaceStatistics.exec();
}