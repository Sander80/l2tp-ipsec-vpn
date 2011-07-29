/*
 * $Id: SmartCardState.h 35 2011-01-28 01:43:49Z werner $
 *
 * File:   SmartCardState.h
 * Author: Werner Jaeger
 *
 * Created on July 16, 2010, 10:31 AM
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

#ifndef SMARTCARDSTATE_H
#define	SMARTCARDSTATE_H

#include <QObject>

class SmartCardInsertWaitTask;
class QMessageBox;

class SmartCardState : public QObject
{
   Q_OBJECT

public:
   explicit SmartCardState(QObject* pParent = 0);
   virtual ~SmartCardState();

   int readersAvailable();
   int waitForCardPresent();

signals:
   void cardInserted();

private slots:
   void waitTaskFinished();

private:
   SmartCardState(const SmartCardState& orig);
   SmartCardState& operator=(const SmartCardState& orig);

   SmartCardInsertWaitTask* m_pWaitTask;
   QMessageBox* m_pMsgBox;
};

#endif	/* SMARTCARDSTATE_H */

