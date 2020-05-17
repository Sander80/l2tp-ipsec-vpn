/*
 * $Id: SecretsChecker.cpp 161 2017-12-25 10:26:31Z wejaeger $
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
#include <QtWidgets/QInputDialog>
#include <QTextStream>
#include <QDir>
#include <QFile>

#include "settings/ConnectionSettings.h"
#include "settings/Preferences.h"
#include "util/EncSecrets.h"
#include "SecretsChecker.h"
#include "VPNControlTask.h"

QMutex SecretsChecker::MUTEX(QMutex::NonRecursive);

static unsigned char const KEY[] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
static unsigned char const IV[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

/*!
 * \class SecretsChecker
 *
 * \brief Checks if all secrets for a given connection name are available.
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
 *         canceled the dialog when asked for the secret, true otherwise.
 */
bool SecretsChecker::check() const
{
   bool fOk(true);

   const PppSettings pppSettings(ConnectionSettings().pppSettings(m_strConnectionName));

//QTextStream(stdout) << "checkSec" << endl;

   if (!pppSettings.refuseEap())
   {
//QTextStream(stdout) << "checkSec 1" << endl;
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
//QTextStream(stdout) << "checkSec 2" << endl;
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
//   printf("%s\n",strIdentity.toStdString().c_str());
  // printf("%d\n",iConnections);
   if (iConnections > 0)
   {
      for (int i = 0; strSecret.isNull() && i < iConnections; i++)
      {
         const QString strConnectionName(settings.connection(i));
         const PppSettings pppSettings(settings.pppSettings(strConnectionName));
         const PppEapSettings eapSettings(pppSettings.eapSettings());
         if (eapSettings.privateKeyPath() == strIdentity)
         {
    //         printf("We are in %d \n", i);
            strSecret = eapSettings.privateKeyPassword();
            if (strSecret.isEmpty()) {
      //          printf("Reading\n");
               strSecret = readSecret(pppSettings);
        //        printf("Read: %s\n", strSecret.toStdString().c_str());
            }
         }
         else if (pppSettings.userName() == strIdentity)
         {
            strSecret = pppSettings.password();
            if (strSecret.isEmpty())
               strSecret = readSecret(pppSettings);
         }
      }
   }

   //printf("Read: %s\n", strSecret.toStdString().c_str());
   return(strSecret);
}

bool SecretsChecker::promptAndStoreSecret(const QString& strTitle, const QString& strLabel, const PppSettings& pppSettings)
{
   bool fOk = MUTEX.tryLock();

   if (fOk)
   {
       const QString strPassword = QInputDialog::getText(NULL, strTitle, strLabel, QLineEdit::Password, "", &fOk);
QTextStream(stdout) << "promt 1" << endl;

       if (fOk)
       {
QTextStream(stdout) << "promt 2" + getSecretsFilePath(pppSettings) << endl;
          QFile secretsFile(getSecretsFilePath(pppSettings));
          fOk = secretsFile.open(QIODevice::WriteOnly);
          if (fOk)
          {
QTextStream(stdout) << "promt 3" << endl;
             EncSecrets secrets(KEY, IV, strPassword.toLatin1().constData());
             fOk = secretsFile.write(secrets.getbuf()) != -1;
QTextStream(stdout) << "promt 4: " << fOk << endl;
          }
       }
       MUTEX.unlock();
   }

   return(fOk);
}

QString SecretsChecker::readSecret(const PppSettings& pppSettings)
{
   QString strSecret;
//printf("%s\n",getSecretsFilePath(pppSettings).toStdString().c_str());
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
   if(pppSettings.userName() != "")
       return(QString(QDir(QDir::tempPath()).absolutePath() + QLatin1Char('/') + pppSettings.userName()));
   else
       return(QString(QDir(QDir::tempPath()).absolutePath() + QLatin1Char('/') + "tmpsecret"));
}
