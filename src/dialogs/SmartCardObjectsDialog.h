/*
 * $Id: SmartCardObjectsDialog.h 151 2012-08-03 16:42:07Z wejaeger $
 *
 * File:   SmartCardObjectsDialog.h
 * Author: Werner Jaeger
 *
 * Created on August 2, 2010, 6:56 PM
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

#ifndef _SMARTCARDOBJECTSDIALOG_H
#define	_SMARTCARDOBJECTSDIALOG_H

#include "models/SmartCardObjectListModel.h"
#include "ui_SmartCardObjectsDialog.h"

class SmartCardObjectsDialog : public QDialog
{
   Q_OBJECT

public:
   explicit SmartCardObjectsDialog(SmartCardObjectListModel::ObjectType objectType, QWidget* pParent = 0);
   virtual ~SmartCardObjectsDialog();

   const QString selectedItem() const;
   const QString selectedUserName() const;

private slots:
   void accept();

private:
   SmartCardObjectsDialog(const SmartCardObjectsDialog& orig);
   SmartCardObjectsDialog& operator=(const SmartCardObjectsDialog& orig);

   Ui::SmartCardObjectsDialog m_Widget;

   SmartCardObjectListModel* const m_pModel;
};

#endif	/* _SMARTCARDOBJECTSDIALOG_H */
