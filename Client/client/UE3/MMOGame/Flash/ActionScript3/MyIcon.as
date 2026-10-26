
package ActionScript3 {

	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.display.Stage;
	import flash.display.Scene;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.Label;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.ItemSlotData;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.MyIconConponent;
	import ActionScript3.MyPanelType;

	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class MyIcon extends MovieClip
	{
		public var itemSlotIcon_mc:MyIconConponent;
		public var ItemTemplateID:int = 0;
		public var index:int = 0;
		
		public function init()
		{
			trace("======================MyIcon INIT====================", itemSlotIcon_mc);
			
			if(itemSlotIcon_mc)
			{
				trace("ASTrace", "itemSlotIcon_mc!");
			}
			else
			{
				itemSlotIcon_mc = this["itemSlotIcon_mc"];
			}
			
			//itemSlotIcon.IconLoader_mc.source = "img://MMO_Weapons_2HSword.02";
			
			this.addEventListener(MouseEvent.ROLL_OVER, onShowIconTips);
			this.addEventListener(MouseEvent.ROLL_OUT, onHideIconTips);
			this.addEventListener(MouseEvent.CLICK, onSelectIcon);
		}
		
		//native function ASRollOverItemSlot(GFxObject mc, ESlotPanelType SlotType, ECONTAINER_SLOT ContainerID, int SlotID );
		//native function ASRollOutItemSlot( GFxObject mc);


		function onShowIconTips()
		{
			ExternalInterface.call("ASRollOverItemSlot",  this, MyPanelType.ESPType_Quest, -1, index);
			//this["root"].ChangeTips();	
		}
		
		function onHideIconTips()
		{
			ExternalInterface.call("ASRollOutItemSlot", this);
			//root["tooltips_mc"].visible = false;
		}
		
		function onSelectIcon()
		{
			ExternalInterface.call("ASSelectAward", this, index, ItemTemplateID);
		}
		
		public function setIconImg(img:String)
		{
			var iconObject : Object = this.getChildByName("itemSlotIcon_mc") as Object;
			var icon : UILoader = iconObject.getChildByName("IconLoader_mc") as UILoader;
			icon.source = img;
			icon.visible = true;
			//ExternalInterface.call("ASTrace", "------setIconImg:" + icon);
		}
		
		public function RemoveAll()
		{
			this.removeEventListener(MouseEvent.ROLL_OVER, onShowIconTips);
			this.removeEventListener(MouseEvent.ROLL_OUT, onHideIconTips);
			this.removeEventListener(MouseEvent.CLICK, onSelectIcon);	
			
			//trace("!!!!112");
			//ExternalInterface.call("ASTrace","itemSlotIcon.RemoveAll---------------------------------------------1");
			//trace(itemSlotIcon_mc);
			itemSlotIcon_mc.RemoveAll();
			itemSlotIcon_mc=null;
			//trace("!!!!113");
			//ExternalInterface.call("ASTrace","itemSlotIcon.RemoveAll---------------------------------------------2");
		}				
	}
}