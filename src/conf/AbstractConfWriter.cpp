/*
 * $Id: AbstractConfWriter.cpp 90 2011-04-22 14:33:35Z werner $
 *
 * File:   AbstractConfWriter.cpp
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

#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>
#include "AbstractConfWriter.h"
#include "VPNControlTask.h"

static const char* const FILENAME = "FILENAME";
static const char* const CREATIONDATE = "CREATIONDATE";
static const char* const APPNAME = "APPNAME";
static const char* const APPVERSION = "APPVERSION";
static const char* const APPPFILEPATH = "APPPFILEPATH";

AbstractConfWriter::AbstractConfWriter(const QString& strTemplateKey, const QString& strWriteTo, FileType type) :
   m_strTemplateKey(strTemplateKey), m_strWriteTo(strWriteTo), m_Type(type),
   m_strInstance(QString("")), m_strFileName(strWriteTo), m_pDictionary(NULL)
{
   ctemplate::Template::StringToTemplateCache(strTemplateKey.toStdString(), readTemplate(strTemplateKey).toStdString());
}

AbstractConfWriter::~AbstractConfWriter()
{
   if (m_pDictionary)
      delete m_pDictionary;
}

const QString& AbstractConfWriter::write()
{
   m_strLastErrorMsg.clear();
   newDictionary();

   fill();
   save();

   return(m_strLastErrorMsg);
}

const QString& AbstractConfWriter::instance() const
{
   return(m_strInstance);
}

void AbstractConfWriter::setInstance(const QString& strInstance)
{
   m_strInstance = strInstance.isNull() ? "" : strInstance;

   const QFileInfo fileInfo(m_strWriteTo);
   m_strFileName = m_strInstance.trimmed().isEmpty() ? m_strWriteTo : fileInfo.path() + "/" + m_strInstance + (fileInfo.fileName().isEmpty() ? "" : "." + fileInfo.fileName());
}

const QString& AbstractConfWriter::fileName() const
{
   return(m_strFileName);
}

void AbstractConfWriter::addErrorMsg(const QString& strErrorMsg)
{
   m_strLastErrorMsg.append(strErrorMsg + '\n');
}

void AbstractConfWriter::save()
{
   dictionary()->SetValue(FILENAME, fileName().toAscii().constData());
   dictionary()->SetValue(CREATIONDATE, QDateTime::currentDateTime().toString().toAscii().constData());
   dictionary()->SetValue(APPNAME, QCoreApplication::instance()->applicationName().toAscii().constData());
   dictionary()->SetValue(APPVERSION, QCoreApplication::instance()->applicationVersion().toAscii().constData());
   dictionary()->SetValue(APPPFILEPATH, QCoreApplication::instance()->applicationFilePath().toAscii().constData());

   std::string strOut;
   ctemplate::Template* const pTpl = ctemplate::Template::GetTemplate(templateKey().toAscii().constData(), ctemplate::DO_NOT_STRIP);

   if (pTpl)
   {
      if (pTpl->Expand(&strOut, dictionary()))
      {
   //   ctemplate::ExpandTemplate(key().toAscii().constData(), ctemplate::DO_NOT_STRIP, dictionary(), &strOut);

         QFile outFile(fileName());
         QDir outFileDir(QFileInfo(outFile).absoluteDir());

         bool fOk = true;
         if (!outFileDir.exists())
         {
            const QString strDirName(outFileDir.dirName());
            outFileDir.cdUp();
            fOk = outFileDir.mkpath(strDirName);
         }

         if (fOk)
         {
//            if (outFile.exists())
//               fOk = outFile.copy(fileName() + "." + QDateTime::currentDateTime().toString("yyyyMMddhhmmss").toAscii().constData() + ".~");

            if (fOk)
            {
               if (outFile.open(QIODevice::WriteOnly | QIODevice::Text))
               {
                  switch (m_Type)
                  {
                     case EXECUTABLE:
                        outFile.setPermissions(outFile.permissions() | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther);
                        break;

                     case SECRET:
                        outFile.setPermissions(QFile::ReadOwner | QFile::WriteOwner);
                        break;

                     default:
                        ;
                  }

                  QTextStream out(&outFile);
                  out << strOut.data();
                  outFile.close();
               }
               else
                  addErrorMsg(QObject::tr("Failed to open configuration file '%1'.").arg(outFile.fileName()));
            }
            else
               addErrorMsg(QObject::tr("Failed to backup file '%1'.").arg(outFile.fileName()));
         }
         else
            addErrorMsg(QObject::tr("Failed to create directory '%1'.").arg(outFileDir.absolutePath()));
      }
      else
         addErrorMsg(QObject::tr("Failed to expand template '%1'.").arg(templateKey()));
   }
   else
      addErrorMsg(QObject::tr("Failed to get template '%1'.").arg(templateKey()));
}

QString AbstractConfWriter::readTemplate(const QString& strKey)
{
   QString strText;
   QFile templateFile(":/templates/" + strKey + ".tpl");
   if (templateFile.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      char acBuf[1024];

      while (!templateFile.atEnd())
      {
         const int iRead = templateFile.read(acBuf,sizeof(acBuf));
         if (iRead > 0)
         {
            acBuf[iRead] = '\0';
            strText.append(acBuf);
         }
         else if (iRead == -1)
         {
            addErrorMsg(QObject::tr("A error occurred while reading template file '%1'.").arg(templateFile.fileName()));
            break;
         }
      }
      templateFile.close();
   }
   else
      addErrorMsg(QObject::tr("Failed to open template file '%1'.").arg(templateFile.fileName()));

   return(strText);
}

void AbstractConfWriter::newDictionary()
{
   if (m_pDictionary)
      delete m_pDictionary;

   m_pDictionary = new ctemplate::TemplateDictionary(m_strTemplateKey.toAscii().constData());
}
