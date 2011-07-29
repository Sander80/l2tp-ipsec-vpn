/*
 * $Id: AdvancedSettingsDialog.cpp 64 2011-04-05 03:39:39Z werner $
 *
 * File:   AdvancedSettingsDialog.cpp
 * Author: wejaeger
 *
 * Created on September 18, 2010, 4:21 PM
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

#include "settings/ConnectionSettings.h"
#include "util/GlobalFunctions.h"
#include "AdvancedSettingsDialog.h"

AdvancedSettingsDialog::AdvancedSettingsDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent), m_strConnectionName(strConnectionName)
{
   m_Widget.setupUi(this);

   setWindowTitle(strConnectionName + tr(" - Advanced Settings"));

   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   readSettings();
}

AdvancedSettingsDialog::~AdvancedSettingsDialog()
{
}

void AdvancedSettingsDialog::onHelpRequested() const
{
   ::showHelp("Configure_advanced_settings");
}

void AdvancedSettingsDialog::accept()
{
   writeSettings();
   QDialog::accept();
}

void AdvancedSettingsDialog::readSettings() const
{
   const PppSettings pppSettings(ConnectionSettings().pppSettings(m_strConnectionName));

   m_Widget.m_pAllowBSDCompressionCheckBox->setChecked(!pppSettings.noBSDCompression());
   m_Widget.m_pAllowDeflateCompressionCheckBox->setChecked(!pppSettings.noDeflate());
   m_Widget.m_pUseTCPHeaderCompressionCheckBox->setChecked(!pppSettings.noVj());
   m_Widget.m_pSendEchoCheckBox->setChecked(pppSettings.lcpEchoInterval() != 0);
}

bool AdvancedSettingsDialog::writeSettings() const
{
   const PppSettings pppSettings(ConnectionSettings().pppSettings(m_strConnectionName));

   bool fRet = pppSettings.setNoBSDCompression(!m_Widget.m_pAllowBSDCompressionCheckBox->isChecked());
   if (fRet) fRet = pppSettings.setNoDeflate(!m_Widget.m_pAllowDeflateCompressionCheckBox->isChecked());
   if (fRet) fRet = pppSettings.setNoVj(!m_Widget.m_pUseTCPHeaderCompressionCheckBox->isChecked());
   if (fRet) fRet = pppSettings.setLcpEchoInterval(m_Widget.m_pSendEchoCheckBox->isChecked() ? -1 : 0);

   return(fRet);
}
