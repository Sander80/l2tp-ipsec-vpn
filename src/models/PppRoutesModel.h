/*
 * $Id: PppRoutesModel.h 165 2017-12-30 14:12:45Z wejaeger $
 *
 * File:   PppRoutesModel.h
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 1:17 PM
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

#ifndef PPPROUTESMODEL_H
#define	PPPROUTESMODEL_H

#include <QAbstractTableModel>
#include "settings/ConnectionSettings.h"

class PppRoutesModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        explicit PppRoutesModel(const QString& strConnectionName, const bool fIsPPPRoute, QObject* pParent = 0);
        virtual ~PppRoutesModel();

        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        bool setData(const QModelIndex& index, const QVariant& value, int iRole = Qt::EditRole);
        QVariant data(const QModelIndex& index, int iRole = Qt::DisplayRole) const;
        QVariant headerData(int iSection, Qt::Orientation orientation, int iRole = Qt::DisplayRole) const;
        Qt::ItemFlags flags(const QModelIndex& index) const;
        bool addRow();
        bool removeRow(int iRow);

    private:
        PppRoutesModel(const PppRoutesModel& orig);
        PppRoutesModel& operator=(const PppRoutesModel& orig);

        const bool m_fIsPPPRoute;
        const PppIpSettings m_PppIpSettings;
};

#endif	/* PPPROUTESMODEL_H */

