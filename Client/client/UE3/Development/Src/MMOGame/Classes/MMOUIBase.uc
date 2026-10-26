class MMOUIBase extends GFxObject
	dependson(TypeDefine)
	native(UI)
	config(UIVisibleMask);

var protected native transient pointer EventAdapter{class IGameEventAdapter};

var  name FriendlyName;
var  string SWFName;
var transient MMOGFXPlayer GFXPlayer;
var bool IsDynamicLoad;
var bool IsInitialized;
var bool IsVisible;
var bool LastVisible;
var bool LastVisibleRecover;
var bool DefaultVisible;
var int CurrentDisplayPriority;
var transient MMOPlayerController ctrl;
var transient MMOPlayer Player;
var bool NeedFirstInit;
var bool CloseOnEsc;
var float AutoCheckTimer;
var bool CanMoveTop;
var bool PanelAllowFocus;
//var bool CanUIBaseFocusGained;
var bool IsTargetOutDistanceClose;
var int	 nTargetMaxDistance;
var bool IsShowWithOutTarget;

var bool CanChangeTabOnPostShow;

/*
 * 显示排斥标记，相同位的都不能同时显示，不同位的可以共存
 * 默认	            0
 * 与Bag共存	    1
 * Bag	            2
 * 对话框、技能	    1|2   对话框弹出会关闭所有其它面板
 */ 
var config int ExclusiveWithVisibilityMask;

// 自己的标记
var config int ExclusiveVisibilityMask;

/*
 * 自动同时显示标记，某个面板显示时会自动显示相同标记位的面板
 * 默认              0
 * Bag               1
 */
var config int CoexistWithVisibilityMask;

// 自己的标记
var config int CoexistVisibilityMask;

var config bool ShowInMatinee;

native function ClearUI();

native function NativeInitLoad();

event InitLoadOld(name inFrndName, MMOGFXPlayer pl)
{
	`log("这里也是不需要的调用，注意去掉相关代码:" @ self @ inFrndName);
}


event InitLoad(MMOGFXPlayer pl)
{
	//FriendlyName = FrndName; // move to defautl properties
// 	if(inFrndName != '')	
// 	{
// 		`log("貌似还有在InitLoad中传了名字过来的，需要修正代码:" @ self @ string(inFrndName));
// 	}

	GFXPlayer = pl;
	ctrl = MMOPlayerController(GetPC());
	if(none != ctrl)
	{
		Player = MMOPlayer( ctrl.Pawn );
	}
	else
	{
		`log("MMOUIBase InitLoad ctrl load fail!");
		Player = none;
	}

	SetString("PanelName", string(FriendlyName));
	SetDistanceTick(GFXPlayer); // TODO：检查这个的合理性

	NativeInitLoad();
}
event SetDistanceTick(MMOGFXPlayer pl)
{
	pl.OnPostAdvance = TickForTestInteractNPCDistance;
}

final native function MMOUIBase FindUIPanel(name inFriendlyName);

native final function NativeShow(bool show);

function ShowUI(name inFriendlyName, optional bool inShow=true)
{
	GFXPlayer.ShowUI(inFriendlyName, inShow);
}

function ToggleShowUI(name inFriendlyName)
{
	GFXPlayer.ToggleShowUI(inFriendlyName);
}

event CallSetPanelText( GFxObject data )
{
	ActionScriptVoid("SetPanelText");
	
}

event CallSetFocusMc(String mc1,String mc2,String mc3,String mc4)
{
	ActionScriptVoid("SetFocusMc");
}

native final function ChangeVisible();
// {
// 	IsVisible = GetBool("visible");
// 	Show(!IsVisible);
// }
native final function bool GetVisible();

event RemoveChild( GFxObject tChild )
{
	ActionScriptVoid("removeChild");
}

//native final function Show(bool V);

// event OnShow(bool show)
// {
// 
// }

event InitOnce()
{
	NativeInitOnce();

	InitWidget();
}

native function NativeInitOnce();

function InitWidget()
{
}

// function OnChangeScene()
// {
// }

//native function UnitWidget();
// {
// 	Show(DefaultVisible);
// }

native final function Item FindItemTemplate(ECONTAINER_SLOT ContainerID, int SlotID);
native final function Item FindItemTemplateByID(int ItemTemplateID);

native function ToogleVisible();

native function OnShutDown();
// native function PlayerHPChange(int NewHP, int MaxHP);
// native function PlayerMPChange(int NewMP, int MaxMP);
native function PlayerLevelChange( int lastLv , int newLv );
native function PlayerPkValueChange( int PkValue );
native function OtherPlayerPkValueChange( MMOPlayer pl, int PkValue );
native function PlayerPkModeChange( int PkMode );
native function OtherPlayerPkModeChange( MMOPlayer pl,int PkMode );
native function PlayerTitleChange( int TitleID );
native function OtherPlayerTitleChange( MMOPlayer pl,int TitleID );
native function BagSlotChange( INT BagId,INT SlotId );
native function PlayerAttributeChange( INT AtrrId, INT inValue );
native function PlayerExpChange( INT CurrentExp, INT MaxExp,INT ChangeExp );
native function PlayerMoneyChange(EMONEY_TYPE MoneyType,  int DeltaMoney);
native function NPCHpChange( NPC npc , int hp );
native function TargetActorChange( BYTE type, MMOActor actor );
native function OtherPlayerHpChange( MMOPlayer pl ,int hp );
native function OtherPlayerMpChange( MMOPlayer pl ,int mp );
//native function UpdateMyTeam();
native function UpdateTeamMate( int UIPos , int Pos );
native function UpdateMyFriend();
//native function UpdateFriendGroup( int GroupId );
//native function SetFriendItemValue(INT GroupID,INT pos,String PlayerName,INT Lv,String Carrer,String Location,String Sign,INT RoleId, int Status);
//native function AddedAttentionBy( int RoleId , string RoleName );

native function FriendChatMsg( int RoleId , string Content );
native function PlayerBaseInfoChange();
native function SkillSlotChange();

native function EnterScene();
native function ChangeScene();
native function EnterLogin();

//zhaojun@snda
native function OnFocusGained();
native function OnFocusLost();
native function bool CanFocusGained();
native function bool CanFocusLost();
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

//~zhaojun@snda
native function bool OnEsc();

native function SoldItemChange();
native function ItemChange(int ContainerID, int SlotID);
native function ItemDelete(int ContainerID, int SlotID);
native function PlayerLevelUp(int NewLv);
native function UnReadFriendChatMsgChange();
native function AddNewNpcData( NPC npc );


native function UpdateTeamContent();
//native function UpdateAllTeamMate();
//native function UpdateTeamMateNum( int MateNum );

native function OnStallStateChange(EEStallState state);

//add by jimZhang@snda.com， chenge screen Pos to gfx pos
// native function Vector GetGfxOffsetVector(Vector Pos,float CavWidth,float CavHeight);
//native function bool GetlockMouseCursorForUI();

native function UpdatePlayerReputation( MMOPlayer Pl , int ForceID, int newReputation, int lastReputation );

native function TickForTestInteractNPCDistance(float deltaTime);


event int GetWidth()
{
	return ActionScriptInt("UCGetWidth");
}

event int GetHeight()
{
	return ActionScriptInt("UCGetHeight");
}

event CallShowHelperButton(bool bShow)
{
	ActionScriptVoid("ShowHelperButton");
}

event CallAsToGrayMc( GFxObject mc, bool isToGray )
{
	ActionScriptVoid("GrayChildMc");
}

event ShowAsMode()
{
	ActionScriptVoid("UCShowMode");
}

event DismissMode()
{
	ActionScriptVoid("UCDismissMode");
}

event ShowPanel(bool show, int panelPriority )
{
	if( panelPriority < 0 ){
		panelPriority = CurrentDisplayPriority;
	}
	else{
		CurrentDisplayPriority = panelPriority;
	}
	ActionScriptVoid("UCShow");

	//`log("============= ShowPanel" @ self @ show @ panelPriority);
}


native function SetItemSlotData( GFxObject mc , Item tItem, ESlotPanelType SlotType, optional ECONTAINER_SLOT ContainerID = E_CONSLOT_MAX, optional int SlotID = -1, optional EItemSlotState inISS = ISS_Normal );
//native function ASStartDrag(GFxObject srcItemSlot, ESlotPanelType srcSlotType, ECONTAINER_SLOT srcContainerID, int srcSlotID); // moved


DefaultProperties
{
	DefaultVisible=false
	IsDynamicLoad=false
	IsInitialized=false
	IsVisible=false
	LastVisible=false
	LastVisibleRecover=false
	FriendlyName="UnNamed"
	SWFName=""
	NeedFirstInit=true
	CloseOnEsc=true
	CanMoveTop=false
	PanelAllowFocus=true
	IsTargetOutDistanceClose = false
	nTargetMaxDistance = 2500
	IsShowWithOutTarget = false
	CanChangeTabOnPostShow=true
}
