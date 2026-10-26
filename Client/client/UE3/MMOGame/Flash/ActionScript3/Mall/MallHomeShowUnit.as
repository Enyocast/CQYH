
package ActionScript3.Mall
{

	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import scaleform.clik.controls.UILoader;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.Common.TimerManager;
	
	public class MallHomeShowUnit extends UIComponent
	{

		public var frontShow0_mc:RadioButton;
		public var frontShow1_mc:RadioButton;
		public var frontShow2_mc:RadioButton;
		public var frontShow3_mc:RadioButton;
		public var frontShow4_mc:RadioButton;
		
		public var showFrontPic_mc:UILoader;
		public var giftBox_mc:MovieClip;
		
		public var arrShowData:Array;
		public var nCurIndex:int = 0;
		public var nMaxIndex:int = 0;
		
		public var nBtn0PosX:int;
		public var nBtn1PosX:int;
		public var nBtn2PosX:int;
		public var nBtn3PosX:int;
		//public var nBtn4PosX:int;
		
		//var needTimer:Timer = new Timer(1000,0);
		var nNeedTime:int = 5;
		
		override protected  function configUI():void 
		{		
			trace("------MallHomePanel  super.configUI:");
			super.configUI();			

			nBtn0PosX = frontShow0_mc.x;
			nBtn1PosX = frontShow1_mc.x;
			nBtn2PosX = frontShow2_mc.x;
			nBtn3PosX = frontShow3_mc.x;
			//nBtn4PosX = frontShow4_mc.x;
			
			frontShow0_mc.addEventListener(MouseEvent.CLICK, 		onClickShowButton0 );
			frontShow1_mc.addEventListener(MouseEvent.CLICK, 		onClickShowButton1);
			frontShow2_mc.addEventListener(MouseEvent.CLICK, 		onClickShowButton2 );
			frontShow3_mc.addEventListener(MouseEvent.CLICK, 		onClickShowButton3 );
			//frontShow4_mc.addEventListener(MouseEvent.CLICK, 		onClickShowButton4 );
			giftBox_mc.addEventListener(MouseEvent.CLICK, 			onClickGoods );
			giftBox_mc.addEventListener(MouseEvent.ROLL_OVER, 		onRollOverGoodsShow);
			giftBox_mc.addEventListener(MouseEvent.ROLL_OUT,  		onRollOutGoodsShow);
			showFrontPic_mc.addEventListener(MouseEvent.ROLL_OVER, 		onRollOverGoodsShow);
			showFrontPic_mc.addEventListener(MouseEvent.ROLL_OUT,  		onRollOutGoodsShow);
			//needTimer.addEventListener(TimerEvent.TIMER,timerHandleNeedTime);
			arrShowData = [];
			showFrontPic_mc.addEventListener(MouseEvent.CLICK, 		onClickShowPic );
			/*
			var arr:Array = new Array;
			for(var n:int = 0; n < 3; ++n)
			{
				var daaa:MallGoodsData = new MallGoodsData;
				arr.push(daaa);
			}
			UpdateMallShowData(arr);*/
			TimerManager.getInstance().add(1000,step);
		}

		public function UpdateMallShowData( data:Array ):void
		{
			ExternalInterface.call( "ASTrace", " MallHomeShowUnit  UpdateMallShowData 00");
			arrShowData.splice();
			for(var n:int = 0; n < 5&&n < data.length; ++n)
			{
				var goodsData:MallGoodsData = data[n] as MallGoodsData;
				arrShowData.push(goodsData);
			}
			ExternalInterface.call( "ASTrace", " MallHomeShowUnit  UpdateMallShowData 11");
			nMaxIndex = data.length;
			frontShow0_mc.visible = (nMaxIndex >= 1);
			frontShow1_mc.visible = (nMaxIndex >= 2);
			frontShow2_mc.visible = (nMaxIndex >= 3);
			frontShow3_mc.visible = (nMaxIndex >= 4);
			//frontShow4_mc.visible = (nMaxIndex >= 5);
			
			if(nMaxIndex == 1)
			{
				frontShow0_mc.x = nBtn3PosX;
			}
			else if(nMaxIndex == 2)
			{
				frontShow0_mc.x = nBtn2PosX;
				frontShow1_mc.x = nBtn3PosX;
			}
			else if(nMaxIndex == 3)
			{
				frontShow0_mc.x = nBtn1PosX;
				frontShow1_mc.x = nBtn2PosX;
				frontShow2_mc.x = nBtn3PosX;
			}
			else if(nMaxIndex == 4)
			{
				frontShow0_mc.x = nBtn0PosX;
				frontShow1_mc.x = nBtn1PosX;
				frontShow2_mc.x = nBtn2PosX;
				frontShow3_mc.x = nBtn3PosX;
			}
			else
			{
				frontShow0_mc.x = nBtn0PosX;
				frontShow1_mc.x = nBtn1PosX;
				frontShow2_mc.x = nBtn2PosX;
				frontShow3_mc.x = nBtn3PosX;
				//frontShow4_mc.x = nBtn4PosX;
			}
			
			frontShow0_mc.selected = true;
			onClickShowButton0();
		}
		
		private function step():void
		{
			nNeedTime -= 1;
			if(nNeedTime < 0)
			{
				nNeedTime = 4;
				nCurIndex++;
				if(nCurIndex >= nMaxIndex)
					nCurIndex = 0;
				frontShow0_mc.selected = (nCurIndex == 0);
				frontShow1_mc.selected = (nCurIndex == 1);
				frontShow2_mc.selected = (nCurIndex == 2);
				frontShow3_mc.selected = (nCurIndex == 3);
				//frontShow4_mc.selected = (nCurIndex == 4);
				showFrontPic_mc.source = GetGoodsIcon();
			}
		}
		public function timerHandleNeedTime(evt:TimerEvent)
		{
			nNeedTime -= 1;
			if(nNeedTime < 0)
			{
				nNeedTime = 4;
				nCurIndex++;
				if(nCurIndex >= nMaxIndex)
					nCurIndex = 0;
				frontShow0_mc.selected = (nCurIndex == 0);
				frontShow1_mc.selected = (nCurIndex == 1);
				frontShow2_mc.selected = (nCurIndex == 2);
				frontShow3_mc.selected = (nCurIndex == 3);
				//frontShow4_mc.selected = (nCurIndex == 4);
				showFrontPic_mc.source = GetGoodsIcon();
			}
		}
		public function onClickShowButton0()
		{
			nCurIndex = 0;
			showFrontPic_mc.source = GetGoodsIcon();
		}
		
		public function onClickShowButton1()
		{
			nCurIndex = 1;
			showFrontPic_mc.source = GetGoodsIcon();
		}
		
		public function onClickShowButton2()
		{
			nCurIndex = 2;
			showFrontPic_mc.source = GetGoodsIcon();
		}
		
		public function onClickShowButton3()
		{
			nCurIndex = 3;
			showFrontPic_mc.source = GetGoodsIcon();
		}
		
		public function onClickShowButton4()
		{
			nCurIndex = 4;
			showFrontPic_mc.source = GetGoodsIcon();
		}
		
		public function onClickShowPic()
		{
			trace("####");
			//if( GetGoodsID() > 0)
				ExternalInterface.call("ASClickMallGoods", GetGoodsID() );
		}
		public function GetGoodsID():int
		{
			if(arrShowData== null)
				return 0;
			if(nCurIndex >= 0 && nCurIndex < arrShowData.length)
				return arrShowData[nCurIndex].ItemID;
			return 0; 
		}
		public function GetGoodsIcon():String
		{
			//return "E:\\goldMoney.png";
			if(arrShowData== null)
				return "";
			if(nCurIndex >= 0 && nCurIndex < arrShowData.length)
				return arrShowData[nCurIndex].ItemIcon;
			return ""; 
		}
		public function onClickGoods()
		{
			ExternalInterface.call("ASClickMallGoods", GetGoodsID());
		}
		function onRollOverGoodsShow( e:Event )
		{
			if(giftBox_mc)
				giftBox_mc.gotoAndStop("down");
			//needTimer.stop();
			TimerManager.getInstance().remove(step);
		}

		function onRollOutGoodsShow( e:Event )
		{
			if(giftBox_mc)
				giftBox_mc.gotoAndStop("up");
			//needTimer.start();
			TimerManager.getInstance().add(1000,step);
		}
	}
}