/*
 * $Id: L2tpConfWriter.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   L2tpConfWriter.h
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

#ifndef L2TPCONFWRITER_H
#define	L2TPCONFWRITER_H

#include "AbstractConfWriter.h"

class L2tpConfWriter : public AbstractConfWriter
{
public:
   L2tpConfWriter(const QString& strTemplateKey, const QString& strWriteTo);
   virtual ~L2tpConfWriter();

protected:
   void fill();

private:
   L2tpConfWriter(const L2tpConfWriter& orig);
   L2tpConfWriter& operator=(const L2tpConfWriter& orig);
};

#endif	/* L2TPCONFWRITER_H */

