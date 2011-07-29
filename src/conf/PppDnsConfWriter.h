/*
 * $Id: PppDnsConfWriter.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   PppDnsConfWriter.h
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

#ifndef PPPDNSCONFWRITER_H
#define	PPPDNSCONFWRITER_H

#include "AbstractConfWriter.h"

class PppDnsConfWriter : public AbstractConfWriter
{
public:
   PppDnsConfWriter(const QString& strTemplateKey, const QString& strWriteTo);
   virtual ~PppDnsConfWriter() {}

protected:
   void fill();

private:
   PppDnsConfWriter(const PppDnsConfWriter& orig);
   PppDnsConfWriter& operator=(const PppDnsConfWriter& orig);
};

#endif	/* PPPDNSCONFWRITER_H */

