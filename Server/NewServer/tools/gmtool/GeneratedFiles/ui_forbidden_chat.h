/********************************************************************************
** Form generated from reading UI file 'forbidden_chat.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORBIDDEN_CHAT_H
#define UI_FORBIDDEN_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_forbidChatDialog
{
public:
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *exeButton;
    QPushButton *exitButton;

    void setupUi(QDialog *forbidChatDialog)
    {
        if (forbidChatDialog->objectName().isEmpty())
            forbidChatDialog->setObjectName(QStringLiteral("forbidChatDialog"));
        forbidChatDialog->resize(350, 200);
        forbidChatDialog->setMinimumSize(QSize(350, 200));
        forbidChatDialog->setMaximumSize(QSize(350, 200));
        radioButton = new QRadioButton(forbidChatDialog);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 40, 82, 17));
        radioButton_2 = new QRadioButton(forbidChatDialog);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 80, 82, 17));
        label_2 = new QLabel(forbidChatDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 40, 61, 16));
        comboBox = new QComboBox(forbidChatDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(170, 40, 141, 22));
        exeButton = new QPushButton(forbidChatDialog);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setGeometry(QRect(140, 110, 75, 23));
        exitButton = new QPushButton(forbidChatDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(230, 110, 75, 23));

        retranslateUi(forbidChatDialog);

        QMetaObject::connectSlotsByName(forbidChatDialog);
    } // setupUi

    void retranslateUi(QDialog *forbidChatDialog)
    {
        forbidChatDialog->setWindowTitle(QApplication::translate("forbidChatDialog", "\347\246\201\350\250\200", 0));
        radioButton->setText(QApplication::translate("forbidChatDialog", "\347\246\201\350\250\200", 0));
        radioButton_2->setText(QApplication::translate("forbidChatDialog", "\350\247\243\351\231\244\347\246\201\350\250\200", 0));
        label_2->setText(QApplication::translate("forbidChatDialog", "\347\246\201\350\250\200\346\227\266\351\227\264", 0));
        exeButton->setText(QApplication::translate("forbidChatDialog", "\346\211\247\350\241\214", 0));
        exitButton->setText(QApplication::translate("forbidChatDialog", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class forbidChatDialog: public Ui_forbidChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORBIDDEN_CHAT_H
