/********************************************************************************
** Form generated from reading UI file 'role_info.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROLE_INFO_H
#define UI_ROLE_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoleInfoDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QPushButton *OkButton;
    QSpacerItem *horizontalSpacer;
    QTextEdit *modifyRoleReasonEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QTreeWidget *baseDataTreeWidget;
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTreeWidget *questWidget;
    QPushButton *delQuestButton;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_12;
    QTreeWidget *spellTreeWidget;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_11;
    QTreeWidget *titleTreeWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_9;
    QTreeWidget *itemWidget;
    QLabel *label_2;
    QPushButton *delItemButton;
    QPushButton *takeItemButton;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QTreeWidget *mailTreeWidget;
    QPushButton *delMailButton;
    QWidget *tab_4;

    void setupUi(QDialog *RoleInfoDialog)
    {
        if (RoleInfoDialog->objectName().isEmpty())
            RoleInfoDialog->setObjectName(QStringLiteral("RoleInfoDialog"));
        RoleInfoDialog->resize(1042, 832);
        gridLayout = new QGridLayout(RoleInfoDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_5 = new QGroupBox(RoleInfoDialog);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(0, 40));
        groupBox_5->setMaximumSize(QSize(16777215, 40));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        OkButton = new QPushButton(groupBox_5);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        OkButton->setMinimumSize(QSize(0, 23));
        OkButton->setMaximumSize(QSize(75, 23));

        gridLayout_4->addWidget(OkButton, 1, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(0, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 0, 1, 1);

        modifyRoleReasonEdit = new QTextEdit(groupBox_5);
        modifyRoleReasonEdit->setObjectName(QStringLiteral("modifyRoleReasonEdit"));
        modifyRoleReasonEdit->setMinimumSize(QSize(500, 0));

        gridLayout_4->addWidget(modifyRoleReasonEdit, 1, 3, 1, 1);

        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        cancelButton = new QPushButton(groupBox_5);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout_4->addWidget(cancelButton, 1, 6, 1, 1);


        gridLayout->addWidget(groupBox_5, 1, 0, 1, 1);

        tabWidget = new QTabWidget(RoleInfoDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_10 = new QGridLayout(tab);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(320, 350));
        groupBox_4->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        baseDataTreeWidget = new QTreeWidget(groupBox_4);
        baseDataTreeWidget->setObjectName(QStringLiteral("baseDataTreeWidget"));
        baseDataTreeWidget->header()->setDefaultSectionSize(120);

        gridLayout_7->addWidget(baseDataTreeWidget, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_7->addWidget(pushButton, 1, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(200, 350));
        groupBox_3->setMaximumSize(QSize(300, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        questWidget = new QTreeWidget(groupBox_3);
        questWidget->setObjectName(QStringLiteral("questWidget"));
        questWidget->header()->setDefaultSectionSize(120);

        gridLayout_3->addWidget(questWidget, 0, 0, 1, 1);

        delQuestButton = new QPushButton(groupBox_3);
        delQuestButton->setObjectName(QStringLiteral("delQuestButton"));

        gridLayout_3->addWidget(delQuestButton, 1, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_3, 0, 1, 1, 1);

        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setMinimumSize(QSize(0, 350));
        gridLayout_12 = new QGridLayout(groupBox_8);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        spellTreeWidget = new QTreeWidget(groupBox_8);
        spellTreeWidget->setObjectName(QStringLiteral("spellTreeWidget"));
        spellTreeWidget->header()->setDefaultSectionSize(160);

        gridLayout_12->addWidget(spellTreeWidget, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_8, 1, 0, 1, 1);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(200, 350));
        groupBox_6->setMaximumSize(QSize(300, 16777215));
        gridLayout_11 = new QGridLayout(groupBox_6);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        titleTreeWidget = new QTreeWidget(groupBox_6);
        titleTreeWidget->setObjectName(QStringLiteral("titleTreeWidget"));
        titleTreeWidget->header()->setDefaultSectionSize(130);

        gridLayout_11->addWidget(titleTreeWidget, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_6, 1, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_9 = new QGridLayout(tab_2);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        itemWidget = new QTreeWidget(tab_2);
        itemWidget->setObjectName(QStringLiteral("itemWidget"));
        itemWidget->setMinimumSize(QSize(450, 0));
        itemWidget->header()->setDefaultSectionSize(150);

        gridLayout_9->addWidget(itemWidget, 1, 0, 1, 5);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_9->addWidget(label_2, 0, 0, 1, 1);

        delItemButton = new QPushButton(tab_2);
        delItemButton->setObjectName(QStringLiteral("delItemButton"));

        gridLayout_9->addWidget(delItemButton, 2, 4, 1, 1);

        takeItemButton = new QPushButton(tab_2);
        takeItemButton->setObjectName(QStringLiteral("takeItemButton"));
        takeItemButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_9->addWidget(takeItemButton, 2, 0, 1, 2);

        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        lineEdit->setInputMethodHints(Qt::ImhPreferNumbers);

        gridLayout_9->addWidget(lineEdit, 0, 2, 1, 1);

        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_9->addWidget(pushButton_3, 0, 3, 1, 2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox_7 = new QGroupBox(tab_3);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(320, 200));
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        mailTreeWidget = new QTreeWidget(groupBox_7);
        mailTreeWidget->setObjectName(QStringLiteral("mailTreeWidget"));
        mailTreeWidget->setEnabled(true);
        mailTreeWidget->header()->setDefaultSectionSize(111);

        gridLayout_8->addWidget(mailTreeWidget, 0, 0, 1, 1);

        delMailButton = new QPushButton(groupBox_7);
        delMailButton->setObjectName(QStringLiteral("delMailButton"));

        gridLayout_8->addWidget(delMailButton, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_7, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(RoleInfoDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RoleInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *RoleInfoDialog)
    {
        RoleInfoDialog->setWindowTitle(QApplication::translate("RoleInfoDialog", "\350\247\222\350\211\262\344\277\241\346\201\257", 0));
        groupBox_5->setTitle(QString());
        OkButton->setText(QApplication::translate("RoleInfoDialog", "\347\241\256\350\256\244", 0));
        label->setText(QApplication::translate("RoleInfoDialog", "\345\216\237\345\233\240", 0));
        cancelButton->setText(QApplication::translate("RoleInfoDialog", "\345\217\226\346\266\210", 0));
        groupBox_4->setTitle(QApplication::translate("RoleInfoDialog", "\345\237\272\347\241\200\345\261\236\346\200\247", 0));
        QTreeWidgetItem *___qtreewidgetitem = baseDataTreeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("RoleInfoDialog", "\345\200\274", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("RoleInfoDialog", "\351\224\256", 0));
        pushButton->setText(QApplication::translate("RoleInfoDialog", "\350\277\224\345\233\236\345\207\272\347\224\237\347\202\271", 0));
        groupBox_3->setTitle(QApplication::translate("RoleInfoDialog", "\344\273\273\345\212\241", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = questWidget->headerItem();
        ___qtreewidgetitem1->setText(1, QApplication::translate("RoleInfoDialog", "\344\273\273\345\212\241\345\220\215", 0));
        ___qtreewidgetitem1->setText(0, QApplication::translate("RoleInfoDialog", "\344\273\273\345\212\241ID", 0));
        delQuestButton->setText(QApplication::translate("RoleInfoDialog", "\345\210\240\351\231\244\344\273\273\345\212\241", 0));
        groupBox_8->setTitle(QApplication::translate("RoleInfoDialog", "\346\212\200\350\203\275", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = spellTreeWidget->headerItem();
        ___qtreewidgetitem2->setText(1, QApplication::translate("RoleInfoDialog", "\346\212\200\350\203\275\346\240\217\344\275\215\347\275\256", 0));
        ___qtreewidgetitem2->setText(0, QApplication::translate("RoleInfoDialog", "\346\212\200\350\203\275\345\220\215", 0));
        groupBox_6->setTitle(QApplication::translate("RoleInfoDialog", "\347\247\260\345\217\267", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = titleTreeWidget->headerItem();
        ___qtreewidgetitem3->setText(1, QApplication::translate("RoleInfoDialog", "\345\210\260\346\234\237\346\227\266\351\227\264", 0));
        ___qtreewidgetitem3->setText(0, QApplication::translate("RoleInfoDialog", "\347\247\260\345\217\267\345\220\215", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RoleInfoDialog", "\345\261\236\346\200\247", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = itemWidget->headerItem();
        ___qtreewidgetitem4->setText(5, QApplication::translate("RoleInfoDialog", "\346\225\260\351\207\217", 0));
        ___qtreewidgetitem4->setText(4, QApplication::translate("RoleInfoDialog", "\347\261\273\345\236\213", 0));
        ___qtreewidgetitem4->setText(3, QApplication::translate("RoleInfoDialog", "\344\275\215\347\275\256", 0));
        ___qtreewidgetitem4->setText(2, QApplication::translate("RoleInfoDialog", "\351\201\223\345\205\267\345\220\215", 0));
        ___qtreewidgetitem4->setText(1, QApplication::translate("RoleInfoDialog", "\351\201\223\345\205\267\345\224\257\344\270\200ID", 0));
        ___qtreewidgetitem4->setText(0, QApplication::translate("RoleInfoDialog", "\351\201\223\345\205\267ID", 0));
        label_2->setText(QApplication::translate("RoleInfoDialog", "\351\201\223\345\205\267\350\275\254\347\247\273\347\233\256\346\240\207\350\247\222\350\211\262", 0));
        delItemButton->setText(QApplication::translate("RoleInfoDialog", "\345\210\240\351\231\244\351\201\223\345\205\267", 0));
        takeItemButton->setText(QApplication::translate("RoleInfoDialog", "\345\220\221\347\233\256\346\240\207\350\203\214\345\214\205\350\275\254\347\247\273", 0));
        pushButton_3->setText(QApplication::translate("RoleInfoDialog", "\347\241\256\350\256\244\347\233\256\346\240\207\350\247\222\350\211\262", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RoleInfoDialog", "\351\201\223\345\205\267", 0));
        groupBox_7->setTitle(QApplication::translate("RoleInfoDialog", "\351\202\256\344\273\266", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = mailTreeWidget->headerItem();
        ___qtreewidgetitem5->setText(5, QApplication::translate("RoleInfoDialog", "\347\211\251\345\223\201\346\225\260\351\207\217", 0));
        ___qtreewidgetitem5->setText(4, QApplication::translate("RoleInfoDialog", "\347\211\251\345\223\201\347\261\273\345\236\213ID", 0));
        ___qtreewidgetitem5->setText(3, QApplication::translate("RoleInfoDialog", "\346\230\257\345\220\246\346\234\211\351\231\204\344\273\266", 0));
        ___qtreewidgetitem5->setText(2, QApplication::translate("RoleInfoDialog", "\346\230\257\345\220\246\351\242\206\345\217\226", 0));
        ___qtreewidgetitem5->setText(1, QApplication::translate("RoleInfoDialog", "\351\202\256\344\273\266\347\261\273\345\236\213", 0));
        ___qtreewidgetitem5->setText(0, QApplication::translate("RoleInfoDialog", "\344\270\273\351\242\230", 0));
        delMailButton->setText(QApplication::translate("RoleInfoDialog", "\345\210\240\351\231\244\351\202\256\344\273\266", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("RoleInfoDialog", "\351\202\256\344\273\266", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("RoleInfoDialog", "\346\212\200\350\203\275", 0));
    } // retranslateUi

};

namespace Ui {
    class RoleInfoDialog: public Ui_RoleInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROLE_INFO_H
