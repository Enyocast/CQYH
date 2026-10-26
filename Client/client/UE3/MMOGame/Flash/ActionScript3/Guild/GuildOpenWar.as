package ActionScript3.Guild {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	
	public class GuildOpenWar extends BaseGuildAlert {
		
		public var txt_money:TextField;
		public var txt_herb:TextField;
		public var txt_wood:TextField;
		public var txt_crystal:TextField;
		public var txt_silver:TextField;
		public var active_dec:TextField;
		public var GuildID:int;//活动ID
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("宣战");
			this.visible=false;
			
			clear();
		}
		
		override protected function onBtClickOk(evt:MouseEvent):void
		{
            ExternalInterface.call("ASGuildWarSumitOpen",GuildID);
			this.visible=false;
		}
		
		public function updateData(dat:Object):void
		{
			var obj:GuildActiveItemData=dat as GuildActiveItemData;
			if(obj)
			{
				this.visible=true;
				GuildID=obj.ID;
				txt_money.htmlText=obj.money;
				txt_herb.htmlText=obj.herb;
				txt_wood.htmlText=obj.wood;
				txt_crystal.htmlText=obj.crystal;
				txt_silver.htmlText=obj.silver;
				
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
			guild_ok_mc.enabled = false;
		}
	}
	
}
