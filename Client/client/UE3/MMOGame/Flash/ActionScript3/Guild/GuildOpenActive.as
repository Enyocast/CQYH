package ActionScript3.Guild {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	
	public class GuildOpenActive extends MyPanel {
		
		public var guild_ok_mc:Button;
		public var txt_money:TextField;
		public var txt_herb:TextField;
		public var txt_wood:TextField;
		public var txt_crystal:TextField;
		public var txt_silver:TextField;
		public var active_dec:TextField;
		public var txt_build:TextField;
		public var ActiveID:int;//活动ID
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("开启活动");
			this.visible=false;
			clear();
			this.MyWindowsFrame_mc.btn_close.RemoveAddedEventListener();
			this.MyWindowsFrame_mc.btn_close.addEventListener(MouseEvent.CLICK,closeHandler);
			guild_ok_mc.addEventListener(MouseEvent.CLICK,clickHandler);
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			this.visible=false;
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASGuildActivitySumitOpen",ActiveID);
		}
		
		public function updateData(dat:Object):void
		{
			var obj:GuildActiveItemData=dat as GuildActiveItemData;
			if(obj)
			{
				this.visible=true;
				ActiveID=obj.ID;
				txt_money.htmlText=obj.money;
				txt_herb.htmlText=obj.herb;
				txt_wood.htmlText=obj.wood;
				txt_crystal.htmlText=obj.crystal;
				txt_silver.htmlText=obj.silver;
				txt_build.htmlText=obj.preBuilding;
				
				guild_ok_mc.enabled = obj.enough;
			}
			else
			{
				clear();
			}
		}
		
		private function clear():void
		{
			txt_money.htmlText="";
			txt_herb.htmlText="";
			txt_wood.htmlText="";
			txt_crystal.htmlText="";
			txt_silver.htmlText="";
			txt_build.htmlText="";
			//guild_ok_mc.enabled = false;
		}
	}
	
}
