/*
 * $Id: AbstractConfWriter.h 110 2011-10-22 12:02:21Z werner $
 *
 * File:   AbstractConfWriter.h
 * Author: Werner Jaeger
 *
 * Created on July 23, 2010, 8:43 AM
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

#ifndef ABSTRACTCONFWRITER_H
#define	ABSTRACTCONFWRITER_H

#include <QString>
#include <ctemplate/template.h>

class AbstractConfWriter
{
public:
   const QString& write();
   const QString& instance() const;
   void setInstance(const QString& strInstance);
   const QString& fileName() const;

protected:
   typedef enum { NORMAL, EXECUTABLE, SECRET } FileType;

   AbstractConfWriter(const QString& strTemplateKey, const QString& strWriteTo, FileType type = NORMAL);
   virtual ~AbstractConfWriter();

   const QString& templateKey() const { return(m_strTemplateKey); }
   ctemplate::TemplateDictionary* dictionary() const { return(m_pDictionary); }
   void addErrorMsg(const QString& strErrorMsg);

   virtual void fill() = 0;

private:
   AbstractConfWriter(const AbstractConfWriter& orig);
   AbstractConfWriter& operator=(const AbstractConfWriter& orig);

   void save();

   void readTemplate(const QString& strKey);

   void newDictionary();

   const QString m_strTemplateKey;
   const QString m_strWriteTo;
   const FileType m_Type;
   QString m_strInstance;
   QString m_strFileName;
   ctemplate::TemplateDictionary* m_pDictionary;

   QString m_strLastErrorMsg;

   bool m_fTemplatesInitialized;
};

#endif	/* ABSTRACTCONFWRITER_H */

