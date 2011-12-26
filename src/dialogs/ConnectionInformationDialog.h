/*
 * $Id: ConnectionInformationDialog.h 112 2011-12-26 03:00:40Z werner $
 *
 * File:   ConnectionInformationDialog.h
 * Author: Werner Jaeger
 *
 * Created on July 18, 2010, 3:09 PM
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

#ifndef CONNECTIONINFORMATIONDIALOG_H
#define	CONNECTIONINFORMATIONDIALOG_H

#include "ui_ConnectionInformationDialog.h"

class ConnectionState;

class ConnectionInformationDialog : public QDialog
{
   Q_OBJECT

public:
   explicit ConnectionInformationDialog(QWidget* pParent = 0);
   virtual ~ConnectionInformationDialog();

   void clearLog() { m_Widget.m_pTextEdit->clear(); }
   void appendLogPlainText(const char* pcText);
   void appendLogColorText(const QColor& color, const char* pcText);

public slots:
   void onConectionStateChanged(const ConnectionState* pNewState, const QString& strConnectionName);

private slots:
   void onStatistics() const;

private:
   ConnectionInformationDialog(const ConnectionInformationDialog& orig);
   ConnectionInformationDialog& operator=(const ConnectionInformationDialog& orig);

   Ui::ConnectionInformationDialog m_Widget;
};

#endif	/* CONNECTIONINFORMATIONDIALOG_H */

