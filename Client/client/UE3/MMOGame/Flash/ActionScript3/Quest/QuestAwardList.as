package ActionScript3.Quest
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import fl.motion.easing.Back;
	import scaleform.clik.core.CLIK;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import ActionScript3.controls.StateUIComponent;
	import ActionScript3.ItemSlot.MyItemSlot;

	public class QuestAwardList extends ListItemTreeRenderer
	{
		public var award_icon0:MyItemSlot;
		public var award_icon1:MyItemSlot;
		public var award_icon2:MyItemSlot;
		public var award_icon3:MyItemSlot;
		
		public function QuestAwardList()
		{
		}

		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren = true;
		}
	}
}