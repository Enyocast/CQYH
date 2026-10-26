class MMOUIHandbookPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var LevelStreamingUIShow _ShowLevel;
var private transient bool _RTSet;
var private transient int _PendingRTCounter;
var NPC	_ShowNpc;
var MMOPlayer _ShowPlayer;

var int _CurClass;
var int _CurType;
var int _CurIndex;
var int _LastClass;
var int _LastType;
var int _LastIndex;
var bool _UsableOnly;

var TurnButtonStats _PlayerRotStates;
var TurnButtonStats _NpcRotStates;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

function InitWidget()
{
	_ShowLevel = GFXPlayer.GetShowLevel("PawnShowLevel_Handbook");
	_RTSet = false;
	_PendingRTCounter = -1;
}

event NPC CloneNPC(NPC Base)
{
	if (_ShowNpc == none)
	{
		_ShowNpc = base.Spawn(class'NPC', GetPC());
 		_ShowNpc.InitItems();
	}
	_ShowNpc.CloneFrom(base);
	_ShowNpc.SetPhysics(PHYS_None);
	return _ShowNpc;
}

event MMOPlayer ClonePlayer(MMOPlayer Base)
{
	if (_ShowPlayer == none)
	{
		_ShowPlayer = base.Spawn(class'MMOPlayer', GetPC());
		_ShowPlayer.InitItems();
	}
	_ShowPlayer.CloneFrom( base );
	_ShowPlayer.SetPhysics(PHYS_None);
	return _ShowPlayer;
}

native function CheckPendingRT(float deltaTime);
native final function SetShowActor(MMOActor actor, float scale);

// UC->AS
event CallUCUpdateHandbookType(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHandbookType");
}

event CallUpdateHandbookProgress(int cur, int max)
{
	ActionScriptVoid("UCUpdateHandbookProgress");
}

event CallUpdateHandbookList(GFxObject dataProvider, int typeIndex, int lineIndex, int rowIndex)
{
	ActionScriptVoid("UCUpdateHandbookList");
}

event CallUpdateHandbookInfo(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateHandbookInfo");
}

event CallSetMainPageType(bool hasAchievement)
{
	ActionScriptVoid("UCSetMainPageType");
}

event CallCanBack()
{
	ActionScriptVoid("UCCanBack");
}

final native function ASSetHandbookClass(int handbookClass);
final native function ASSetHandbookType(int selectIndex);
final native function ASClickHandbookItem(int type, int index);
final native function ASShowTips_SkillSettingActive( GFxObject mc );
final native function ASHideTips_SkillSettingActive( GFxObject mc );

final native function ASShowTips_MonsterSkill( GFxObject mc );
final native function ASHideTips_MonsterSkill( GFxObject mc );

final native function ASGotoMapPage(string mapName);
final native function ASGotoMonsterPage(string monsterName);
final native function ASCheckUseableOnly(bool useableOnly);
final native function ASSearchByKey(string key);
final native function ASBackButtonClick();

final native function ASOpenWorldMap(int mapId);
final native function ASGotoPosition(int mapId);
final native function ASPlayDesciptionSound();

final native function ASPlayerRotate(int dir);
final native function ASNpcRotate(int dir);
final native function ASReleaseRotate();
final native function ASGotoEquipPage(int itemId);
final native function PostAdvance(float deltaTime);

DefaultProperties
{
	_CurClass=0
	_CurType=0
	_CurIndex=0
	_LastClass=0
    _LastType=0
    _LastIndex=0
	_UsableOnly=false//#25527
	IsDynamicLoad=true
	DefaultVisible=false
	_PendingRTCounter=-1
	_RTSet=false
}
