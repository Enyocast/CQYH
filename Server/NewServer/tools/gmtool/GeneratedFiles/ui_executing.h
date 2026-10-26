/********************************************************************************
** Form generated from reading UI file 'executing.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXECUTING_H
#define UI_EXECUTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ExecutingDialog
{
public:

    void setupUi(QDialog *ExecutingDialog)
    {
        if (ExecutingDialog->objectName().isEmpty())
            ExecutingDialog->setObjectName(QStringLiteral("ExecutingDialog"));
        ExecutingDialog->resize(425, 100);

        retranslateUi(ExecutingDialog);

        QMetaObject::connectSlotsByName(ExecutingDialog);
    } // setupUi

    void retranslateUi(QDialog *ExecutingDialog)
    {
        ExecutingDialog->setWindowTitle(QApplication::translate("ExecutingDialog", "Executing", 0));
    } // retranslateUi

};

namespace Ui {
    class ExecutingDialog: public Ui_ExecutingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXECUTING_H
