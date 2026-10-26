#ifndef ASIMOV_H
#define ASIMOV_H

#include <QtWidgets/QMainWindow>
#include "ui_asimov.h"
#include <list>

using namespace std;

#define ROBOT_SCRIPT_NAME   "script/robot/main.lua"
#define FUNC_ON_ROLE_DELETE "on_role_delete"

class CUser;
class CRole;

enum USER_TREE_TYPE
{
    utUser = 0,
    utRole,
};

struct lua_State;

class asimov : public QMainWindow
{
    Q_OBJECT

public:
	asimov(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~asimov();

    static asimov& GetInstance(void);
    BOOL Cleanup(void);

    static void LogOutput(INT32 eLogLevel, const char* pcszMessage, INT32 nMessageSize);

    virtual void timerEvent(QTimerEvent* event);

public:
    void OnSyncRoleList(CUser* poUser, CRole* poRoleList[], INT32 nRoleCount);
    void OnCreateRole(CUser* poUser, CRole* poRole, BOOL bSuccess);
    void OnDeleteRole(CUser* poUser, UINT32 dwRoleID, BOOL bSuccess);

    // 更新显示游戏中玩家角色列表信息。
    void UpdateRoleTable(CRole * poRole);
    void RemovePlayingRole(CRole * poRole);

    // 从UI获取用户输入信息。
    BOOL requireParam(const CHAR * pcszName, CHAR * pszVal, INT32 nLen);

    void setCaseStatus(const char* pcszCaseName, const char* pcszMessage);
    void setCaseResult(const char* pcszCaseName, const char* pcszMessage);

    VOID setAutoCase(BOOL bVal);
    UINT64 GetStartTick(void)                   {return m_qwStartTick;}

public slots:
    void runScript(void);
    void logFilter(const QString& text);
    void newUser(void);
    void newTestUser(void);
    void deleteUser(void);

    void login(void);
    void createRole(void);
    void selectRole(void);
    void deleteRole(void);
    void logout(void);
    
    void userTreeLogout(QTreeWidgetItem *, int);
    void userTreeDoubleClick(QTreeWidgetItem *, int);
    void roleClick(QTreeWidgetItem *);
    void rolePressed(QTreeWidgetItem *);
    void userPressed(QTreeWidgetItem *, int);
    void paramClick(QTableWidgetItem *);
    void caseTreeDoubleClick(QTreeWidgetItem *, int);
    void coverageCaseTreeDoubleClick(QTreeWidgetItem *, int);
    void perfCaseTreeDoubleClick(QTreeWidgetItem *, int);
    void commandListDoubleClick(QListWidgetItem *);

    void reloadScript(void);
    void cleanLog(void);
    void RefreshTestCaseList(void);
    void RefreshCoverageTestCaseList(void);
    void RefreshPerfTestCaseList(void);
    void RefreshCommandList(void);

    void AddUserWidget(CUser * poUser);
    void DeleteUserWidget(CUser * poUser);

    void AddRoleWidget(CRole * poRole);
    void DeleteRoleWidget(CRole * poRole);
    void RefreshUserWidget(CUser * poUser);

    void AutoCase();

    void EnableLog();
    void DisableLog();

    void ExportResults();

private:
    BOOL _RefreshVariables(void);
    BOOL _SetGlobalUser(CUser * poUser);
    BOOL _GetLuaTable(lua_State * L, map<QString, QString> & mapTable,
        const char * pcszName);
    BOOL _GetParams(map<QString, QString> & mapParam,
        map<QString, QString> & mapRoutineParam);
    lua_State * _GetMainLuaState();

    void _NewUser(QString strUserName, QString strPassword);
    CRole * _GetPlayingRoleByID(UINT32 dwRoleID);
    
    void _RefreshUserRoleWidget(CUser * poUser);
    
    void _ShowRoleInfo(CRole * poRole);
    
    void _Login(CUser * poUser);
    
    BOOL _RunScript(QString script);

private:
    Ui::asimovClass ui;
    UINT64          m_qwStartTick;
    INT32           m_nGameLoop;
    list<CRole *>   m_pPlayingRoleList;
    CRole *         m_pCurDisplayRole;
    BOOL            m_bAutoCase;
	BOOL			m_bEnableDisplay;
    typedef std::map<QString, QTreeWidgetItem*>  MAP_CASE_NAME_2_TREE_ITEM;
    MAP_CASE_NAME_2_TREE_ITEM   m_mapCaseName2TreeItem;

    struct CTraverseUserData
    {
        asimov * pThis;
        BOOL operator()(CUser * poUser);
    };
};

#endif // ASIMOV_H
