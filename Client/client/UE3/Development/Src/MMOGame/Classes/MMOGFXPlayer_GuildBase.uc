class MMOGFXPlayer_GuildBase extends MMOGFXPlayer
	native(UI);

var MMOUIGuildCreatePanel _GuildCreatePanel;
var MMOUIGuildViewPanel _GuildViewPanel;
var MMOUIGuildMainPanel _GuildMainPanel;
var MMOUIGuildWarehouse _GuildWarehouse;
var MMOUIGuildInstructionPanel _GuildInstructionPanel;
var MMOUIGuildWarViewPanel _GuildWarViewPanel;
var MMOUISabacEnrollViewPanel _SabacEnrollViewPanel;

function ASRegisterGuildCreatePanel(MMOUIGuildCreatePanel mc)
{ 
	_GuildCreatePanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_Create);
}

function ASRegisterGuildViewPanel(MMOUIGuildViewPanel mc)
{ 
	_GuildViewPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_View);
}

function RegisterGuildWarehouse(MMOUIGuildWarehouse mc)
{ 
	_GuildWarehouse = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_Warehouse);
}

function ASRegisterGuildMainPanel(MMOUIGuildMainPanel mc)
{ 
	_GuildMainPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_Main);
}

function ASRegisterGuildInstructionPanel(MMOUIGuildInstructionPanel mc)
{ 
	_GuildInstructionPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_Instruction);
}

function ASRegisterGuildWarViewPanel(MMOUIGuildWarViewPanel mc)
{ 
	_GuildWarViewPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_WarView);
}

function ASRegisterSabacEnrollViewPanel(MMOUISabacEnrollViewPanel mc)
{ 
	_SabacEnrollViewPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Guild_SabacEnroll);
}

native function PostAdvance( float dt );

native final function ShowGuildCreatePanel();
native final function ShowGuildViewPanel();
// 创建家族
native final function ASCreateGuild(String guildName, String guildAnnounce);
native final function ASInputError();

// 家族查看
native final function ASViewGuild();
native final function ASUpdateGuildViewInfo(int id);
// 家族查找
native final function ASFindGuild(bool isId, String content);
// 翻页
native final function ASPageUp();
native final function ASPageDown();
// 仓库
native final function ASGuildWarehouseMore();
native final function ASGuildWarehouseUpdate();
native final function ASGuildWarehouseTab( int tabID );
// 申请加入家族
native final function ASApplyForJoint(int id);
// 更新申请列表
native final function ASUpdateGuildPendingMemberList();
// 同意加入家族
native final function ASAgreeToJoin(int id);
// 拒绝加入家族
native final function ASRefuseToJoin(int id);
// 资源捐献
native final function ASContribute(int type, int count);
// 更改通告
native final function ASChangeNotice(String notice);
// 更改宣言
native final function ASChangeAnnounce(String announce);
// 查看更多家族事件
native final function ASViewMoreEvents();
// 招募成员
native final function ASInviteMember(String roleName);
native final function ASSortMember(int type, bool isUp);
// 驱逐成员
native final function ASExpelMember(int id);
// 更改职位
native final function ASChangePost(int roleId, int post);
// 是否显示在线成员
native final function ASShowOnlineMember(bool isShow);
// 上线成员通知
native final function ASOnlineMemberNotify(bool notify);
// 族长禅位
native final function ASLeaderDemise(String roleName);
// 家族解散
native final function ASDisbandGuild(String text);
// 退出家族
native final function ASQuitGuild();
// 更新家族权限显示
native final function ASUpdateGuildRights(int post);
// 更新仓库权限显示
native final function ASModifyGuildStorageRights(int post, GFXObject rights);
native final function ASUpdateGuildStorageRights(int post);
// 俸禄分配
native final function ASDistributeSalary(GFXObject percent);
native final function ASApplyAlly(String guildName, int timeType);
native final function ASApplyEnemy(String guildName, int timeType);
native final function ASAgreeAlly(int id);
native final function ASRefuseAlly(int id);
native final function ASFullMemberRightClick(int posX, int posY, int roleId);
native final function ASForeignApplyDayType(int foreignType, int dayType);

// 家族战
native final function ASChallenge(String guildName);
native final function ASMatchChallenge(int id);
native final function ASSearchGuild();
native final function ASChallengeConfirm(int guildId);

DefaultProperties
{
	MovieInfoStr="UI_GuildBaseWidget.GuildBaseWidget"
	Priority = 5
}
