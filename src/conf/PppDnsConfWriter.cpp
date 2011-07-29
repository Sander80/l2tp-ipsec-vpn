/*
 * $Id: PppDnsConfWriter.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   PppDnsConfWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on August 21, 2010, 6:43 AM
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

#include "settings/ConnectionSettings.h"
#include "PppDnsConfWriter.h"

static const char* const DNS_SECTION = "DNS_SECTION";
static const char* const SEARCH_SECTION = "SEARCH_SECTION";
static const char* const IPADDRESS = "IPADDRESS";
static const char* const SEARCHLIST = "SEARCHLIST";

PppDnsConfWriter::PppDnsConfWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo)
{
}

void PppDnsConfWriter::fill()
{
   QString strInstance(instance());
   const QString strConnectionName(strInstance.replace(QCoreApplication::instance()->objectName() + "-", ""));

   const PppSettings pppSettings = ConnectionSettings().pppSettings(strConnectionName);
   const PppIpSettings ipSettings(pppSettings.ipSettings());
   const bool fUsePeerDns = ipSettings.usePeerDns();

   if (!fUsePeerDns && !ipSettings.preferredDnsServerAddress().isEmpty())
      dictionary()->AddSectionDictionary(DNS_SECTION)->SetValue(IPADDRESS, ipSettings.preferredDnsServerAddress().toAscii().constData());

   if (!fUsePeerDns && !ipSettings.alternateDnsServerAddress().isEmpty())
      dictionary()->AddSectionDictionary(DNS_SECTION)->SetValue(IPADDRESS, ipSettings.alternateDnsServerAddress().toAscii().constData());

   if (!fUsePeerDns && !ipSettings.searchDomains().isEmpty())
      dictionary()->AddSectionDictionary(SEARCH_SECTION)->SetValue(SEARCHLIST, ipSettings.searchDomains().toAscii().constData());
}
