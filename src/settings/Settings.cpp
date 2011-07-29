/*
 * $Id: Settings.cpp 47 2011-02-13 02:40:16Z werner $
 *
 * File:   Settings.cpp
 * Author: Werner Jaeger
 *
 * Created on August 9, 2010, 11:36 AM
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

#include <QStringList>
#include <QCoreApplication>
#include <QFileInfo>

#include "Settings.h"

Settings::Settings() : m_Settings(configureQSettings()), m_PreviouslyLastModified(lastModified())
{
}

Settings::~Settings()
{
}

bool Settings::isWriteable() const
{
   return(qSettings()->isWritable());
}

void Settings::clearChanged()
{
   m_PreviouslyLastModified = lastModified();
}

bool Settings::hasChanged() const
{
   return(m_PreviouslyLastModified < lastModified());
}

/**
 * Unfortunately QSettings does not provide a method to remove array elements.
 *
 * So, we have to read in all keys and values of the named array section, delete
 * the whole array section and write it out again, omitting the deleted
 * row. We also have to take care to adapt the array indices after the deleted
 * row and to write finally the new size entry.
 */
bool Settings::removeArrayItem(const QString& strArrayName, int iIndex) const
{
   bool fRet = false;

   qSettings()->beginReadArray(strArrayName);
   const QStringList keys(qSettings()->allKeys());
   QStringList values;

   if (iIndex < keys.size())
   {
      for (int i = 0; i < keys.size(); i++)
         values.insert(i, qSettings()->value(keys.at(i)).toString());
      qSettings()->endArray();

      qSettings()->beginGroup(strArrayName);
      qSettings()->remove("");

      const QChar cIndex2Remove(iIndex + 1 + 48);
      QChar cIndex2Write;
      for (int i = 0; i < keys.size(); i++)
      {
         const QString& strKey = keys.at(i);
         const QChar cIndex2Read(strKey.at(0));
         if (cIndex2Read.isDigit())
         {
            if (cIndex2Read != cIndex2Remove)
            {
               cIndex2Write = cIndex2Read > cIndex2Remove ? QChar(cIndex2Read.digitValue() - 1 + 48) : QChar(cIndex2Read.digitValue() + 48);
               qSettings()->setValue(cIndex2Write + strKey.mid(1), values.at(i));
            }
         }
      }
      qSettings()->setValue("size", QString(cIndex2Write));
      qSettings()->endGroup();
      fRet = true;
   }

   return(fRet);
}

QDateTime Settings::lastModified() const
{
   return(QFileInfo(qSettings()->fileName()).lastModified());
}

QSettings* Settings::configureQSettings()
{
   return(new QSettings(QSettings::SystemScope, QCoreApplication::organizationName(), QCoreApplication::applicationName()));
}

