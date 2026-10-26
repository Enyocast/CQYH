package UI_TeamWidget.AS{
	
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.events.TextEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;
	
	public class TeamFBListItemDetail extends UIComponent
	{
		override protected function configUI():void
		{
			super.configUI();
			visible = false;
		}
	}
}