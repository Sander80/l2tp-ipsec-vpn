/*
 * $Id: EapSettingsDialog.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   EapSettingsDialog.h
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

#ifndef _EAPSETTINGSDIALOG_H
#define	_EAPSETTINGSDIALOG_H

#include "ui_EapSettingsDialog.h"

class EapSettingsDialog : public QDialog
{
   Q_OBJECT

public:
   explicit EapSettingsDialog(const QString& strConnectionName, QWidget* pParent = 0);
   virtual ~EapSettingsDialog();

private slots:
   void onUseCertificateRadioButtonToggled(bool fChecked);
   void onCertificate();
   void onPrivateKey();
   void onCaCertificate();
   void readSettings();
   bool writeSettings() const;
   void onHelpRequested() const;
   void accept();

private:
   EapSettingsDialog(const EapSettingsDialog& orig);
   EapSettingsDialog& operator=(const EapSettingsDialog& orig);

   Ui::EapSettingsDialog m_Widget;

   const QString m_strConnectionName;
   QString m_strUserName;
};

#endif	/* _EAPSETTINGSDIALOG_H */
