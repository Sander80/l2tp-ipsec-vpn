/*
 * $Id: ConnectionEditor.cpp 87 2011-04-20 09:21:12Z werner $
 *
 * File:   ConnectionEditor.cpp
 * Author: Werner Jaeger
 *
 * Created on August 30, 2010, 12:59 PM
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

#include "dialogs/ConnectionEditorDialog.h"
#include "models/ConnectionsModel.h"
#include "settings/ConnectionSettings.h"
#include "L2tpIPsecVpnApplication.h"

#include "ConnectionEditor.h"

ConnectionEditor::ConnectionEditor(L2tpIPsecVpnApplication& application, QObject* pParent) : QObject(pParent), m_Application(application), m_pConnectionEditorDialog(application.mode() == L2tpIPsecVpnApplication::APPLYSETTINGS ? NULL : new ConnectionEditorDialog)
{
   if (m_pConnectionEditorDialog)
   {
      connect(m_pConnectionEditorDialog, SIGNAL(connectionAdded(const QString&)), this, SLOT(onConnectionAdded(const QString&)));
      connect(m_pConnectionEditorDialog, SIGNAL(connectionRemoved(const QString&)), this, SLOT(onConnectionRemoved(const QString&)));
   }
}

ConnectionEditor::~ConnectionEditor()
{
   if (m_pConnectionEditorDialog)
      delete m_pConnectionEditorDialog;
}

int ConnectionEditor::exec()
{
   int iRet(0);

   if (!m_pConnectionEditorDialog)
   {
      ConnectionsModel* pConnectionsModel(new ConnectionsModel());
      ConnectionSettings* pConnectionSettings(new ConnectionSettings());
      iRet = (ConnectionEditorDialog::applySettings(pConnectionsModel, pConnectionSettings) ? 0 : 1);
      delete pConnectionsModel;
      delete pConnectionSettings;
   }
   else
      iRet = (m_pConnectionEditorDialog->exec() == QDialog::Accepted ? 0 : 1);

   return(iRet);
}

void ConnectionEditor::onConnectionAdded(const QString& strName)
{
   m_Application.sendConnectionAddedMessage(strName);
}

void ConnectionEditor::onConnectionRemoved(const QString& strName)
{
   m_Application.sendConnectionRemovedMessage(strName);
}
