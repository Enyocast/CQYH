/********************************************************************************
** Form generated from reading UI file 'view_friend.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_FRIEND_H
#define UI_VIEW_FRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_viewFriendDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QTreeWidget *treeWidget;

    void setupUi(QDialog *viewFriendDialog)
    {
        if (viewFriendDialog->objectName().isEmpty())
            viewFriendDialog->setObjectName(QStringLiteral("viewFriendDialog"));
        viewFriendDialog->resize(623, 478);
        gridLayout = new QGridLayout(viewFriendDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(viewFriendDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(60, 16777215));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        treeWidget = new QTreeWidget(groupBox);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setDefaultSectionSize(100);

        gridLayout_2->addWidget(treeWidget, 1, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(viewFriendDialog);

        QMetaObject::connectSlotsByName(viewFriendDialog);
    } // setupUi

    void retranslateUi(QDialog *viewFriendDialog)
    {
        viewFriendDialog->setWindowTitle(QApplication::translate("viewFriendDialog", "\346\237\245\347\234\213\345\245\275\345\217\213", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("viewFriendDialog", "\350\247\222\350\211\262\345\220\215", 0));
        label_2->setText(QApplication::translate("viewFriendDialog", "\346\210\221\345\217\253MT", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("viewFriendDialog", "\350\247\222\350\211\262\345\220\215", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("viewFriendDialog", "\345\245\275\345\217\213\347\261\273\345\236\213", 0));
    } // retranslateUi

};

namespace Ui {
    class viewFriendDialog: public Ui_viewFriendDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_FRIEND_H
