/********************************************************************************
** Form generated from reading UI file 'move_position.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVE_POSITION_H
#define UI_MOVE_POSITION_H

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

class Ui_movePositionDialog
{
public:
    QLabel *label;
    QTreeWidget *treeWidget_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QPushButton *exeButton;
    QPushButton *exitButton;
    QComboBox *comboBox;

    void setupUi(QDialog *movePositionDialog)
    {
        if (movePositionDialog->objectName().isEmpty())
            movePositionDialog->setObjectName(QStringLiteral("movePositionDialog"));
        movePositionDialog->resize(350, 300);
        movePositionDialog->setMinimumSize(QSize(350, 300));
        movePositionDialog->setMaximumSize(QSize(350, 300));
        label = new QLabel(movePositionDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 221, 21));
        treeWidget_2 = new QTreeWidget(movePositionDialog);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));
        treeWidget_2->setGeometry(QRect(20, 30, 300, 120));
        treeWidget_2->setMinimumSize(QSize(300, 120));
        treeWidget_2->setMaximumSize(QSize(300, 16777215));
        treeWidget_2->setAlternatingRowColors(true);
        treeWidget_2->setIndentation(2);
        treeWidget_2->setSortingEnabled(true);
        treeWidget_2->header()->setDefaultSectionSize(50);
        treeWidget_2->header()->setMinimumSectionSize(27);
        label_2 = new QLabel(movePositionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 160, 91, 16));
        label_3 = new QLabel(movePositionDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 170, 46, 13));
        label_4 = new QLabel(movePositionDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 210, 21, 16));
        lineEdit_2 = new QLineEdit(movePositionDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(50, 210, 51, 20));
        label_5 = new QLabel(movePositionDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(120, 210, 21, 16));
        lineEdit_3 = new QLineEdit(movePositionDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(130, 210, 51, 20));
        lineEdit_4 = new QLineEdit(movePositionDialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(210, 210, 51, 20));
        label_6 = new QLabel(movePositionDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(200, 210, 21, 16));
        exeButton = new QPushButton(movePositionDialog);
        exeButton->setObjectName(QStringLiteral("exeButton"));
        exeButton->setGeometry(QRect(150, 260, 75, 23));
        exitButton = new QPushButton(movePositionDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(240, 260, 75, 23));
        comboBox = new QComboBox(movePositionDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(150, 170, 161, 22));

        retranslateUi(movePositionDialog);

        QMetaObject::connectSlotsByName(movePositionDialog);
    } // setupUi

    void retranslateUi(QDialog *movePositionDialog)
    {
        movePositionDialog->setWindowTitle(QApplication::translate("movePositionDialog", "\347\247\273\345\212\250\344\275\215\347\275\256", 0));
        label->setText(QApplication::translate("movePositionDialog", "\346\202\250\345\260\206\350\246\201\345\257\271\350\277\231\344\272\233\350\247\222\350\211\262\350\277\233\350\241\214\346\223\215\344\275\234", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(6, QApplication::translate("movePositionDialog", "\346\234\200\350\277\221\347\231\273\345\275\225\346\227\266\351\227\264", 0));
        ___qtreewidgetitem->setText(5, QApplication::translate("movePositionDialog", "\347\255\211\347\272\247", 0));
        ___qtreewidgetitem->setText(4, QApplication::translate("movePositionDialog", "\350\201\214\344\270\232", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("movePositionDialog", "\346\200\247\345\210\253", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("movePositionDialog", "\350\247\222\350\211\262\345\220\215", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("movePositionDialog", "\350\247\222\350\211\262ID", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("movePositionDialog", "\345\214\272\346\234\215", 0));
        label_2->setText(QApplication::translate("movePositionDialog", "\347\233\256\346\240\207\344\275\215\347\275\256", 0));
        label_3->setText(QApplication::translate("movePositionDialog", "\345\234\260\345\233\276", 0));
        label_4->setText(QApplication::translate("movePositionDialog", "X", 0));
        label_5->setText(QApplication::translate("movePositionDialog", "Y", 0));
        lineEdit_4->setText(QString());
        label_6->setText(QApplication::translate("movePositionDialog", "Z", 0));
        exeButton->setText(QApplication::translate("movePositionDialog", "\346\211\247\350\241\214", 0));
        exitButton->setText(QApplication::translate("movePositionDialog", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class movePositionDialog: public Ui_movePositionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVE_POSITION_H
