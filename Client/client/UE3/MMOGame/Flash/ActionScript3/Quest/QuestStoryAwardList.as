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
	import scaleform.clik.controls.UILoader;

	public class QuestStoryAwardList extends UIComponent
	{
		public var award_exp_mc:MovieClip;
		public var award_money_mc:MovieClip;
		public var award_money_ex_mc:MovieClip;
		public var award_activity_mc:MovieClip;
		
		public function QuestStoryAwardList()
		{
		}

		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren = true;
		}
	}
}