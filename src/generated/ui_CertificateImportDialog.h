/********************************************************************************
** Form generated from reading UI file 'CertificateImportDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CERTIFICATEIMPORTDIALOG_H
#define UI_CERTIFICATEIMPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CertificateImportDialog
{
public:
    QVBoxLayout *m_pDialogLayout;
    QFrame *m_pP12Frame;
    QGridLayout *m_pFileFrameLayout;
    QLineEdit *m_pFileEdit;
    QPushButton *m_pBrowseFilePushButton;
    QTextEdit *m_pInfoTextEdit;
    QLabel *m_pFileLabel;
    QCheckBox *m_pSeletAutomaticallyCheckBox;
    QFrame *m_pPemFrame;
    QFormLayout *m_pPemFrameLayout;
    QLabel *m_pPrivateKeyPassphraseLabel;
    QLineEdit *m_pPrivateKeyPassphraseEdit;
    QLabel *m_pVerifyPrivateKeyPassphraseLabel;
    QLineEdit *m_pVerifyPrivateKeyPassphraseEdit;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *CertificateImportDialog)
    {
        if (CertificateImportDialog->objectName().isEmpty())
            CertificateImportDialog->setObjectName(QString::fromUtf8("CertificateImportDialog"));
        CertificateImportDialog->resize(515, 297);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        CertificateImportDialog->setWindowIcon(icon);
        CertificateImportDialog->setSizeGripEnabled(true);
        m_pDialogLayout = new QVBoxLayout(CertificateImportDialog);
        m_pDialogLayout->setObjectName(QString::fromUtf8("m_pDialogLayout"));
        m_pP12Frame = new QFrame(CertificateImportDialog);
        m_pP12Frame->setObjectName(QString::fromUtf8("m_pP12Frame"));
        m_pP12Frame->setFrameShape(QFrame::Box);
        m_pP12Frame->setFrameShadow(QFrame::Sunken);
        m_pFileFrameLayout = new QGridLayout(m_pP12Frame);
        m_pFileFrameLayout->setObjectName(QString::fromUtf8("m_pFileFrameLayout"));
        m_pFileEdit = new QLineEdit(m_pP12Frame);
        m_pFileEdit->setObjectName(QString::fromUtf8("m_pFileEdit"));
        m_pFileEdit->setReadOnly(true);

        m_pFileFrameLayout->addWidget(m_pFileEdit, 0, 1, 1, 1);

        m_pBrowseFilePushButton = new QPushButton(m_pP12Frame);
        m_pBrowseFilePushButton->setObjectName(QString::fromUtf8("m_pBrowseFilePushButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/search"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBrowseFilePushButton->setIcon(icon1);

        m_pFileFrameLayout->addWidget(m_pBrowseFilePushButton, 0, 2, 1, 1);

        m_pInfoTextEdit = new QTextEdit(m_pP12Frame);
        m_pInfoTextEdit->setObjectName(QString::fromUtf8("m_pInfoTextEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pInfoTextEdit->sizePolicy().hasHeightForWidth());
        m_pInfoTextEdit->setSizePolicy(sizePolicy);
        m_pInfoTextEdit->setMinimumSize(QSize(0, 80));
        m_pInfoTextEdit->setMaximumSize(QSize(16777215, 16777215));
        m_pInfoTextEdit->setAutoFillBackground(true);
        m_pInfoTextEdit->setFrameShape(QFrame::NoFrame);
        m_pInfoTextEdit->setFrameShadow(QFrame::Plain);
        m_pInfoTextEdit->setReadOnly(true);

        m_pFileFrameLayout->addWidget(m_pInfoTextEdit, 3, 0, 1, 3);

        m_pFileLabel = new QLabel(m_pP12Frame);
        m_pFileLabel->setObjectName(QString::fromUtf8("m_pFileLabel"));

        m_pFileFrameLayout->addWidget(m_pFileLabel, 0, 0, 1, 1);

        m_pSeletAutomaticallyCheckBox = new QCheckBox(m_pP12Frame);
        m_pSeletAutomaticallyCheckBox->setObjectName(QString::fromUtf8("m_pSeletAutomaticallyCheckBox"));
        m_pSeletAutomaticallyCheckBox->setChecked(true);

        m_pFileFrameLayout->addWidget(m_pSeletAutomaticallyCheckBox, 1, 0, 1, 2);


        m_pDialogLayout->addWidget(m_pP12Frame);

        m_pPemFrame = new QFrame(CertificateImportDialog);
        m_pPemFrame->setObjectName(QString::fromUtf8("m_pPemFrame"));
        m_pPemFrame->setFrameShape(QFrame::Box);
        m_pPemFrame->setFrameShadow(QFrame::Sunken);
        m_pPemFrameLayout = new QFormLayout(m_pPemFrame);
        m_pPemFrameLayout->setObjectName(QString::fromUtf8("m_pPemFrameLayout"));
        m_pPrivateKeyPassphraseLabel = new QLabel(m_pPemFrame);
        m_pPrivateKeyPassphraseLabel->setObjectName(QString::fromUtf8("m_pPrivateKeyPassphraseLabel"));

        m_pPemFrameLayout->setWidget(0, QFormLayout::LabelRole, m_pPrivateKeyPassphraseLabel);

        m_pPrivateKeyPassphraseEdit = new QLineEdit(m_pPemFrame);
        m_pPrivateKeyPassphraseEdit->setObjectName(QString::fromUtf8("m_pPrivateKeyPassphraseEdit"));
        m_pPrivateKeyPassphraseEdit->setEchoMode(QLineEdit::Password);

        m_pPemFrameLayout->setWidget(0, QFormLayout::FieldRole, m_pPrivateKeyPassphraseEdit);

        m_pVerifyPrivateKeyPassphraseLabel = new QLabel(m_pPemFrame);
        m_pVerifyPrivateKeyPassphraseLabel->setObjectName(QString::fromUtf8("m_pVerifyPrivateKeyPassphraseLabel"));

        m_pPemFrameLayout->setWidget(1, QFormLayout::LabelRole, m_pVerifyPrivateKeyPassphraseLabel);

        m_pVerifyPrivateKeyPassphraseEdit = new QLineEdit(m_pPemFrame);
        m_pVerifyPrivateKeyPassphraseEdit->setObjectName(QString::fromUtf8("m_pVerifyPrivateKeyPassphraseEdit"));
        m_pVerifyPrivateKeyPassphraseEdit->setEchoMode(QLineEdit::Password);

        m_pPemFrameLayout->setWidget(1, QFormLayout::FieldRole, m_pVerifyPrivateKeyPassphraseEdit);


        m_pDialogLayout->addWidget(m_pPemFrame);

        m_pButtonBox = new QDialogButtonBox(CertificateImportDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        m_pDialogLayout->addWidget(m_pButtonBox);

#ifndef QT_NO_SHORTCUT
        m_pFileLabel->setBuddy(m_pFileEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(m_pFileEdit, m_pBrowseFilePushButton);
        QWidget::setTabOrder(m_pBrowseFilePushButton, m_pSeletAutomaticallyCheckBox);
        QWidget::setTabOrder(m_pSeletAutomaticallyCheckBox, m_pInfoTextEdit);
        QWidget::setTabOrder(m_pInfoTextEdit, m_pPrivateKeyPassphraseEdit);
        QWidget::setTabOrder(m_pPrivateKeyPassphraseEdit, m_pVerifyPrivateKeyPassphraseEdit);
        QWidget::setTabOrder(m_pVerifyPrivateKeyPassphraseEdit, m_pButtonBox);

        retranslateUi(CertificateImportDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), CertificateImportDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), CertificateImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CertificateImportDialog);
    } // setupUi

    void retranslateUi(QDialog *CertificateImportDialog)
    {
        CertificateImportDialog->setWindowTitle(QApplication::translate("CertificateImportDialog", "Import Certificate Dialog", 0));
#ifndef QT_NO_TOOLTIP
        m_pFileEdit->setToolTip(QApplication::translate("CertificateImportDialog", "Full path to PKCS12 (*.p12, *.pfx) encoded certificate bundle file to import", 0));
#endif // QT_NO_TOOLTIP
        m_pBrowseFilePushButton->setText(QString());
        m_pFileLabel->setText(QApplication::translate("CertificateImportDialog", "PKCS12 File:", 0));
#ifndef QT_NO_TOOLTIP
        m_pSeletAutomaticallyCheckBox->setToolTip(QApplication::translate("CertificateImportDialog", "If checked. the imported certificate is automatically selected as IPsec authentication certificate ", 0));
#endif // QT_NO_TOOLTIP
        m_pSeletAutomaticallyCheckBox->setText(QApplication::translate("CertificateImportDialog", "Use this certificate for IPsec authentication", 0));
        m_pPrivateKeyPassphraseLabel->setText(QApplication::translate("CertificateImportDialog", "Private key passphrase:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPrivateKeyPassphraseEdit->setToolTip(QApplication::translate("CertificateImportDialog", "Enter the passphrase that shall be used to encrypt the imported private key", 0));
#endif // QT_NO_TOOLTIP
        m_pVerifyPrivateKeyPassphraseLabel->setText(QApplication::translate("CertificateImportDialog", "Verify private key passphrase:", 0));
#ifndef QT_NO_TOOLTIP
        m_pVerifyPrivateKeyPassphraseEdit->setToolTip(QApplication::translate("CertificateImportDialog", "Type the private key passphrase again to confirm", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class CertificateImportDialog: public Ui_CertificateImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CERTIFICATEIMPORTDIALOG_H
