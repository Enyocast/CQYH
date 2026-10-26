/********************************************************************************
** Form generated from reading UI file 'delete_item.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETE_ITEM_H
#define UI_DELETE_ITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_deleteItemDialog
{
public:
    QTreeWidget *treeWidget_2;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *exitButton;
    QPushButton *exeButton;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox_2;

    void setupUi(QDialog *deleteItemDialog)
    {
        if (deleteItemDialog->objectName().isEmpty())
            deleteItemDialog->setObjectName(QStringLiteral("deleteItemDialog"));
        deleteItemDialog->resize(350, 300);
        deleteItemDialog->setMinimumSize(QSize(350, 300));
        deleteItemDialog->setMaximumSize(QSize(350, 300));
        treeWidget_2 = new QTreeWidget(deleteItemDialog);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));
        treeWidget_2->setGeometry(QRect(20, 30, 300, 120));
        treeWidget_2->setMinimumSize(QSize(300, 120));
        treeWidget_2->setMaximumSize(QSize(300, 16777215));
        treeWidget_2->setAlternatingRowColors(true);
        treeWidget_2->setIndentation(2);
        treeWidget_2->setSortingEnabled(true);
        treeWidget_2->header()->setDefaultSectionSize(50);
        treeWidget_2->header()->setMinimumSectionSize(27);
        label = new QLabel(deleteItemDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 221, 21));
        label_2 = new QLabel(deleteItemDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 170, 51, 16));
        comboBox = new QComboBox(deleteItemDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 170, 191, 22));
        exitButton = new QPushButton(deleteItemDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(250, 260, 75, 23));
        exeButton = new QPushButton(deleteItemDialog);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setGeometry(QRect(160, 260, 75, 23));
        label_3 = new QLabel(deleteItemDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 210, 61, 16));
        lineEdit = new QLineEdit(deleteItemDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 210, 131, 20));
        label_4 = new QLabel(deleteItemDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 210, 46, 13));
        lineEdit_2 = new QLineEdit(deleteItemDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(270, 210, 71, 20));
        comboBox_2 = new QComboBox(deleteItemDialog);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(80, 210, 131, 22));

        retranslateUi(deleteItemDialog);

        QMetaObject::connectSlotsByName(deleteItemDialog);
    } // setupUi

    void retranslateUi(QDialog *deleteItemDialog)
    {
        deleteItemDialog->setWindowTitle(QApplication::translate("deleteItemDialog", "\345\210\240\351\231\244\351\201\223\345\205\267", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(6, QApplication::translate("deleteItemDialog", "\346\234\200\350\277\221\347\231\273\345\275\225\346\227\266\351\227\264", 0));
        ___qtreewidgetitem->setText(5, QApplication::translate("deleteItemDialog", "\347\255\211\347\272\247", 0));
        ___qtreewidgetitem->setText(4, QApplication::translate("deleteItemDialog", "\350\201\214\344\270\232", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("deleteItemDialog", "\346\200\247\345\210\253", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("deleteItemDialog", "\350\247\222\350\211\262\345\220\215", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("deleteItemDialog", "\350\247\222\350\211\262ID", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("deleteItemDialog", "\345\214\272\346\234\215", 0));
        label->setText(QApplication::translate("deleteItemDialog", "\346\202\250\345\260\206\350\246\201\345\257\271\350\277\231\344\272\233\350\247\222\350\211\262\350\277\233\350\241\214\346\223\215\344\275\234", 0));
        label_2->setText(QApplication::translate("deleteItemDialog", "\345\210\240\351\231\244\346\226\271\345\274\217", 0));
        exitButton->setText(QApplication::translate("deleteItemDialog", "\351\200\200\345\207\272", 0));
        exeButton->setText(QApplication::translate("deleteItemDialog", "\346\211\247\350\241\214", 0));
        label_3->setText(QApplication::translate("deleteItemDialog", "TextLabel", 0));
        label_4->setText(QApplication::translate("deleteItemDialog", "\346\225\260\351\207\217", 0));
    } // retranslateUi

};

namespace Ui {
    class deleteItemDialog: public Ui_deleteItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_ITEM_H
