/*
 * $Id: ErrorEx.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   ErrorEx.h
 * Author: Werner Jaeger
 *
 * Created on July 31, 2010, 4:30 PM
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

#ifndef ERROREX_H
#define	ERROREX_H

#include <QObject>
#include <QString>

class ErrorEx
{
public:
   ErrorEx(QString strText, QString strClassName = "")
   {
      m_strMsg = strText;
      if (!strClassName.isEmpty())
         m_strMsg += " (" + strClassName + ")";
   }

   ErrorEx(const ErrorEx& errorEx)
   {
      m_strMsg = errorEx.m_strMsg;
   }

   virtual ~ErrorEx() {}

   void appendString(QString strText)
   {
      m_strMsg = m_strMsg + " " + strText;
   }

   QString getString() const
   {
      return(m_strMsg);
   }

   const char* getCString() const
   {
      return(m_strMsg.toAscii());
   }

   bool isEmpty() const
   {
      return(m_strMsg.isEmpty());
   }

   static void checkOutOfMemory(const void* pVoid)
   {
      if (!pVoid) throw ErrorEx(QObject::tr("Out of Memory"));
   }

private:
   ErrorEx& operator=(const ErrorEx& orig);

	QString m_strMsg;
};

#endif	/* ERROREX_H */

