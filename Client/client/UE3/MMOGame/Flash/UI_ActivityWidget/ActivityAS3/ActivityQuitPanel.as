
package UI_ActivityWidget.ActivityAS3
{
	import ActionScript3.MyPanel;
	
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

	public class ActivityQuitPanel extends MyPanel
	{
		public var  listActivity_mc:ScrollingList;
		//public var rememberContent_tf:TextField;
		//public var LookTask:TextField;
		public var  huoyueValue_tf:TextField;
		
        public var titleBar:MovieClip;
		public var  viewActivityBtn_mc:Button;
		//public var  backGameBtn_mc:Button;
		//public var  backLoginBtn_mc:Button;
		public var  quitGameBtn_mc:Button;
		public var  giftIcon0_mc:GiftBox;
		public var  giftIcon1_mc:GiftBox;
		public var  giftIcon2_mc:GiftBox;
		public var  giftIcon3_mc:GiftBox;
		public var  giftIcon4_mc:GiftBox;
		
		public var gifticon0_mc:GiftIcon;
		public var gifticon1_mc:GiftIcon;
		public var gifticon2_mc:GiftIcon;
		public var gifticon3_mc:GiftIcon;
		public var gifticon4_mc:GiftIcon;
		
		public var effect0:MovieClip;
		public var effect1:MovieClip;
		public var effect2:MovieClip;
		public var effect3:MovieClip;
		public var effect4:MovieClip;
		
		var data0:ActivityRewardBarItemData = null;
		var data1:ActivityRewardBarItemData = null;
		var data2:ActivityRewardBarItemData = null;
		var data3:ActivityRewardBarItemData = null;
		var data4:ActivityRewardBarItemData = null;
		
		override protected  function configUI():void 
		{		
			ShowMode="BC";
			super.configUI();			
			this.SetWindowTitle("退出游戏");
			var i:int=0;
			for(i=0;i<5;i++){
				var effmc:MovieClip=this.getChildByName("effect"+i) as MovieClip;
				effmc.mouseChildren=false;
			    effmc.mouseEnabled=false;
			    effmc.gotoAndStop(1);
			    effmc.visible=false;
			}
			titleBar.btnHead0.addEventListener(MouseEvent.CLICK,onClickListHead0 );
			titleBar.btnHead1.addEventListener(MouseEvent.CLICK,onClickListHead1 );
			titleBar.btnHead2.addEventListener(MouseEvent.CLICK,onClickListHead2 );
			titleBar.btnHead3.addEventListener(MouseEvent.CLICK,onClickListHead3 );
			titleBar.btnHead4.addEventListener(MouseEvent.CLICK,onClickListHead4 );
			
			gifticon0_mc.addEventListener(MouseEvent.CLICK, 		onCLickQuitGetReward0 );
			gifticon1_mc.addEventListener(MouseEvent.CLICK, 		onCLickQuitGetReward1 );
			gifticon2_mc.addEventListener(MouseEvent.CLICK, 		onCLickQuitGetReward2 );
			gifticon3_mc.addEventListener(MouseEvent.CLICK, 		onCLickQuitGetReward3 );
			gifticon4_mc.addEventListener(MouseEvent.CLICK, 		onCLickQuitGetReward4 );
			
			viewActivityBtn_mc.addEventListener(MouseEvent.CLICK, onClickViewActivity );
			//backGameBtn_mc.addEventListener(MouseEvent.CLICK, 	  onCLickBackGame );
			//backLoginBtn_mc.addEventListener(MouseEvent.CLICK, 	  onBackLogin);
			quitGameBtn_mc.addEventListener(MouseEvent.CLICK, 	  onQuitGame );
			

			gifticon0_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardBarItem0);
			gifticon0_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardBarItem0);
			
			gifticon1_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardBarItem1);
			gifticon1_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardBarItem1);
			
			gifticon2_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardBarItem2);
			gifticon2_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardBarItem2);
			
			gifticon3_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardBarItem3);
			gifticon3_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardBarItem3);
			
			gifticon4_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardBarItem4);
			gifticon4_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardBarItem4);
			
/*			LookTask.styleSheet = new StyleSheet  ;
			LookTask.addEventListener(TextEvent.LINK, onLinkCallBack);
			LookTask.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			LookTask.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);*/
			
//			ExternalInterface.call("ASRegisterActivityQuitPanel", this);

			//UCUpdateRememberContent(["11","22","33","44","55"]);
/*			
			
			SetBoxState(1,gifticon0_mc);
			
			SetBoxState(5,gifticon1_mc);
			SetBoxState(9,gifticon2_mc);
			SetBoxState(3,gifticon3_mc);
			
			SetBoxState(1,gifticon4_mc);
			var tAABar:Array = new Array;
			for(var n :int = 0; n < 3; ++n)
			{
				var data1:ActivityRewardBarItemData = new ActivityRewardBarItemData;
				data1.Pos = 20*n;
				data1.condition = (n + 1).toString();
				data1.nType = n %3;
				data1.nState = n %3;
				tAABar.push(data1);
			}
			UCUpdateQuitActivityReward(tAABar);*/
		}

		public function UCUpdateActivityQuitListData( dat:Array ):void
		{
			listActivity_mc.dataProvider = new DataProvider(dat);
			listActivity_mc.validateNow();
			listActivity_mc.invalidateData();
		}		

		public function onClickListHead0()
		{
			//ExternalInterface.call("ASClickQuitListHeadSort", 0 );
		}
		public function onClickListHead1()
		{
			ExternalInterface.call("ASClickQuitListHeadSort", 4 );
		}
		public function onClickListHead2()
		{
			ExternalInterface.call("ASClickQuitListHeadSort", 5 );
		}
		public function onClickListHead3()
		{
			//ExternalInterface.call("ASClickQuitListHeadSort", 3 );
		}
		public function onClickListHead4()
		{
			ExternalInterface.call("ASClickQuitListHeadSort", 3 );
		}
		
		public function onClickViewActivity()
		{
			ExternalInterface.call("ASClickOpenActivityPanel", this);
		}
		public function onCLickBackGame()
		{
			ExternalInterface.call("ASClickBackGame", this);
		}
		public function onBackLogin()
		{
			ExternalInterface.call("ASClickBackLogin", this);
		}
		public function onQuitGame()
		{
			ExternalInterface.call("ASClickQuitGame", this);
		}
		
		public function onCLickQuitGetReward0()
		{
			if(data0 != null){
				effect0.visible=false;
			    effect0.gotoAndStop(1);
			    ExternalInterface.call("ASClickQuitGetReward", 0);
			}
		}
		public function onCLickQuitGetReward1()
		{
			if(data1 != null){
				effect1.visible=false;
			    effect1.gotoAndStop(1);
				ExternalInterface.call("ASClickQuitGetReward", 1);
			}
		}
		public function onCLickQuitGetReward2()
		{
			if(data2 != null){
				effect2.visible=false;
			    effect2.gotoAndStop(1);
				ExternalInterface.call("ASClickQuitGetReward", 2);
			}
		}
		public function onCLickQuitGetReward3()
		{
			if(data3 != null){
				effect3.visible=false;
			    effect3.gotoAndStop(1);
				ExternalInterface.call("ASClickQuitGetReward", 3);
			}
				
		}
		public function onCLickQuitGetReward4()
		{
			if(data4 != null){
				effect4.visible=false;
			    effect4.gotoAndStop(1);
				ExternalInterface.call("ASClickQuitGetReward", 4);
			}
		}
		
		public function UCUpdateQuitActivityReward(data:Array)
		{
			var irdata:ActivityRewardBarItemData = new ActivityRewardBarItemData;
			irdata.condition = "----";
			irdata.nState = -1;
			irdata.nType = 0;
			SetGiftItemState(irdata,giftIcon0_mc,gifticon0_mc,0);
			SetGiftItemState(irdata,giftIcon1_mc,gifticon1_mc,1);
			SetGiftItemState(irdata,giftIcon2_mc,gifticon2_mc,2);
			SetGiftItemState(irdata,giftIcon3_mc,gifticon3_mc,3);
			SetGiftItemState(irdata,giftIcon4_mc,gifticon4_mc,4);

			data0 = null;data1= null; data2 = null; data3 = null; data4 = null;
			if(data)
			{
				for(var n:int = 0; n < data.length; ++n)
				{
					var itemData:ActivityRewardBarItemData = data[n] as ActivityRewardBarItemData;
					if(n == 0)
					{
						data0 = itemData;
						SetGiftItemState(itemData,giftIcon0_mc,gifticon0_mc,0);
					}
					else if(n == 1)
					{
						data1 = itemData;
						SetGiftItemState(itemData,giftIcon1_mc,gifticon1_mc,1);
					}
					else if(n == 2)
					{
						data2 = itemData;
						SetGiftItemState(itemData,giftIcon2_mc,gifticon2_mc,2);
					}
					else if(n == 3)
					{
						data3 = itemData;
						SetGiftItemState(itemData,giftIcon3_mc,gifticon3_mc,3);
					}
					else if(n == 4)
					{
						data4 = itemData;
						SetGiftItemState(itemData,giftIcon4_mc,gifticon4_mc,4);
					}
				}
			}
		}
		public function UCUpdateActivityValue(data:String)
		{
			huoyueValue_tf.text = data;
		}
		
		public function UCUpdateRememberContent(data:Array)
		{
/*			if(data)
			{
				var strInfo:String = String("");
				var str:String="";
				for(var n:int = 0; n < data.length; ++n)
				{
					if(n%2==0){
						strInfo +=  data[n] as String;
						strInfo += "\n";
					}else{
						str+=data[n] as String;
						str+="\n";
					}
				}
				this.LookTask.wordWrap=true;
				this.LookTask.multiline=true;
				this.LookTask.htmlText =str; 
				rememberContent_tf.wordWrap = true;
				rememberContent_tf.multiline=true;
				rememberContent_tf.htmlText = strInfo;
				
			}*/
		}
		
		function SetGiftItemState(data:ActivityRewardBarItemData,giftmc:GiftBox,giftIconMc:GiftIcon,idx:int=0)
		{ 
			if(data == null || giftmc == null || giftIconMc == null)
				return;
			
			var textInfo:TextField = giftmc.getChildByName("giftCondition_tf") as TextField;
			textInfo.text =  "需活跃度"+data.condition;
			var mc:MovieClip=this.getChildByName("effect"+idx) as MovieClip;
			mc.visible=false;
			mc.gotoAndStop(1);
			var nType:int = data.nType * 4 + 1;
			//不可领取
			if(data.nState == 0)
			{
				SetBoxState(nType,giftIconMc);
			}
			//可领取
			else if(data.nState == 1)
			{
				mc.visible=true;
				mc.gotoAndPlay(1);
				SetBoxState(nType ,giftIconMc);
			}
			//已领取
			else if(data.nState == 2)
			{
				SetBoxState(nType + 3,giftIconMc);
			}
			else
			{
				SetBoxState(nType,giftIconMc);
			}
		}
		
		function SetBoxOverState(data:ActivityRewardBarItemData,icon_mc:GiftIcon,over:int)
		{
			trace("onRollOverRewardBarItem3",data.nState,data.nType);
			
			if(data.nState == 1 || data.nState == 0)
			{
				var nType:int = data.nType * 4 + 1;
				SetBoxState(nType  + over,icon_mc);
			}
			/*else if(data.nState == 0)
			{
				SetBoxState(nType + over,icon_mc);
			}*/
		}
		
		function SetBoxState(state:int,icon_mc:GiftIcon)
		{
			if(state > 0 && state<= 12)
				icon_mc.gotoAndStop("_"+state);
		}
		
		function onRollOverRewardBarItem0( e:Event )
		{
			if(data0 != null)
			{
				SetBoxOverState(data0,gifticon0_mc,1);
				ExternalInterface.call("ASShowTips_ActivityRewardItemBar", this ,0);
			}
		}

		function onRollOutRewardBarItem0( e:Event )
		{
			if(data0 != null)
			{
				SetBoxOverState(data0,gifticon0_mc,0);
				ExternalInterface.call("ASHideTips_ActivityRewardItemBar" );
			}
		}
		
		function onRollOverRewardBarItem1( e:Event )
		{
			if(data1 != null)
			{
				SetBoxOverState(data1,gifticon1_mc,1);
				ExternalInterface.call("ASShowTips_ActivityRewardItemBar", this ,1);
			}
		}

		function onRollOutRewardBarItem1( e:Event )
		{
			if(data1 != null)
			{
				SetBoxOverState(data1,gifticon1_mc,0);
				ExternalInterface.call("ASHideTips_ActivityRewardItemBar" );
			}
		}
		
		function onRollOverRewardBarItem2( e:Event )
		{
			if(data2 != null)
			{
				SetBoxOverState(data2,gifticon2_mc,1);
				ExternalInterface.call("ASShowTips_ActivityRewardItemBar", this ,2);
			}
		}

		function onRollOutRewardBarItem2( e:Event )
		{
			if(data2 != null)
			{
				SetBoxOverState(data2,gifticon2_mc,0);
				ExternalInterface.call("ASHideTips_ActivityRewardItemBar" );
			}
		}
		
		function onRollOverRewardBarItem3( e:Event )
		{
			if(data3 != null)
			{
				SetBoxOverState(data3,gifticon3_mc,1);
				ExternalInterface.call("ASShowTips_ActivityRewardItemBar", this,3 );
			}
		}

		function onRollOutRewardBarItem3( e:Event )
		{
			if(data3 != null)
			{
				SetBoxOverState(data3,gifticon3_mc,0);
				ExternalInterface.call("ASHideTips_ActivityRewardItemBar" );
			}
		}
		
		function onRollOverRewardBarItem4( e:Event )
		{
			if(data4 != null)
			{
				SetBoxOverState(data4,gifticon4_mc,1);
				ExternalInterface.call("ASShowTips_ActivityRewardItemBar", this ,4);
			}
		}

		function onRollOutRewardBarItem4( e:Event )
		{
			if(data4 != null)
			{
				SetBoxOverState(data4,gifticon4_mc,0);
				ExternalInterface.call("ASHideTips_ActivityRewardItemBar" );
			}
		}
		
		function onLinkOverCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
	}
}