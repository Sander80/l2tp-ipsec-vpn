/*
 * $Id: CertificateImportDialog.h 129 2012-04-07 10:15:46Z wejaeger $
 *
 * File:   CertificateImportDialog.h
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

#ifndef _CERTIFICATEIMPORTDIALOG_H
#define	_CERTIFICATEIMPORTDIALOG_H

#include "ui_CertificateImportDialog.h"

class Pkcs12;
class QString;

class CertificateImportDialog : public QDialog
{
   Q_OBJECT

public:
   CertificateImportDialog(QWidget* pParent = 0);
   virtual ~CertificateImportDialog();

   const QString certificateFilename() const;
   const QString certificateFilenamePath() const;
   const QString privateKeyFilename() const;
   const QString privateKeyFilenamePath() const;
   const QString caCertificateFilename() const;
   const QString caCertificateFilenamePath() const;
   const QString passPhrase() const;
   bool useAsAuthenticationCertificate() const;

private slots:
   void onHelpRequested() const;
   void onCertificate();
   void onValidateInput() const;
   void accept();

private:
   CertificateImportDialog(const CertificateImportDialog& orig);
   CertificateImportDialog& operator=(const CertificateImportDialog& orig);

   bool isInputValid() const;
   bool writePems() const;
   void showError();

   bool checkIfFileExistAndConfirmOverwrite(const QString& strFilenamePath, const QString& strType) const;

   Ui::CertificateImportDialog m_Widget;

   Pkcs12* m_pPkcs12;
};

#endif	/* _CERTIFICATEIMPORTDIALOG_H */
