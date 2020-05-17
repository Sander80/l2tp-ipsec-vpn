/********************************************************************************
** Form generated from reading UI file 'ConnectionEditorDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONEDITORDIALOG_H
#define UI_CONNECTIONEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ConnectionEditorDialog
{
public:
    QGridLayout *m_pGridLayout;
    QPushButton *m_pAdd;
    QPushButton *m_pEdit;
    QPushButton *m_pDelete;
    QTableView *m_pConnections;
    QCommandLinkButton *m_pPreferencesCommandLinkButton;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *ConnectionEditorDialog)
    {
        if (ConnectionEditorDialog->objectName().isEmpty())
            ConnectionEditorDialog->setObjectName(QString::fromUtf8("ConnectionEditorDialog"));
        ConnectionEditorDialog->resize(397, 246);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connectEstablished"), QSize(), QIcon::Normal, QIcon::Off);
        ConnectionEditorDialog->setWindowIcon(icon);
        ConnectionEditorDialog->setSizeGripEnabled(true);
        m_pGridLayout = new QGridLayout(ConnectionEditorDialog);
        m_pGridLayout->setObjectName(QString::fromUtf8("m_pGridLayout"));
        m_pGridLayout->setHorizontalSpacing(9);
        m_pGridLayout->setVerticalSpacing(8);
        m_pAdd = new QPushButton(ConnectionEditorDialog);
        m_pAdd->setObjectName(QString::fromUtf8("m_pAdd"));
        m_pAdd->setAutoDefault(false);

        m_pGridLayout->addWidget(m_pAdd, 1, 1, 1, 1);

        m_pEdit = new QPushButton(ConnectionEditorDialog);
        m_pEdit->setObjectName(QString::fromUtf8("m_pEdit"));
        m_pEdit->setAutoDefault(false);
        m_pEdit->setDefault(true);

        m_pGridLayout->addWidget(m_pEdit, 2, 1, 1, 1);

        m_pDelete = new QPushButton(ConnectionEditorDialog);
        m_pDelete->setObjectName(QString::fromUtf8("m_pDelete"));
        m_pDelete->setAutoDefault(false);

        m_pGridLayout->addWidget(m_pDelete, 3, 1, 1, 1);

        m_pConnections = new QTableView(ConnectionEditorDialog);
        m_pConnections->setObjectName(QString::fromUtf8("m_pConnections"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pConnections->sizePolicy().hasHeightForWidth());
        m_pConnections->setSizePolicy(sizePolicy);
        m_pConnections->setFocusPolicy(Qt::WheelFocus);
        m_pConnections->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_pConnections->setShowGrid(false);
        m_pConnections->setWordWrap(false);
        m_pConnections->setCornerButtonEnabled(true);
        m_pConnections->verticalHeader()->setVisible(false);

        m_pGridLayout->addWidget(m_pConnections, 1, 0, 4, 1);

        m_pPreferencesCommandLinkButton = new QCommandLinkButton(ConnectionEditorDialog);
        m_pPreferencesCommandLinkButton->setObjectName(QString::fromUtf8("m_pPreferencesCommandLinkButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pPreferencesCommandLinkButton->sizePolicy().hasHeightForWidth());
        m_pPreferencesCommandLinkButton->setSizePolicy(sizePolicy1);
        m_pPreferencesCommandLinkButton->setMinimumSize(QSize(150, 36));
        m_pPreferencesCommandLinkButton->setMaximumSize(QSize(150, 36));
        m_pPreferencesCommandLinkButton->setAutoDefault(false);

        m_pGridLayout->addWidget(m_pPreferencesCommandLinkButton, 0, 0, 1, 1);

        m_pButtonBox = new QDialogButtonBox(ConnectionEditorDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);

        m_pGridLayout->addWidget(m_pButtonBox, 5, 0, 1, 2);


        retranslateUi(ConnectionEditorDialog);
        QObject::connect(m_pConnections, SIGNAL(doubleClicked(QModelIndex)), m_pEdit, SLOT(click()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), ConnectionEditorDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(ConnectionEditorDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionEditorDialog)
    {
        ConnectionEditorDialog->setWindowTitle(QApplication::translate("ConnectionEditorDialog", "VPN Connections", 0));
        m_pAdd->setText(QApplication::translate("ConnectionEditorDialog", "&Add ...", 0));
        m_pEdit->setText(QApplication::translate("ConnectionEditorDialog", "&Edit ...", 0));
        m_pDelete->setText(QApplication::translate("ConnectionEditorDialog", "&Delete ...", 0));
        m_pPreferencesCommandLinkButton->setText(QApplication::translate("ConnectionEditorDialog", "&Preferences ...", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectionEditorDialog: public Ui_ConnectionEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONEDITORDIALOG_H
