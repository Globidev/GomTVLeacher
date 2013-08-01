/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiMainWindow
{
public:
    QAction *actionOptions;
    QAction *actionLogs;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *searchField;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCommandLinkButton *loadMore;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QMenu *menuLogs;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UiMainWindow)
    {
        if (UiMainWindow->objectName().isEmpty())
            UiMainWindow->setObjectName(QStringLiteral("UiMainWindow"));
        UiMainWindow->resize(900, 600);
        UiMainWindow->setMinimumSize(QSize(900, 600));
        actionOptions = new QAction(UiMainWindow);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionLogs = new QAction(UiMainWindow);
        actionLogs->setObjectName(QStringLiteral("actionLogs"));
        centralwidget = new QWidget(UiMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        searchField = new QLineEdit(centralwidget);
        searchField->setObjectName(QStringLiteral("searchField"));

        verticalLayout->addWidget(searchField);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loadMore = new QCommandLinkButton(centralwidget);
        loadMore->setObjectName(QStringLiteral("loadMore"));

        horizontalLayout->addWidget(loadMore);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        UiMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UiMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 21));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuLogs = new QMenu(menubar);
        menuLogs->setObjectName(QStringLiteral("menuLogs"));
        UiMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UiMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        UiMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuLogs->menuAction());
        menuOptions->addAction(actionOptions);
        menuLogs->addAction(actionLogs);

        retranslateUi(UiMainWindow);

        QMetaObject::connectSlotsByName(UiMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UiMainWindow)
    {
        UiMainWindow->setWindowTitle(QApplication::translate("UiMainWindow", "GomTV leacher", 0));
        actionOptions->setText(QApplication::translate("UiMainWindow", "options", 0));
        actionLogs->setText(QApplication::translate("UiMainWindow", "logs", 0));
        loadMore->setText(QApplication::translate("UiMainWindow", "Load More", 0));
        menuOptions->setTitle(QApplication::translate("UiMainWindow", "Options", 0));
        menuLogs->setTitle(QApplication::translate("UiMainWindow", "Logs", 0));
    } // retranslateUi

};

namespace Ui {
    class UiMainWindow: public Ui_UiMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
