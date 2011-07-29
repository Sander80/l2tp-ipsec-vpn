/*
 * $Id: PeerAuthenticationDialog.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   PeerAuthenticationDialog.h
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 11:19 AM
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

#ifndef _PEERAUTHENTICATIONDIALOG_H
#define	_PEERAUTHENTICATIONDIALOG_H

#include "ui_PeerAuthenticationDialog.h"

class PeerAuthenticationDialog : public QDialog
{
   Q_OBJECT

public:
   explicit PeerAuthenticationDialog(const QString& strConnectionName, QWidget* pParent = 0);
   virtual ~PeerAuthenticationDialog();

private slots:
   void readSettings() const;
   bool writeSettings() const;
   void onHelpRequested() const;
   void accept();

private:
   PeerAuthenticationDialog(const PeerAuthenticationDialog& orig);
   PeerAuthenticationDialog& operator=(const PeerAuthenticationDialog& orig);

   Ui::PeerAuthenticationDialog m_Widget;

   const QString m_strConnectionName;
};

#endif	/* _PEERAUTHENTICATIONDIALOG_H */
