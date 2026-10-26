class MMOUIGuildMainPanel extends MMOUIBase
	native(UI);

var GFxObject ExpelConfirmBox;
var GFxObject QuitConfirmBox;
var bool IsShowOnlineMember;
var string _WarTargetName;
var GFxObject ChallengeConfirmBox;
var int _ShowPage;
var int _ShowSubPage;
var GFxObject _AllyCancelConfirmBox;
var GFxObject _ContributeConfirmBox;

native function PlayerMoneyChange(EMONEY_TYPE MoneyType, INT DeltaMoney);

native function ReplyAgreeExpel(GFxObject mc);
native function ReplyRefuseExpel(GFxObject mc);

native function ReplyAgreeQuit(GFxObject mc);
native function ReplyRefuseQuit(GFxObject mc);

native function AgreeChallengeNow(GFxObject mc);
native function RefuseChallengeNow(GFxObject mc);

native function AgreeAllyCancel(GFxObject mc);
native function RefuseAllyCancel(GFxObject mc);

native function AgreeContribute(GFxObject mc);
native function RefuseContribute(GFxObject mc);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

// UC->AS
event CallSetWindowTitle(string title)
{
	ActionScriptVoid("UCSetWindowTitle");
}

event CallInitGuild(bool hasGuild)
{
	ActionScriptVoid("UCInitGuild");
}

event CallUpdateGuildFullMemberList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildFullMemberList");
}

event CallUpdateGuildPendingMemberList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildPendingMemberList");
}

event CallUpdateGuildBaseInfo(GFxObject object)
{
	ActionScriptVoid("UCUpdateGuildBaseInfo");
}

event CallUpdateGuildNotice(String notice)
{
	ActionScriptVoid("UCUpdateGuildNotice");
}

event CallUpdateGuildEvents(String events)
{
	ActionScriptVoid("UCUpdateGuildEvents");
}

event CallUpdateGuildMoneyEvents(String events)
{
	ActionScriptVoid("UCUpdateGuildMoneyEvents");
}

event CallUpdateGuildAllyList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildAllyList");
}

event CallUpdateGuildEnemyList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildEnemyList");
}

event CallUpdateGuildApplyAllyList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildApplyAllyList");
}

event CallUpdateGuildRights(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildRights");
}

event CallUpdateGuildStorageRights(GFxObject dataProvider, string tips)
{
	ActionScriptVoid("UCUpdateGuildStorageRights");
}

event CallUpdateGuildStorageState(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildStorageState");
}

event CallUpdateGuildSalary(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateGuildSalary");
}

event CallUpdateContributeInfo(int maxMoney, string intro)
{
	ActionScriptVoid("UCUpdateContributeInfo");
}

event CallUpdateGuildWarInfo(GFxObject object)
{
	ActionScriptVoid("UCUpdateGuildWarInfo");
}

event CallUpdateGuildWarCD(string time)
{
	ActionScriptVoid("UCUpdateGuildWarCD");
}

event CallUpdateForeignApplyConsume(String money)
{
	ActionScriptVoid("UCUpdateForeignApplyConsume");
}

event CallUpdateGuildWarSearchState(GFxObject object)
{
	ActionScriptVoid("UCUpdateGuildWarSearchState");
}

event CallUpdateGuildWarSearchInfo(GFxObject object)
{
	ActionScriptVoid("UCUpdateGuildWarSearchInfo");
}

event CallUpdateGuildIntroduce(String intro)
{
	ActionScriptVoid("UCUpdateGuildIntroduce");
}

event CallShowGuildMainPage(int page, int subPage)
{
	ActionScriptVoid("UCShowGuildMainPage");
}

event CallInitShowOnlineMember()
{
	ActionScriptVoid("UCClear");
}

event CallUpdateViewMoreHistoryState(bool enable)
{
	ActionScriptVoid("UCSetMoreButtonState");
}

event CallUpdateGuildActiveList(GFxObject object)
{
	ActionScriptVoid("UCUpdateGuildActive");
}

event CallUpdateGuildActiveListItem(GFxObject object)
{
	ActionScriptVoid("UCGuildActiveOpenData");
}

event CallShowActiveOpenConfirm(GFxObject object)
{
	ActionScriptVoid("UCShowActiveOpenConfirm");
}

event CallHideActiveOpenConfirm()
{
	ActionScriptVoid("UCHideActiveOpenConfirm");
}

event CallEnableGuildWar(bool enableGuildWar)
{
	ActionScriptVoid("UCUpdateGuildWarButtonState");
}

// 公会查看
native final function ASViewGuild();
// 更新申请列表
native final function ASUpdateGuildPendingMemberList();
// 同意加入公会
native final function ASAgreeToJoin(int id);
// 拒绝加入公会
native final function ASRefuseToJoin(int id);
// 资源捐献
native final function ASContribute(int type, int count);
// 更改通告
native final function ASChangeNotice(String notice);
// 更改宣言
native final function ASChangeAnnounce(String announce);
// 查看更多公会事件
native final function ASViewMoreEvents();
// 招募成员
native final function ASInviteMember(String roleName);
native final function ASSortMember(int type, bool isUp);
// 驱逐成员退出公会
native final function ASExpelMember(int id);
// 更改职位
native final function ASChangePost(int roleId, int post);
// 是否显示在线成员
native final function ASShowOnlineMember(bool isShow);
// 上线成员通知
native final function ASOnlineMemberNotify(bool notify);
// 族长禅位
native final function ASLeaderDemise(String roleName);
// 公会解散
native final function ASDisbandGuild(String text);
// 退出公会
native final function ASQuitGuild();
// 更新公会权限显示
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
native final function ASAllianceRightClick(int posX, int posY, int guildId);
native final function ASGuildEnemyRightClick(int posX, int posY, int guildId);
// 公会战
native final function ASChallenge(String guildName);
native final function ASSearchGuild();
native final function ASSetShowPage(int page, int subPage);
// 公会活动
native final function ASGuildActivityClickOpen(int activityId);
native final function ASGuildActivitySumitOpen(int activityId);

DefaultProperties
{
	_ShowPage=1
	_ShowSubPage=1
	IsDynamicLoad=true
	DefaultVisible=false
	IsShowOnlineMember=false
}
