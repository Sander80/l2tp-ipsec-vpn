/*
 * $Id: OpensslConfWriter.cpp 92 2011-06-17 05:54:54Z werner $
 *
 * File:   OpensslConfWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on August 7, 2010, 4:52 PM
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

#include "settings/Preferences.h"
#include "OpensslConfWriter.h"

static const char* const ENGINEID = "ENGINEID";
static const char* const DYNAMICPATH = "DYNAMICPATH";
static const char* const MODULEPATH = "MODULEPATH";

OpensslConfWriter::OpensslConfWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo)
{
}

void OpensslConfWriter::fill()
{
   const OpenSSLSettings opensslSettings(Preferences().openSSLSettings());

   dictionary()->SetValue(ENGINEID, opensslSettings.engineId().toAscii().constData());
   dictionary()->SetValue(DYNAMICPATH, opensslSettings.enginePath().toAscii().constData());
   dictionary()->SetValue(MODULEPATH, opensslSettings.pkcs11Path().toAscii().constData());
}
