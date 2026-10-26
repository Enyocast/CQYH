package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.display.MovieClip;
	import flash.utils.Timer;
	import flash.events.MouseEvent;




	public class MessageDeathWidget extends MyPanel
	{

		//场合
		static var S_Normal:Number = 1;
		static var S_Battle:Number = 2;
		static var S_Dungeons:Number = 3;
		static var S_PVP:Number = 4;

		//复活方式
		static var revive_Around:Number = 1;
		static var revive_Coin:Number = 2;
		static var revive_Free:Number = 3;

        public var tipinfo:MovieClip;
		//public var tF_Info:TextField;
		public var tF_timeCounter:TextField;
		public var tF_timeCounterWaiting:TextField;
		public var tF_Title3:TextField;
		public var tF_Title1:TextField;
		public var tF_Title2:TextField;		

		public var ReviveCtrl_mc:MovieClip;
		public var btn_Revive_Around:Button;
		public var btn_Revive_Coin:Button;
		public var btn_Revive_Free:Button;
		
		public var tF_Revive1:TextField;
		public var tF_Revive2:TextField;
		public var tF_Revive3:TextField;
		public var tF_Revive1_Info:TextField;
		public var tF_Revive2_Info:TextField;
		public var tF_Revive3_Info:TextField;
		public var mcMoney1:MovieClip;
		public var mcMoney2:MovieClip;
		
		public var mapType:Number = 0;
		public var mapTypeName:String = "";
		public var itemCount:Number = 0;
		public var reqObject:Object = null;
		public var reqMoney:Number = 2000;
		public var playerMoney:Number = 0;
		public var reviveCountDown:Number = 60;
		public var reviveCountDownWaiting:Number = 10;
		public var timerCountDown:Timer = new Timer(1000);
		public var timerCountDownWaiting:Timer = new Timer(1000);
		
		public var Revive_NormolItem:Array = [70,120];
		public var Revive_MedicineItem:Array = [54,93,132];

		override protected function configUI():void
		{
			super.configUI();
			
			if(ReviveCtrl_mc){
				btn_Revive_Around 	= ReviveCtrl_mc.getChildByName("btn_Revive_Around") as Button;
				btn_Revive_Coin		= ReviveCtrl_mc.getChildByName("btn_Revive_Coin") as Button;
				btn_Revive_Free		= ReviveCtrl_mc.getChildByName("btn_Revive_Free") as Button;
			}
			
			if(btn_Revive_Around)
			{
				tF_Revive1 		= btn_Revive_Around.getChildByName("tF_Revive1") as TextField;
				tF_Revive1_Info	= btn_Revive_Around.getChildByName("tF_Revive1_Info") as TextField;
				mcMoney1 		= btn_Revive_Around.getChildByName("mcMoney1") as MovieClip;				
			}
			
			if(btn_Revive_Coin)
			{
				tF_Revive2 		= btn_Revive_Coin.getChildByName("tF_Revive2") as TextField;
				tF_Revive2_Info	= btn_Revive_Coin.getChildByName("tF_Revive2_Info") as TextField;
				mcMoney2 		= btn_Revive_Coin.getChildByName("mcMoney2") as MovieClip;				
			}			
			
			if(btn_Revive_Free)
			{
				tF_Revive3 		= btn_Revive_Free.getChildByName("tF_Revive3") as TextField;
				tF_Revive3_Info	= btn_Revive_Free.getChildByName("tF_Revive3_Info") as TextField;
			}						
			showTipsNone(null);
			
			ExternalInterface.call( "RegisterDeath", this);

			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
			timerCountDownWaiting.addEventListener(TimerEvent.TIMER, timerHandleWaiting);
			

			btn_Revive_Around.addEventListener("click",function _clickRevive(e:Event){ clickRevive(e,revive_Around);});
			btn_Revive_Around.addEventListener(MouseEvent.MOUSE_DOWN,function rollHandler(e:MouseEvent){
		    if(btn_Revive_Around.state=="down"){
				 tF_Revive1.textColor=0xb5b4b4;
				 tF_Revive1_Info.textColor=0xc4b686; }});
			btn_Revive_Coin.addEventListener("click",function _clickRevive(e:Event){ clickRevive(e,revive_Coin);});
			btn_Revive_Coin.addEventListener(MouseEvent.MOUSE_DOWN,function rollHandler(e:MouseEvent){
		    if(btn_Revive_Coin.state=="down"){
				 tF_Revive2.textColor=0xb5b4b4;
				 tF_Revive2_Info.textColor=0xc4b686; }});
			btn_Revive_Free.addEventListener("click",function _clickRevive(e:Event){ clickRevive(e,revive_Free);});
			btn_Revive_Free.addEventListener(MouseEvent.MOUSE_DOWN,function rollHandler(e:MouseEvent){
		    if(btn_Revive_Free.state=="down"){
				 tF_Revive3.textColor=0xb5b4b4;
				 tF_Revive3_Info.textColor=0xc4b686; }});
			btn_Revive_Around.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,revive_Around);});
			btn_Revive_Coin.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,revive_Coin); });
			btn_Revive_Free.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,revive_Free); });
			btn_Revive_Around.addEventListener("rollOut",showTipsNone);
			btn_Revive_Coin.addEventListener("rollOut",showTipsNone);
			btn_Revive_Free.addEventListener("rollOut",showTipsNone);
			
			ShowMode = "CC";
			
			//updateBtnPos(true);
			//setRevive_FreeEnable(true);
			//setRevive_CoinEnable(false);
		}


		function timerHandle():void
		{

			reviveCountDown = reviveCountDown - 1;
			tF_timeCounter.text = "" + reviveCountDown;
			if (reviveCountDown<=0)
			{
				reviveCountDown = 0;
				timerCountDown.stop();
				ExternalInterface.call("ASRelife",revive_Free,0);
			}			
			
		}
		
		function timerHandleWaiting():void
		{
			reviveCountDownWaiting = reviveCountDownWaiting - 1;
			tF_timeCounterWaiting.text = "" + reviveCountDownWaiting;
			tF_Revive3.text = "免费复活" + "(" + reviveCountDownWaiting + ")";
			
			if (reviveCountDownWaiting <= 0)
			{
				setRevive_FreeEnable(true);
				tF_Revive3.text = "免费复活";
				reviveCountDownWaiting = 0;
				timerCountDownWaiting.stop();
				timeCountStart();
				
			}			
			
		}		

		public function ResetDeathType():void
		{
			ExternalInterface.call("GetCurrentMapType",this,"mapType");
			if (mapType == 2)
			{
				mapTypeName = "Dungeon";
				//ShowRevive(true,1);
				//ShowRevive(true,2);
				//ShowRevive(true,3);
			}
			else if (mapType == 3)
			{
				mapTypeName = "BattleField";
				//ShowRevive(false,1);
				//ShowRevive(false,2);
				//ShowRevive(false,3);
			}
			else if (mapType == 4)
			{
				mapTypeName = "Arena";
				//ShowRevive(false,0);
			}
			else if (mapType == 7)//E_est_Guild
			{
				//ShowRevive(false,1);
				//ShowRevive(false,2);
				//ShowRevive(true, 3);
			}
			else
			{
				mapTypeName = "Static";
				//ShowRevive(true,1);
				//ShowRevive(true,2);
				//ShowRevive(true,3);
			}
			
			ReviveCtrl_mc.visible = true;
			//tF_Title1.visible = true;
			//tF_Title2.visible = true;
			//tF_timeCounter.visible = true;
			//tF_timeCounterWaiting.visible = false;
			//tF_Title3.visible = false;
			setTimeCountTxtShow(false);
			setTimeWaitingTxtShow(false);
			ResetBtn();
		}
		
		public function ShowWaitingRevive(nCountDown:Number):void
		{
			ExternalInterface.call("ASTrace","ShowWaitingRevive");
			ReviveCtrl_mc.visible = false;
			tF_Title1.visible = false;
			tF_Title2.visible = false;
			tF_timeCounter.visible = false;
			tF_timeCounterWaiting.visible = true;
			tF_Title3.visible = true;
			
			tF_timeCounterWaiting.text = ""+nCountDown;
			reviveCountDownWaiting = nCountDown;
			timerCountDownWaiting.start();
			
		}
		
		public function ShowRevive(bShow:Boolean,group:Number):void
		{
			if (group==1)
			{
				btn_Revive_Around.visible = bShow;

			}
			else if (group==2)
			{
				btn_Revive_Coin.visible = bShow;
				//tF_Revive2.visible = bShow;
				//tF_Revive2_Info.visible = bShow;
				//mcMoney2.visible = bShow;
			}
			else if (group==3)
			{
				btn_Revive_Free.visible = bShow;
				//tF_Revive3.visible = bShow;
				//tF_Revive3_Info.visible = bShow;
			}
			else
			{
				btn_Revive_Around.visible = bShow;
				//tF_Revive1.visible = bShow;
				//tF_Revive1_Info.visible = bShow;
				//btn_gainReviveCoin.visible = bShow;
				//mcMoney1.visible = bShow;

				btn_Revive_Coin.visible = bShow;
				//tF_Revive2.visible = bShow;
				//tF_Revive2_Info.visible = bShow;
				//mcMoney2.visible = bShow;

				btn_Revive_Free.visible = bShow;
				//tF_Revive3.visible = bShow;
				//tF_Revive3_Info.visible = bShow;
			}
		}

		public function InitLoad():void
		{
			trace("InitLoad");
			ResetDeathType();

			ExternalInterface.call( "SetTextByID",tF_Title1,"MMOGame.reviveDialog.textTitle1");
			ExternalInterface.call( "SetTextByID",tF_Title2,"MMOGame.reviveDialog.textTitle2"+mapTypeName);
			ExternalInterface.call( "SetTextByID",tF_Revive1,"MMOGame.reviveDialog.textRevive1"+mapTypeName);
			ExternalInterface.call( "SetTextByID",tF_Revive2,"MMOGame.reviveDialog.textRevive2"+mapTypeName);
			ExternalInterface.call( "SetTextByID",tF_Revive3,"MMOGame.reviveDialog.textRevive3"+mapTypeName);
			ExternalInterface.call( "SetTextByID",tF_Revive1_Info,"MMOGame.reviveDialog.textRevive1Info");
			ExternalInterface.call( "SetTextByID",tF_Revive2_Info,"MMOGame.reviveDialog.textRevive2Info");
			ExternalInterface.call( "SetTextByID",tF_Revive3_Info,"MMOGame.reviveDialog.textRevive3Info");

			//得到复活币道具数量;
			ExternalInterface.call("GetItemCountByID",this,"itemCount", reqObject.ReqItemID);// 100001);
			tF_Revive1_Info.text = ""+reqObject.ReqItemCount+  "/" + itemCount ;
			tF_Revive1.textColor=0xffffff;
			tF_Revive1_Info.textColor=0xfff0be;
			
			if(itemCount>=reqObject.ReqItemCount)
				updateBtnPos(true);
			else
				updateBtnPos(false);
			
			//得到游戏币数量
			ExternalInterface.call("GetPlayerGold",this,"playerMoney");
			tF_Revive2_Info.text = ""+ reqObject.ReqMoney;// + playerMoney ;
			if (playerMoney>=reqObject.ReqMoney && reqObject.PlayerKilled)
			{
				setRevive_CoinEnable(true);
			}
			else
			{
				setRevive_CoinEnable(false);

			}
			
			
			//得到死亡复活倒计时
			
			//tF_Revive1.textColor=tF_Revive1_Info.textColor=0x686868;
			//tF_Revive2.textColor=tF_Revive2_Info.textColor=0x686868;
			
			if(reqObject.PlayerKilled && reqObject.WaitTime > 0)
			{
				timeWaitingStart();
			}
			else
			{
				timeCountStart();
			}
			

		}
		
		public function timeCountStart():void
		{
			setTimeCountTxtShow(true);
			setTimeWaitingTxtShow(false);
			
			ExternalInterface.call("GetReviveCountDown",this,"reviveCountDown");
			tF_timeCounter.text = "" + reviveCountDown;
			timerCountDown.start();
		}
		
		public function timeWaitingStart():void
		{
			setTimeCountTxtShow(false);
			setTimeWaitingTxtShow(true);

			tF_timeCounterWaiting.text = ""+reqObject.WaitTime;
			
			setRevive_FreeEnable(false);
			
			reviveCountDownWaiting = reqObject.WaitTime;
			timerCountDownWaiting.start();

		}
		
		public function setTimeCountTxtShow(v:Boolean):void
		{
			tF_Title1.visible = v;
			tF_Title2.visible = v;
			tF_timeCounter.visible = v;
		}
		
		public function setTimeWaitingTxtShow(v:Boolean):void
		{
			tF_timeCounterWaiting.visible = v
			tF_Title3.visible = v;
		}
		
		public function updateBtnPos(haveMedicine:Boolean):void
		{
			if(haveMedicine)
			{
				showBtnByMedicine(true,true);
				btn_Revive_Around.y = Revive_MedicineItem[0];
				btn_Revive_Coin.y = Revive_MedicineItem[1];
				btn_Revive_Free.y = Revive_MedicineItem[2];
			}
			else
			{
				showBtnByMedicine(true,false);
				btn_Revive_Coin.y = Revive_NormolItem[0];
				btn_Revive_Free.y = Revive_NormolItem[1];
			}
			
		}
		
		
		public function updateData(dat:Object):void
		{
			ResetBtn();
			reqMoney = dat.ReqMoney;
			reqObject = dat;
			InitLoad();
		}

		function clickRevive(e:Event,type:Number):void
		{
			if(type==revive_Coin)
			{
				if(btn_Revive_Coin.enabled == false)
				{
					return;
				}
			}
			else if(type==revive_Around)
			{
				if(btn_Revive_Around.enabled == false)
				{
					return;
				}
			}
			reviveCountDown = 0;
			timerCountDown.stop();
			reviveCountDownWaiting = 0;
			timerCountDownWaiting.stop();
			
			ExternalInterface.call("ASRelife",type,100001);
			
			
		}

		function showTipsNone(e:Event):void
		{
			tipinfo.visible=false;
			tipinfo.tF_Info.text = "";
		}

		public function showTips(e:Event,type:Number):void
		{
			if (type==revive_Around)
			{
                tipinfo.visible=true;
				ExternalInterface.call( "SetTextByID",tipinfo.tF_Info,"MMOGame.reviveDialog.textTips1"+mapTypeName);
			}
			else if (type==revive_Coin)
			{
			    tipinfo.visible=true;
				ExternalInterface.call( "SetTextByID",tipinfo.tF_Info,"MMOGame.reviveDialog.textTips2"+mapTypeName);
			}
			else if (type==revive_Free)
			{
			    tipinfo.visible=true;
				ExternalInterface.call( "SetTextByID",tipinfo.tF_Info,"MMOGame.reviveDialog.textTips3"+mapTypeName);
			}
			else
			{
				tipinfo.visible=false;
				tipinfo.tF_Info.text = "";
			}
		}

		public function ResetBtn():void
		{
			btn_Revive_Around.visible = false;
			btn_Revive_Coin.visible = false;
			btn_Revive_Free.visible = false;
		}
		
		public function showBtnByMedicine(v:Boolean,m:Boolean):void
		{
			btn_Revive_Around.visible = m;
			btn_Revive_Coin.visible = v;
			btn_Revive_Free.visible = v;
			layou(m);
		}
		
		private function layou(b:Boolean):void
		{
			if(b==true){
				btn_Revive_Around.y=54;
				btn_Revive_Coin.y=btn_Revive_Around.y+37;
			}else{
				btn_Revive_Coin.y=72;
			}
		   btn_Revive_Free.y=btn_Revive_Coin.y+37;
		}
		
		public function setRevive_FreeEnable(v:Boolean):void
		{
			btn_Revive_Free.enabled = v;
			if(v)
			{
				tF_Revive3.textColor = 0xffffff;
				tF_Revive3_Info.textColor = 0xfff0be;
			}
			else
			{
				tF_Revive3.textColor = tF_Revive3_Info.textColor = 0x686868;
			}
		}
		
		public function setRevive_CoinEnable(v:Boolean):void
		{
			btn_Revive_Coin.enabled = v;
			
			if (v)
			{
				tF_Revive2.textColor=0xffffff;
				tF_Revive2_Info.textColor=0xfff0be;
			}
			else
			{
				btn_Revive_Coin.enabled = false;
				btn_Revive_Coin.mouseEnabled = true;
			    tF_Revive2.textColor=tF_Revive2_Info.textColor=0x686868;

			}
		}

	}
}