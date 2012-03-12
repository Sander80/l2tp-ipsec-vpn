/*
 * $Id: ConnectionSettingsDialog.cpp 114 2012-01-22 05:07:35Z werner $
 *
 * File:   ConnectionSettingsDialog.cpp
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

#include <QMessageBox>
#include <QFileDialog>

#include "settings/ConnectionSettings.h"
#include "models/ConnectionsModel.h"
#include "models/IPsecCertificateListModel.h"
#include "util/GlobalFunctions.h"
#include "PeerAuthenticationDialog.h"
#include "IpSettingsDialog.h"
#include "EapSettingsDialog.h"
#include "AdvancedSettingsDialog.h"
#include "CertificateImportDialog.h"
#include "ConnectionSettingsDialog.h"

static const char* const RSASIG("rsasig");
static const char* const SECRET("secret");
static const char* const IPSECPRIVATEKEYPATH("/etc/ipsec.d/private");

ConnectionSettingsDialog::ConnectionSettingsDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent),
   m_strConnectionName(strConnectionName), m_pCertificateListModel(new IPsecCertificateListModel())
{
   m_Widget.setupUi(this);

   m_Widget.m_pIPsecCertificateListView->setModel(m_pCertificateListModel);
   m_Widget.m_pConnectionNameEdit->setText(strConnectionName);

   m_Widget.m_pIPsecGatewayEdit->setValidator(new QRegExpValidator(::gatewayValidationRE(), this));
   m_Widget.m_pTabWidget->setCurrentIndex(0);

   connect(m_Widget.m_pIPsecUseCertificateRadioButton, SIGNAL(toggled(bool)), SLOT(onUseIPsecCertificateRadioButtonToggled(bool)));
   connect(m_Widget.m_pIPsecBrowsePrivateKeyButton, SIGNAL(clicked()), SLOT(onPrivateKey()));
   connect(m_Widget.m_pPppPropertiesButton, SIGNAL(clicked()), SLOT(onEapProperties()));
   connect(m_Widget.m_pPppPeerAuthenticationButton, SIGNAL(clicked()), SLOT(onPeerAuthentication()));
   connect(m_Widget.m_pPppIpSettingsButton, SIGNAL(clicked()), SLOT(onIpSettings()));
   connect(m_Widget.m_pPppAdvancedButton, SIGNAL(clicked()), SLOT(onAdvancedSettings()));
   connect(m_Widget.m_pPppUseEAPRadioButton, SIGNAL(toggled(bool)), SLOT(onUseEapRadioButtonToggled(bool)));
   connect(m_Widget.m_pImportPushButton, SIGNAL(clicked()), SLOT(onImport()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   readSettings();
}

ConnectionSettingsDialog::~ConnectionSettingsDialog()
{
   delete m_pCertificateListModel;
}

void ConnectionSettingsDialog::onHelpRequested() const
{
   switch (m_Widget.m_pTabWidget->currentIndex())
   {
      case 0:
         ::showHelp("Configure_IPsec_options");
         break;

      case 1:
         ::showHelp("Configure_L2TP_options");
         break;

      case 2:
         ::showHelp("Configure_PPP_options");
         break;

      default:
         ::showHelp("Configuring_a_connection");
   }
}

void ConnectionSettingsDialog::accept()
{
   writeSettings();
   QDialog::accept();
}

void ConnectionSettingsDialog::readSettings() const
{
   const ConnectionSettings settings;

   readCommonSettings(CommonSettings(settings.commonSettings(m_strConnectionName)));
   readIPSecSettings(IPSecSettings(settings.ipsecSettings(m_strConnectionName)));
   readL2tpSettings(L2tpSettings(settings.l2tpSettings(m_strConnectionName)));
   readPppSettings(PppSettings(settings.pppSettings(m_strConnectionName)));
}

bool ConnectionSettingsDialog::writeSettings() const
{
   const ConnectionSettings settings;

   bool fRet(writeCommonSetting((settings.commonSettings(m_strConnectionName))));
   if (fRet) fRet = writeIPsecSetting((settings.ipsecSettings(m_strConnectionName)));
   if (fRet) fRet = writeL2tpSettings((settings.l2tpSettings(m_strConnectionName)));
   if (fRet) fRet = writePppSettings((settings.pppSettings(m_strConnectionName)));

   return(fRet);
}

void ConnectionSettingsDialog::onEapProperties()const
{
   EapSettingsDialog eapSettings(m_strConnectionName);
   if (eapSettings.exec() == QDialog::Accepted)
      readSettings();
}

void ConnectionSettingsDialog::onPeerAuthentication() const
{
   PeerAuthenticationDialog peerAuthentication(m_strConnectionName);
   peerAuthentication.exec();
}

void ConnectionSettingsDialog::onIpSettings() const
{
   IpSettingsDialog ipsecSettings(m_strConnectionName);
   ipsecSettings.exec();
}

void ConnectionSettingsDialog::onAdvancedSettings() const
{
   AdvancedSettingsDialog advancedSettings(m_strConnectionName);
   advancedSettings.exec();
}

void ConnectionSettingsDialog::onUseIPsecCertificateRadioButtonToggled(bool fEnable)
{
   if (fEnable)
   {
      m_Widget.m_pIPsecCertificateListView->setEnabled(true);
      m_Widget.m_pIPsecPrivateKeyFrame->setEnabled(true);
      m_Widget.m_pIPsecPreSharedKeyEdit->setEnabled(false);
   }
   else
   {
      m_Widget.m_pIPsecCertificateListView->setEnabled(false);
      m_Widget.m_pIPsecPrivateKeyFrame->setEnabled(false);
      m_Widget.m_pIPsecPreSharedKeyEdit->setEnabled(true);
   }
}

void ConnectionSettingsDialog::onUseEapRadioButtonToggled(bool fEnabled)
{
   if (fEnabled)
   {
      m_Widget.m_pPppPropertiesButton->setEnabled(true);
      m_Widget.m_pPppAllowProtocolsListWidget->setEnabled(false);
      m_Widget.m_pPppUserNameEdit->setEnabled(false);
      m_Widget.m_pPppPwdEdit->setEnabled(false);
   }
   else
   {
      m_Widget.m_pPppPropertiesButton->setEnabled(false);
      m_Widget.m_pPppAllowProtocolsListWidget->setEnabled(true);
      m_Widget.m_pPppUserNameEdit->setEnabled(true);
      m_Widget.m_pPppPwdEdit->setEnabled(true);
   }
}

void ConnectionSettingsDialog::onPrivateKey()
{
   const QString strPrivateKeyPath(QFileDialog::getOpenFileName(this, tr("Choose private key ..."), IPSECPRIVATEKEYPATH, tr("PEM private keys (*.pem)")));

   if (!strPrivateKeyPath.isNull())
      m_Widget.m_pIPsecPrivateKeyFileEdit->setText(strPrivateKeyPath);
}

void ConnectionSettingsDialog::onImport()
{
   CertificateImportDialog importDialog;
   if (importDialog.exec() == QDialog::Accepted)
   {
      m_pCertificateListModel->refresh();

      if (importDialog.useAsAuthenticationCertificate())
      {
         m_pCertificateListModel->select(importDialog.certificateFilename());
         m_Widget.m_pIPsecPrivateKeyFileEdit->setText(importDialog.privateKeyFilenamePath());
         m_Widget.m_pIPsecPassphraseEdit->setText(importDialog.passPhrase());
      }
   }
}

void ConnectionSettingsDialog::readCommonSettings(const CommonSettings& commonSettings) const
{
   m_Widget.m_pConnectAutomatically->setChecked(commonSettings.autoConnect());
   m_Widget.m_pDisableIPSecEncryption->setChecked(commonSettings.disableIPSecEncryption());
}

void ConnectionSettingsDialog::readIPSecSettings(const IPSecSettings& ipsecSettings) const
{
   m_Widget.m_pIPsecGatewayEdit->setText(ipsecSettings.gateway());
   m_Widget.m_pIPsecIdentityEdit->setText(ipsecSettings.identity());

   const QString strAuthBy(ipsecSettings.authBy());
   if (RSASIG == strAuthBy)
   {
      m_Widget.m_pIPsecUsePreSharedKeyRadioButton->setChecked(false);
      m_Widget.m_pIPsecUseCertificateRadioButton->setChecked(true);
      m_Widget.m_pIPsecPreSharedKeyEdit->setEnabled(false);
      m_Widget.m_pIPsecCertificateListView->setEnabled(true);
      m_Widget.m_pIPsecPrivateKeyFrame->setEnabled(true);
   }
   else
   {
      m_Widget.m_pIPsecUsePreSharedKeyRadioButton->setChecked(true);
      m_Widget.m_pIPsecUseCertificateRadioButton->setChecked(false);
      m_Widget.m_pIPsecPreSharedKeyEdit->setEnabled(true);
      m_Widget.m_pIPsecCertificateListView->setEnabled(false);
      m_Widget.m_pIPsecPrivateKeyFrame->setEnabled(false);
   }

   m_Widget.m_pIPsecPreSharedKeyEdit->setText(ipsecSettings.preSharedKey());
   m_pCertificateListModel->select(ipsecSettings.certificateFileName());
   m_Widget.m_pIPsecPrivateKeyFileEdit->setText(ipsecSettings.privateKeyFilePath());
   m_Widget.m_pIPsecPassphraseEdit->setText(ipsecSettings.privateKeyPassphrase());
}

void ConnectionSettingsDialog::readL2tpSettings(const L2tpSettings& l2tpSettings) const
{
   m_Widget.m_pL2tpLengthBitCheckBox->setCheckState(l2tpSettings.lengthBit() == true ? Qt::Checked : Qt::Unchecked);

   const bool fRedial = l2tpSettings.redial();
   m_Widget.m_pL2tpRedialCheckBox->setCheckState(fRedial ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pL2tpRedialTimeoutSpinBox->setValue(l2tpSettings.redialTimeout());
   m_Widget.m_pL2tpRedialTimeoutSpinBox->setEnabled(fRedial);
   m_Widget.m_pL2tpRedialAttemptsSpinBox->setValue(l2tpSettings.redialAttempts());
   m_Widget.m_pL2tpRedialAttemptsSpinBox->setEnabled(fRedial);
}

void ConnectionSettingsDialog::readPppSettings(const PppSettings& pppSettings) const
{
   if (!pppSettings.refuseEap())
   {
      m_Widget.m_pPppAllowProtocolsRadioButton->setChecked(false);
      m_Widget.m_pPppUseEAPRadioButton->setChecked(true);
      m_Widget.m_pPppAllowProtocolsListWidget->setEnabled(false);
      m_Widget.m_pPppPropertiesButton->setEnabled(true);
      m_Widget.m_pPppUserNameEdit->setEnabled(false);
      m_Widget.m_pPppPwdEdit->setEnabled(false);
   }
   else
   {
      m_Widget.m_pPppAllowProtocolsRadioButton->setChecked(true);
      m_Widget.m_pPppUseEAPRadioButton->setChecked(false);
      m_Widget.m_pPppAllowProtocolsListWidget->setEnabled(true);
      m_Widget.m_pPppPropertiesButton->setEnabled(false);
      m_Widget.m_pPppUserNameEdit->setEnabled(true);
      m_Widget.m_pPppPwdEdit->setEnabled(true);
   }

   m_Widget.m_pPppAllowProtocolsListWidget->item(0)->setCheckState(!pppSettings.refusePap() ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pPppAllowProtocolsListWidget->item(1)->setCheckState(!pppSettings.refuseChap() ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pPppAllowProtocolsListWidget->item(2)->setCheckState(!pppSettings.refuseMsChap() ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pPppAllowProtocolsListWidget->item(3)->setCheckState(!pppSettings.refuseMsChapV2() ? Qt::Checked : Qt::Unchecked);

   m_Widget.m_pPppUserNameEdit->setText(pppSettings.userName());
   m_Widget.m_pPppPwdEdit->setText(pppSettings.password());
}

bool ConnectionSettingsDialog::writeCommonSetting(const CommonSettings& commonSettings) const
{
   bool fRet(commonSettings.setAutoConnect(m_Widget.m_pConnectAutomatically->isChecked()));
   if (fRet) fRet = commonSettings.setDisableIPSecEncryption(m_Widget.m_pDisableIPSecEncryption->isChecked());

   return(fRet);
}

bool ConnectionSettingsDialog::writeIPsecSetting(const IPSecSettings& ipsecSettings) const
{
   bool fRet(ipsecSettings.setGateway(m_Widget.m_pIPsecGatewayEdit->text()));
   if (fRet) fRet = ipsecSettings.setIdentity(m_Widget.m_pIPsecIdentityEdit->text());
   if (fRet) fRet = ipsecSettings.setAuthBy(m_Widget.m_pIPsecUseCertificateRadioButton->isChecked() ? RSASIG : SECRET);
   if (fRet) fRet = ipsecSettings.setPreSharedKey(m_Widget.m_pIPsecPreSharedKeyEdit->text());
   if (fRet) fRet = ipsecSettings.setCertificateFileName(m_pCertificateListModel->selectedCertificateFileName());
   if (fRet) fRet = ipsecSettings.setPrivateKeyFilePath(m_Widget.m_pIPsecPrivateKeyFileEdit->text());
   if (fRet) fRet = ipsecSettings.setPrivateKeyPassphrase(m_Widget.m_pIPsecPassphraseEdit->text());

   return(fRet);
}

bool ConnectionSettingsDialog::writeL2tpSettings(const L2tpSettings& l2tpSettings) const
{
   bool fRet(l2tpSettings.setLengthBit(m_Widget.m_pL2tpLengthBitCheckBox->checkState()));
   if (fRet) fRet = l2tpSettings.setRedial(m_Widget.m_pL2tpRedialCheckBox->checkState());
   if (fRet) fRet = l2tpSettings.setRedialTimeout(m_Widget.m_pL2tpRedialTimeoutSpinBox->value());
   if (fRet) fRet = l2tpSettings.setRedialAttempts(m_Widget.m_pL2tpRedialAttemptsSpinBox->value());

   return(fRet);
}

bool ConnectionSettingsDialog::writePppSettings(const PppSettings& pppSettings) const
{
   bool fRet(pppSettings.setRefuseEap(!m_Widget.m_pPppUseEAPRadioButton->isChecked()));
   if (fRet) fRet = pppSettings.setRefusePap(m_Widget.m_pPppAllowProtocolsListWidget->item(0)->checkState() == Qt::Checked ? false : true);
   if (fRet) fRet = pppSettings.setRefuseChap(m_Widget.m_pPppAllowProtocolsListWidget->item(1)->checkState() == Qt::Checked ? false : true);
   if (fRet) fRet = pppSettings.setRefuseMsChap(m_Widget.m_pPppAllowProtocolsListWidget->item(2)->checkState() == Qt::Checked ? false : true);
   if (fRet) fRet = pppSettings.setRefuseMsChapV2(m_Widget.m_pPppAllowProtocolsListWidget->item(3)->checkState() == Qt::Checked ? false : true);
   if (fRet) fRet = pppSettings.setUserName(m_Widget.m_pPppUserNameEdit->text());
   if (fRet) fRet = pppSettings.setPassword(m_Widget.m_pPppPwdEdit->text());

   return(fRet);
}

