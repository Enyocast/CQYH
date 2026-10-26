package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.utils.getTimer;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.events.Event;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Common.Events.ParamEvent;

	public class BuffPanel extends MyPanel
	{
		var TimeFrame:Number = 200;//时间侦听间隔
		var WanTime:Number = 4000;
		var timerCountDown:Timer = new Timer(TimeFrame);
		var StackCount:Array = [0,0,0,0,0,0,0,0,0,0,0,0,0,0];
		var CurTime:Array = [0,0,0,0,0,0,0,0,0,0,0,0,0,0];
		var MaxTime:Array = [1,1,1,1,1,1,1,1,1,1,1,1,1,1];
		var WanFlag:Array = [0,0,0,0,0,0,0,0,0,0,0,0,0,0];
		var ShowTimeUp:Array = [1,1,1,1,1,1,1,1,1,1,1,1,1,1];
		var BuffID:Array = [0,0,0,0,0,0,0,0,0,0,0,0,0,0];
		var BuffIcon:Array = ["","","","","","","","","","","","","",""];
		var DeltaTime:uint = 0;
		var LastTime:uint = 0;
		public var BuffOwnerID:uint = 0;
		public var curBuffSlotID:uint = 0;
		public var curBuffID:uint = 0;


		override protected function configUI():void
		{
			this.ShowMode="BUFF";
			super.configUI();
			var buffSlot0:MovieClip =(getChildByName("buffSlot"+0) as MovieClip);
			if (buffSlot0!=null)
			{
				buffSlot0.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,0);});
				buffSlot0.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,0);});
				buffSlot0.addEventListener("rollOut",RollOut );
			}

			var buffSlot1:MovieClip =(getChildByName("buffSlot"+1) as MovieClip);
			if (buffSlot1!=null)
			{
				buffSlot1.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,1);});
				buffSlot1.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,1);});
				buffSlot1.addEventListener("rollOut",RollOut );
			}

			var buffSlot2:MovieClip =(getChildByName("buffSlot"+2) as MovieClip);
			if (buffSlot2!=null)
			{
				buffSlot2.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,2);});;
				buffSlot2.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,2);});
				buffSlot2.addEventListener("rollOut",RollOut );
			}

			var buffSlot3:MovieClip =(getChildByName("buffSlot"+3) as MovieClip);
			if (buffSlot3!=null)
			{
				buffSlot3.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,3);});;
				buffSlot3.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,3);});
				buffSlot3.addEventListener("rollOut",RollOut );
			}

			var buffSlot4:MovieClip =(getChildByName("buffSlot"+4) as MovieClip);
			if (buffSlot4!=null)
			{
				buffSlot4.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,4);});;
				buffSlot4.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,4);});
				buffSlot4.addEventListener("rollOut",RollOut );
			}

			var buffSlot5:MovieClip =(getChildByName("buffSlot"+5) as MovieClip);
			if (buffSlot5!=null)
			{
				buffSlot5.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,5);});;
				buffSlot5.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,5);});
				buffSlot5.addEventListener("rollOut",RollOut );
			}

			var buffSlot6:MovieClip =(getChildByName("buffSlot"+6) as MovieClip);
			if (buffSlot6!=null)
			{
				buffSlot6.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,6);});;
				buffSlot6.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,6);});
				buffSlot6.addEventListener("rollOut",RollOut );
			}

			var buffSlot7:MovieClip =(getChildByName("buffSlot"+7) as MovieClip);
			if (buffSlot7!=null)
			{
				buffSlot7.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,7);});;
				buffSlot7.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,7);});
				buffSlot7.addEventListener("rollOut",RollOut );
			}

			var buffSlot8:MovieClip =(getChildByName("buffSlot"+8) as MovieClip);
			if (buffSlot8!=null)
			{
				buffSlot8.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,8);});;
				buffSlot8.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,8);});
				buffSlot8.addEventListener("rollOut",RollOut );
			}

			var buffSlot9:MovieClip =(getChildByName("buffSlot"+9) as MovieClip);
			if (buffSlot9!=null)
			{
				buffSlot9.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,9);});;
				buffSlot9.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,9);});
				buffSlot9.addEventListener("rollOut",RollOut );
			}

			var buffSlot10:MovieClip =(getChildByName("buffSlot"+10) as MovieClip);
			if (buffSlot10!=null)
			{
				buffSlot10.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,10);});;
				buffSlot10.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,10);});
				buffSlot10.addEventListener("rollOut",RollOut );
			}

			var buffSlot11:MovieClip =(getChildByName("buffSlot"+11) as MovieClip);
			if (buffSlot11!=null)
			{
				buffSlot11.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,11);});;
				buffSlot11.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,11);});
				buffSlot11.addEventListener("rollOut",RollOut );
			}

			var buffSlot12:MovieClip =(getChildByName("buffSlot"+12) as MovieClip);
			if (buffSlot12!=null)
			{
				buffSlot12.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,12);});;
				buffSlot12.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,12);});
				buffSlot12.addEventListener("rollOut",RollOut );
			}

			var buffSlot13:MovieClip =(getChildByName("buffSlot"+13) as MovieClip);
			if (buffSlot13!=null)
			{
				buffSlot13.addEventListener(MouseEvent.CLICK , function _MouseRightClick(e:Event){  MouseRightClick(e,13);});;
				buffSlot13.addEventListener("rollOver",function _showTips(e:Event){ showTips(e,13);});
				buffSlot13.addEventListener("rollOut",RollOut );
			}


			for (var i:int=0; i<14; i++)
			{
				HideBuff(i);
			}
			LastTime = getTimer();
			DeltaTime = 0;
			timerCountDown.addEventListener(TimerEvent.TIMER, timeUpHandle);
			timerCountDown.start();
			stageChangeHandler(null);
		}

		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.y = cavasHeight - 8;
			this.x =(cavasWidth-976>>1)+430;
		}

		public function MouseRightClick( e:Event, slot:Number)
		{
			if ((e as MouseEventEx).buttonIdx == 1)
			{
				curBuffSlotID = slot;
				curBuffID = BuffID[slot];
				ExternalInterface.call("MouseRightClickBuff", this,curBuffID,curBuffSlotID );
				ExternalInterface.call("ASHideTips");
				return;
			}
		}

		function showTips(e:Event,slot:Number)
		{
			curBuffSlotID = slot;
			curBuffID = BuffID[slot];
			ExternalInterface.call("ASShowTips_BuffSlot",this,curBuffID,curBuffSlotID );
			//TFT_BuffSlot = 4;
			//this["root"].ChangeTips();
		}

		public function HideTips()
		{
			if (root["tooltips_mc"] != null)
			{
				root["tooltips_mc"].visible = false;
			}
		}

		public function RollOut( e:Event  )
		{
			HideTips();
			ExternalInterface.call("ASRollOutItemSlot",this );
		}

		public function HideBuff( buffSlotID:Number)
		{
			var buffSlot:MovieClip =(getChildByName("buffSlot"+buffSlotID) as MovieClip);
			buffSlot.visible = false;
		}


		public function ShowTime( buffSlot:MovieClip, buffCurTime:Number ,bShowTimeUp:uint )
		{
			if (bShowTimeUp)
			{
				var d = Math.floor(buffCurTime/(60*60*24*1000));
				var h = Math.floor(buffCurTime/(60*60*1000));
				var m = Math.floor(buffCurTime / (60 * 1000));
				var s = Math.floor(buffCurTime/(1000));
				if (d>=1)
				{
					(buffSlot.getChildByName("tF_time")  as TextField).text = ""+d+"d" ;
				}
				else if (h>=1)
				{
					(buffSlot.getChildByName("tF_time")  as TextField).text = ""+h+"h" ;
				}
				else if (m>=1)
				{
					(buffSlot.getChildByName("tF_time")  as TextField).text = ""+m+"m" ;
				}
				else if (s>=1)
				{
					(buffSlot.getChildByName("tF_time")  as TextField).text = ""+s+"s" ;
				}
				else
				{
					(buffSlot.getChildByName("tF_time")  as TextField).text = "0";
				}
			}
			else
			{
				(buffSlot.getChildByName("tF_time")  as TextField).text = "";
			}
		}

		public function ShowBuff( buffSlotID:uint, buffIcon:String,  buffMaxTime:Number,  buffCurTime:Number, stackCount:uint , OwnerID:uint, buffID:uint, bShowTimeUp:uint,  debuff:Boolean)
		{
			var buffSlot:MovieClip =(getChildByName("buffSlot"+buffSlotID) as MovieClip);
			ShowTime(buffSlot,buffCurTime,bShowTimeUp);

			var iconBk:MovieClip =(buffSlot.getChildByName("buff_mc")  as MovieClip);
			if (iconBk)
			{
				if (buffIcon.length > 0)
				{
					if(BuffIcon[buffSlotID]!=buffIcon)
					{
						BuffIcon[buffSlotID]=buffIcon;
						(iconBk.getChildByName("itemIconLoader_mc") as UILoader).source = "img://"+ buffIcon;
					}
				}
				else
				{
					if(BuffIcon[buffSlotID]!=buffIcon)
					{
						BuffIcon[buffSlotID]=buffIcon;
						(iconBk.getChildByName("itemIconLoader_mc") as UILoader).source = null;
					}
				}
			}

			var tFStack:TextField =(buffSlot.getChildByName("tF_stack")  as TextField);
			if (tFStack)
			{
				//if(StackCount[buffSlotID]!=stackCount)
				{
					StackCount[buffSlotID]=stackCount;
					if(stackCount>1){
						tFStack.text = "" + stackCount;
					}
					else
					{
						tFStack.text = "";
					}
				}
			}

			BuffID[buffSlotID] = buffID;
//			ShowTimeUp[buffSlotID] = bShowTimeUp;
			BuffOwnerID = OwnerID;
			CurTime[buffSlotID] = buffCurTime;
			MaxTime[buffSlotID] = buffMaxTime;
//			StackCount[buffSlotID] = stackCount;
//			WanFlag[buffSlotID] = 0;
			buffSlot.SetDebuff(debuff);
			if (bShowTimeUp==0)
			{
				//if(ShowTimeUp[buffSlotID]!=bShowTimeUp)
				{
					ShowTimeUp[buffSlotID] = bShowTimeUp;
					buffSlot.ShowCD(false);
				}
			}
			else
			{
				if(ShowTimeUp[buffSlotID]!=bShowTimeUp)
				{
					ShowTimeUp[buffSlotID] = bShowTimeUp;					
					buffSlot.ShowCD(true);
				}
				buffSlot.SetDivide(buffMaxTime-buffCurTime,buffMaxTime);
			}
			
			if(WanFlag[buffSlotID]!=0)
			{
				WanFlag[buffSlotID]=0;
				buffSlot.SetState(WanFlag[buffSlotID]);
			}
			buffSlot.visible = true;
			//this.visible = true;

		}

		function timeUpHandle(e:TimerEvent)
		{
			//var CurrentTime:Number = getTimer();
			//DeltaTime = CurrentTime - LastTime;
			//LastTime = CurrentTime;

			for (var i=0; i<14; i++)
			{
				if (ShowTimeUp[i] && CurTime[i] > 0)
				{
					CurTime[i] = CurTime[i] - TimeFrame;
					if (CurTime[i] < 0)
					{
						CurTime[i] = 0;
					}

					var buffSlot:MovieClip =(getChildByName("buffSlot"+i) as MovieClip);
					if (buffSlot!=null)
					{
						if (CurTime[i] < WanTime && WanFlag[i] == 0)
						{
							WanFlag[i] = 1;
							buffSlot.SetState(WanFlag[i]);
						}

						if (ShowTimeUp[i])
						{
							buffSlot.SetDivide(MaxTime[i]-CurTime[i],MaxTime[i]);
						}

						ShowTime( buffSlot, CurTime[i], ShowTimeUp[i]);
					}

				}
			}
		}

	}
}