/*
 * $Id: EncSecrets.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   EncSecrets.cpp
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

#include <cstring>       // strlen, bzero
#include <openssl/evp.h> // Enc*(), Dec*()
#include "EncSecrets.h"

/**
 * Stores a base64 encoded blowfish encrypted buffer.
 *
 * Very useful to store small buffers, like passwords, into files. It also
 * seems to be working very well even for larger buffers.
 *
 * This document was last updated at \today (GMT -1).
 */

/**
 * 1st constructor, used for encrypting/encoding.
 *
 * #acKey# is the 16 bytes blowfish encryption key, #acIv# is the 8 bytes
 * random number initialization vector, #pcAscbuf# is is the buffer to be
 * encrypted/encoded.
 */
EncSecrets::EncSecrets(const unsigned char acKey[16], const unsigned char acIv[8], const char* pcAscbuf)
{
   // Allocates enough amount of memory to be used by the buffer.
   m_iBufferSize = (2 * ::strlen(pcAscbuf)) > 32 ? 2 * ::strlen(pcAscbuf) : 32;

   m_pcB64buf =  static_cast<unsigned char*>(::malloc(m_iBufferSize));
   unsigned char* const pcBfbuf =  static_cast<unsigned char*>(::malloc(m_iBufferSize));

   const int iOutlen = EncSecrets::encrypt(pcAscbuf, acIv, acKey, pcBfbuf);
   encode(pcBfbuf, iOutlen);

   ::bzero(pcBfbuf, m_iBufferSize);
   ::free(pcBfbuf);
}

/**
 * 2nd constructor, used for decoding/decrypting.
 *
 * #pcB64buf# is an already base64 encoded blowfish encrypted buffer.
 */
EncSecrets::EncSecrets(const char* pcB64buf)
{
   // Allocates enough amount of memory to be used by the buffer.
   m_iBufferSize = ::strlen(pcB64buf);

   m_pcB64buf = static_cast<unsigned char*>(::malloc(m_iBufferSize + 1));

   for(int i = 0; i < m_iBufferSize; i++)
      m_pcB64buf[i] = pcB64buf[i];

   m_pcB64buf[m_iBufferSize] = '\0';
}

EncSecrets::~EncSecrets()
{
   ::bzero(m_pcB64buf, m_iBufferSize);
   ::free(m_pcB64buf);
}

/**
 * Returns base64 encoded buffer.
 */
const char* EncSecrets::getbuf(void) const
{
   return(reinterpret_cast<const char*>(m_pcB64buf));
}

/**
 * Returns decoded/decrypted string.
 *
 * #acKey# is the blowfish encryption key and #acIv# is
 * the random number initialization vector used to decrypt.
 */
QString EncSecrets::retrieve(const unsigned char acKey[16], const unsigned char acIv[8])
{
   unsigned char* const pcBfbuf = static_cast<unsigned char*>(::malloc(m_iBufferSize));
   char* const pcAscbuf = static_cast<char*>(::malloc(m_iBufferSize));

   const int iTotal = decode(pcBfbuf);
   const int iOutLen = ::EncSecrets::decrypt(pcBfbuf, iTotal, pcAscbuf, acKey, acIv);

   const QString strRet = QString::fromAscii(pcAscbuf, iOutLen);

   ::free(pcBfbuf);
   ::free(pcAscbuf);

   return(strRet);
}

// Base64 encodes pcBfbuf.
int EncSecrets::encode(const unsigned char* pcBfbuf, int iOutlen)
{
   EVP_ENCODE_CTX ectx;
   int iLen, iTotal = 0;

   ::EVP_EncodeInit(&ectx);
   ::EVP_EncodeUpdate(&ectx, m_pcB64buf, &iLen, pcBfbuf, iOutlen);
   iTotal += iLen;

   ::EVP_EncodeFinal(&ectx, m_pcB64buf + iLen, &iLen);
   iTotal += iLen;

   return(iTotal);
}

// Base64 decodification.
int EncSecrets::decode(unsigned char* pcBfbuf)
{
   EVP_ENCODE_CTX ectx;
   int iLen, iTotal = 0;

   ::EVP_DecodeInit(&ectx);
   ::EVP_DecodeUpdate(&ectx, pcBfbuf, &iLen, m_pcB64buf, ::strlen(reinterpret_cast<char*>(m_pcB64buf)));
   iTotal += iLen;

   ::EVP_DecodeFinal(&ectx, pcBfbuf + iLen, &iLen);
   iTotal += iLen;

   return(iTotal);
}

// Blowfish encrypts pcAscbuf into pcBfbuf.
int EncSecrets::encrypt(const char* pcAscbuf, const unsigned char acIv[8], const unsigned char acKey[16], unsigned char* pcBfbuf)
{
   EVP_CIPHER_CTX ctx;
   int iOutlen = 0;
   int iTmplen;

   ::EVP_CIPHER_CTX_init(&ctx);
   ::EVP_EncryptInit_ex(&ctx, ::EVP_bf_cbc(), NULL, acKey, acIv);

   if(::EVP_EncryptUpdate(&ctx, pcBfbuf, &iOutlen, reinterpret_cast<const unsigned char*>(pcAscbuf), ::strlen(pcAscbuf)))
   {
      if(::EVP_EncryptFinal_ex(&ctx, pcBfbuf + iOutlen, &iTmplen))
         iOutlen += iTmplen;
   }

   ::EVP_CIPHER_CTX_cleanup(&ctx);

   return(iOutlen);
}

// Blowfish decryption.
int EncSecrets::decrypt(const unsigned char* pcBfbuf, int iTotal, char* pcAscbuf, const unsigned char acKey[16], const unsigned char acIv[8])
{
   EVP_CIPHER_CTX ctx;
   int iOutlen = 0;
   int iTmplen;

   ::EVP_CIPHER_CTX_init(&ctx);
   ::EVP_DecryptInit_ex(&ctx, ::EVP_bf_cbc(), NULL, acKey, acIv);

   if(::EVP_DecryptUpdate(&ctx, reinterpret_cast<unsigned char*>(pcAscbuf), &iOutlen, pcBfbuf, iTotal))
   {
      if(::EVP_DecryptFinal(&ctx, reinterpret_cast<unsigned char*>(pcAscbuf + iOutlen), &iTmplen))
         iOutlen += iTmplen;
   }

   ::EVP_CIPHER_CTX_cleanup(&ctx);

   return(iOutlen);
}


