package ActionScript3.Widget
{

	import ActionScript3.MyPanel;
	import ActionScript3.MyActivePanel;
	import flash.external.ExternalInterface;

	import ActionScript3.MyItemSlot;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.Widget.CharEquipPanel;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import flash.events.TimerEvent;	
	import flash.utils.Timer;


	public class CharactorPanel extends MyPanel
	{
		//public var ItemsData:Array;
		//
		public var paperDollPanel_mc:PaperDollPanel;
		public var relationPanel_mc:RelationPanel;
		public var famePanel_mc:FamePanel;

		public var tab0_mc:MyTipButton;
		public var tab1_mc:MyTipButton;
		public var tab2_mc:MyTipButton;
		
		
		

		var timerCountDown:Timer = new Timer(1000);


		public function updateItemsData(ItemsListData:Array)
		{
			relationPanel_mc.updateItemsData(ItemsListData);
		}

		public function updateFameData(ItemsListData:Array)
		{
			famePanel_mc.updateItemsData(ItemsListData);
		}

		public function test()
		{
			ExternalInterface.call("ASTrace","test");
		}

		override protected function configUI():void
		{
			super.configUI();
			
			tab0_mc.MWTabIcon_mc.gotoAndStop("role0");
			tab1_mc.MWTabIcon_mc.gotoAndStop("role1");		
			tab2_mc.MWTabIcon_mc.gotoAndStop("role2");

			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
			timerCountDown.start();

			tab0_mc.addEventListener( ButtonEvent.CLICK,ClickTab0 );
			tab1_mc.addEventListener( ButtonEvent.CLICK ,ClickTab1 );
			tab2_mc.addEventListener( ButtonEvent.CLICK ,ClickTab2 );

			paperDollPanel_mc.visible = true;
			SetPanelDrag(paperDollPanel_mc.InfoDragButton_mc);
			InfoDragButton_mc = paperDollPanel_mc.InfoDragButton_mc;
			relationPanel_mc.visible = false;
			famePanel_mc.visible = false;


			if (paperDollPanel_mc.role_turnleft_mc)
			{

				paperDollPanel_mc.role_turnleft_mc.addEventListener( ButtonEvent.PRESS , TurnLeft );
				//;
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
				for (i = 0; i < 15; i++)
				{
					paperDollPanel_mc.roleContent_Gear["slot_" + i].Veins_mc.visible = true;
				}
				paperDollPanel_mc.roleContent_Gear.slot_0.Veins_mc.gotoAndStop("helm");

				paperDollPanel_mc.roleContent_Gear.slot_1.Veins_mc.gotoAndStop('shoulders');
				paperDollPanel_mc.roleContent_Gear.slot_2.Veins_mc.gotoAndStop('chest');
				paperDollPanel_mc.roleContent_Gear.slot_3.Veins_mc.gotoAndStop('legs');

				paperDollPanel_mc.roleContent_Gear.slot_4.Veins_mc.gotoAndStop('gloves');
				paperDollPanel_mc.roleContent_Gear.slot_11.Veins_mc.gotoAndStop('manteau');
				paperDollPanel_mc.roleContent_Gear.slot_13.Veins_mc.gotoAndStop('ring');
				paperDollPanel_mc.roleContent_Gear.slot_6.Veins_mc.gotoAndStop('ring');
				paperDollPanel_mc.roleContent_Gear.slot_5.Veins_mc.gotoAndStop('wrist');
				paperDollPanel_mc.roleContent_Gear.slot_12.Veins_mc.gotoAndStop('wrist');

				paperDollPanel_mc.roleContent_Gear.slot_7.Veins_mc.gotoAndStop('trinket');
				paperDollPanel_mc.roleContent_Gear.slot_8.Veins_mc.gotoAndStop('neck');
				paperDollPanel_mc.roleContent_Gear.slot_9.Veins_mc.gotoAndStop('belt');
				paperDollPanel_mc.roleContent_Gear.slot_10.Veins_mc.gotoAndStop('boots');

				paperDollPanel_mc.roleContent_Gear.slot_14.Veins_mc.gotoAndStop('mainhand');
				paperDollPanel_mc.roleContent_Gear.slot_15.Veins_mc.gotoAndStop('offhand');
			}


			ExternalInterface.call( "RegisterCharactor", this );

		}



		function TurnLeft()
		{
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



		function ClickTab0(e:Event)
		{
			paperDollPanel_mc.visible = true;
			relationPanel_mc.visible = false;
			famePanel_mc.visible = false;
			SetPanelDrag(paperDollPanel_mc.InfoDragButton_mc);
			ExternalInterface.call("ASCharactorTab",0 );
		}
		function ClickTab1(e:Event)
		{
			paperDollPanel_mc.visible = false;
			relationPanel_mc.visible = true;
			famePanel_mc.visible = false;
			SetPanelDrag(relationPanel_mc.InfoDragButton_mc);
			ExternalInterface.call("ASCharactorTab",1 );
		}
		function ClickTab2(e:Event)
		{
			paperDollPanel_mc.visible = false;
			relationPanel_mc.visible = false;
			famePanel_mc.visible = true;
			SetPanelDrag(famePanel_mc.InfoDragButton_mc);
			ExternalInterface.call("ASCharactorTab",2 );


			//var itemsData:Array = new Array();
			//for (var i:int = 1; i < 13; i++)
			//{
			//itemsData.push({label:"Item" + i, index:i ,type:0, deepth:0, numStar:1+i%5,isCurrent:false,isNew:false,sourceImg:"",visible:true,ID:i,ValidTime:i*i*20});
			//}
			//
			//itemsData[0].isCurrent = true;
			//itemsData[0].isNew = true;
			//itemsData[1].isNew = true;
			//
			//updateFameData( itemsData );
		}



		function timerHandle()
		{
			if (visible && famePanel_mc.visible)
			{
				ExternalInterface.call("ASCharactorTab",2 );
			}
		}
	}
}