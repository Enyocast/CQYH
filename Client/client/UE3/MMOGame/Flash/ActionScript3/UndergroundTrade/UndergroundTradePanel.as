package ActionScript3.UndergroundTrade
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	
	import ActionScript3.UndergroundTrade.AuctionPanel;
	import ActionScript3.UndergroundTrade.MySignPanel;
	import ActionScript3.UndergroundTrade.SearchPanel;
	
	public class UndergroundTradePanel extends MyPanel
	{
		public var search_tipbtn_mc:MyTipButton;
		public var mysign_tipbtn_mc:MyTipButton;
		public var auction_tipbtn_mc:MyTipButton;
		
		public var auction_panel_mc:AuctionPanel;
		public var mysign_panel_mc:MySignPanel;
		public var search_panel_mc:SearchPanel;
		
		public function UndergroundTradePanel()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("------UndergroundTradePanel  super.configUI:");
			super.configUI();
			
			search_tipbtn_mc.addEventListener(MouseEvent.CLICK, OnSearchEquip);
			mysign_tipbtn_mc.addEventListener(MouseEvent.CLICK, OnMySignEquip);
			auction_tipbtn_mc.addEventListener(MouseEvent.CLICK, OnAuction);
			
			OnSearchEquip();
			
			ExternalInterface.call("ASRegisterUndergroundTradePanel", this);
		}
		
		public function OnSearchEquip():void
		{
			if(null != search_panel_mc 
			   && null != mysign_tipbtn_mc && null != auction_tipbtn_mc)
			{
				search_panel_mc.visible = true;
				mysign_panel_mc.visible = false;
				auction_panel_mc.visible = false;
			}
			else
				trace("UndergroundTradePanel->OnSearchEquip() failed!");
		}
		
		public function OnMySignEquip():void
		{
			if(null != search_panel_mc 
			   && null != mysign_tipbtn_mc && null != auction_tipbtn_mc)
			{
				search_panel_mc.visible = false;
				mysign_panel_mc.visible = true;
				auction_panel_mc.visible = false;
			}
			else
				trace("UndergroundTradePanel->OnMySignEquip() failed!");
		}
		
		public function OnAuction():void
		{
			if(null != search_panel_mc 
			   && null != mysign_tipbtn_mc && null != auction_tipbtn_mc)
			{
				search_panel_mc.visible = false;
				mysign_panel_mc.visible = false;
				auction_panel_mc.visible = true;
			}
			else
				trace("UndergroundTradePanel->OnAuction() failed!");
		}
	}
	
}
