/*
 * $Id: Libtool.h 45 2011-02-12 00:25:26Z werner $
 *
 * File:   Libtool.h
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

#ifndef LIBTOOL_H
#define	LIBTOOL_H

class QString;
struct lt__handle;

class Libtool
{
public:
   Libtool(const QString& strLibraryFilePath);
   virtual ~Libtool();

   bool hasSymbol(const QString& strSymbolName) const;

private:
   Libtool(const Libtool& orig);
   Libtool& operator=(const Libtool& orig);

   bool loaded() const { return !!m_pLoadedModuleHandle; };
   void exit() const;

   static lt__handle* init(const QString& strLibraryFilePath);

   lt__handle* const m_pLoadedModuleHandle;
};

#endif	/* LIBTOOL_H */

