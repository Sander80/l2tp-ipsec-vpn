/*
 * $Id: ConnectionsModel.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   ConnectionsModel.cpp
 * Author: Werner Jaeger
 *
 * Created on July 18, 2010, 5:30 PM
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

#include "ConnectionsModel.h"
#include "ConnectionState.h"
#include "settings/ConnectionSettings.h"
#include "dialogs/ConnectionEditorDialog.h"

ConnectionsModel::ConnectionsModel(QObject* pParent) : QAbstractTableModel(pParent), m_pSettings(new ConnectionSettings())
{
}

ConnectionsModel::~ConnectionsModel()
{
   delete m_pSettings;
}

bool ConnectionsModel::isWriteable() const
{
   return(m_pSettings->isWriteable());
}

int ConnectionsModel::rowCount(const QModelIndex& /* parent */) const
{
   return(m_pSettings->connections());
}

int ConnectionsModel::columnCount(const QModelIndex& /* parent */) const
{
   return(1);
}

QVariant ConnectionsModel::data(const QModelIndex& index, int iRole) const
{
   QVariant ret;

   if (index.isValid())
   {
      if (iRole == Qt::DisplayRole)
         ret = m_pSettings->connection(index.row());
      else if (iRole == Qt::TextAlignmentRole)
         ret = int(Qt::AlignLeft | Qt::AlignVCenter);
   }

   return(ret);
}

QVariant ConnectionsModel::headerData(int iSection, Qt::Orientation orientation, int iRole) const
{
   QVariant ret;

   if (iRole == Qt::DisplayRole && iSection == 0 && orientation == Qt::Horizontal)
      ret = tr("Name");

   return(ret);
}

ConnectionsModel::Result ConnectionsModel::addRow(const QString& strName, const QModelIndex& parent)
{
   Result result(ConnectionsModel::Ok);

   const int iRow = m_pSettings->connections();
   beginInsertRows(parent, iRow, iRow);
   switch (m_pSettings->addConnection(strName))
   {
      case ConnectionSettings::DuplicateName:
         result = ConnectionsModel::DuplicateName;
         break;

      case ConnectionSettings::InvalidName:
         result = ConnectionsModel::InvalidName;
         break;

      case ConnectionSettings::ReadOnly:
         result = ConnectionsModel::ReadOnly;
         break;

      case ConnectionSettings::Ok:
         result = ConnectionsModel::Ok;
         break;
   }
   endInsertRows();

   return(result);
}

bool ConnectionsModel::removeRow(int iRow, const QModelIndex& parent)
{
   bool fRet;

   beginRemoveRows(parent, iRow, iRow);
   fRet = m_pSettings->removeConnection(iRow);
   endRemoveRows();

   return(fRet);
}
