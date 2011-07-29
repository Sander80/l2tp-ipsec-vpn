/*
 * $Id: OpensslConfWriter.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   OpensslConfWriter.h
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

#ifndef OPENSSLCONFWRITER_H
#define	OPENSSLCONFWRITER_H

#include "AbstractConfWriter.h"

class OpensslConfWriter : public AbstractConfWriter
{
public:
   OpensslConfWriter(const QString& strTemplateKey, const QString& strWriteTo);
   virtual ~OpensslConfWriter() {}

protected:
   void fill();

private:
   OpensslConfWriter(const OpensslConfWriter& orig);
   OpensslConfWriter& operator=(const OpensslConfWriter& orig);
};

#endif	/* OPENSSLCONFWRITER_H */

