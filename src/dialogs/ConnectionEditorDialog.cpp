/*
 * $Id: ConnectionEditorDialog.cpp 120 2012-03-08 04:57:41Z werner $
 *
 * File:   ConnectionEditorDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on July 18, 2010, 1:09 PM
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

#include <QInputDialog>
#include <QMessageBox>
#include <QFile>

#include "conf/ConfWriter.h"
#include "models/ConnectionsModel.h"
#include "settings/ConnectionSettings.h"
#include "settings/Preferences.h"
#include "util/GlobalFunctions.h"
#include "ConnectionSettingsDialog.h"
#include "ConnectionEditorDialog.h"
#include "PreferencesEditorDialog.h"

ConnectionEditorDialog::ConnectionEditorDialog(QWidget* pParent) : QDialog(pParent), m_pConnectionsModel(new ConnectionsModel()), m_pConnectionSettings(new ConnectionSettings())
{
   m_Widget.setupUi(this);

   m_Widget.m_pConnections->setModel(m_pConnectionsModel);
   m_Widget.m_pConnections->horizontalHeader()->setStretchLastSection(true);
   m_Widget.m_pConnections->setSelectionBehavior(QAbstractItemView::SelectRows);

   connect(m_Widget.m_pPreferencesCommandLinkButton, SIGNAL(clicked()), this, SLOT(editPreferences()));
   connect(m_Widget.m_pAdd, SIGNAL(clicked()), SLOT(addConnection()));
   connect(m_Widget.m_pEdit, SIGNAL(clicked()), SLOT(editConnection()));
   connect(m_Widget.m_pDelete, SIGNAL(clicked()), SLOT(removeConnection()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   if (m_pConnectionsModel->rowCount() > 0)
      m_Widget.m_pConnections->setCurrentIndex(m_pConnectionsModel->index(0, 0));
   else
      enableDeleteAndEdit(false);

   m_Widget.m_pConnections->setFocus();

   m_pConnectionSettings->clearChanged();
}

ConnectionEditorDialog::~ConnectionEditorDialog()
{
   delete m_pConnectionsModel;
   delete m_pConnectionSettings;
}

void ConnectionEditorDialog::onHelpRequested() const
{
   ::showHelp("Installing_L2TP_over_IPsec_VPN_Manager");
}

void ConnectionEditorDialog::accept()
{
   if (m_pConnectionSettings->hasChanged())
   {
      applySettings(m_pConnectionsModel, m_pConnectionSettings, windowTitle(), m_Widget.m_pConnections);
      m_pConnectionSettings->clearChanged();
   }

   QDialog::accept();
}

void ConnectionEditorDialog::reject()
{
   if (m_pConnectionSettings->hasChanged())
   {
      applySettings(m_pConnectionsModel, m_pConnectionSettings, windowTitle(), m_Widget.m_pConnections);
      m_pConnectionSettings->clearChanged();
   }

   QDialog::reject();
}

bool ConnectionEditorDialog::applySettings(ConnectionsModel* pConnectionsModel, ConnectionSettings* pConnectionSettings, const QString strMsgBoxTitle, QWidget* pFocus)
{
   const OpenSSLSettings openSSLSettings(Preferences().openSSLSettings());
   const int iConnections(pConnectionSettings->connections());

   bool fRet(true);

   if (iConnections > 0)
   {
      if (pConnectionsModel->isWriteable())
      {
         if (pFocus)
            QMessageBox::information(NULL, strMsgBoxTitle, tr("You need to reconnect for your changes to take effect!"));

         fRet = ConfWriter::write(ConfWriter::IPsec);
         if (fRet) fRet = ConfWriter::write(ConfWriter::IPsecSECRET);
         if (fRet) fRet = ConfWriter::write(ConfWriter::L2TP);

         for (int i = 0; fRet && i < iConnections; i++)
         {
            const QString strConnectionName(pConnectionSettings->connection(i));

            fRet = ConfWriter::write(ConfWriter::PPP, strConnectionName);
            if (fRet)
            {
               const QString strDNSConfInstance(QCoreApplication::instance()->objectName() + "-" +strConnectionName);
               const QString strDNSConfFile(ConfWriter::fileName(ConfWriter::PPPDNSCONF, strDNSConfInstance));
               const PppIpSettings ipSettings(pConnectionSettings->pppSettings(strConnectionName).ipSettings());

               if (ipSettings.usePeerDns() || (ipSettings.alternateDnsServerAddress().isEmpty() && ipSettings.preferredDnsServerAddress().isEmpty() && ipSettings.searchDomains().isEmpty()))
               {
                  if (QFile::exists(strDNSConfFile))
                     QFile::remove(strDNSConfFile);
               }
               else
                  fRet = ConfWriter::write(ConfWriter::PPPDNSCONF, strDNSConfInstance);
            }
         }

         if (fRet) fRet = ConfWriter::write(ConfWriter::PPPUPSCRIPT);
         if (fRet) fRet = ConfWriter::write(ConfWriter::PPPDOWNSCRIPT);
         if (fRet) fRet = ConfWriter::write(ConfWriter::GETIPSECINFO);
         if (fRet) fRet = ConfWriter::write(ConfWriter::RSYSLOG);
         if (fRet)
         {
            if (openSSLSettings.enginePath().isEmpty() || openSSLSettings.pkcs11Path().isEmpty() || openSSLSettings.engineId().isEmpty())
            {
               const QString strOpenSSLConfFile(ConfWriter::fileName(ConfWriter::OPENSSL));
               if (QFile::exists(strOpenSSLConfFile))
                  QFile::remove(strOpenSSLConfFile);
            }
            else
               fRet = ConfWriter::write(ConfWriter::OPENSSL);
         }
      }
      else
      {
         if (pFocus)
            QMessageBox::critical(NULL, tr("Apply settings"), tr("You do not have the permission to apply settings"));

         fRet = false;
      }
   }

   if (pFocus)
      pFocus->setFocus();

    return(fRet);
}

void ConnectionEditorDialog::editPreferences()
{
   PreferencesEditorDialog preferences;
   preferences.exec();
   m_Widget.m_pConnections->setFocus();
}

void ConnectionEditorDialog::addConnection()
{
   if (m_pConnectionsModel->isWriteable())
   {
      const QString strTitle(tr("New Connection"));

      QString strName("");
      bool fOk = true;
      ConnectionsModel::Result result(ConnectionsModel::InvalidName);
      while (fOk && result != ConnectionsModel::Ok)
      {
         strName = QInputDialog::getText(this, strTitle, tr("Connection name:"), QLineEdit::Normal, strName, &fOk);

         if (fOk)
         {
            const int iRow = m_pConnectionsModel->rowCount();
            result = m_pConnectionsModel->addRow(strName);
            switch (result)
            {
               case ConnectionsModel::Ok:
                  m_Widget.m_pConnections->setCurrentIndex(m_pConnectionsModel->index(iRow, 0));
                  enableDeleteAndEdit(true);
                  emit connectionAdded(strName);
                  break;

               case ConnectionsModel::DuplicateName:
                  QMessageBox::critical(this, strTitle, tr("A connection with name '%1' already exists").arg(strName));
                  break;

               case ConnectionsModel::InvalidName:
                  QMessageBox::critical(this, strTitle, tr("The provided name '%1' contains invalid characters.\n\nName must start with a letter and may contain only letters, digits, periods, underscores, and hyphens.\nMaximum length is 30.").arg(strName));
                  break;

               default:
                  break;
            }
         }
      }
   }
   else
      QMessageBox::critical(this, tr("New Connection"), tr("You do not have the permission to add a connection"));

   m_Widget.m_pConnections->setFocus();
}

void ConnectionEditorDialog::editConnection()
{
   if (m_pConnectionsModel->isWriteable())
   {
      const QModelIndex index = m_Widget.m_pConnections->currentIndex();

      if (index.row() >= 0)
      {
         const QString strName = m_pConnectionsModel->data(index, Qt::DisplayRole).toString();

         ConnectionSettingsDialog settings(strName);
         settings.exec();
      }
   }
   else
      QMessageBox::critical(this, tr("Edit Connection"), tr("You do not have the permission to edit a connection"));

   m_Widget.m_pConnections->setFocus();
}

void ConnectionEditorDialog::removeConnection()
{
   if (m_pConnectionsModel->isWriteable())
   {
      const QModelIndex index = m_Widget.m_pConnections->currentIndex();

      if (index.row() >= 0)
      {
         const QString strName = m_pConnectionsModel->data(index, Qt::DisplayRole).toString();

         if (QMessageBox::question(this, tr("Delete Connection"), tr("Are you sure you wish to delete the connection '%1'?").arg(strName), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
         {
            if (m_pConnectionsModel->removeRow(index.row()))
            {
               const int iRows =  m_pConnectionsModel->rowCount();
               if (index.row() < iRows)
                  m_Widget.m_pConnections->setCurrentIndex(m_pConnectionsModel->index(index.row(), 0));
               else if (iRows > 0)
                  m_Widget.m_pConnections->setCurrentIndex(m_pConnectionsModel->index(index.row() - 1, 0));

               enableDeleteAndEdit(iRows > 0);
               emit connectionRemoved(strName);
            }
         }
      }
   }
   else
      QMessageBox::critical(this, tr("Delete Connection"), tr("You do not have the permission to remmove a connection"));

   m_Widget.m_pConnections->setFocus();
}

void ConnectionEditorDialog::enableDeleteAndEdit(bool fEnable)
{
   m_Widget.m_pDelete->setEnabled(fEnable);
   m_Widget.m_pEdit->setEnabled(fEnable);
}
