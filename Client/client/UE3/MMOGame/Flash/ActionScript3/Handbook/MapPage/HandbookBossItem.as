package ActionScript3.Handbook.MapPage
{
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Handbook.ConstansDefine;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	
	public class HandbookBossItem extends Button
	{
		public var icon_mc:UILoader;
		public var name_tf:TextField;
		
		public function HandbookBossItem()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			icon_mc.source = null;
			name_tf.text = "";
			this.addEventListener(ButtonEvent.CLICK, onItemClick, false, 0, true);
		}
		
		private function onItemClick(evt:ButtonEvent):void
		{
			ExternalInterface.call(ConstansDefine.ASGotoMonsterPage, name_tf.text);
		}
	}
}