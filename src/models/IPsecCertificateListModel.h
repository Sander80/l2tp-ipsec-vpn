/*
 * $Id: IPsecCertificateListModel.h 69 2011-04-12 04:33:22Z werner $
 *
 * File:   IPsecCertificateListModel.h
 * Author: Werner Jaeger
 *
 * Created on July 27, 2010, 1:50 PM
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

#ifndef IPSECCERTIFICATELISTMODEL_H
#define	IPSECCERTIFICATELISTMODEL_H

#include <QAbstractListModel>

class QDir;

class IPsecCertificateListModel : public QAbstractListModel
{
   Q_OBJECT

public:
   explicit IPsecCertificateListModel(QObject* pParent = 0);
   virtual ~IPsecCertificateListModel();

   void refresh();
   int rowCount(const QModelIndex& parent = QModelIndex()) const;
   QVariant data(const QModelIndex& index, int iRole = Qt::DisplayRole) const;
   bool setData(const QModelIndex& index, const QVariant& qvalue, int iRole = Qt::EditRole);
   Qt::ItemFlags flags(const QModelIndex& index) const;

   const QString& selectedCertificateFileName() const;
   bool select(const QString& strCertificateFileName);

private:
   IPsecCertificateListModel(const IPsecCertificateListModel& orig);
   IPsecCertificateListModel& operator=(const IPsecCertificateListModel& orig);

   int indexOf(const QString& strCertificateFileName) const;
   QString value(int i) const;

   QDir* const m_pCertificateDirectory;
   QString m_strSelected;

};

#endif	/* IPSECCERTIFICATELISTMODEL_H */

