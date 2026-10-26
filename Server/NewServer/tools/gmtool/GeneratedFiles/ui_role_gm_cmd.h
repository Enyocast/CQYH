/********************************************************************************
** Form generated from reading UI file 'role_gm_cmd.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROLE_GM_CMD_H
#define UI_ROLE_GM_CMD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_roleGMDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *okButton;
    QPushButton *exitButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QTextEdit *textEdit_2;

    void setupUi(QDialog *roleGMDialog)
    {
        if (roleGMDialog->objectName().isEmpty())
            roleGMDialog->setObjectName(QStringLiteral("roleGMDialog"));
        roleGMDialog->resize(545, 451);
        gridLayout = new QGridLayout(roleGMDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        okButton = new QPushButton(roleGMDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 2, 0, 1, 1);

        exitButton = new QPushButton(roleGMDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        gridLayout->addWidget(exitButton, 2, 1, 1, 1);

        groupBox_2 = new QGroupBox(roleGMDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(50, 50));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_2->addWidget(textEdit, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 2);

        groupBox = new QGroupBox(roleGMDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 50));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textEdit_2 = new QTextEdit(groupBox);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        gridLayout_3->addWidget(textEdit_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 2);


        retranslateUi(roleGMDialog);

        QMetaObject::connectSlotsByName(roleGMDialog);
    } // setupUi

    void retranslateUi(QDialog *roleGMDialog)
    {
        roleGMDialog->setWindowTitle(QApplication::translate("roleGMDialog", "GM\345\221\275\344\273\244", 0));
        okButton->setText(QApplication::translate("roleGMDialog", "OK", 0));
        exitButton->setText(QApplication::translate("roleGMDialog", "Exit", 0));
        groupBox_2->setTitle(QApplication::translate("roleGMDialog", "\346\214\207\344\273\244", 0));
        groupBox->setTitle(QApplication::translate("roleGMDialog", "\345\216\237\345\233\240", 0));
    } // retranslateUi

};

namespace Ui {
    class roleGMDialog: public Ui_roleGMDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROLE_GM_CMD_H
