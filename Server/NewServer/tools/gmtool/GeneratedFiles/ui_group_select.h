/********************************************************************************
** Form generated from reading UI file 'group_select.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUP_SELECT_H
#define UI_GROUP_SELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_groupSelectDialog
{
public:
    QPushButton *exeButton;
    QPushButton *exitButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;

    void setupUi(QDialog *groupSelectDialog)
    {
        if (groupSelectDialog->objectName().isEmpty())
            groupSelectDialog->setObjectName(QStringLiteral("groupSelectDialog"));
        groupSelectDialog->resize(400, 300);
        exeButton = new QPushButton(groupSelectDialog);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setGeometry(QRect(230, 260, 75, 23));
        exitButton = new QPushButton(groupSelectDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(310, 260, 75, 23));
        groupBox = new QGroupBox(groupSelectDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 318, 60));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);


        retranslateUi(groupSelectDialog);

        QMetaObject::connectSlotsByName(groupSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *groupSelectDialog)
    {
        groupSelectDialog->setWindowTitle(QApplication::translate("groupSelectDialog", "\345\214\272\346\234\215\351\200\211\346\213\251", 0));
        exeButton->setText(QApplication::translate("groupSelectDialog", "\347\241\256\350\256\244", 0));
        exitButton->setText(QApplication::translate("groupSelectDialog", "\345\217\226\346\266\210", 0));
        groupBox->setTitle(QString());
        checkBox->setText(QApplication::translate("groupSelectDialog", "\345\205\250\345\214\272\345\205\250\346\234\215", 0));
    } // retranslateUi

};

namespace Ui {
    class groupSelectDialog: public Ui_groupSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUP_SELECT_H
