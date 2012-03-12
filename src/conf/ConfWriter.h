/*
 * $Id: ConfWriter.h 120 2012-03-08 04:57:41Z werner $
 *
 * File:   ConfWriter.h
 * Author: Werner Jaeger
 *
 * Created on July 23, 2010, 9:14 AM
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

#ifndef CONFWRITER_H
#define	CONFWRITER_H

class ConfWriter
{
public:
   typedef enum { IPsec, L2TP, PPP, RSYSLOG, GETIPSECINFO, PPPUPSCRIPT, PPPDNSCONF, PPPDOWNSCRIPT, OPENSSL, IPsecSECRET, END} Conf;

   static bool write(Conf conf, const QString& strInstance = "");
   static const QString& fileName(Conf conf, const QString& strInstance = "");

private:
   ConfWriter();
   virtual ~ConfWriter();
   ConfWriter(const ConfWriter& orig);
   ConfWriter& operator=(const ConfWriter& orig);
};

#endif	/* CONFWRITER_H */

