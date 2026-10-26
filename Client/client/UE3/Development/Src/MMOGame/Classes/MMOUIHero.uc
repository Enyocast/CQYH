class MMOUIHero extends MMOUIBaseSlotContainer
	native(UI)
	config(UIVisibleMask);

var GFxObject heroPanel;
var String	ShowLevelName;
var LevelStreamingUIShow	ShowLevel;
var Array<int> AttributeList;

var EPlayerClass HeroClassId;
var EGenderType  HeroSex;

native function ClearUI();

// event OnShow(bool show)
// {
//  	super.OnShow(show);
// 	if(show){
// 		RefreshHero(true);
// 		//EnableCapture();
// 	}
// 	//else{
// 	//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.MoviePlayer_Hero,class'MMOUIManager'.default.Panel_Hero,false, "");
// 	//}
// }


native function EnterScene();
native function ChangeScene();

native function UpdateEquip();
native function ModelEquip();
native function SysModelEquip();
native function CreateShowLevel();
native function EnableCapture();

native function int GetSlotType();

native function RefreshAttribute();
native function RefreshInfo();
native function RefreshSlot();
native function RefreshSummon();

native function InitUIText();


native function bool OnLeftMousePress(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnLeftMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnRightMouseClick(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID,bool bDefault);
native function bool OnDragDrop(GFxObject SrcSlotMC, GFxObject DestSlotMC, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID, ESlotPanelType DestSlotType, ECONTAINER_SLOT DestContainerID, int DestSlotID);


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	InitUIText();
}



event InitOnce()
{
	super.InitOnce();

	heroPanel  = GetObject("HeroPanel_mc");
	InitUIText();
}


event RefreshHero(bool bForceUpdate)
{
	RefreshSummon();
	RefreshSlot();
	RefreshAttribute();
	RefreshInfo();
	if(bForceUpdate){
		EnableCapture();
	}
}

event CallUpdateAttribute(GFxObject Provider)
{
	ActionScriptVoid("updateAttributeData");
}

event CallUpdateInfo(GFxObject BaseInfo)
{
	ActionScriptVoid("updateInfo");
}

event CallUpdateSlot(GFxObject BaseInfoArray)
{
	ActionScriptVoid("updateSlotData");
}

event CallShowCapture(bool bShow)
{
	ActionScriptVoid("showCapture");
}

event CallShowSummon(bool bShow)
{
	ActionScriptVoid("showSummon");
}

event CallInitUIText(GFxObject UIData)
{
	ActionScriptVoid("initUIText");
}

DefaultProperties
{
	ShowLevelName="PawnShowLevel_Hero"
	IsDynamicLoad=true
	DefaultVisible=true
	HeroClassId=EPCT_None
	HeroSex=EGT_None
}
