/*
 * $Id: PppUpScriptWriter.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   PppUpScriptWriter.h
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

#ifndef PPPUPSCRIPTWRITER_H
#define	PPPUPSCRIPTWRITER_H

#include "AbstractConfWriter.h"

class PppUpScriptWriter : public AbstractConfWriter
{
public:
   PppUpScriptWriter(const QString& strTemplateKey, const QString& strWriteTo);
   virtual ~PppUpScriptWriter() {}

protected:
   void fill();

private:
   PppUpScriptWriter(const PppUpScriptWriter& orig);
   PppUpScriptWriter& operator=(const PppUpScriptWriter& orig);
};

#endif	/* PPPUPSCRIPTWRITER_H */

