/*
 *	 战场配置
 * */
class MMOBattleTemplate extends Object
	hidecategories(Object)
	native;

//战场类型
enum EBattle_Mode
{
	EBATL_INVALID		<DisplayName="EBATL_TYPE_INVALID">,
	EBATL_5V5		    <DisplayName="EBATL_TYPE_5V5">,
	EBATL_10V10		    <DisplayName="EBATL_TYPE_10V10">,
	EBATL_15V15		    <DisplayName="EBATL_TYPE_15V15">,
	EBATL_10V10V10		<DisplayName="EBATL_TYPE_10V10V10">,
	EBATL_20V20		    <DisplayName="EBATL_TYPE_20V20">
};

enum EBattle_Style
{
	EBS_GetCoreItem            <DisplayName="Get Flag">,
	//EBS_HuntPlayer             <DisplayName="Kill Player">,
	//EBS_HuntNpc                <DisplayName="Kill NPC">,
	//EBS_Occupy                 <DisplayName="Get territory">,
	//EBS_Guard                  <DisplayName="Guard territory">,
	//EBS_ConvoyNpc              <DisplayName="Help NPC">,
	//EBS_KeepState              <DisplayName="Keep Buff">
};

struct native BattleItemReward
{
	//物品奖励
	var() int                       ID                <DisplayName="Item ID">;
	//物品奖励数量
	var() int                       Num               <DisplayName="Item Number">;

	structdefaultproperties
	{
		ID=0
		Num=0
	}
};

struct native BattleReward
{
	//物品奖励
	var() array<BattleItemReward>   Items                <DisplayName="Items Reward(battle score)">;
	////经验奖励
	//var() int                       Exp                  <DisplayName="Exp Reward">;
	////胜利战场点数奖励
	//var() int                       WinPoints            <DisplayName="Points Reward for Win">;
	////失败战场点数奖励
	//var() int                       FaildPoints          <DisplayName="Points Reward for Faild">;
	////声望奖励
	//var() int                       FameID               <DisplayName="Fame of which(it's ID)">;
	////声望奖励点数
	//var() int                       FamePoints           <DisplayName="Fame Rewards">;

	structdefaultproperties
	{
		//Exp=0
		//WinPoints=0
		//FaildPoints=0
		//FameID=0
		//FamePoints=0
	}
};

struct native BattleScore
{
	var() int       ScoreToWin                   <DisplayName="Score To Win">;

	//var() int       GetCoreItem            <DisplayName="Get Flag Score">;
	//var() int       HuntPlayer             <DisplayName="Kill Player Score">;
	//var() int       HuntNpc                <DisplayName="Kill NPC score">;
	//var() int       Occupy                 <DisplayName="Get territory score">;
	//var() int       Guard                  <DisplayName="Guard territory score">;
	//var() int       ConvoyNpc              <DisplayName="Help NPC score">;
	//var() int       KeepState              <DisplayName="Keep Buff score">;

	//var() int       Damage1st                   <DisplayName="First damage score">;
	//var() int       Damage2nd                   <DisplayName="Second damage score">;
	//var() int       Damage3rd                   <DisplayName="Third damage score">;
	//var() int       Heal1st                     <DisplayName="First Heal score">;
	//var() int       Heal2nd                     <DisplayName="Second Heal score">;
	//var() int       Heal3rd                     <DisplayName="Third Heal score">;

	structdefaultproperties
	{
		ScoreToWin=0
		//GetCoreItem=0
		//HuntPlayer=0
		//HuntNpc=0
		//Occupy=0
		//Guard=0
		//ConvoyNpc=0
		//KeepState=0
		//Damage1st=0
		//Damage2nd=0
		//Damage3rd=0
		//Heal1st=0
		//Heal2nd=0
		//Heal3rd=0
	}
};
//战场信息
struct native BattleTemplate
{
	//战场地图名
	var() int              ID                     <DisplayName="Map ServerID">;
	//战场名字（显示用）
	var() string           DisplayName            <DisplayName="Battle Name for display">;
	//战场背景介绍
	var() string           Desc	                  <DisplayName="Battle discription">;
	//资源图编号
	var() int              IconIdx                <DisplayName="Icon Index in Flash">;
	//战场复活时间
	var() int              ReviveTime             <DisplayName="Revive Time">;
	////开启人数
	//var() int              PlayerMin              <DisplayName="Minimal player">;
	////等级限制
	//var() int              LevelLimit             <DisplayName="Level Limit">;
	//战场时间
	var() int              ContinueTime           <DisplayName="Continue Time">;
	////复活方式
	//var() int              RebownType             <DisplayName="Rebown Type">;
	////战场对战模式
	//var EBattle_Mode     Mode                   <DisplayName="Battle Mode">;

	//战场奖励
	var() BattleReward     Reward                 <DisplayName="Battle Reward">;

	////战场地图名
	//var() int              MapServerID            <DisplayName="Map ServerID">;

	//是否在随机战场中被勾选
	var bool                       IsSelected;
	
	//战场胜利条件描述
	var() string           WinDesc  	                <DisplayName="Battle Win Desc">;
	//战场得分形式描述
	var() string           ScoreDesc                    <DisplayName="Battle Score Desc">;
	////战场给分表
	var() BattleScore      Score                        <DisplayName="Battle Score">;
	//主要任务
	var() EBattle_Style    BattleStyle                  <DisplayName="Battle Style">;

	structdefaultproperties
	{
		ID=1
		DisplayName=""
		Desc=""
		IconIdx=0
		ReviveTime=30
		IsSelected=true
		WinDesc=""
		ScoreDesc=""
	}
};

var int RandomBattleMinLv                                     <DisplayName="Random Min Level">;
var int RandomBattleMinSlt                                    <DisplayName="Random Min Select">;
var int RandomBattleMaxSlt                                    <DisplayName="Random Max Select">;
var(RandomBattle) BattleTemplate  RandomBattle                              <DisplayName="Random Battle">;

var(AllBattles) array<BattleTemplate> BattleTemplateList                  <DisplayName="Battle List">;

cpptext
{
	int GetBattleTemplateCnt();
	void RevertSelected();
	FBattleTemplate *FindBattleTemplateBy( INT battleID );
	FBattleTemplate *GetBattleTemplateIn( INT idx );
	//
	INT GetBattleServerIdx( INT battleID );
}

defaultproperties
{
	RandomBattleMinLv=0
	RandomBattleMinSlt=0
	RandomBattleMaxSlt=200
}