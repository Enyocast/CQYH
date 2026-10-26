/********************************************************************************
** Form generated from reading UI file 'loader.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADER_H
#define UI_LOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *loginButton;
    QPushButton *exitButton;
    QLineEdit *userNameEdit;
    QLineEdit *userPwdEdit;
    QLabel *label_3;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QStringLiteral("loginDialog"));
        loginDialog->resize(300, 180);
        loginDialog->setMinimumSize(QSize(300, 180));
        loginDialog->setMaximumSize(QSize(300, 180));
        label = new QLabel(loginDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 46, 13));
        label_2 = new QLabel(loginDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 46, 13));
        loginButton = new QPushButton(loginDialog);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(50, 130, 75, 23));
        loginButton->setMouseTracking(true);
        loginButton->setAcceptDrops(true);
        exitButton = new QPushButton(loginDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(170, 130, 75, 23));
        userNameEdit = new QLineEdit(loginDialog);
        userNameEdit->setObjectName(QStringLiteral("userNameEdit"));
        userNameEdit->setGeometry(QRect(110, 40, 113, 20));
        userPwdEdit = new QLineEdit(loginDialog);
        userPwdEdit->setObjectName(QStringLiteral("userPwdEdit"));
        userPwdEdit->setGeometry(QRect(110, 80, 113, 20));
        userPwdEdit->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(loginDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 10, 201, 16));

        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QApplication::translate("loginDialog", "GM\345\267\245\345\205\267", 0));
        label->setText(QApplication::translate("loginDialog", "\350\264\246\345\217\267", 0));
        label_2->setText(QApplication::translate("loginDialog", "\345\257\206\347\240\201", 0));
        loginButton->setText(QApplication::translate("loginDialog", "\347\231\273\351\231\206", 0));
        exitButton->setText(QApplication::translate("loginDialog", "\351\200\200\345\207\272", 0));
        label_3->setText(QApplication::translate("loginDialog", "Login...", 0));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADER_H
