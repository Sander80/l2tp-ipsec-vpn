/*
 * $Id: RouteSettingsDialog.cpp 64 2011-04-05 03:39:39Z werner $
 *
 * File:   RouteSettingsDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 4:17 PM
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

#include <QMessageBox>

#include "models/PppRoutesModel.h"
#include "util/GlobalFunctions.h"
#include "RouteSettingsDialog.h"

RouteSettingsDialog::RouteSettingsDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent), m_strConnectionName(strConnectionName), m_pRoutesModel(new PppRoutesModel(strConnectionName))
{
   m_Widget.setupUi(this);

   m_Widget.m_pRoutesTableView->setModel(m_pRoutesModel);
   m_Widget.m_pRoutesTableView->horizontalHeader()->setStretchLastSection(true);
   m_Widget.m_pRoutesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

   connect(m_Widget.m_pAddButton, SIGNAL(clicked()), SLOT(addRoute()));
   connect(m_Widget.m_pDeleteButton, SIGNAL(clicked()), SLOT(removeRoute()));
   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   if (m_pRoutesModel->rowCount() > 0)
      m_Widget.m_pRoutesTableView->setCurrentIndex(m_pRoutesModel->index(0, 0));
   else
      m_Widget.m_pDeleteButton->setEnabled(false);

   setWindowTitle(tr("Edit routes for VPN connection ") + strConnectionName);

   readSettings();
}

RouteSettingsDialog::~RouteSettingsDialog()
{
   delete m_pRoutesModel;
}

void RouteSettingsDialog::addRoute() const
{
   const int iRow = m_pRoutesModel->rowCount();

   if (m_pRoutesModel->addRow())
   {
      m_Widget.m_pRoutesTableView->setCurrentIndex(m_pRoutesModel->index(iRow, 0));
      m_Widget.m_pDeleteButton->setEnabled(true);
   }

   m_Widget.m_pRoutesTableView->setFocus();
}

void RouteSettingsDialog::removeRoute() const
{
   const QModelIndex index = m_Widget.m_pRoutesTableView->currentIndex();

   if (index.row() >= 0)
   {
      const QString strAddress = m_pRoutesModel->data(m_pRoutesModel->index(index.row(), 0), Qt::DisplayRole).toString();

      if (QMessageBox::question(NULL, tr("Delete Route"), tr("Are you sure you wish to delete the route '%1'?").arg(strAddress), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
      {
         if (m_pRoutesModel->removeRow(index.row()))
         {
            const int iRows =  m_pRoutesModel->rowCount();
            if (index.row() < iRows)
               m_Widget.m_pRoutesTableView->setCurrentIndex(m_pRoutesModel->index(index.row(), 0));
            else if (iRows > 0)
               m_Widget.m_pRoutesTableView->setCurrentIndex(m_pRoutesModel->index(index.row() - 1, 0));

            m_Widget.m_pDeleteButton->setEnabled(iRows > 0);
         }
      }
   }

   m_Widget.m_pRoutesTableView->setFocus();
}

void RouteSettingsDialog::onHelpRequested() const
{
   ::showHelp("Configure_routes");
}

void RouteSettingsDialog::accept()
{
   writeSettings();
   QDialog::accept();
}

void RouteSettingsDialog::readSettings() const
{
   const PppIpSettings ipSettings = ConnectionSettings().pppSettings(m_strConnectionName).ipSettings();

   if (ipSettings.useDefaultGateway())
   {
      m_Widget.m_pUseDefaultGatewayRadioButton->setChecked(true);
      m_Widget.m_pUseExplicitRoutesRadioButton->setChecked(false);
      m_Widget.m_pAddButton->setDisabled(true);
      m_Widget.m_pDeleteButton->setDisabled(true);
      m_Widget.m_pRoutesTableView->setDisabled(true);
   }
   else
   {
      m_Widget.m_pUseDefaultGatewayRadioButton->setChecked(false);
      m_Widget.m_pUseExplicitRoutesRadioButton->setChecked(true);
      m_Widget.m_pAddButton->setEnabled(true);
      m_Widget.m_pDeleteButton->setEnabled(true);
      m_Widget.m_pRoutesTableView->setEnabled(true);
   }
}

bool RouteSettingsDialog::writeSettings() const
{
   const PppIpSettings ipSettings = ConnectionSettings().pppSettings(m_strConnectionName).ipSettings();

   return(ipSettings.setUseDefaultGateway(m_Widget.m_pUseDefaultGatewayRadioButton->isChecked()));
}