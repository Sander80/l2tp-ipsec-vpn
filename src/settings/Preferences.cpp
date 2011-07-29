/*
 * $Id: Preferences.cpp 47 2011-02-13 02:40:16Z werner $
 *
 * File:   Preferences.cpp
 * Author: Werner Jaeger
 *
 * Created on August 9, 2010, 12:12 PM
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

#include <QSettings>
#include <QFile>

#include "Preferences.h"

#if defined(_WIN32) || defined(USE_CYGWIN)
static const char* const EngineDefaultLibrary = "engine_pkcs11.dll";
static const char* const PKCS11DefaultLibrary = "opensc-pkcs11.dll";
#else
static const char* const EngineDefaultLibrary = "/usr/lib/engines/engine_pkcs11.so";
static const char* const PKCS11DefaultLibrary = "/usr/lib/opensc-pkcs11.so";
#endif

static const char* const DefaultEngineId = "pkcs11";

static const QString PREFERENCES = "Preferences";
static const QString OPENSSL = "OpenSSL";

static const QString ENGINEPATH = PREFERENCES + '/' + OPENSSL + '/' + "enginePath";
static const QString PKCS11PATH = PREFERENCES + '/' + OPENSSL + '/' + "pkcs11Path";
static const QString ENGINEID = PREFERENCES + '/' + OPENSSL + '/' + "engineId";

Preferences::Preferences()
{
}

Preferences::~Preferences()
{
}

OpenSSLSettings Preferences::openSSLSettings() const
{
   return(OpenSSLSettings());
}

bool OpenSSLSettings::setEnginePath(const QString& strEnginePath) const
{
   if (strEnginePath != EngineDefaultLibrary)
   {
      if (qSettings()->value(ENGINEPATH) != strEnginePath)
         qSettings()->setValue(ENGINEPATH, strEnginePath);
   }
   else
      qSettings()->remove(ENGINEPATH);

   return(true);
}

QString OpenSSLSettings::enginePath() const
{
   return(qSettings()->value(ENGINEPATH, QFile(EngineDefaultLibrary).exists() ? EngineDefaultLibrary : "").toString());
}

bool OpenSSLSettings::setPkcs11Path(const QString& strModulePath) const
{
   if (strModulePath != PKCS11DefaultLibrary)
   {
     if (qSettings()->value(PKCS11PATH) != strModulePath)
          qSettings()->setValue(PKCS11PATH, strModulePath);
   }
   else
      qSettings()->remove(PKCS11PATH);

   return(true);
}

QString OpenSSLSettings::pkcs11Path() const
{
   return(qSettings()->value(PKCS11PATH, QFile(PKCS11DefaultLibrary).exists() ? PKCS11DefaultLibrary : "").toString());
}

bool OpenSSLSettings::setEngineId(const QString& strEngineId) const
{
   if (strEngineId != DefaultEngineId)
   {
     if (qSettings()->value(ENGINEID) != strEngineId)
         qSettings()->setValue(ENGINEID, strEngineId);
   }
   else
      qSettings()->remove(ENGINEID);

   return(true);
}

QString OpenSSLSettings::engineId() const
{
   return(qSettings()->value(ENGINEID, DefaultEngineId).toString());
}
