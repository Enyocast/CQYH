/********************************************************************
	created:	15:4:2013   15:46
	file:		guild_mgr.h
	author:		Allan Tao
	
	purpose:	GS guild management class
*********************************************************************/

#ifndef _H_GS_GUILD_MGR_H_
#define _H_GS_GUILD_MGR_H_



#include "guild_def.h"
#include "id_object_pool.h"
#include "gs_guild.h"

class  CScene;

class CGuildMgr
{
private:
    CGuildMgr();
    ~CGuildMgr();
public:
    static  CGuildMgr m_Instance_;
    static  CGuildMgr &GetInstance();

    BOOL    Init();
    BOOL    UnInit();

    CGSGuild *NewGuild(UINT32 dwGuildID);
    BOOL     DelGuild(CGSGuild *poGuild);

    CGSGuild *FindGuild(UINT32 dwGuildID);

    BOOL    AddWarRelation(UINT32 dwIntruderID, UINT32 dwDefenderID);
    GUILD_WAR_DATA *FindWarRelation(UINT32 dwIntruderID, UINT32 dwDefenderID);
    GUILD_WAR_DATA *FindWarByAttackGuildID(UINT32 dwIntruderID);
    GUILD_WAR_DATA *FindWarByDefendGuildID(UINT32 dwDefenderID);
    BOOL    DelWarRelation(UINT32 dwIntruderID, UINT32 dwDefenderID);

public:
    // Enemies can fight each other without gaining PK points
    BOOL    IsHostile(UINT32 dwGuildID, UINT32 dwTargetGuildID);
    BOOL    IsFriendly(UINT32 dwGuildID, UINT32 dwTargetGuildID);

private:
    CIDObjectPool<CGSGuild, UINT32>     m_GuildPool;

    typedef std::list<GUILD_WAR_DATA>   GS_WAR_LIST;
    GS_WAR_LIST     m_warList;

};


BOOL CloseGuildDungeonCommission(UINT32 dwSceneTemplateID, UINT32 dwSceneID);

BOOL GuildWarLockRole(CScene *poScene);

BOOL SendMSToAddRes(UINT32 dwRoleID, INT32 nType, INT32 nCount);



#endif //_H_GS_GUILD_MGR_H_




