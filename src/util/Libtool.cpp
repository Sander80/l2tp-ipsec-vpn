/*
 * $Id: Libtool.cpp 45 2011-02-12 00:25:26Z werner $
 *
 * File:   Libtool.cpp
 * Author: wejaeger
 *
 * Created on February 8, 2011, 1:27 PM
 *
 * Copyright 2011 Werner Jaeger.
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

#include <QString>
#include <ltdl.h>

#include "util/GlobalFunctions.h"
#include "Libtool.h"

Libtool::Libtool(const QString& strLibraryFilePath) : m_pLoadedModuleHandle(Libtool::init(strLibraryFilePath))
{
}

Libtool::~Libtool()
{
   exit();
}

bool Libtool::hasSymbol(const QString& strSymbolName) const
{
   return(loaded() && !!::lt_dlsym(m_pLoadedModuleHandle, strSymbolName.toAscii().constData()));
}

void Libtool::exit() const
{
   ::lt_dlexit();

   if (m_pLoadedModuleHandle)
      ::lt_dlclose(m_pLoadedModuleHandle);
}

lt_dlhandle Libtool::init(const QString& strLibraryFilePath)
{
   lt_dlhandle pModuleHandle(NULL);

   if (::lt_dlinit() == 0 && !strLibraryFilePath.isEmpty())
      pModuleHandle = ::lt_dlopen(::string2FileName(strLibraryFilePath));

   return(pModuleHandle);
}

