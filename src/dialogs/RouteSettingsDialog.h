/*
 * $Id: RouteSettingsDialog.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   RouteSettingsDialog.h
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 4:17 PM
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

#ifndef _ROUTESETTINGSDIALOG_H
#define	_ROUTESETTINGSDIALOG_H

#include "ui_RouteSettingsDialog.h"

class PppRoutesModel;

class RouteSettingsDialog : public QDialog
{
   Q_OBJECT

public:
   explicit RouteSettingsDialog(const QString& strConnectionName, QWidget* pParent = 0);
   virtual ~RouteSettingsDialog();

private slots:
   void addRoute() const;
   void removeRoute() const;
   void onHelpRequested() const;
   void accept();

private:
   RouteSettingsDialog(const RouteSettingsDialog& orig);
   RouteSettingsDialog& operator=(const RouteSettingsDialog& orig);

   void readSettings() const;
   bool writeSettings() const;

   Ui::RouteSettingsDialog m_Widget;

   const QString m_strConnectionName;
   PppRoutesModel* m_pRoutesModel;
};

#endif	/* _ROUTESETTINGSDIALOG_H */
