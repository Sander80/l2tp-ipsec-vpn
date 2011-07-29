/*
 * $Id: IpSettingsDialog.cpp 64 2011-04-05 03:39:39Z werner $
 *
 * File:   IpSettingsDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on August 20, 2010, 9:59 AM
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

#include "util/GlobalFunctions.h"
#include "settings/ConnectionSettings.h"
#include "RouteSettingsDialog.h"
#include "IpSettingsDialog.h"

IpSettingsDialog::IpSettingsDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent), m_strConnectionName(strConnectionName)
{
   m_Widget.setupUi(this);

   setWindowTitle(strConnectionName + tr(" - Ip Settings"));

   m_Widget.m_pPrimaryDNSServersEdit->setValidator(new QRegExpValidator(::ipv4ValidationRE(), this));
   m_Widget.m_pSecundaryDNSServersEdit->setValidator(new QRegExpValidator(::ipv4ValidationRE(), this));
   m_Widget.m_pSearchDomainsEdit->setValidator(new QRegExpValidator(::hostNameListValidationRE(), this));

   connect(m_Widget.m_pRoutesButton, SIGNAL(clicked()), SLOT(onRouteSettings()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   readSettings();
}

IpSettingsDialog::~IpSettingsDialog()
{
}

void IpSettingsDialog::onRouteSettings() const
{
   RouteSettingsDialog routeSettings(m_strConnectionName);
   routeSettings.exec();
}

void IpSettingsDialog::onHelpRequested() const
{
   ::showHelp("Configure_IP_settings");
}

void IpSettingsDialog::accept()
{
   writeSettings();
   QDialog::accept();
}

void IpSettingsDialog::readSettings() const
{
   const ConnectionSettings settings;
   const PppIpSettings ipSettings = settings.pppSettings(m_strConnectionName).ipSettings();

   if (ipSettings.usePeerDns())
   {
      m_Widget.m_pAutomaticDNSCheckBox->setChecked(true);
      m_Widget.m_pPrimaryDNSServersEdit->setDisabled(true);
      m_Widget.m_pSecundaryDNSServersEdit->setDisabled(true);
      m_Widget.m_pSearchDomainsEdit->setDisabled(true);
   }
   else
   {
      m_Widget.m_pAutomaticDNSCheckBox->setChecked(false);
      m_Widget.m_pPrimaryDNSServersEdit->setEnabled(true);
      m_Widget.m_pSecundaryDNSServersEdit->setEnabled(true);
      m_Widget.m_pSearchDomainsEdit->setEnabled(true);
   }

   m_Widget.m_pPrimaryDNSServersEdit->setText(ipSettings.preferredDnsServerAddress());
   m_Widget.m_pSecundaryDNSServersEdit->setText(ipSettings.alternateDnsServerAddress());
   m_Widget.m_pSearchDomainsEdit->setText(ipSettings.searchDomains());
}

bool IpSettingsDialog::writeSettings() const
{
   const ConnectionSettings settings;
   const PppIpSettings ipSettings = settings.pppSettings(m_strConnectionName).ipSettings();

   bool fRet = ipSettings.setUsePeerDns(m_Widget.m_pAutomaticDNSCheckBox->isChecked());
   if (fRet) fRet = ipSettings.setPreferredDnsServerAddress(m_Widget.m_pPrimaryDNSServersEdit->text());
   if (fRet) fRet = ipSettings.setAlternateDnsServerAddress(m_Widget.m_pSecundaryDNSServersEdit->text());
   if (fRet) fRet = ipSettings.setSearchDomains(m_Widget.m_pSearchDomainsEdit->text());

   return(fRet);
}