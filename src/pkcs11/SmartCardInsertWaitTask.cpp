/*
 * $Id: SmartCardInsertWaitTask.cpp 120 2012-03-08 04:57:41Z werner $
 *
 * File:   SmartCardInsertWaitTask.cpp
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

#include "SmartCardInsertWaitTask.h"
#include "pkcs11/Pkcs11.h"

SmartCardInsertWaitTask::SmartCardInsertWaitTask(const Pkcs11& pkcs11) : m_pkcs11(pkcs11), m_iRet(0), m_fStop(false)
{
}

SmartCardInsertWaitTask::~SmartCardInsertWaitTask()
{
}

void SmartCardInsertWaitTask::run()
{
   m_fStop = false;

   if (Pkcs11::loaded())
   {
      do
      {
         m_iRet = m_pkcs11.slotList().count();
         QThread::sleep(1);
      }
      while (m_iRet == 0 && !m_fStop);
   }
}
