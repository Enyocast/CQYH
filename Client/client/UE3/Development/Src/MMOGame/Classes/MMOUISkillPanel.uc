/********************************************************************
	Created:	2012/06
	Filename: 	MMOUISkillPanel
	file ext:	uc
	Author:		hemu@snda
	Purpose:	MMOUISkillPanel 技能界面，包含以下4块  
				-Console 技能总览
				-Active  主动技能
				  -Rune 符文充能、激活
				  -SkillUp 技能熟练度升级：心练、魂练
				-Passive 被动技能
				-Avarta  Avarta技能
*********************************************************************/

class MMOUISkillPanel extends MMOUIBase
	dependson(UIKeyMapManager)
	native(UI)
	config(UIVisibleMask);

enum ESkill_PageType
{
	ESkill_Console,
	ESkill_Active,
	ESkill_Passive,
	ESkill_Avarta,
};

//var MMOPlayer           MainPlayer;
//var MMOPlayerController PC;
//var array<MMOAbility>   AllAbilities;
//var UIKeyMapManager     KeyMapManager;

//var ESkill_PageType CurPageType;

//var int NowActivePageNum;
//var int NowPassivePageNum;
//var int NowAvartaPageNum;
//var int NowAvartaRunePageNum;

//var int TotalActivePageNum;
//var int TotalPassivePageNum;
//var int TotalAvartaPageNum;
//var int TotalAvartaRunePageNum;

//var int MaxActiveModifyCount;
//var int MaxPassiveModifyCount;
//var int MaxAvartaModifyCount;

//var int ActiveSlotCount;
//var int ActiveRuneCount;
//var int PassiveSlotCount;
//var int AvartaSlotCount;
//var int AvartaRuneCount;

////==================ActiveModify()================================ 
//var array<int> ActiveRealSlotList;
//struct native sCurrentActive
//{
//	//var int ItemId; //0~2
//	var int ActiveId;
//	var bool IsChanged;
//};
//var array<sCurrentActive>  RealActives;
//var array<sCurrentActive>  CurrentActives;
//struct native sAllActive
//{
//	var int ActiveId;
//	var bool IsEquiped;
//};
//var array<sAllActive>  AllActives;
//var int CurrentActiveSlot;
//var int CurrentSelectedActiveSlot;
//var int CurrentSelectedActiveId;
//var int CurrentSelectedActiveRuneSlot;

//var int CurrentSelectedAvartaSlot;
//var int CurrentSelectedAvartaId;
//var int CurrentSelectedAvartaRuneSlot;

//var int NowRequestNormalPracticeActiveId;
//var int NowNormalPracticeActiveId;
//var int NowNormalPracticeType;
//var int NowNormalPracticeProgress;

//var int NowRequestFastPracticeActiveId;
//var int NowFastPracticeActiveId;
//var int NowFastPracticeType;
//var int NowFastPracticeProgress;
//var int NowPracticeType;
//var bool IsInFastPractice;

//var string StrTimeLeft;

//enum SkillPracticeType
//{
//	SkillPT_None,
//	SkillPT_Noraml,
//	SkillPT_Fast
//};
//var bool IsRequestCloseNormalSkillPractice;
//var bool IsRequestCloseFastSkillPractice;
//var bool HasAskStopSkillPractice;
////==================PassiveModify()================================ 
//struct native sCurrentPassive
//{
//	//var int ItemId; //0~2
//	var int PassiveId;
//	var bool IsChanged;
//};
//var array<sCurrentPassive>  RealPassives;
//var array<sCurrentPassive>  CurrentPassives;
//struct native sAllPassive
//{
//	var int PassiveId;
//	var bool IsEquiped;
//};
//var array<sAllPassive>  AllPassives;
//var int CurrentPassiveSlot;

//// QTE技能  命名正好与Avatar区分开故沿用资源名 
////==================AvartaModify()================================ 
//struct native sCurrentAvarta
//{
//	//var int ItemId; //0~2
//	var int AvartaId;
//	var bool IsChanged;
//};
//var array<sCurrentAvarta>  RealAvartas;
//var array<sCurrentAvarta>  CurrentAvartas;
//struct native sAllAvarta
//{
//	var int AvartaId;
//	var bool IsEquiped;
//};
//var array<sAllAvarta>  AllAvartas;
//var int CurrentAvartaSlot;
//var const float UpdateInterval;
//var float ElapsedTime;


//native function     PostAdvance(float DeltaTime);
////更新心练面板
//native final  function     UpdateNormalPractice( );

//native final  function 	int GetRealActiveRealSlotId(int activeSlotId );
//native final  function 	SendEquipActive(int activeSlotId,int abilityId );
//native final  function 	SendEquipPassive(int passiveSlotId,int abilityId );
//native final  function 	SendEquipAvarta(int avartaSlotId,int abilityId );

//native function         SkillSlotChange();
//native final  function 	RefreshAll( );
//native final  function 	SendEquipActiveRune( int activeSlotId, int runeSlotId);
//native final  function 	SendEquipAvartaRune( int avartaSlotId, int runeSlotId);
//native final  function 	SendActivateRune( int inSpellId, int runeSlotId);
//native final  function 	RuneActivate( int wSpellID, int byRuneSlot, int byDurabilityType, int nDurability );
//native final  function 	RuneDurSync( int wSpellID, int byRuneSlot, int byDurabilityType, int nDurability );
//native final  function 	RuneEquip( int bySlot, int wSpellID, int byRuneSlot );
			
////相关检测 防止Crash
//native final  function bool Validate();

////重新登录后 重置状态
//native function EnterLogin();

//event RefreshData()
//{
//	RefreshCurrentSpell();
//	//RefreshActiveModify();
//}

////进行初始化
//event InitLoad(MMOGFXPlayer pl)
//{
//	super.InitLoad(pl);
//	//_UIPlayer = pl;	
//	//@test
//	`log("MMOUISkillPanel : InitLoad()");
//	IniData();

//	ActiveRealSlotList.Add( ActiveSlotCount );
//	ActiveRealSlotList[ 0 ] = ECK_MouseL;
//	ActiveRealSlotList[ 1 ] = ECK_MouseR;
//	//变化太多 乖乖先写定s
//	ActiveRealSlotList[ 2 ] = ECK_Slot1;
//	ActiveRealSlotList[ 3 ] = ECK_Slot2;
//	ActiveRealSlotList[ 4 ] = ECK_Slot3;
//	ActiveRealSlotList[ 5 ] = ECK_Slot4;

//	CurrentActives.Add( ActiveSlotCount );
//	RealActives.Add( ActiveSlotCount );

//	CurrentPassives.Add( PassiveSlotCount );
//	RealPassives.Add( PassiveSlotCount );

//	CurrentAvartas.Add( AvartaSlotCount );
//	RealAvartas.Add( AvartaSlotCount );

//	class'MMOUIManager'.static.SetReplaceHotSkillDelegate( ReplaceHotSkill );
//}

////Tab键直接切换左右键技能
//native final  function ReplaceHotSkill();

//event IniData()
//{
	
//	`log("==============================MMOUISkillPanel::IniData() Opended=================================================");
//	PC = MMOPlayerController( GetPC() );
//	MainPlayer = MMOPlayer( PC.Pawn );
//	//ThisWorld = GetPC().WorldInfo;
//	//`log("worldinfo:"$ThisWorld.GetMapInfo() );
//	KeyMapManager = MMOGame(PC.WorldInfo.Game).KeyMapManager;
//	PageJump( ESkill_Console );
//	GetObject("SpellConsole").SetVisible( true );
//	GetObject("ActiveModify").SetVisible( false );
//	GetObject("PassiveModify").SetVisible( false );
//	GetObject("AvartaModify").SetVisible( false );

//}

//native function NativeInitOnce();

//native final  function SetLockedState( int slotId, GFxObject tObj, int uiSlot );
////刷新整体面板
//native final  function RefreshCurrentSpell();

//event SetItem( GFxObject mc,int quantity,string IconName,int ItemIndex,optional string Type="", optional int itemColor = 0  )
//{
//	GFXPlayer.CallSetItemData(mc,quantity,IconName,ItemIndex, ESPType_SkillPanel, Type,itemColor );
//}

////背包改变响应
//native function BagSlotChange( INT BagId,INT SlotId );
////刷新当前页面
//native final  function RefreshCurrentPage( );
////刷新页面
//native final  function RefreshPage( ESkill_PageType tSPT );
////执行相关的变量初始化 
//native final  function PageJump( ESkill_PageType tSPT );
////PlayerMoneyChange
//native function PlayerMoneyChange(EMONEY_TYPE MoneyType, int Money, int OldMoney);

////==================================================RefreshActiveModify()====================================================== 

////设置ActiveBtn
//native final  function SetSpellBtnByActiveId(GFxObject tObj,int SlotId,int abilityId,bool isSubCtrl = false );
////选择当前CurrentActiveSlot
//native final  function SetCurrentActive( int activeSlotId );
////RefreshActiveModify
//native final  function RefreshActiveModify();
////选择CurrentActiveSlot 切换成的对应 AllActives( abilityId ) 的 ActiveId
//native final  function SelectActive( int tSlotId,int abilityId );

////符文,技能点等刷新显示
//native final  function OnSelecteActiveChanged( int abilityId );
////判断当前符文是否能被激活
//native final  function bool CanActiveRune( MMOAbility tRune );
////设置RuneBtn
//native final  function SetRuneBtnByAbility(MMOAbility tRune,int iRuneSlot );
////点击装配符文
//native final  function EquipRune( int runeSlotId);
////点击激活符文
//native final  function ActivateRune( int runeSlotId);
////取消符文装配
//native final  function CleanRune();
///*
////符文图标hover 
//native final  function OnRuneBtnHover( int runeSlotId );*/

////Active是否已经被装备
//native final  function int IsActiveAlreadyEquiped( int abilityId );
////确认提交Modify
//native final  function ConfirmActive( );
//native final  function ActiveLastPage();
//native final  function ActiveNextPage();

////技能升级
////点击弹出面板
//native final  function ASClickNormalPractice( bool IsToggle = true );
//native final  function ASClickFastPractice( bool IsToggle = true );
////点击开始升级技能
//native final  function ASStartNormalPractice(  );
//native final  function ASStartFastPractice(  );
////选择心练类型
//native final  function ASChooseNormalParcticeType( int NPType );
////选择魂练类型
//native final  function ASChooseFastPracticeType( int FPType );
////魂练用药
//native final  function ASUseFastPracticeItem( int FPItem );
////中止升级技能
//native final  function ASStopPractice( int inActiveId );
////中止并关闭技能升级面板
//native final  function ASStopPracticeAndClose( int inActiveId,SkillPracticeType spt );
////中止技能升级确认
//native final  function StopSkillPracticeOk(GFxObject mc);
////中止技能升级取消
//native final  function StopSkillPracticeCancel(GFxObject mc);

////开始技能升级
//native final  function NetStartSkillPractice(int inActiveId,int byPracticeType,int	nInterval,int nEndTime );
////结束技能升级
//native final  function NetStopSkillPractice(int inActiveId);
////技能熟练度提醒
//native final  function NetSkillProgressChange( int inActiveId,int nProgress );
////技能升级提示
//native final  function NetSkillLevelUp( int inActiveId,int byLevel );
////技能升级提示
//native final  function NetSkillPointChangeNotify( );
////技能升级功能开启
//native final  function EnableSkillUp( bool isEnable = true );

////==================================================RefreshPassiveModify()====================================================== 

////设置PassiveBtn
//native final  function SetSpellBtnByPassiveId(GFxObject tObj,int SlotId,int abilityId,bool isSubCtrl = false );
////选择当前CurrentPassiveSlot
//native final  function SetCurrentPassive( int passiveSlotId );
////RefreshPassiveModify
//native final  function RefreshPassiveModify();
////选择CurrentPassiveSlot 切换成的对应 AllPassives( abilityId ) 的 PassiveId
//native final  function SelectPassive( int tSlotId,int abilityId );
////Passive是否已经被装备
//native final  function int IsPassiveAlreadyEquiped( int abilityId );
////确认提交Modify
//native final  function ConfirmPassive( );

////==================================================RefreshAvartaModify()====================================================== 

////设置AvartaBtn
//native final  function SetSpellBtnByAvartaId(GFxObject tObj,int SlotId,int abilityId,bool isSubCtrl = false );
////设置AvartaBtn
//native final  function SetSpellBtnByAvarta(GFxObject tObj,int SlotId,MMOAbility tAvarta,bool isSubCtrl = false,bool isRuneCtrl = false );
////选择当前CurrentAvartaSlot
//native final  function SetCurrentAvarta( int avartaSlotId );
////RefreshAvartaModify
//native final  function RefreshAvartaModify();
////选择CurrentAvartaSlot 切换成的对应 AllAvartas( abilityId ) 的 AvartaId
//native final  function SelectAvarta( int tSlotId,int abilityId );
////刷一遍符文
//native final  function OnSelecteAvartaChanged( int  abilityId );
////abilityId 号技能装配了第 tSlotId 个符文
//native final  function SelectAvartaRune( int tSlotId,int abilityId );
////Avarta是否已经被装备
//native final  function int IsAvartaAlreadyEquiped( int abilityId );
////确认提交Modify
//native final  function ConfirmAvarta( );
////翻页
//native final  function AvartaLastPage();
//native final  function AvartaNextPage();
//native final  function AvartaRuneLastPage();
//native final  function AvartaRuneNextPage();

//DefaultProperties
//{
//	IsDynamicLoad=true
//	MaxActiveModifyCount=10
//	MaxPassiveModifyCount=20
//	MaxAvartaModifyCount=5
//	ActiveSlotCount=6
//	ActiveRuneCount=5
//	AvartaRuneCount=10
//	PassiveSlotCount=3
//	AvartaSlotCount=3
//	IsRequestCloseNormalSkillPractice=false
//	IsRequestCloseFastSkillPractice=false
//	HasAskStopSkillPractice=false
//	UpdateInterval=0.06 //Second
//	ElapsedTime=0
//}
