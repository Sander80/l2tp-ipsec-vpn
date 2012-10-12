/*
 * $Id: SmartCardObjectsDialog.cpp 151 2012-08-03 16:42:07Z wejaeger $
 *
 * File:   SmartCardObjectsDialog.cpp
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
#include <QMessageBox>

#include "SmartCardObjectsDialog.h"

SmartCardObjectsDialog::SmartCardObjectsDialog(SmartCardObjectListModel::ObjectType objectType, QWidget* pParent) : QDialog(pParent), m_pModel(new SmartCardObjectListModel(objectType))
{
   m_Widget.setupUi(this);
   m_Widget.m_pSmartCardObjectsListView->setModel(m_pModel);
}

SmartCardObjectsDialog::~SmartCardObjectsDialog()
{
   delete m_pModel;
}

const QString SmartCardObjectsDialog::selectedItem() const
{
   QString strItem;

   const QModelIndex currentIndex(m_Widget.m_pSmartCardObjectsListView->currentIndex());
   if (currentIndex.isValid())
      strItem = m_pModel->data(currentIndex, Qt::UserRole).toString();

   return(strItem);
}

const QString SmartCardObjectsDialog::selectedUserName() const
{
   QString strUserName;

   const QModelIndex currentIndex(m_Widget.m_pSmartCardObjectsListView->currentIndex());
   if (currentIndex.isValid())
      strUserName = m_pModel->data(currentIndex, Qt::UserRole + 1).toString();

   return(strUserName);
}

void SmartCardObjectsDialog::accept()
{
   if (m_pModel->objectType() == SmartCardObjectListModel::Certificate)
   {
      const QModelIndex currentIndex(m_Widget.m_pSmartCardObjectsListView->currentIndex());

      if (currentIndex.isValid())
      {
         if (m_pModel->storeCert(currentIndex))
            QDialog::accept();
         else
            QMessageBox::critical(NULL, windowTitle(), tr("Failed to write certificate file '%1'.").arg(selectedItem()));
      }
   }
   else
      QDialog::accept();
}

