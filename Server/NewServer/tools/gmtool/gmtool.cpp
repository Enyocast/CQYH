#include "stdafx.h"
#include "gmtool.h"
#include <QtWidgets//QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include "forbidden_chat.h"
#include "kick_user.h"
#include "mail.h"
#include "move_position.h"
#include "delete_item.h"
#include "view_guild.h"
#include "svr_select.h"
#include "gm_manager.h"
#include "message_handler.h"
#include "session_mgr.h"
#include "server_mgr.h"
#include "tl_config.h"
#include "my_tree_widget_item.h"
#include "svr_tree_widget_item.h"
#include "cmd_manager.h"
#include "base_role.h"
#include "executing.h"
#include "role_info.h"

#include "time_ex.h"
//#include "game_world.h"
#include "view_friend.h"
#include "gm_def.h"
#include "string_ex.h"
#include <time.h>
#include "gm_log.h"
#include "gmtool_def.h"
#include "data_mgr.h"
#include "logic.h"
#include "server_list.h"
#include "gm_version.h"
#include "role_gm_cmd.h"
#include "ld_widget.h"


#define TIME_ONE_HOUR_INDEX     (0)
#define TIME_ONE_DAY_INDEX     (1)
#define TIME_THREE_DAY_INDEX     (2)
#define TIME_SEVEN_DAY_INDEX     (3)
#define TIME_FOREVER_INDEX     (4)


QApplication app(__argc, __argv);
gmtool g_gmtool;


gmtool::gmtool(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    // initialize

    m_pLDWidget = NULL;
    memset(m_arrItemPoint, 0, sizeof(m_arrItemPoint));

    //ui.comboBox->insertItem(ROLE_SEARCH_NONE, " ");
    //ui.comboBox->insertItem(ROLE_SEARCH_BY_NAME, QString::fromLocal8Bit(cszUserSearchTypeName));
    //ui.comboBox->insertItem(ROLE_SEARCH_BY_ID, QString::fromLocal8Bit(cszUserSearchTypeID));
    //ui.comboBox->addItem(QString::fromLocal8Bit(cszUserSearchTypeAccount));

    ui.treeWidget->setColumnWidth(0, 55);
    ui.treeWidget->setColumnWidth(1, 55);
    ui.treeWidget->setColumnWidth(2, 60);
    ui.treeWidget->setColumnWidth(3, 100);
    ui.treeWidget->setColumnWidth(4, 80);
    ui.treeWidget->setColumnWidth(5, 80);
    ui.treeWidget->setColumnWidth(6, 130);
    ui.treeWidget->setColumnWidth(7, 40);
    ui.treeWidget->setColumnWidth(8, 60);
    ui.treeWidget->setColumnWidth(9, 40);

    connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui.clearLogButton, SIGNAL(clicked()), this, SLOT(ClearLog()));
    connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(Login()));
    connect(ui.logoutButton, SIGNAL(clicked()), this, SLOT(Logout()));
    connect(ui.tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(SecondInit(int)));
    //connect(ui.treeWidget_SvrList, SIGNAL(itemChanged(QTreeWidgetItem * item, int column)), this, SLOT(UpdateSelectedServer(QTreeWidgetItem * item, int column)));

    
    // tag 1
    connect(ui.radioButton_query_1, SIGNAL(clicked()), this, SLOT(SetFocusRoleName()));
    connect(ui.radioButton_query_2, SIGNAL(clicked()), this, SLOT(SetFocusUserName()));
    connect(ui.radioButton_queryByID, SIGNAL(clicked()), this, SLOT(SetFocusRoleIDByEdit()));
    connect(ui.radioButton_queryByFile, SIGNAL(clicked()), this, SLOT(SetFocusRoleIDByFile()));

    connect(ui.queryRoleID, SIGNAL(clicked()), this, SLOT(QueryRoleID()));
    connect(ui.query_role_data_button, SIGNAL(clicked()), this, SLOT(QueryRoleData()));
    connect(ui.viewButton, SIGNAL(clicked()), this, SLOT(ViewRoleData()));
    connect(ui.modifyButton, SIGNAL(clicked()), this, SLOT(ModifyRoleData()));
    connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(ui.roleGMCmdhButton, SIGNAL(clicked()), this, SLOT(RoleGMCmd()));

    m_pQueryIDRadioGroup = new QButtonGroup;
    m_pQueryIDRadioGroup->addButton(ui.radioButton_query_1, GM_QUERY_BY_ROLE_NAME);
    m_pQueryIDRadioGroup->addButton(ui.radioButton_query_2, GM_QUERY_BY_USER_NAME);

    m_pQueryRoleRadioGroup = new QButtonGroup;
    m_pQueryRoleRadioGroup->addButton(ui.radioButton_queryByID, 1);
    m_pQueryRoleRadioGroup->addButton(ui.radioButton_queryByFile, 2);



    // tag 2
    connect(ui.radioButton_6, SIGNAL(clicked()), this, SLOT(SetFocusRoleIDByEdit2()));
    connect(ui.radioButton_5, SIGNAL(clicked()), this, SLOT(SetFocusRoleIDByFile2()));
    connect(ui.fc1_radioButton, SIGNAL(clicked()), this, SLOT(SetFocusForbidChat()));

    connect(ui.forbiddenChatButton, SIGNAL(clicked()), this, SLOT(ForBiddenChat()));
    connect(ui.unForbiddenChatButton, SIGNAL(clicked()), this, SLOT(UnforbidChat()));
    connect(ui.freezeRoleButton, SIGNAL(clicked()), this, SLOT(FreezeRole()));
    connect(ui.unfreezeRoleButton, SIGNAL(clicked()), this, SLOT(UnfreezeRole()));
    connect(ui.kickRoleButton, SIGNAL(clicked()), this, SLOT(KickRole()));
    connect(ui.mailButton, SIGNAL(clicked()), this, SLOT(Mail()));
    connect(ui.toolButton_2, SIGNAL(clicked()), this, SLOT(OpenFile_2()));
    m_pRadioGroup = new QButtonGroup;
    m_pRadioGroup->addButton(ui.radioButton_5, 1);
    m_pRadioGroup->addButton(ui.radioButton_6, 2);

    m_pFCRadioGroup = new QButtonGroup;
    m_pFCRadioGroup->addButton(ui.fc1_radioButton, 1);
    m_pFCRadioGroup->addButton(ui.fc2_radioButton, 2);

    ui.fc1_comboBox->clear();
    ui.fc1_comboBox->insertItem(TIME_ONE_HOUR_INDEX, QString::fromLocal8Bit("1小时"));
    ui.fc1_comboBox->insertItem(TIME_ONE_DAY_INDEX, QString::fromLocal8Bit("1天"));
    ui.fc1_comboBox->insertItem(TIME_THREE_DAY_INDEX, QString::fromLocal8Bit("3天"));
    ui.fc1_comboBox->insertItem(TIME_SEVEN_DAY_INDEX, QString::fromLocal8Bit("7天"));
    ui.fc1_comboBox->insertItem(TIME_FOREVER_INDEX, QString::fromLocal8Bit("永久"));


    // tag 4
    connect(ui.comboBox, SIGNAL(clicked()), this, SLOT(SelectGroup()));
    connect(ui.annouceButton, SIGNAL(clicked()), this, SLOT(AnnounceFunc()));
    connect(ui.getAnnounceButton, SIGNAL(clicked()), this, SLOT(GetAnnounceList()));
    connect(ui.delAnnounceButton, SIGNAL(clicked()), this, SLOT(DelAnnounce()));

    QDateTime   qDataTime;
    qDataTime.setTime_t(time(NULL));
    ui.dateTimeEdit_announce->setDateTime(qDataTime);

    //connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(SelectSvrWithCheckBox()));
    //connect(ui.comboBox, SIGNAL(activated(const QString &)), this, SLOT(SearchRoleType(const QString &)));
    

    // tag 5

    ui.dateTimeEdit_log_1->setDateTime(qDataTime);
    ui.dateTimeEdit_log_2->setDateTime(qDataTime);

    ui.logComboBox->clear();
    ui.logComboBox->insertItem(GM_LOG_QUERY_ROLE_LOGIN, QString::fromLocal8Bit("账号登入登出"));
    ui.logComboBox->insertItem(GM_LOG_QUERY_ROLE_LOGOUT, QString::fromLocal8Bit("角色登出"));
    ui.logComboBox->insertItem(GM_LOG_QUERY_ITEM, QString::fromLocal8Bit("道具流转"));
    ui.logComboBox->insertItem(GM_LOG_QUERY_MONEY, QString::fromLocal8Bit("货币流转"));
    ui.logComboBox->insertItem(GM_LOG_QUERY_QUEST, QString::fromLocal8Bit("角色任务"));
    ui.logComboBox->insertItem(GM_LOG_QUERY_GM, QString::fromLocal8Bit("gm指令日志"));

    connect(ui.logComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeInputType(int)));
    connect(ui.searchButton_log, SIGNAL(clicked()), this, SLOT(LogSearch()));

    ui.lineEdit_log->setDisabled(true);
    _DisableTag5();

    ChangeInputType(ui.logComboBox->currentIndex());

    // tag 6
    connect(ui.queryfileButton, SIGNAL(clicked()), this, SLOT(QueryNameToID()));

    // tag 7
    connect(ui.pushButton_gmStrCmd, SIGNAL(clicked()), this, SLOT(SendGMStrCmd()));


    

    startTimer(125);

}

gmtool::~gmtool()
{

}

void gmtool::timerEvent(QTimerEvent* event)
{
    INT32       nRetCode = 0;

    nRetCode = CGMManager::GetInstance().MainLoop();
    if (!nRetCode)
    {
        nRetCode = CGMManager::GetInstance().UnInit();
        LOG_CHECK_ERROR(nRetCode);
        QMessageBox::critical(this, "critical", "Application error, will exit!", QMessageBox::Yes);
        close();
    }

    if (m_pLDWidget)
        m_pLDWidget->MainLoop();

}


void gmtool::Ok()
{

}

void gmtool::Execute()
{

}

void gmtool::Exit()
{
    close();
}

void gmtool::ClearLog()
{
    ui.textBrowser->clear();
}


void gmtool::Login()
{
    INT32       nRetCode = 0;
    GM_SESSION  *pGMSession = NULL;

    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; ++nIndex)
    {
        if (m_arrItemPoint[nIndex])
        {
            Qt::CheckState state = m_arrItemPoint[nIndex]->checkState(0);
            if (state == Qt::Checked)
            {
                pGMSession = CSessionMgr::GetInstance().GetGMSession(m_arrItemPoint[nIndex]->GetSessionID());
                LOG_PROCESS_ERROR(pGMSession);

                nRetCode = CMessageHandler::GetInstance().DoLoginToGM(m_arrItemPoint[nIndex]->GetSessionID(), CGMManager::GetInstance().GetUserName(), CGMManager::GetInstance().GetUserPwd());
                if (nRetCode == FALSE)
                {
                    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("未链接上服务器，无法登陆"), QMessageBox::Yes);
                    return;
                }

                nRetCode = CGMLog::GetInstance().Log("登陆服务器[%s]....", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
                LOG_PROCESS_ERROR(nRetCode);
                break;      // 每次只处理一个server Allan Tao[5.3.2014] 
            }
        }
    }

    return ;
Exit0:
    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("登陆失败，请稍后重试或联系开发人员"), QMessageBox::Yes);
    return;
}

void gmtool::Logout()
{
    INT32           nRetCode = 0;
    GM_SESSION      *pGMSession = NULL;

    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; ++nIndex)
    {
        if (m_arrItemPoint[nIndex])
        {
            Qt::CheckState state = m_arrItemPoint[nIndex]->checkState(0);
            if (state == Qt::Checked)
            {
                pGMSession = CSessionMgr::GetInstance().GetGMSession(m_arrItemPoint[nIndex]->GetSessionID());
                LOG_PROCESS_ERROR(pGMSession);

                CDataMgr::GetInstance().ClearItemMap(nIndex);

                nRetCode = CMessageHandler::GetInstance().DoLogoutToGM(m_arrItemPoint[nIndex]->GetSessionID());
                if (nRetCode == FALSE)
                {
                    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("未链接上服务器，无法登陆"), QMessageBox::Yes);
                    return;
                }

                nRetCode = CGMLog::GetInstance().Log("登出服务器[%s]....", QString::fromUtf8(pGMSession->szGMName).toLocal8Bit().data());
                LOG_PROCESS_ERROR(nRetCode);

                break;      // 每次只处理一个server Allan Tao[5.3.2014] 
            }
        }
    }

    return ;
Exit0:
    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("登陆失败，请稍后重试或联系开发人员"), QMessageBox::Yes);
    return;
}

void gmtool::SecondInit(int nIndex)
{
    INT32       nRetCode = 0;
    ITEM_TEMPLATE_DATA  *pTemplate = NULL;
    // index 0 - n
    if (nIndex == 1)
    {
        UINT32 dwSessionID = 0;

        INF("second init begin");
        for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; ++nIndex)
        {
            nRetCode = IsServerSelected(nIndex);
            if (nRetCode == TRUE)
            {
                dwSessionID = nIndex;
                break;
            }
        }
        if (MAX_GM_SESSION_COUNT == dwSessionID)
        {
            //QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择执行区服"), QMessageBox::Yes);
            return;
        }

        INF("second init begin item map");
        ui.mailItem_comboBox->clear();
        INT32 i = 1;
        CDataMgr::GetInstance().ItemMapBegin(dwSessionID);
        while (pTemplate = CDataMgr::GetInstance().ItemMapNext(dwSessionID))
        {
            QString     str;
            
            str.append(pTemplate->szName);

            str.append(" - ");
            
            char        szNum[64] = { 0 };
            gm_itoa(pTemplate->dwTempID, szNum);

            str.append(szNum);

            //str.setNum(pTemplate->dwTempID, 10);

            ui.mailItem_comboBox->insertItem(i, str);
            ++i;
        }
        INF("second init item map end i[%d]", i);
    }
    else if ( nIndex == 3 )
    {
        // tag 4
        QDateTime   qDataTime;
        qDataTime.setTime_t(time(NULL));
        ui.dateTimeEdit_announce->setDateTime(qDataTime);

        ui.announceWidget->clear();
    }
    else if (nIndex == 4)
    {
        QDateTime   qDataTime;
        qDataTime.setTime_t(time(NULL));
        ui.dateTimeEdit_log_1->setDateTime(qDataTime);
        ui.dateTimeEdit_log_2->setDateTime(qDataTime);

        INT32   nComboIndex = ui.logComboBox->currentIndex();
        ChangeInputType(nComboIndex);
    }
Exit0:
    return;
}

void gmtool::UpdateSelectedServer(QTreeWidgetItem * item, int column)
{
    INT32       nRetCode = 0;
    nRetCode = CServerMgr::GetInstance().UpdateSelectServer();
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

//void gmtool::SearchRoleType(const QString & selectItemText)
//{
//    //if (selectItemText == QString::fromLocal8Bit(cszUserSearchTypeName))
//    //{
//    //    ui.label_2->setText(QString::fromLocal8Bit(cszUserSearchTypeName));
//    //    ui.label_2->show();
//    //    ui.lineEdit->show();
//    //}
//    //else if (selectItemText == QString::fromLocal8Bit(cszUserSearchTypeID))
//    //{
//    //    ui.label_2->setText(QString::fromLocal8Bit(cszUserSearchTypeID));
//    //    ui.label_2->show();
//    //    ui.lineEdit->show();
//    //}
//    //else if (selectItemText == QString::fromLocal8Bit(cszUserSearchTypeAccount))
//    //{
//    //    ui.label_2->setText(QString::fromLocal8Bit(cszUserSearchTypeAccount));
//    //    ui.label_2->show();
//    //    ui.lineEdit->show();
//    //}
//    //else
//    //{
//    //    DisableAllInputWidget();
//    //}
//    //ui.lineEdit->clear();
//    
//}

void gmtool::SetFocusRoleName()
{
    ui.lineEdit_query_1->setFocus();
}

void gmtool::SetFocusUserName()
{
    ui.lineEdit_query_2->setFocus();
}

void gmtool::SetFocusRoleIDByEdit()
{
    ui.lineEdit_queryByid->setFocus();
}

void gmtool::SetFocusRoleIDByFile()
{
    ui.lineEdit_queryByFile->setFocus();
}

void gmtool::QueryRoleID()
{
    INT32       nRetCode = 0;
    INT32       nSelectRadioID = -1;
    char        szName[128] = { 0 };

    ui.treeWidget_queryroleid->clear();

    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsServerSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择执行区服"), QMessageBox::Yes);
        return;
    }

    if (-1 == m_pQueryIDRadioGroup->checkedId())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择要查询的日志"), QMessageBox::Yes);
        return;
    }

    nSelectRadioID = m_pQueryIDRadioGroup->checkedId();
    if (nSelectRadioID == GM_QUERY_BY_ROLE_NAME)
        strxcpy(szName, ui.lineEdit_query_1->text().toUtf8(), sizeof(szName));
    else if (nSelectRadioID == GM_QUERY_BY_USER_NAME)
        strxcpy(szName, ui.lineEdit_query_2->text().toUtf8(), sizeof(szName));
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择查询类型"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    if (0 == strlen(szName))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请输入正确的名字"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    nRetCode = CCmdManager::GetInstance().QueryRoleID(nSelectRadioID, szName);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    return;
Exit0:
    return;
}

void gmtool::QueryRoleData()
{
    INT32       nRetCode = 0;
    char        szRoleName[ROLE_NAME_LEN] = { 0 };
    GM_SESSION  *pGMSession = NULL;
    CMD_BASE    *pCmd = NULL;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    if (ui.radioButton_queryByID->isChecked())
    {
        if (ui.lineEdit_queryByid->text().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请正确填写角色名"), QMessageBox::Yes);
            return;
        }

        strxcpy(szRoleName, ui.lineEdit_queryByid->text().toUtf8(), ROLE_NAME_LEN);

        ui.treeWidget->clear();
        CDataMgr::GetInstance().ClearRole();

        pCmd = CCmdManager::GetInstance().NewCmd(CMD_QUERY_ROLE_DATA);
        LOG_PROCESS_ERROR(pCmd);

        pCmd->nType = CMD_QUERY_ROLE_DATA;
        pCmd->nSvrNum = 0;
        strxcpy(((QUERY_ROLE_DATA*)pCmd)->szRoleName, szRoleName, ROLE_NAME_LEN);
        ((QUERY_ROLE_DATA*)pCmd)->dwRoleID = 0;

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_QUERY_ROLE_DATA, szRoleName, pCmd);
        LOG_CHECK_ERROR(nRetCode);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }

    }
    else if (ui.radioButton_queryByFile->isChecked())
    {
        //nRetCode = _ReadRoleIDFromFile(ui.lineEdit_queryByFile->text().toUtf8(), roleIDList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        return;
    }

    return;
Exit0:
    return;
}

void gmtool::ViewRoleData()
{
    INT32       nRetCode = 0;
    GM_SESSION  *pGMSession = NULL;

    nRetCode = CCmdManager::GetInstance().IsCmdExecuting();
    if (nRetCode)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    CMyTreeWidgetItem * pItem = (CMyTreeWidgetItem*)ui.treeWidget->currentItem();
    if (pItem)
    {
        CRoleInfo   *pRoleInfo = new CRoleInfo(0, pItem->GetID());
        pRoleInfo->show();
    }

    return;
Exit0:
    return;
}

void gmtool::ModifyRoleData()
{
    INT32       nRetCode = 0;
    typedef std::list<UINT32>   ROLEID_LIST;
    ROLEID_LIST roleIDList;
    UINT32      dwRoleID = 0;
    char        szRoleName[ROLE_NAME_LEN] = { 0 };

    nRetCode = CCmdManager::GetInstance().IsCmdExecuting();
    if (nRetCode)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    // clear role cache
    ui.treeWidget->clear();

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("请确认角色处于离线状态！否则将导致玩家数据不一致"));
    if (nCheckEnum == QMessageBox::Yes)
    {
        if (ui.radioButton_queryByID->isChecked())
        {
            if (ui.lineEdit_queryByid->text().toUtf8().length() <= 0)
            {
                QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
                return;
            }

            strxcpy(szRoleName, ui.lineEdit_queryByid->text().toUtf8(), ROLE_NAME_LEN);

            LOAD_ROLE_DATA *pCmd = (LOAD_ROLE_DATA*)CCmdManager::GetInstance().NewCmd(CMD_LOAD_ROLE_DATA);
            LOG_PROCESS_ERROR(pCmd);

            pCmd->nType = CMD_LOAD_ROLE_DATA;
            pCmd->nSvrNum = 0;
            strxcpy(((LOAD_ROLE_DATA*)pCmd)->szRoleName, szRoleName, ROLE_NAME_LEN);
            ((LOAD_ROLE_DATA*)pCmd)->dwRoleID = 0;

            nRetCode = CCmdManager::GetInstance().PreQuery(CMD_LOAD_ROLE_DATA, szRoleName, pCmd);
            LOG_CHECK_ERROR(nRetCode);
            if (nRetCode == FALSE)
            {
                QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
                LOG_PROCESS_ERROR(FALSE);
            }
        }
        else if (ui.radioButton_queryByFile->isChecked())
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("角色ID 数量过多"), QMessageBox::Yes);
            return;
        }
        else
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入类型"), QMessageBox::Yes);
            return;
        }
    }
    else
    {
        return;
    }

    return;
Exit0:
    return;
}

void gmtool::OpenFile()
{
    ui.lineEdit_queryByFile->clear();
    QFileDialog *pFileDialog = new QFileDialog(this);
    if (pFileDialog == NULL)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("打开文件对话框失败"), QMessageBox::Yes);
        return;
    }

    pFileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件"));
    pFileDialog->setDirectory(".");
    if (pFileDialog->exec() == QDialog::Accepted)
    {
        QString path = pFileDialog->selectedFiles()[0];
        ui.lineEdit_queryByFile->setText(path);
    }
    else
    {
        QMessageBox::information(this, "critical", QString::fromLocal8Bit("未选择文件"), QMessageBox::Yes);
        return;
    }

    delete pFileDialog;
}

void gmtool::RoleGMCmd()
{
    INT32       nRetCode = 0;
    typedef std::list<UINT32>   ROLEID_LIST;
    ROLEID_LIST roleIDList;
    UINT32      dwRoleID = 0;
    char        szRoleName[ROLE_NAME_LEN] = { 0 };

    nRetCode = CCmdManager::GetInstance().IsCmdExecuting();
    if (nRetCode)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    if (ui.radioButton_queryByID->isChecked())
    {
        if (ui.lineEdit_queryByid->text().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        strxcpy(szRoleName, ui.lineEdit_queryByid->text().toUtf8(), ROLE_NAME_LEN);
    }
    else if (ui.radioButton_queryByFile->isChecked())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("角色ID 数量过多"), QMessageBox::Yes);
        return;
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入类型"), QMessageBox::Yes);
        return;
    }

    CRoleGMCmd      exe;
    exe.exec();

    if (exe.IsExeCmd())
    {
        EXE_ROLE_CMD *pCmd = (EXE_ROLE_CMD*)CCmdManager::GetInstance().NewCmd(CMD_EXE_ROLE_GM_CMD);
        LOG_PROCESS_ERROR(pCmd);

        pCmd->nType = CMD_EXE_ROLE_GM_CMD;
        pCmd->nSvrNum = 0;
        strxcpy(((EXE_ROLE_CMD*)pCmd)->szRoleName, szRoleName, ROLE_NAME_LEN);
        strxcpy(((EXE_ROLE_CMD*)pCmd)->szReason, exe.GetReason(), 2048);
        strxcpy(((EXE_ROLE_CMD*)pCmd)->szGM, exe.GetBuffer(), MAX_GM_COMMAND_LEN);
        ((EXE_ROLE_CMD*)pCmd)->dwRoleID = 0;

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_EXE_ROLE_GM_CMD, szRoleName, pCmd);
        LOG_CHECK_ERROR(nRetCode);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }

Exit0:
    return;
}


// tag 2
void gmtool::SetFocusRoleIDByEdit2()
{
    ui.textEdit_RoleID->setFocus();
}

void gmtool::SetFocusRoleIDByFile2()
{
    ui.lineEdit->setFocus();
}

void gmtool::SetFocusForbidChat()
{
    ui.fc1_comboBox->showPopup();
}



void gmtool::ForBiddenChat()
{
    INT32       nRetCode = 0;
    INT32       nIndex = 0;
    INT64       llTime = 0;
    ROLE_RESULT     roleres;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认禁言？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    if (ui.fc1_radioButton->isChecked())
    {
        nIndex = ui.fc1_comboBox->currentIndex();
        if (nIndex == TIME_ONE_HOUR_INDEX)
            llTime = 3600;
        else if (nIndex == TIME_ONE_DAY_INDEX)
            llTime = 86400;
        else if (nIndex == TIME_THREE_DAY_INDEX)
            llTime = 86400 * 3;
        else if (nIndex == TIME_SEVEN_DAY_INDEX)
            llTime = 86400 * 7;
        else if (nIndex == TIME_FOREVER_INDEX)
            llTime = FOREVER_TIME;
        else
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("输入错误"), QMessageBox::Yes);
            return;
        }
    }
    else if (ui.fc2_radioButton->isCheckable())
    {
        llTime = ui.forbiddenChatTimeEdit->text().toLong();
        if (llTime == -1)
            llTime = FOREVER_TIME;
        else if (llTime == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("参数错误"), QMessageBox::Yes);
            return;
        }
        else
        {
            llTime *= 60;
            if (llTime > 1000000000)
                llTime = FOREVER_TIME;
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择禁言时间"), QMessageBox::Yes);
        return;
    }

    FORBIDDEN_CHAT *pCmd = (FORBIDDEN_CHAT*)CCmdManager::GetInstance().NewCmd(CMD_FORBIDDEN_CHAT);
    LOG_PROCESS_ERROR(pCmd);

    pCmd->nType = CMD_FORBIDDEN_CHAT;
    pCmd->nSvrNum = 0;
    pCmd->llTime = llTime;
    pCmd->roleList.clear();
    pCmd->roleResList.clear();
    memset(pCmd->szFileName, 0, sizeof(pCmd->szFileName));

    if (ui.radioButton_6->isChecked())
    {
        if (ui.textEdit_RoleID->toPlainText().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        roleres.dwRoleID = 0;
        roleres.nResult = errUnknownError;
        strxcpy(roleres.szRoleName, ui.textEdit_RoleID->toPlainText().toUtf8(), ROLE_NAME_LEN);
        pCmd->roleList.push_back(roleres);

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FORBIDDEN_CHAT, roleres.szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else if (ui.radioButton_queryByFile->isCheckable())
    {
        strxcpy(pCmd->szFileName, ui.lineEdit->text().toUtf8(), sizeof(pCmd->szFileName));

        nRetCode = _ReadRoleFromFile(pCmd->szFileName, pCmd->roleList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        if (pCmd->roleList.size() == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("有效角色名数量为0"), QMessageBox::Yes);
            return;
        }

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FORBIDDEN_CHAT, pCmd->roleList.begin()->szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入方式"), QMessageBox::Yes);
        return;
    }

    return ;
Exit0:
    return;
}

void gmtool::UnforbidChat()
{
    INT32       nRetCode = 0;
    ROLE_RESULT     roleres;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认解除禁言？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    FORBIDDEN_CHAT *pCmd = (FORBIDDEN_CHAT*)CCmdManager::GetInstance().NewCmd(CMD_FORBIDDEN_CHAT);
    LOG_PROCESS_ERROR(pCmd);

    pCmd->nType = CMD_FORBIDDEN_CHAT;
    pCmd->nSvrNum = 0;
    pCmd->llTime = 0;
    pCmd->roleList.clear();
    pCmd->roleResList.clear();
    memset(pCmd->szFileName, 0, sizeof(pCmd->szFileName));

    if (ui.radioButton_6->isChecked())
    {
        if (ui.textEdit_RoleID->toPlainText().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        roleres.dwRoleID = 0;
        roleres.nResult = errUnknownError;
        strxcpy(roleres.szRoleName, ui.textEdit_RoleID->toPlainText().toUtf8(), ROLE_NAME_LEN);
        pCmd->roleList.push_back(roleres);

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FORBIDDEN_CHAT, roleres.szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else if (ui.radioButton_queryByFile->isCheckable())
    {
        strxcpy(pCmd->szFileName, ui.lineEdit->text().toUtf8(), sizeof(pCmd->szFileName));

        nRetCode = _ReadRoleFromFile(pCmd->szFileName, pCmd->roleList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        if (pCmd->roleList.size() == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("有效角色名数量为0"), QMessageBox::Yes);
            return;
        }

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FORBIDDEN_CHAT, pCmd->roleList.begin()->szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入方式"), QMessageBox::Yes);
        return;
    }

    return;
Exit0:
    return;
}


void gmtool::FreezeRole()
{
    INT32       nRetCode = 0;
    INT64       llTime = 0;
    INT32       nIndex = 0;
    ROLE_RESULT     roleres;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认封号？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    if (ui.fc1_radioButton->isChecked())
    {
        nIndex = ui.fc1_comboBox->currentIndex();
        if (nIndex == TIME_ONE_HOUR_INDEX)
            llTime = 3600;
        else if (nIndex == TIME_ONE_DAY_INDEX)
            llTime = 86400;
        else if (nIndex == TIME_THREE_DAY_INDEX)
            llTime = 86400 * 3;
        else if (nIndex == TIME_SEVEN_DAY_INDEX)
            llTime = 86400 * 7;
        else if (nIndex == TIME_FOREVER_INDEX)
            llTime = FOREVER_TIME;
        else
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("输入错误"), QMessageBox::Yes);
            return;
        }
    }
    else if (ui.fc2_radioButton->isChecked())
    {
        llTime = ui.forbiddenChatTimeEdit->text().toLong();
        if (llTime == -1)
            llTime = FOREVER_TIME;
        else
        {
            llTime *= 60;
            if (llTime > 1000000000)
                llTime = FOREVER_TIME;
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择冻结时间"), QMessageBox::Yes);
        return;
    }


    FREEZE_ROLE *pCmd = (FREEZE_ROLE*)CCmdManager::GetInstance().NewCmd(CMD_FREEZE_ROLE);
    LOG_PROCESS_ERROR(pCmd);

    pCmd->nType = CMD_FREEZE_ROLE;
    pCmd->nSvrNum = 0;
    pCmd->llTime = llTime;
    pCmd->roleList.clear();
    pCmd->roleResList.clear();
    memset(pCmd->szFileName, 0, sizeof(pCmd->szFileName));

    if (ui.radioButton_6->isChecked())
    {
        if (ui.textEdit_RoleID->toPlainText().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        roleres.dwRoleID = 0;
        roleres.nResult = errUnknownError;
        strxcpy(roleres.szRoleName, ui.textEdit_RoleID->toPlainText().toUtf8(), ROLE_NAME_LEN);
        pCmd->roleList.push_back(roleres);

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FREEZE_ROLE, roleres.szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else if (ui.radioButton_queryByFile->isCheckable())
    {
        strxcpy(pCmd->szFileName, ui.lineEdit->text().toUtf8(), sizeof(pCmd->szFileName));

        nRetCode = _ReadRoleFromFile(pCmd->szFileName, pCmd->roleList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        if (pCmd->roleList.size() == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("有效角色名数量为0"), QMessageBox::Yes);
            return;
        }

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FREEZE_ROLE, pCmd->roleList.begin()->szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入方式"), QMessageBox::Yes);
        return;
    }

    return;
Exit0:
    return;
}

void gmtool::UnfreezeRole()
{
    INT32       nRetCode = 0;
    ROLE_RESULT     roleres;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认解除封号？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    FREEZE_ROLE *pCmd = (FREEZE_ROLE*)CCmdManager::GetInstance().NewCmd(CMD_FREEZE_ROLE);
    LOG_PROCESS_ERROR(pCmd);

    pCmd->nType = CMD_FREEZE_ROLE;
    pCmd->nSvrNum = 0;
    pCmd->llTime = 0;
    pCmd->roleList.clear();
    pCmd->roleResList.clear();
    memset(pCmd->szFileName, 0, sizeof(pCmd->szFileName));

    if (ui.radioButton_6->isChecked())
    {
        if (ui.textEdit_RoleID->toPlainText().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        roleres.dwRoleID = 0;
        roleres.nResult = errUnknownError;
        strxcpy(roleres.szRoleName, ui.textEdit_RoleID->toPlainText().toUtf8(), ROLE_NAME_LEN);
        pCmd->roleList.push_back(roleres);

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FREEZE_ROLE, roleres.szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else if (ui.radioButton_queryByFile->isCheckable())
    {
        strxcpy(pCmd->szFileName, ui.lineEdit->text().toUtf8(), sizeof(pCmd->szFileName));

        nRetCode = _ReadRoleFromFile(pCmd->szFileName, pCmd->roleList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        if (pCmd->roleList.size() == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("有效角色名数量为0"), QMessageBox::Yes);
            return;
        }

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_FREEZE_ROLE, pCmd->roleList.begin()->szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入方式"), QMessageBox::Yes);
        return;
    }

    return;
Exit0:
    return;
}

void gmtool::KickRole()
{
    INT32       nRetCode = 0;
    ROLE_RESULT     roleres;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认强制角色下线？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    KICK_ROLE *pCmd = (KICK_ROLE*)CCmdManager::GetInstance().NewCmd(CMD_KICK_ROLE);
    LOG_PROCESS_ERROR(pCmd);

    pCmd->nType = CMD_KICK_ROLE;
    pCmd->nSvrNum = 0;
    pCmd->roleList.clear();
    pCmd->roleResList.clear();
    memset(pCmd->szFileName, 0, sizeof(pCmd->szFileName));

    if (ui.radioButton_6->isChecked())
    {
        if (ui.textEdit_RoleID->toPlainText().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        roleres.dwRoleID = 0;
        roleres.nResult = errUnknownError;
        strxcpy(roleres.szRoleName, ui.textEdit_RoleID->toPlainText().toUtf8(), ROLE_NAME_LEN);
        pCmd->roleList.push_back(roleres);

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_KICK_ROLE, roleres.szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else if (ui.radioButton_queryByFile->isCheckable())
    {
        strxcpy(pCmd->szFileName, ui.lineEdit->text().toUtf8(), sizeof(pCmd->szFileName));

        nRetCode = _ReadRoleFromFile(pCmd->szFileName, pCmd->roleList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        if (pCmd->roleList.size() == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("有效角色名数量为0"), QMessageBox::Yes);
            return;
        }

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_KICK_ROLE, pCmd->roleList.begin()->szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入方式"), QMessageBox::Yes);
        return;
    }
    return;
Exit0:
    return;
}

void gmtool::Mail()
{
    INT32       nRetCode = 0;
    ROLE_RESULT     roleres;
    BOOL        bParam = FALSE;
    char    szTitle[MAIL_SUBJECT_LEN] = { 0 };
    char    szContent[MAIL_CONTENT_LEN] = { 0 };
    char    szReason[COMMON_NAME_LEN] = { 0 };
    UINT32  dwItemID = 0;
    INT32   nItemNum = 0;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认发送邮件？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    dwItemID = ui.lineEdit_mail_2->text().toULong();
    nItemNum = ui.lineEdit_mail_3->text().toLong();
    strxcpy(szTitle, ui.lineEdit_mail_1->text().toUtf8(), sizeof(szTitle));
    strxcpy(szContent, ui.textEdit_mail->toPlainText().toUtf8(), sizeof(szContent));
    strxcpy(szReason, ui.mailReasonEdit->toPlainText().toUtf8(), sizeof(szReason));

    if (dwItemID > 0 && nItemNum > 0)
        bParam = TRUE;
    if (dwItemID == 0 && nItemNum == 0)
        bParam = TRUE;
    if (0 == strlen(szTitle) || 0 == strlen(szContent))
        bParam = TRUE;

    if (bParam == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请输入正确的参数"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    if (dwItemID > 0 && strlen(szReason) <= 0)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请输入原因"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    if (strlen(szReason) > GM_REASON_LEN - 1)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("原因过长!"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    //////////////////////////////////////////////////////////////////////////
    SEND_MAIL *pCmd = (SEND_MAIL*)CCmdManager::GetInstance().NewCmd(CMD_SEND_MAIL);
    LOG_PROCESS_ERROR(pCmd);

    pCmd->nType = CMD_SEND_MAIL;
    pCmd->nSvrNum = 0;
    pCmd->dwItemID = dwItemID;
    pCmd->nItemNum = nItemNum;
    strxcpy(pCmd->szTitle, szTitle, sizeof(pCmd->szTitle));
    strxcpy(pCmd->szContent, szContent, sizeof(pCmd->szContent));
    memset(pCmd->szReason, 0, sizeof(pCmd->szReason));
    strxcpy(pCmd->szReason, szReason, sizeof(pCmd->szReason));
    pCmd->roleList.clear();
    pCmd->roleResList.clear();

    if (ui.radioButton_6->isChecked())
    {
        if (ui.textEdit_RoleID->toPlainText().toUtf8().length() <= 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写角色名"), QMessageBox::Yes);
            return;
        }

        roleres.dwRoleID = 0;
        roleres.nResult = errUnknownError;
        strxcpy(roleres.szRoleName, ui.textEdit_RoleID->toPlainText().toUtf8(), ROLE_NAME_LEN);
        pCmd->roleList.push_back(roleres);

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_SEND_MAIL, roleres.szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else if (ui.radioButton_queryByFile->isCheckable())
    {
        strxcpy(pCmd->szFileName, ui.lineEdit->text().toUtf8(), sizeof(pCmd->szFileName));

        nRetCode = _ReadRoleFromFile(pCmd->szFileName, pCmd->roleList);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色ID文件失败"), QMessageBox::Yes);
            return;
        }

        if (pCmd->roleList.size() == 0)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("有效角色名数量为0"), QMessageBox::Yes);
            return;
        }

        nRetCode = CCmdManager::GetInstance().PreQuery(CMD_SEND_MAIL, pCmd->roleList.begin()->szRoleName, pCmd);
        if (nRetCode == FALSE)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
            LOG_PROCESS_ERROR(FALSE);
        }
    }
    else
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择角色ID输入方式"), QMessageBox::Yes);
        return;
    }

    return;
Exit0:
    return;
}

void gmtool::OpenFile_2()
{
    ui.lineEdit->clear();

    QFileDialog *pFileDialog = new QFileDialog(this);
    if (pFileDialog == NULL)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("打开文件对话框失败"), QMessageBox::Yes);
        return;
    }

    pFileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件"));
    pFileDialog->setDirectory(".");
    if (pFileDialog->exec() == QDialog::Accepted)
    {
        QString path = pFileDialog->selectedFiles()[0];
        ui.lineEdit->setText(path);
    }
    else
    {
        QMessageBox::information(this, "critical", QString::fromLocal8Bit("未选择文件"), QMessageBox::Yes);
        return;
    }

    delete pFileDialog;
}



// tag 4
BOOL gmtool::_SelectGroup(INT32 &nGroupID)
{
    INT32       nRetCode = 0;

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    LOG_PROCESS_ERROR(nRetCode);

    nGroupID = ui.comboBox->currentIndex();

    return TRUE;
Exit0:
    return FALSE;
}

void gmtool::AnnounceFunc()
{
    INT32       nRetCode = 0;
    UINT32      dwBeginTime = 0;
    INT32       nIntervalTime = 0;
    INT32       nRepeatNum = 0;
    char        szAnnounce[GM_ANNOUNCE_LENGTH] = { 0 };
    INT32       nAnnounceLength = 0;
    INT32       nGroupID = 0;

    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsServerSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认发送公告？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    nRetCode = _SelectGroup(nGroupID);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return ;
    }

    dwBeginTime = ui.dateTimeEdit_announce->dateTime().toTime_t();
    dwBeginTime /= 60;
    dwBeginTime *= 60;
    nIntervalTime = ui.lineEdit_announce_1->text().toLong();
    nRepeatNum = ui.lineEdit_announce_2->text().toLong();
    strxcpy(szAnnounce, ui.textEdit_announce->toPlainText().toUtf8(), sizeof(szAnnounce));

    nRetCode = FilterUtf8EnterKey(szAnnounce);
    LOG_PROCESS_ERROR(nRetCode);

    nAnnounceLength = strlen(szAnnounce);
    if (nIntervalTime <= 0 || nRepeatNum <= 0 || 0 == nAnnounceLength)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("参数不对"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    if (nAnnounceLength >= GM_ANNOUNCE_LENGTH)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("公告过长，可能会截断"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    nRetCode = CCmdManager::GetInstance().SendAnnounce(nGroupID, dwBeginTime, nIntervalTime, nRepeatNum, szAnnounce);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    return;
Exit0:
    return;
}

void gmtool::GetAnnounceList()
{
    INT32       nRetCode = 0;
    INT32       nGroupID = 0;

    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return; 
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    nRetCode = _SelectGroup(nGroupID);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    ui.announceWidget->clear();
    CDataMgr::GetInstance().ClearAnnounceList();

    nRetCode = CCmdManager::GetInstance().QueryAnnounceList(nGroupID);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    return;
Exit0:
    return;
}

void gmtool::DelAnnounce()
{
    INT32       nRetCode = 0;
    UINT32      dwSessionID = 0;
    INT32       nSelectSvrNum = 0;
    INT32       nAnnounceSerial = -1;
    GM_SESSION  *pGMSession = NULL;
    DEL_ANNOUNCE   *pAnnounceCmd = NULL;
    INT32       nGroupID = 0;

    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认删除公告？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    nRetCode = _SelectGroup(nGroupID);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    // get announce serial
    CMyTreeWidgetItem*pTreeWidgetItem = (CMyTreeWidgetItem*)ui.announceWidget->currentItem();
    if (pTreeWidgetItem)
        nAnnounceSerial = pTreeWidgetItem->GetID();
    
    if (-1 == nAnnounceSerial)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请选择要删除的公告"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    nRetCode = CCmdManager::GetInstance().DelAnnounce(nGroupID, nAnnounceSerial);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    return;
Exit0:
    return;
}





// tag 2
void gmtool::ChangeInputType(int nIndex)
{
    if (nIndex < GM_LOG_QUERY_NONE || nIndex > GM_QUERY_NUM)
        return;

    ui.label_log_0->setDisabled(true);
    ui.lineEdit_log_0->setDisabled(true);

    ui.label_log_1->setDisabled(true);
    ui.lineEdit_log_1->setDisabled(true);

    ui.label_log_2->setDisabled(true);
    ui.lineEdit_log_2->setDisabled(true);

    ui.label_log_3->setDisabled(true);
    ui.lineEdit_log_3->setDisabled(true);

    ui.label_log_4->setDisabled(true);
    ui.lineEdit_log_4->setDisabled(true);

    ui.label_log_5->setDisabled(true);
    ui.lineEdit_log_5->setDisabled(true);

    ui.label_log_6->setDisabled(true);
    ui.lineEdit_log_6->setDisabled(true);


    switch (nIndex)
    {
    case GM_LOG_QUERY_ROLE_LOGIN:
    {
        ui.label_log_0->setDisabled(false);
        ui.lineEdit_log_0->setDisabled(false);
    }
        break;
    case GM_LOG_QUERY_ROLE_LOGOUT:
    {
        ui.label_log_1->setDisabled(false);
        ui.lineEdit_log_1->setDisabled(false);
    }
        break;
    case GM_LOG_QUERY_ITEM:
    {
        ui.label_log_1->setDisabled(false);
        ui.lineEdit_log_1->setDisabled(false);

        ui.label_log_2->setDisabled(false);
        ui.lineEdit_log_2->setDisabled(false);

        ui.label_log_3->setDisabled(false);
        ui.lineEdit_log_3->setDisabled(false);
    }
        break;
    case GM_LOG_QUERY_MONEY:
    {
        ui.label_log_1->setDisabled(false);
        ui.lineEdit_log_1->setDisabled(false);

        ui.label_log_4->setDisabled(false);
        ui.lineEdit_log_4->setDisabled(false);

        ui.label_log_5->setDisabled(false);
        ui.lineEdit_log_5->setDisabled(false);
    }
        break;
    case GM_LOG_QUERY_QUEST:
    {
        ui.label_log_1->setDisabled(false);
        ui.lineEdit_log_1->setDisabled(false);

        ui.label_log_6->setDisabled(false);
        ui.lineEdit_log_6->setDisabled(false);
    }
        break;
    default:
        break;
    }


}

void gmtool::LogSearch()
{
    INT32       nRetCode  = 0;
    UINT32      dwBeginTime = 0;
    UINT32      dwEndTime = 0;
    char        szQueryStr[1024] = { 0 };
    INT32       nLogType = GM_LOG_QUERY_NONE;
    
    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = _PreDealGameLogFile();
    if (!nRetCode)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("无法创建指定log输出文件"), QMessageBox::Yes);
        return;
    }

    nLogType = ui.logComboBox->currentIndex();
    dwBeginTime = ui.dateTimeEdit_log_1->dateTime().toTime_t();
    dwEndTime = ui.dateTimeEdit_log_2->dateTime().toTime_t();

    nRetCode = _SerializeQueryLogStr(nLogType, szQueryStr);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("日志类型错误"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    nRetCode = CCmdManager::GetInstance().QueryLog(nLogType, dwBeginTime , dwEndTime, szQueryStr);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    ui.textEdit->clear();

    return;
Exit0:
    if (m_pCmd)
        CCmdManager::GetInstance().DelCmd(m_pCmd);
    return ;
}

BOOL gmtool::PutsGameLog(INT32 nLogType, BOOL bTruncated, INT32 nLength, const char *pcszBuffer)
{
    INT32       nCount = 0;
    INT32       nWriteFileLength = 0;
    FILE        *pf = NULL;

    LOG_PROCESS_ERROR(pcszBuffer);

    ui.textEdit->append(QString::fromUtf8(pcszBuffer));

    // output to file
    pf = fopen("../output.txt", "a+");
    LOG_PROCESS_ERROR(pf);

    nWriteFileLength = fwrite(pcszBuffer, 1, strlen(pcszBuffer), pf);
    LOG_PROCESS_ERROR(nWriteFileLength == strlen(pcszBuffer));

    fclose(pf);

    if (bTruncated == TRUE)
    {
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("查询数据过长，请缩短查询范围"), QMessageBox::Yes);
    }

    return TRUE;
Exit0:
    return FALSE;
}


// tag 6
void gmtool::QueryNameToID()
{
    INT32       nRetCode = 0;
    std::map<INT32, ROLE_NAME_DATA> RoleNameMap;

    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    nRetCode = _ReadRoleNameFromFile(ui.queryfile_lineEdit->text().toUtf8(), RoleNameMap);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("读取角色名文件失败"), QMessageBox::Yes);
        return;
    }

    nRetCode = CCmdManager::GetInstance().QueryNameToID(RoleNameMap);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    return;
Exit0:
    return;
}

// tag 7
void gmtool::SendGMStrCmd()
{
    INT32       nRetCode = 0;
    char        szStr[MAX_GM_COMMAND_LEN] = { 0 };

    if (CCmdManager::GetInstance().IsCmdExecuting())
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("命令执行中..."), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认执行该gm指令？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    strxcpy(szStr, ui.textEdit_gmStrCmd->toPlainText().toUtf8(), sizeof(szStr));
    if (0 == strlen(szStr))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请输入gm指令"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    nRetCode = CCmdManager::GetInstance().SendGMStrCmd(szStr);
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
        LOG_PROCESS_ERROR(FALSE);
    }

    return;
Exit0:
    return;
}




BOOL gmtool::Init()
{
    g_pRoleInfo = NULL;

    for (UINT32 dwSessionID = 0; dwSessionID < MAX_GM_SESSION_COUNT; ++dwSessionID)
    {
        GM_SESSION *pGMSession = CSessionMgr::GetInstance().GetGMSession(dwSessionID);
        if (pGMSession && pGMSession->dwType == stGM)
        {
            QBrush brush(QColor(255, 0, 0, 255));
            brush.setStyle(Qt::SolidPattern);

            m_arrItemPoint[dwSessionID] = new CSvrTreeWidgetItem;
            m_arrItemPoint[dwSessionID]->SetSessionID(dwSessionID);

            m_arrItemPoint[dwSessionID]->setCheckState(0, Qt::Unchecked);
            m_arrItemPoint[dwSessionID]->setText(0, QString::fromUtf8(pGMSession->szGMName));
            m_arrItemPoint[dwSessionID]->setForeground(0, brush);

            ui.treeWidget_SvrList->addTopLevelItem(m_arrItemPoint[dwSessionID]);
        }
    }

    connect(ui.treeWidget_SvrList, &QTreeWidget::itemClicked, this, &gmtool::UpdateSelectedServer);
    return TRUE;
}

BOOL gmtool::SetTitle()
{
    char        szNum[32] = { 0 };
    char        szSubVersion[32] = { 0 };

    setWindowTitle(QString::fromLocal8Bit("账号: ") + QString::fromLocal8Bit(CGMManager::GetInstance().GetUserName()) 
        + QString::fromLocal8Bit("    版本号: ") + QString::fromLocal8Bit(gm_itoa(GM_MAJOR_VERSION, szNum))
        + QString::fromLocal8Bit("---") + QString::fromLocal8Bit(gm_itoa(GM_MINOR_VERSION, szSubVersion)));
    return TRUE;
}

BOOL gmtool::IsServerSelected(UINT32 dwSessionID)
{
    LOG_PROCESS_ERROR(dwSessionID < MAX_GM_SESSION_COUNT);

    if (!m_arrItemPoint[dwSessionID])
        return FALSE;

    Qt::CheckState state = m_arrItemPoint[dwSessionID]->checkState(0);
    if (state != Qt::Checked)
        return FALSE;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::UpdateSvrNameColor(UINT32 dwSessionID, GM_SVR_STATE eState)
{
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);

    LOG_PROCESS_ERROR(dwSessionID < MAX_GM_SESSION_COUNT);
    LOG_PROCESS_ERROR(m_arrItemPoint[dwSessionID]);

    switch (eState)
    {
    case GM_SVR_STATE_NONE:
        {
            
        }
        break;
    case GM_SVR_STATE_REGISTERED:   // 黄
        {
            brush.setColor(QColor(200,200,0,255));
        }
        break;
    case GM_SVR_STATE_LOGIN:        // 绿
        {
            brush.setColor(QColor(0,255,0,255));
        }
        break;
    case GM_SVR_STATE_DISCONNECT:       // 红
        {
            brush.setColor(QColor(255,0,0,255));
        }
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    m_arrItemPoint[dwSessionID]->setForeground(0, brush);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::OutputLog(const char *pcszLog)
{
    char    szBuffer[1024] = { 0 };
    time_t tCurTime = _time64(NULL);

    struct tm*  pTM = localtime(&tCurTime);
    LOG_PROCESS_ERROR(pTM);

    LOG_PROCESS_ERROR(pcszLog);

    snprintf(szBuffer, 1024, "%02d-%02d %02d:%02d:%02d %s", pTM->tm_mon+1, pTM->tm_mday, pTM->tm_hour, pTM->tm_min, pTM->tm_sec, pcszLog);

    //ui.textBrowser->setPlainText(QString::fromLocal8Bit(pcszLog));
    ui.textBrowser->append(QString::fromLocal8Bit(szBuffer));

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::OutputMessageBox(const char *pcszStr)
{
    LOG_PROCESS_ERROR(pcszStr);

    QMessageBox::information(this, "", QString::fromLocal8Bit(pcszStr), QMessageBox::Yes);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::_ReadRoleFromFile(const char *pcszFileName, std::list<ROLE_RESULT> &list)
{
    INT32       nRetCode = 0;
    FILE        *pFile = NULL;
    char        szRoleBuffer[ROLE_NAME_LEN] = { 0 };
    INT32       nIndex = 1;

    LOG_PROCESS_ERROR(pcszFileName);

    // read string
    pFile = fopen(pcszFileName, "r");
    if (pFile == NULL)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("指定文件无法打开"), QMessageBox::Yes);
        return FALSE;
    }

    list.clear();
    while (NULL != fgets(szRoleBuffer, sizeof(szRoleBuffer), pFile))
    {
        INT32   nOffset = 0;
        ROLE_RESULT  data;
        data.dwRoleID = 0;
        data.nResult = errUnknownError;

        if (nIndex == 1)
            nOffset = 3;

        for (INT32 i = 0; i < ROLE_NAME_LEN; ++i)
        {
            if (szRoleBuffer[i + nOffset] == '\r' || szRoleBuffer[i + nOffset] == '\n')
            {
                data.szRoleName[i] = '\0';
                break;
            }
            data.szRoleName[i] = szRoleBuffer[i + nOffset];
        }
        data.szRoleName[ROLE_NAME_LEN - 1] = '\0';

        //strxcpy(data.szRoleName, szRoleBuffer, ROLE_NAME_LEN);
        list.push_back(data);

        memset(szRoleBuffer, 0, sizeof(szRoleBuffer));
        nIndex++;
    }

    fclose(pFile);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::UpdateRoleResult(const char *pcszFileName, INT32 nType, std::list<ROLE_RESULT> &list)
{
    INT32       nRetCode = 0;
    FILE        *pFile = NULL;
    char        szRoleBuffer[ROLE_NAME_LEN] = { 0 };
    INT32       nIndex = 1;
    char        szFileNameBuffer[256] = { 0 };
    INT32 i = 0;

    LOG_PROCESS_ERROR(pcszFileName);
    
    //while (pcszFileName[i] != '\0')
    //{
    //    if (pcszFileName[i] == '.')
    //    {
    //        memcpy(szFileNameBuffer, pcszFileName, i);
    //        strcat(szFileNameBuffer, "_result");
    //        memcpy(szFileNameBuffer, pcszFileName + i, strlen(pcszFileName) - i);
    //        break;
    //    }
    //    ++i;
    //}
    //if (strlen(szFileNameBuffer) == 0)
    //{
    //}
        strxcpy(szFileNameBuffer, pcszFileName, sizeof(szFileNameBuffer));
        if (nType == CMD_FORBIDDEN_CHAT)
            strcat(szFileNameBuffer, "_chat_result");
        else if (nType == CMD_FREEZE_ROLE)
            strcat(szFileNameBuffer, "_freeze_result");
        else if (nType == CMD_KICK_ROLE)
            strcat(szFileNameBuffer, "_kickrole_result");
        else if (nType == CMD_SEND_MAIL)
            strcat(szFileNameBuffer, "_sendmail_result");
        
    // read string
    pFile = fopen(szFileNameBuffer, "w");
    if (pFile == NULL)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("指定文件无法打开"), QMessageBox::Yes);
        return FALSE;
    }

    char BOM[] = { -17, -69, -65 };
    fwrite(BOM, 1, 3, pFile);

    {
        const INT32 MAX_RES_BUFFER_LENGTH = 1024 * 1024;
        INT32   nBufferLength = 0;
        char    *pcBuffer = new char[MAX_RES_BUFFER_LENGTH];
        LOG_PROCESS_ERROR(pcBuffer);

        nBufferLength += snprintf(pcBuffer + nBufferLength, MAX_RES_BUFFER_LENGTH - nBufferLength, "RoleName\tRoleID\tResult \n");
        for (std::list<ROLE_RESULT>::iterator iter = list.begin(); iter != list.end(); ++iter)
        {
            if (iter->nResult == errSuccess)
                nBufferLength += snprintf(pcBuffer + nBufferLength, MAX_RES_BUFFER_LENGTH - nBufferLength, "%s\t%u\tsuccess \n", iter->szRoleName, iter->dwRoleID);
            else 
                nBufferLength += snprintf(pcBuffer + nBufferLength, MAX_RES_BUFFER_LENGTH - nBufferLength, "%s\t%u\tfailed \n", iter->szRoleName, iter->dwRoleID);
        }
        
        fwrite(pcBuffer, 1, nBufferLength, pFile);

        delete[] pcBuffer;
        pcBuffer = NULL;
    }

    fclose(pFile);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::_ReadRoleIDFromFile(const char *pcszFileName, std::list<UINT32> &RoleIDList)
{
    INT32       nRetCode = 0;
    const INT32 FILE_BUFFER_LENGTH = 1024 * 1024 * 10;
    char        *pBuffer = NULL;
    FILE        *pFile = NULL;
    INT32       nFileLength = 0;

    LOG_PROCESS_ERROR(pcszFileName);

    // read string
    pFile = fopen(pcszFileName, "r");
    if (pFile == NULL)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("指定文件无法打开"), QMessageBox::Yes);
        return FALSE;
    }
    
    pBuffer = new char[FILE_BUFFER_LENGTH];
    LOG_PROCESS_ERROR(pBuffer);

    nFileLength = fread(pBuffer, 1, FILE_BUFFER_LENGTH, pFile);
    if (nFileLength <= 0)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("文件打开错误"), QMessageBox::Yes);
        return FALSE;
    }
    fclose(pFile);

    // parse string
    RoleIDList.clear();
    nRetCode = ParseIDString(pBuffer, nFileLength, RoleIDList);
    if (!nRetCode)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("角色ID 格式错误"), QMessageBox::Yes);
        return FALSE;
    }

    delete[] pBuffer;
    
    return TRUE;
Exit0:
    if (pBuffer)
        delete[] pBuffer;
    return FALSE;
}

BOOL gmtool::_ReadRoleNameFromFile(const char *pcszFileName, std::map<INT32, ROLE_NAME_DATA> &RoleNameMap)
{
    INT32       nRetCode = 0;
    const INT32 FILE_BUFFER_LENGTH = 1024 * 1024 * 10;
    char        *pBuffer = NULL;
    FILE        *pFile = NULL;
    INT32       nFileLength = 0;
    char        szRoleBuffer[32] = { 0 };
    INT32       nIndex = 1;
    char        szFileNameBuffer[256] = { 0 };

    LOG_PROCESS_ERROR(pcszFileName);

    memcpy(szFileNameBuffer, "../", sizeof("../"));
    strcat(szFileNameBuffer, pcszFileName);

    // read string
    pFile = fopen(szFileNameBuffer, "r");
    if (pFile == NULL)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("指定文件无法打开"), QMessageBox::Yes);
        return FALSE;
    }

    RoleNameMap.clear();
    while (NULL != fgets(szRoleBuffer, sizeof(szRoleBuffer), pFile))
    {
        ROLE_NAME_DATA  data;
        data.dwRoleID = 0;
        strxcpy(data.szRoleName, szRoleBuffer, ROLE_NAME_LEN);
        RoleNameMap.insert(std::make_pair(nIndex, data));

        memset(szRoleBuffer, 0, sizeof(szRoleBuffer));
        nIndex++;
    }

    fclose(pFile);

    return TRUE;
Exit0:
    return FALSE;
}



BOOL gmtool::_Tag2ReadRoleID(ROLEID_LIST& roleIDList)
{
    INT32       nRetCode = 0;

    roleIDList.clear();
    if (ui.radioButton_6->isChecked())
    {
        nRetCode = ParseIDString(ui.textEdit_RoleID->toPlainText().toUtf8(), ui.textEdit_RoleID->toPlainText().toUtf8().length(), roleIDList);
        if (!nRetCode)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("角色ID 格式错误"), QMessageBox::Yes);
            return FALSE;
        }
        if (roleIDList.size() > 10)
        {
            QMessageBox::critical(this, "critical", QString::fromLocal8Bit("角色ID 数量过多"), QMessageBox::Yes);
            return FALSE;
        }
    }
    else if (ui.radioButton_5->isChecked())
    {
        return FALSE;
    }

    if (roleIDList.size() == 0)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("未获取角色ID"), QMessageBox::Yes);
        return FALSE;
    }

    return TRUE;
}

void gmtool::_DisableTag5()
{
    ui.lineEdit_log_1->setDisabled(true);
    ui.lineEdit_log_2->setDisabled(true);
    ui.lineEdit_log_3->setDisabled(true);
}

BOOL gmtool::_PreDealGameLogFile()
{
    FILE    *pf = fopen("../output.txt", "wb");
    LOG_PROCESS_ERROR(pf);

    fclose(pf);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::_SerializeQueryLogStr(INT32 nLogType, char *pcszQueryStr)
{
    char        szSndaID[65] = { 0 };
    UINT32      dwRoleID = 0;
    UINT32      dwTargetRoleID = 0;
    UINT32      dwItemID = 0;
    UINT64      qwGuid = 0;
    INT32       nMoneyType = 0;
    INT32       nQuestID = 0;

    LOG_PROCESS_ERROR(pcszQueryStr);

    switch (nLogType)
    {
    case GM_LOG_QUERY_ROLE_LOGIN:
    {
        strxcpy(szSndaID, ui.lineEdit_log_0->text().toUtf8(), sizeof(szSndaID));
        sprintf(pcszQueryStr, "%s", szSndaID);
    }
        break;
    case GM_LOG_QUERY_ROLE_LOGOUT:
    {
        dwRoleID = ui.lineEdit_log_1->text().toULong();
        sprintf(pcszQueryStr, "%u", dwRoleID);
    }
        break;
    case GM_LOG_QUERY_ITEM:
    {
        dwRoleID = ui.lineEdit_log_1->text().toULong();
        dwItemID = ui.lineEdit_log_2->text().toULong();
        qwGuid = ui.lineEdit_log_3->text().toULongLong();

        sprintf(pcszQueryStr, "%u %u %llu", dwRoleID, dwItemID, qwGuid);
    }
        break;
    case GM_LOG_QUERY_MONEY:
    {
        dwRoleID = ui.lineEdit_log_1->text().toULong();
        dwTargetRoleID = ui.lineEdit_log_4->text().toULong();
        nMoneyType = ui.lineEdit_log_5->text().toInt();

        sprintf(pcszQueryStr, "%u %u %d", dwRoleID, dwTargetRoleID, nMoneyType);
    }
        break;
    case GM_LOG_QUERY_QUEST:
    {
        dwRoleID = ui.lineEdit_log_1->text().toULong();
        nQuestID = ui.lineEdit_log_6->text().toInt();

        sprintf(pcszQueryStr, "%u %d", dwRoleID, nQuestID);
    }
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    return TRUE;
Exit0:
    return FALSE;
}


BOOL gmtool::UpdateAnnounceList()
{
    GM_SVR  *pSvr = NULL;

    TL_ANNOUNCE_LIST    &rList = CDataMgr::GetInstance().GetAnnounceList();

    ui.announceWidget->clear();

    for (INT32 i = 0; i < rList.nCount; ++i)
    {
        CMyTreeWidgetItem   *pTreeItem = new CMyTreeWidgetItem;
        char        szNum[20] = { 0 };

        pTreeItem->SetID(rList.data[i].dwSerial);

        pSvr = GetServer(rList.data[i].nSvrID);
        LOG_CHECK_ERROR(pSvr);
        if (pSvr)
        {
            if (rList.data[i].nGroupID == 0)
                pTreeItem->setText(0, QString::fromLocal8Bit("全区"));
            else
                pTreeItem->setText(0, QString::fromUtf8(pSvr->groupList[rList.data[i].nGroupID].szGroupName));
        }
        else
        {
            pTreeItem->setText(0, QString::fromLocal8Bit("未找到组名"));
        }

        pTreeItem->setText(1, QString(gm_itoa(rList.data[i].dwIntervalTime, szNum)).toLocal8Bit());
        pTreeItem->setText(2, QString(gm_itoa(rList.data[i].dwRepeatNum, szNum)).toLocal8Bit());
        pTreeItem->setText(3, QString::fromUtf8(rList.data[i].szText));

        ui.announceWidget->addTopLevelItem(pTreeItem);
    }

    return TRUE;
}

BOOL gmtool::DelAnnounce(UINT32 dwAnnounceSerial)
{
    INT32       nRetCode = 0;

    nRetCode = CDataMgr::GetInstance().DelAnnounceFromList(dwAnnounceSerial);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = UpdateAnnounceList();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::AddQueryRoleIDResult(INT32 nAreaID, UINT32 dwRoleID, const char *pcszRoleName, const char *pcszUserName)
{
    CMyTreeWidgetItem   *pTreeItem = new CMyTreeWidgetItem;
    char        szNum[20] = { 0 };

    pTreeItem->setText(0, QString(gm_itoa(nAreaID,szNum)).toLocal8Bit());
    pTreeItem->setText(1, QString(gm_itoa(dwRoleID,szNum)).toLocal8Bit());
    pTreeItem->setText(2, QString::fromUtf8(pcszRoleName));
    pTreeItem->setText(3, QString::fromUtf8(pcszUserName));

    ui.treeWidget_queryroleid->addTopLevelItem(pTreeItem);

    return TRUE;
}

BOOL gmtool::AddQueryRoleDataResult(INT32 nAreaID, BOOL bIsOnline, GM_ROLE_DATA* pRole)
{
    INT32   nRetCode = 0;
    char    szName[ROLE_NAME_LEN] = { 0 };
    INT32   nGroupID = -1;
    INT32   nSex = 0;
    INT32   nClass = 0;
    INT32   nLevel = 0;
    UINT32  dwDeleteTime = 0;
    CMyTreeWidgetItem   *pTreeItem = NULL;
    char    szSaveTime[21] = { 0 };

    LOG_PROCESS_ERROR(pRole);

    pTreeItem = new CMyTreeWidgetItem;

    INT32   nLength = 0;

    while (nLength < pRole->nLength)
    {
        GM_ROLE_SLOT    *pRoleSlot = (GM_ROLE_SLOT*)(pRole->szData + nLength);
        if (pRoleSlot->wRoleType == GM_ROLE_BASE_DATA)
        {
            switch (pRoleSlot->wBaseDataType)
            {
            case GM_RBD_NAME:
                strxcpy(szName, pRoleSlot->szData, ROLE_NAME_LEN);
                break;
            case GM_RBD_GROUPID:
                nGroupID = *((INT32*)pRoleSlot->szData);
                break;
            case GM_RBD_DELETETIME:
                dwDeleteTime = *((UINT32*)pRoleSlot->szData);
                break;
            case GM_RBD_CLASS:
                nClass = *((INT32*)pRoleSlot->szData);
                break;
            case GM_RBD_SEX:
                nSex = *((INT32*)pRoleSlot->szData);
                break;
            case GM_RBD_LEVEL:
                nLevel = *((INT32*)pRoleSlot->szData);
                break;
            case GM_RBD_LAST_LOGOUT_TIME:
                strxcpy(szSaveTime, pRoleSlot->szData, 21);
                break;
            default:
                break;
            }
        }

        nLength += pRoleSlot->wLength;
    }
   
    nRetCode = DisplayBaseInfoWidgetItem(pTreeItem, nAreaID, nGroupID, pRole->dwRoleID, bIsOnline, szSaveTime, dwDeleteTime, szName, nSex, nClass, nLevel);
    LOG_PROCESS_ERROR(nRetCode);

    ui.treeWidget->addTopLevelItem(pTreeItem);

    return TRUE;
Exit0:
    if (pTreeItem)
        delete pTreeItem;
    return FALSE;
}

BOOL gmtool::LoadRoleData(UINT32 dwSessionID, UINT32 dwRoleID)
{
    CRoleInfo   *pRoleInfo = NULL;
    
    pRoleInfo = new CRoleInfo(dwSessionID, dwRoleID, 1);
    g_pRoleInfo = pRoleInfo;

    pRoleInfo->exec();

    return TRUE;
Exit0:
    if (pRoleInfo)
    {
        delete pRoleInfo;
        g_pRoleInfo = NULL;
    }
        
    return FALSE;
}

BOOL gmtool::SetLDMode()
{
    INT32 nTabPageCount = ui.tabWidget->count();

    for (INT32 i = 0; i < nTabPageCount; ++i)
    {
        ui.tabWidget->removeTab(0);
    }

    CLDWidget   *pLDWidget = new CLDWidget(ui.tabWidget);

    if (pLDWidget)
    {
        ui.tabWidget->addTab(pLDWidget, QString());
        m_pLDWidget = pLDWidget;
    }

    return TRUE;
}

BOOL gmtool::ServerLogin(INT32 nSvrID)
{



    // tag 4
    INT32       nServerListIndex = 0;
    ui.comboBox->clear();

    for (; nServerListIndex < GM_MAX_SERVER_COUNT; ++nServerListIndex)
    {
        if (g_TLConfig.ServerList.arrGMList[nServerListIndex].nSvrID == nSvrID)
            break;
    }
    LOG_PROCESS_ERROR(GM_MAX_SERVER_COUNT != nServerListIndex);

    ui.comboBox->insertItem(0, QString::fromLocal8Bit("全区"));
    for (INT32 nIndex = 1; nIndex < MAX_SERVER_GROUP_COUNT; ++nIndex)
    {
        QString a;
        a = QString::number(nIndex) + QString::fromLocal8Bit(" - ");
        if (0 == strlen(g_TLConfig.ServerList.arrGMList[nServerListIndex].groupList[nIndex].szGroupName))
        {
            ui.comboBox->insertItem(nIndex, a);
        }
        else
        {
            ui.comboBox->insertItem(nIndex, a + QString::fromUtf8(g_TLConfig.ServerList.arrGMList[nServerListIndex].groupList[nIndex].szGroupName));
        }
    }


    // ld_widget
    if (g_gmtool.GetLDWidget())
        g_gmtool.GetLDWidget()->ServerLogin(nSvrID);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL gmtool::LogoutServer(UINT32 dwSessionID)
{
    if (m_pLDWidget)
    {
        m_pLDWidget->UnInit();
    }

    return TRUE;
}





BOOL ParseIDString(const char *pBuffer, UINT32 dwLength, std::list<UINT32> &list)
{
    char        szRoleID[12] = { 0 };

    LOG_PROCESS_ERROR(pBuffer);

    list.clear();

    for (INT32 i = 0; i < dwLength; ++i)
    {
        if ((pBuffer[i] < '0' || pBuffer[i] > '9') && pBuffer[i] != ' ')
            return FALSE;
    }

    for (INT32 i = 0, j = 0; i < dwLength; ++i)
    {
        if (j >= 12)
            return FALSE;

        szRoleID[j] = pBuffer[i];

        if ((szRoleID[j] == ' ') || (i == dwLength - 1))
        {
            if (szRoleID[j] == ' ')
                szRoleID[j] = '\0';

            if (j > 0 || (szRoleID[j] >= '0' && szRoleID[j] <= '9'))
                list.push_back(QString(szRoleID).toULong());
            
            j = 0;
            memset(szRoleID, 0, sizeof(szRoleID));
        }
        else
            ++j;

    }

    return TRUE;
Exit0:
    return FALSE;
}






