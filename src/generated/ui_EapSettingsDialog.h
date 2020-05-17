/********************************************************************************
** Form generated from reading UI file 'EapSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EAPSETTINGSDIALOG_H
#define UI_EAPSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EapSettingsDialog
{
public:
    QVBoxLayout *m_pDialogLayout;
    QGroupBox *m_pConnectingGroupBox;
    QVBoxLayout *m_pConnectingGroupLayout;
    QRadioButton *m_pUseSmartCardRadioButton;
    QRadioButton *m_pUseCertificateRadioButton;
    QFrame *m_pCertificateFrame;
    QGridLayout *m_pCertificateFrameLayout;
    QLabel *m_pCertificateLabel;
    QLineEdit *m_pCertificateEdit;
    QPushButton *m_pBrowseCertificateButton;
    QLabel *m_pPrivateKeyLabel;
    QLineEdit *m_pPrivateKeyEdit;
    QPushButton *m_pBrowsePrivateKeyButton;
    QLabel *m_pPrivateKeyPwdLabel;
    QLineEdit *m_pPrivateKeyPwdEdit;
    QFrame *m_pCaCertificateFrame;
    QHBoxLayout *m_pCaCertificateFrameLayout;
    QLabel *m_pCaCertificateLabel;
    QLineEdit *m_pCaCertificateEdit;
    QPushButton *m_pBrowseCaCertificateButton;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *EapSettingsDialog)
    {
        if (EapSettingsDialog->objectName().isEmpty())
            EapSettingsDialog->setObjectName(QString::fromUtf8("EapSettingsDialog"));
        EapSettingsDialog->resize(502, 318);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        EapSettingsDialog->setWindowIcon(icon);
        EapSettingsDialog->setSizeGripEnabled(true);
        m_pDialogLayout = new QVBoxLayout(EapSettingsDialog);
        m_pDialogLayout->setObjectName(QString::fromUtf8("m_pDialogLayout"));
        m_pConnectingGroupBox = new QGroupBox(EapSettingsDialog);
        m_pConnectingGroupBox->setObjectName(QString::fromUtf8("m_pConnectingGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pConnectingGroupBox->sizePolicy().hasHeightForWidth());
        m_pConnectingGroupBox->setSizePolicy(sizePolicy);
        m_pConnectingGroupLayout = new QVBoxLayout(m_pConnectingGroupBox);
        m_pConnectingGroupLayout->setObjectName(QString::fromUtf8("m_pConnectingGroupLayout"));
        m_pUseSmartCardRadioButton = new QRadioButton(m_pConnectingGroupBox);
        m_pUseSmartCardRadioButton->setObjectName(QString::fromUtf8("m_pUseSmartCardRadioButton"));

        m_pConnectingGroupLayout->addWidget(m_pUseSmartCardRadioButton);

        m_pUseCertificateRadioButton = new QRadioButton(m_pConnectingGroupBox);
        m_pUseCertificateRadioButton->setObjectName(QString::fromUtf8("m_pUseCertificateRadioButton"));

        m_pConnectingGroupLayout->addWidget(m_pUseCertificateRadioButton);


        m_pDialogLayout->addWidget(m_pConnectingGroupBox);

        m_pCertificateFrame = new QFrame(EapSettingsDialog);
        m_pCertificateFrame->setObjectName(QString::fromUtf8("m_pCertificateFrame"));
        sizePolicy.setHeightForWidth(m_pCertificateFrame->sizePolicy().hasHeightForWidth());
        m_pCertificateFrame->setSizePolicy(sizePolicy);
        m_pCertificateFrame->setFrameShape(QFrame::Box);
        m_pCertificateFrame->setFrameShadow(QFrame::Sunken);
        m_pCertificateFrameLayout = new QGridLayout(m_pCertificateFrame);
        m_pCertificateFrameLayout->setObjectName(QString::fromUtf8("m_pCertificateFrameLayout"));
        m_pCertificateLabel = new QLabel(m_pCertificateFrame);
        m_pCertificateLabel->setObjectName(QString::fromUtf8("m_pCertificateLabel"));

        m_pCertificateFrameLayout->addWidget(m_pCertificateLabel, 0, 0, 1, 1);

        m_pCertificateEdit = new QLineEdit(m_pCertificateFrame);
        m_pCertificateEdit->setObjectName(QString::fromUtf8("m_pCertificateEdit"));
        m_pCertificateEdit->setReadOnly(true);

        m_pCertificateFrameLayout->addWidget(m_pCertificateEdit, 0, 1, 1, 1);

        m_pBrowseCertificateButton = new QPushButton(m_pCertificateFrame);
        m_pBrowseCertificateButton->setObjectName(QString::fromUtf8("m_pBrowseCertificateButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/search"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBrowseCertificateButton->setIcon(icon1);

        m_pCertificateFrameLayout->addWidget(m_pBrowseCertificateButton, 0, 2, 1, 1);

        m_pPrivateKeyLabel = new QLabel(m_pCertificateFrame);
        m_pPrivateKeyLabel->setObjectName(QString::fromUtf8("m_pPrivateKeyLabel"));

        m_pCertificateFrameLayout->addWidget(m_pPrivateKeyLabel, 1, 0, 1, 1);

        m_pPrivateKeyEdit = new QLineEdit(m_pCertificateFrame);
        m_pPrivateKeyEdit->setObjectName(QString::fromUtf8("m_pPrivateKeyEdit"));
        m_pPrivateKeyEdit->setReadOnly(true);

        m_pCertificateFrameLayout->addWidget(m_pPrivateKeyEdit, 1, 1, 1, 1);

        m_pBrowsePrivateKeyButton = new QPushButton(m_pCertificateFrame);
        m_pBrowsePrivateKeyButton->setObjectName(QString::fromUtf8("m_pBrowsePrivateKeyButton"));
        m_pBrowsePrivateKeyButton->setIcon(icon1);
        m_pBrowsePrivateKeyButton->setAutoDefault(false);

        m_pCertificateFrameLayout->addWidget(m_pBrowsePrivateKeyButton, 1, 2, 1, 1);

        m_pPrivateKeyPwdLabel = new QLabel(m_pCertificateFrame);
        m_pPrivateKeyPwdLabel->setObjectName(QString::fromUtf8("m_pPrivateKeyPwdLabel"));

        m_pCertificateFrameLayout->addWidget(m_pPrivateKeyPwdLabel, 2, 0, 1, 1);

        m_pPrivateKeyPwdEdit = new QLineEdit(m_pCertificateFrame);
        m_pPrivateKeyPwdEdit->setObjectName(QString::fromUtf8("m_pPrivateKeyPwdEdit"));
        m_pPrivateKeyPwdEdit->setEchoMode(QLineEdit::Password);
        m_pPrivateKeyPwdEdit->setReadOnly(false);

        m_pCertificateFrameLayout->addWidget(m_pPrivateKeyPwdEdit, 2, 1, 1, 1);


        m_pDialogLayout->addWidget(m_pCertificateFrame);

        m_pCaCertificateFrame = new QFrame(EapSettingsDialog);
        m_pCaCertificateFrame->setObjectName(QString::fromUtf8("m_pCaCertificateFrame"));
        sizePolicy.setHeightForWidth(m_pCaCertificateFrame->sizePolicy().hasHeightForWidth());
        m_pCaCertificateFrame->setSizePolicy(sizePolicy);
        m_pCaCertificateFrame->setFrameShape(QFrame::Box);
        m_pCaCertificateFrame->setFrameShadow(QFrame::Sunken);
        m_pCaCertificateFrameLayout = new QHBoxLayout(m_pCaCertificateFrame);
        m_pCaCertificateFrameLayout->setObjectName(QString::fromUtf8("m_pCaCertificateFrameLayout"));
        m_pCaCertificateLabel = new QLabel(m_pCaCertificateFrame);
        m_pCaCertificateLabel->setObjectName(QString::fromUtf8("m_pCaCertificateLabel"));

        m_pCaCertificateFrameLayout->addWidget(m_pCaCertificateLabel);

        m_pCaCertificateEdit = new QLineEdit(m_pCaCertificateFrame);
        m_pCaCertificateEdit->setObjectName(QString::fromUtf8("m_pCaCertificateEdit"));
        m_pCaCertificateEdit->setReadOnly(true);

        m_pCaCertificateFrameLayout->addWidget(m_pCaCertificateEdit);

        m_pBrowseCaCertificateButton = new QPushButton(m_pCaCertificateFrame);
        m_pBrowseCaCertificateButton->setObjectName(QString::fromUtf8("m_pBrowseCaCertificateButton"));
        m_pBrowseCaCertificateButton->setIcon(icon1);
        m_pBrowseCaCertificateButton->setAutoDefault(false);

        m_pCaCertificateFrameLayout->addWidget(m_pBrowseCaCertificateButton);


        m_pDialogLayout->addWidget(m_pCaCertificateFrame);

        m_pButtonBox = new QDialogButtonBox(EapSettingsDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        m_pDialogLayout->addWidget(m_pButtonBox);

#ifndef QT_NO_SHORTCUT
        m_pCertificateLabel->setBuddy(m_pCertificateEdit);
        m_pPrivateKeyLabel->setBuddy(m_pPrivateKeyEdit);
        m_pPrivateKeyPwdLabel->setBuddy(m_pPrivateKeyPwdEdit);
        m_pCaCertificateLabel->setBuddy(m_pCaCertificateEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(m_pUseSmartCardRadioButton, m_pUseCertificateRadioButton);
        QWidget::setTabOrder(m_pUseCertificateRadioButton, m_pCertificateEdit);
        QWidget::setTabOrder(m_pCertificateEdit, m_pBrowseCertificateButton);
        QWidget::setTabOrder(m_pBrowseCertificateButton, m_pPrivateKeyEdit);
        QWidget::setTabOrder(m_pPrivateKeyEdit, m_pBrowsePrivateKeyButton);
        QWidget::setTabOrder(m_pBrowsePrivateKeyButton, m_pPrivateKeyPwdEdit);
        QWidget::setTabOrder(m_pPrivateKeyPwdEdit, m_pCaCertificateEdit);
        QWidget::setTabOrder(m_pCaCertificateEdit, m_pBrowseCaCertificateButton);
        QWidget::setTabOrder(m_pBrowseCaCertificateButton, m_pButtonBox);

        retranslateUi(EapSettingsDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), EapSettingsDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), EapSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EapSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *EapSettingsDialog)
    {
        EapSettingsDialog->setWindowTitle(QApplication::translate("EapSettingsDialog", "EAP settings", 0));
        m_pConnectingGroupBox->setTitle(QApplication::translate("EapSettingsDialog", "When connecting", 0));
        m_pUseSmartCardRadioButton->setText(QApplication::translate("EapSettingsDialog", "Use my smart card", 0));
        m_pUseCertificateRadioButton->setText(QApplication::translate("EapSettingsDialog", "Use a certificate on this computer", 0));
        m_pCertificateLabel->setText(QApplication::translate("EapSettingsDialog", "User certificate:", 0));
#ifndef QT_NO_TOOLTIP
        m_pCertificateEdit->setToolTip(QApplication::translate("EapSettingsDialog", "Full path to a X.509 encoded personal certificate file", 0));
#endif // QT_NO_TOOLTIP
        m_pBrowseCertificateButton->setText(QString());
        m_pPrivateKeyLabel->setText(QApplication::translate("EapSettingsDialog", "Private key:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPrivateKeyEdit->setToolTip(QApplication::translate("EapSettingsDialog", "Full path to a X.509 pem encoded private key file", 0));
#endif // QT_NO_TOOLTIP
        m_pBrowsePrivateKeyButton->setText(QString());
        m_pPrivateKeyPwdLabel->setText(QApplication::translate("EapSettingsDialog", "Passphrase:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPrivateKeyPwdEdit->setToolTip(QApplication::translate("EapSettingsDialog", "Enter the PIN or passphrase for your private key.\n"
"\n"
"If left empty you'll be ask each time you try to establish a connection.", 0));
#endif // QT_NO_TOOLTIP
        m_pCaCertificateLabel->setText(QApplication::translate("EapSettingsDialog", "CA Certificate:", 0));
#ifndef QT_NO_TOOLTIP
        m_pCaCertificateEdit->setToolTip(QApplication::translate("EapSettingsDialog", "Full path to a X.509 pem encoded Certificate Authority certificate file", 0));
#endif // QT_NO_TOOLTIP
        m_pBrowseCaCertificateButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EapSettingsDialog: public Ui_EapSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EAPSETTINGSDIALOG_H
