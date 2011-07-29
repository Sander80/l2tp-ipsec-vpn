/*
 * $Id: EapSettingsDialog.cpp 69 2011-04-12 04:33:22Z werner $
 *
 * File:   EapSettingsDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on July 29, 2010, 2:48 PM
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

#include <QFileDialog>
#include <QDir>

#include "pkcs11/Pkcs11.h"
#include "util/CertificateInfo.h"
#include "util/GlobalFunctions.h"
#include "settings/ConnectionSettings.h"
#include "ConnectionSettingsDialog.h"
#include "SmartCardObjectsDialog.h"
#include "EapSettingsDialog.h"

EapSettingsDialog::EapSettingsDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent), m_strConnectionName(strConnectionName)
{
   m_Widget.setupUi(this);

   setWindowTitle(strConnectionName + tr(" - EAP Settings"));

   connect(m_Widget.m_pUseCertificateRadioButton, SIGNAL(toggled(bool)), SLOT(onUseCertificateRadioButtonToggled(bool)));
   connect(m_Widget.m_pBrowseCertificateButton, SIGNAL(clicked()), SLOT(onCertificate()));
   connect(m_Widget.m_pBrowsePrivateKeyButton, SIGNAL(clicked()), SLOT(onPrivateKey()));
   connect(m_Widget.m_pBrowseCaCertificateButton, SIGNAL(clicked()), SLOT(onCaCertificate()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   readSettings();
}

EapSettingsDialog::~EapSettingsDialog()
{
}

void EapSettingsDialog::onUseCertificateRadioButtonToggled(bool fChecked)
{
   PppEapSettings eapSettings(ConnectionSettings().pppSettings(m_strConnectionName).eapSettings());

   if ((!fChecked && eapSettings.useSmartCard()) || (fChecked && !eapSettings.useSmartCard()))
   {
      m_Widget.m_pCertificateEdit->setText(eapSettings.certificatePath());
      m_Widget.m_pPrivateKeyEdit->setText(eapSettings.privateKeyPath());
      m_Widget.m_pPrivateKeyPwdEdit->setText(eapSettings.privateKeyPassword());
   }
   else
   {
      m_Widget.m_pCertificateEdit->setText("");
      m_Widget.m_pPrivateKeyEdit->setText("");
      m_Widget.m_pPrivateKeyPwdEdit->setText("");
   }
}

void EapSettingsDialog::onCertificate()
{
   if (m_Widget.m_pUseSmartCardRadioButton->isChecked())
   {
      SmartCardObjectsDialog dialog(SmartCardObjectListModel::Certificate);
      dialog.setWindowTitle(tr("Choose your personal certificate ..."));
      if (dialog.exec() == QDialog::Accepted)
      {
         m_Widget.m_pCertificateEdit->setText(dialog.selectedItem());
         m_strUserName = dialog.selectedUserName();
      }
   }
   else
   {
      const QString strCertPath(QFileDialog::getOpenFileName(this, tr("Choose your personal certificate ..."), QDir::homePath(), tr("PEM certificates (*.pem)")));

      if (!strCertPath.isNull())
      {
         m_Widget.m_pCertificateEdit->setText(strCertPath);
         m_strUserName = CertificateInfo(strCertPath).email();
      }
   }
}

void EapSettingsDialog::onPrivateKey()
{
   if (m_Widget.m_pUseSmartCardRadioButton->isChecked())
   {
      SmartCardObjectsDialog dialog(SmartCardObjectListModel::PublicKey);
      dialog.setWindowTitle(tr("Choose your private key ..."));
      if (dialog.exec() == QDialog::Accepted)
          m_Widget.m_pPrivateKeyEdit->setText(dialog.selectedItem());
   }
   else
   {
      const QString strPrivateKeyPath(QFileDialog::getOpenFileName(this, tr("Choose your private key ..."), QString(), tr("PEM private keys (*.pem)")));

      if (!strPrivateKeyPath.isNull())
         m_Widget.m_pPrivateKeyEdit->setText(strPrivateKeyPath);
   }
}

void EapSettingsDialog::onCaCertificate()
{
   const QString strCaCertPath(QFileDialog::getOpenFileName(this, tr("Choose a Certificate Authority certificate ..."), QString(), tr("PEM certificates (*.pem)")));

   if (!strCaCertPath.isNull())
      m_Widget.m_pCaCertificateEdit->setText(strCaCertPath);
}

void EapSettingsDialog::readSettings()
{
   const ConnectionSettings settings;
   const PppSettings pppSettings(settings.pppSettings(m_strConnectionName));
   const PppEapSettings eapSettings = pppSettings.eapSettings();

   if (!Pkcs11::loaded())
   {
      m_Widget.m_pUseSmartCardRadioButton->setDisabled(true);

      if (eapSettings.useSmartCard())
      {
         eapSettings.setUseSmartCard(false);
         eapSettings.setCertificatePath("");
         eapSettings.setPrivateKeyPath("");
         eapSettings.setPrivateKeyPassword("");
      }
   }

   if (eapSettings.useSmartCard())
   {
       m_Widget.m_pUseSmartCardRadioButton->setChecked(true);
       m_Widget.m_pUseCertificateRadioButton->setChecked(false);
   }
   else
   {
       m_Widget.m_pUseSmartCardRadioButton->setChecked(false);
       m_Widget.m_pUseCertificateRadioButton->setChecked(true);
   }

   m_Widget.m_pCertificateEdit->setText(eapSettings.certificatePath());
   m_Widget.m_pPrivateKeyEdit->setText(eapSettings.privateKeyPath());
   m_Widget.m_pPrivateKeyPwdEdit->setText(eapSettings.privateKeyPassword());
   m_Widget.m_pCaCertificateEdit->setText(eapSettings.caCertificatePath());
   m_strUserName = pppSettings.userName();
}

bool EapSettingsDialog::writeSettings() const
{
   const ConnectionSettings settings;
   const PppSettings pppSettings(settings.pppSettings(m_strConnectionName));
   const PppEapSettings eapSettings(pppSettings.eapSettings());

   bool fRet(eapSettings.setUseSmartCard(m_Widget.m_pUseSmartCardRadioButton->isChecked()));
   if (fRet) fRet = eapSettings.setCertificatePath(m_Widget.m_pCertificateEdit->text());
   if (fRet) fRet = eapSettings.setPrivateKeyPath(m_Widget.m_pPrivateKeyEdit->text());
   if (fRet) fRet = eapSettings.setPrivateKeyPassword(m_Widget.m_pPrivateKeyPwdEdit->text());
   if (fRet) fRet = eapSettings.setCaCertificatePath(m_Widget.m_pCaCertificateEdit->text());
   if (fRet) fRet = pppSettings.setUserName(m_strUserName);

   return(fRet);
}

void EapSettingsDialog::onHelpRequested() const
{
   ::showHelp("Configure_EAP_TLS_.28certificate.29_authentication");
}

void EapSettingsDialog::accept()
{
   writeSettings();
   QDialog::accept();
}
