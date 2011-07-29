/*
 * $Id: ConnectionsModel.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   ConnectionsModel.h
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

#ifndef CONNECTIONSMODEL_H
#define	CONNECTIONSMODEL_H

#include <QAbstractTableModel>

class ConnectionSettings;

class ConnectionsModel : public QAbstractTableModel
{
   Q_OBJECT

public:
   typedef enum { Ok, InvalidName, DuplicateName, ReadOnly } Result;

   explicit ConnectionsModel(QObject* pParent = 0);
   virtual ~ConnectionsModel();

   bool isWriteable() const;
   int rowCount(const QModelIndex& parent = QModelIndex()) const;
   int columnCount(const QModelIndex& parent = QModelIndex()) const;
   QVariant data(const QModelIndex& index, int iRole = Qt::DisplayRole) const;
   QVariant headerData(int iSection, Qt::Orientation orientation, int iRole = Qt::DisplayRole) const;
   Result addRow(const QString& strName, const QModelIndex& parent = QModelIndex());
   bool removeRow(int iRow, const QModelIndex& parent = QModelIndex());

private:
   ConnectionsModel(const ConnectionsModel& orig);
   ConnectionsModel& operator=(const ConnectionsModel& orig);

   ConnectionSettings* const m_pSettings;
};

#endif	/* CONNECTIONSMODEL_H */

