/*
 * $Id: GlobalFunctions.h 64 2011-04-05 03:39:39Z werner $
 *
 * File:   GlobalFunctions.h
 * Author: Werner Jaeger
 *
 * Created on July 31, 2010, 7:28 PM
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

#ifndef GLOBALFUNCTIONS_H
#define	GLOBALFUNCTIONS_H

#include <QString>

class QRegExp;

const QRegExp& ipv4ValidationRE();
const QRegExp& ipValidationRE();
const QRegExp& gatewayValidationRE();
const QRegExp& hostNameValidationRE();
const QRegExp& hostNameListValidationRE();

QString utf82QString(const void* vpValue, unsigned long ulLen);
QByteArray fileName2ByteArray(const QString& strFileName);
const char* string2FileName(const QString& strFileNme);
void showHelp(const QString& strFragment = QString::null);

#endif	/* GLOBALFUNCTIONS_H */

