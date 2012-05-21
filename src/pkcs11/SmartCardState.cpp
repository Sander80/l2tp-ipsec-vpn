/*
 * $Id: SmartCardState.cpp 133 2012-05-02 09:13:26Z wejaeger $
 *
 * File:   SmartCardState.cpp
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

#include <QCoreApplication>
#include <qglobal.h>
#include <QMessageBox>
#include <QPushButton>

#include "pkcs11/Pkcs11.h"
#include "SmartCardState.h"
#include "SmartCardInsertWaitTask.h"

SmartCardState::SmartCardState(QObject* pParent) : QObject(pParent), m_pWaitTask(NULL),
   m_pMsgBox(new QMessageBox(QMessageBox::Information, QCoreApplication::instance()->applicationName(), QObject::tr("Please insert your smart card ..."), QMessageBox::Cancel))
{
}

SmartCardState::~SmartCardState()
{
   if (m_pWaitTask)
      delete m_pWaitTask;

   if (m_pMsgBox)
      delete m_pMsgBox;
}

int SmartCardState::readersAvailable()
{
   int iRet(0);

   if (Pkcs11::loaded())
   {
      Pkcs11 p11;

      iRet = p11.slotsAvailable();
   }

   return(iRet);
}

int SmartCardState::waitForCardPresent()
{
   int iRet(0);

   if (Pkcs11::loaded())
   {
      Pkcs11 p11;
      iRet = p11.slotList().count();

      if (iRet == 0)
      {
         if (m_pWaitTask != NULL)
            delete m_pWaitTask;

         m_pWaitTask = new SmartCardInsertWaitTask(p11);
         connect(m_pWaitTask, SIGNAL(finished()), this, SLOT(waitTaskFinished()));
         m_pWaitTask->start();

         iRet = m_pMsgBox->exec();
         if(iRet == QMessageBox::Cancel)
         {
            m_pWaitTask->stop();
            iRet = 0;
         }
      }
   }

   return(iRet);
}

void SmartCardState::waitTaskFinished()
{
   const int iRet(m_pWaitTask->result());
   m_pMsgBox->done(iRet);
}
