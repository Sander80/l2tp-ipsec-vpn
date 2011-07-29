/*
 * $Id: RSysLogConfWriter.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   RSysLogConfWriter.h
 * Author: Werner Jaeger
 *
 * Created on July 24, 2010, 9:41 AM
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

#ifndef RSYSLOGCONFWRITER_H
#define	RSYSLOGCONFWRITER_H

#include "AbstractConfWriter.h"

class RSysLogConfWriter : public AbstractConfWriter
{
public:
   RSysLogConfWriter(const QString& strTemplateKey, const QString& strWriteTo);
   virtual ~RSysLogConfWriter() {}

protected:
   void fill() {}

private:
   RSysLogConfWriter(const RSysLogConfWriter& orig);
   RSysLogConfWriter& operator=(const RSysLogConfWriter& orig);
};

#endif	/* RSYSLOGCONFWRITER_H */

