class MMOUIDurabilityShowing extends MMOUIBase
	native(UI);

enum EEquipState
{
	EEquipDurSta_Normal,
	EEquipDurSta_Yellow,
	EEquipDurSta_Red
};

enum EEquipDurComp
{
	EEquipDurComp_MAIN_HAND,
    EEquipDurComp_HEAD,
    EEquipDurComp_SHOULDER,
    EEquipDurComp_BODY,
    EEquipDurComp_LEG,
    EEquipDurComp_ARM,
    EEquipDurComp_WAIST,
    EEquipDurComp_FOOT,
    EEquipDurComp_BACK,
    EEquipDurComp_AVATAR_NoUsed,
    EEquipDurComp_NECK,
    EEquipDurComp_FINGER,
    EEquipDurComp_WRIST
};

var GFxObject Component_MAIN_HAND;
var GFxObject Component_HEAD;
var GFxObject Component_SHOULDER;
var GFxObject Component_BODY;
var GFxObject Component_LEG;
var GFxObject Component_ARM;
var GFxObject Component_WAIST;
var GFxObject Component_FOOT;
var GFxObject Component_BACK;
var GFxObject Component_NECK;
var GFxObject Component_FINGER;
var GFxObject Component_WRIST;

var int HasLowDurabilityEquip;
var int PanelWidth;
//
event UCCallInitAllComponents()
{
	ActionScriptVoid("InitAllComponents");
}

//
event UCCallSetComponentState( int equipDurCompID, int curState )
{
	ActionScriptVoid( "SetComponentState" );
}

//===============================================================================================================
//===============================================================================================================
native function bool SkipCaptureInputKey( string key, EInputEvent eIE, string strHoverControllerName, Vector2D ClickPosInMovieSpace);

native function ASHintDurabilityDetail( GFxObject mc );
native function ASHideDurabilityDetail();
//===============================================================================================================
//===============================================================================================================

defaultproperties
{
	//FriendlyName=DurabilityShowing
	HasLowDurabilityEquip=0
	PanelWidth=105
}