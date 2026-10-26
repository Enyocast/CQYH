/********************************************************************************
** Form generated from reading UI file 'kick_user.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KICK_USER_H
#define UI_KICK_USER_H

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

class Ui_kickUserDialog
{
public:
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QComboBox *comboBox;
    QLabel *label_2;
    QPushButton *exitButton;
    QPushButton *exeButton;
    QRadioButton *radioButton_3;

    void setupUi(QDialog *kickUserDialog)
    {
        if (kickUserDialog->objectName().isEmpty())
            kickUserDialog->setObjectName(QStringLiteral("kickUserDialog"));
        kickUserDialog->resize(350, 200);
        kickUserDialog->setMinimumSize(QSize(350, 200));
        kickUserDialog->setMaximumSize(QSize(350, 200));
        radioButton = new QRadioButton(kickUserDialog);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 30, 101, 17));
        radioButton_2 = new QRadioButton(kickUserDialog);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 60, 101, 17));
        comboBox = new QComboBox(kickUserDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(190, 60, 141, 22));
        label_2 = new QLabel(kickUserDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 60, 61, 16));
        exitButton = new QPushButton(kickUserDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(250, 120, 75, 23));
        exeButton = new QPushButton(kickUserDialog);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setGeometry(QRect(160, 120, 75, 23));
        radioButton_3 = new QRadioButton(kickUserDialog);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(20, 90, 82, 17));

        retranslateUi(kickUserDialog);

        QMetaObject::connectSlotsByName(kickUserDialog);
    } // setupUi

    void retranslateUi(QDialog *kickUserDialog)
    {
        kickUserDialog->setWindowTitle(QApplication::translate("kickUserDialog", "\350\270\242\344\272\272\345\260\201\345\217\267", 0));
        radioButton->setText(QApplication::translate("kickUserDialog", "\350\270\242\344\272\272(\345\274\272\345\210\266\344\270\213\347\272\277)", 0));
        radioButton_2->setText(QApplication::translate("kickUserDialog", "\345\260\201\345\217\267(\347\246\201\346\255\242\347\231\273\351\231\206)", 0));
        label_2->setText(QApplication::translate("kickUserDialog", "\345\260\201\347\246\201\346\227\266\351\227\264", 0));
        exitButton->setText(QApplication::translate("kickUserDialog", "\351\200\200\345\207\272", 0));
        exeButton->setText(QApplication::translate("kickUserDialog", "\346\211\247\350\241\214", 0));
        radioButton_3->setText(QApplication::translate("kickUserDialog", "\350\247\243\351\231\244\345\260\201\347\246\201", 0));
    } // retranslateUi

};

namespace Ui {
    class kickUserDialog: public Ui_kickUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KICK_USER_H
