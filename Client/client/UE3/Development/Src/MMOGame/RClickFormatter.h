#ifndef _RCLICKFORMATTER_H_
#define _RCLICKFORMATTER_H_

#include "MMOPrerequisites.h"
#include "MMOFacade.h"
#include "MMOUtil.h"

class IRClickFormatter
{
public:

	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu) = 0;
};

class RClickFormatter
{
	typedef std::map<ERClickMenuType, IRClickFormatter*, M_UE3_STL_ALLOC_MAP(ERClickMenuType, IRClickFormatter*) > RClickFormatterMap;
	static RClickFormatterMap _RClickFormatterMap;

public:

	static void RegRClickFormatter( ERClickMenuType RClickType, IRClickFormatter* fmt );
	static IRClickFormatter* GetRClickFormatter( ERClickMenuType RClickType );

	static void FormatRClick( ERClickMenuType RClickType, class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_TargetInfo
//------------------------------------------------------------------------
class RClickFormatter_TargetInfo : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_TeamMember
//------------------------------------------------------------------------
class RClickFormatter_TeamMember : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_TeamMate
//------------------------------------------------------------------------
class RClickFormatter_TeamMate : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_ChatPlayer
//------------------------------------------------------------------------
class RClickFormatter_ChatPlayer : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_TeamNearby
//------------------------------------------------------------------------
class RClickFormatter_TeamNearby : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_Friend
//------------------------------------------------------------------------
class RClickFormatter_Friend : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_BattleMember
//------------------------------------------------------------------------
class RClickFormatter_BattleMember : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_FriendGroup
//------------------------------------------------------------------------
class RClickFormatter_FriendGroup : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_Attention
//------------------------------------------------------------------------
class RClickFormatter_Attention : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_Black
//------------------------------------------------------------------------
class RClickFormatter_Black : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_GuildMember
//------------------------------------------------------------------------
class RClickFormatter_GuildMember : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_GuildAlliance
//------------------------------------------------------------------------
class RClickFormatter_GuildAlliance : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_GuildEnemy
//------------------------------------------------------------------------
class RClickFormatter_GuildEnemy : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};

//------------------------------------------------------------------------
//RClickFormatter_Dungeon
//------------------------------------------------------------------------
class RClickFormatter_Dungeon : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_RankListPlayer
//------------------------------------------------------------------------
class RClickFormatter_RankListPlayer : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_RankListGuild
//------------------------------------------------------------------------
class RClickFormatter_RankListGuild : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


//------------------------------------------------------------------------
//RClickFormatter_AuctionPlayer
//------------------------------------------------------------------------
class RClickFormatter_AuctionPlayer : public IRClickFormatter
{
public:
	virtual void FormatRClick(class UMMOUIRClickMenu* RClickMenu);
};


#endif
