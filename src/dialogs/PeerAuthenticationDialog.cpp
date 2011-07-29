/*
 * $Id: PeerAuthenticationDialog.cpp 64 2011-04-05 03:39:39Z werner $
 *
 * File:   PeerAuthenticationDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 11:19 AM
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
#include "PeerAuthenticationDialog.h"

PeerAuthenticationDialog::PeerAuthenticationDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent), m_strConnectionName(strConnectionName)
{
   m_Widget.setupUi(this);

   setWindowTitle(strConnectionName + tr(" - Peer Authentication Settings"));

   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   readSettings();
}

PeerAuthenticationDialog::~PeerAuthenticationDialog()
{
}

void PeerAuthenticationDialog::readSettings() const
{
   const ConnectionSettings settings;
   const PppSettings pppSettings = settings.pppSettings(m_strConnectionName);

   m_Widget.m_pRemoteNameEdit->setText(pppSettings.remoteName());
}

bool PeerAuthenticationDialog::writeSettings() const
{
   const ConnectionSettings settings;
   const PppSettings pppSettings = settings.pppSettings(m_strConnectionName);

   bool fRet = pppSettings.setRemoteName(m_Widget.m_pRemoteNameEdit->text());

   return(fRet);
}

void PeerAuthenticationDialog::onHelpRequested() const
{
   ::showHelp("Configure_Peer_authentication");
}

void PeerAuthenticationDialog::accept()
{
   writeSettings();
   QDialog::accept();
}

