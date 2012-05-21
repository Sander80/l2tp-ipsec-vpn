/*
 * $Id: CertificateImportDialog.cpp 129 2012-04-07 10:15:46Z wejaeger $
 *
 * File:   CertificateImportDialog.cpp
 * Author: wejaeger
 *
 * Created on April 11, 2011, 11:58 AM
 *
 * Copyright 2011 Werner Jaeger.
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
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>

#include "util/GlobalFunctions.h"
#include "util/Pkcs12.h"
#include "CertificateImportDialog.h"
#include "pkcs11/SmartCardState.h"

static const QString IPSECCERTSPATH("/etc/ipsec.d/certs/");
static const QString IPSECPRIVATEKEYPATH("/etc/ipsec.d/private/");
static const QString IPSECCACERTSPATH("/etc/ipsec.d/cacerts/");
static const QString PEMEXT(".pem");

CertificateImportDialog::CertificateImportDialog(QWidget* pParent) : QDialog(pParent), m_pPkcs12(NULL)
{
   m_Widget.setupUi(this);

   QPalette infoTextEditPalette(m_Widget.m_pInfoTextEdit->palette());
   infoTextEditPalette.setColor(QPalette::Base, palette().color(backgroundRole()));
   m_Widget.m_pInfoTextEdit->setPalette(infoTextEditPalette);

   onValidateInput();

   connect(m_Widget.m_pBrowseFilePushButton, SIGNAL(clicked()), SLOT(onCertificate()));
   connect(m_Widget.m_pPrivateKeyPassphraseEdit, SIGNAL(textChanged(const QString &)), SLOT(onValidateInput()));
   connect(m_Widget.m_pVerifyPrivateKeyPassphraseEdit, SIGNAL(textChanged(const QString &)), SLOT(onValidateInput()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));
}

CertificateImportDialog::~CertificateImportDialog()
{
   if (m_pPkcs12)
      delete m_pPkcs12;
}

const QString CertificateImportDialog::certificateFilename() const
{
   return(isInputValid() ? m_pPkcs12->cn() + PEMEXT : QString::null);
}

const QString CertificateImportDialog::certificateFilenamePath() const
{
   return(IPSECCERTSPATH + certificateFilename());
}

const QString CertificateImportDialog::privateKeyFilename() const
{
   return(isInputValid() ? m_pPkcs12->cn() + PEMEXT : QString::null);
}

const QString CertificateImportDialog::privateKeyFilenamePath() const
{
   return(IPSECPRIVATEKEYPATH + privateKeyFilename());
}

const QString CertificateImportDialog::caCertificateFilename() const
{
   return(isInputValid() ? m_pPkcs12->issuer() + PEMEXT : QString::null);
}

const QString CertificateImportDialog::caCertificateFilenamePath() const
{
   return(IPSECCACERTSPATH + caCertificateFilename());
}

const QString CertificateImportDialog::passPhrase() const
{
   return(m_Widget.m_pPrivateKeyPassphraseEdit->text());
}

bool CertificateImportDialog::useAsAuthenticationCertificate() const
{
   return(m_Widget.m_pSeletAutomaticallyCheckBox->isChecked());
}

void CertificateImportDialog::onHelpRequested() const
{
   ::showHelp("Import_PKCS12_certificate_bundle");
}

void CertificateImportDialog::onCertificate()
{
   const QString strPkcs12FileNamePath(QFileDialog::getOpenFileName(this, tr("Choose the PKCS12 certificate bundle to import ..."), QDir::homePath(), tr("PKSC#12 certificate bundle (*.p12 *.pfx)")));

   if (!strPkcs12FileNamePath.isNull())
   {
      m_Widget.m_pFileEdit->setText(strPkcs12FileNamePath);

      bool fOk(true);
      QString strPassphrase;
      while (fOk && strPassphrase.isNull())
         strPassphrase = QInputDialog::getText(this, tr("Passphrase Entry Dialog"), tr("Please enter the passphrase that was used to encrypt this certificate bundle:"), QLineEdit::Password, QString(), &fOk);

      if (fOk && !strPassphrase.isEmpty())
      {
         m_Widget.m_pInfoTextEdit->clear();

         if (m_pPkcs12)
         {
            delete m_pPkcs12;
            m_pPkcs12 = NULL;
         }

         m_pPkcs12 =  new Pkcs12(strPkcs12FileNamePath, strPassphrase);

         if (m_pPkcs12->error().isNull())
         {
            m_Widget.m_pInfoTextEdit->insertHtml("<b>" + tr("Content:") + "</b><br>");
            m_Widget.m_pInfoTextEdit->insertHtml("1 " + tr("certificate") + " " + m_pPkcs12->cn() + " " + tr("issued by") + " " + m_pPkcs12->issuer() + "<br>");

            if (m_pPkcs12->hasPrivateKey())
               m_Widget.m_pInfoTextEdit->insertHtml("1 " + tr("private key") + "<br>");

            m_Widget.m_pInfoTextEdit->insertHtml(tr("%n root certificate(s)", "", m_pPkcs12->caCerts()));

            m_Widget.m_pPrivateKeyPassphraseEdit->setFocus();
         }
         else
            showError();
      }
   }

   onValidateInput();
}

void CertificateImportDialog::onValidateInput() const
{
   if (isInputValid())
      m_Widget.m_pButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
   else
      m_Widget.m_pButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

void CertificateImportDialog::accept()
{
   if (isInputValid())
   {
      if (writePems())
         QDialog::accept();
      else
         showError();
   }
}

bool CertificateImportDialog::isInputValid() const
{
   const QString strPassphrase(m_Widget.m_pPrivateKeyPassphraseEdit->text());
   const QString strVerifyPassphrase(m_Widget.m_pVerifyPrivateKeyPassphraseEdit->text());

   bool fRet(m_pPkcs12 && m_pPkcs12->error().isNull() && !strPassphrase.isEmpty() && strPassphrase == strVerifyPassphrase);

   return(fRet);
}

bool CertificateImportDialog::writePems() const
{
   bool fRet(false);

   if (isInputValid())
   {
      if (checkIfFileExistAndConfirmOverwrite(certificateFilenamePath(), tr("certificate file")))
         fRet = m_pPkcs12->cert2Pem(certificateFilenamePath());
      else
         fRet = true;

      if (fRet)
      {
         if (checkIfFileExistAndConfirmOverwrite(privateKeyFilenamePath(), tr("private key file")))
            fRet = m_pPkcs12->privateKey2Pem(privateKeyFilenamePath(), m_Widget.m_pPrivateKeyPassphraseEdit->text());
      }

      if (fRet && m_pPkcs12->caCerts() > 0)
      {
         if (checkIfFileExistAndConfirmOverwrite(caCertificateFilenamePath(), tr("root certificate file")))
            fRet = (m_pPkcs12->caChain2Pem(caCertificateFilenamePath()) == m_pPkcs12->caCerts());
      }
   }

   return(fRet);
}

void CertificateImportDialog::showError()
{
   m_Widget.m_pInfoTextEdit->clear();
   m_Widget.m_pInfoTextEdit->insertHtml("<b>" + tr("Error:") + "</b><br>");
   m_Widget.m_pInfoTextEdit->insertHtml("<div style='color:red'>" + m_pPkcs12->error() + "</div>");
}

bool CertificateImportDialog::checkIfFileExistAndConfirmOverwrite(const QString& strFilenamePath, const QString& strType) const
{
   bool fRet(true);

   QDir dir(strFilenamePath);
   const QFile file(strFilenamePath);

   if (file.exists())
   {
      const QString strText(tr("A") + " " + strType + " " + "named" + " \"" + dir.dirName() + "\" " + tr("already exists.  Do you want to replace it?"));
      dir.cdUp();
      const QString strInformativeText(tr("The") + " " + strType + " " + tr("already exists in") + " \"" + dir.path() + "\" " + tr(". Replacing it will overwrite its contents."));

      QMessageBox msgBox;
      msgBox.setWindowTitle(tr("Importing certificates ..."));
      msgBox.setText(strText);
      msgBox.setInformativeText(strInformativeText);
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      msgBox.setDefaultButton(QMessageBox::No);

      if (msgBox.exec() != QMessageBox::Yes)
         fRet = false;
   }

   return(fRet);
}
