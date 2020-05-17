/********************************************************************************
** Form generated from reading UI file 'ConnectionInformationDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONINFORMATIONDIALOG_H
#define UI_CONNECTIONINFORMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionInformationDialog
{
public:
    QVBoxLayout *m_pDialogLayout;
    QTabWidget *m_pTabWidget;
    QWidget *m_pInfoTab;
    QGridLayout *gridLayout;
    QLabel *m_pGatewayLabel;
    QLabel *m_pGateway;
    QLabel *m_pInterfaceNameLabel;
    QLabel *m_pInterfaceName;
    QLabel *m_pRemoteHostLabel;
    QLabel *m_pRemoteHost;
    QLabel *m_pIPlAddressLabel;
    QLabel *m_pIPAddress;
    QLabel *m_pSubnetMaskLabel;
    QLabel *m_pSubnetMask;
    QLabel *m_pPrimaryDNSLabel;
    QLabel *m_pPrimaryDNS;
    QLabel *m_pSecondaryDNSLabel;
    QLabel *m_pSecondaryDNS;
    QLabel *m_pTenaryDNSLabel;
    QLabel *m_pTenaryDNS;
    QPushButton *m_pStatisticsPushButton;
    QLabel *m_pInternetInterfaceNameLabel;
    QLabel *m_pInternetInterfaceName;
    QLabel *m_pInternetInterfaceGatewayLabel;
    QLabel *m_pInternetInterfaceGateway;
    QWidget *m_pLogTab;
    QVBoxLayout *m_pLogTabLayout;
    QTextEdit *m_pTextEdit;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *ConnectionInformationDialog)
    {
        if (ConnectionInformationDialog->objectName().isEmpty())
            ConnectionInformationDialog->setObjectName(QString::fromUtf8("ConnectionInformationDialog"));
        ConnectionInformationDialog->resize(479, 379);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConnectionInformationDialog->sizePolicy().hasHeightForWidth());
        ConnectionInformationDialog->setSizePolicy(sizePolicy);
        ConnectionInformationDialog->setSizeGripEnabled(true);
        m_pDialogLayout = new QVBoxLayout(ConnectionInformationDialog);
        m_pDialogLayout->setObjectName(QString::fromUtf8("m_pDialogLayout"));
        m_pTabWidget = new QTabWidget(ConnectionInformationDialog);
        m_pTabWidget->setObjectName(QString::fromUtf8("m_pTabWidget"));
        m_pInfoTab = new QWidget();
        m_pInfoTab->setObjectName(QString::fromUtf8("m_pInfoTab"));
        gridLayout = new QGridLayout(m_pInfoTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pGatewayLabel = new QLabel(m_pInfoTab);
        m_pGatewayLabel->setObjectName(QString::fromUtf8("m_pGatewayLabel"));

        gridLayout->addWidget(m_pGatewayLabel, 0, 0, 1, 1);

        m_pGateway = new QLabel(m_pInfoTab);
        m_pGateway->setObjectName(QString::fromUtf8("m_pGateway"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pGateway->sizePolicy().hasHeightForWidth());
        m_pGateway->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_pGateway, 0, 1, 1, 1);

        m_pInterfaceNameLabel = new QLabel(m_pInfoTab);
        m_pInterfaceNameLabel->setObjectName(QString::fromUtf8("m_pInterfaceNameLabel"));

        gridLayout->addWidget(m_pInterfaceNameLabel, 3, 0, 1, 1);

        m_pInterfaceName = new QLabel(m_pInfoTab);
        m_pInterfaceName->setObjectName(QString::fromUtf8("m_pInterfaceName"));
        sizePolicy1.setHeightForWidth(m_pInterfaceName->sizePolicy().hasHeightForWidth());
        m_pInterfaceName->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_pInterfaceName, 3, 1, 1, 1);

        m_pRemoteHostLabel = new QLabel(m_pInfoTab);
        m_pRemoteHostLabel->setObjectName(QString::fromUtf8("m_pRemoteHostLabel"));

        gridLayout->addWidget(m_pRemoteHostLabel, 4, 0, 1, 1);

        m_pRemoteHost = new QLabel(m_pInfoTab);
        m_pRemoteHost->setObjectName(QString::fromUtf8("m_pRemoteHost"));
        sizePolicy1.setHeightForWidth(m_pRemoteHost->sizePolicy().hasHeightForWidth());
        m_pRemoteHost->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_pRemoteHost, 4, 1, 1, 1);

        m_pIPlAddressLabel = new QLabel(m_pInfoTab);
        m_pIPlAddressLabel->setObjectName(QString::fromUtf8("m_pIPlAddressLabel"));

        gridLayout->addWidget(m_pIPlAddressLabel, 5, 0, 1, 1);

        m_pIPAddress = new QLabel(m_pInfoTab);
        m_pIPAddress->setObjectName(QString::fromUtf8("m_pIPAddress"));
        sizePolicy1.setHeightForWidth(m_pIPAddress->sizePolicy().hasHeightForWidth());
        m_pIPAddress->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_pIPAddress, 5, 1, 1, 1);

        m_pSubnetMaskLabel = new QLabel(m_pInfoTab);
        m_pSubnetMaskLabel->setObjectName(QString::fromUtf8("m_pSubnetMaskLabel"));

        gridLayout->addWidget(m_pSubnetMaskLabel, 6, 0, 1, 1);

        m_pSubnetMask = new QLabel(m_pInfoTab);
        m_pSubnetMask->setObjectName(QString::fromUtf8("m_pSubnetMask"));

        gridLayout->addWidget(m_pSubnetMask, 6, 1, 1, 1);

        m_pPrimaryDNSLabel = new QLabel(m_pInfoTab);
        m_pPrimaryDNSLabel->setObjectName(QString::fromUtf8("m_pPrimaryDNSLabel"));

        gridLayout->addWidget(m_pPrimaryDNSLabel, 7, 0, 1, 1);

        m_pPrimaryDNS = new QLabel(m_pInfoTab);
        m_pPrimaryDNS->setObjectName(QString::fromUtf8("m_pPrimaryDNS"));
        sizePolicy1.setHeightForWidth(m_pPrimaryDNS->sizePolicy().hasHeightForWidth());
        m_pPrimaryDNS->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_pPrimaryDNS, 7, 1, 1, 1);

        m_pSecondaryDNSLabel = new QLabel(m_pInfoTab);
        m_pSecondaryDNSLabel->setObjectName(QString::fromUtf8("m_pSecondaryDNSLabel"));

        gridLayout->addWidget(m_pSecondaryDNSLabel, 8, 0, 1, 1);

        m_pSecondaryDNS = new QLabel(m_pInfoTab);
        m_pSecondaryDNS->setObjectName(QString::fromUtf8("m_pSecondaryDNS"));
        sizePolicy1.setHeightForWidth(m_pSecondaryDNS->sizePolicy().hasHeightForWidth());
        m_pSecondaryDNS->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_pSecondaryDNS, 8, 1, 1, 1);

        m_pTenaryDNSLabel = new QLabel(m_pInfoTab);
        m_pTenaryDNSLabel->setObjectName(QString::fromUtf8("m_pTenaryDNSLabel"));

        gridLayout->addWidget(m_pTenaryDNSLabel, 9, 0, 1, 1);

        m_pTenaryDNS = new QLabel(m_pInfoTab);
        m_pTenaryDNS->setObjectName(QString::fromUtf8("m_pTenaryDNS"));

        gridLayout->addWidget(m_pTenaryDNS, 9, 1, 1, 1);

        m_pStatisticsPushButton = new QPushButton(m_pInfoTab);
        m_pStatisticsPushButton->setObjectName(QString::fromUtf8("m_pStatisticsPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(85);
        sizePolicy2.setVerticalStretch(27);
        sizePolicy2.setHeightForWidth(m_pStatisticsPushButton->sizePolicy().hasHeightForWidth());
        m_pStatisticsPushButton->setSizePolicy(sizePolicy2);
        m_pStatisticsPushButton->setLayoutDirection(Qt::RightToLeft);
        m_pStatisticsPushButton->setAutoDefault(false);

        gridLayout->addWidget(m_pStatisticsPushButton, 10, 2, 1, 1);

        m_pInternetInterfaceNameLabel = new QLabel(m_pInfoTab);
        m_pInternetInterfaceNameLabel->setObjectName(QString::fromUtf8("m_pInternetInterfaceNameLabel"));

        gridLayout->addWidget(m_pInternetInterfaceNameLabel, 1, 0, 1, 1);

        m_pInternetInterfaceName = new QLabel(m_pInfoTab);
        m_pInternetInterfaceName->setObjectName(QString::fromUtf8("m_pInternetInterfaceName"));

        gridLayout->addWidget(m_pInternetInterfaceName, 1, 1, 1, 1);

        m_pInternetInterfaceGatewayLabel = new QLabel(m_pInfoTab);
        m_pInternetInterfaceGatewayLabel->setObjectName(QString::fromUtf8("m_pInternetInterfaceGatewayLabel"));

        gridLayout->addWidget(m_pInternetInterfaceGatewayLabel, 2, 0, 1, 1);

        m_pInternetInterfaceGateway = new QLabel(m_pInfoTab);
        m_pInternetInterfaceGateway->setObjectName(QString::fromUtf8("m_pInternetInterfaceGateway"));

        gridLayout->addWidget(m_pInternetInterfaceGateway, 2, 1, 1, 1);

        m_pTabWidget->addTab(m_pInfoTab, QString());
        m_pLogTab = new QWidget();
        m_pLogTab->setObjectName(QString::fromUtf8("m_pLogTab"));
        m_pLogTabLayout = new QVBoxLayout(m_pLogTab);
        m_pLogTabLayout->setObjectName(QString::fromUtf8("m_pLogTabLayout"));
        m_pTextEdit = new QTextEdit(m_pLogTab);
        m_pTextEdit->setObjectName(QString::fromUtf8("m_pTextEdit"));
        m_pTextEdit->setReadOnly(true);

        m_pLogTabLayout->addWidget(m_pTextEdit);

        m_pTabWidget->addTab(m_pLogTab, QString());

        m_pDialogLayout->addWidget(m_pTabWidget);

        m_pButtonBox = new QDialogButtonBox(ConnectionInformationDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_pButtonBox->sizePolicy().hasHeightForWidth());
        m_pButtonBox->setSizePolicy(sizePolicy3);
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Close);

        m_pDialogLayout->addWidget(m_pButtonBox);

        QWidget::setTabOrder(m_pTabWidget, m_pStatisticsPushButton);
        QWidget::setTabOrder(m_pStatisticsPushButton, m_pButtonBox);
        QWidget::setTabOrder(m_pButtonBox, m_pTextEdit);

        retranslateUi(ConnectionInformationDialog);
        QObject::connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), ConnectionInformationDialog, SLOT(close()));

        m_pTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConnectionInformationDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionInformationDialog)
    {
        ConnectionInformationDialog->setWindowTitle(QApplication::translate("ConnectionInformationDialog", "L2TP IPSec VPN", 0));
        m_pGatewayLabel->setText(QApplication::translate("ConnectionInformationDialog", "Remote Server:", 0));
        m_pGateway->setText(QString());
        m_pInterfaceNameLabel->setText(QApplication::translate("ConnectionInformationDialog", "PtP Interface:", 0));
        m_pInterfaceName->setText(QString());
        m_pRemoteHostLabel->setText(QApplication::translate("ConnectionInformationDialog", "Destination Address:", 0));
        m_pRemoteHost->setText(QString());
        m_pIPlAddressLabel->setText(QApplication::translate("ConnectionInformationDialog", "IP Address:", 0));
        m_pIPAddress->setText(QString());
        m_pSubnetMaskLabel->setText(QApplication::translate("ConnectionInformationDialog", "Subnet Mask:", 0));
        m_pSubnetMask->setText(QString());
        m_pPrimaryDNSLabel->setText(QApplication::translate("ConnectionInformationDialog", "Primary DNS:", 0));
        m_pPrimaryDNS->setText(QString());
        m_pSecondaryDNSLabel->setText(QApplication::translate("ConnectionInformationDialog", "Secondary DNS:", 0));
        m_pSecondaryDNS->setText(QString());
        m_pTenaryDNSLabel->setText(QApplication::translate("ConnectionInformationDialog", "Tenary DNS:", 0));
        m_pTenaryDNS->setText(QString());
        m_pStatisticsPushButton->setText(QApplication::translate("ConnectionInformationDialog", "Statistics ...", 0));
        m_pInternetInterfaceNameLabel->setText(QApplication::translate("ConnectionInformationDialog", "Internet Interface:", 0));
        m_pInternetInterfaceName->setText(QString());
        m_pInternetInterfaceGatewayLabel->setText(QApplication::translate("ConnectionInformationDialog", "Internet Interface Gateway:", 0));
        m_pInternetInterfaceGateway->setText(QString());
        m_pTabWidget->setTabText(m_pTabWidget->indexOf(m_pInfoTab), QApplication::translate("ConnectionInformationDialog", "Info", 0));
        m_pTabWidget->setTabText(m_pTabWidget->indexOf(m_pLogTab), QApplication::translate("ConnectionInformationDialog", "Logs", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectionInformationDialog: public Ui_ConnectionInformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONINFORMATIONDIALOG_H
