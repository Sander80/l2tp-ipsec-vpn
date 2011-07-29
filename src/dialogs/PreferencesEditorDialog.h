/*
 * $Id: PreferencesEditorDialog.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   PreferencesEditorDialog.h
 * Author: wejaeger
 *
 * Created on February 4, 2011, 11:21 AM
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

#ifndef _PREFERENCESEDITORDIALOG_H
#define	_PREFERENCESEDITORDIALOG_H

#include "ui_PreferencesEditorDialog.h"

class PreferencesEditorDialog : public QDialog
{
   Q_OBJECT

public:
   explicit PreferencesEditorDialog(QWidget* pParent = 0);
   virtual ~PreferencesEditorDialog();

private slots:
   void onEnginePath();
   void onPkcs11Path();
   void onHelpRequested() const;
   void accept();
   void readSettings() const;
   bool writeSettings() const;

private:
   PreferencesEditorDialog(const PreferencesEditorDialog& orig);
   PreferencesEditorDialog& operator=(const PreferencesEditorDialog& orig);

   Ui::PreferencesEditorDialog m_Widget;
};

#endif	/* _PREFERENCESEDITORDIALOG_H */
