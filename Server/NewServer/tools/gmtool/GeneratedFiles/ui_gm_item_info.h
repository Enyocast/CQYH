/********************************************************************************
** Form generated from reading UI file 'gm_item_info.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GM_ITEM_INFO_H
#define UI_GM_ITEM_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_GMItemInfoDialog
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QPushButton *exitButton;

    void setupUi(QDialog *GMItemInfoDialog)
    {
        if (GMItemInfoDialog->objectName().isEmpty())
            GMItemInfoDialog->setObjectName(QStringLiteral("GMItemInfoDialog"));
        GMItemInfoDialog->resize(371, 604);
        GMItemInfoDialog->setMinimumSize(QSize(350, 300));
        GMItemInfoDialog->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(GMItemInfoDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(GMItemInfoDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        exitButton = new QPushButton(GMItemInfoDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        gridLayout->addWidget(exitButton, 1, 0, 1, 1);


        retranslateUi(GMItemInfoDialog);

        QMetaObject::connectSlotsByName(GMItemInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *GMItemInfoDialog)
    {
        GMItemInfoDialog->setWindowTitle(QApplication::translate("GMItemInfoDialog", "\351\201\223\345\205\267\344\277\241\346\201\257", 0));
        exitButton->setText(QApplication::translate("GMItemInfoDialog", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class GMItemInfoDialog: public Ui_GMItemInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GM_ITEM_INFO_H
