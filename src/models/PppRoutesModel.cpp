/*
 * $Id: PppRoutesModel.cpp 165 2017-12-30 14:12:45Z wejaeger $
 *
 * File:   PppRoutesModel.cpp
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 1:16 PM
 *
 * Copyright 2010 Werner Jaeger.
 *
 * Upgraded and maintained since 2020 by Alexander Smirnov.
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

PppRoutesModel::PppRoutesModel(const QString& strConnectionName, const bool fIsPPPRoute, QObject* pParent) : QAbstractTableModel(pParent), m_fIsPPPRoute(fIsPPPRoute), m_PppIpSettings(ConnectionSettings().pppSettings(strConnectionName).ipSettings())
{
}

PppRoutesModel::~PppRoutesModel()
{
}

int PppRoutesModel::rowCount(const QModelIndex& /* parent */) const
{
    return(m_fIsPPPRoute ? m_PppIpSettings.routes() : m_PppIpSettings.noRoutes());
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
                    fRet = m_fIsPPPRoute ? m_PppIpSettings.setRouteAddress(index.row(), value.toString()) : m_PppIpSettings.setNoRouteAddress(index.row(), value.toString());
                    break;

                case 1:
                    fRet = m_fIsPPPRoute ? m_PppIpSettings.setRouteNetmask(index.row(), value.toString()) : m_PppIpSettings.setNoRouteNetmask(index.row(), value.toString());
                    break;

                case 2:
                    fRet = m_fIsPPPRoute ? m_PppIpSettings.setRouteComment(index.row(), value.toString()) : m_PppIpSettings.setNoRouteComment(index.row(), value.toString());
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
                    ret = m_fIsPPPRoute ? m_PppIpSettings.routeAddress(index.row()) : m_PppIpSettings.noRouteAddress(index.row());
                    break;

                case 1:
                    ret = m_fIsPPPRoute ? m_PppIpSettings.routeNetmask(index.row()) : m_PppIpSettings.noRouteNetmask(index.row());
                    break;

                case 2:
                    ret = m_fIsPPPRoute ? m_PppIpSettings.routeComment(index.row()) : m_PppIpSettings.noRouteComment(index.row());
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

    const int iRow =  m_fIsPPPRoute ? m_PppIpSettings.routes() : m_PppIpSettings.noRoutes();
    beginInsertRows(QModelIndex(), iRow, iRow);
    fRet =  m_fIsPPPRoute ? m_PppIpSettings.addRoute() :  m_PppIpSettings.addNoRoute();
    endInsertRows();

    return(fRet);
}

bool PppRoutesModel::removeRow(int iRow)
{
    bool fRet;

    beginRemoveRows(QModelIndex(), iRow, iRow);
    fRet =  m_fIsPPPRoute ? m_PppIpSettings.removeRoute(iRow) : m_PppIpSettings.removeNoRoute(iRow);
    endRemoveRows();

    return(fRet);

}

