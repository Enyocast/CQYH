package UI_AuctionHouse.AS
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	
	public class AuctionListItemBase extends ListItemTreeRenderer 
	{
		public var rankindex_txt_mc:TextField;
		public var guildname_txt_mc:TextField;
		public var num_txt_mc:TextField;
		public var guildername_txt_mc:TextField;
		public var level_txt_mc:TextField;
		public var found_txt_mc:TextField;
		
		
		public function AuctionListItemBase()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();

			addEventListener(MouseEvent.CLICK, onClick);
			setUpdateDataCallBack(updateData);
		}
		
		function onClick(e:Event)
		{
			
		}
		
		function updateData(data:Object):void
		{
			
		}	
		
	}
	
}
