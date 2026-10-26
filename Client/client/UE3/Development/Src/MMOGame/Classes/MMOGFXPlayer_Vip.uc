class MMOGFXPlayer_Vip extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIVip _VipPanel;

function RegisterVIPPanel( MMOUIVip mc )
{
	_VipPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Vip );
}

//
native function ASBuyVipLevel( int level );
native function ASBugYuanBao();
native function ASVIPTips( GFxObject hintMc );
native function ASHideVIPTips();
native function ASVipShopClick(int type);

//End
DefaultProperties
{
	MovieInfoStr="UI_Vip.VipWidget"
	Priority=5
}
