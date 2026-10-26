class MMOUIMallFriendPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);
var GFxObject listFriend;

var GFxObject	MallGiveFriendConfirmBox;
var localized string friendName;

native function NativeInitLoad();

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	listFriend = GetObject("friendList_mc");
}

event CallSetGoodsInfo(int nGoodsID, int nNum)
{
	ActionScriptVoid("UCSetGoodsInfo");
}

event CallUpdateFriendList(GFxObject dataProvider)
{
	ActionScriptVoid("UCUpdateFriendList");
}

event CallUpdateMoney(int nMoney)
{
	ActionScriptVoid("UCMallUpdateGoldMoney");
}

final native function ASClickGiveFriendGoods(String roleName ,int nGoodsID, int nNum);

native function ConfirmMallGiveFriend(GFxObject mc);
native function CancelMallGiveFriend(GFxObject mc);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=false
}