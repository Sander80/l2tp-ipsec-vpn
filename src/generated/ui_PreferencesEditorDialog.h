/********************************************************************************
** Form generated from reading UI file 'PreferencesEditorDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESEDITORDIALOG_H
#define UI_PREFERENCESEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesEditorDialog
{
public:
    QVBoxLayout *m_pDialogLayout;
    QTabWidget *m_pTabWidget;
    QWidget *m_pTabOpenSSL;
    QGridLayout *m_pOpenSSLTabLayout;
    QLabel *m_pEngineIdLabel;
    QLineEdit *m_pEngineIDLineEdit;
    QLabel *m_pEnginPathLabel;
    QLineEdit *m_pEnginePathLineEdit;
    QPushButton *m_pEnginePathPushButton;
    QLabel *m_pPkcs11PathLabel;
    QLineEdit *m_pPkcs11PathLineEdit;
    QPushButton *m_pPkcs11PathPushButton;
    QSpacerItem *m_pOpenSSLVerticalSpacer;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *PreferencesEditorDialog)
    {
        if (PreferencesEditorDialog->objectName().isEmpty())
            PreferencesEditorDialog->setObjectName(QString::fromUtf8("PreferencesEditorDialog"));
        PreferencesEditorDialog->resize(451, 208);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        PreferencesEditorDialog->setWindowIcon(icon);
        PreferencesEditorDialog->setSizeGripEnabled(true);
        m_pDialogLayout = new QVBoxLayout(PreferencesEditorDialog);
        m_pDialogLayout->setObjectName(QString::fromUtf8("m_pDialogLayout"));
        m_pTabWidget = new QTabWidget(PreferencesEditorDialog);
        m_pTabWidget->setObjectName(QString::fromUtf8("m_pTabWidget"));
        m_pTabOpenSSL = new QWidget();
        m_pTabOpenSSL->setObjectName(QString::fromUtf8("m_pTabOpenSSL"));
        m_pOpenSSLTabLayout = new QGridLayout(m_pTabOpenSSL);
        m_pOpenSSLTabLayout->setObjectName(QString::fromUtf8("m_pOpenSSLTabLayout"));
        m_pEngineIdLabel = new QLabel(m_pTabOpenSSL);
        m_pEngineIdLabel->setObjectName(QString::fromUtf8("m_pEngineIdLabel"));

        m_pOpenSSLTabLayout->addWidget(m_pEngineIdLabel, 0, 0, 1, 1);

        m_pEngineIDLineEdit = new QLineEdit(m_pTabOpenSSL);
        m_pEngineIDLineEdit->setObjectName(QString::fromUtf8("m_pEngineIDLineEdit"));

        m_pOpenSSLTabLayout->addWidget(m_pEngineIDLineEdit, 0, 1, 1, 1);

        m_pEnginPathLabel = new QLabel(m_pTabOpenSSL);
        m_pEnginPathLabel->setObjectName(QString::fromUtf8("m_pEnginPathLabel"));

        m_pOpenSSLTabLayout->addWidget(m_pEnginPathLabel, 1, 0, 1, 1);

        m_pEnginePathLineEdit = new QLineEdit(m_pTabOpenSSL);
        m_pEnginePathLineEdit->setObjectName(QString::fromUtf8("m_pEnginePathLineEdit"));
        m_pEnginePathLineEdit->setReadOnly(true);

        m_pOpenSSLTabLayout->addWidget(m_pEnginePathLineEdit, 1, 1, 1, 1);

        m_pEnginePathPushButton = new QPushButton(m_pTabOpenSSL);
        m_pEnginePathPushButton->setObjectName(QString::fromUtf8("m_pEnginePathPushButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/search"), QSize(), QIcon::Normal, QIcon::Off);
        m_pEnginePathPushButton->setIcon(icon1);

        m_pOpenSSLTabLayout->addWidget(m_pEnginePathPushButton, 1, 2, 1, 1);

        m_pPkcs11PathLabel = new QLabel(m_pTabOpenSSL);
        m_pPkcs11PathLabel->setObjectName(QString::fromUtf8("m_pPkcs11PathLabel"));

        m_pOpenSSLTabLayout->addWidget(m_pPkcs11PathLabel, 2, 0, 1, 1);

        m_pPkcs11PathLineEdit = new QLineEdit(m_pTabOpenSSL);
        m_pPkcs11PathLineEdit->setObjectName(QString::fromUtf8("m_pPkcs11PathLineEdit"));
        m_pPkcs11PathLineEdit->setReadOnly(true);

        m_pOpenSSLTabLayout->addWidget(m_pPkcs11PathLineEdit, 2, 1, 1, 1);

        m_pPkcs11PathPushButton = new QPushButton(m_pTabOpenSSL);
        m_pPkcs11PathPushButton->setObjectName(QString::fromUtf8("m_pPkcs11PathPushButton"));
        m_pPkcs11PathPushButton->setIcon(icon1);

        m_pOpenSSLTabLayout->addWidget(m_pPkcs11PathPushButton, 2, 2, 1, 1);

        m_pOpenSSLVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_pOpenSSLTabLayout->addItem(m_pOpenSSLVerticalSpacer, 3, 0, 1, 1);

        m_pTabWidget->addTab(m_pTabOpenSSL, QString());

        m_pDialogLayout->addWidget(m_pTabWidget);

        m_pButtonBox = new QDialogButtonBox(PreferencesEditorDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        m_pDialogLayout->addWidget(m_pButtonBox);

#ifndef QT_NO_SHORTCUT
        m_pEngineIdLabel->setBuddy(m_pEngineIDLineEdit);
        m_pEnginPathLabel->setBuddy(m_pEnginePathLineEdit);
        m_pPkcs11PathLabel->setBuddy(m_pPkcs11PathLineEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(m_pTabWidget, m_pEngineIDLineEdit);
        QWidget::setTabOrder(m_pEngineIDLineEdit, m_pEnginePathLineEdit);
        QWidget::setTabOrder(m_pEnginePathLineEdit, m_pEnginePathPushButton);
        QWidget::setTabOrder(m_pEnginePathPushButton, m_pPkcs11PathLineEdit);
        QWidget::setTabOrder(m_pPkcs11PathLineEdit, m_pPkcs11PathPushButton);
        QWidget::setTabOrder(m_pPkcs11PathPushButton, m_pButtonBox);

        retranslateUi(PreferencesEditorDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), PreferencesEditorDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), PreferencesEditorDialog, SLOT(reject()));

        m_pTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PreferencesEditorDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesEditorDialog)
    {
        PreferencesEditorDialog->setWindowTitle(QApplication::translate("PreferencesEditorDialog", "Preferences", 0));
        m_pEngineIdLabel->setText(QApplication::translate("PreferencesEditorDialog", "Engine &ID:", 0));
#ifndef QT_NO_TOOLTIP
        m_pEngineIDLineEdit->setToolTip(QApplication::translate("PreferencesEditorDialog", "Unique identifier for OpenSSL engine", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        m_pEngineIDLineEdit->setWhatsThis(QApplication::translate("PreferencesEditorDialog", "Unique identifier for OpenSSL engine", 0));
#endif // QT_NO_WHATSTHIS
        m_pEnginPathLabel->setText(QApplication::translate("PreferencesEditorDialog", "&Engine Path:", 0));
#ifndef QT_NO_TOOLTIP
        m_pEnginePathLineEdit->setToolTip(QApplication::translate("PreferencesEditorDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Full path to a shared library implementing the <a href=\"http://www.openssl.org/docs/crypto/engine.html\"><span style=\" text-decoration: underline; color:#0000ff;\">OpenSSL engine interface</span></a></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        m_pEnginePathLineEdit->setWhatsThis(QApplication::translate("PreferencesEditorDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Full path to a shared library implementing the <a href=\"http://www.openssl.org/docs/crypto/engine.html\"><span style=\" text-decoration: underline; color:#0000ff;\">OpenSSL engine interface</span></a></p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        m_pEnginePathPushButton->setText(QString());
        m_pPkcs11PathLabel->setText(QApplication::translate("PreferencesEditorDialog", "&PKCS 11 Path:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPkcs11PathLineEdit->setToolTip(QApplication::translate("PreferencesEditorDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Full path to a shared library implementing the <a href=\"http://www.rsa.com/rsalabs/node.asp?id=2133\"><span style=\" text-decoration: underline; color:#0000ff;\">Cryptographic Token Interface</span></a></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        m_pPkcs11PathLineEdit->setWhatsThis(QApplication::translate("PreferencesEditorDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Full path to a shared library implementing the <a href=\"http://www.rsa.com/rsalabs/node.asp?id=2133\"><span style=\" text-decoration: underline; color:#0000ff;\">Cryptographic Token Interface</span></a></p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        m_pPkcs11PathPushButton->setText(QString());
        m_pTabWidget->setTabText(m_pTabWidget->indexOf(m_pTabOpenSSL), QApplication::translate("PreferencesEditorDialog", "OpenSSL", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesEditorDialog: public Ui_PreferencesEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESEDITORDIALOG_H
