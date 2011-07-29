/*
 * $Id: InterfaceStatisticsDialog.h 67 2011-04-07 15:38:50Z werner $
 *
 * File:   InterfaceStatisticsDialog.h
 * Author: wejaeger
 *
 * Created on April 7, 2011, 11:52 AM
 *
 * Copyright 2010-2011 Werner Jaeger.
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

#ifndef _INTERFACESTATISTICSDIALOG_H
#define	_INTERFACESTATISTICSDIALOG_H

#include <QString>

#include "ui_InterfaceStatisticsDialog.h"

class QTimer;

class InterfaceStatisticsDialog : public QDialog
{
   Q_OBJECT

public:
   InterfaceStatisticsDialog(const QString& strInterfaceName, QWidget* pParent = 0);
   virtual ~InterfaceStatisticsDialog();

private slots:
   void onUpdateStatistic() const;

private:
   InterfaceStatisticsDialog(const InterfaceStatisticsDialog& orig);
   InterfaceStatisticsDialog& operator=(const InterfaceStatisticsDialog& orig);

   const QString connectionTime() const;

   static const QString formatBytes(const long long lBytes);
   static qint64 connectedSince(const QString& strInterfaceName);

   const QString m_strInterfaceName;
   const uint m_iConectedSince;

   QTimer* const m_pTimer;

   Ui::InterfaceStatisticsDialog m_Widget;
};

#endif	/* _INTERFACESTATISTICSDIALOG_H */
