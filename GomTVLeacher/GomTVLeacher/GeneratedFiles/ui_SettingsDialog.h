/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UiOptionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *mediaPlayerEdit;
    QLineEdit *vodEdit;
    QLineEdit *livestreamerEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *vodBrowse;
    QPushButton *livestreamerBrowse;
    QPushButton *mediaPlayerBrowse;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *UiOptionDialog)
    {
        if (UiOptionDialog->objectName().isEmpty())
            UiOptionDialog->setObjectName(QStringLiteral("UiOptionDialog"));
        UiOptionDialog->resize(443, 146);
        verticalLayout = new QVBoxLayout(UiOptionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(UiOptionDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        mediaPlayerEdit = new QLineEdit(UiOptionDialog);
        mediaPlayerEdit->setObjectName(QStringLiteral("mediaPlayerEdit"));

        gridLayout->addWidget(mediaPlayerEdit, 2, 1, 1, 1);

        vodEdit = new QLineEdit(UiOptionDialog);
        vodEdit->setObjectName(QStringLiteral("vodEdit"));

        gridLayout->addWidget(vodEdit, 0, 1, 1, 1);

        livestreamerEdit = new QLineEdit(UiOptionDialog);
        livestreamerEdit->setObjectName(QStringLiteral("livestreamerEdit"));

        gridLayout->addWidget(livestreamerEdit, 1, 1, 1, 1);

        label_2 = new QLabel(UiOptionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(UiOptionDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        vodBrowse = new QPushButton(UiOptionDialog);
        vodBrowse->setObjectName(QStringLiteral("vodBrowse"));

        gridLayout->addWidget(vodBrowse, 0, 2, 1, 1);

        livestreamerBrowse = new QPushButton(UiOptionDialog);
        livestreamerBrowse->setObjectName(QStringLiteral("livestreamerBrowse"));

        gridLayout->addWidget(livestreamerBrowse, 1, 2, 1, 1);

        mediaPlayerBrowse = new QPushButton(UiOptionDialog);
        mediaPlayerBrowse->setObjectName(QStringLiteral("mediaPlayerBrowse"));

        gridLayout->addWidget(mediaPlayerBrowse, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setSizeConstraint(QLayout::SetMinimumSize);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(UiOptionDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(UiOptionDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(UiOptionDialog);
        QObject::connect(okButton, SIGNAL(clicked()), UiOptionDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), UiOptionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UiOptionDialog);
    } // setupUi

    void retranslateUi(QDialog *UiOptionDialog)
    {
        UiOptionDialog->setWindowTitle(QApplication::translate("UiOptionDialog", "Options", 0));
        label->setText(QApplication::translate("UiOptionDialog", "Livestreamer path :", 0));
        label_2->setText(QApplication::translate("UiOptionDialog", "Media player path :", 0));
        label_3->setText(QApplication::translate("UiOptionDialog", "Vod output path :", 0));
        vodBrowse->setText(QApplication::translate("UiOptionDialog", "Browse...", 0));
        livestreamerBrowse->setText(QApplication::translate("UiOptionDialog", "Browse...", 0));
        mediaPlayerBrowse->setText(QApplication::translate("UiOptionDialog", "Browse...", 0));
        okButton->setText(QApplication::translate("UiOptionDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("UiOptionDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class UiOptionDialog: public Ui_UiOptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
