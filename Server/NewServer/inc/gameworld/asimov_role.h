//////////////////////////////////////////////////////////////////////////
//  Allan Tao[11.10.2014] 
// 
//////////////////////////////////////////////////////////////////////////


#ifndef _H_ASIMOV_ROLE_H_
#define _H_ASIMOV_ROLE_H_


#include "guild_def.h"
#include "achievement_def.h"

#ifndef _ROBOT

class CAsimovRole
{
public:
    CAsimovRole()       {}
    ~CAsimovRole()      {}

    //BOOL    Init(CRole *poRole)      { return TRUE; }
    //BOOL    UnInit()    { return TRUE; }
};


#else

class CRole;


class CAsimovRole
{
public:
    CAsimovRole();
    ~CAsimovRole();

    BOOL    Init(CRole *poRole);
    BOOL    UnInit();
    
    
    UINT32  RandShieldRole();
    
    INT32   RandCompleteAchievement();
    BOOL    AddCompleteAchievement(INT32 nAchievementID);
    BOOL    DelCompleteAchievement(INT32 nAchievementID);


    BOOL    DelGuildApp(UINT32 dwGuildID);
    void    SetInviteGuildRoleID(UINT32 dwGuildID);
    UINT32  GetInviteGuildRoleID();
    void    ClearViewList();
    BOOL    AddViewList(UINT32 dwGuildID);

    INT32   GetViewListNum();
    UINT32  GetViewListGuildIDByIndex(INT32 nIndex);



    BOOL    LuaClearGuildApp();
    BOOL    LuaIsInGuildAppList(UINT32 dwGuildID);
    INT32   LuaGetGuildAppNum();
    UINT32  LuaGetGuildAppByIndex(INT32 nIndex);
    BOOL    LuaAddGuildApp(UINT32 dwGuildID);
    BOOL    LuaDelGuildApp(UINT32 dwGuildID);


private:
    CRole               *m_poRole;

    //////////////////////////////// achievement /////////////////////////////
    INT32               m_nCompleteAchievementNum;
    INT32               m_arrAchievementList[ACHIEVEMENT_MAX];
    //////////////////////////////// achievement /////////////////////////////

    //////////////////////////////// guild ///////////////////////////////////
    INT32               m_nGuildAppNum;
    UINT32              m_dwGuildApp[10];

    UINT32              m_dwInviteGuildRoleID;

    INT32               m_nValidViewGuildNum;
    UINT32              m_arrViewGuildIDList[MAX_VIEW_GUILD_LIST_COUNT];
    ///////////////////////////// guild end //////////////////////////////////

};


#endif //_ROBOT











#endif // !_H_ASIMOV_ROLE_H_






