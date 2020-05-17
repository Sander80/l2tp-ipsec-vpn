/********************************************************************************
** Form generated from reading UI file 'ConnectionSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONSETTINGSDIALOG_H
#define UI_CONNECTIONSETTINGSDIALOG_H

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
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionSettingsDialog
{
public:
    QGridLayout *m_pDialogGridLayout;
    QFormLayout *m_pConnectionNameLayout;
    QLabel *m_pConnectionNameLabel;
    QLineEdit *m_pConnectionNameEdit;
    QCheckBox *m_pConnectAutomatically;
    QTabWidget *m_pTabWidget;
    QWidget *m_pTabIPsec;
    QGridLayout *m_pIPsecTabLayout;
    QFormLayout *m_pIPsecGatewayLayout;
    QLabel *m_pIPsecGatewayLabel;
    QLineEdit *m_pIPsecGatewayEdit;
    QLabel *m_pIPsecIdentityLabel;
    QLineEdit *m_pIPsecIdentityEdit;
    QRadioButton *m_pIPsecUsePreSharedKeyRadioButton;
    QLineEdit *m_pIPsecPreSharedKeyEdit;
    QRadioButton *m_pIPsecUseCertificateRadioButton;
    QListView *m_pIPsecCertificateListView;
    QFrame *m_pIPsecPrivateKeyFrame;
    QGridLayout *m_pIPsecPrivateKeyLayout;
    QLabel *m_pIPsecPrivateKeyLabel;
    QLineEdit *m_pIPsecPrivateKeyFileEdit;
    QLabel *m_pIPsecPassphraseLabel;
    QLineEdit *m_pIPsecPassphraseEdit;
    QPushButton *m_pIPsecBrowsePrivateKeyButton;
    QPushButton *m_pImportPushButton;
    QWidget *m_pTabL2TP;
    QGridLayout *m_pL2tpTabLayout;
    QCheckBox *m_pL2tpRedialCheckBox;
    QCheckBox *m_pL2tpLengthBitCheckBox;
    QFormLayout *m_pL2tpRedialLayout;
    QLabel *m_pL2tpRedialTimeoutLabel;
    QSpinBox *m_pL2tpRedialTimeoutSpinBox;
    QLabel *m_pL2tpRedialAttemptsLabel;
    QSpinBox *m_pL2tpRedialAttemptsSpinBox;
    QWidget *m_pTabPpp;
    QGridLayout *m_pPppTabLayout;
    QRadioButton *m_pPppUseEAPRadioButton;
    QPushButton *m_pPppPropertiesButton;
    QRadioButton *m_pPppAllowProtocolsRadioButton;
    QListWidget *m_pPppAllowProtocolsListWidget;
    QFrame *m_pPppCredentialsFrame;
    QGridLayout *m_pIPsecCredentialsLayout;
    QLabel *m_pPppUserNameLabel;
    QLineEdit *m_pPppUserNameEdit;
    QLabel *m_pPppPwdLabel;
    QLineEdit *m_pPppPwdEdit;
    QPushButton *m_pPppPeerAuthenticationButton;
    QPushButton *m_pPppIpSettingsButton;
    QPushButton *m_pPppAdvancedButton;
    QDialogButtonBox *m_pButtonBox;
    QCheckBox *m_pDisableIPSecEncryption;

    void setupUi(QDialog *ConnectionSettingsDialog)
    {
        if (ConnectionSettingsDialog->objectName().isEmpty())
            ConnectionSettingsDialog->setObjectName(QString::fromUtf8("ConnectionSettingsDialog"));
        ConnectionSettingsDialog->resize(451, 478);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        ConnectionSettingsDialog->setWindowIcon(icon);
        ConnectionSettingsDialog->setSizeGripEnabled(true);
        m_pDialogGridLayout = new QGridLayout(ConnectionSettingsDialog);
        m_pDialogGridLayout->setObjectName(QString::fromUtf8("m_pDialogGridLayout"));
        m_pConnectionNameLayout = new QFormLayout();
        m_pConnectionNameLayout->setObjectName(QString::fromUtf8("m_pConnectionNameLayout"));
        m_pConnectionNameLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_pConnectionNameLabel = new QLabel(ConnectionSettingsDialog);
        m_pConnectionNameLabel->setObjectName(QString::fromUtf8("m_pConnectionNameLabel"));
        m_pConnectionNameLabel->setTextFormat(Qt::AutoText);

        m_pConnectionNameLayout->setWidget(0, QFormLayout::LabelRole, m_pConnectionNameLabel);

        m_pConnectionNameEdit = new QLineEdit(ConnectionSettingsDialog);
        m_pConnectionNameEdit->setObjectName(QString::fromUtf8("m_pConnectionNameEdit"));
        m_pConnectionNameEdit->setEnabled(false);
        m_pConnectionNameEdit->setAcceptDrops(false);
        m_pConnectionNameEdit->setMaxLength(30);
        m_pConnectionNameEdit->setReadOnly(true);

        m_pConnectionNameLayout->setWidget(0, QFormLayout::FieldRole, m_pConnectionNameEdit);


        m_pDialogGridLayout->addLayout(m_pConnectionNameLayout, 0, 0, 1, 2);

        m_pConnectAutomatically = new QCheckBox(ConnectionSettingsDialog);
        m_pConnectAutomatically->setObjectName(QString::fromUtf8("m_pConnectAutomatically"));

        m_pDialogGridLayout->addWidget(m_pConnectAutomatically, 1, 0, 1, 1);

        m_pTabWidget = new QTabWidget(ConnectionSettingsDialog);
        m_pTabWidget->setObjectName(QString::fromUtf8("m_pTabWidget"));
        m_pTabWidget->setFocusPolicy(Qt::StrongFocus);
        m_pTabWidget->setTabPosition(QTabWidget::North);
        m_pTabWidget->setTabShape(QTabWidget::Rounded);
        m_pTabIPsec = new QWidget();
        m_pTabIPsec->setObjectName(QString::fromUtf8("m_pTabIPsec"));
        m_pTabIPsec->setFocusPolicy(Qt::StrongFocus);
        m_pIPsecTabLayout = new QGridLayout(m_pTabIPsec);
        m_pIPsecTabLayout->setObjectName(QString::fromUtf8("m_pIPsecTabLayout"));
        m_pIPsecGatewayLayout = new QFormLayout();
        m_pIPsecGatewayLayout->setObjectName(QString::fromUtf8("m_pIPsecGatewayLayout"));
        m_pIPsecGatewayLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_pIPsecGatewayLayout->setVerticalSpacing(6);
        m_pIPsecGatewayLayout->setContentsMargins(-1, 0, -1, 10);
        m_pIPsecGatewayLabel = new QLabel(m_pTabIPsec);
        m_pIPsecGatewayLabel->setObjectName(QString::fromUtf8("m_pIPsecGatewayLabel"));
        m_pIPsecGatewayLabel->setTextFormat(Qt::AutoText);

        m_pIPsecGatewayLayout->setWidget(0, QFormLayout::LabelRole, m_pIPsecGatewayLabel);

        m_pIPsecGatewayEdit = new QLineEdit(m_pTabIPsec);
        m_pIPsecGatewayEdit->setObjectName(QString::fromUtf8("m_pIPsecGatewayEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pIPsecGatewayEdit->sizePolicy().hasHeightForWidth());
        m_pIPsecGatewayEdit->setSizePolicy(sizePolicy);
        m_pIPsecGatewayEdit->setFocusPolicy(Qt::StrongFocus);

        m_pIPsecGatewayLayout->setWidget(0, QFormLayout::FieldRole, m_pIPsecGatewayEdit);

        m_pIPsecIdentityLabel = new QLabel(m_pTabIPsec);
        m_pIPsecIdentityLabel->setObjectName(QString::fromUtf8("m_pIPsecIdentityLabel"));

        m_pIPsecGatewayLayout->setWidget(1, QFormLayout::LabelRole, m_pIPsecIdentityLabel);

        m_pIPsecIdentityEdit = new QLineEdit(m_pTabIPsec);
        m_pIPsecIdentityEdit->setObjectName(QString::fromUtf8("m_pIPsecIdentityEdit"));
        sizePolicy.setHeightForWidth(m_pIPsecIdentityEdit->sizePolicy().hasHeightForWidth());
        m_pIPsecIdentityEdit->setSizePolicy(sizePolicy);
        m_pIPsecIdentityEdit->setFocusPolicy(Qt::StrongFocus);

        m_pIPsecGatewayLayout->setWidget(1, QFormLayout::FieldRole, m_pIPsecIdentityEdit);


        m_pIPsecTabLayout->addLayout(m_pIPsecGatewayLayout, 0, 0, 1, 2);

        m_pIPsecUsePreSharedKeyRadioButton = new QRadioButton(m_pTabIPsec);
        m_pIPsecUsePreSharedKeyRadioButton->setObjectName(QString::fromUtf8("m_pIPsecUsePreSharedKeyRadioButton"));
        m_pIPsecUsePreSharedKeyRadioButton->setCheckable(true);
        m_pIPsecUsePreSharedKeyRadioButton->setChecked(true);

        m_pIPsecTabLayout->addWidget(m_pIPsecUsePreSharedKeyRadioButton, 1, 0, 1, 1);

        m_pIPsecPreSharedKeyEdit = new QLineEdit(m_pTabIPsec);
        m_pIPsecPreSharedKeyEdit->setObjectName(QString::fromUtf8("m_pIPsecPreSharedKeyEdit"));
        m_pIPsecPreSharedKeyEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        m_pIPsecTabLayout->addWidget(m_pIPsecPreSharedKeyEdit, 2, 0, 1, 2);

        m_pIPsecUseCertificateRadioButton = new QRadioButton(m_pTabIPsec);
        m_pIPsecUseCertificateRadioButton->setObjectName(QString::fromUtf8("m_pIPsecUseCertificateRadioButton"));

        m_pIPsecTabLayout->addWidget(m_pIPsecUseCertificateRadioButton, 3, 0, 1, 1);

        m_pIPsecCertificateListView = new QListView(m_pTabIPsec);
        m_pIPsecCertificateListView->setObjectName(QString::fromUtf8("m_pIPsecCertificateListView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pIPsecCertificateListView->sizePolicy().hasHeightForWidth());
        m_pIPsecCertificateListView->setSizePolicy(sizePolicy1);
        m_pIPsecCertificateListView->setMinimumSize(QSize(0, 23));

        m_pIPsecTabLayout->addWidget(m_pIPsecCertificateListView, 4, 0, 1, 1);

        m_pIPsecPrivateKeyFrame = new QFrame(m_pTabIPsec);
        m_pIPsecPrivateKeyFrame->setObjectName(QString::fromUtf8("m_pIPsecPrivateKeyFrame"));
        m_pIPsecPrivateKeyFrame->setEnabled(true);
        m_pIPsecPrivateKeyFrame->setFrameShape(QFrame::Box);
        m_pIPsecPrivateKeyFrame->setFrameShadow(QFrame::Sunken);
        m_pIPsecPrivateKeyLayout = new QGridLayout(m_pIPsecPrivateKeyFrame);
        m_pIPsecPrivateKeyLayout->setObjectName(QString::fromUtf8("m_pIPsecPrivateKeyLayout"));
        m_pIPsecPrivateKeyLabel = new QLabel(m_pIPsecPrivateKeyFrame);
        m_pIPsecPrivateKeyLabel->setObjectName(QString::fromUtf8("m_pIPsecPrivateKeyLabel"));

        m_pIPsecPrivateKeyLayout->addWidget(m_pIPsecPrivateKeyLabel, 0, 0, 1, 1);

        m_pIPsecPrivateKeyFileEdit = new QLineEdit(m_pIPsecPrivateKeyFrame);
        m_pIPsecPrivateKeyFileEdit->setObjectName(QString::fromUtf8("m_pIPsecPrivateKeyFileEdit"));
        m_pIPsecPrivateKeyFileEdit->setReadOnly(true);

        m_pIPsecPrivateKeyLayout->addWidget(m_pIPsecPrivateKeyFileEdit, 0, 1, 1, 1);

        m_pIPsecPassphraseLabel = new QLabel(m_pIPsecPrivateKeyFrame);
        m_pIPsecPassphraseLabel->setObjectName(QString::fromUtf8("m_pIPsecPassphraseLabel"));

        m_pIPsecPrivateKeyLayout->addWidget(m_pIPsecPassphraseLabel, 2, 0, 1, 1);

        m_pIPsecPassphraseEdit = new QLineEdit(m_pIPsecPrivateKeyFrame);
        m_pIPsecPassphraseEdit->setObjectName(QString::fromUtf8("m_pIPsecPassphraseEdit"));
        m_pIPsecPassphraseEdit->setEchoMode(QLineEdit::Password);

        m_pIPsecPrivateKeyLayout->addWidget(m_pIPsecPassphraseEdit, 2, 1, 1, 1);

        m_pIPsecBrowsePrivateKeyButton = new QPushButton(m_pIPsecPrivateKeyFrame);
        m_pIPsecBrowsePrivateKeyButton->setObjectName(QString::fromUtf8("m_pIPsecBrowsePrivateKeyButton"));
        m_pIPsecBrowsePrivateKeyButton->setMinimumSize(QSize(36, 27));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/search"), QSize(), QIcon::Normal, QIcon::Off);
        m_pIPsecBrowsePrivateKeyButton->setIcon(icon1);

        m_pIPsecPrivateKeyLayout->addWidget(m_pIPsecBrowsePrivateKeyButton, 0, 2, 1, 1);


        m_pIPsecTabLayout->addWidget(m_pIPsecPrivateKeyFrame, 6, 0, 1, 2);

        m_pImportPushButton = new QPushButton(m_pTabIPsec);
        m_pImportPushButton->setObjectName(QString::fromUtf8("m_pImportPushButton"));

        m_pIPsecTabLayout->addWidget(m_pImportPushButton, 4, 1, 1, 1);

        m_pTabWidget->addTab(m_pTabIPsec, QString());
        m_pTabL2TP = new QWidget();
        m_pTabL2TP->setObjectName(QString::fromUtf8("m_pTabL2TP"));
        m_pTabL2TP->setFocusPolicy(Qt::StrongFocus);
        m_pL2tpTabLayout = new QGridLayout(m_pTabL2TP);
        m_pL2tpTabLayout->setObjectName(QString::fromUtf8("m_pL2tpTabLayout"));
        m_pL2tpRedialCheckBox = new QCheckBox(m_pTabL2TP);
        m_pL2tpRedialCheckBox->setObjectName(QString::fromUtf8("m_pL2tpRedialCheckBox"));

        m_pL2tpTabLayout->addWidget(m_pL2tpRedialCheckBox, 0, 0, 1, 1);

        m_pL2tpLengthBitCheckBox = new QCheckBox(m_pTabL2TP);
        m_pL2tpLengthBitCheckBox->setObjectName(QString::fromUtf8("m_pL2tpLengthBitCheckBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pL2tpLengthBitCheckBox->sizePolicy().hasHeightForWidth());
        m_pL2tpLengthBitCheckBox->setSizePolicy(sizePolicy2);
        m_pL2tpLengthBitCheckBox->setChecked(true);

        m_pL2tpTabLayout->addWidget(m_pL2tpLengthBitCheckBox, 2, 0, 1, 1);

        m_pL2tpRedialLayout = new QFormLayout();
        m_pL2tpRedialLayout->setObjectName(QString::fromUtf8("m_pL2tpRedialLayout"));
        m_pL2tpRedialLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        m_pL2tpRedialLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_pL2tpRedialTimeoutLabel = new QLabel(m_pTabL2TP);
        m_pL2tpRedialTimeoutLabel->setObjectName(QString::fromUtf8("m_pL2tpRedialTimeoutLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_pL2tpRedialTimeoutLabel->sizePolicy().hasHeightForWidth());
        m_pL2tpRedialTimeoutLabel->setSizePolicy(sizePolicy3);

        m_pL2tpRedialLayout->setWidget(0, QFormLayout::LabelRole, m_pL2tpRedialTimeoutLabel);

        m_pL2tpRedialTimeoutSpinBox = new QSpinBox(m_pTabL2TP);
        m_pL2tpRedialTimeoutSpinBox->setObjectName(QString::fromUtf8("m_pL2tpRedialTimeoutSpinBox"));
        m_pL2tpRedialTimeoutSpinBox->setEnabled(false);
        sizePolicy3.setHeightForWidth(m_pL2tpRedialTimeoutSpinBox->sizePolicy().hasHeightForWidth());
        m_pL2tpRedialTimeoutSpinBox->setSizePolicy(sizePolicy3);
        m_pL2tpRedialTimeoutSpinBox->setMaximum(300);

        m_pL2tpRedialLayout->setWidget(0, QFormLayout::FieldRole, m_pL2tpRedialTimeoutSpinBox);

        m_pL2tpRedialAttemptsLabel = new QLabel(m_pTabL2TP);
        m_pL2tpRedialAttemptsLabel->setObjectName(QString::fromUtf8("m_pL2tpRedialAttemptsLabel"));
        sizePolicy3.setHeightForWidth(m_pL2tpRedialAttemptsLabel->sizePolicy().hasHeightForWidth());
        m_pL2tpRedialAttemptsLabel->setSizePolicy(sizePolicy3);

        m_pL2tpRedialLayout->setWidget(1, QFormLayout::LabelRole, m_pL2tpRedialAttemptsLabel);

        m_pL2tpRedialAttemptsSpinBox = new QSpinBox(m_pTabL2TP);
        m_pL2tpRedialAttemptsSpinBox->setObjectName(QString::fromUtf8("m_pL2tpRedialAttemptsSpinBox"));
        m_pL2tpRedialAttemptsSpinBox->setEnabled(false);
        sizePolicy3.setHeightForWidth(m_pL2tpRedialAttemptsSpinBox->sizePolicy().hasHeightForWidth());
        m_pL2tpRedialAttemptsSpinBox->setSizePolicy(sizePolicy3);
        m_pL2tpRedialAttemptsSpinBox->setFocusPolicy(Qt::WheelFocus);

        m_pL2tpRedialLayout->setWidget(1, QFormLayout::FieldRole, m_pL2tpRedialAttemptsSpinBox);


        m_pL2tpTabLayout->addLayout(m_pL2tpRedialLayout, 1, 0, 1, 1);

        m_pTabWidget->addTab(m_pTabL2TP, QString());
        m_pTabPpp = new QWidget();
        m_pTabPpp->setObjectName(QString::fromUtf8("m_pTabPpp"));
        m_pTabPpp->setFocusPolicy(Qt::StrongFocus);
        m_pPppTabLayout = new QGridLayout(m_pTabPpp);
        m_pPppTabLayout->setObjectName(QString::fromUtf8("m_pPppTabLayout"));
        m_pPppUseEAPRadioButton = new QRadioButton(m_pTabPpp);
        m_pPppUseEAPRadioButton->setObjectName(QString::fromUtf8("m_pPppUseEAPRadioButton"));
        m_pPppUseEAPRadioButton->setChecked(true);

        m_pPppTabLayout->addWidget(m_pPppUseEAPRadioButton, 0, 0, 1, 3);

        m_pPppPropertiesButton = new QPushButton(m_pTabPpp);
        m_pPppPropertiesButton->setObjectName(QString::fromUtf8("m_pPppPropertiesButton"));

        m_pPppTabLayout->addWidget(m_pPppPropertiesButton, 1, 0, 1, 1);

        m_pPppAllowProtocolsRadioButton = new QRadioButton(m_pTabPpp);
        m_pPppAllowProtocolsRadioButton->setObjectName(QString::fromUtf8("m_pPppAllowProtocolsRadioButton"));

        m_pPppTabLayout->addWidget(m_pPppAllowProtocolsRadioButton, 2, 0, 1, 2);

        m_pPppAllowProtocolsListWidget = new QListWidget(m_pTabPpp);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(m_pPppAllowProtocolsListWidget);
        __qlistwidgetitem->setCheckState(Qt::Unchecked);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(m_pPppAllowProtocolsListWidget);
        __qlistwidgetitem1->setCheckState(Qt::Unchecked);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(m_pPppAllowProtocolsListWidget);
        __qlistwidgetitem2->setCheckState(Qt::Unchecked);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(m_pPppAllowProtocolsListWidget);
        __qlistwidgetitem3->setCheckState(Qt::Unchecked);
        m_pPppAllowProtocolsListWidget->setObjectName(QString::fromUtf8("m_pPppAllowProtocolsListWidget"));

        m_pPppTabLayout->addWidget(m_pPppAllowProtocolsListWidget, 3, 0, 1, 3);

        m_pPppCredentialsFrame = new QFrame(m_pTabPpp);
        m_pPppCredentialsFrame->setObjectName(QString::fromUtf8("m_pPppCredentialsFrame"));
        m_pPppCredentialsFrame->setFrameShape(QFrame::Box);
        m_pPppCredentialsFrame->setFrameShadow(QFrame::Sunken);
        m_pIPsecCredentialsLayout = new QGridLayout(m_pPppCredentialsFrame);
        m_pIPsecCredentialsLayout->setObjectName(QString::fromUtf8("m_pIPsecCredentialsLayout"));
        m_pPppUserNameLabel = new QLabel(m_pPppCredentialsFrame);
        m_pPppUserNameLabel->setObjectName(QString::fromUtf8("m_pPppUserNameLabel"));

        m_pIPsecCredentialsLayout->addWidget(m_pPppUserNameLabel, 0, 0, 1, 1);

        m_pPppUserNameEdit = new QLineEdit(m_pPppCredentialsFrame);
        m_pPppUserNameEdit->setObjectName(QString::fromUtf8("m_pPppUserNameEdit"));

        m_pIPsecCredentialsLayout->addWidget(m_pPppUserNameEdit, 0, 1, 1, 1);

        m_pPppPwdLabel = new QLabel(m_pPppCredentialsFrame);
        m_pPppPwdLabel->setObjectName(QString::fromUtf8("m_pPppPwdLabel"));

        m_pIPsecCredentialsLayout->addWidget(m_pPppPwdLabel, 1, 0, 1, 1);

        m_pPppPwdEdit = new QLineEdit(m_pPppCredentialsFrame);
        m_pPppPwdEdit->setObjectName(QString::fromUtf8("m_pPppPwdEdit"));
        m_pPppPwdEdit->setEchoMode(QLineEdit::Password);

        m_pIPsecCredentialsLayout->addWidget(m_pPppPwdEdit, 1, 1, 1, 1);


        m_pPppTabLayout->addWidget(m_pPppCredentialsFrame, 4, 0, 1, 3);

        m_pPppPeerAuthenticationButton = new QPushButton(m_pTabPpp);
        m_pPppPeerAuthenticationButton->setObjectName(QString::fromUtf8("m_pPppPeerAuthenticationButton"));

        m_pPppTabLayout->addWidget(m_pPppPeerAuthenticationButton, 5, 0, 1, 1);

        m_pPppIpSettingsButton = new QPushButton(m_pTabPpp);
        m_pPppIpSettingsButton->setObjectName(QString::fromUtf8("m_pPppIpSettingsButton"));

        m_pPppTabLayout->addWidget(m_pPppIpSettingsButton, 5, 1, 1, 1);

        m_pPppAdvancedButton = new QPushButton(m_pTabPpp);
        m_pPppAdvancedButton->setObjectName(QString::fromUtf8("m_pPppAdvancedButton"));

        m_pPppTabLayout->addWidget(m_pPppAdvancedButton, 5, 2, 1, 1);

        m_pTabWidget->addTab(m_pTabPpp, QString());

        m_pDialogGridLayout->addWidget(m_pTabWidget, 3, 0, 1, 2);

        m_pButtonBox = new QDialogButtonBox(ConnectionSettingsDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        m_pDialogGridLayout->addWidget(m_pButtonBox, 4, 0, 1, 1);

        m_pDisableIPSecEncryption = new QCheckBox(ConnectionSettingsDialog);
        m_pDisableIPSecEncryption->setObjectName(QString::fromUtf8("m_pDisableIPSecEncryption"));

        m_pDialogGridLayout->addWidget(m_pDisableIPSecEncryption, 2, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        m_pConnectionNameLabel->setBuddy(m_pConnectionNameEdit);
        m_pIPsecGatewayLabel->setBuddy(m_pIPsecGatewayEdit);
        m_pIPsecIdentityLabel->setBuddy(m_pIPsecIdentityEdit);
        m_pIPsecPrivateKeyLabel->setBuddy(m_pIPsecPrivateKeyFileEdit);
        m_pIPsecPassphraseLabel->setBuddy(m_pIPsecPassphraseEdit);
        m_pL2tpRedialTimeoutLabel->setBuddy(m_pL2tpRedialTimeoutSpinBox);
        m_pL2tpRedialAttemptsLabel->setBuddy(m_pL2tpRedialAttemptsSpinBox);
        m_pPppUserNameLabel->setBuddy(m_pPppUserNameEdit);
        m_pPppPwdLabel->setBuddy(m_pPppPwdEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(m_pConnectionNameEdit, m_pConnectAutomatically);
        QWidget::setTabOrder(m_pConnectAutomatically, m_pDisableIPSecEncryption);
        QWidget::setTabOrder(m_pDisableIPSecEncryption, m_pTabWidget);
        QWidget::setTabOrder(m_pTabWidget, m_pIPsecGatewayEdit);
        QWidget::setTabOrder(m_pIPsecGatewayEdit, m_pIPsecIdentityEdit);
        QWidget::setTabOrder(m_pIPsecIdentityEdit, m_pIPsecUsePreSharedKeyRadioButton);
        QWidget::setTabOrder(m_pIPsecUsePreSharedKeyRadioButton, m_pIPsecPreSharedKeyEdit);
        QWidget::setTabOrder(m_pIPsecPreSharedKeyEdit, m_pIPsecUseCertificateRadioButton);
        QWidget::setTabOrder(m_pIPsecUseCertificateRadioButton, m_pIPsecCertificateListView);
        QWidget::setTabOrder(m_pIPsecCertificateListView, m_pImportPushButton);
        QWidget::setTabOrder(m_pImportPushButton, m_pIPsecPrivateKeyFileEdit);
        QWidget::setTabOrder(m_pIPsecPrivateKeyFileEdit, m_pIPsecBrowsePrivateKeyButton);
        QWidget::setTabOrder(m_pIPsecBrowsePrivateKeyButton, m_pIPsecPassphraseEdit);
        QWidget::setTabOrder(m_pIPsecPassphraseEdit, m_pL2tpRedialCheckBox);
        QWidget::setTabOrder(m_pL2tpRedialCheckBox, m_pL2tpRedialTimeoutSpinBox);
        QWidget::setTabOrder(m_pL2tpRedialTimeoutSpinBox, m_pL2tpRedialAttemptsSpinBox);
        QWidget::setTabOrder(m_pL2tpRedialAttemptsSpinBox, m_pL2tpLengthBitCheckBox);
        QWidget::setTabOrder(m_pL2tpLengthBitCheckBox, m_pPppUseEAPRadioButton);
        QWidget::setTabOrder(m_pPppUseEAPRadioButton, m_pPppPropertiesButton);
        QWidget::setTabOrder(m_pPppPropertiesButton, m_pPppAllowProtocolsRadioButton);
        QWidget::setTabOrder(m_pPppAllowProtocolsRadioButton, m_pPppAllowProtocolsListWidget);
        QWidget::setTabOrder(m_pPppAllowProtocolsListWidget, m_pPppUserNameEdit);
        QWidget::setTabOrder(m_pPppUserNameEdit, m_pPppPwdEdit);
        QWidget::setTabOrder(m_pPppPwdEdit, m_pPppPeerAuthenticationButton);
        QWidget::setTabOrder(m_pPppPeerAuthenticationButton, m_pPppIpSettingsButton);
        QWidget::setTabOrder(m_pPppIpSettingsButton, m_pPppAdvancedButton);
        QWidget::setTabOrder(m_pPppAdvancedButton, m_pButtonBox);

        retranslateUi(ConnectionSettingsDialog);
        QObject::connect(m_pL2tpRedialCheckBox, SIGNAL(clicked(bool)), m_pL2tpRedialAttemptsSpinBox, SLOT(setEnabled(bool)));
        QObject::connect(m_pL2tpRedialCheckBox, SIGNAL(clicked(bool)), m_pL2tpRedialTimeoutSpinBox, SLOT(setEnabled(bool)));
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), ConnectionSettingsDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), ConnectionSettingsDialog, SLOT(reject()));

        m_pTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConnectionSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionSettingsDialog)
    {
        ConnectionSettingsDialog->setWindowTitle(QApplication::translate("ConnectionSettingsDialog", "Connection Settings", 0));
        m_pConnectionNameLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Connection &name:", 0));
        m_pConnectAutomatically->setText(QApplication::translate("ConnectionSettingsDialog", "Connect &automatically", 0));
#ifndef QT_NO_TOOLTIP
        m_pIPsecGatewayLabel->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        m_pIPsecGatewayLabel->setText(QApplication::translate("ConnectionSettingsDialog", "&Remote Server:", 0));
#ifndef QT_NO_TOOLTIP
        m_pIPsecGatewayEdit->setToolTip(QApplication::translate("ConnectionSettingsDialog", "IPv4 address or domain name of the remote access server that you want to connect to.\n"
"\n"
"Examples:\n"
"1.2.3.4\n"
"ipsec.server.edu", 0));
#endif // QT_NO_TOOLTIP
        m_pIPsecIdentityLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Server &Identity:", 0));
#ifndef QT_NO_TOOLTIP
        m_pIPsecIdentityEdit->setToolTip(QApplication::translate("ConnectionSettingsDialog", "Leave empty if you don't want to check peers's identity,\n"
"otherwise enter the peer's identity \n"
"\n"
"This is mostly a distinguished name like 'CN=cisco-fcs-ber'.", 0));
#endif // QT_NO_TOOLTIP
        m_pIPsecUsePreSharedKeyRadioButton->setText(QApplication::translate("ConnectionSettingsDialog", "Use &pre-shared key for authentication", 0));
        m_pIPsecUseCertificateRadioButton->setText(QApplication::translate("ConnectionSettingsDialog", "Use &Certificate for authentication", 0));
        m_pIPsecPrivateKeyLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Private &key:", 0));
#ifndef QT_NO_TOOLTIP
        m_pIPsecPrivateKeyFileEdit->setToolTip(QApplication::translate("ConnectionSettingsDialog", "Full path to a X.509 pem encoded private key file", 0));
#endif // QT_NO_TOOLTIP
        m_pIPsecPassphraseLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Passphrase:", 0));
        m_pIPsecBrowsePrivateKeyButton->setText(QString());
        m_pImportPushButton->setText(QApplication::translate("ConnectionSettingsDialog", "Import ...", 0));
        m_pTabWidget->setTabText(m_pTabWidget->indexOf(m_pTabIPsec), QApplication::translate("ConnectionSettingsDialog", "IPsec", 0));
#ifndef QT_NO_TOOLTIP
        m_pL2tpRedialCheckBox->setToolTip(QApplication::translate("ConnectionSettingsDialog", "If checked, l2tpd will attempt to redial if the call get disconected.", 0));
#endif // QT_NO_TOOLTIP
        m_pL2tpRedialCheckBox->setText(QApplication::translate("ConnectionSettingsDialog", "Redial", 0));
#ifndef QT_NO_TOOLTIP
        m_pL2tpLengthBitCheckBox->setToolTip(QApplication::translate("ConnectionSettingsDialog", "If Checked, the length bit present in the l2tp packet payload will be used.", 0));
#endif // QT_NO_TOOLTIP
        m_pL2tpLengthBitCheckBox->setText(QApplication::translate("ConnectionSettingsDialog", "Length bit", 0));
        m_pL2tpRedialTimeoutLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Timeout:", 0));
#ifndef QT_NO_TOOLTIP
        m_pL2tpRedialTimeoutSpinBox->setToolTip(QApplication::translate("ConnectionSettingsDialog", "Wait N seconds before redial. The redial option must be set to yes to use this option.", 0));
#endif // QT_NO_TOOLTIP
        m_pL2tpRedialAttemptsLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Attempts:", 0));
#ifndef QT_NO_TOOLTIP
        m_pL2tpRedialAttemptsSpinBox->setToolTip(QApplication::translate("ConnectionSettingsDialog", "Will give up redial tries after N attempts.", 0));
#endif // QT_NO_TOOLTIP
        m_pTabWidget->setTabText(m_pTabWidget->indexOf(m_pTabL2TP), QApplication::translate("ConnectionSettingsDialog", "L2TP", 0));
#ifndef QT_NO_TOOLTIP
        m_pPppUseEAPRadioButton->setToolTip(QApplication::translate("ConnectionSettingsDialog", "With this option set, pppd will agree to authenticate itself to the peer exclusively using EAP.", 0));
#endif // QT_NO_TOOLTIP
        m_pPppUseEAPRadioButton->setText(QApplication::translate("ConnectionSettingsDialog", "Use Extensible Authentication Protocol (EAP)", 0));
        m_pPppPropertiesButton->setText(QApplication::translate("ConnectionSettingsDialog", "Properties ...", 0));
        m_pPppAllowProtocolsRadioButton->setText(QApplication::translate("ConnectionSettingsDialog", "Allow these protocols", 0));

        const bool __sortingEnabled = m_pPppAllowProtocolsListWidget->isSortingEnabled();
        m_pPppAllowProtocolsListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = m_pPppAllowProtocolsListWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("ConnectionSettingsDialog", "Unencrypted password (PAP)", 0));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem->setToolTip(QApplication::translate("ConnectionSettingsDialog", "With this option set, pppd will agree to authenticate itself to the peer using PAP.", 0));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem1 = m_pPppAllowProtocolsListWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("ConnectionSettingsDialog", "Challenge Authentication Protocol (CHAP)", 0));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem1->setToolTip(QApplication::translate("ConnectionSettingsDialog", "With this option set, pppd will agree to authenticate itself to the peer using CHAP.", 0));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem2 = m_pPppAllowProtocolsListWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("ConnectionSettingsDialog", "Microsoft CHAP (MS-Chap)", 0));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem2->setToolTip(QApplication::translate("ConnectionSettingsDialog", "With this option set, pppd will agree to authenticate itself to the peer using MS-CHAP.", 0));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem3 = m_pPppAllowProtocolsListWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("ConnectionSettingsDialog", "Microsoft CHAP Version 2 (MS-CHAPv2)", 0));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem3->setToolTip(QApplication::translate("ConnectionSettingsDialog", "With this option set, pppd will agree to authenticate itself to the peer using MS-CHAPv2.", 0));
#endif // QT_NO_TOOLTIP
        m_pPppAllowProtocolsListWidget->setSortingEnabled(__sortingEnabled);

        m_pPppUserNameLabel->setText(QApplication::translate("ConnectionSettingsDialog", "User name:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPppUserNameEdit->setToolTip(QApplication::translate("ConnectionSettingsDialog", "Set the name used for authenticating the local system to the remote access server.", 0));
#endif // QT_NO_TOOLTIP
        m_pPppPwdLabel->setText(QApplication::translate("ConnectionSettingsDialog", "Password:", 0));
#ifndef QT_NO_TOOLTIP
        m_pPppPwdEdit->setToolTip(QApplication::translate("ConnectionSettingsDialog", "Enter your password.\n"
"\n"
"If left empty you'll be ask each time you try to establish a connection.", 0));
#endif // QT_NO_TOOLTIP
        m_pPppPeerAuthenticationButton->setText(QApplication::translate("ConnectionSettingsDialog", "Peer authentication ...", 0));
        m_pPppIpSettingsButton->setText(QApplication::translate("ConnectionSettingsDialog", "IP settings ...", 0));
        m_pPppAdvancedButton->setText(QApplication::translate("ConnectionSettingsDialog", "Advanced ...", 0));
        m_pTabWidget->setTabText(m_pTabWidget->indexOf(m_pTabPpp), QApplication::translate("ConnectionSettingsDialog", "PPP", 0));
        m_pDisableIPSecEncryption->setText(QApplication::translate("ConnectionSettingsDialog", "&Disable IPSEC Encryption", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectionSettingsDialog: public Ui_ConnectionSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONSETTINGSDIALOG_H
