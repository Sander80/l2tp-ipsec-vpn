/*
 * $Id: IpSettingsDialog.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   IpSettingsDialog.h
 * Author: Werner Jaeger
 *
 * Created on August 20, 2010, 9:59 AM
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

#ifndef _IPSETTINGSDIALOG_H
#define	_IPSETTINGSDIALOG_H

#include "ui_IpSettingsDialog.h"

class IpSettingsDialog : public QDialog
{
   Q_OBJECT

public:
   IpSettingsDialog(const QString& strConnectionName, QWidget* pParent = 0);
   virtual ~IpSettingsDialog();

private slots:
   void onRouteSettings() const;
   void onHelpRequested() const;
   void accept();

private:
   IpSettingsDialog(const IpSettingsDialog& orig);
   IpSettingsDialog& operator=(const IpSettingsDialog& orig);

   void readSettings() const;
   bool writeSettings() const;

   Ui::IpSettingsDialog m_Widget;

   const QString m_strConnectionName;
};

#endif	/* _IPSECSETTINGSDIALOG_H */
