/*
 * $Id: PreferencesEditorDialog.cpp 129 2012-04-07 10:15:46Z wejaeger $
 *
 * File:   PreferencesEditorDialog.cpp
 * Author: wejaeger
 *
 * Created on February 4, 2011, 11:21 AM
 *
 * Copyright 2011 Werner Jaeger.
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

#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>

#include "pkcs11/Pkcs11.h"
#include "settings/Preferences.h"
#include "util/ErrorEx.h"
#include "util/GlobalFunctions.h"
#include "util/Libtool.h"
#include "PreferencesEditorDialog.h"

static const QString VALIDOPENSSLENGINELIBSYMBOL("ENGINE_init");
static const QString ENGINEIDPATTERN("[a-zA-Z0-9]{0,20}");
static const QRegExp REENGINID("^" + ENGINEIDPATTERN + "$");

#if defined(_WIN32) || defined(USE_CYGWIN)
static const QString DEFLIBPATH("/WINDOWS/system32");
static const QString LIBFILTER(QObject::tr("Dynamic library files (*.dll)"));
#else
static const QString DEFLIBPATH("/usr/lib");
static const QString LIBFILTER(QObject::tr("Shared library files (*.so)"));
#endif

PreferencesEditorDialog::PreferencesEditorDialog(QWidget* pParent) : QDialog(pParent)
{
   m_Widget.setupUi(this);

   m_Widget.m_pEngineIDLineEdit->setValidator(new QRegExpValidator(REENGINID, this));

   connect(m_Widget.m_pEnginePathPushButton, SIGNAL(clicked()), SLOT(onEnginePath()));
   connect(m_Widget.m_pPkcs11PathPushButton, SIGNAL(clicked()), SLOT(onPkcs11Path()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   readSettings();
}

PreferencesEditorDialog::~PreferencesEditorDialog()
{
}

void PreferencesEditorDialog::onEnginePath()
{
   const OpenSSLSettings settings(Preferences().openSSLSettings());

   const QString strEnginePath(QFileDialog::getOpenFileName(this, tr("Choose path of engine library ..."), settings.enginePath().isEmpty() ? DEFLIBPATH : settings.enginePath(), LIBFILTER));

   if (!strEnginePath.isNull())
      m_Widget.m_pEnginePathLineEdit->setText(strEnginePath);
}

void PreferencesEditorDialog::onPkcs11Path()
{
   const OpenSSLSettings settings(Preferences().openSSLSettings());

   const QString strPkcs11Path(QFileDialog::getOpenFileName(this, tr("Choose path of PKCS11 library ..."), settings.pkcs11Path().isEmpty() ? DEFLIBPATH : settings.pkcs11Path(), LIBFILTER));

   if (!strPkcs11Path.isNull())
      m_Widget.m_pPkcs11PathLineEdit->setText(strPkcs11Path);
}

void PreferencesEditorDialog::onHelpRequested() const
{
   ::showHelp("Editing_preferences");
}

void PreferencesEditorDialog::accept()
{
   const QString strPkcs11Lib(m_Widget.m_pPkcs11PathLineEdit->text());
   const QString strCurrentPkcs11Lib(Preferences().openSSLSettings().pkcs11Path());

   if (!m_Widget.m_pEngineIDLineEdit->text().isEmpty())
   {
      if (!m_Widget.m_pEnginePathLineEdit->text().isEmpty())
      {
         if (!strPkcs11Lib.isEmpty())
         {
            if (Libtool(m_Widget.m_pEnginePathLineEdit->text()).hasSymbol(VALIDOPENSSLENGINELIBSYMBOL))
            {
               try
               {
                  if (strPkcs11Lib != strCurrentPkcs11Lib)
                     Pkcs11::loadLibrary(strPkcs11Lib, false);

                  writeSettings();
                  QDialog::accept();
               }
               catch (const ErrorEx& error)
               {
                  QMessageBox::critical(NULL, QCoreApplication::applicationName(), error.getString());

                  if (!strCurrentPkcs11Lib.isEmpty() && !Pkcs11::loaded())
                  {
                     if (!Pkcs11::loadLibrary(strCurrentPkcs11Lib, true))
                        QMessageBox::critical(NULL, QCoreApplication::applicationName(), QObject::tr("I couldn't load PKCS11 library %1.").arg(strCurrentPkcs11Lib));
                  }
               }
            }
            else
               QMessageBox::critical(NULL, QCoreApplication::applicationName(), QObject::tr("%1 is not a valid OpenSSL engine library.").arg(m_Widget.m_pEnginePathLineEdit->text()));
         }
         else
            QMessageBox::critical(NULL, QCoreApplication::applicationName(), QObject::tr("%1 must not be empty.").arg(m_Widget.m_pPkcs11PathLabel->text()));
      }
      else
         QMessageBox::critical(NULL, QCoreApplication::applicationName(), QObject::tr("%1 must not be empty.").arg(m_Widget.m_pEnginPathLabel->text()));
   }
   else
      QMessageBox::critical(NULL, QCoreApplication::applicationName(), QObject::tr("%1 must not be empty.").arg(m_Widget.m_pEngineIdLabel->text()));
}

void PreferencesEditorDialog::readSettings() const
{
   const OpenSSLSettings settings(Preferences().openSSLSettings());

   m_Widget.m_pEngineIDLineEdit->setText(settings.engineId());
   m_Widget.m_pEnginePathLineEdit->setText(settings.enginePath());
   m_Widget.m_pPkcs11PathLineEdit->setText(settings.pkcs11Path());
}

bool PreferencesEditorDialog::writeSettings() const
{
   const OpenSSLSettings settings(Preferences().openSSLSettings());

   bool fRet(settings.setEngineId(m_Widget.m_pEngineIDLineEdit->text()));
   if (fRet) fRet = settings.setEnginePath(m_Widget.m_pEnginePathLineEdit->text());
   if (fRet) fRet = settings.setPkcs11Path(m_Widget.m_pPkcs11PathLineEdit->text());

   return(fRet);
}
