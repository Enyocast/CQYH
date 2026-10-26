/********************************************************************
	created:	28:2:2013   16:00
	file:		master_mgr.h
	author:		Allan Tao
	
	purpose:	 ¶ÕΩπ‹¿Ì∆˜
*********************************************************************/


#ifndef _H_MASTER_MGR_H_
#define _H_MASTER_MGR_H_


#include "master_def.h"
#include "id_object_pool.h"
#include "onlinerole/online_role_data.h"
#include "object_pool.h"
#include "server_def.h"

struct MS_TEACHER_DATA 
{
    UINT32      dwRoleID;
    UINT8       byStudNum;
    UINT32      arrStudentID[MAX_STUDENT_NUM];
};

struct MS_STUDENT_DATA 
{
    UINT32      dwRoleID;
    UINT32      dwTeacherID;
};



class CMasterMgr
{
private:
    CMasterMgr();
    virtual ~CMasterMgr();
private:
    static CMasterMgr   ms_Instance_;

public:
    static CMasterMgr& GetInstance(void);

    BOOL    Init();
    BOOL    Uninit();


//////////////////////////////////////////////////////////////////////////
// master
//////////////////////////////////////////////////////////////////////////
public:
    BOOL    BeMaster(MS_ROLE_DATA *pRole);
    INT32   CreateMasterRelation(MS_ONLINE_ROLE_DATA &teacher, MS_ONLINE_ROLE_DATA &student);
    INT32   DelMasterRelation(UINT32 dwTeacherID, MS_ROLE_DATA &student, BOOL bIsGrad);


    MS_TEACHER_DATA *GetTeacherData(UINT32 dwTeacherID);
    MS_STUDENT_DATA *GetStudentData(UINT32 dwStudentID);

    BOOL    IsStudent(UINT32 dwRoleID);
    BOOL    IsMaster(UINT32 dwRoleID);
    BOOL    IsStudentFull(MS_ONLINE_ROLE_DATA &onlineRole);
    INT32   GetStudentNum(UINT32 dwTeacherID);

    void    AddCZ_i(INT32 nSvrGroup, UINT64 qwID, INT32 nLevel, BOOL isSave);
    void    AddCZ(INT32 nSvrGroup, UINT32 dwRole1, UINT32 dwRole2, INT32 nLevel);
    BOOL    DelCZ(UINT32 dwRole1, UINT32 dwRole2);
    INT32   GetCZ(UINT32 dwRole1, UINT32 dwRole2);
    BOOL    UpdateCZ(UINT32 dwRole1, MS_ONLINE_ROLE_DATA &onlineRole, INT32 nLevel);

    BOOL    LoadTeacherData(UINT32 dwTeacherID);
    BOOL    LoadStudentData(UINT32 dwTeacherID, UINT32 dwStudentID);
protected:
    BOOL    _AddMasterRelationToMysql(INT32 nSvrGroup, UINT32 dwTeacherID, UINT32 dwStudentID);
    BOOL    _DelMasterRelationToMysql(UINT32 dwTeacherID, UINT32 dwStudentID);

    BOOL    _AddCZToMysql(INT32 nSvrGroup, UINT64 qwID, INT32 nCZ);
    BOOL    _DelCZToMysql(UINT64 qwID);
    BOOL    _UpdateCZToMysql(UINT64 qwID, INT32 nCZ);


//////////////////////////////////////////////////////////////////////////
// recruit
//////////////////////////////////////////////////////////////////////////
public:
    INT32   AddRecruit(MS_ONLINE_ROLE_DATA &onlineRoleData);
    INT32   DelRecruit(MS_ONLINE_ROLE_DATA &onlineRoleData);

    // to be delete todo_tq Allan Tao
    //BOOL    GetRecruitList(char *buff, UINT8 &count );
    BOOL    GetRecruitData(INT32 nGroup, UINT32 &dwRoleID);

    BOOL    AddSolo(INT32 nGroup, UINT32 dwRoleID);
    BOOL    DelSolo(INT32 nGroup, UINT32 dwRoleID);
    BOOL    GetSolo(INT32 nGroup, UINT32 &dwRoleID);

    MS_ONLINE_ROLE_DATA*    GetOneFromTwitter(INT32 nGroup);
    BOOL    JoinTwitter(MS_ONLINE_ROLE_DATA &onlineRoleData);
    BOOL    QuitTwitter(MS_ONLINE_ROLE_DATA &onlineRoleData);
    BOOL    AjustRankingsOnTwitter(MS_ONLINE_ROLE_DATA &onlineRoleData);
    BOOL    AjustRankingsOnTwitter(MS_ONLINE_ROLE_DATA &onlineRoleData, BOOL bMasterExpAdd);

private:
    CObjectPool<MS_TEACHER_DATA>        m_TeacherPool;
    CObjectPool<MS_STUDENT_DATA>        m_StudentPool;

    typedef std::map<UINT32, MS_TEACHER_DATA*>   TEACHER_MAP;
    TEACHER_MAP         m_mapTeacher;

    typedef std::map<UINT32, MS_STUDENT_DATA*>  STUD_MAP;
    STUD_MAP            m_mapStudent;


    typedef std::map<UINT64, INT32>     CZ_MAP;
    CZ_MAP              m_mapCZ;

    // recruit 
    typedef std::list<UINT32>       RECRUIT_LIST;
    typedef RECRUIT_LIST::iterator  RECRUIT_LISTIter;
    RECRUIT_LIST            m_RecruitList[MAX_SERVER_GROUP_COUNT];
    RECRUIT_LISTIter        m_CursorRoleIter[MAX_SERVER_GROUP_COUNT];

    typedef std::list<UINT32>       SOLO_LIST;
    typedef SOLO_LIST::iterator     SOLO_LISTIter;
    SOLO_LIST               m_SoloList[MAX_SERVER_GROUP_COUNT];
    SOLO_LISTIter           m_SoloCursorIter[MAX_SERVER_GROUP_COUNT];

    CBaseList       m_TwitterList[MAX_SERVER_GROUP_COUNT];
};

BOOL LoadMaster(std::list<void*>& rResult, void* pUserData);
BOOL LoadMasterCZ(std::list<void*>& rResult, void* pUserData);

BOOL MasterCancelSendApp(MS_ONLINE_ROLE_DATA &onlineRoleData, UINT32 dwRoleID);
BOOL MasterCancelRecvApp(MS_ONLINE_ROLE_DATA &onlineRoleData, UINT32 dwRoleID);
BOOL MasterTeacherCancelAllApp(MS_ONLINE_ROLE_DATA &onlineRoleData);
BOOL MasterStudentCancelAllApp(MS_ONLINE_ROLE_DATA &onlineRoleData);

BOOL    PushRoleInfoToTeacher(UINT32 dwRoleID);

BOOL    MasterLevelUp(MS_ONLINE_ROLE_DATA &onlineRoleData);
BOOL    MasterRoleLogin(MS_ONLINE_ROLE_DATA &onlineRoleData);
BOOL    MasterRoleLogout(MS_ONLINE_ROLE_DATA &onlineRoleData);

BOOL    SyncMasterDataToGS(MS_ONLINE_ROLE_DATA &onlineRoleData);

BOOL    RoleDel(MS_ONLINE_ROLE_DATA &onlineRoleData);

INT32   GetMasterCD(INT32 nLevel);









#endif //_H_MASTER_MGR_H_



