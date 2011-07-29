/*
 * $Id: PppDownScriptWriter.cpp 30 2010-11-27 23:22:37Z werner $
 *
 * File:   PppDownScriptWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on August 6, 2010, 1:28 PM
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

#include <ctemplate/template.h>
#include "settings/ConnectionSettings.h"
#include "ConfWriter.h"
#include "PppDownScriptWriter.h"

static const char* const CONN_SECTION = "CONN_SECTION";
static const char* const DEFAULT_GATEWAY_SECTION = "DEFAULT_GATEWAY_SECTION";

static const char* const OBJECTNAME = "OBJECTNAME";
static const char* const GETIPSECINFOLIB = "GETIPSECINFOLIB";
static const char* const GATEWAY = "GATEWAY";
static const char* const IPPARAM = "IPPARAM";

PppDownScriptWriter::PppDownScriptWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo, AbstractConfWriter::EXECUTABLE)
{
}

void PppDownScriptWriter::fill()
{
   dictionary()->SetValue(OBJECTNAME, QCoreApplication::instance()->objectName().toAscii().constData());
   dictionary()->SetValue(GETIPSECINFOLIB, ConfWriter::fileName(ConfWriter::GETIPSECINFO).toAscii().constData());

   const ConnectionSettings settings;
   const int iConnections = settings.connections();

   for (int i = 0; i < iConnections; i++)
   {
      const QString strName(settings.connection(i));

      if (!strName.isEmpty())
      {
         const PppIpSettings ipSetting(settings.pppSettings(strName).ipSettings());
         ctemplate::TemplateDictionary* const pConnection = dictionary()->AddSectionDictionary(CONN_SECTION);

         pConnection->SetValue(IPPARAM, (QCoreApplication::instance()->objectName() + "-" + strName).toAscii().constData());
         pConnection->SetValue(GATEWAY, settings.ipsecSettings(strName).gateway().toAscii().constData());

         if (ipSetting.useDefaultGateway())
            pConnection->AddSectionDictionary(DEFAULT_GATEWAY_SECTION);
      }
      else
         addErrorMsg(QObject::tr("No such connection: '%1'.").arg(strName));
   }
}
