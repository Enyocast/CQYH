package ActionScript3.UndergroundTrade 
{
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.TextInput;
	
	
	public class UTBidMySignPanel extends MyPanel
	{
		public var bidobject_itemslot_mc:MyItemSlot;
		public var currprice_txt_mc:TextField;
		public var pricemybid_txt_mc:TextField;
		public var realusegold_txt_mc:TextField;
		public var discountrate_txt_mc:TextField;
		public var autobid_checkbtn_mc:Button;
		public var maxmybid_input_mc:TextInput;
		public var desc_txt_mc:TextField;
		public var gold_txt_mc:TextField;
		public var bid_btn_mc:Button;
		
		public function UTBidMySignPanel()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("----------------UTBidPanel::configUI");
			
			super.configUI();
			
			InitData();
			
			ExternalInterface.call("ASRegisterUTBidMySignPanel", this);
		}		
		
		private function InitData():void
		{
			if(null != autobid_checkbtn_mc)
			{
				autobid_checkbtn_mc.label = "自动加标";
				autobid_checkbtn_mc.addEventListener(MouseEvent.CLICK, OnAutoBidClick);
			}
			
			if(null != desc_txt_mc)
				desc_txt_mc.text = "1、竞标自己签名的装备可以享受一定的折扣，实际扣除金币少于竞标价\
												2、使用自动竞标后，当有标价高于我的出价，系统会按照5%幅度自动加价，直到其他人出\
												价超过我的最高出价        \
												3、当成功拍卖后，最高出价多余的部分将会返还给玩家";
			
			if(null != maxmybid_input_mc)
				maxmybid_input_mc.editable = false;
				
			if(null != bid_btn_mc)
			{
				bid_btn_mc.label = "竞标";
				bid_btn_mc.addEventListener(MouseEvent.CLICK, OnBidClick);
			}
		}
		
		function OnAutoBidClick()
		{
			if(null != autobid_checkbtn_mc)
				autobid_checkbtn_mc.selected = !autobid_checkbtn_mc.selected;
			if(null != maxmybid_input_mc)
			{
				if(autobid_checkbtn_mc.selected)
					maxmybid_input_mc.editable = true;
				else
					maxmybid_input_mc.editable = false;
			}
		}
		
		function OnBidClick():void
		{
			
		}
	}
	
}
