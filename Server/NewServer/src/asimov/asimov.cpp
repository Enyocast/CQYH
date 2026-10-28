#include "stdafx.h"
#include "sol_bindings.h"
#include "asimov.h"

#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtreewidget.h>
#include <time.h>


#include "game_world.h"
#include "script_mgr.h"
#include "user_mgr.h"
#include "ai_processor.h"
extern QApplication * ASIMOV_APP;
static asimov* s_pSelf = NULL;

asimov::asimov(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags), m_bAutoCase(FALSE), m_bEnableDisplay(TRUE)
{
    ui.setupUi(this);

    m_qwStartTick = GetTickCountEx();
    m_nGameLoop = 0;

    QObject::connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(runScript()));
    QObject::connect(ui.filterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(logFilter(const QString&)));
    QObject::connect(ui.enterButton, SIGNAL(clicked()), this, SLOT(runScript()));
    QObject::connect(ui.reloadButton, SIGNAL(clicked()), this, SLOT(reloadScript()));
    QObject::connect(ui.cleanButton, SIGNAL(clicked()), this, SLOT(cleanLog()));

    QObject::connect(ui.actionNew_User, SIGNAL(triggered()), this, SLOT(newUser()));
    QObject::connect(ui.actionNew_Test_User, SIGNAL(triggered()), this, SLOT(newTestUser()));
    QObject::connect(ui.actionDelete_User, SIGNAL(triggered()), this, SLOT(deleteUser()));

    QObject::connect(ui.actionLogin, SIGNAL(triggered()), this, SLOT(login()));
    QObject::connect(ui.actionCreate_Role, SIGNAL(triggered()), this, SLOT(createRole()));

    QObject::connect(ui.actionDelete_Role, SIGNAL(triggered()), this, SLOT(deleteRole()));
    QObject::connect(ui.actionLogout, SIGNAL(triggered()), this, SLOT(logout()));
    QObject::connect(ui.actionExit, SIGNAL(triggered()), ASIMOV_APP, SLOT(quit()));

    QObject::connect(ui.userTable, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
        this, SLOT(userTreeDoubleClick(QTreeWidgetItem *, int)));
    QObject::connect(ui.userTable, SIGNAL(itemPressed(QTreeWidgetItem *, int)),
        this, SLOT(userPressed(QTreeWidgetItem *, int)));
    QObject::connect(ui.testTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
        this, SLOT(caseTreeDoubleClick(QTreeWidgetItem *, int)));
    QObject::connect(ui.coverageTestTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
        this, SLOT(coverageCaseTreeDoubleClick(QTreeWidgetItem *, int)));
    QObject::connect(ui.perfTestTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
        this, SLOT(perfCaseTreeDoubleClick(QTreeWidgetItem *, int)));

    QObject::connect(ui.roleTable, SIGNAL(itemClicked(QTreeWidgetItem *, int)),
        this, SLOT(roleClick(QTreeWidgetItem *)));
    QObject::connect(ui.roleTable, SIGNAL(itemPressed(QTreeWidgetItem *, int)),
        this, SLOT(rolePressed(QTreeWidgetItem *)));

    QObject::connect(ui.paramTable, SIGNAL(itemClicked(QTableWidgetItem *)),
        this, SLOT(paramClick(QTableWidgetItem *)));

    QObject::connect(ui.actionEnable_Log, SIGNAL(triggered()), this, SLOT(EnableLog()));
    QObject::connect(ui.actionDisable_Log, SIGNAL(triggered()), this, SLOT(DisableLog()));
    QObject::connect(ui.actionExport_results, SIGNAL(triggered()), this, SLOT(ExportResults()));

    QObject::connect(ui.commandList, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
        this, SLOT(commandListDoubleClick(QListWidgetItem *)));

    ui.testTree->setColumnWidth(0, 200);
    ui.testTree->setColumnWidth(1, 360);
    ui.testTree->setColumnWidth(2, 120);
    ui.testTree->sortItems(0, Qt::AscendingOrder);
    ui.testTree->setSortingEnabled(true);

    ui.coverageTestTree->setColumnWidth(0, 200);
    ui.coverageTestTree->setColumnWidth(1, 360);
    ui.coverageTestTree->setColumnWidth(2, 120);
    ui.coverageTestTree->sortItems(0, Qt::AscendingOrder);
    ui.coverageTestTree->setSortingEnabled(true);

    ui.perfTestTree->setColumnWidth(0, 200);
    ui.perfTestTree->setColumnWidth(1, 360);
    ui.perfTestTree->setColumnWidth(2, 120);
    ui.perfTestTree->sortItems(0, Qt::AscendingOrder);
    ui.perfTestTree->setSortingEnabled(true);

    m_pCurDisplayRole = NULL;
    startTimer(20);
    ui.lineEdit->setFocus();
}

asimov::~asimov()
{

}

asimov& asimov::GetInstance(void)
{
    if (s_pSelf == NULL)
        s_pSelf = new asimov;
    return *s_pSelf;
}

BOOL asimov::Cleanup(void)
{
    SAFE_DELETE(s_pSelf);

    return TRUE;
}

void asimov::timerEvent(QTimerEvent* event)
{
    INT32 nRetCode = 0;
    INT32 nStackTop = 0;
    CGameWorld& rGameWorld = CGameWorld::GetInstance();
    UINT64 qwStartTick = GetTickCountEx();

    CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    UINT64 qwCurrentTick = GetTickCountEx();
    while ((qwCurrentTick - m_qwStartTick) * GAME_FPS > (INT64)m_nGameLoop * 1000)
    {
        rGameWorld.SetGameTime(time(NULL));
        rGameWorld.SetGameTick(GetTickCountEx());

        nRetCode = rGameWorld.MainLoop();
        LOG_CHECK_ERROR(nRetCode);

		CUserMgr::GetInstance().MainLoop(poScript);

		nRetCode = poScript->CallFunction("MainLoop", "");
		LOG_PROCESS_ERROR(nRetCode);

        m_nGameLoop++;
    }

    UINT64 qwInterval = GetTickCountEx() - qwStartTick;
	if (qwInterval > 60)
		CRI("too slow mainloop %llu", qwInterval);
Exit0:
    return;
}

void asimov::EnableLog()
{
	m_bEnableDisplay = TRUE;

    CLog::GetInstance().SetCustomOutput(&asimov::LogOutput);
}

void asimov::DisableLog()
{
	m_bEnableDisplay = FALSE;

    CLog::GetInstance().SetCustomOutput(NULL);
}

void asimov::ExportResults()
{
    string      str;
    str.clear();

    QTreeWidgetItemIterator iter(ui.testTree);
    const char * c_string = NULL;
    const char * c_childString = NULL;

    while (*iter)
    {
        INT32 nTempCount = (*iter)->childCount();
        if (nTempCount)
        {
            QByteArray tempArr = (*iter)->text(0).toLatin1();
			c_string = tempArr.data();

            str += c_string;
            str += "\r\n";

            for (int i = 0; i < nTempCount; i++)
            {
                str += "\t";
                //if ((*iter)->child(i)->text(0))
                {
                    QByteArray tempArr = (*iter)->child(i)->text(0).toLatin1();
                    c_childString = tempArr.data();
                    str += c_childString;
                    str += "\t";
                }

                //if ((*iter)->child(i)->text(1))
                {
                    QByteArray tempArr = (*iter)->child(i)->text(1).toLatin1();
                    c_childString = tempArr.data();
                    str += c_childString;
                    str += "\t";
                }

                //if ((*iter)->child(i)->text(2))
                {
                    QByteArray tempArr = (*iter)->child(i)->text(2).toLatin1();
                    c_childString = tempArr.data();
                    str += c_childString;
                }
                str += "\r\n";
            }  
        }
        else
        {
            //if ((*iter)->text(0))
            {
                QByteArray tempArr = (*iter)->text(0).toLatin1();
                c_string = tempArr.data();
                str += c_string;
                str += "\t";
            }

            str += "\t";

            //if ((*iter)->text(1))
            {
                QByteArray tempArr = (*iter)->text(1).toLatin1();
                c_string = tempArr.data();
                str += c_string;
                str += "\t";
            }

            //if ((*iter)->text(2))
            {
                QByteArray tempArr = (*iter)->text(2).toLatin1();
                c_string = tempArr.data();
                str += c_string;
            }
            str += "\r\n";
        }

        ++iter;
    }

    FILE    *fp = fopen("TestCaseResult.txt", "w");
    if (!fp)
        ASSERT(FALSE && "open file failed!");

    fwrite(str.c_str(), str.length(), 1, fp);

    fclose(fp);

}

void asimov::LogOutput(INT32 eLogLevel, const char* pcszMessage, INT32 nMessageSize)
{
    QListWidgetItem* pItem = NULL;

    pItem = new QListWidgetItem(QString::fromUtf8(pcszMessage));
    LOG_PROCESS_ERROR(pItem);

    pItem->setSizeHint(QSize(0, 16));

    switch (eLogLevel)
    {
    case lltSDU:
    case lltDebug:
    case lltMove:
        pItem->setTextColor(Qt::black);
        break;
    case lltInfo:
        pItem->setTextColor(Qt::darkGreen);
        break;
    case lltWarning:
        pItem->setTextColor(Qt::darkYellow);
        break;
    case lltCritical:
        pItem->setTextColor(Qt::red);
        break;
    case lltLua:
        pItem->setTextColor(Qt::blue);
        break;
    default:
        break;
    }

    asimov::GetInstance().ui.logText->addItem(pItem);
Exit0:
    return;
}

BOOL asimov::_RefreshVariables(void)
{
    BOOL bRetCode = TRUE;
    lua_State * L = NULL;
    INT32 nUserTable = 0;
    QList<QTreeWidgetItem*> SelectedItems;
    QTreeWidgetItem* pTreeItem = NULL;

    L = _GetMainLuaState();
    LOG_PROCESS_ERROR(L);

    lua_newtable(L);
    nUserTable = lua_gettop(L);

    SelectedItems = ui.userTable->selectedItems();

    if (SelectedItems.empty())
    {
        for (INT32 nIndex = 0; nIndex < ui.userTable->topLevelItemCount(); nIndex++)
        {
            pTreeItem = ui.userTable->topLevelItem(nIndex);

            lua_pushstring(L, pTreeItem->text(0).toUtf8().data());
            cqyh::lua::push_object(L, (CUser*)(pTreeItem->data(0, Qt::UserRole).toUInt()), "CUser");
            lua_settable(L, nUserTable);
        }

        lua_setglobal(L, "UserTable");
        bRetCode = FALSE;
    }
    else
    {
        for (QList<QTreeWidgetItem*>::iterator it = SelectedItems.begin();
            it != SelectedItems.end(); ++it)
        {
            if ((*it)->text(0).isEmpty())
                continue;

            lua_pushstring(L, (*it)->text(0).toUtf8().data());
            cqyh::lua::push_object(L, (CUser*)((*it)->data(0, Qt::UserRole).toUInt()), "CUser");
            lua_settable(L, nUserTable);
        }

        lua_setglobal(L, "UserTable");
        bRetCode = TRUE;
    }

Exit0:
    return bRetCode;
}

BOOL asimov::_SetGlobalUser(CUser * poUser)
{
    lua_State* L = NULL;

    L = _GetMainLuaState();
    LOG_PROCESS_ERROR(L);

    cqyh::lua::push_object(L, poUser, "CUser");
    lua_setglobal(L, "g_user");

    return TRUE;
Exit0:
    return FALSE;
}

BOOL asimov::_GetLuaTable(lua_State * L, map<QString, QString> & mapTable,
                          const char * pcszName)
{
    INT32 nOffset = 0;

    lua_getglobal(L, pcszName);
    nOffset = lua_gettop(L);
    LOG_PROCESS_ERROR(lua_istable(L, nOffset));

    lua_pushnil(L);
    while (lua_next(L, nOffset) != 0) {
        if (lua_isstring(L, -2))
            mapTable[lua_tostring(L, -2)] = lua_tostring(L, -1);
        lua_pop(L, 1);
    }

    lua_pop(L, nOffset);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL asimov::_GetParams(map<QString, QString> & mapParam,
                        map<QString, QString> & mapRoutineParam)
{
    BOOL bRetval = FALSE;

    lua_State * L = NULL;
    L = _GetMainLuaState();
    LOG_PROCESS_ERROR(L);

    bRetval = _GetLuaTable(L, mapParam, "g_param");
    LOG_PROCESS_ERROR(bRetval);

    bRetval = _GetLuaTable(L, mapRoutineParam, "g_routine");
    LOG_PROCESS_ERROR(bRetval);

    return TRUE;
Exit0:
    return FALSE;
}

lua_State * asimov::_GetMainLuaState()
{
    BOOL bRetCode = FALSE;
    CLuaScript * poScript = NULL;
    lua_State * L = NULL;

    poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    L = poScript->GetLuaState();
    LOG_PROCESS_ERROR(L);

    return L;
Exit0:
    return NULL;
}

void asimov::_NewUser(QString strUserName, QString strPassword)
{
    CUser* poUser = NULL;
    poUser = CUserMgr::GetInstance().NewUser(strUserName.toUtf8().data(), "pt", strPassword.toUtf8().data(), CUserMgr::GetInstance().GetDefaultGroupID());
    LOG_PROCESS_ERROR(poUser);

Exit0:
    return;
}

void asimov::DeleteUserWidget(CUser * poUser)
{
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->m_pUserWidget);

    if (poUser->GetPlayingRole() != NULL)
    {
        DeleteRoleWidget(poUser->GetPlayingRole());
    }

    QTreeWidgetItem * pItem = ui.userTable->takeTopLevelItem(ui.userTable->indexOfTopLevelItem(poUser->m_pUserWidget));

    if (pItem != NULL)
    {
        delete pItem;
		poUser->m_pUserWidget = NULL;
    }

    return;
Exit0:
    return;
}

void asimov::AddUserWidget(CUser * poUser)
{
    QTreeWidgetItem * pUserTree = new QTreeWidgetItem();
    pUserTree->setText(0, poUser->GetUserName());
    pUserTree->setData(0, Qt::UserRole, QVariant((UINT32) poUser));
    pUserTree->setData(1, Qt::UserRole, QVariant((UINT32) utUser));

    poUser->m_pUserWidget = pUserTree;
    ui.userTable->addTopLevelItem(pUserTree);

    RefreshUserWidget(poUser);
    _RefreshUserRoleWidget(poUser);

    return;
}

void asimov::AddRoleWidget(CRole * poRole)
{
    INT32 nIdx = 0;
    QTreeWidgetItem * pItem = NULL;
    QString strID;
    QString qs;
    //QList<QTreeWidgetItem*> ql;

    pItem = new QTreeWidgetItem();
    LOG_PROCESS_ERROR(pItem);

    //ql = ui.roleTable->findItems(poRole->GetName(),Qt::MatchExactly,0);
    //LOG_PROCESS_ERROR( ql.isEmpty() );

    strID.sprintf("ID [%d]", poRole->GetObjID());
    pItem->setText(0, poRole->GetName());
    pItem->setText(1, strID);
    pItem->setData(0, Qt::UserRole, QVariant((UINT32)poRole));
    ui.roleTable->addTopLevelItem(pItem);
    
	ui.roleTable->setHeaderLabel(QString("Role : %1").arg(ui.roleTable->topLevelItemCount()));

    return;
Exit0:
    return;
}

void asimov::DeleteRoleWidget(CRole * poRole)
{
    QTreeWidgetItemIterator it(ui.roleTable);
    while (*it)
    {
        if ((CRole *)((*it)->data(0, Qt::UserRole).toUInt()) == poRole)
        {
            QTreeWidgetItem * pItem = ui.roleTable->takeTopLevelItem(ui.roleTable->indexOfTopLevelItem(*it));
            if (pItem != NULL)
            {
                delete pItem;
            }
            break;
        }
        it++;
    }

	ui.roleTable->setHeaderLabel(QString("Role : %1").arg(ui.roleTable->topLevelItemCount()));

    return;
Exit0:
    return;
}

void asimov::RefreshUserWidget(CUser * poUser)
{
	QString strStat;

	PROCESS_ERROR(m_bEnableDisplay);

    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->m_pUserWidget);

    switch(poUser->GetUserState())
    {
    case usUnconnected:
        strStat = "Unconnected";
        break;
    case usConnected:
        strStat = "Connected";
        break;
    case usSelectRole:
        strStat = "SelectRole";
        break;
    case usCreatingRole:
        strStat = "CreatingRole";
        break;
    case usPlaying:
        strStat = "Playing";
        break;
    case usDeletingRole:
        strStat = "DeletingRole";
        break;
    case usConnectingBS:
        strStat = "ConnectingBS";
        break;
    case usConnectingGT:
        strStat = "Connecting";
        break;
    default:
        strStat = "";
        return;
    }

    poUser->m_pUserWidget->setText(1, strStat);

    return;
Exit0:
    return;
}

void asimov::_RefreshUserRoleWidget(CUser * poUser)
{
	PROCESS_ERROR(m_bEnableDisplay);

    INT32 nIdx = 0;
    LOG_PROCESS_ERROR(poUser);
    LOG_PROCESS_ERROR(poUser->m_pUserWidget);

    while(poUser->m_pUserWidget->childCount() > 0)
    {
        poUser->m_pUserWidget->takeChild(0);
    }

    CRole** ppRoles = poUser->GetRoleList();
    if (ppRoles == NULL)
    {
        return;
    }

    for (INT32 nIdx=0; nIdx < MAX_ROLE_PER_USER; ++nIdx)
    {
        CRole* poRole = ppRoles[nIdx];
        if (poRole == NULL)
            continue;
        
        QTreeWidgetItem * pRoleTree = new QTreeWidgetItem;
        LOG_PROCESS_ERROR(pRoleTree);

        pRoleTree->setFlags(pRoleTree->flags() & (~Qt::ItemIsSelectable));
        pRoleTree->setText(0, poRole->GetName());

        if (poUser->GetPlayingRole() == poRole)
        {
            pRoleTree->setText(1, "Playing");
            poUser->m_pUserWidget->setExpanded(true);
        }
        else
        {
            pRoleTree->setText(1, "");
        }

        pRoleTree->setData(0, Qt::UserRole, QVariant((UINT32) poUser));
        pRoleTree->setData(1, Qt::UserRole, QVariant((UINT32) utRole));
        pRoleTree->setData(2, Qt::UserRole, QVariant((UINT32) poRole->GetObjID()));

        poUser->m_pUserWidget->addChild(pRoleTree);
    }

    return;
Exit0:
    return;
}

BOOL asimov::_RunScript(QString script)
{
    INT32 nRetCode = 0;
    CLuaScript* poScript = NULL;
    QString strScript;

    strScript = script;
    if (_RefreshVariables())
    {
        strScript = QString("function _runScript(name, user) \n") + 
            script +
            "end\n" +
            "TraverseUser(_runScript);\n";
    }

    poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    nRetCode = poScript->LoadFromBuffer(poScript->GetScriptName(), 
        strScript.toUtf8().data(),strScript.length());
    LOG_PROCESS_ERROR(nRetCode);

    ui.lineEdit->clear();
    INF("---");

    return TRUE;
Exit0:
    return FALSE;
}

void asimov::runScript(void)
{
    BOOL retval;
    if (ui.globalScript->isChecked())
    {
        retval = _RunScript(ui.lineEdit->text());
        LOG_PROCESS_ERROR(retval);
    }
    else if (ui.specifyScript->isChecked())
    {
        _RefreshVariables();

        QList<QTreeWidgetItem*> selectedItems = ui.userTable->selectedItems();
        if (selectedItems.size() != 1)
            return;

        QTreeWidgetItem* item = *(selectedItems.begin());
        UINT32 userType = item->data(1, Qt::UserRole).toUInt();
        if (userType != utUser)
            return;

        CUser* poUser = (CUser *) (item->data(0, Qt::UserRole).toUInt());
        poUser->GMCommand(ui.lineEdit->text().toUtf8().data());
    }

Exit0:
    return;
}

void asimov::logFilter(const QString& text)
{
    for (INT32 nIndex = 0; nIndex < ui.logText->count(); nIndex++)
    {
        QListWidgetItem* pItem = ui.logText->item(nIndex);
        LOG_PROCESS_ERROR(pItem);

        if (pItem->text().contains(text, Qt::CaseInsensitive))
            pItem->setHidden(false);
        else
            pItem->setHidden(true);
    }

Exit0:
    return;
}

void asimov::newUser(void)
{
    INT32 nRetCode = 0;
    QInputDialog InputDialog;
    QString strUserName;
    QString strPassword;

    InputDialog.setLabelText("UserName : ");
    InputDialog.exec();
    strUserName = InputDialog.textValue();

    InputDialog.setLabelText("Password : ");
    InputDialog.exec();
    strPassword = InputDialog.textValue();

    _NewUser(strUserName, strPassword);

    return;
}

void asimov::newTestUser(void)
{
    INT32 nRetCode = 0;
    QInputDialog InputDialog;
    INT32 nTestUserCount = 0;

    InputDialog.setLabelText("Test User Count : ");
    InputDialog.setInputMode(QInputDialog::IntInput);
    InputDialog.setIntRange(0, 10000);
    InputDialog.exec();
    nTestUserCount = InputDialog.intValue();

    for (INT32 nIndex = 0; nIndex < nTestUserCount; nIndex++)
    {
        _NewUser(QString("test%1").arg(nIndex), QString("a"));
    }
}

void asimov::deleteUser(void)
{
    INT32 nRetCode = 0;
    QList<QTreeWidgetItem*> selectedItems = ui.userTable->selectedItems();

    for (QList<QTreeWidgetItem*>::iterator it = selectedItems.begin(); it != selectedItems.end(); ++it)
    {
        CUser* poUser = (CUser*)((*it)->data(0, Qt::UserRole).toUInt());
        if (poUser == NULL)
            continue;

        nRetCode = CUserMgr::GetInstance().DelUser(poUser);
        LOG_CHECK_ERROR(nRetCode);
    }
}

void asimov::login(void)
{
    QList<QTreeWidgetItem*> selectedItems = ui.userTable->selectedItems();

    for (QList<QTreeWidgetItem*>::iterator it = selectedItems.begin(); it != selectedItems.end(); ++it)
    {
        CUser* poUser = (CUser*)((*it)->data(0, Qt::UserRole).toUInt());
        _Login(poUser);
    }
}

void asimov::_Login(CUser * poUser)
{
    INT32 nRetCode = 0;
    PROCESS_ERROR(poUser);
    nRetCode = poUser->ConnectServer("127.0.0.1", 8701, TRUE);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void asimov::createRole(void)
{
    INT32 nRetCode = 0;
    QList<QTreeWidgetItem*> selectedItems = ui.userTable->selectedItems();

    for (QList<QTreeWidgetItem*>::iterator it = selectedItems.begin(); it != selectedItems.end(); ++it)
    {
        CUser* poUser = (CUser*)((*it)->data(0, Qt::UserRole).toUInt());
        if (poUser == NULL)
            continue;

        nRetCode = poUser->CreateRole(poUser->GetUserName(), 1, 1, 1, 1, 1);
        LOG_PROCESS_ERROR(nRetCode);
    }

Exit0:
    return;
}

void asimov::selectRole(void)
{
    return;
}


void asimov::userTreeDoubleClick(QTreeWidgetItem * item, int column)
{
    CUser * poUser = (CUser *) (item->data(0, Qt::UserRole).toUInt());
    UINT32 userType = item->data(1, Qt::UserRole).toUInt();
    if (userType == utUser)
    {
        if (poUser->GetUserState() == usUnconnected)
        {
            poUser->ConnectServer(1228742316, 8701, TRUE);
        }
    }
    else if (userType == utRole)
    {
        if(poUser->GetUserState() == usPlaying)
        {
            poUser->LeaveGame(item->data(2, Qt::UserRole).toUInt());
            return;
        }
        else if (poUser->GetUserState() != usUnconnected)
        {
            poUser->SelectRole(item->data(2, Qt::UserRole).toUInt());
            return;
        }
    }
}

void asimov::roleClick(QTreeWidgetItem * item)
{
    CRole * poRole = (CRole *) (item->data(0, Qt::UserRole).toUInt());
    _ShowRoleInfo(poRole);
}

void asimov::rolePressed(QTreeWidgetItem * item)
{
    QAction * pCreateAction, * pReleaseAction, * pWanderAIAction;
    if (ASIMOV_APP->mouseButtons() == Qt::RightButton)
    {
        QMenu qm(ui.roleTable);
        CRole * poRole = (CRole *) (item->data(0, Qt::UserRole).toUInt());
        if (poRole == NULL)
        {
            return;
        }

        if (poRole->GetAIProcessor() == NULL)
        {
            pCreateAction = qm.addAction("Create AI.");
            pWanderAIAction = qm.addAction("Bind wander AI.");
            pWanderAIAction->setEnabled(false);
        }
        else
        {
            pReleaseAction = qm.addAction("Release AI.");
            pWanderAIAction = qm.addAction("Bind wander AI.");
            pWanderAIAction->setEnabled(true);
        }
    }
}

void asimov::userPressed(QTreeWidgetItem * item, int cnt)
{
    QAction * pLoginAction, * pLogoutAction, * pDeleteAction;
    if (ASIMOV_APP->mouseButtons() == Qt::RightButton)
    {
        QMenu qm(ui.roleTable);

        CUser * poUser = (CUser *) (item->data(0, Qt::UserRole).toUInt());
        UINT32 userType = item->data(1, Qt::UserRole).toUInt();
        if (poUser != NULL && userType == utUser)
        {
            if (poUser->GetUserState() == usUnconnected)
            {
                pLoginAction = qm.addAction("Login");
            }
            else
            {
                pLogoutAction = qm.addAction("Logout");
            }

            pDeleteAction = qm.addAction("Delete");

            QAction * at = qm.exec(QCursor::pos());

            if (at == pLoginAction)
            {
                _Login(poUser);
            }
            else if (at == pLogoutAction)
            {
                poUser->Logout();
                item->takeChildren();
            }
            else if (at == pDeleteAction)
            {
                CUserMgr::GetInstance().DelUser(poUser);
            }
        }
    }
}

void asimov::reloadScript(void)
{
    CGameWorld::GetInstance().Reload("all");
    RefreshTestCaseList();
    RefreshCoverageTestCaseList();
    RefreshPerfTestCaseList();
    RefreshCommandList();
}

void asimov::cleanLog(void)
{
    ui.logText->clear();
}


void asimov::deleteRole(void)
{
    INT32 nRetCode = 0;
    QList<QTreeWidgetItem*> selectedItems = ui.userTable->selectedItems();

    for (QList<QTreeWidgetItem*>::iterator it = selectedItems.begin();
        it != selectedItems.end(); ++it)
    {
        CUser* poUser = (CUser*)((*it)->data(0, Qt::UserRole).toUInt());
        if (poUser == NULL)
            continue;

        //nRetCode = poUser->DeleteRole(poUser->GetUserName());
        //LOG_PROCESS_ERROR(nRetCode);
    }

Exit0:
    return;
}

void asimov::logout(void)
{
    QList<QTreeWidgetItem*> selectedItems = ui.userTable->selectedItems();

    for (QList<QTreeWidgetItem*>::iterator it = selectedItems.begin();
        it != selectedItems.end(); ++it)
    {
        CUser* poUser = (CUser*)((*it)->data(0, Qt::UserRole).toUInt());
        poUser->Logout();
        (*it)->takeChildren();
    }
}

void asimov::userTreeLogout(QTreeWidgetItem * item, int cnt)
{
    ;
}

void asimov::OnSyncRoleList(CUser* poUser, CRole* poRoleList[], INT32 nRoleCount)
{
    INT32 nRetCode = 0;

    for (INT32 nIndex = 0; nIndex < nRoleCount; nIndex++)
    {
        nRetCode = poUser->AddRole(poRoleList[nIndex]);
        LOG_PROCESS_ERROR(nRetCode);
    }

    RefreshUserWidget(poUser);
    _RefreshUserRoleWidget(poUser);

Exit0:
    return;
}

void asimov::OnCreateRole(CUser* poUser, CRole* poRole, BOOL bSuccess)
{
    INT32 nRetCode = 0;

    if (bSuccess)
    {
        nRetCode = poUser->AddRole(poRole);
        LOG_PROCESS_ERROR(nRetCode);

        RefreshUserWidget(poUser);
        _RefreshUserRoleWidget(poUser);
    }

Exit0:

    return;
}

void asimov::OnDeleteRole(CUser* poUser, UINT32 dwRoleID, BOOL bSuccess)
{
    INT32 nRetCode = 0;

    if (bSuccess)
    {
        nRetCode = poUser->RemoveRole(dwRoleID);
        LOG_PROCESS_ERROR(nRetCode);

        RefreshUserWidget(poUser);
        _RefreshUserRoleWidget(poUser);
    }

Exit0:

    return;
}

CRole * asimov::_GetPlayingRoleByID(UINT32 dwRoleID)
{
    list<CRole *>::iterator it;
    for (it = m_pPlayingRoleList.begin(); it != m_pPlayingRoleList.end(); ++it)
    {
        if ((*it)->GetObjID() == dwRoleID)
        {
            return *it;
        }
    }
    return NULL;
}


void asimov::UpdateRoleTable(CRole * poRole)
{
    INT32 nRetCode = 0;

    if (_GetPlayingRoleByID(poRole->GetObjID()))
    {
        RemovePlayingRole(poRole);
    }
    else
    {
        m_pPlayingRoleList.push_back(poRole);
    }

    return;
}

void asimov::RemovePlayingRole(CRole * poRole)
{
    if (_GetPlayingRoleByID(poRole->GetObjID()))
    {
        m_pPlayingRoleList.erase(std::find(m_pPlayingRoleList.begin(),
            m_pPlayingRoleList.end(), poRole));
    }
}

BOOL asimov::CTraverseUserData::operator()(CUser * poUser)
{
    QTreeWidgetItem * pUserTree = new QTreeWidgetItem();
    pUserTree->setText(0, poUser->GetUserName());
    if (poUser->GetUserState() == usUnconnected)
    {
        pUserTree->setText(1, "Unconnected");
    }
    else if (poUser->GetUserState() == usConnected)
    {
        pUserTree->setText(1, "Connected");
    }
    else if (poUser->GetUserState() == usSelectRole)
    {
        pUserTree->setText(1, "SelectRole");
    }
    else if (poUser->GetUserState() == usCreatingRole)
    {
        pUserTree->setText(1, "CreatingRole");
    }
    else if (poUser->GetUserState() == usPlaying)
    {
        pUserTree->setText(1, "Playing");
    }
    else if (poUser->GetUserState() == usDeletingRole)
    {
        pUserTree->setText(1, "DeletingRole");
    }
    else if(poUser->GetUserState() == usConnectingBS)
    {
        pUserTree->setText(1, "ConnectingBS");
    }
    else if (poUser->GetUserState() == usConnectingGT)
    {
        pUserTree->setText(1, "Connecting");
    }

    pUserTree->setData(0, Qt::UserRole, QVariant((UINT32) poUser));
    pUserTree->setData(1, Qt::UserRole, QVariant((UINT32) utUser));
    pThis->ui.userTable->addTopLevelItem(pUserTree);



    return TRUE;

Exit0:
    return FALSE;
}


void asimov::RefreshTestCaseList(void)
{
    CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    lua_State* L = poScript->GetLuaState();
    LOG_PROCESS_ERROR(L);

    lua_getglobal(L, "TestCase");
    LOG_PROCESS_ERROR(lua_istable(L, -1));

    ui.testTree->clear();

    INT32 nTestCaseTable = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, nTestCaseTable))
    {
        if (lua_istable(L, -1))
        {
            const char* pcszModuleName = lua_tostring(L, -2);
            LOG_PROCESS_ERROR(pcszModuleName);

            QTreeWidgetItem* pModuleItem = new QTreeWidgetItem;
            LOG_PROCESS_ERROR(pModuleItem);

            pModuleItem->setText(0, pcszModuleName);
            ui.testTree->addTopLevelItem(pModuleItem);

            INT32 nModuleTable = lua_gettop(L);
            lua_pushnil(L);
            while (lua_next(L, nModuleTable))
            {
                const char* pcszTestCaseName = lua_tostring(L, -2);
                LOG_PROCESS_ERROR(pcszTestCaseName);

                QTreeWidgetItem* pTreeItem = new QTreeWidgetItem(pModuleItem);
                LOG_PROCESS_ERROR(pTreeItem);

                pTreeItem->setText(0, pcszTestCaseName);

                lua_pop(L, 1);
            }
        }
        else if (lua_isfunction(L, -1))
        {
            const char* pcszTestCaseName = lua_tostring(L, -2);
            LOG_PROCESS_ERROR(pcszTestCaseName);

            QTreeWidgetItem* pTreeItem = new QTreeWidgetItem;
            LOG_PROCESS_ERROR(pTreeItem);

            pTreeItem->setText(0, pcszTestCaseName);
            ui.testTree->addTopLevelItem(pTreeItem);
        }
        lua_pop(L, 1);
    }

Exit0:

    return;
}

void asimov::RefreshCoverageTestCaseList(void)
{
    CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    lua_State* L = poScript->GetLuaState();
    LOG_PROCESS_ERROR(L);

    lua_getglobal(L, "CoverageTestCase");
    LOG_PROCESS_ERROR(lua_istable(L, -1));

    ui.coverageTestTree->clear();

    INT32 nTestCaseTable = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, nTestCaseTable))
    {
        if (lua_istable(L, -1))
        {
            const char* pcszModuleName = lua_tostring(L, -2);
            LOG_PROCESS_ERROR(pcszModuleName);

            QTreeWidgetItem* pModuleItem = new QTreeWidgetItem;
            LOG_PROCESS_ERROR(pModuleItem);

            pModuleItem->setText(0, pcszModuleName);
            ui.coverageTestTree->addTopLevelItem(pModuleItem);

            INT32 nModuleTable = lua_gettop(L);
            lua_pushnil(L);
            while (lua_next(L, nModuleTable))
            {
                const char* pcszTestCaseName = lua_tostring(L, -2);
                LOG_PROCESS_ERROR(pcszTestCaseName);

                QTreeWidgetItem* pTreeItem = new QTreeWidgetItem(pModuleItem);
                LOG_PROCESS_ERROR(pTreeItem);

                pTreeItem->setText(0, pcszTestCaseName);

                lua_pop(L, 1);
            }
        }
        else if (lua_isfunction(L, -1))
        {
            const char* pcszTestCaseName = lua_tostring(L, -2);
            LOG_PROCESS_ERROR(pcszTestCaseName);

            QTreeWidgetItem* pTreeItem = new QTreeWidgetItem;
            LOG_PROCESS_ERROR(pTreeItem);

            pTreeItem->setText(0, pcszTestCaseName);
            ui.coverageTestTree->addTopLevelItem(pTreeItem);
        }
        lua_pop(L, 1);
    }

Exit0:

    return;
}

void asimov::RefreshPerfTestCaseList(void)
{
    CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    lua_State* L = poScript->GetLuaState();
    LOG_PROCESS_ERROR(L);

    lua_getglobal(L, "PerfTestCase");
    LOG_PROCESS_ERROR(lua_istable(L, -1));

    ui.perfTestTree->clear();

    INT32 nTestCaseTable = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, nTestCaseTable))
    {
        if (lua_istable(L, -1))
        {
            const char* pcszModuleName = lua_tostring(L, -2);
            LOG_PROCESS_ERROR(pcszModuleName);

            QTreeWidgetItem* pModuleItem = new QTreeWidgetItem;
            LOG_PROCESS_ERROR(pModuleItem);

            pModuleItem->setText(0, pcszModuleName);
            ui.perfTestTree->addTopLevelItem(pModuleItem);

            INT32 nModuleTable = lua_gettop(L);
            lua_pushnil(L);
            while (lua_next(L, nModuleTable))
            {
                const char* pcszTestCaseName = lua_tostring(L, -2);
                LOG_PROCESS_ERROR(pcszTestCaseName);

                QTreeWidgetItem* pTreeItem = new QTreeWidgetItem(pModuleItem);
                LOG_PROCESS_ERROR(pTreeItem);

                pTreeItem->setText(0, pcszTestCaseName);

                lua_pop(L, 1);
            }
        }
        else if (lua_isfunction(L, -1))
        {
            const char* pcszTestCaseName = lua_tostring(L, -2);
            LOG_PROCESS_ERROR(pcszTestCaseName);

            QTreeWidgetItem* pTreeItem = new QTreeWidgetItem;
            LOG_PROCESS_ERROR(pTreeItem);

            pTreeItem->setText(0, pcszTestCaseName);
            ui.perfTestTree->addTopLevelItem(pTreeItem);
        }
        lua_pop(L, 1);
    }

Exit0:

    return;
}

void asimov::RefreshCommandList(void)
{
    CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    lua_State* L = poScript->GetLuaState();
    LOG_PROCESS_ERROR(L);

    lua_getglobal(L, "CommandList");
    LOG_PROCESS_ERROR(lua_istable(L, -1));

    ui.commandList->clear();

    INT32 nCommandTable = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, nCommandTable))
    {
        const char* pcszCommand = lua_tostring(L, -1);
        LOG_PROCESS_ERROR(pcszCommand);

        QListWidgetItem* pItem = new QListWidgetItem(ui.commandList);
        LOG_PROCESS_ERROR(pItem);

        pItem->setText(pcszCommand);

        lua_pop(L, 1);
    }
    lua_pop(L, 1);

Exit0:

    return;
}

void asimov::_ShowRoleInfo(CRole * poRole = NULL)
{
    TCHAR pszInfo[512] = {0};
    QTableWidgetItem * pItem = NULL;
    INT32 nIdx = 0;
    CUser* poUser = NULL;

    if (poRole == NULL)
    {
        if (m_pCurDisplayRole == NULL)
        {
            return;
        }
        poRole = m_pCurDisplayRole;
    }

    ui.textBrowser->clear();
    poUser = CUserMgr::GetInstance().FindUser(poRole->GetSessionID());
    
    if (poUser)
    {
            snprintf(pszInfo, sizeof(pszInfo), "<font color=\"red\">Role: %s (%s)</font>",
                poRole->GetName(), poUser->GetUserName());
        ui.textBrowser->append(pszInfo);
    }

    snprintf(pszInfo, sizeof(pszInfo), "Pos: [X: %lld Y: %lld Z: %lld]",
        poRole->GetX(), poRole->GetY(), poRole->GetZ());
    ui.textBrowser->append(pszInfo);

    snprintf(pszInfo, sizeof(pszInfo), "Real Pos: [X: %.3f Y: %.3f Z: %.3f]",
        poRole->GetX() / (double) POINT_PER_CM, poRole->GetY() / (double) POINT_PER_CM, poRole->GetZ() / (double) POINT_PER_CM);
    ui.textBrowser->append(pszInfo);

    snprintf(pszInfo, sizeof(pszInfo), "Walk Speed: %d.", poRole->GetAttr(catWalkSpeed));
    ui.textBrowser->append(pszInfo);

	snprintf(pszInfo, sizeof(pszInfo), "Run Speed: %d.", poRole->GetAttr(catRunSpeed));
	ui.textBrowser->append(pszInfo);

    map<QString, QString> mapTextParam, mapRoutineParam;
    _SetGlobalUser(poUser);
    _RunScript("get_data()");
    _GetParams(mapTextParam, mapRoutineParam);

    ui.paramTable->clear();
    ui.paramTable->setColumnCount(3);
    ui.paramTable->setRowCount(mapTextParam.size() + mapRoutineParam.size());

    map<QString, QString>::iterator it;
    nIdx = 0;
    for (it = mapTextParam.begin(); it != mapTextParam.end(); ++it)
    {
        pItem = new QTableWidgetItem(it->first);
        LOG_PROCESS_ERROR(pItem);
        pItem->setFlags(pItem->flags() & (~Qt::ItemIsSelectable) & (~Qt::ItemIsEditable));
        ui.paramTable->setItem(nIdx, 0, pItem);

        pItem = new QTableWidgetItem(it->second);
        LOG_PROCESS_ERROR(pItem);
        pItem->setFlags(pItem->flags() & (~Qt::ItemIsSelectable) & (~Qt::ItemIsEditable));
        ui.paramTable->setItem(nIdx, 1, pItem);

        nIdx++;
    }

    for (it = mapRoutineParam.begin(); it != mapRoutineParam.end(); ++it)
    {
        pItem = new QTableWidgetItem(it->first);
        LOG_PROCESS_ERROR(pItem);
        pItem->setFlags(pItem->flags() & (~Qt::ItemIsSelectable) & (~Qt::ItemIsEditable));
        ui.paramTable->setItem(nIdx, 0, pItem);

        pItem = new QTableWidgetItem("Execute");
        pItem->setData(Qt::UserRole, QVariant((QString) it->second));
        pItem->setBackgroundColor(Qt::GlobalColor::cyan);
        LOG_PROCESS_ERROR(pItem);
        pItem->setFlags(pItem->flags() & (~Qt::ItemIsSelectable) & (~Qt::ItemIsEditable));
        ui.paramTable->setItem(nIdx, 2, pItem);

        nIdx++;
    }

    m_pCurDisplayRole = poRole;

Exit0:
    return;
}


void asimov::paramClick(QTableWidgetItem * item)
{
    if (item->column() == 2) // For "Run" button
    {
        QString script = item->data(Qt::UserRole).toString();
        if (script.length() > 0)
        {
            _RunScript(script);
        }
    }
}

void asimov::AutoCase()
{
    _RunScript("run();");
}

void asimov::caseTreeDoubleClick(QTreeWidgetItem* pTreeItem, int nColumn)
{
    char szScript[1024];

    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->parent())
    {
        sprintf(szScript, "addco(\"%s.%s\", TestCase.%s.%s);", 
			pTreeItem->parent()->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data(),
			pTreeItem->parent()->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data());
        pTreeItem->setText(2, "");
        _RunScript(szScript);
    }
    else if (pTreeItem->childCount() == 0)
    {
        sprintf(szScript, "addco(\"%s\", TestCase.%s);", 
			pTreeItem->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data());
        pTreeItem->setText(2, "");
        _RunScript(szScript);
    }

Exit0:
    return;
}

void asimov::coverageCaseTreeDoubleClick(QTreeWidgetItem* pTreeItem, int nColumn)
{
    char szScript[1024];

    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->parent())
    {
        sprintf(szScript, "addco(\"%s.%s\", CoverageTestCase.%s.%s);", 
			pTreeItem->parent()->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data(),
			pTreeItem->parent()->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data());
        pTreeItem->setText(2, "");
        _RunScript(szScript);
    }
    else if (pTreeItem->childCount() == 0)
    {
        sprintf(szScript, "addco(\"%s\", CoverageTestCase.%s);", 
			pTreeItem->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data());
        pTreeItem->setText(2, "");
        _RunScript(szScript);
    }

Exit0:
    return;
}

void asimov::perfCaseTreeDoubleClick(QTreeWidgetItem* pTreeItem, int nColumn)
{
    char szScript[1024];

    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->parent())
    {
        sprintf(szScript, "addco(\"%s.%s\", PerfTestCase.%s.%s);", 
			pTreeItem->parent()->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data(),
			pTreeItem->parent()->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data());
        pTreeItem->setText(2, "");
        _RunScript(szScript);
    }
    else if (pTreeItem->childCount() == 0)
    {
        sprintf(szScript, "addco(\"%s\", PerfTestCase.%s);", 
			pTreeItem->text(0).toLatin1().data(), pTreeItem->text(0).toLatin1().data());
        pTreeItem->setText(2, "");
        _RunScript(szScript);
    }

Exit0:
    return;
}

void asimov::commandListDoubleClick(QListWidgetItem * item)
{
    char szScript[1024];

    LOG_PROCESS_ERROR(item);

    _RunScript(item->text().toLatin1().data());

Exit0:
    return;
}

BOOL asimov::requireParam(const CHAR * pcszName, CHAR * pszVal, INT32 nLen)
{
    INT32 nRetCode = 0;
    QInputDialog InputDialog;

    LOG_PROCESS_ERROR(pcszName);
    LOG_PROCESS_ERROR(pszVal);

    InputDialog.setLabelText(pcszName);
    INT32 nRetval = InputDialog.exec();
    if (nRetval == QDialog::Accepted)
    {
        strncpy(pszVal, InputDialog.textValue().toLatin1().data(), nLen);
        return TRUE;
    }
Exit0:
    return FALSE;
}

void asimov::setCaseStatus(const char* pcszCaseName, const char* pcszMessage)
{
	PROCESS_ERROR(m_bEnableDisplay);

    char szCaseName[256];
    QTreeWidgetItem* pTreeItem = NULL;
    strcpy(szCaseName, pcszCaseName);

    if (QString(pcszCaseName).contains(QChar('.'), Qt::CaseSensitive))
    {
        const char* pcszModuleName = strtok(szCaseName, ".");
        const char* pcszTestCaseName = pcszModuleName + strlen(pcszModuleName) + 1;
        QList<QTreeWidgetItem*> TreeItemList = ui.testTree->findItems(pcszModuleName, Qt::MatchExactly, 0);
        PROCESS_ERROR(!TreeItemList.isEmpty());

        pTreeItem = TreeItemList.front();

        for (int i = 0; i < pTreeItem->childCount(); i++)
        {
            if (pTreeItem->child(i)->text(0) == QString(pcszTestCaseName))
            {
                pTreeItem->child(i)->setText(1, pcszMessage);
                break;
            }
        }
    }
    else
    {
        QList<QTreeWidgetItem*> TreeItemList = ui.testTree->findItems(pcszCaseName, Qt::MatchExactly, 0);
        PROCESS_ERROR(!TreeItemList.isEmpty());

        pTreeItem = TreeItemList.front();
        pTreeItem->setText(1, pcszMessage);
    }


Exit0:
    return;
}

void asimov::setCaseResult(const char* pcszCaseName, const char* pcszMessage)
{
    char szCaseName[256];
    QTreeWidgetItem* pTreeItem = NULL;
    strcpy(szCaseName, pcszCaseName);

    if (QString(pcszCaseName).contains(QChar('.'), Qt::CaseSensitive))
    {
        const char* pcszModuleName = strtok(szCaseName, ".");
        const char* pcszTestCaseName = pcszModuleName + strlen(pcszModuleName) + 1;
        QList<QTreeWidgetItem*> TreeItemList = ui.testTree->findItems(pcszModuleName, Qt::MatchExactly, 0);
        PROCESS_ERROR(!TreeItemList.isEmpty());

        pTreeItem = TreeItemList.front();

        for (int i = 0; i < pTreeItem->childCount(); i++)
        {
            if (pTreeItem->child(i)->text(0) == QString(pcszTestCaseName))
            {
                pTreeItem->child(i)->setText(2, pcszMessage);
                break;
            }
        }
    }
    else
    {
        QList<QTreeWidgetItem*> TreeItemList = ui.testTree->findItems(pcszCaseName, Qt::MatchExactly, 0);
        PROCESS_ERROR(!TreeItemList.isEmpty());

        pTreeItem = TreeItemList.front();
        pTreeItem->setText(2, pcszMessage);
    }

    if (m_bAutoCase)
    {
        if (strcmp(pcszMessage, "failed") == 0)
        {
            printf("case [%s] failed.\n", pcszCaseName);
        }

        BOOL bFinish = TRUE;
        QTreeWidgetItemIterator it(ui.testTree);
        while (*it)
        {
            QString text = (*it)->text(2);
            if (text.length() <= 0)
            {
                bFinish = FALSE;
                break;
            }
            it++;
        }

        if (bFinish)
        {
            ASIMOV_APP->quit();
        }
    }

Exit0:
    return;
}

VOID asimov::setAutoCase(BOOL bVal)
{
    m_bAutoCase = bVal;
}
