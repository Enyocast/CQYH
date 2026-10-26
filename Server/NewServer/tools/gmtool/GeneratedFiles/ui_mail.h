/********************************************************************************
** Form generated from reading UI file 'mail.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIL_H
#define UI_MAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_mailDialog
{
public:
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QTextEdit *textEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *exeButton;
    QPushButton *exitButton;

    void setupUi(QDialog *mailDialog)
    {
        if (mailDialog->objectName().isEmpty())
            mailDialog->setObjectName(QStringLiteral("mailDialog"));
        mailDialog->resize(380, 280);
        mailDialog->setMinimumSize(QSize(380, 280));
        mailDialog->setMaximumSize(QSize(380, 280));
        label_2 = new QLabel(mailDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 20, 46, 13));
        lineEdit = new QLineEdit(mailDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 20, 271, 20));
        label_3 = new QLabel(mailDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 50, 46, 13));
        textEdit = new QTextEdit(mailDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(80, 50, 271, 111));
        label_4 = new QLabel(mailDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 170, 46, 13));
        label_5 = new QLabel(mailDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 190, 46, 13));
        label_6 = new QLabel(mailDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(210, 190, 31, 16));
        lineEdit_2 = new QLineEdit(mailDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 190, 81, 20));
        lineEdit_3 = new QLineEdit(mailDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(250, 190, 61, 20));
        exeButton = new QPushButton(mailDialog);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setGeometry(QRect(190, 230, 75, 23));
        exitButton = new QPushButton(mailDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(280, 230, 75, 23));

        retranslateUi(mailDialog);

        QMetaObject::connectSlotsByName(mailDialog);
    } // setupUi

    void retranslateUi(QDialog *mailDialog)
    {
        mailDialog->setWindowTitle(QApplication::translate("mailDialog", "\345\217\221\351\200\201\351\202\256\344\273\266", 0));
        label_2->setText(QApplication::translate("mailDialog", "\346\240\207\351\242\230", 0));
        label_3->setText(QApplication::translate("mailDialog", "\345\206\205\345\256\271", 0));
        label_4->setText(QApplication::translate("mailDialog", "\351\231\204\344\273\266", 0));
        label_5->setText(QApplication::translate("mailDialog", "\351\201\223\345\205\267ID", 0));
        label_6->setText(QApplication::translate("mailDialog", "\346\225\260\351\207\217", 0));
        exeButton->setText(QApplication::translate("mailDialog", "\346\211\247\350\241\214", 0));
        exitButton->setText(QApplication::translate("mailDialog", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class mailDialog: public Ui_mailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIL_H
