/*
 * $Id: RouteSettingsDialog.cpp 165 2017-12-30 14:12:45Z wejaeger $
 *
 * File:   RouteSettingsDialog.cpp
 * Author: Werner Jaeger
 *
 * Created on August 5, 2010, 4:17 PM
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

#include <QtWidgets/QMessageBox>

#include "models/PppRoutesModel.h"
#include "util/GlobalFunctions.h"
#include "RouteSettingsDialog.h"

RouteSettingsDialog::RouteSettingsDialog(const QString& strConnectionName, QWidget* pParent) : QDialog(pParent), m_strConnectionName(strConnectionName), m_pPPPRoutesModel(new PppRoutesModel(strConnectionName, true)), m_pNoRoutesModel(new PppRoutesModel(strConnectionName, false))
{
   m_Widget.setupUi(this);

   m_Widget.m_pRoutesTableView->setModel(m_pPPPRoutesModel);
   m_Widget.m_pRoutesTableView->horizontalHeader()->setStretchLastSection(true);
   m_Widget.m_pRoutesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

   m_Widget.m_pNoRoutesTableView->setModel(m_pNoRoutesModel);
   m_Widget.m_pNoRoutesTableView->horizontalHeader()->setStretchLastSection(true);
   m_Widget.m_pNoRoutesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

   connect(m_Widget.m_pAddButton, SIGNAL(clicked()), SLOT(addRoute()));
   connect(m_Widget.m_pDeleteButton, SIGNAL(clicked()), SLOT(removeRoute()));

   connect(m_Widget.m_pAddNoRouteButton, SIGNAL(clicked()), SLOT(addNoRoute()));
   connect(m_Widget.m_pDeleteNoRouteButton, SIGNAL(clicked()), SLOT(removeNoRoute()));

   connect(m_Widget.m_pButtonBox, SIGNAL(helpRequested()), SLOT(onHelpRequested()));

   if (m_pPPPRoutesModel->rowCount() > 0)
      m_Widget.m_pRoutesTableView->setCurrentIndex(m_pPPPRoutesModel->index(0, 0));
   else
      m_Widget.m_pDeleteButton->setEnabled(false);

   if (m_pNoRoutesModel->rowCount() > 0)
      m_Widget.m_pNoRoutesTableView->setCurrentIndex(m_pNoRoutesModel->index(0, 0));
   else
      m_Widget.m_pDeleteNoRouteButton->setEnabled(false);

   setWindowTitle(tr("Edit routes for VPN connection ") + strConnectionName);

   readSettings();
}

RouteSettingsDialog::~RouteSettingsDialog()
{
   delete m_pPPPRoutesModel;
   delete m_pNoRoutesModel;
}

void RouteSettingsDialog::addRoute() const
{
   const int iRow = m_pPPPRoutesModel->rowCount();

   if (m_pPPPRoutesModel->addRow())
   {
      m_Widget.m_pRoutesTableView->setCurrentIndex(m_pPPPRoutesModel->index(iRow, 0));
      m_Widget.m_pDeleteButton->setEnabled(true);
   }

   m_Widget.m_pRoutesTableView->setFocus();
}

void RouteSettingsDialog::addNoRoute() const
{
   const int iRow = m_pNoRoutesModel->rowCount();

   if (m_pNoRoutesModel->addRow())
   {
      m_Widget.m_pNoRoutesTableView->setCurrentIndex(m_pNoRoutesModel->index(iRow, 0));
      m_Widget.m_pDeleteNoRouteButton->setEnabled(true);
   }

   m_Widget.m_pNoRoutesTableView->setFocus();
}

void RouteSettingsDialog::removeRoute() const
{
   const QModelIndex index = m_Widget.m_pRoutesTableView->currentIndex();

   if (index.row() >= 0)
   {
      const QString strAddress = m_pPPPRoutesModel->data(m_pPPPRoutesModel->index(index.row(), 0), Qt::DisplayRole).toString();

      if (QMessageBox::question(NULL, tr("Delete Route"), tr("Are you sure you wish to delete the route '%1'?").arg(strAddress), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
      {
         if (m_pPPPRoutesModel->removeRow(index.row()))
         {
            const int iRows =  m_pPPPRoutesModel->rowCount();
            if (index.row() < iRows)
               m_Widget.m_pRoutesTableView->setCurrentIndex(m_pPPPRoutesModel->index(index.row(), 0));
            else if (iRows > 0)
               m_Widget.m_pRoutesTableView->setCurrentIndex(m_pPPPRoutesModel->index(index.row() - 1, 0));

            m_Widget.m_pDeleteButton->setEnabled(iRows > 0);
         }
      }
   }

   m_Widget.m_pRoutesTableView->setFocus();
}

void RouteSettingsDialog::removeNoRoute() const
{
   const QModelIndex index = m_Widget.m_pNoRoutesTableView->currentIndex();

   if (index.row() >= 0)
   {
      const QString strAddress = m_pNoRoutesModel->data(m_pNoRoutesModel->index(index.row(), 0), Qt::DisplayRole).toString();

      if (QMessageBox::question(NULL, tr("Delete Route"), tr("Are you sure you wish to delete the route '%1'?").arg(strAddress), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
      {
         if (m_pNoRoutesModel->removeRow(index.row()))
         {
            const int iRows =  m_pNoRoutesModel->rowCount();
            if (index.row() < iRows)
               m_Widget.m_pNoRoutesTableView->setCurrentIndex(m_pNoRoutesModel->index(index.row(), 0));
            else if (iRows > 0)
               m_Widget.m_pNoRoutesTableView->setCurrentIndex(m_pNoRoutesModel->index(index.row() - 1, 0));

            m_Widget.m_pDeleteNoRouteButton->setEnabled(iRows > 0);
         }
      }
   }

   m_Widget.m_pNoRoutesTableView->setFocus();
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
      m_Widget.m_pAddNoRouteButton->setDisabled(false);
      m_Widget.m_pDeleteButton->setDisabled(true);
      m_Widget.m_pDeleteNoRouteButton->setDisabled(false);
      m_Widget.m_pRoutesTableView->setDisabled(true);
      m_Widget.m_pNoRoutesTableView->setDisabled(false);
   }
   else
   {
      m_Widget.m_pUseDefaultGatewayRadioButton->setChecked(false);
      m_Widget.m_pUseExplicitRoutesRadioButton->setChecked(true);
      m_Widget.m_pAddButton->setEnabled(true);
      m_Widget.m_pAddNoRouteButton->setEnabled(false);
      m_Widget.m_pDeleteButton->setEnabled(true);
      m_Widget.m_pDeleteNoRouteButton->setEnabled(false);
      m_Widget.m_pRoutesTableView->setEnabled(true);
      m_Widget.m_pNoRoutesTableView->setEnabled(false);
   }
}

bool RouteSettingsDialog::writeSettings() const
{
   const PppIpSettings ipSettings = ConnectionSettings().pppSettings(m_strConnectionName).ipSettings();

   return(ipSettings.setUseDefaultGateway(m_Widget.m_pUseDefaultGatewayRadioButton->isChecked()));
}
