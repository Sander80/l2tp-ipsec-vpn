/*
 * $Id: SmartCardObjectListModel.h 151 2012-08-03 16:42:07Z wejaeger $
 *
 * File:   SmartCardObjectListModel.h
 * Author: Werner Jaeger
 *
 * Created on August 2, 2010, 5:11 PM
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

#ifndef SMARTCARDOBJECTLISTMODEL_H
#define	SMARTCARDOBJECTLISTMODEL_H

#include <QList>
#include <QAbstractListModel>

class SmartCardInfo;

class SmartCardObjectListModel : public QAbstractListModel
{
   Q_OBJECT

public:
   typedef enum { Certificate, PublicKey } ObjectType;

   explicit SmartCardObjectListModel(ObjectType objectType);
   virtual ~SmartCardObjectListModel();

   int rowCount(const QModelIndex& parent = QModelIndex()) const;
   QVariant data(const QModelIndex& index, int iRole = Qt::DisplayRole) const;
   bool storeCert(const QModelIndex& index) const;
   const ObjectType& objectType() const { return(m_ObjectType); }

private:
   SmartCardObjectListModel(const SmartCardObjectListModel& orig);
   SmartCardObjectListModel& operator=(const SmartCardObjectListModel& orig);

   QString value(int i) const;
   QString idValue(int i) const;

   void readTokens();

   ObjectType const m_ObjectType;
   QList<SmartCardInfo*>* const m_pSmartCardObjects;
};

#endif	/* SMARTCARDOBJECTLISTMODEL_H */

