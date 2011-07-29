/*
 * $Id: SecretsChecker.cpp 38 2011-02-05 02:01:47Z werner $
 *
 * File:   SecretsChecker.cpp
 * Author: wejaeger
 *
 * Created on October 3, 2010, 8:50 AM
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

#include <QCoreApplication>
#include <QInputDialog>
#include <QDir>
#include <QFile>

#include "settings/ConnectionSettings.h"
#include "settings/Preferences.h"
#include "util/EncSecrets.h"
#include "SecretsChecker.h"
#include "VPNControlTask.h"

static unsigned char const KEY[] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
static unsigned char const IV[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

/*!
 * \class SecretsChecker
 *
 * \brief Checks if all secrets for a given conection name are available.
 */

/*!
 * Creates a new SecretsChecker object for the given connection name.
 */
SecretsChecker::SecretsChecker(const QString& strConnectionName) : m_strConnectionName(strConnectionName)
{
}

SecretsChecker::~SecretsChecker()
{
}

/*!
 * \brief Makes sure all needed secrets are available.
 *
 * Tests if needed secrets are stored in the settings of the given connection
 * name.
 *
 * If a secret is not stored a dialog is opened to ask for it, and the secret
 * is temporarily stored.
 *
 * \return false if secret is not stored in the connection settings and user
 *         cancled the dialog when asked for the secret, true otherwise.
 */
bool SecretsChecker::check() const
{
   bool fOk(true);

   const PppSettings pppSettings(ConnectionSettings().pppSettings(m_strConnectionName));

   if (!pppSettings.refuseEap())
   {
      const PppEapSettings eapSettings(pppSettings.eapSettings());
      if (eapSettings.privateKeyPassword().isEmpty())
      {
         if (eapSettings.privateKeyPath().startsWith(Preferences().openSSLSettings().engineId()))
            fOk = promptAndStoreSecret(QCoreApplication::applicationName(), QObject::tr("Please enter your PIN:"), pppSettings);
         else
            fOk = promptAndStoreSecret(QCoreApplication::applicationName(), QObject::tr("Please enter your passphrase:"), pppSettings);
      }
   }
   else
   {
      if (pppSettings.password().isEmpty())
         fOk = promptAndStoreSecret(QCoreApplication::applicationName(), QObject::tr("Please enter your password:"), pppSettings);
   }

   return(fOk);
}

/*!
 * \brief Retrieves the clear text secret for the given identity.
 *
 * \param strIdentity as provided by the ppp passprompt.so plugin as argv[1].
 *
 * \return the secret or a QString::null if failed to retrieve.
 */
QString SecretsChecker::getSecret(const QString& strIdentity)
{
   const ConnectionSettings settings;
   const int iConnections = settings.connections();

   QString strSecret;

   if (iConnections > 0)
   {
      for (int i = 0; strSecret.isNull() && i < iConnections; i++)
      {
         const QString strConnectionName(settings.connection(i));
         const PppSettings pppSettings(settings.pppSettings(strConnectionName));
         const PppEapSettings eapSettings(pppSettings.eapSettings());

         if (eapSettings.privateKeyPath() == strIdentity)
         {
            strSecret = eapSettings.privateKeyPassword();
            if (strSecret.isEmpty())
               strSecret = readSecret(pppSettings);
         }
         else if (pppSettings.userName() == strIdentity)
         {
            strSecret = pppSettings.password();
            if (strSecret.isEmpty())
               strSecret = readSecret(pppSettings);
         }
      }
   }

   return(strSecret);
}

bool SecretsChecker::promptAndStoreSecret(const QString& strTitle, const QString& strLabel, const PppSettings& pppSettings)
{
   bool fOk;

   const QString strPassword = QInputDialog::getText(NULL, strTitle, strLabel, QLineEdit::Password, "", &fOk);

   if (fOk)
   {
      QFile secretsFile(getSecretsFilePath(pppSettings));
      fOk = secretsFile.open(QIODevice::WriteOnly);
      if (fOk)
      {
         EncSecrets secrets(KEY, IV, strPassword.toAscii().constData());
         fOk = secretsFile.write(secrets.getbuf()) != -1;
      }
   }

   return(fOk);
}

QString SecretsChecker::readSecret(const PppSettings& pppSettings)
{
   QString strSecret;

   QFile secretsFile(getSecretsFilePath(pppSettings));
   if (secretsFile.exists())
   {
      if (secretsFile.open(QIODevice::ReadOnly))
      {
         QByteArray abSecret(secretsFile.readAll());
         EncSecrets secrets(abSecret.data());
         strSecret = secrets.retrieve(KEY, IV);
      }
      secretsFile.remove();
   }

   return(strSecret);
}

QString SecretsChecker::getSecretsFilePath(const PppSettings& pppSettings)
{
   return(QString(QDir(QDir::tempPath()).absolutePath() + QLatin1Char('/') + pppSettings.userName()));
}