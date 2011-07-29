/*
 * $Id: ConnectionEditor.h 13 2010-09-17 09:12:39Z werner $
 *
 * File:   ConnectionEditor.h
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

#ifndef CONNECTIONEDITOR_H
#define	CONNECTIONEDITOR_H

#include <QObject>

class L2tpIPsecVpnApplication;
class ConnectionEditorDialog;

class ConnectionEditor : public QObject
{
   Q_OBJECT

public:
   explicit ConnectionEditor(L2tpIPsecVpnApplication& application, QObject* pParent = 0);
   virtual ~ConnectionEditor();

   int exec();

private slots:
   void onConnectionAdded(const QString& strName);
   void onConnectionRemoved(const QString& strName);

private:
   ConnectionEditor(const ConnectionEditor& orig);
   ConnectionEditor& operator=(const ConnectionEditor& orig);

   L2tpIPsecVpnApplication& m_Application;
   ConnectionEditorDialog* const m_pConnectionEditorDialog;
};

#endif	/* CONNECTIONEDITOR_H */

