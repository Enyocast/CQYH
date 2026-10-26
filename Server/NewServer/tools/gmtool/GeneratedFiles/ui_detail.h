/********************************************************************************
** Form generated from reading UI file 'detail.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAIL_H
#define UI_DETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_detailDialog
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QTreeWidget *treeWidget;
    QLabel *label;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *detailDialog)
    {
        if (detailDialog->objectName().isEmpty())
            detailDialog->setObjectName(QStringLiteral("detailDialog"));
        detailDialog->resize(531, 603);
        gridLayout_2 = new QGridLayout(detailDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(detailDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        treeWidget = new QTreeWidget(groupBox);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setColumnCount(3);
        treeWidget->header()->setDefaultSectionSize(160);

        gridLayout_3->addWidget(treeWidget, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 160));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(detailDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 35));
        groupBox_2->setMaximumSize(QSize(16777215, 35));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 23));
        pushButton_2->setMaximumSize(QSize(75, 23));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(75, 23));
        pushButton->setMaximumSize(QSize(75, 23));

        horizontalLayout->addWidget(pushButton);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(detailDialog);

        QMetaObject::connectSlotsByName(detailDialog);
    } // setupUi

    void retranslateUi(QDialog *detailDialog)
    {
        detailDialog->setWindowTitle(QApplication::translate("detailDialog", "\350\257\246\347\273\206\344\277\241\346\201\257", 0));
        groupBox->setTitle(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("detailDialog", "\346\225\260\351\207\217", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("detailDialog", "\350\247\222\350\211\262", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("detailDialog", "\350\256\242\345\215\225ID", 0));
        label->setText(QApplication::translate("detailDialog", "TextLabel", 0));
        groupBox_2->setTitle(QString());
        pushButton_2->setText(QApplication::translate("detailDialog", "\345\217\226\346\266\210\350\256\242\345\215\225", 0));
        pushButton->setText(QApplication::translate("detailDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class detailDialog: public Ui_detailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAIL_H
