/********************************************************************************
** Form generated from reading UI file 'IpSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPSETTINGSDIALOG_H
#define UI_IPSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_IpSettingsDialog
{
public:
    QGridLayout *m_pDialogLayout;
    QFrame *m_pFrame;
    QGridLayout *m_pFrameLayout;
    QCheckBox *m_pAutomaticDNSCheckBox;
    QLabel *m_pPrimaryDNSServersLabel;
    QLineEdit *m_pPrimaryDNSServersEdit;
    QLabel *m_pSecundaryDNSServersLabel;
    QLineEdit *m_pSecundaryDNSServersEdit;
    QLabel *m_pSearchDomainsLabel;
    QLineEdit *m_pSearchDomainsEdit;
    QPushButton *m_pRoutesButton;
    QSpacerItem *m_pVerticalSpacer;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *IpSettingsDialog)
    {
        if (IpSettingsDialog->objectName().isEmpty())
            IpSettingsDialog->setObjectName(QString::fromUtf8("IpSettingsDialog"));
        IpSettingsDialog->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        IpSettingsDialog->setWindowIcon(icon);
        IpSettingsDialog->setSizeGripEnabled(true);
        m_pDialogLayout = new QGridLayout(IpSettingsDialog);
        m_pDialogLayout->setObjectName(QString::fromUtf8("m_pDialogLayout"));
        m_pFrame = new QFrame(IpSettingsDialog);
        m_pFrame->setObjectName(QString::fromUtf8("m_pFrame"));
        m_pFrame->setFrameShape(QFrame::Box);
        m_pFrame->setFrameShadow(QFrame::Sunken);
        m_pFrameLayout = new QGridLayout(m_pFrame);
        m_pFrameLayout->setObjectName(QString::fromUtf8("m_pFrameLayout"));
        m_pAutomaticDNSCheckBox = new QCheckBox(m_pFrame);
        m_pAutomaticDNSCheckBox->setObjectName(QString::fromUtf8("m_pAutomaticDNSCheckBox"));

        m_pFrameLayout->addWidget(m_pAutomaticDNSCheckBox, 0, 0, 1, 3);

        m_pPrimaryDNSServersLabel = new QLabel(m_pFrame);
        m_pPrimaryDNSServersLabel->setObjectName(QString::fromUtf8("m_pPrimaryDNSServersLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pPrimaryDNSServersLabel->sizePolicy().hasHeightForWidth());
        m_pPrimaryDNSServersLabel->setSizePolicy(sizePolicy);

        m_pFrameLayout->addWidget(m_pPrimaryDNSServersLabel, 1, 0, 1, 1);

        m_pPrimaryDNSServersEdit = new QLineEdit(m_pFrame);
        m_pPrimaryDNSServersEdit->setObjectName(QString::fromUtf8("m_pPrimaryDNSServersEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pPrimaryDNSServersEdit->sizePolicy().hasHeightForWidth());
        m_pPrimaryDNSServersEdit->setSizePolicy(sizePolicy1);

        m_pFrameLayout->addWidget(m_pPrimaryDNSServersEdit, 1, 1, 1, 2);

        m_pSecundaryDNSServersLabel = new QLabel(m_pFrame);
        m_pSecundaryDNSServersLabel->setObjectName(QString::fromUtf8("m_pSecundaryDNSServersLabel"));
        sizePolicy.setHeightForWidth(m_pSecundaryDNSServersLabel->sizePolicy().hasHeightForWidth());
        m_pSecundaryDNSServersLabel->setSizePolicy(sizePolicy);

        m_pFrameLayout->addWidget(m_pSecundaryDNSServersLabel, 2, 0, 1, 1);

        m_pSecundaryDNSServersEdit = new QLineEdit(m_pFrame);
        m_pSecundaryDNSServersEdit->setObjectName(QString::fromUtf8("m_pSecundaryDNSServersEdit"));

        m_pFrameLayout->addWidget(m_pSecundaryDNSServersEdit, 2, 1, 1, 2);

        m_pSearchDomainsLabel = new QLabel(m_pFrame);
        m_pSearchDomainsLabel->setObjectName(QString::fromUtf8("m_pSearchDomainsLabel"));
        sizePolicy.setHeightForWidth(m_pSearchDomainsLabel->sizePolicy().hasHeightForWidth());
        m_pSearchDomainsLabel->setSizePolicy(sizePolicy);

        m_pFrameLayout->addWidget(m_pSearchDomainsLabel, 3, 0, 1, 1);

        m_pSearchDomainsEdit = new QLineEdit(m_pFrame);
        m_pSearchDomainsEdit->setObjectName(QString::fromUtf8("m_pSearchDomainsEdit"));

        m_pFrameLayout->addWidget(m_pSearchDomainsEdit, 3, 1, 1, 2);

        m_pRoutesButton = new QPushButton(m_pFrame);
        m_pRoutesButton->setObjectName(QString::fromUtf8("m_pRoutesButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pRoutesButton->sizePolicy().hasHeightForWidth());
        m_pRoutesButton->setSizePolicy(sizePolicy2);
        m_pRoutesButton->setMinimumSize(QSize(85, 27));
        m_pRoutesButton->setLayoutDirection(Qt::LeftToRight);
        m_pRoutesButton->setAutoDefault(false);

        m_pFrameLayout->addWidget(m_pRoutesButton, 5, 2, 1, 1);

        m_pVerticalSpacer = new QSpacerItem(20, 23, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_pFrameLayout->addItem(m_pVerticalSpacer, 4, 0, 1, 3);


        m_pDialogLayout->addWidget(m_pFrame, 0, 0, 1, 1);

        m_pButtonBox = new QDialogButtonBox(IpSettingsDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        m_pDialogLayout->addWidget(m_pButtonBox, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        m_pPrimaryDNSServersLabel->setBuddy(m_pPrimaryDNSServersEdit);
        m_pSecundaryDNSServersLabel->setBuddy(m_pSecundaryDNSServersEdit);
        m_pSearchDomainsLabel->setBuddy(m_pSearchDomainsEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(m_pAutomaticDNSCheckBox, m_pPrimaryDNSServersEdit);
        QWidget::setTabOrder(m_pPrimaryDNSServersEdit, m_pSecundaryDNSServersEdit);
        QWidget::setTabOrder(m_pSecundaryDNSServersEdit, m_pSearchDomainsEdit);
        QWidget::setTabOrder(m_pSearchDomainsEdit, m_pRoutesButton);
        QWidget::setTabOrder(m_pRoutesButton, m_pButtonBox);

        retranslateUi(IpSettingsDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), IpSettingsDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), IpSettingsDialog, SLOT(reject()));
        QObject::connect(m_pAutomaticDNSCheckBox, SIGNAL(toggled(bool)), m_pPrimaryDNSServersEdit, SLOT(setDisabled(bool)));
        QObject::connect(m_pAutomaticDNSCheckBox, SIGNAL(toggled(bool)), m_pSecundaryDNSServersEdit, SLOT(setDisabled(bool)));
        QObject::connect(m_pAutomaticDNSCheckBox, SIGNAL(toggled(bool)), m_pSearchDomainsEdit, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(IpSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *IpSettingsDialog)
    {
        IpSettingsDialog->setWindowTitle(QApplication::translate("IpSettingsDialog", "IpSettingsDialog", 0));
#ifndef QT_NO_TOOLTIP
        m_pAutomaticDNSCheckBox->setToolTip(QApplication::translate("IpSettingsDialog", "If checked the peer is asked for up to 2 DNS server addresses, otherwise provide the desired primary and secundary DNS server addresses manually in the edit boxes below.", 0));
#endif // QT_NO_TOOLTIP
        m_pAutomaticDNSCheckBox->setText(QApplication::translate("IpSettingsDialog", "Obtain DNS server addresses automatically", 0));
        m_pPrimaryDNSServersLabel->setText(QApplication::translate("IpSettingsDialog", "Preferred DNS server:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPrimaryDNSServersEdit->setToolTip(QApplication::translate("IpSettingsDialog", "Ip addresses of preferred domain name server used to resolve host names. Address must be entered as IPv4 address.\n"
"\n"
"Example:\n"
"1.2.3.4", 0));
#endif // QT_NO_TOOLTIP
        m_pSecundaryDNSServersLabel->setText(QApplication::translate("IpSettingsDialog", "Alternate DNS server:", 0));
#ifndef QT_NO_TOOLTIP
        m_pSecundaryDNSServersEdit->setToolTip(QApplication::translate("IpSettingsDialog", "Ip addresses of alternate domain name server used to resolve host names. Address must be entered as IPv4 address.\n"
"\n"
"Example:\n"
"1.2.3.4", 0));
#endif // QT_NO_TOOLTIP
        m_pSearchDomainsLabel->setText(QApplication::translate("IpSettingsDialog", "Search domains:", 0));
#ifndef QT_NO_TOOLTIP
        m_pSearchDomainsEdit->setToolTip(QApplication::translate("IpSettingsDialog", "Domains used when resolving hostnames.\n"
"Use spaces to separate multiple domains.", 0));
#endif // QT_NO_TOOLTIP
        m_pRoutesButton->setText(QApplication::translate("IpSettingsDialog", "Routes ...", 0));
    } // retranslateUi

};

namespace Ui {
    class IpSettingsDialog: public Ui_IpSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPSETTINGSDIALOG_H
