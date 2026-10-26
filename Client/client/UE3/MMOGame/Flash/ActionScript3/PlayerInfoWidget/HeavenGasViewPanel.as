package ActionScript3.PlayerInfoWidget
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataBinding;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.utils.getDefinitionByName;
	import flash.utils.getQualifiedClassName;
	import UI_FX_Lib.FX_Lib_AS3.FX_Default;
	import flash.system.ApplicationDomain;


	public class HeavenGasViewPanel extends UIComponent
	{
		public var gasFieldMc:MovieClip;
		public var gasPurseMc:MovieClip;
		public var gasSeaTitle:MovieClip;
		
		public var tArrEquip:Array;

		public var gasPowerValue_mc:TextField;
		public var gasPower_mc:MovieClip;

		public var tArrGasLabel0:Array;
		public var tArrGasLabel1:Array;
		
		override protected function configUI():void
		{
			
			super.configUI();
			
			tArrGasLabel0 = new Array;
			tArrGasLabel1 = new Array;
			for(var p:int = 0; p < 18; ++p)
			{
				var objectText:TextField = getChildByName("gasLabel" + p)as TextField;
				if(objectText)
				{	if(p%2 == 0)
						tArrGasLabel0.push(objectText);
					else 
						tArrGasLabel1.push(objectText);
				}
			}
			
			//var nIndex:int = 1;
			tArrEquip = new Array;
			for(var n:int = 0; n < 9; ++n)
			{
				var object0:MyItemSlot = getChildByName("GasEquip" + n)as MyItemSlot;
				if(object0)
				{
					object0.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
					object0.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
					tArrEquip.push(object0);
					//object0.itemSlotIcon.IconLoader_mc.source = "test/" + nIndex++.toString() + ".swf";
				}
			}
			
			if(gasPower_mc)
			{
				gasPower_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasPower);
				gasPower_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasPower);
			}
		}
		
		public function UpdateEquipGasView(data:Array)
		{
			if(data == null)
				return;
			var strGasTips:String = "";
			var _localSlot:MyItemSlot = null;
			var nPower:int = 0;
			for(var n:int = 0; n < data.length && n < tArrEquip.length; ++n)
			{
				var temp:HeavenGasViewData = data[n] as HeavenGasViewData;
				if(temp)
				{
					tArrGasLabel0[temp.nIndex].autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
					tArrGasLabel0[temp.nIndex].wordWrap 	= 			true;
					tArrGasLabel0[temp.nIndex].htmlText 	= 			temp.sLabel0;
					tArrGasLabel0[temp.nIndex].height 		= 			tArrGasLabel0[temp.nIndex].textHeight;
					
					tArrGasLabel1[temp.nIndex].autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
					tArrGasLabel1[temp.nIndex].wordWrap 	= 			true;
					tArrGasLabel1[temp.nIndex].htmlText 	= 			temp.sLabel1;
					tArrGasLabel1[temp.nIndex].height 		= 			tArrGasLabel1[temp.nIndex].textHeight;
					
					if(temp.sLabel0 != "")
					{
						strGasTips += temp.sLabel0;
						strGasTips += "\n";
					}
					nPower += temp.nWarPower;
					
					_localSlot = tArrEquip[n];
					
					_localSlot.isSlotLocked = temp.bLocked;
					_localSlot.enabled = !temp.bLocked;
					_localSlot.ItemTemplateID = temp.nIndex;
					
					if(_localSlot&&_localSlot.itemSlotIcon.IconLoader_mc.source != temp.sIconName)
					{
						_localSlot.itemSlotIcon.IconLoader_mc.source = "";
						_localSlot.itemSlotIcon.IconLoader_mc.source  = temp.sIconName;
						_localSlot.itemSlotIcon.IconLoader_mc.visible = true;
					}
				}
			}
			gasPower_mc.tipsHtml = "战斗力:" + nPower.toString() + "\n"+strGasTips;
		}

		function onRollOverHeavenGasSlot( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShow_HeavenGasViewTips",this);
		}

		function onRollOutHeavenGasSlot( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_PlainText" );
		}
		function onRollOverHeavenGasPower( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShow_HeavenGasPowerViewTips",this);
		}

		function onRollOutHeavenGasPower( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_PlainText" );
		}
	}
}