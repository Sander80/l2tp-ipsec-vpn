/*
 * $Id: SmartCardInsertWaitTask.h 35 2011-01-28 01:43:49Z werner $
 *
 * File:   SmartCardInsertWaitTask.h
 * Author: Werner Jaeger
 *
 * Created on July 16, 2010, 7:08 PM
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

#ifndef SMARTCARDINSERTWAITTASK_H
#define	SMARTCARDINSERTWAITTASK_H

#include <QThread>

class Pkcs11;

class SmartCardInsertWaitTask : public QThread
{
public:
   SmartCardInsertWaitTask(const Pkcs11& pkcs11);
   virtual ~SmartCardInsertWaitTask();

   void run();
   void stop() { m_fStop = true;  wait(); }

   int result() const { return(m_iRet); }

private:
   SmartCardInsertWaitTask(const SmartCardInsertWaitTask& orig);
   SmartCardInsertWaitTask& operator=(const SmartCardInsertWaitTask& orig);

   const Pkcs11& m_pkcs11;

   int m_iRet;
   volatile bool m_fStop;
};

#endif	/* SMARTCARDINSERTWAITTASK_H */

