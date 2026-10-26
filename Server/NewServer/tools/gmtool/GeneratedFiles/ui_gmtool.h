/********************************************************************************
** Form generated from reading UI file 'gmtool.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GMTOOL_H
#define UI_GMTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gmtoolClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_9;
    QPushButton *loginButton;
    QPushButton *logoutButton;
    QTreeWidget *treeWidget_SvrList;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_10;
    QTextBrowser *textBrowser;
    QPushButton *clearLogButton;
    QPushButton *exitButton;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *queryRoleID;
    QLabel *label_14;
    QRadioButton *radioButton_query_1;
    QRadioButton *radioButton_query_2;
    QLineEdit *lineEdit_query_1;
    QLineEdit *lineEdit_query_2;
    QTreeWidget *treeWidget_queryroleid;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_11;
    QRadioButton *radioButton_queryByID;
    QRadioButton *radioButton_queryByFile;
    QLineEdit *lineEdit_queryByid;
    QLabel *label_15;
    QTreeWidget *treeWidget;
    QPushButton *viewButton;
    QToolButton *toolButton;
    QLineEdit *lineEdit_queryByFile;
    QPushButton *roleGMCmdhButton;
    QPushButton *query_role_data_button;
    QPushButton *modifyButton;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QRadioButton *radioButton_5;
    QLineEdit *lineEdit;
    QRadioButton *radioButton_6;
    QToolButton *toolButton_2;
    QTextEdit *textEdit_RoleID;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_14;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lineEdit_mail_2;
    QLabel *label_20;
    QLineEdit *lineEdit_mail_3;
    QPushButton *mailButton;
    QTextEdit *textEdit_mail;
    QLineEdit *lineEdit_mail_1;
    QComboBox *mailItem_comboBox;
    QLabel *label_11;
    QTextEdit *mailReasonEdit;
    QGroupBox *groupBox_3;
    QLineEdit *forbiddenChatTimeEdit;
    QPushButton *forbiddenChatButton;
    QPushButton *unForbiddenChatButton;
    QLabel *label_4;
    QPushButton *freezeRoleButton;
    QPushButton *unfreezeRoleButton;
    QPushButton *kickRoleButton;
    QRadioButton *fc1_radioButton;
    QRadioButton *fc2_radioButton;
    QComboBox *fc1_comboBox;
    QLabel *label_13;
    QWidget *tab_4;
    QWidget *tab_5;
    QGridLayout *gridLayout_12;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_13;
    QLabel *label;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit_announce;
    QLabel *label_6;
    QLineEdit *lineEdit_announce_1;
    QLabel *label_16;
    QLineEdit *lineEdit_announce_2;
    QPushButton *annouceButton;
    QTextEdit *textEdit_announce;
    QPushButton *delAnnounceButton;
    QLabel *label_5;
    QComboBox *comboBox;
    QTreeWidget *announceWidget;
    QPushButton *getAnnounceButton;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_7;
    QPushButton *searchButton_log;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_8;
    QLabel *label_8;
    QLabel *label_7;
    QDateTimeEdit *dateTimeEdit_log_1;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_16;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_log_1;
    QLineEdit *lineEdit_log_1;
    QLineEdit *lineEdit_log_3;
    QLabel *label_log_3;
    QLabel *label_log_2;
    QLineEdit *lineEdit_log_2;
    QLineEdit *lineEdit_log_6;
    QLineEdit *lineEdit_log_4;
    QLineEdit *lineEdit_log_5;
    QLabel *label_log_6;
    QLabel *label_log_4;
    QLabel *label_log_5;
    QLabel *label_log_0;
    QLineEdit *lineEdit_log_0;
    QDateTimeEdit *dateTimeEdit_log_2;
    QComboBox *logComboBox;
    QLabel *label_10;
    QLineEdit *lineEdit_log;
    QTextEdit *textEdit;
    QWidget *tab_7;
    QPushButton *queryfileButton;
    QLineEdit *queryfile_lineEdit;
    QLabel *label_12;
    QWidget *tab_6;
    QLabel *label_2;
    QTextEdit *textEdit_gmStrCmd;
    QPushButton *pushButton_gmStrCmd;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *gmtoolClass)
    {
        if (gmtoolClass->objectName().isEmpty())
            gmtoolClass->setObjectName(QStringLiteral("gmtoolClass"));
        gmtoolClass->resize(1011, 832);
        centralWidget = new QWidget(gmtoolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_12 = new QGroupBox(centralWidget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setMinimumSize(QSize(150, 150));
        groupBox_12->setMaximumSize(QSize(222, 16777215));
        gridLayout_9 = new QGridLayout(groupBox_12);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        loginButton = new QPushButton(groupBox_12);
        loginButton->setObjectName(QStringLiteral("loginButton"));

        gridLayout_9->addWidget(loginButton, 1, 1, 1, 1);

        logoutButton = new QPushButton(groupBox_12);
        logoutButton->setObjectName(QStringLiteral("logoutButton"));

        gridLayout_9->addWidget(logoutButton, 1, 2, 1, 1);

        treeWidget_SvrList = new QTreeWidget(groupBox_12);
        treeWidget_SvrList->setObjectName(QStringLiteral("treeWidget_SvrList"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        treeWidget_SvrList->setFont(font);
        treeWidget_SvrList->setAutoFillBackground(false);
        treeWidget_SvrList->setAlternatingRowColors(true);
        treeWidget_SvrList->setAllColumnsShowFocus(true);
        treeWidget_SvrList->header()->setCascadingSectionResizes(false);
        treeWidget_SvrList->header()->setHighlightSections(false);
        treeWidget_SvrList->header()->setProperty("showSortIndicator", QVariant(false));

        gridLayout_9->addWidget(treeWidget_SvrList, 0, 1, 1, 2);


        gridLayout->addWidget(groupBox_12, 2, 0, 1, 1);

        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(500, 150));
        groupBox_6->setMaximumSize(QSize(16777215, 150));
        gridLayout_10 = new QGridLayout(groupBox_6);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        textBrowser = new QTextBrowser(groupBox_6);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout_10->addWidget(textBrowser, 0, 0, 3, 1);

        clearLogButton = new QPushButton(groupBox_6);
        clearLogButton->setObjectName(QStringLiteral("clearLogButton"));

        gridLayout_10->addWidget(clearLogButton, 1, 1, 1, 1);

        exitButton = new QPushButton(groupBox_6);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setMinimumSize(QSize(75, 23));
        exitButton->setMaximumSize(QSize(75, 23));

        gridLayout_10->addWidget(exitButton, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_6, 3, 0, 1, 2);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 200));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        queryRoleID = new QPushButton(groupBox_4);
        queryRoleID->setObjectName(QStringLiteral("queryRoleID"));

        gridLayout_4->addWidget(queryRoleID, 0, 5, 2, 1);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 2, 0, 1, 1);

        radioButton_query_1 = new QRadioButton(groupBox_4);
        radioButton_query_1->setObjectName(QStringLiteral("radioButton_query_1"));

        gridLayout_4->addWidget(radioButton_query_1, 0, 0, 1, 1);

        radioButton_query_2 = new QRadioButton(groupBox_4);
        radioButton_query_2->setObjectName(QStringLiteral("radioButton_query_2"));

        gridLayout_4->addWidget(radioButton_query_2, 1, 0, 1, 1);

        lineEdit_query_1 = new QLineEdit(groupBox_4);
        lineEdit_query_1->setObjectName(QStringLiteral("lineEdit_query_1"));

        gridLayout_4->addWidget(lineEdit_query_1, 0, 1, 1, 1);

        lineEdit_query_2 = new QLineEdit(groupBox_4);
        lineEdit_query_2->setObjectName(QStringLiteral("lineEdit_query_2"));

        gridLayout_4->addWidget(lineEdit_query_2, 1, 1, 1, 1);

        treeWidget_queryroleid = new QTreeWidget(groupBox_4);
        treeWidget_queryroleid->setObjectName(QStringLiteral("treeWidget_queryroleid"));
        treeWidget_queryroleid->header()->setDefaultSectionSize(100);

        gridLayout_4->addWidget(treeWidget_queryroleid, 2, 1, 1, 5);


        gridLayout_2->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        gridLayout_11 = new QGridLayout(groupBox_9);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        radioButton_queryByID = new QRadioButton(groupBox_9);
        radioButton_queryByID->setObjectName(QStringLiteral("radioButton_queryByID"));
        radioButton_queryByID->setMaximumSize(QSize(75, 20));

        gridLayout_11->addWidget(radioButton_queryByID, 0, 0, 1, 1);

        radioButton_queryByFile = new QRadioButton(groupBox_9);
        radioButton_queryByFile->setObjectName(QStringLiteral("radioButton_queryByFile"));
        radioButton_queryByFile->setEnabled(false);
        radioButton_queryByFile->setMaximumSize(QSize(75, 20));

        gridLayout_11->addWidget(radioButton_queryByFile, 1, 0, 1, 1);

        lineEdit_queryByid = new QLineEdit(groupBox_9);
        lineEdit_queryByid->setObjectName(QStringLiteral("lineEdit_queryByid"));

        gridLayout_11->addWidget(lineEdit_queryByid, 0, 1, 1, 4);

        label_15 = new QLabel(groupBox_9);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMaximumSize(QSize(16777215, 28));

        gridLayout_11->addWidget(label_15, 4, 2, 1, 1);

        treeWidget = new QTreeWidget(groupBox_9);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(400, 200));
        treeWidget->setMaximumSize(QSize(16777215, 500));
        treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setIndentation(2);
        treeWidget->setSortingEnabled(true);
        treeWidget->setAnimated(false);
        treeWidget->setColumnCount(10);
        treeWidget->header()->setDefaultSectionSize(70);

        gridLayout_11->addWidget(treeWidget, 7, 0, 1, 5);

        viewButton = new QPushButton(groupBox_9);
        viewButton->setObjectName(QStringLiteral("viewButton"));

        gridLayout_11->addWidget(viewButton, 8, 4, 1, 1);

        toolButton = new QToolButton(groupBox_9);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setMinimumSize(QSize(60, 0));

        gridLayout_11->addWidget(toolButton, 1, 4, 1, 1);

        lineEdit_queryByFile = new QLineEdit(groupBox_9);
        lineEdit_queryByFile->setObjectName(QStringLiteral("lineEdit_queryByFile"));
        lineEdit_queryByFile->setEnabled(false);

        gridLayout_11->addWidget(lineEdit_queryByFile, 1, 1, 1, 3);

        roleGMCmdhButton = new QPushButton(groupBox_9);
        roleGMCmdhButton->setObjectName(QStringLiteral("roleGMCmdhButton"));

        gridLayout_11->addWidget(roleGMCmdhButton, 3, 2, 1, 1);

        query_role_data_button = new QPushButton(groupBox_9);
        query_role_data_button->setObjectName(QStringLiteral("query_role_data_button"));
        query_role_data_button->setMinimumSize(QSize(0, 0));
        query_role_data_button->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_11->addWidget(query_role_data_button, 3, 3, 1, 1);

        modifyButton = new QPushButton(groupBox_9);
        modifyButton->setObjectName(QStringLiteral("modifyButton"));
        QFont font1;
        font1.setPointSize(8);
        modifyButton->setFont(font1);

        gridLayout_11->addWidget(modifyButton, 3, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_9, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        gridLayout_5->addWidget(radioButton_5, 1, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_5->addWidget(lineEdit, 1, 1, 1, 1);

        radioButton_6 = new QRadioButton(groupBox);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));

        gridLayout_5->addWidget(radioButton_6, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));

        gridLayout_5->addWidget(toolButton_2, 1, 2, 1, 1);

        textEdit_RoleID = new QTextEdit(groupBox);
        textEdit_RoleID->setObjectName(QStringLiteral("textEdit_RoleID"));
        textEdit_RoleID->setMinimumSize(QSize(0, 80));

        gridLayout_5->addWidget(textEdit_RoleID, 0, 1, 1, 2);

        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(400, 200));
        gridLayout_14 = new QGridLayout(groupBox_5);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_14->addWidget(label_17, 0, 0, 1, 1);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_14->addWidget(label_18, 1, 0, 1, 1);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_14->addWidget(label_19, 5, 0, 1, 1);

        lineEdit_mail_2 = new QLineEdit(groupBox_5);
        lineEdit_mail_2->setObjectName(QStringLiteral("lineEdit_mail_2"));

        gridLayout_14->addWidget(lineEdit_mail_2, 5, 1, 1, 1);

        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_14->addWidget(label_20, 5, 2, 1, 1);

        lineEdit_mail_3 = new QLineEdit(groupBox_5);
        lineEdit_mail_3->setObjectName(QStringLiteral("lineEdit_mail_3"));

        gridLayout_14->addWidget(lineEdit_mail_3, 5, 3, 1, 1);

        mailButton = new QPushButton(groupBox_5);
        mailButton->setObjectName(QStringLiteral("mailButton"));

        gridLayout_14->addWidget(mailButton, 5, 4, 1, 1);

        textEdit_mail = new QTextEdit(groupBox_5);
        textEdit_mail->setObjectName(QStringLiteral("textEdit_mail"));

        gridLayout_14->addWidget(textEdit_mail, 1, 1, 1, 4);

        lineEdit_mail_1 = new QLineEdit(groupBox_5);
        lineEdit_mail_1->setObjectName(QStringLiteral("lineEdit_mail_1"));

        gridLayout_14->addWidget(lineEdit_mail_1, 0, 1, 1, 4);

        mailItem_comboBox = new QComboBox(groupBox_5);
        mailItem_comboBox->setObjectName(QStringLiteral("mailItem_comboBox"));
        mailItem_comboBox->setEnabled(false);
        mailItem_comboBox->setEditable(true);
        mailItem_comboBox->setMaxVisibleItems(16);

        gridLayout_14->addWidget(mailItem_comboBox, 4, 1, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_14->addWidget(label_11, 2, 0, 1, 1);

        mailReasonEdit = new QTextEdit(groupBox_5);
        mailReasonEdit->setObjectName(QStringLiteral("mailReasonEdit"));

        gridLayout_14->addWidget(mailReasonEdit, 2, 1, 1, 4);


        gridLayout_5->addWidget(groupBox_5, 3, 0, 1, 3);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(450, 150));
        forbiddenChatTimeEdit = new QLineEdit(groupBox_3);
        forbiddenChatTimeEdit->setObjectName(QStringLiteral("forbiddenChatTimeEdit"));
        forbiddenChatTimeEdit->setGeometry(QRect(380, 30, 113, 20));
        forbiddenChatButton = new QPushButton(groupBox_3);
        forbiddenChatButton->setObjectName(QStringLiteral("forbiddenChatButton"));
        forbiddenChatButton->setGeometry(QRect(40, 80, 75, 23));
        unForbiddenChatButton = new QPushButton(groupBox_3);
        unForbiddenChatButton->setObjectName(QStringLiteral("unForbiddenChatButton"));
        unForbiddenChatButton->setGeometry(QRect(130, 80, 75, 23));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 30, 111, 16));
        freezeRoleButton = new QPushButton(groupBox_3);
        freezeRoleButton->setObjectName(QStringLiteral("freezeRoleButton"));
        freezeRoleButton->setGeometry(QRect(280, 80, 75, 23));
        unfreezeRoleButton = new QPushButton(groupBox_3);
        unfreezeRoleButton->setObjectName(QStringLiteral("unfreezeRoleButton"));
        unfreezeRoleButton->setGeometry(QRect(370, 80, 75, 23));
        kickRoleButton = new QPushButton(groupBox_3);
        kickRoleButton->setObjectName(QStringLiteral("kickRoleButton"));
        kickRoleButton->setGeometry(QRect(20, 120, 75, 23));
        fc1_radioButton = new QRadioButton(groupBox_3);
        fc1_radioButton->setObjectName(QStringLiteral("fc1_radioButton"));
        fc1_radioButton->setGeometry(QRect(150, 30, 21, 17));
        fc2_radioButton = new QRadioButton(groupBox_3);
        fc2_radioButton->setObjectName(QStringLiteral("fc2_radioButton"));
        fc2_radioButton->setGeometry(QRect(350, 30, 21, 17));
        fc1_comboBox = new QComboBox(groupBox_3);
        fc1_comboBox->setObjectName(QStringLiteral("fc1_comboBox"));
        fc1_comboBox->setGeometry(QRect(180, 30, 111, 22));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(530, 0, 121, 81));

        gridLayout_5->addWidget(groupBox_3, 2, 0, 1, 3);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        gridLayout_12 = new QGridLayout(tab_5);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer_2, 3, 0, 1, 1);

        groupBox_13 = new QGroupBox(tab_5);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setMinimumSize(QSize(400, 150));
        groupBox_13->setMaximumSize(QSize(16777215, 200));
        gridLayout_13 = new QGridLayout(groupBox_13);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        label = new QLabel(groupBox_13);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_13->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_13);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_13->addWidget(label_3, 2, 0, 1, 1);

        dateTimeEdit_announce = new QDateTimeEdit(groupBox_13);
        dateTimeEdit_announce->setObjectName(QStringLiteral("dateTimeEdit_announce"));

        gridLayout_13->addWidget(dateTimeEdit_announce, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox_13);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_13->addWidget(label_6, 3, 0, 1, 1);

        lineEdit_announce_1 = new QLineEdit(groupBox_13);
        lineEdit_announce_1->setObjectName(QStringLiteral("lineEdit_announce_1"));

        gridLayout_13->addWidget(lineEdit_announce_1, 3, 1, 1, 1);

        label_16 = new QLabel(groupBox_13);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_13->addWidget(label_16, 3, 2, 1, 1);

        lineEdit_announce_2 = new QLineEdit(groupBox_13);
        lineEdit_announce_2->setObjectName(QStringLiteral("lineEdit_announce_2"));

        gridLayout_13->addWidget(lineEdit_announce_2, 3, 3, 1, 1);

        annouceButton = new QPushButton(groupBox_13);
        annouceButton->setObjectName(QStringLiteral("annouceButton"));

        gridLayout_13->addWidget(annouceButton, 4, 3, 1, 1);

        textEdit_announce = new QTextEdit(groupBox_13);
        textEdit_announce->setObjectName(QStringLiteral("textEdit_announce"));
        textEdit_announce->setMinimumSize(QSize(0, 50));

        gridLayout_13->addWidget(textEdit_announce, 1, 1, 1, 3);

        delAnnounceButton = new QPushButton(groupBox_13);
        delAnnounceButton->setObjectName(QStringLiteral("delAnnounceButton"));

        gridLayout_13->addWidget(delAnnounceButton, 4, 0, 1, 1);

        label_5 = new QLabel(groupBox_13);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_13->addWidget(label_5, 0, 0, 1, 1);

        comboBox = new QComboBox(groupBox_13);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMaxVisibleItems(16);

        gridLayout_13->addWidget(comboBox, 0, 1, 1, 1);


        gridLayout_12->addWidget(groupBox_13, 0, 0, 1, 1);

        announceWidget = new QTreeWidget(tab_5);
        announceWidget->setObjectName(QStringLiteral("announceWidget"));
        announceWidget->setIndentation(20);
        announceWidget->header()->setDefaultSectionSize(100);

        gridLayout_12->addWidget(announceWidget, 2, 0, 1, 1);

        getAnnounceButton = new QPushButton(tab_5);
        getAnnounceButton->setObjectName(QStringLiteral("getAnnounceButton"));

        gridLayout_12->addWidget(getAnnounceButton, 1, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBox_7 = new QGroupBox(tab_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(280, 435));
        groupBox_7->setMaximumSize(QSize(280, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_7);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_10 = new QGroupBox(groupBox_7);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        gridLayout_7 = new QGridLayout(groupBox_10);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(2, 2, 2, 2);
        searchButton_log = new QPushButton(groupBox_10);
        searchButton_log->setObjectName(QStringLiteral("searchButton_log"));

        gridLayout_7->addWidget(searchButton_log, 2, 0, 1, 2);

        groupBox_11 = new QGroupBox(groupBox_10);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        gridLayout_8 = new QGridLayout(groupBox_11);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_8 = new QLabel(groupBox_11);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(55, 16777215));

        gridLayout_8->addWidget(label_8, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox_11);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(55, 16777215));

        gridLayout_8->addWidget(label_7, 2, 1, 1, 1);

        dateTimeEdit_log_1 = new QDateTimeEdit(groupBox_11);
        dateTimeEdit_log_1->setObjectName(QStringLiteral("dateTimeEdit_log_1"));

        gridLayout_8->addWidget(dateTimeEdit_log_1, 2, 2, 1, 1);

        groupBox_14 = new QGroupBox(groupBox_11);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setMinimumSize(QSize(0, 250));
        gridLayout_16 = new QGridLayout(groupBox_14);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_16->addItem(verticalSpacer_3, 7, 0, 1, 1);

        label_log_1 = new QLabel(groupBox_14);
        label_log_1->setObjectName(QStringLiteral("label_log_1"));

        gridLayout_16->addWidget(label_log_1, 1, 0, 1, 1);

        lineEdit_log_1 = new QLineEdit(groupBox_14);
        lineEdit_log_1->setObjectName(QStringLiteral("lineEdit_log_1"));

        gridLayout_16->addWidget(lineEdit_log_1, 1, 1, 1, 1);

        lineEdit_log_3 = new QLineEdit(groupBox_14);
        lineEdit_log_3->setObjectName(QStringLiteral("lineEdit_log_3"));

        gridLayout_16->addWidget(lineEdit_log_3, 3, 1, 1, 1);

        label_log_3 = new QLabel(groupBox_14);
        label_log_3->setObjectName(QStringLiteral("label_log_3"));

        gridLayout_16->addWidget(label_log_3, 3, 0, 1, 1);

        label_log_2 = new QLabel(groupBox_14);
        label_log_2->setObjectName(QStringLiteral("label_log_2"));

        gridLayout_16->addWidget(label_log_2, 2, 0, 1, 1);

        lineEdit_log_2 = new QLineEdit(groupBox_14);
        lineEdit_log_2->setObjectName(QStringLiteral("lineEdit_log_2"));

        gridLayout_16->addWidget(lineEdit_log_2, 2, 1, 1, 1);

        lineEdit_log_6 = new QLineEdit(groupBox_14);
        lineEdit_log_6->setObjectName(QStringLiteral("lineEdit_log_6"));

        gridLayout_16->addWidget(lineEdit_log_6, 6, 1, 1, 1);

        lineEdit_log_4 = new QLineEdit(groupBox_14);
        lineEdit_log_4->setObjectName(QStringLiteral("lineEdit_log_4"));

        gridLayout_16->addWidget(lineEdit_log_4, 4, 1, 1, 1);

        lineEdit_log_5 = new QLineEdit(groupBox_14);
        lineEdit_log_5->setObjectName(QStringLiteral("lineEdit_log_5"));

        gridLayout_16->addWidget(lineEdit_log_5, 5, 1, 1, 1);

        label_log_6 = new QLabel(groupBox_14);
        label_log_6->setObjectName(QStringLiteral("label_log_6"));

        gridLayout_16->addWidget(label_log_6, 6, 0, 1, 1);

        label_log_4 = new QLabel(groupBox_14);
        label_log_4->setObjectName(QStringLiteral("label_log_4"));

        gridLayout_16->addWidget(label_log_4, 4, 0, 1, 1);

        label_log_5 = new QLabel(groupBox_14);
        label_log_5->setObjectName(QStringLiteral("label_log_5"));

        gridLayout_16->addWidget(label_log_5, 5, 0, 1, 1);

        label_log_0 = new QLabel(groupBox_14);
        label_log_0->setObjectName(QStringLiteral("label_log_0"));

        gridLayout_16->addWidget(label_log_0, 0, 0, 1, 1);

        lineEdit_log_0 = new QLineEdit(groupBox_14);
        lineEdit_log_0->setObjectName(QStringLiteral("lineEdit_log_0"));

        gridLayout_16->addWidget(lineEdit_log_0, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_14, 1, 1, 1, 2);

        dateTimeEdit_log_2 = new QDateTimeEdit(groupBox_11);
        dateTimeEdit_log_2->setObjectName(QStringLiteral("dateTimeEdit_log_2"));

        gridLayout_8->addWidget(dateTimeEdit_log_2, 3, 2, 1, 1);

        logComboBox = new QComboBox(groupBox_11);
        logComboBox->setObjectName(QStringLiteral("logComboBox"));

        gridLayout_8->addWidget(logComboBox, 0, 1, 1, 2);


        gridLayout_7->addWidget(groupBox_11, 0, 0, 1, 2);

        label_10 = new QLabel(groupBox_10);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_7->addWidget(label_10, 1, 0, 1, 1);

        lineEdit_log = new QLineEdit(groupBox_10);
        lineEdit_log->setObjectName(QStringLiteral("lineEdit_log"));

        gridLayout_7->addWidget(lineEdit_log, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_10);


        gridLayout_6->addWidget(groupBox_7, 0, 0, 1, 1);

        textEdit = new QTextEdit(tab_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_6->addWidget(textEdit, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        queryfileButton = new QPushButton(tab_7);
        queryfileButton->setObjectName(QStringLiteral("queryfileButton"));
        queryfileButton->setGeometry(QRect(480, 100, 75, 23));
        queryfile_lineEdit = new QLineEdit(tab_7);
        queryfile_lineEdit->setObjectName(QStringLiteral("queryfile_lineEdit"));
        queryfile_lineEdit->setGeometry(QRect(50, 100, 391, 20));
        label_12 = new QLabel(tab_7);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(60, 150, 381, 41));
        tabWidget->addTab(tab_7, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        label_2 = new QLabel(tab_6);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 20, 91, 16));
        textEdit_gmStrCmd = new QTextEdit(tab_6);
        textEdit_gmStrCmd->setObjectName(QStringLiteral("textEdit_gmStrCmd"));
        textEdit_gmStrCmd->setGeometry(QRect(140, 10, 501, 161));
        pushButton_gmStrCmd = new QPushButton(tab_6);
        pushButton_gmStrCmd->setObjectName(QStringLiteral("pushButton_gmStrCmd"));
        pushButton_gmStrCmd->setGeometry(QRect(30, 140, 75, 23));
        tabWidget->addTab(tab_6, QString());

        gridLayout->addWidget(tabWidget, 2, 1, 1, 1);

        gmtoolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(gmtoolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1011, 21));
        gmtoolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(gmtoolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        gmtoolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(gmtoolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        gmtoolClass->setStatusBar(statusBar);

        retranslateUi(gmtoolClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(gmtoolClass);
    } // setupUi

    void retranslateUi(QMainWindow *gmtoolClass)
    {
        gmtoolClass->setWindowTitle(QApplication::translate("gmtoolClass", "gmtool", 0));
        groupBox_12->setTitle(QApplication::translate("gmtoolClass", "\346\234\215\345\212\241\345\231\250\351\200\211\346\213\251", 0));
        loginButton->setText(QApplication::translate("gmtoolClass", "\347\231\273\351\231\206\346\234\215\345\212\241\345\231\250", 0));
        logoutButton->setText(QApplication::translate("gmtoolClass", "\347\231\273\345\207\272\346\234\215\345\212\241\345\231\250", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_SvrList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("gmtoolClass", "\346\234\215\345\212\241\345\231\250\345\210\227\350\241\250", 0));
        groupBox_6->setTitle(QString());
        clearLogButton->setText(QApplication::translate("gmtoolClass", "\346\270\205\347\251\272log", 0));
        exitButton->setText(QApplication::translate("gmtoolClass", "\351\200\200\345\207\272", 0));
        groupBox_4->setTitle(QString());
        queryRoleID->setText(QApplication::translate("gmtoolClass", "\346\237\245\350\257\242\350\247\222\350\211\262ID", 0));
        label_14->setText(QApplication::translate("gmtoolClass", "\350\247\222\350\211\262ID", 0));
        radioButton_query_1->setText(QApplication::translate("gmtoolClass", "\350\247\222\350\211\262\345\220\215", 0));
        radioButton_query_2->setText(QApplication::translate("gmtoolClass", "\350\264\246\345\217\267\345\220\215", 0));
#ifndef QT_NO_TOOLTIP
        lineEdit_query_1->setToolTip(QApplication::translate("gmtoolClass", "\346\224\257\346\214\201\351\203\250\345\210\206\346\250\241\347\263\212\346\237\245\350\257\242", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lineEdit_query_2->setToolTip(QApplication::translate("gmtoolClass", "\346\232\202\344\270\215\346\224\257\346\214\201\346\250\241\347\263\212\346\237\245\350\257\242", 0));
#endif // QT_NO_TOOLTIP
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_queryroleid->headerItem();
        ___qtreewidgetitem1->setText(3, QApplication::translate("gmtoolClass", "\350\264\246\345\217\267\345\220\215", 0));
        ___qtreewidgetitem1->setText(2, QApplication::translate("gmtoolClass", "\350\247\222\350\211\262\345\220\215", 0));
        ___qtreewidgetitem1->setText(1, QApplication::translate("gmtoolClass", "\350\247\222\350\211\262ID", 0));
        ___qtreewidgetitem1->setText(0, QApplication::translate("gmtoolClass", "\345\244\247\345\214\272ID", 0));
        groupBox_9->setTitle(QString());
        radioButton_queryByID->setText(QApplication::translate("gmtoolClass", "\350\247\222\350\211\262\345\220\215", 0));
        radioButton_queryByFile->setText(QApplication::translate("gmtoolClass", "\346\226\207\344\273\266\350\276\223\345\205\245", 0));
#ifndef QT_NO_TOOLTIP
        lineEdit_queryByid->setToolTip(QApplication::translate("gmtoolClass", "<html><head/><body><p>\344\270\215\350\266\205\350\277\20710\344\270\252\350\247\222\350\211\262ID,\347\251\272\346\240\274\345\210\206\351\232\224</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_15->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->headerItem();
        ___qtreewidgetitem2->setText(9, QApplication::translate("gmtoolClass", "\347\255\211\347\272\247", 0));
        ___qtreewidgetitem2->setText(8, QApplication::translate("gmtoolClass", "\350\201\214\344\270\232", 0));
        ___qtreewidgetitem2->setText(7, QApplication::translate("gmtoolClass", "\346\200\247\345\210\253", 0));
        ___qtreewidgetitem2->setText(6, QApplication::translate("gmtoolClass", "\346\234\200\345\220\216\345\233\236\345\206\231\346\225\260\346\215\256\346\227\266\351\227\264", 0));
        ___qtreewidgetitem2->setText(5, QApplication::translate("gmtoolClass", "\346\230\257\345\220\246\345\234\250\347\272\277", 0));
        ___qtreewidgetitem2->setText(4, QApplication::translate("gmtoolClass", "\346\230\257\345\220\246\350\242\253\345\210\240\351\231\244", 0));
        ___qtreewidgetitem2->setText(3, QApplication::translate("gmtoolClass", "\350\247\222\350\211\262\345\220\215", 0));
        ___qtreewidgetitem2->setText(2, QApplication::translate("gmtoolClass", "\350\247\222\350\211\262ID", 0));
        ___qtreewidgetitem2->setText(1, QApplication::translate("gmtoolClass", "\345\214\272\347\273\204", 0));
        ___qtreewidgetitem2->setText(0, QApplication::translate("gmtoolClass", "\345\244\247\345\214\272", 0));
        viewButton->setText(QApplication::translate("gmtoolClass", "\346\237\245\347\234\213\350\247\222\350\211\262\346\225\260\346\215\256", 0));
        toolButton->setText(QApplication::translate("gmtoolClass", "...", 0));
#ifndef QT_NO_TOOLTIP
        lineEdit_queryByFile->setToolTip(QApplication::translate("gmtoolClass", "txt\346\240\274\345\274\217\346\226\207\344\273\266,\347\251\272\346\240\274\345\210\206\351\232\224\350\247\222\350\211\262ID", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        roleGMCmdhButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        roleGMCmdhButton->setText(QApplication::translate("gmtoolClass", "\345\257\271\350\247\222\350\211\262\346\211\247\350\241\214gm\346\214\207\344\273\244", 0));
        query_role_data_button->setText(QApplication::translate("gmtoolClass", "\346\237\245\350\257\242", 0));
        modifyButton->setText(QApplication::translate("gmtoolClass", "\344\277\256\346\224\271\350\247\222\350\211\262\346\225\260\346\215\256", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("gmtoolClass", "\350\247\222\350\211\262\346\223\215\344\275\234", 0));
        groupBox->setTitle(QString());
        radioButton_5->setText(QApplication::translate("gmtoolClass", "\344\273\216\346\226\207\344\273\266\350\276\223\345\205\245", 0));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("gmtoolClass", "txt\346\240\274\345\274\217\346\226\207\344\273\266,\347\251\272\346\240\274\345\210\206\351\232\224\350\247\222\350\211\262ID", 0));
#endif // QT_NO_TOOLTIP
        radioButton_6->setText(QApplication::translate("gmtoolClass", "\350\247\222\350\211\262\345\220\215", 0));
        toolButton_2->setText(QApplication::translate("gmtoolClass", "...", 0));
#ifndef QT_NO_TOOLTIP
        textEdit_RoleID->setToolTip(QApplication::translate("gmtoolClass", "\344\270\215\350\266\205\350\277\20710\344\270\252\350\247\222\350\211\262ID,\347\251\272\346\240\274\345\210\206\351\232\224", 0));
#endif // QT_NO_TOOLTIP
        groupBox_5->setTitle(QString());
        label_17->setText(QApplication::translate("gmtoolClass", "\351\202\256\344\273\266\346\240\207\351\242\230", 0));
        label_18->setText(QApplication::translate("gmtoolClass", "\351\202\256\344\273\266\345\206\205\345\256\271", 0));
        label_19->setText(QApplication::translate("gmtoolClass", "\351\231\204\344\273\266\351\201\223\345\205\267ID", 0));
        label_20->setText(QApplication::translate("gmtoolClass", "\351\231\204\344\273\266\351\201\223\345\205\267\346\225\260\351\207\217", 0));
        mailButton->setText(QApplication::translate("gmtoolClass", "\345\217\221\351\202\256\344\273\266", 0));
        label_11->setText(QApplication::translate("gmtoolClass", "\345\216\237\345\233\240", 0));
        groupBox_3->setTitle(QString());
        forbiddenChatButton->setText(QApplication::translate("gmtoolClass", "\347\246\201\350\250\200", 0));
        unForbiddenChatButton->setText(QApplication::translate("gmtoolClass", "\350\247\243\351\231\244\347\246\201\350\250\200", 0));
        label_4->setText(QApplication::translate("gmtoolClass", "\346\214\201\347\273\255\346\227\266\351\227\264\357\274\232\345\210\206\351\222\237", 0));
        freezeRoleButton->setText(QApplication::translate("gmtoolClass", "\345\260\201\345\217\267", 0));
        unfreezeRoleButton->setText(QApplication::translate("gmtoolClass", "\350\247\243\351\231\244\345\260\201\345\217\267", 0));
        kickRoleButton->setText(QApplication::translate("gmtoolClass", "\345\274\272\345\210\266\344\270\213\347\272\277", 0));
        fc1_radioButton->setText(QString());
        fc2_radioButton->setText(QString());
        label_13->setText(QApplication::translate("gmtoolClass", "  -1\346\230\257\346\260\270\344\271\205\345\260\201\345\217\267", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("gmtoolClass", "\345\260\201\345\217\267\343\200\201\347\246\201\350\250\200\343\200\201\351\202\256\344\273\266", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("gmtoolClass", "\345\205\254\344\274\232\346\223\215\344\275\234", 0));
        groupBox_13->setTitle(QApplication::translate("gmtoolClass", "\345\205\254\345\221\212", 0));
        label->setText(QApplication::translate("gmtoolClass", "\345\205\254\345\221\212\345\206\205\345\256\271", 0));
        label_3->setText(QApplication::translate("gmtoolClass", "\345\274\200\345\247\213\346\227\266\351\227\264", 0));
        label_6->setText(QApplication::translate("gmtoolClass", "\345\276\252\347\216\257\351\227\264\351\232\224\357\274\232\347\247\222", 0));
        label_16->setText(QApplication::translate("gmtoolClass", "\345\276\252\347\216\257\346\254\241\346\225\260", 0));
        annouceButton->setText(QApplication::translate("gmtoolClass", "\345\217\221\345\205\254\345\221\212", 0));
        delAnnounceButton->setText(QApplication::translate("gmtoolClass", "\345\210\240\351\231\244\345\205\254\345\221\212", 0));
        label_5->setText(QApplication::translate("gmtoolClass", "\347\273\204\357\274\232", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = announceWidget->headerItem();
        ___qtreewidgetitem3->setText(3, QApplication::translate("gmtoolClass", "\345\206\205\345\256\271", 0));
        ___qtreewidgetitem3->setText(2, QApplication::translate("gmtoolClass", "\345\211\251\344\275\231\351\207\215\345\244\215\346\254\241\346\225\260", 0));
        ___qtreewidgetitem3->setText(1, QApplication::translate("gmtoolClass", "\351\227\264\351\232\224\346\227\266\351\227\264", 0));
        ___qtreewidgetitem3->setText(0, QApplication::translate("gmtoolClass", "\347\273\204", 0));
        getAnnounceButton->setText(QApplication::translate("gmtoolClass", "\350\216\267\345\217\226\345\267\262\345\217\221\351\200\201\345\205\254\345\221\212", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("gmtoolClass", "\346\264\273\345\212\250\347\233\270\345\205\263,\345\205\254\345\221\212", 0));
        groupBox_7->setTitle(QString());
        groupBox_10->setTitle(QString());
        searchButton_log->setText(QApplication::translate("gmtoolClass", "\346\237\245\350\257\242", 0));
        groupBox_11->setTitle(QString());
        label_8->setText(QApplication::translate("gmtoolClass", "\347\273\223\346\235\237\346\227\266\351\227\264", 0));
        label_7->setText(QApplication::translate("gmtoolClass", "\345\274\200\345\247\213\346\227\266\351\227\264", 0));
        groupBox_14->setTitle(QString());
        label_log_1->setText(QApplication::translate("gmtoolClass", "\345\216\237\350\247\222\350\211\262ID", 0));
        label_log_3->setText(QApplication::translate("gmtoolClass", "\351\201\223\345\205\267\346\265\201\346\260\264\345\217\267", 0));
        label_log_2->setText(QApplication::translate("gmtoolClass", "\351\201\223\345\205\267\347\261\273\345\236\213", 0));
        label_log_6->setText(QApplication::translate("gmtoolClass", "\344\273\273\345\212\241ID", 0));
        label_log_4->setText(QApplication::translate("gmtoolClass", "\347\233\256\346\240\207\350\247\222\350\211\262", 0));
        label_log_5->setText(QApplication::translate("gmtoolClass", "\350\264\247\345\270\201\347\261\273\345\236\213", 0));
        label_log_0->setText(QApplication::translate("gmtoolClass", "\347\233\233\345\244\247\351\200\232\350\241\214\350\257\201", 0));
        label_10->setText(QApplication::translate("gmtoolClass", "\350\276\223\345\207\272\346\226\207\344\273\266\345\220\215", 0));
        lineEdit_log->setText(QApplication::translate("gmtoolClass", "output.txt", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("gmtoolClass", "\346\227\245\345\277\227\346\237\245\350\257\242", 0));
        queryfileButton->setText(QApplication::translate("gmtoolClass", "\346\237\245\350\257\242", 0));
        label_12->setText(QApplication::translate("gmtoolClass", "\350\276\223\345\207\272\346\226\207\344\273\266\345\220\215\344\270\272\357\274\232 nameTOid.txt\346\226\207\344\273\266", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("gmtoolClass", "\346\211\271\351\207\217\346\237\245\350\257\242\350\247\222\350\211\262ID", 0));
        label_2->setText(QApplication::translate("gmtoolClass", "\347\263\273\347\273\237\346\214\207\344\273\244", 0));
        pushButton_gmStrCmd->setText(QApplication::translate("gmtoolClass", "\346\211\247\350\241\214\346\214\207\344\273\244", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("gmtoolClass", "\345\205\266\344\273\226", 0));
    } // retranslateUi

};

namespace Ui {
    class gmtoolClass: public Ui_gmtoolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GMTOOL_H
