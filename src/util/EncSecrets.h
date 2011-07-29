/*
 * $Id: EncSecrets.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   EncSecrets.h
 * Author: Werner Jaeger
 *
 * Created on July 28, 2010, 10:48 AM
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

#ifndef ENCSECRETS_H
#define	ENCSECRETS_H

#include <QString>

class EncSecrets
{
public:
   EncSecrets(const unsigned char acKey[16], const unsigned char acIv[8], const char* pcAscbuf);
   EncSecrets(const char* pcB64buf);
   virtual ~EncSecrets();

   const char* getbuf(void) const;
   QString retrieve(const unsigned char acKey[16], const unsigned char acIv[8]);

private:
   EncSecrets(const EncSecrets& orig);
   EncSecrets& operator=(const EncSecrets& orig);

   int encode(const unsigned char* pcBfbuf, int iOutlen);
   int decode(unsigned char* pcBfbuf);
   static int encrypt(const char* pcAscbuf, const unsigned char acIv[8], const unsigned char acKey[16], unsigned char* pcBfbuf);
   static int decrypt(const unsigned char* pcBfbuf, int iTotal, char* pcAscbuf, const unsigned char acKey[16], const unsigned char acIv[8]);

   unsigned char* m_pcB64buf;
   int m_iBufferSize;
};

#endif	/* ENCSECRETS_H */

