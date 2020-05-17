/********************************************************************************
** Form generated from reading UI file 'InterfaceStatisticsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACESTATISTICSDIALOG_H
#define UI_INTERFACESTATISTICSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_InterfaceStatisticsDialog
{
public:
    QFormLayout *formLayout;
    QLabel *m_pTransmittedBytesLabel;
    QLabel *m_pTransmittedBytes;
    QLabel *m_pTransmittedPacketsLabel;
    QLabel *m_pTransmittedPackets;
    QLabel *m_pTransmissionErrorsLabel;
    QLabel *m_pTransmissionErrors;
    QSpacerItem *m_pVerticalSpacer1;
    QLabel *m_pReceivedBytesLabel;
    QLabel *m_pReceivedBytes;
    QLabel *m_pReceivedPacketsLabel;
    QLabel *m_pReceivedPackets;
    QLabel *m_pReceptionErrorsLabel;
    QLabel *m_pReceptionErrors;
    QSpacerItem *m_pVerticalSpacer2;
    QLabel *m_pSinceLabel;
    QLabel *m_pSince;
    QLabel *m_pConnectionTimeLabel;
    QLabel *m_pConnectionTime;
    QDialogButtonBox *m_pButtonBox;
    QSpacerItem *m_pVerticalSpacer3;
    QLabel *m_pCollisionsLabel;
    QLabel *m_pCollisions;

    void setupUi(QDialog *InterfaceStatisticsDialog)
    {
        if (InterfaceStatisticsDialog->objectName().isEmpty())
            InterfaceStatisticsDialog->setObjectName(QString::fromUtf8("InterfaceStatisticsDialog"));
        InterfaceStatisticsDialog->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connectEstablished"), QSize(), QIcon::Normal, QIcon::Off);
        InterfaceStatisticsDialog->setWindowIcon(icon);
        InterfaceStatisticsDialog->setSizeGripEnabled(true);
        formLayout = new QFormLayout(InterfaceStatisticsDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_pTransmittedBytesLabel = new QLabel(InterfaceStatisticsDialog);
        m_pTransmittedBytesLabel->setObjectName(QString::fromUtf8("m_pTransmittedBytesLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, m_pTransmittedBytesLabel);

        m_pTransmittedBytes = new QLabel(InterfaceStatisticsDialog);
        m_pTransmittedBytes->setObjectName(QString::fromUtf8("m_pTransmittedBytes"));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_pTransmittedBytes);

        m_pTransmittedPacketsLabel = new QLabel(InterfaceStatisticsDialog);
        m_pTransmittedPacketsLabel->setObjectName(QString::fromUtf8("m_pTransmittedPacketsLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, m_pTransmittedPacketsLabel);

        m_pTransmittedPackets = new QLabel(InterfaceStatisticsDialog);
        m_pTransmittedPackets->setObjectName(QString::fromUtf8("m_pTransmittedPackets"));

        formLayout->setWidget(1, QFormLayout::FieldRole, m_pTransmittedPackets);

        m_pTransmissionErrorsLabel = new QLabel(InterfaceStatisticsDialog);
        m_pTransmissionErrorsLabel->setObjectName(QString::fromUtf8("m_pTransmissionErrorsLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, m_pTransmissionErrorsLabel);

        m_pTransmissionErrors = new QLabel(InterfaceStatisticsDialog);
        m_pTransmissionErrors->setObjectName(QString::fromUtf8("m_pTransmissionErrors"));

        formLayout->setWidget(2, QFormLayout::FieldRole, m_pTransmissionErrors);

        m_pVerticalSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(4, QFormLayout::LabelRole, m_pVerticalSpacer1);

        m_pReceivedBytesLabel = new QLabel(InterfaceStatisticsDialog);
        m_pReceivedBytesLabel->setObjectName(QString::fromUtf8("m_pReceivedBytesLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, m_pReceivedBytesLabel);

        m_pReceivedBytes = new QLabel(InterfaceStatisticsDialog);
        m_pReceivedBytes->setObjectName(QString::fromUtf8("m_pReceivedBytes"));

        formLayout->setWidget(5, QFormLayout::FieldRole, m_pReceivedBytes);

        m_pReceivedPacketsLabel = new QLabel(InterfaceStatisticsDialog);
        m_pReceivedPacketsLabel->setObjectName(QString::fromUtf8("m_pReceivedPacketsLabel"));

        formLayout->setWidget(6, QFormLayout::LabelRole, m_pReceivedPacketsLabel);

        m_pReceivedPackets = new QLabel(InterfaceStatisticsDialog);
        m_pReceivedPackets->setObjectName(QString::fromUtf8("m_pReceivedPackets"));

        formLayout->setWidget(6, QFormLayout::FieldRole, m_pReceivedPackets);

        m_pReceptionErrorsLabel = new QLabel(InterfaceStatisticsDialog);
        m_pReceptionErrorsLabel->setObjectName(QString::fromUtf8("m_pReceptionErrorsLabel"));

        formLayout->setWidget(7, QFormLayout::LabelRole, m_pReceptionErrorsLabel);

        m_pReceptionErrors = new QLabel(InterfaceStatisticsDialog);
        m_pReceptionErrors->setObjectName(QString::fromUtf8("m_pReceptionErrors"));

        formLayout->setWidget(7, QFormLayout::FieldRole, m_pReceptionErrors);

        m_pVerticalSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(9, QFormLayout::LabelRole, m_pVerticalSpacer2);

        m_pSinceLabel = new QLabel(InterfaceStatisticsDialog);
        m_pSinceLabel->setObjectName(QString::fromUtf8("m_pSinceLabel"));

        formLayout->setWidget(10, QFormLayout::LabelRole, m_pSinceLabel);

        m_pSince = new QLabel(InterfaceStatisticsDialog);
        m_pSince->setObjectName(QString::fromUtf8("m_pSince"));

        formLayout->setWidget(10, QFormLayout::FieldRole, m_pSince);

        m_pConnectionTimeLabel = new QLabel(InterfaceStatisticsDialog);
        m_pConnectionTimeLabel->setObjectName(QString::fromUtf8("m_pConnectionTimeLabel"));

        formLayout->setWidget(11, QFormLayout::LabelRole, m_pConnectionTimeLabel);

        m_pConnectionTime = new QLabel(InterfaceStatisticsDialog);
        m_pConnectionTime->setObjectName(QString::fromUtf8("m_pConnectionTime"));

        formLayout->setWidget(11, QFormLayout::FieldRole, m_pConnectionTime);

        m_pButtonBox = new QDialogButtonBox(InterfaceStatisticsDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Close);

        formLayout->setWidget(13, QFormLayout::SpanningRole, m_pButtonBox);

        m_pVerticalSpacer3 = new QSpacerItem(20, 10000, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(12, QFormLayout::LabelRole, m_pVerticalSpacer3);

        m_pCollisionsLabel = new QLabel(InterfaceStatisticsDialog);
        m_pCollisionsLabel->setObjectName(QString::fromUtf8("m_pCollisionsLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, m_pCollisionsLabel);

        m_pCollisions = new QLabel(InterfaceStatisticsDialog);
        m_pCollisions->setObjectName(QString::fromUtf8("m_pCollisions"));

        formLayout->setWidget(3, QFormLayout::FieldRole, m_pCollisions);


        retranslateUi(InterfaceStatisticsDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), InterfaceStatisticsDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), InterfaceStatisticsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InterfaceStatisticsDialog);
    } // setupUi

    void retranslateUi(QDialog *InterfaceStatisticsDialog)
    {
        InterfaceStatisticsDialog->setWindowTitle(QApplication::translate("InterfaceStatisticsDialog", "Interface Statistics", 0));
        m_pTransmittedBytesLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Transmitted bytes:", 0));
        m_pTransmittedBytes->setText(QString());
        m_pTransmittedPacketsLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Transmitted packets:", 0));
        m_pTransmittedPackets->setText(QString());
        m_pTransmissionErrorsLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Transmission errors:", 0));
        m_pTransmissionErrors->setText(QString());
        m_pReceivedBytesLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Received bytes:", 0));
        m_pReceivedBytes->setText(QString());
        m_pReceivedPacketsLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Received packets:", 0));
        m_pReceivedPackets->setText(QString());
        m_pReceptionErrorsLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Reception errors:", 0));
        m_pReceptionErrors->setText(QString());
        m_pSinceLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Connected since:", 0));
        m_pSince->setText(QString());
        m_pConnectionTimeLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Connection time:", 0));
        m_pConnectionTime->setText(QString());
        m_pCollisionsLabel->setText(QApplication::translate("InterfaceStatisticsDialog", "Collisions:", 0));
        m_pCollisions->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceStatisticsDialog: public Ui_InterfaceStatisticsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACESTATISTICSDIALOG_H
