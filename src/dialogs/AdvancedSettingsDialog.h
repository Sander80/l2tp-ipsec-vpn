/*
 * $Id: AdvancedSettingsDialog.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   AdvancedSettingsDialog.h
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

#ifndef _ADVANCEDSETTINGSDIALOG_H
#define	_ADVANCEDSETTINGSDIALOG_H

#include "ui_AdvancedSettingsDialog.h"

class AdvancedSettingsDialog : public QDialog
{
   Q_OBJECT

public:
   AdvancedSettingsDialog(const QString& strConnectionName, QWidget* pParent = 0);
   virtual ~AdvancedSettingsDialog();
private slots:
   void onHelpRequested() const;
   void accept();

private:
   AdvancedSettingsDialog(const AdvancedSettingsDialog& orig);
   AdvancedSettingsDialog& operator=(const AdvancedSettingsDialog& orig);

   void readSettings() const;
   bool writeSettings() const;

   Ui::AdvancedSettingsDialog m_Widget;

   const QString m_strConnectionName;
};

#endif	/* _ADVANCEDSETTINGSDIALOG_H */
