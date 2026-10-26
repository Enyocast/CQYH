package UI_EquipEnhance.EquipEnhanceAS3
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import ActionScript3.MyPanel;
	import UI_EquipEnhance.EquipEnhanceAS3.MakeEnhancePanel;
	//import ActionScript3.MyTipButton;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	public class EquipEnhancePanel extends MyPanel
	{
		public var iCurTab:int;
		//public var tab1_mc:MyTipButton;
		//public var tab2_mc:MyTipButton;
		public var MakeEnhancePanel_mc:MakeEnhancePanel;
		//public var TransEnhancePanel_mc:MyPanel;
		
		override protected function configUI():void
		{
			super.configUI();

			ExternalInterface.call( "RegisterEquipEnhance", this );
			
			//
			//tab1_mc.MWTabIcon_mc.gotoAndStop("enhance0");
			//tab2_mc.MWTabIcon_mc.gotoAndStop("enhance1");
			//tab1_mc.addEventListener( "click", function _contentChange(e:Event){ contentChange(e,0);} );
			//tab2_mc.addEventListener( "click", function _contentChange(e:Event){ contentChange(e,1);} );

			ShowContent(0);
		}
		//
		function contentChange( e:Event, idx:int )
		{
			ShowContent( idx );
			//
			ExternalInterface.call( "ASUpdateEquipEnhancePanel", iCurTab );
		}
		//
		public function ShowContent( idx:int )
		{
			iCurTab = idx;
			MakeEnhancePanel_mc.visible = false;
			//TransEnhancePanel_mc.visible = false;
			//tab1_mc.selected = false;
			//tab2_mc.selected = false;
			switch( iCurTab )
			{
				case 0:
				MakeEnhancePanel_mc.visible = true;
				//tab1_mc.selected = true;
				//ExternalInterface.call( "ASTrace", "Enhance!" );
				break;
				
				case 1:
				//TransEnhancePanel_mc.visible = true;
				//tab2_mc.selected = true;
				//ExternalInterface.call( "ASTrace", "UnEnhance!" );
				break;
				
				default:
				break;
			}
		}
	}
}