/*
 * $Id: PppRoutesModel.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   PppRoutesModel.cpp
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 1:16 PM
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

#include "PppRoutesModel.h"

PppRoutesModel::PppRoutesModel(const QString& strConnectionName, QObject* pParent) : QAbstractTableModel(pParent), m_PppIpSettings(ConnectionSettings().pppSettings(strConnectionName).ipSettings())
{
}

PppRoutesModel::~PppRoutesModel()
{
}

int PppRoutesModel::rowCount(const QModelIndex& /* parent */) const
{
   return(m_PppIpSettings.routes());
}

int PppRoutesModel::columnCount(const QModelIndex& /* parent */) const
{
   return(3);
}

bool PppRoutesModel::setData(const QModelIndex& index, const QVariant& value, int iRole)
{
   bool fRet = false;

   if (index.isValid())
   {
      if (iRole == Qt::EditRole)
      {
         switch (index.column())
         {
            case 0:
               fRet = m_PppIpSettings.setRouteAddress(index.row(), value.toString());
               break;

            case 1:
               fRet = m_PppIpSettings.setRouteNetmask(index.row(), value.toString());
               break;

            case 2:
               fRet = m_PppIpSettings.setRouteComment(index.row(), value.toString());
               break;
         }
      }

      emit dataChanged(index, index);
      fRet = true;
   }

   return(fRet);
}

QVariant PppRoutesModel::data(const QModelIndex& index, int iRole) const
{
   QVariant ret;

   if (index.isValid())
   {
      if (iRole == Qt::DisplayRole || iRole == Qt::EditRole)
      {
         switch (index.column())
         {
            case 0:
               ret = m_PppIpSettings.routeAddress(index.row());
               break;

            case 1:
               ret = m_PppIpSettings.routeNetmask(index.row());
               break;

            case 2:
               ret = m_PppIpSettings.routeComment(index.row());
               break;
         }
      }
      else if (iRole == Qt::TextAlignmentRole)
         ret = int(Qt::AlignLeft | Qt::AlignVCenter);
   }

   return(ret);
}

QVariant PppRoutesModel::headerData(int iSection, Qt::Orientation orientation, int iRole) const
{
   QVariant ret;

   if (iRole == Qt::DisplayRole && orientation == Qt::Horizontal)
   {
      switch (iSection)
      {
         case 0:
            ret = tr("Address");
            break;

         case 1:
            ret = tr("Netmask");
            break;

         case 2:
            ret = tr("Comment");
            break;
      }
   }

   return(ret);
}

Qt::ItemFlags PppRoutesModel::flags(const QModelIndex& index) const
{
   return(QAbstractTableModel::flags(index) | Qt::ItemIsEditable);
}

bool PppRoutesModel::addRow()
{
   bool fRet = true;

   const int iRow = m_PppIpSettings.routes();
   beginInsertRows(QModelIndex(), iRow, iRow);
   fRet = m_PppIpSettings.addRoute();
   endInsertRows();

   return(fRet);
}

bool PppRoutesModel::removeRow(int iRow)
{
   bool fRet;

   beginRemoveRows(QModelIndex(), iRow, iRow);
   fRet = m_PppIpSettings.removeRoute(iRow);
   endRemoveRows();

   return(fRet);

}

