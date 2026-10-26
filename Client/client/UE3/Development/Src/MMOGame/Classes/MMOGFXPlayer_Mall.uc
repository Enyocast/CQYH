class MMOGFXPlayer_Mall extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIMallPanel       _mallPanel;
var MMOUIMallBuyPanel    _mallBuyPanel;
var MMOUIMallFriendPanel _mallFriendPanel;
var MMOUIMallEquipRolePanel _mallEquipRolePanel;

var GFxObject	MallBuyConfirmBox;
var GFxObject	MallGiveFriendConfirmBox;
var int  GoodsID;
var int  GoodsNum;
var localized string friendName;
var TurnButtonStats TurnButton;


function RegisterMallPanel(MMOUIMallPanel mc)
{
	_mallPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Mall);
}


function RegisterFriendPanel(MMOUIMallFriendPanel mc)
{
	_mallFriendPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MallFriend);
}

function RegisterBuyGoodsPanel(MMOUIMallBuyPanel mc)
{
	_mallBuyPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MallBuyGoods);
}

function RegisterEquipRolePanel(MMOUIMallEquipRolePanel mc)
{
	_mallEquipRolePanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MallEquipRole);
}
event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	local bool res;
	res = _mallEquipRolePanel.SkipCaptureInputKey( key,  eIE, strHoverControllerName, ClickPosInMovieSpace);
	if(res == false)
		return false;
	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}
native function ASStartDrag(GFxObject SrcItemSlot, ESlotPanelType SrcSlotType, ECONTAINER_SLOT SrcContainerID, int SrcSlotID);

final native function ASClickGiveFriendGoods(String roleName ,int nGoodsID, int nNum);
final native function ASClickGiveFriend(int nGoodsID, int nNum);
final native function ASClickBuyGoods(int nGoodsID, int nNum);
final native function ASClickBtnBuyVip();
final native function ASClickBtnCheckIn();
final native function ASAddGoldMoney();
final native function ASClickMallTap(int nIndex);
final native function ASClickMallGoods(int nGoodsID);
final native function ASClickPrePage();
final native function ASClickNextPage();
final native function ASClickDropMenuHotType(int nType);
final native function ASClickDropMenuAvaibleType(int nType);
final native function ASClickSendToChat();
final native function ASClickTakeOnOff();
final native function ASClickTurnRight();
final native function ASClickTurnLeft();
final native function ASReleasTurn();

native function ConfirmMallBuy(GFxObject mc);
native function CancelMallBuy(GFxObject mc);
native function ConfirmMallGiveFriend(GFxObject mc);
native function CancelMallGiveFriend(GFxObject mc);
native function PostAdvance(float DeltaTime );
//
DefaultProperties
{
	MovieInfoStr="UI_Mall.Mall"
	Priority=5
	GoodsID = 0
	GoodsNum = 0
    bCaptureMouseInput = 1
}
