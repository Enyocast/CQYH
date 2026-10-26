
package ActionScript3.Mall
{
	import ActionScript3.MyPanel;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	//import scaleform.clik.motion.Tween;
	//import fl.transitions.TweenEvent;
	import scaleform.clik.motion.Tween;
	import fl.motion.easing.Linear;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import flash.utils.Timer;
	import flash.events.TimerEvent;

	public class MallGoodsNoticeUnit extends UIComponent
	{
		public var notice_mc:TextField;
		public var tArrNotice:Array = new Array;;
		public var nCurIndex:int = 0;
		var buttonTween0:Tween;
		public var noticeClip_mc:MovieClip;
		var needTimer:Timer = new Timer(33,0);
		var nNeedTime:int = 10;
		
		override protected  function configUI():void 
		{		
			trace("------MallGoodsNoticeUnit  super.configUI:");
			super.configUI();			
			notice_mc = noticeClip_mc.getChildByName("notice_tf") as TextField;
			/*var tNotice = new Array;
			
			var tstr:String = String("<font color = '#14a800'>[0时57分]</font>wanjia购买了<font color = '#1EFF00'><a href='event:,3,2'><u>银</u></a></font>");
			tstr = String("<font color = '#14a800'>[0时57分]</font>wanjia购买了<font color = '#1EFF00'><a href='event:,3,2'><u>银1</u></a></font>");
			tstr = String("<font color = '#14a800'>[0时57分]</font>wanjia购买了<font color = '#1EFF00'><a href='event:,3,2'><u>银2</u></a></font>");
			tstr = String("<font color = '#14a800'>[0时57分]</font>wanjia购买了<font color = '#1EFF00'><a href='event:,3,2'><u>银3</u></a></font>");
			 
			tNotice.push(tstr);*/

			needTimer.addEventListener(TimerEvent.TIMER,timerHandleNeedTime);
			needTimer.start();
			//UpdateNewNotice(tNotice);
			
			//btnNoticePre_mc.addEventListener(MouseEvent.CLICK, 			onClickPreNotice);
			//btnNoticeNext_mc.addEventListener(MouseEvent.CLICK, 		onClickNextNotice);
			//this.addEventListener(MouseEvent.RollOver, 		onClickNextNotice);
			
			
			
			notice_mc.styleSheet = new StyleSheet  ;
			notice_mc.addEventListener(TextEvent.LINK, onLinkCallBack);
			notice_mc.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			notice_mc.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			//noticeClip_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverInfo);
			//noticeClip_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutInfo);
			this.addEventListener(MouseEvent.ROLL_OVER, onRollOverInfo);
			this.addEventListener(MouseEvent.ROLL_OUT, onRollOutInfo);
			
			ExternalInterface.call( "ASTrace", "MallGoodsNoticeUnit");
		}
		public function timerHandleNeedTime(evt:TimerEvent)
		{
			if(tArrNotice.length == 0)
				return;
			nNeedTime -= 1;
			var nSpan = 3;
			if(nNeedTime < 0)
			{
				nNeedTime = 350;
				noticeClip_mc.y = 5;
				noticeClip_mc.x = this.width;
				notice_mc.autoSize 	= 	flash.text.TextFieldAutoSize.LEFT;
				notice_mc.htmlText 	= GetCurNotice();
				
				var nWidthText:int = notice_mc.width;
				notice_mc.width = nWidthText;
				noticeClip_mc.width = nWidthText;
				nSpan = (nWidthText + this.width)/350;
				nCurIndex++;
			}
			else
			{
				noticeClip_mc.x -= nSpan;
			}
		}
		public function UpdateNewNotice(data:Array)
		{
			tArrNotice.splice();
			for(var n:int = 0; n  < data.length; ++n)
			{
				tArrNotice.push(data[n]);
			}
			nCurIndex = 0;
			//StartNewTween();
		}
		public function AddNewNotice(str:String)
		{
			tArrNotice.push(str);
		}
		/*
		public function onClickPreNotice()
		{
			nCurIndex--;
			notice_tf.text = GetCurNotice();
		}
		public function onClickNextNotice()
		{
			if(buttonTween)
				buttonTween.paused = true;
		}*/
		
		public function onRollOverInfo()
		{
			trace("onRollOverInfo",this.width,notice_mc.width);
			if(buttonTween0)
				buttonTween0.paused = true;
			needTimer.stop();
		}
		public function onRollOutInfo()
		{
			trace("onRollOutInfo");
			if(buttonTween0)
				buttonTween0.paused = false;
			needTimer.start();
		}
		
		public function GetCurNotice():String
		{
			if(nCurIndex >= tArrNotice.length || nCurIndex < 0)
					nCurIndex = 0;
					
			if(nCurIndex >= 0 && nCurIndex < tArrNotice.length)
				return tArrNotice[nCurIndex];
			return "";
		}

		function StartNewTween()
		{
			var NeedTime:int 	= 6000;
			noticeClip_mc.y = 5;
			noticeClip_mc.x = this.width;

			notice_mc.htmlText 	= GetCurNotice();
		
			var nWidthText:int = notice_mc.width;
			notice_mc.width = nWidthText;
			noticeClip_mc.width = nWidthText;
		trace("111",noticeClip_mc.width,notice_mc.width);
		
			buttonTween0 = new Tween(NeedTime,noticeClip_mc,{x: -nWidthText},{paused:false,ease:Linear.easeNone,onComplete:CompleteTween,loop:false});
		
		ExternalInterface.call( "ASTrace", "StartNewTween",this.width,noticeClip_mc.width,notice_mc.width,nWidthText);
		trace("222",noticeClip_mc.width,notice_mc.width);
		}
		
		function CompleteTween()
		{
			if (tArrNotice.length == 0)
				return;
			nCurIndex++;
			if(nCurIndex >= tArrNotice.length)
				nCurIndex = 0;
			StartNewTween();
		}
		
		function onLinkOverCallBack(e:TextEventEx)
		{
			trace("onLinkOverCallBack");;
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx)
		{
			trace("onLinkOutCallBack");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent)
		{
			trace("onLinkCallBack");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
	}
}