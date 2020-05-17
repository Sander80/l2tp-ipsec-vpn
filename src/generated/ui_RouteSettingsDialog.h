/********************************************************************************
** Form generated from reading UI file 'RouteSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTESETTINGSDIALOG_H
#define UI_ROUTESETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_RouteSettingsDialog
{
public:
    QGridLayout *m_pDialogGridLayout;
    QPushButton *m_pAddButton;
    QPushButton *m_pDeleteButton;
    QTableView *m_pRoutesTableView;
    QDialogButtonBox *m_pButtonBox;
    QRadioButton *m_pUseExplicitRoutesRadioButton;
    QRadioButton *m_pUseDefaultGatewayRadioButton;
    QPushButton *m_pDeleteNoRouteButton;
    QPushButton *m_pAddNoRouteButton;
    QTableView *m_pNoRoutesTableView;

    void setupUi(QDialog *RouteSettingsDialog)
    {
        if (RouteSettingsDialog->objectName().isEmpty())
            RouteSettingsDialog->setObjectName(QString::fromUtf8("RouteSettingsDialog"));
        RouteSettingsDialog->resize(439, 287);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/configure"), QSize(), QIcon::Normal, QIcon::Off);
        RouteSettingsDialog->setWindowIcon(icon);
        RouteSettingsDialog->setSizeGripEnabled(true);
        m_pDialogGridLayout = new QGridLayout(RouteSettingsDialog);
        m_pDialogGridLayout->setSpacing(9);
        m_pDialogGridLayout->setObjectName(QString::fromUtf8("m_pDialogGridLayout"));
        m_pDialogGridLayout->setContentsMargins(9, 15, 9, 9);
        m_pAddButton = new QPushButton(RouteSettingsDialog);
        m_pAddButton->setObjectName(QString::fromUtf8("m_pAddButton"));
        m_pAddButton->setAutoDefault(false);

        m_pDialogGridLayout->addWidget(m_pAddButton, 8, 1, 1, 1);

        m_pDeleteButton = new QPushButton(RouteSettingsDialog);
        m_pDeleteButton->setObjectName(QString::fromUtf8("m_pDeleteButton"));
        m_pDeleteButton->setAutoDefault(false);

        m_pDialogGridLayout->addWidget(m_pDeleteButton, 9, 1, 1, 1);

        m_pRoutesTableView = new QTableView(RouteSettingsDialog);
        m_pRoutesTableView->setObjectName(QString::fromUtf8("m_pRoutesTableView"));
        m_pRoutesTableView->setFocusPolicy(Qt::WheelFocus);

        m_pDialogGridLayout->addWidget(m_pRoutesTableView, 8, 0, 3, 1);

        m_pButtonBox = new QDialogButtonBox(RouteSettingsDialog);
        m_pButtonBox->setObjectName(QString::fromUtf8("m_pButtonBox"));
        m_pButtonBox->setOrientation(Qt::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::Help|QDialogButtonBox::Ok);

        m_pDialogGridLayout->addWidget(m_pButtonBox, 11, 0, 1, 2);

        m_pUseExplicitRoutesRadioButton = new QRadioButton(RouteSettingsDialog);
        m_pUseExplicitRoutesRadioButton->setObjectName(QString::fromUtf8("m_pUseExplicitRoutesRadioButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pUseExplicitRoutesRadioButton->sizePolicy().hasHeightForWidth());
        m_pUseExplicitRoutesRadioButton->setSizePolicy(sizePolicy);

        m_pDialogGridLayout->addWidget(m_pUseExplicitRoutesRadioButton, 4, 0, 1, 2);

        m_pUseDefaultGatewayRadioButton = new QRadioButton(RouteSettingsDialog);
        m_pUseDefaultGatewayRadioButton->setObjectName(QString::fromUtf8("m_pUseDefaultGatewayRadioButton"));

        m_pDialogGridLayout->addWidget(m_pUseDefaultGatewayRadioButton, 0, 0, 1, 2);

        m_pDeleteNoRouteButton = new QPushButton(RouteSettingsDialog);
        m_pDeleteNoRouteButton->setObjectName(QString::fromUtf8("m_pDeleteNoRouteButton"));
        m_pDeleteNoRouteButton->setAutoDefault(false);

        m_pDialogGridLayout->addWidget(m_pDeleteNoRouteButton, 2, 1, 1, 1);

        m_pAddNoRouteButton = new QPushButton(RouteSettingsDialog);
        m_pAddNoRouteButton->setObjectName(QString::fromUtf8("m_pAddNoRouteButton"));
        m_pAddNoRouteButton->setAutoDefault(false);

        m_pDialogGridLayout->addWidget(m_pAddNoRouteButton, 1, 1, 1, 1);

        m_pNoRoutesTableView = new QTableView(RouteSettingsDialog);
        m_pNoRoutesTableView->setObjectName(QString::fromUtf8("m_pNoRoutesTableView"));

        m_pDialogGridLayout->addWidget(m_pNoRoutesTableView, 1, 0, 3, 1);

        QWidget::setTabOrder(m_pUseDefaultGatewayRadioButton, m_pUseExplicitRoutesRadioButton);
        QWidget::setTabOrder(m_pUseExplicitRoutesRadioButton, m_pRoutesTableView);
        QWidget::setTabOrder(m_pRoutesTableView, m_pAddButton);
        QWidget::setTabOrder(m_pAddButton, m_pDeleteButton);
        QWidget::setTabOrder(m_pDeleteButton, m_pButtonBox);

        retranslateUi(RouteSettingsDialog);
        QObject::connect(m_pButtonBox, SIGNAL(accepted()), RouteSettingsDialog, SLOT(accept()));
        QObject::connect(m_pButtonBox, SIGNAL(rejected()), RouteSettingsDialog, SLOT(accept()));
        QObject::connect(m_pUseDefaultGatewayRadioButton, SIGNAL(toggled(bool)), m_pAddButton, SLOT(setDisabled(bool)));
        QObject::connect(m_pUseDefaultGatewayRadioButton, SIGNAL(toggled(bool)), m_pDeleteButton, SLOT(setDisabled(bool)));
        QObject::connect(m_pUseDefaultGatewayRadioButton, SIGNAL(toggled(bool)), m_pRoutesTableView, SLOT(setDisabled(bool)));
        QObject::connect(m_pUseExplicitRoutesRadioButton, SIGNAL(toggled(bool)), m_pAddNoRouteButton, SLOT(setDisabled(bool)));
        QObject::connect(m_pUseExplicitRoutesRadioButton, SIGNAL(toggled(bool)), m_pDeleteNoRouteButton, SLOT(setDisabled(bool)));
        QObject::connect(m_pUseExplicitRoutesRadioButton, SIGNAL(toggled(bool)), m_pNoRoutesTableView, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(RouteSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *RouteSettingsDialog)
    {
        RouteSettingsDialog->setWindowTitle(QApplication::translate("RouteSettingsDialog", "RouteSettingsDialog", 0));
        m_pAddButton->setText(QApplication::translate("RouteSettingsDialog", "Add", 0));
        m_pDeleteButton->setText(QApplication::translate("RouteSettingsDialog", "Delete ...", 0));
#ifndef QT_NO_TOOLTIP
        m_pRoutesTableView->setToolTip(QApplication::translate("RouteSettingsDialog", "route packages with the destination addresses listed here through the PPP tunnel.", 0));
#endif // QT_NO_TOOLTIP
        m_pUseExplicitRoutesRadioButton->setText(QApplication::translate("RouteSettingsDialog", "Use following explicit routes to intranet locations (split tunneling)", 0));
#ifndef QT_NO_TOOLTIP
        m_pUseDefaultGatewayRadioButton->setToolTip(QApplication::translate("RouteSettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Based on the <span style=\" font-weight:600;\">Use default gateway on remote network</span> setting, one of the following occurs when the VPN connection is active: </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">When the <span style=\" font-weight:600;\">Use default gateway on remote network</span> check box is cleared, Internet locations are reachable and intranet locations a"
                        "re not reachable, except for those matching the network ID of the Internet address class of the assigned IP address. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">When the<span style=\" font-weight:600;\"> Use default gateway on remote network</span> check box is selected (the default setting), all intranet locations are reachable and Internet locations are not reachable, except for the address of the VPN server and locations available through other routes. </li></ul></body></html>", 0));
#endif // QT_NO_TOOLTIP
        m_pUseDefaultGatewayRadioButton->setText(QApplication::translate("RouteSettingsDialog", "Use default gateway on the remote network except for", 0));
        m_pDeleteNoRouteButton->setText(QApplication::translate("RouteSettingsDialog", "Delete ...", 0));
        m_pAddNoRouteButton->setText(QApplication::translate("RouteSettingsDialog", "Add", 0));
#ifndef QT_NO_TOOLTIP
        m_pNoRoutesTableView->setToolTip(QApplication::translate("RouteSettingsDialog", "route packages with the destination addresses listed here through the default interfacel.", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class RouteSettingsDialog: public Ui_RouteSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTESETTINGSDIALOG_H
