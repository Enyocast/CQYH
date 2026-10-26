package UI_SkillTree.SkillTreeAS3
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
	
	//import FX_DefaultClass;


	public class HeavenGasMainPanel extends UIComponent
	{
		public var openBtnGasPractise_mc:Button;
		public var oneKeyBtnMergeGas_mc:Button;
		public var tempGasIcon_mc:MovieClip;
		public var gasFieldMc:MovieClip;
		public var gasPurseMc:MovieClip;
		public var gasSeaTitle:MovieClip;
		
		public var tArrEquip:Array;
		public var tArrBag:Array;
		public var tArrBank:Array;
		
		//public var tArrEquipGasIcon:Array;
		//public var tArrBagGasIcon:Array;
		//public var tArrBankGasIcon:Array;
		
		public var GasBagTarget:MyItemSlot;
		
		public var GasBagIndex0:MyItemSlot;
		public var GasBagIndex2:MyItemSlot;
		
		var 	_GasMovieClass:Class;
		public var gas00:FX_Default;
		public var gasSelected_mc:MovieClip;
		public var gasPowerValue_mc:TextField;
		public var gasPower_mc:MovieClip;
		public var GetGas_mc:MovieClip;
		public var mergeGasFX_mc:MovieClip;
		
		public var tArrGasLabel0:Array;
		public var tArrGasLabel1:Array;
		public var cc:FX_Default;
		
		override protected function configUI():void
		{
			
			super.configUI();
			
			if(cc)
			{
				cc.visible = false;
			}
			
			if(openBtnGasPractise_mc)
				openBtnGasPractise_mc.addEventListener(ButtonEvent.CLICK,ClickOpenGasPractise);
			if(oneKeyBtnMergeGas_mc)
				oneKeyBtnMergeGas_mc.addEventListener(ButtonEvent.CLICK,ClickOneKeyMergeGas);
			
			
			_GasMovieClass = getDefinitionByName( "FX_Default" ) as Class;
			
			trace( "class!!!!"+_GasMovieClass );
			//trace("=======HeavenGasMainPanel3",_AttackClass);
			
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
			
			var nIndex:int = 1;
			tArrEquip = new Array;
			//tArrEquipGasIcon = new Array;
			for(var n:int = 0; n < 9; ++n)
			{
				var object0:MyItemSlot = getChildByName("GasEquip" + n)as MyItemSlot;
				if(object0)
				{
					object0.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
					object0.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
					//tArrEquipGasIcon.push(null);
					tArrEquip.push(object0);
					
					//if(nIndex == 1 || nIndex == 9)
						//object0.itemSlotIcon.IconLoader_mc.source = "test/" + nIndex++.toString() + ".swf";
					//object0.itemSlotIcon.IconLoader_mc.scale = 1;
					
				}
			}
			tArrBag = new Array;
			//tArrBagGasIcon = new Array;
			for(var i:int = 0; i < 32; ++i)
			{
				var object1:MyItemSlot = getChildByName("GasBagIndex" + i) as MyItemSlot;
				if(object1)
				{
					object1.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
					object1.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
					//tArrBagGasIcon.push(null);
					tArrBag.push(object1);
					//object1.itemSlotIcon.IconLoader_mc.source = "test/" + nIndex++.toString() + ".swf";
					//object1.itemSlotIcon.IconLoader_mc.scale = 1;
				}
			}
			//GasBagTarget.itemSlotIcon.IconLoader_mc.source = "test/" + 1 + ".swf";
			tArrBank = new Array;
			//tArrBankGasIcon = new Array;
			for(var k:int = 0; k < 16; ++k)
			{
				var object2:MyItemSlot = getChildByName("GasBankIndex" + k) as MyItemSlot;
				if(object2)
				{
					object2.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
					object2.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
					//tArrBankGasIcon.push(null);
					tArrBank.push(object2);
					//object2.itemSlotIcon.IconLoader_mc.source = "test/" + nIndex++.toString() + ".swf";
					//object2.itemSlotIcon.IconLoader_mc. = 1;
				}
			}
			
			if( GasBagTarget )
			{
				GasBagTarget.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
				GasBagTarget.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
			}
			
			if(gasPower_mc)
			{
				gasPower_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasPower);
				gasPower_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasPower);
			}
			
			if(gasSelected_mc)
			{
				gasSelected_mc.visible = false;
				gasSelected_mc.mouseEnabled = false;
			}
			gas00.visible = false;
			
			//test();
		}
		
		public function ClickOpenGasPractise()
		{
			ExternalInterface.call( "ASClickOpenGasPractisePanel", this);
		}
		public function ClickOneKeyMergeGas()
		{
			//UCSetGasIconState(0,0,true,1,1,"14.swf","");
			
			//UCSetGasIconState(0,32,true,1,1,"14.swf","");
			ExternalInterface.call( "ASClickOneKeyMergeGas", this);
		}
		
		function test()
		{
			var list:Array = new Array;
			var data:HeavenGasEquipData = new HeavenGasEquipData;
			data.nIndex = 0;
			data.sLabel0 = "11";
			data.sLabel0 = "22";
			list.push(data);
			
			
			UCUpdateEquipGasSlot(list);
		}
		
		public function UCUpdateEquipGasPower(data:int)
		{
			gasPowerValue_mc.text = data.toString();
		}
		//播放动画类型
		public function UCPlayAnimationGas(nIndex:int,nContainer:int,nSlot:int)
		{
			 GetGas_mc.gotoAndPlay("start");
			 if(nIndex == 0)
			 	mergeGasFX_mc.gotoAndPlay("on");
		}
		
		public function UCUpdateEquipGasSlot(data:Array)
		{
			if(data == null)
				return;
			for(var n:int = 0; n < data.length; ++n)
			{
				var temp:HeavenGasEquipData = data[n] as HeavenGasEquipData;
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
				}
			}
		}
		public function UCUpdateEquipGasSingleSlot(data:Object)
		{
			if(data == null)
				return;

			var temp:HeavenGasEquipData = data as HeavenGasEquipData;
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
			}
		}
		public function UCSetSelectedIconTarget(nContainer:int,nSlot:int)
		{
			var _localSlot:MyItemSlot = null;
			if(nContainer == 0)
			{
				if(nSlot < tArrBag.length  && nSlot >= 0)
				{
					_localSlot = tArrBag[nSlot];
					if(_localSlot)
					{
						gasSelected_mc.x = _localSlot.x;
						gasSelected_mc.y = _localSlot.y;
					}
				}
			}
		}
		
		public function UCSetGasIconState(nContainer:int,nInedx:int,bShow:Boolean,nIconType:int,nLevel:int,icon0:String,icon1:String)
		{
			var _localSlot:MyItemSlot = null;
			
			ExternalInterface.call( "ASTrace", "===========UCSetGasIconState load: "+icon0 +nContainer+ nInedx);
			if(nContainer == 0)
			{
				if(nInedx < tArrBag.length  && nInedx >= 0)
				{
					_localSlot = tArrBag[nInedx];
				}
				else
				{
					if(bShow)
					{
						
						//if(GasBagTarget.itemSlotIcon.IconLoader_mc.source  != icon0)
						{
							ExternalInterface.call( "ASTrace", "GasBagTarget.itemSlotIcon.IconLoader_mc.source 1= "+GasBagTarget.itemSlotIcon.IconLoader_mc.source);
							
							GasBagTarget.itemSlotIcon.IconLoader_mc.source = "";
							GasBagTarget.itemSlotIcon.IconLoader_mc.source  = icon0;
							GasBagTarget.itemSlotIcon.IconLoader_mc.visible  = true;
						}
					}
					else
						GasBagTarget.itemSlotIcon.IconLoader_mc.source = "";
					ExternalInterface.call( "ASTrace", "GasBagTarget.itemSlotIcon.IconLoader_mc.source 2= "+GasBagTarget.itemSlotIcon.IconLoader_mc.source);
					gasSelected_mc.visible = bShow;
				}
			}
			else if(nContainer == 1)
			{
				if(nInedx < tArrBank.length  && nInedx >= 0)
				{
					_localSlot = tArrBank[nInedx];
				}
			}
			else if(nContainer == 2)
			{
				if(nInedx < tArrEquip.length  && nInedx >= 0)
				{
					_localSlot = tArrEquip[nInedx];
				}
			}
			if(_localSlot)
			{
				//if(_localSlot.itemSlotIcon.IconLoader_mc.source != icon0)
				{
					ExternalInterface.call( "ASTrace", "_localSlot.itemSlotIcon.IconLoader_mc.source 1= "+_localSlot.itemSlotIcon.IconLoader_mc.source);
					_localSlot.itemSlotIcon.IconLoader_mc.source = "";
					_localSlot.itemSlotIcon.IconLoader_mc.source  = icon0;
					_localSlot.itemSlotIcon.IconLoader_mc.visible = true;
				}
					
				ExternalInterface.call( "ASTrace", "_localSlot.itemSlotIcon.IconLoader_mc.source 2= "+_localSlot.itemSlotIcon.IconLoader_mc.source);
			}
		}
		public function AddGasIcon():FX_Default
		{
			var tempMc:FX_Default = new _GasMovieClass as FX_Default;
			//tempMc.mouseEnabled = false;
			
			trace("=======HeavenGasMainPanel1",tempMc);
			addChild( tempMc );
			//tempMc.SetMouseEnabled(false);
			//tArrGasIcon.push(tempMc);
			return tempMc;
		}
		
		function onRollOverHeavenGasSlot( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenGasSlot",this);
		}

		function onRollOutHeavenGasSlot( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_HeavenGasSlot" );
		}
		function onRollOverHeavenGasPower( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenGasPower",this);
		}

		function onRollOutHeavenGasPower( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_HeavenGasPower" );
		}
	}
}