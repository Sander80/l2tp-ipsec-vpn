/*
 * $Id: L2tpConfWriter.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   L2tpConfWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on July 25, 2010, 5:37 PM
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
#include <ctemplate/template.h>
#include "settings/ConnectionSettings.h"
#include "ConfWriter.h"
#include "L2tpConfWriter.h"

static const char* const YES = "yes";
static const char* const NO = "no";
static const char* const REDIALTIMEOUTLINE = "redial timeout = %u";
static const char* const REDIALATTEMPTSLINE = "max redials = %u";

static const char* const LAC_SECTION = "LAC_SECTION";
static const char* const NAME = "NAME";
static const char* const GATEWAY = "GATEWAY";

static const char* const PPPOPTFILE = "PPPOPTFILE";
static const char* const LENGTHBIT = "LENGTHBIT";
static const char* const REDIAL = "REDIAL";
static const char* const REDIALTIMEOUT = "REDIALTIMEOUT";
static const char* const REDIALATTEMPTS = "REDIALATTEMPTS";

L2tpConfWriter::L2tpConfWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo)
{
}

L2tpConfWriter::~L2tpConfWriter()
{
}

void L2tpConfWriter::fill()
{
   const ConnectionSettings settings;
   const int iConnections = settings.connections();

   for (int i = 0; i < iConnections; i++)
   {
      ctemplate::TemplateDictionary* const pLacSection = dictionary()->AddSectionDictionary(LAC_SECTION);
      const QString strName(settings.connection(i));

      if (!strName.isEmpty())
      {
         const IPSecSettings ipsecSetting(settings.ipsecSettings(strName));
         const L2tpSettings l2tpSetting(settings.l2tpSettings(strName));

         pLacSection->SetValue(NAME, strName.toAscii().constData());
         pLacSection->SetValue(GATEWAY, ipsecSetting.gateway().toAscii().constData());

         pLacSection->SetValue(PPPOPTFILE, ConfWriter::fileName(ConfWriter::PPP, strName).toAscii().constData());
         pLacSection->SetValue(LENGTHBIT, l2tpSetting.lengthBit() ? YES : NO);

         if (l2tpSetting.redial())
         {
            pLacSection->SetValue(REDIAL, YES);
            pLacSection->SetFormattedValue(REDIALTIMEOUT, REDIALTIMEOUTLINE, l2tpSetting.redialTimeout());
            pLacSection->SetFormattedValue(REDIALATTEMPTS, REDIALATTEMPTSLINE, l2tpSetting.redialAttempts());
         }
         else
            pLacSection->SetValue(REDIAL, NO);
      }
      else
         addErrorMsg(QObject::tr("No such connection: '%1'.").arg(strName));
   }
}

