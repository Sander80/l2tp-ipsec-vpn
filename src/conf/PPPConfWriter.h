/*
 * $Id: PPPConfWriter.h 42 2011-02-05 07:08:01Z werner $
 *
 * File:   PPPConfWriter.h
 * Author: Werner Jaeger
 *
 * Created on July 27, 2010, 8:50 AM
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

#ifndef PPPCONFWRITER_H
#define	PPPCONFWRITER_H

#include "AbstractConfWriter.h"

class PPPConfWriter : public AbstractConfWriter
{
public:
   PPPConfWriter(const QString& strTemplateKey, const QString& strWriteTo);
   virtual ~PPPConfWriter();

protected:
   void fill();

private:
   PPPConfWriter(const PPPConfWriter& orig);
   PPPConfWriter& operator=(const PPPConfWriter& orig);

   void addRefuseEntry(const QString& strRefuse) const;
   void addCertEntry(const QString& strCertEntry) const;
};

#endif	/* PPPCONFWRITER_H */

