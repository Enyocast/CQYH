class MMOGFXPlayer_PopUpHintBox extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIEquipGainHintBox _EquipGainHintBox;

function RegisterEquipGainHintBox( MMOUIEquipGainHintBox mc )
{
	_EquipGainHintBox = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_EquipGainHintBox);
}

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

//End
DefaultProperties
{
	MovieInfoStr="UI_PopUpHintBox.PopUpHintBox"
	Priority=5
}
