package ActionScript3.Widget
{

	import ActionScript3.MyPanel;
	import ActionScript3.MyActivePanel;
	import flash.external.ExternalInterface;

	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.Widget.CharEquipPanel;
	import ActionScript3.ItemSlotData;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;



	public class HeroPanel extends MyPanel
	{

		public var paperDollPanel_mc:PaperDollPanel;

		override protected function configUI():void
		{
			super.configUI();

			paperDollPanel_mc.visible = true;

			if (paperDollPanel_mc.role_turnleft_mc)
			{
				paperDollPanel_mc.role_turnleft_mc.addEventListener( ButtonEvent.PRESS , TurnLeft );
				paperDollPanel_mc.role_turnleft_mc.addEventListener( ButtonEvent.CLICK ,TurnRelease );
				paperDollPanel_mc.role_turnleft_mc.addEventListener( ButtonEvent.RELEASE_OUTSIDE ,TurnRelease );
			}
			if (paperDollPanel_mc.role_turnright_mc)
			{
				paperDollPanel_mc.role_turnright_mc.addEventListener( ButtonEvent.PRESS ,TurnRight );
				paperDollPanel_mc.role_turnright_mc.addEventListener( ButtonEvent.CLICK ,TurnRelease );
				paperDollPanel_mc.role_turnright_mc.addEventListener( ButtonEvent.RELEASE_OUTSIDE ,TurnRelease );
			}
			
			if (paperDollPanel_mc.roleContent_Gear)
			{
				var i:int;
				var frameName:Array = ["helm","shoulders","chest","legs","gloves","wrist","ring","trinket","neck","belt","boots","gloves","wrist","ring","mainhand","offhand"];
				for (i = 0; i < 15; i++)
				{
					var slot:MyItemSlot = paperDollPanel_mc.roleContent_Gear.getChildByName("slot_" + i) as MyItemSlot;//   ["slot_" + i];
					//slot.Veins_mc.visible = true;
					//slot.Veins_mc.gotoAndStop(frameName[i]);
				}
			}
			SetPanelDrag(paperDollPanel_mc.InfoDragButton_mc);
			
			//TestAttributeData();
			ExternalInterface.call( "RegisterHero", this );
		}

		function TurnLeft()
		{
			visible = false;
			ExternalInterface.call("TurnPress",true);
		}
		function TurnRight()
		{
			ExternalInterface.call("TurnPress",false);
		}
		function TurnRelease()
		{
			ExternalInterface.call("TurnRelease");
		}

		public function TestAttributeData()
		{
			//trace("TestAttributeData");
			var AttributeData:Array = new Array();
			for (var i:int = 1; i < 13; i++)
			{
				AttributeData.push({label:"attribute" + i, index:i ,type:0, deepth:1, visible:true,ID:i});
			}
			AttributeData[0].deepth = 0;
			AttributeData[5].deepth = 0;
			AttributeData[10].deepth = 0;

			AttributeData[0].type = 2;
			AttributeData[5].type = 1;
			AttributeData[10].type = 1;

			updateAttributeData(AttributeData);

			var AttributeObj:Object = {Growth:"attribute",Understanding:"-",Exp:"99/100"};
			updateInfo(AttributeObj);
			
		}

		public function updateAttributeData(AttributeData:Array)
		{
			paperDollPanel_mc.updateAttributeData(AttributeData);
		}

		public function updateInfo(data:Object)
		{
			paperDollPanel_mc.updateInfo(data);
		}
		
		public function showCapture(bShow:Boolean)
		{
			paperDollPanel_mc.showCapture(bShow);
		}		

		public function showSummon(bSummon:Boolean)
		{
			paperDollPanel_mc.showSummon(bSummon);
		}
		public function initUIText(data:Object)
		{
			paperDollPanel_mc.initUIText(data);
		}

		override public function getSlotByName(slotName:String):MyItemSlot
		{
			var slot:MyItemSlot = paperDollPanel_mc.roleContent_Gear.getChildByName(slotName) as MyItemSlot;
			return slot;
		}






	}
}