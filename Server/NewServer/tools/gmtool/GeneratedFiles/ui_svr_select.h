/********************************************************************************
** Form generated from reading UI file 'svr_select.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVR_SELECT_H
#define UI_SVR_SELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SelectSvrDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *exeButton;
    QPushButton *exitButton;

    void setupUi(QDialog *SelectSvrDialog)
    {
        if (SelectSvrDialog->objectName().isEmpty())
            SelectSvrDialog->setObjectName(QStringLiteral("SelectSvrDialog"));
        SelectSvrDialog->resize(518, 474);
        verticalLayout = new QVBoxLayout(SelectSvrDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(SelectSvrDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(500, 400));

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SelectSvrDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(500, 50));
        groupBox_2->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(315, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exeButton = new QPushButton(groupBox_2);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setMinimumSize(QSize(75, 22));
        exeButton->setMaximumSize(QSize(75, 22));

        horizontalLayout->addWidget(exeButton);

        exitButton = new QPushButton(groupBox_2);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setMinimumSize(QSize(75, 22));
        exitButton->setMaximumSize(QSize(75, 22));

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(SelectSvrDialog);

        QMetaObject::connectSlotsByName(SelectSvrDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectSvrDialog)
    {
        SelectSvrDialog->setWindowTitle(QApplication::translate("SelectSvrDialog", "Dialog", 0));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        exeButton->setText(QApplication::translate("SelectSvrDialog", "\347\241\256\345\256\232", 0));
        exitButton->setText(QApplication::translate("SelectSvrDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectSvrDialog: public Ui_SelectSvrDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVR_SELECT_H
