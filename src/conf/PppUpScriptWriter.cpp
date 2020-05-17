/*
 * $Id: PppUpScriptWriter.cpp 165 2017-12-30 14:12:45Z wejaeger $
 *
 * File:   PppUpScriptWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on August 6, 2010, 1:18 PM
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
#include "conf/ConfWriter.h"
#include "settings/ConnectionSettings.h"
#include "PppUpScriptWriter.h"

static const char* const CONN_SECTION = "CONN_SECTION";
static const char* const ROUTE_SECTION = "ROUTE_SECTION";
static const char* const NOROUTE_SECTION = "NOROUTE_SECTION";
static const char* const DEFAULT_GATEWAY_SECTION = "DEFAULT_GATEWAY_SECTION";

static const char* const OBJECTNAME = "OBJECTNAME";
static const char* const GETIPSECINFOLIB = "GETIPSECINFOLIB";
static const char* const GATEWAY = "GATEWAY";
static const char* const IPPARAM = "IPPARAM";
static const char* const IPADDRESS = "IPADDRESS";
static const char* const IPNETMASK = "IPNETMASK";

PppUpScriptWriter::PppUpScriptWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo, AbstractConfWriter::EXECUTABLE)
{
}

void PppUpScriptWriter::fill()
{
   dictionary()->SetValue(OBJECTNAME, QCoreApplication::instance()->objectName().toLatin1().constData());
   dictionary()->SetValue(GETIPSECINFOLIB, ConfWriter::fileName(ConfWriter::GETIPSECINFO).toLatin1().constData());

   const ConnectionSettings settings;
   const int iConnections(settings.connections());

   for (int i = 0; i < iConnections; i++)
   {
      ctemplate::TemplateDictionary* const pConnection(dictionary()->AddSectionDictionary(CONN_SECTION));
      const QString strName(settings.connection(i));

      if (!strName.isEmpty())
      {
         pConnection->SetValue(IPPARAM, (QCoreApplication::instance()->objectName() + "-" + strName).toLatin1().constData());
         pConnection->SetValue(GATEWAY, settings.ipsecSettings(strName).gateway().toLatin1().constData());

         const PppIpSettings ipSetting(settings.pppSettings(strName).ipSettings());

         if (!ipSetting.useDefaultGateway())
         {
            // ctemplate::TemplateDictionary* const pDefaultRoute(pConnection->AddSectionDictionary(ROUTE_SECTION));
            // pDefaultRoute->SetValue(IPADDRESS, "`echo \"${PPP_LOCAL}\" | cut -d'.' -f1`.0.0.0");
            // pDefaultRoute->SetValue(IPNETMASK, "255.0.0.0");

            const int iRoutes(ipSetting.routes());
            for (int j = 0; j < iRoutes; j++)
            {
               ctemplate::TemplateDictionary* const pRoute(pConnection->AddSectionDictionary(ROUTE_SECTION));
               pRoute->SetValue(IPADDRESS, ipSetting.routeAddress(j).toLatin1().constData());
               pRoute->SetValue(IPNETMASK, ipSetting.routeNetmask(j).toLatin1().constData());
            }
         }
         else
         {
            pConnection->AddSectionDictionary(DEFAULT_GATEWAY_SECTION);

            const int iNoRoutes(ipSetting.noRoutes());
            for (int j = 0; j < iNoRoutes; j++)
            {
               ctemplate::TemplateDictionary* const pNoRoute(pConnection->AddSectionDictionary(NOROUTE_SECTION));
               pNoRoute->SetValue(IPADDRESS, ipSetting.noRouteAddress(j).toLatin1().constData());
               pNoRoute->SetValue(IPNETMASK, ipSetting.noRouteNetmask(j).toLatin1().constData());
            }
         }
      }
      else
         addErrorMsg(QObject::tr("No such connection: '%1'.").arg(strName));
   }
}
