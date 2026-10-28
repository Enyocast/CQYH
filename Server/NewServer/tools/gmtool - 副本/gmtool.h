/********************************************************************
	created:	4:7:2013   18:35
	file:		gmtool.h
	author:		Allan Tao
	
	purpose:	GM工具主界面类
*********************************************************************/
#ifndef GMTOOL_H
#define GMTOOL_H

#include <QtWidgets/QMainWindow>
#include "ui_gmtool.h"
#include "server_def.h"
#include "string_def.h"
#include "cmd_data.h"

struct ITEM_LOG_DATA;
struct TL_ROLE_BASE_INFO;
class CSvrTreeWidgetItem;
enum GM_SVR_STATE;
struct CMD_BASE;
struct GM_ROLE_DATA;
struct GM_SESSION;
struct LOG_DATA;
struct ROLE_NAME_DATA;
struct CLDWidget;

class gmtool : public QMainWindow
{
    Q_OBJECT

public:
    gmtool(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~gmtool();

    typedef std::list<UINT32>   ROLEID_LIST;

    virtual void timerEvent(QTimerEvent* event);


public:
    BOOL    Init();

    BOOL    SetTitle();

    BOOL    IsServerSelected(UINT32 dwSessionID);

    BOOL    UpdateSvrNameColor(UINT32 dwSessionID, GM_SVR_STATE eState);

    BOOL    OutputLog(const char *pcszLog);
    BOOL    OutputMessageBox(const char *pcszStr);

    BOOL        UpdateAnnounceList();
    BOOL        DelAnnounce(UINT32 dwAnnounceSerial);

    BOOL        AddQueryRoleIDResult(INT32 nAreaID, UINT32 dwRoleID, const char *pcszRoleName, const char *pcszUserName);
    BOOL        AddQueryRoleDataResult(INT32 nAreaID, BOOL bIsOnline, GM_ROLE_DATA* pRole);
    BOOL        LoadRoleData(UINT32 dwSessionID, UINT32 dwRoleID);

    BOOL        SetLDMode();
    CLDWidget   *GetLDWidget()      { return m_pLDWidget; }

    BOOL        ServerLogin(INT32 nSvrID);
    BOOL        LogoutServer(UINT32 dwSessionID);

public slots:
    void Ok();
    void Execute();
    void Exit();
    void ClearLog();

    void Login();
    void Logout();

    void SecondInit(int nIndex);
    void UpdateSelectedServer(QTreeWidgetItem * item, int column);

    //////////////////////////////////////////////////////////////////////////
    // tag 1: role相关
    // tag 2: 封号，禁言，邮件
    // tag 3: 公会操作
    // tag 4: 活动相关，公告
    // tag 5: 日志查询
    // tag 6: 其他
    //////////////////////////////////////////////////////////////////////////

    // tag 1
    void SetFocusRoleName();
    void SetFocusUserName();
    void SetFocusRoleIDByEdit();
    void SetFocusRoleIDByFile();

    void QueryRoleID();
    void QueryRoleData();
    void ViewRoleData();
    void ModifyRoleData();
    void OpenFile();
    void RoleGMCmd();


    // tag 2
    void SetFocusRoleIDByEdit2();
    void SetFocusRoleIDByFile2();
    void SetFocusForbidChat();

    void ForBiddenChat();
    void UnforbidChat();
    void FreezeRole();
    void UnfreezeRole();
    void KickRole();
    void Mail();
    void OpenFile_2();


    // tag 4
    
    void AnnounceFunc();
    void GetAnnounceList();
    void DelAnnounce();

    // tag 5
    void ChangeInputType(int nIndex);
    void LogSearch();


    BOOL PutsGameLog(INT32 nLogType, BOOL bTruncated, INT32 nLength, const char *pcszBuffer);


    // tag 6
    void QueryNameToID();


    // tag 7
    void SendGMStrCmd();

    //void SearchRoleType(const QString &);


public:
    BOOL    UpdateRoleResult(const char *pcszFileName, INT32 nType, std::list<ROLE_RESULT> &list);

protected:
    BOOL    _ReadRoleFromFile(const char *pcszFileName, std::list<ROLE_RESULT> &list);
    BOOL    _ReadRoleIDFromFile(const char *pcszFileName, std::list<UINT32> &RoleIDList);
    BOOL    _ReadRoleNameFromFile(const char *pcszFileName, std::map<INT32, ROLE_NAME_DATA> &RoleNameMap);


    // tag 2
    BOOL    _Tag2ReadRoleID(ROLEID_LIST& roleIDList);

    // tag 4
    BOOL    _SelectGroup(INT32 &nGroupID);

    //tag 5
    void    _DisableTag5();
    BOOL    _PreDealGameLogFile();
    BOOL    _SerializeQueryLogStr(INT32 nLogType, char *pcszQueryStr);

private:
    Ui::gmtoolClass ui;
    
    QButtonGroup    *m_pQueryRoleRadioGroup;
    QButtonGroup    *m_pQueryIDRadioGroup;
    QButtonGroup    *m_pRadioGroup;
    QButtonGroup    *m_pFCRadioGroup;
    //QButtonGroup    *m_pFLRadioGroup;
    //QButtonGroup    *m_pButtonGroup;

    CSvrTreeWidgetItem  *m_arrItemPoint[MAX_GM_SESSION_COUNT];

    CMD_BASE    *m_pCmd;


    // tag 4
    INT32       m_nSelectSvrID;


    //
    CLDWidget       *m_pLDWidget;

};



BOOL ParseIDString(const char *pBuffer, UINT32 dwLength, std::list<UINT32> &list);

//BOOL ParseNameString(const char *pBuffer, UINT32 dwLength, std::list<ROLE_NAME_DATA> &list);


extern gmtool g_gmtool;
extern QApplication app;



#endif // GMTOOL_H
