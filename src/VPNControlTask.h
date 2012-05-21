/*
 * $Id: VPNControlTask.h 139 2012-05-08 18:07:50Z wejaeger $
 *
 * File:   VPNControlTask.h
 * Author: Werner Jaeger
 *
 * Created on July 8, 2010, 5:09 PM
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

#ifndef VPNCONTROLTASK_H
#define	VPNCONTROLTASK_H

#include <QThread>

#include "VpnClientConnection.h"

class QFile;
class QByteArray;
class QTextStream;
class QSocketNotifier;
class VpnControlDaemonClient;

class VPNControlTask : public QThread
{
   Q_OBJECT

public:
   enum Action {Connect, Disconnect};

   explicit VPNControlTask(QObject* pParent);
   virtual ~VPNControlTask();

   void run();
   bool stop(unsigned long iWaitMiliSeconds);

   void setConnectionName(const QString& strConnectionName);
   const QString& connectionName() const;
   void setAction(Action action);
   Action action() const;
   int restartPcscDaemon();

   qint64 readLogLine(char* data, qint64 iMaxSize);
   qint64 readErrorLine(char* data, qint64 iMaxSize);

signals:
   void readyReadLog();
   void commandOutputReceived(const QString& strOutputLine);
   void errorMessageEmited(int iErrorCode);

private slots:
   void readyReadVpnLogPipe();
   void onResult(int iReturnCode, const QString& stCommand);
   void onCommandOutput(const QString& strOutputLine);

private:
   VPNControlTask(const VPNControlTask& orig);
   VPNControlTask& operator=(const VPNControlTask& orig);

   bool createControlClient();
   void deleteControlClient();
   void runConnect();
   void runDisconnect();
   void runAndWait(VpnClientConnection::Command iCommand, const QString strArguments = "");
   void emitErrorMsg(const QString& strErrorContext);
   void clearVpnLogPipe();
   static bool plutoIsRunning();

   VpnControlDaemonClient* m_pControlClient;
   QString m_strConnectionName;
   Action m_Action;
   volatile int m_iReturnCode;
   volatile bool m_fIPSecConnectionAdded;
   volatile bool m_fIPSecConnectionIsUp;
   QByteArray* const m_pByteArray;
   QTextStream* const m_pErrorStream;
   QSocketNotifier* m_pVpnLogPipeNotifier;

   static QFile m_vpnLogPipe;
};

#endif	/* VPNCONTROLTASK_H */
