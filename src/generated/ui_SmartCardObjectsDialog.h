/********************************************************************************
** Form generated from reading UI file 'SmartCardObjectsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMARTCARDOBJECTSDIALOG_H
#define UI_SMARTCARDOBJECTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>

QT_BEGIN_NAMESPACE

class Ui_SmartCardObjectsDialog
{
public:
    QGridLayout *gridLayout;
    QListView *m_pSmartCardObjectsListView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SmartCardObjectsDialog)
    {
        if (SmartCardObjectsDialog->objectName().isEmpty())
            SmartCardObjectsDialog->setObjectName(QString::fromUtf8("SmartCardObjectsDialog"));
        SmartCardObjectsDialog->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        SmartCardObjectsDialog->setWindowIcon(icon);
        SmartCardObjectsDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(SmartCardObjectsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pSmartCardObjectsListView = new QListView(SmartCardObjectsDialog);
        m_pSmartCardObjectsListView->setObjectName(QString::fromUtf8("m_pSmartCardObjectsListView"));

        gridLayout->addWidget(m_pSmartCardObjectsListView, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SmartCardObjectsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(SmartCardObjectsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SmartCardObjectsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SmartCardObjectsDialog, SLOT(reject()));
        QObject::connect(m_pSmartCardObjectsListView, SIGNAL(doubleClicked(QModelIndex)), SmartCardObjectsDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(SmartCardObjectsDialog);
    } // setupUi

    void retranslateUi(QDialog *SmartCardObjectsDialog)
    {
        SmartCardObjectsDialog->setWindowTitle(QApplication::translate("SmartCardObjectsDialog", "SmartCardObjectsDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class SmartCardObjectsDialog: public Ui_SmartCardObjectsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMARTCARDOBJECTSDIALOG_H
