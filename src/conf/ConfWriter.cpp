/*
 * $Id: ConfWriter.cpp 13 2010-09-17 09:12:39Z werner $
 *
 * File:   ConfWriter.cpp
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

#include <QObject>
#include <QMessageBox>
#include "IPsecConfWriter.h"
#include "IPsecSecretsConfWriter.h"
#include "L2tpConfWriter.h"
#include "PPPConfWriter.h"
#include "RSysLogConfWriter.h"
#include "GetIPsecInfoScriptWriter.h"
#include "PppUpScriptWriter.h"
#include "PppDownScriptWriter.h"
#include "OpensslConfWriter.h"
#include "ConfWriter.h"
#include "IPsecSecretsConfWriter.h"
#include "PppDnsConfWriter.h"

struct
{
   const char* pKey;
   QString strPath;
}
static WRITERARG[] =
{
   {"ipsec.conf", "/etc/ipsec.conf"},
   {"xl2tpd.conf", "/etc/xl2tpd/xl2tpd.conf"},
   {"options.xl2tpd", "/etc/ppp/options.xl2tpd"},
   {"30-l2tp-ipsec-vpn.conf", "/etc/rsyslog.d/30-l2tp-ipsec-vpn.conf"},
   {"getIPSecInfo.lib", "/etc/ppp/getIPSecInfo.lib"},
   {"L2tpIPsecVpn-up", "/etc/ppp/ip-up.d/L2tpIPsecVpn-up"},
   {"L2tpIPsecVpn-dns", "/etc/ppp/resolv/"},
   {"L2tpIPsecVpn-down", "/etc/ppp/ip-down.d/L2tpIPsecVpn-down"},
   {"openssl.cnf", "/etc/ppp/openssl.cnf"},
   {"ipsec.secrets", "/etc/ipsec.secrets"}
};

static AbstractConfWriter* WRITER[] =
{
   new IPsecConfWriter(WRITERARG[ConfWriter::IPsec].pKey, WRITERARG[ConfWriter::IPsec].strPath),
   new L2tpConfWriter(WRITERARG[ConfWriter::L2TP].pKey, WRITERARG[ConfWriter::L2TP].strPath),
   new PPPConfWriter(WRITERARG[ConfWriter::PPP].pKey, WRITERARG[ConfWriter::PPP].strPath),
   new RSysLogConfWriter(WRITERARG[ConfWriter::RSYSLOG].pKey, WRITERARG[ConfWriter::RSYSLOG].strPath),
   new GetIPsecInfoScriptWriter(WRITERARG[ConfWriter::GETIPSECINFO].pKey, WRITERARG[ConfWriter::GETIPSECINFO].strPath),
   new PppUpScriptWriter(WRITERARG[ConfWriter::PPPUPSCRIPT].pKey, WRITERARG[ConfWriter::PPPUPSCRIPT].strPath),
   new PppDnsConfWriter(WRITERARG[ConfWriter::PPPDNSCONF].pKey, WRITERARG[ConfWriter::PPPDNSCONF].strPath),
   new PppDownScriptWriter(WRITERARG[ConfWriter::PPPDOWNSCRIPT].pKey, WRITERARG[ConfWriter::PPPDOWNSCRIPT].strPath),
   new OpensslConfWriter(WRITERARG[ConfWriter::OPENSSL].pKey, WRITERARG[ConfWriter::OPENSSL].strPath),
   new IPsecSecretsConfWriter(WRITERARG[ConfWriter::IPsecSECRET].pKey, WRITERARG[ConfWriter::IPsecSECRET].strPath)
};

bool ConfWriter::write(Conf conf, const QString& strInstance)
{
   bool fRet = false;

   AbstractConfWriter* const writer = WRITER[conf];
   writer->setInstance(strInstance);
   const QString strError(writer->write());
   if (strError.isEmpty())
      fRet = true;
   else
      QMessageBox::critical(NULL, QObject::tr("An error occurred while writing ") + WRITERARG[conf].strPath, strError);

   return(fRet);
}

const QString& ConfWriter::fileName(Conf conf, const QString& strInstance)
{
   AbstractConfWriter* const writer = WRITER[conf];
   writer->setInstance(strInstance);
   return(writer->fileName());
}
