/*
 * $Id: Settings.h 47 2011-02-13 02:40:16Z werner $
 *
 * File:   Settings.h
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

#ifndef SETTINGS_H
#define	SETTINGS_H

#include <QSharedPointer>
#include <QSettings>
#include <QDateTime>

class Settings
{
public:
   bool isWriteable() const;
   void clearChanged();
   bool hasChanged() const;

protected:
   Settings();
   virtual ~Settings();

   QSettings* qSettings() const { return(m_Settings.data()); }

   bool removeArrayItem(const QString& strArrayName, int iIndex) const;

private:
   Settings& operator=(const Settings& orig);

   QDateTime lastModified() const;

   static QSettings* configureQSettings();

   QSharedPointer<QSettings> const m_Settings;

   QDateTime m_PreviouslyLastModified;
};

#endif	/* SETTINGS_H */

