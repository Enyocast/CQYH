class MMOUIEquipGainHintBox extends MMOUIBase
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

var GFxObject _GainedEquipIconSlot;
var GFxObject _EquipScoreTf;
var GFxObject _HintBoxMsgTf;
var GFxObject _CloseHintBtn;
var GFxObject _CheckEquipBtn;

var int PanelX;
var int PanelY;
var int PanelOrigX;
var int PanelOrigY;

var init array<OperationItemBagPos> _NewGainedEquip;

native function ItemsChanged( int bagId, int slotId );
native function OnItemSwapped( int srcConIdx, int srcSlotIdx, int dstConIdx, int dstSlotIdx );
native function ClearUI();

final native function TryShowNextOrHide();
final native function CheckNewEquipment();

//===============================================================================================================
//===============================================================================================================
//function RegisterEquipGainHintBox( MMOUIEquipGainHintBox mc )
//{
//	_EquipGainHintBox = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_EquipGainHintBox);
//}

//
//event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
//{
//	if( strHoverControllerName == "PlayerArraw_mc" || strHoverControllerName == "MapNpcView_mc" ){
//		return false;
//	}

//	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
//}

//
native function ASCheckNewEquipment();
native function ASCloseNewEquipmentHintBox();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=EquipGainHintBox
	PanelOrigX=0
	PanelOrigY=40
	IsDynamicLoad=true
	CloseOnEsc=false
}
