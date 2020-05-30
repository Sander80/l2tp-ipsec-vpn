/*
 * $Id: PPPConfWriter.cpp 43 2011-02-05 20:18:05Z werner $
 *
 * File:   PPPConfWriter.cpp
 * Author: Werner Jaeger
 *
 * Created on July 27, 2010, 8:50 AM
 *
 * Copyright 2010 Werner Jaeger.
 *
 * Upgraded and maintained since 2020 by Alexander Smirnov.
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

#include <QCoreApplication>

#include "settings/ConnectionSettings.h"
#include "PPPConfWriter.h"

static const char* const REFUSE_SECTION = "REFUSE_SECTION";
static const char* const CERT_SECTION = "CERT_SECTION";
static const char* const PASSWORD_SECTION = "PASSWORD_SECTION";

static const char* const REFUSEEAPLINE = "refuse-eap";
static const char* const REFUSEPAPLINE = "refuse-pap";
static const char* const REFUSECHAPLINE = "refuse-chap";
static const char* const REFUSEMSCHAPLINE = "refuse-mschap";
static const char* const REFUSEMSCHAPV2LINE = "refuse-mschap-v2";
static const char* const USEPEERDNSLINE = "usepeerdns";
static const char* const NOBSDCOMPLINE = "nobsdcomp";
static const char* const NODEFLATELINE = "nodeflate";
static const char* const NOVJLINE = "novj";
static const char* const LCPECHOINTERVALLINE = "lcp-echo-interval ";
static const QString CERTLINE = "cert ";
static const QString CALINE = "ca ";
static const QString KEYLINE = "key ";


static const char* const IPPARAM = "IPPARAM";
static const char* const REMOTENAME = "REMOTENAME";
static const char* const NAME = "NAME";
static const char* const PASSWORD = "PASSWORD";
static const char* const USEPEERDNS = "USEPEERDNS";
static const char* const NOBSDCOMP = "NOBSDCOMP";
static const char* const NODEFLATE = "NODEFLATE";
static const char* const NOVJ = "NOVJ";
static const char* const LCPECHOINTERVAL = "LCPECHOINTERVAL";
static const char* const REFUSEPROTOCOL = "REFUSEPROTOCOL";
static const char* const CERTENTRY = "CERTENTRY";

PPPConfWriter::PPPConfWriter(const QString& strTemplateKey, const QString& strWriteTo) : AbstractConfWriter(strTemplateKey, strWriteTo)
{
}

PPPConfWriter::~PPPConfWriter()
{
}

void PPPConfWriter::fill()
{
    dictionary()->SetValue(IPPARAM, (QCoreApplication::instance()->objectName() + "-" + instance()).toLatin1().constData());

    const PppSettings pppSettings = ConnectionSettings().pppSettings(instance());

    dictionary()->SetValue(REMOTENAME, pppSettings.remoteName().toLatin1().constData());
    dictionary()->SetValue(NAME, pppSettings.userName().toLatin1().constData());

    dictionary()->SetValue(PASSWORD, pppSettings.password().toLatin1().constData());



    if (pppSettings.ipSettings().usePeerDns())
        dictionary()->SetValue(USEPEERDNS, USEPEERDNSLINE);

    if (pppSettings.noBSDCompression())
        dictionary()->SetValue(NOBSDCOMP, NOBSDCOMPLINE);

    if (pppSettings.noDeflate())
        dictionary()->SetValue(NODEFLATE, NODEFLATELINE);

    if (pppSettings.noVj())
        dictionary()->SetValue(NOVJ, NOVJLINE);

    if (pppSettings.lcpEchoInterval() != -1)
        dictionary()->SetValue(LCPECHOINTERVAL, QString(LCPECHOINTERVALLINE + QString::number(pppSettings.lcpEchoInterval())).toLatin1().constData());

    const bool fRefuseEap = pppSettings.refuseEap();
    if (fRefuseEap) addRefuseEntry(REFUSEEAPLINE);
    if (!fRefuseEap || pppSettings.refusePap()) addRefuseEntry(REFUSEPAPLINE);
    if (!fRefuseEap || pppSettings.refuseChap()) addRefuseEntry(REFUSECHAPLINE);
    if (!fRefuseEap || pppSettings.refuseMsChap()) addRefuseEntry(REFUSEMSCHAPLINE);
    if (!fRefuseEap || pppSettings.refuseMsChapV2()) addRefuseEntry(REFUSEMSCHAPV2LINE);

    if(fRefuseEap)
    {
        addPasswordEntry(pppSettings.password());

    }
    else
    {
        const PppEapSettings eapSettings = pppSettings.eapSettings();
        if (!eapSettings.certificatePath().isEmpty()) addCertEntry((CERTLINE + "\"" + eapSettings.certificatePath() + "\"").toLatin1().constData());
        if (!eapSettings.caCertificatePath().isEmpty()) addCertEntry((CALINE + "\"" + eapSettings.caCertificatePath() + "\"").toLatin1().constData());
        if (!eapSettings.privateKeyPath().isEmpty()) addCertEntry((KEYLINE + "\"" + eapSettings.privateKeyPath() + "\"").toLatin1().constData());
    }
}

void PPPConfWriter::addRefuseEntry(const QString& strRefuse) const
{
    dictionary()->AddSectionDictionary(REFUSE_SECTION)->SetValue(REFUSEPROTOCOL, strRefuse.toLatin1().constData());
}

void PPPConfWriter::addCertEntry(const QString& strCertEntry) const
{
    dictionary()->AddSectionDictionary(CERT_SECTION)->SetValue(CERTENTRY, strCertEntry.toLatin1().constData());
}
void PPPConfWriter::addPasswordEntry(const QString& strPasswordEntry) const
{
    dictionary()->AddSectionDictionary(PASSWORD_SECTION)->SetValue(PASSWORD, strPasswordEntry.toLatin1().constData());
}
