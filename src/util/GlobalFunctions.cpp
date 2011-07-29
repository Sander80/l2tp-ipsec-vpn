/*
 * $Id: GlobalFunctions.cpp 64 2011-04-05 03:39:39Z werner $
 *
 * File:   GlobalFunctions.cpp
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

#include <QRegExp>
#include <QUrl>
#include <QDesktopServices>

#include "GlobalFunctions.h"

static QString HOSTNAMEPATTERN("([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,6}");
static QString IPV4PATTERN("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
static QString IPPATTERN("\\s*((([0-9A-Fa-f]{1,4}:){7}(([0-9A-Fa-f]{1,4})|:))|(([0-9A-Fa-f]{1,4}:){6}(:|((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})|(:[0-9A-Fa-f]{1,4})))|(([0-9A-Fa-f]{1,4}:){5}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:){4}(:[0-9A-Fa-f]{1,4}){0,1}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:){3}(:[0-9A-Fa-f]{1,4}){0,2}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:){2}(:[0-9A-Fa-f]{1,4}){0,3}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:)(:[0-9A-Fa-f]{1,4}){0,4}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(:(:[0-9A-Fa-f]{1,4}){0,5}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})))(%.+)?\\s*");
static const QRegExp REVALIDGATEWAY(QString("^") + QString("(") + HOSTNAMEPATTERN + ")|(" + IPV4PATTERN + ")" + "$");
static const QRegExp REVALIDIPV4("^" + IPV4PATTERN + "$");
static const QRegExp REVALIDIP("^" + IPPATTERN + "$");
static const QRegExp REVALIDHOSTNAME("^" + HOSTNAMEPATTERN + "$");
static const QRegExp REVALIDHOSTNAMELIST("^" + HOSTNAMEPATTERN + "(?:\\s+" + HOSTNAMEPATTERN + ")*$");

const QRegExp& ipv4ValidationRE()
{
   return(REVALIDIPV4);
}

const QRegExp& ipValidationRE()
{
   return(REVALIDIP);
}

const QRegExp& gatewayValidationRE()
{
   return(REVALIDGATEWAY);
}

const QRegExp& hostNameValidationRE()
{
   return(REVALIDHOSTNAME);
}

const QRegExp& hostNameListValidationRE()
{
   return(REVALIDHOSTNAMELIST);
}

QString utf82QString(const void* vpValue, unsigned long ulLen)
{
   const QString str(QString::fromUtf8(static_cast<const char*>(vpValue), ulLen));
   return(str.trimmed());
}

QByteArray fileName2ByteArray(const QString& strFileName)
{
#ifdef WIN32
	return(strFileName.toLocal8Bit());
#else
	return(strFileName.toUtf8());
#endif
}

const char* string2FileName(const QString& strFileNme)
{
   return(fileName2ByteArray(strFileNme).constData());
}

void showHelp(const QString& strFragment)
{

   QUrl url("http://wiki.l2tpipsecvpn.tuxfamily.org/wiki/index.php?title=Main_Page");

   if (!strFragment.isNull())
      url.setFragment(strFragment);

   QDesktopServices::openUrl(url);
}
