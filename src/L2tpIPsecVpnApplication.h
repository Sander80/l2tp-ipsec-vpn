/*
 * $Id: L2tpIPsecVpnApplication.h 130 2012-04-08 06:18:04Z wejaeger $
 *
 * File:   L2tpIPsecVpnApplication.h
 * Author: Werner Jaeger
 *
 * Created on August 9, 2010, 2:29 PM
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

#ifndef L2TPIPSECVPNAPPLICATION_H
#define	L2TPIPSECVPNAPPLICATION_H

#include <QApplication>

class ConnectionManager;
class QProcess;
class LocalPeer;

class L2tpIPsecVpnApplication : public QApplication
{
   Q_OBJECT

public:
   enum APPLICATIONMODE
   {
      CONNECTION_MANAGER,
      CONNECTION_EDITOR,
      CONNECTION_EDITOR_STARTER,
      APPLYSETTINGS,
      DELETEALLCONFFILES,
      PASSWORD_CALLBACK
   };

   L2tpIPsecVpnApplication(int& iArgc, char** ppArgv, APPLICATIONMODE appMode);
   virtual ~L2tpIPsecVpnApplication();

   // reimplemented from QApplication so we can throw exceptions in slots
   virtual bool notify(QObject* pReceiver, QEvent* pEvent);

   bool isRunning();
   APPLICATIONMODE mode() const;
   bool sendConnectionAddedMessage(const QString& strConnectionName);
   bool sendConnectionRemovedMessage(const QString& strConnectionName);

   int startConnectionEditorDialog(bool fDetached = false) const;

   static APPLICATIONMODE parseCmdLine(int& iArgc, char** ppArgv);
   static QString getGrahicalSUCmdLine();

signals:
   void connectionAdded(const QString& strConnectionName);
   void connectionRemoved(const QString& strConnectionName);
   void connectionEditorDialogClosed(int iExitCode);

private slots:
   void onMessageReceived(const QString& strMessage);
   void onConnectionEditorDialogClosed(int iExitCode);

private:
   L2tpIPsecVpnApplication(const L2tpIPsecVpnApplication& orig);
   L2tpIPsecVpnApplication & operator=(const L2tpIPsecVpnApplication& orig);

   const APPLICATIONMODE m_Mode;
   QProcess* const m_pProcess;
   LocalPeer* const m_pLocalPeer;
};

#endif	/* L2TPIPSECVPNAPPLICATION_H */

