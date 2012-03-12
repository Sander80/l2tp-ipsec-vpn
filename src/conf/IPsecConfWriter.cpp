/*
 * $Id: IPsecConfWriter.cpp 114 2012-01-22 05:07:35Z werner $
 *
 * File:   IPsecConfWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on July 23, 2010, 6:52 AM
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

#include <QObject>
#include <QString>
#include <ctemplate/template.h>
#include "settings/ConnectionSettings.h"
#include "IPsecConfWriter.h"

static const char* const RSASIG = "rsasig";
static const char* const LEFTCERTLINE = "leftcert=\"%s\"";

static const char* const CONN_SECTION = "CONN_SECTION";
static const char* const NAME = "NAME";
static const char* const GATEWAY = "GATEWAY";
static const char* const IDENTITY = "IDENTITY";
static const char* const AUTHBY = "AUTHBY";
static const char* const LEFTCERT = "LEFTCERT";

IPsecConfWriter::IPsecConfWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo)
{
}

IPsecConfWriter::~IPsecConfWriter()
{
}

void IPsecConfWriter::fill()
{
   const ConnectionSettings settings;
   const int iConnections = settings.connections();

   for (int i = 0; i < iConnections; i++)
   {
      const QString strName(settings.connection(i));

      if (!strName.isEmpty())
      {
         if (!settings.commonSettings(strName).disableIPSecEncryption())
         {
            ctemplate::TemplateDictionary* const pConnection = dictionary()->AddSectionDictionary(CONN_SECTION);

            const IPSecSettings ipsecSetting(settings.ipsecSettings(strName));

            pConnection->SetValue(NAME, strName.toAscii().constData());
            pConnection->SetValue(GATEWAY, ipsecSetting.gateway().toAscii().constData());
            pConnection->SetValue(IDENTITY, ipsecSetting.identity().toAscii().constData());
            pConnection->SetValue(AUTHBY, ipsecSetting.authBy().toAscii().constData());
            if (ipsecSetting.authBy() == RSASIG)
               pConnection->SetFormattedValue(LEFTCERT, LEFTCERTLINE, ipsecSetting.certificateFileName().toAscii().constData());
         }
      }
      else
         addErrorMsg(QObject::tr("No such connection: '%1'.").arg(strName));
   }
}

