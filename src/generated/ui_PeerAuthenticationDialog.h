/********************************************************************************
** Form generated from reading UI file 'PeerAuthenticationDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEERAUTHENTICATIONDIALOG_H
#define UI_PEERAUTHENTICATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PeerAuthenticationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *m_pRemoteNameFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pRemoteNameLabel;
    QLineEdit *m_pRemoteNameEdit;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *PeerAuthenticationDialog)
    {
        if (PeerAuthenticationDialog->objectName().isEmpty())
            PeerAuthenticationDialog->setObjectName(QString::fromUtf8("PeerAuthenticationDialog"));
        PeerAuthenticationDialog->resize(417, 103);
        PeerAuthenticationDialog->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(PeerAuthenticationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pRemoteNameFrame = new QFrame(PeerAuthenticationDialog);
        m_pRemoteNameFrame->setObjectName(QString::fromUtf8("m_pRemoteNameFrame"));
        m_pRemoteNameFrame->setFrameShape(QFrame::StyledPanel);
        m_pRemoteNameFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(m_pRemoteNameFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pRemoteNameLabel = new QLabel(m_pRemoteNameFrame);
        m_pRemoteNameLabel->setObjectName(QString::fromUtf8("m_pRemoteNameLabel"));

        horizontalLayout->addWidget(m_pRemoteNameLabel);

        m_pRemoteNameEdit = new QLineEdit(m_pRemoteNameFrame);
        m_pRemoteNameEdit->setObjectName(QString::fromUtf8("m_pRemoteNameEdit"));

        horizontalLayout->addWidget(m_pRemoteNameEdit);


        verticalLayout->addWidget(m_pRemoteNameFrame);

        m_pButtonBox = new QDialogButtonBox(PeerAuthenticationDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(m_pButtonBox);

#ifndef QT_NO_SHORTCUT
        m_pRemoteNameLabel->setBuddy(m_pRemoteNameEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(m_pRemoteNameEdit, m_pButtonBox);

        retranslateUi(PeerAuthenticationDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), PeerAuthenticationDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), PeerAuthenticationDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PeerAuthenticationDialog);
    } // setupUi

    void retranslateUi(QDialog *PeerAuthenticationDialog)
    {
        PeerAuthenticationDialog->setWindowTitle(QApplication::translate("PeerAuthenticationDialog", "PeerAuthenticationDialog", 0));
        m_pRemoteNameLabel->setText(QApplication::translate("PeerAuthenticationDialog", "Remote name:", 0));
#ifndef QT_NO_TOOLTIP
        m_pRemoteNameEdit->setToolTip(QApplication::translate("PeerAuthenticationDialog", "Set the assumed name of the remote system for authentication purposes.\n"
"\n"
"If not empty, the name reported by the peer is checked against this name and connection will be refused if the reported name is different.", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class PeerAuthenticationDialog: public Ui_PeerAuthenticationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEERAUTHENTICATIONDIALOG_H
