package ActionScript3.Battle{
	import ActionScript3.ItemSlot.IconSlot
	//import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	
	public class BattleFreeSelect extends UIComponent
	{
		//战场图
		public var BattleNameTf:TextField;
		//战场图
		public var BtlPicImgLoder:UILoader;
		//战场描述
		public var BtlDescTf:TextField;
		//物品奖励
		public var BtlAwardItemsIcon0:IconSlot;
		//经验奖励
		public var BtlAwardExpTf:TextField;
		
		override protected function configUI():void
		{
			trace("------BattleFreeSelect  super.configUI:");
			super.configUI();
		}
	}
}