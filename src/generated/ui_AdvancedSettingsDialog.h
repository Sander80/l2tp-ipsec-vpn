/********************************************************************************
** Form generated from reading UI file 'AdvancedSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCEDSETTINGSDIALOG_H
#define UI_ADVANCEDSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AdvancedSettingsDialog
{
public:
    QVBoxLayout *m_pDialogLayout;
    QGroupBox *m_pCompressionGroupBox;
    QVBoxLayout *m_pCompressionLayout;
    QCheckBox *m_pAllowBSDCompressionCheckBox;
    QCheckBox *m_pAllowDeflateCompressionCheckBox;
    QCheckBox *m_pUseTCPHeaderCompressionCheckBox;
    QGroupBox *m_pEchoGroupBox;
    QVBoxLayout *m_pEchoLayout;
    QCheckBox *m_pSendEchoCheckBox;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *AdvancedSettingsDialog)
    {
        if (AdvancedSettingsDialog->objectName().isEmpty())
            AdvancedSettingsDialog->setObjectName(QString::fromUtf8("AdvancedSettingsDialog"));
        AdvancedSettingsDialog->resize(305, 221);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        AdvancedSettingsDialog->setWindowIcon(icon);
        AdvancedSettingsDialog->setSizeGripEnabled(true);
        m_pDialogLayout = new QVBoxLayout(AdvancedSettingsDialog);
        m_pDialogLayout->setObjectName(QString::fromUtf8("m_pDialogLayout"));
        m_pCompressionGroupBox = new QGroupBox(AdvancedSettingsDialog);
        m_pCompressionGroupBox->setObjectName(QString::fromUtf8("m_pCompressionGroupBox"));
        m_pCompressionLayout = new QVBoxLayout(m_pCompressionGroupBox);
        m_pCompressionLayout->setObjectName(QString::fromUtf8("m_pCompressionLayout"));
        m_pAllowBSDCompressionCheckBox = new QCheckBox(m_pCompressionGroupBox);
        m_pAllowBSDCompressionCheckBox->setObjectName(QString::fromUtf8("m_pAllowBSDCompressionCheckBox"));

        m_pCompressionLayout->addWidget(m_pAllowBSDCompressionCheckBox);

        m_pAllowDeflateCompressionCheckBox = new QCheckBox(m_pCompressionGroupBox);
        m_pAllowDeflateCompressionCheckBox->setObjectName(QString::fromUtf8("m_pAllowDeflateCompressionCheckBox"));

        m_pCompressionLayout->addWidget(m_pAllowDeflateCompressionCheckBox);

        m_pUseTCPHeaderCompressionCheckBox = new QCheckBox(m_pCompressionGroupBox);
        m_pUseTCPHeaderCompressionCheckBox->setObjectName(QString::fromUtf8("m_pUseTCPHeaderCompressionCheckBox"));

        m_pCompressionLayout->addWidget(m_pUseTCPHeaderCompressionCheckBox);


        m_pDialogLayout->addWidget(m_pCompressionGroupBox);

        m_pEchoGroupBox = new QGroupBox(AdvancedSettingsDialog);
        m_pEchoGroupBox->setObjectName(QString::fromUtf8("m_pEchoGroupBox"));
        m_pEchoLayout = new QVBoxLayout(m_pEchoGroupBox);
        m_pEchoLayout->setObjectName(QString::fromUtf8("m_pEchoLayout"));
        m_pSendEchoCheckBox = new QCheckBox(m_pEchoGroupBox);
        m_pSendEchoCheckBox->setObjectName(QString::fromUtf8("m_pSendEchoCheckBox"));

        m_pEchoLayout->addWidget(m_pSendEchoCheckBox);


        m_pDialogLayout->addWidget(m_pEchoGroupBox);

        m_pButtonBox = new QDialogButtonBox(AdvancedSettingsDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);
        m_pButtonBox->setCenterButtons(true);

        m_pDialogLayout->addWidget(m_pButtonBox);

        QWidget::setTabOrder(m_pAllowBSDCompressionCheckBox, m_pAllowDeflateCompressionCheckBox);
        QWidget::setTabOrder(m_pAllowDeflateCompressionCheckBox, m_pUseTCPHeaderCompressionCheckBox);
        QWidget::setTabOrder(m_pUseTCPHeaderCompressionCheckBox, m_pSendEchoCheckBox);
        QWidget::setTabOrder(m_pSendEchoCheckBox, m_pButtonBox);

        retranslateUi(AdvancedSettingsDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), AdvancedSettingsDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), AdvancedSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AdvancedSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *AdvancedSettingsDialog)
    {
        AdvancedSettingsDialog->setWindowTitle(QApplication::translate("AdvancedSettingsDialog", "Advanced Settings", 0));
        m_pCompressionGroupBox->setTitle(QApplication::translate("AdvancedSettingsDialog", "Compression", 0));
        m_pAllowBSDCompressionCheckBox->setText(QApplication::translate("AdvancedSettingsDialog", "Allow &BSD data compression", 0));
        m_pAllowDeflateCompressionCheckBox->setText(QApplication::translate("AdvancedSettingsDialog", "Allow &Deflate data compression", 0));
        m_pUseTCPHeaderCompressionCheckBox->setText(QApplication::translate("AdvancedSettingsDialog", "Use TCP &header compression", 0));
        m_pEchoGroupBox->setTitle(QApplication::translate("AdvancedSettingsDialog", "Echo", 0));
        m_pSendEchoCheckBox->setText(QApplication::translate("AdvancedSettingsDialog", "Send PPP &echo packets", 0));
    } // retranslateUi

};

namespace Ui {
    class AdvancedSettingsDialog: public Ui_AdvancedSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCEDSETTINGSDIALOG_H
