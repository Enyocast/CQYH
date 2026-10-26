/********************************************************************************
** Form generated from reading UI file 'exchange_limit.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXCHANGE_LIMIT_H
#define UI_EXCHANGE_LIMIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_exchangeLimitDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_3;
    QLabel *label_7;
    QSpinBox *spinBox;
    QLabel *label_4;
    QLabel *label_8;
    QSpinBox *spinBox_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *exchangeLimitDialog)
    {
        if (exchangeLimitDialog->objectName().isEmpty())
            exchangeLimitDialog->setObjectName(QStringLiteral("exchangeLimitDialog"));
        exchangeLimitDialog->resize(416, 304);
        gridLayout = new QGridLayout(exchangeLimitDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(exchangeLimitDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_5 = new QLabel(exchangeLimitDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(exchangeLimitDialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMaximum(999.99);
        doubleSpinBox->setSingleStep(1);

        gridLayout->addWidget(doubleSpinBox, 0, 2, 1, 2);

        label_2 = new QLabel(exchangeLimitDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_6 = new QLabel(exchangeLimitDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 1, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(exchangeLimitDialog);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMaximum(999.99);

        gridLayout->addWidget(doubleSpinBox_2, 1, 2, 1, 2);

        label_3 = new QLabel(exchangeLimitDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_7 = new QLabel(exchangeLimitDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        spinBox = new QSpinBox(exchangeLimitDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(9999);

        gridLayout->addWidget(spinBox, 2, 2, 1, 2);

        label_4 = new QLabel(exchangeLimitDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_8 = new QLabel(exchangeLimitDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 1, 1, 1);

        spinBox_2 = new QSpinBox(exchangeLimitDialog);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(9999);

        gridLayout->addWidget(spinBox_2, 3, 2, 1, 2);

        pushButton = new QPushButton(exchangeLimitDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 1, 1, 2);

        pushButton_2 = new QPushButton(exchangeLimitDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 3, 1, 1);


        retranslateUi(exchangeLimitDialog);

        QMetaObject::connectSlotsByName(exchangeLimitDialog);
    } // setupUi

    void retranslateUi(QDialog *exchangeLimitDialog)
    {
        exchangeLimitDialog->setWindowTitle(QApplication::translate("exchangeLimitDialog", "\346\267\273\345\212\240\351\201\223\345\205\267", 0));
        label->setText(QApplication::translate("exchangeLimitDialog", "\346\234\200\351\253\230\344\273\267\346\240\274", 0));
        label_5->setText(QApplication::translate("exchangeLimitDialog", "1", 0));
        label_2->setText(QApplication::translate("exchangeLimitDialog", "\346\234\200\344\275\216\344\273\267\346\240\274", 0));
        label_6->setText(QApplication::translate("exchangeLimitDialog", "2", 0));
        label_3->setText(QApplication::translate("exchangeLimitDialog", "\345\215\225\346\254\241\346\214\202\345\215\225\351\231\220\345\210\266", 0));
        label_7->setText(QApplication::translate("exchangeLimitDialog", "3", 0));
        label_4->setText(QApplication::translate("exchangeLimitDialog", "\346\257\217\346\254\241\346\214\202\345\215\225\351\231\220\345\210\266", 0));
        label_8->setText(QApplication::translate("exchangeLimitDialog", "4", 0));
        pushButton->setText(QApplication::translate("exchangeLimitDialog", "\344\277\256\346\224\271", 0));
        pushButton_2->setText(QApplication::translate("exchangeLimitDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class exchangeLimitDialog: public Ui_exchangeLimitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXCHANGE_LIMIT_H
