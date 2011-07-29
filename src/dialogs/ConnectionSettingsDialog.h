/*
 * $Id: ConnectionSettingsDialog.h 69 2011-04-12 04:33:22Z werner $
 *
 * File:   ConnectionSettingsDialog.h
 * Author: Werner Jaeger
 *
 * Created on July 21, 2010, 5:27 PM
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

#ifndef _CONNECTIONSETTINGSDIALOG_H
#define	_CONNECTIONSETTINGSDIALOG_H

#include "ui_ConnectionSettingsDialog.h"

class CommonSettings;
class IPSecSettings;
class L2tpSettings;
class PppSettings;
class IPsecCertificateListModel;

class ConnectionSettingsDialog : public QDialog
{
   Q_OBJECT

public:
   ConnectionSettingsDialog(const QString& strConnectionName, QWidget* pParent = 0);
   virtual ~ConnectionSettingsDialog();

private slots:
   void onHelpRequested() const;
   void accept();
   void readSettings() const;
   bool writeSettings() const;
   void onEapProperties() const;
   void onPeerAuthentication() const;
   void onIpSettings() const;
   void onAdvancedSettings() const;
   void onUseIPsecCertificateRadioButtonToggled(bool fEnable);
   void onUseEapRadioButtonToggled(bool fEnabled);
   void onPrivateKey();
   void onImport();

private:
   ConnectionSettingsDialog(const ConnectionSettingsDialog& orig);
   ConnectionSettingsDialog& operator=(const ConnectionSettingsDialog& orig);

   void readCommonSettings(const CommonSettings& commonSettings) const;
   void readIPSecSettings(const IPSecSettings& ipsecSettings) const;
   void readL2tpSettings(const L2tpSettings& l2tpSettings) const;
   void readPppSettings(const PppSettings& pppSettings) const;
   bool writeCommonSetting(const CommonSettings& commonSettings) const;
   bool writeIPsecSetting(const IPSecSettings& ipsecSettings) const;
   bool writeL2tpSettings(const L2tpSettings& l2tpSettings) const;
   bool writePppSettings(const PppSettings& pppSettings) const;

   Ui::ConnectionSettingsDialog m_Widget;

   const QString m_strConnectionName;

   IPsecCertificateListModel* const m_pCertificateListModel;
};

#endif	/* _CONNECTIONSETTINGSDIALOG_H */
