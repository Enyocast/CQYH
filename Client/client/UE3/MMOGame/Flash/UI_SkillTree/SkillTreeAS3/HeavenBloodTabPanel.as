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
	import ActionScript3.MyTipButton;
	
	public class HeavenBloodTabPanel extends UIComponent
	{
		public var bloodtype0:MyTipButton;
		public var bloodtype1:MyTipButton;
		public var bloodtype2:MyTipButton;
		public var bloodtype3:MyTipButton;
		public var bloodtype4:MyTipButton;
		public var bloodtype5:MyTipButton;
		public var bloodtype6:MyTipButton;
		public var bloodtype7:MyTipButton;
		public var bloodtype8:MyTipButton;
		public var bloodtype9:MyTipButton;
		public var completeState_tf:TextField;
		
		public var bloodLink0_mc:MovieClip;
		public var bloodLink1_mc:MovieClip;
		public var bloodLink2_mc:MovieClip;
		public var bloodLink3_mc:MovieClip;
		public var bloodLink4_mc:MovieClip;
		public var bloodLink5_mc:MovieClip;
		public var bloodLink6_mc:MovieClip;
		public var bloodLink7_mc:MovieClip;
		public var bloodLink8_mc:MovieClip;
		
		
		public var nodeMax0_mc:MovieClip;
		public var nodeMax1_mc:MovieClip;
		public var nodeMax2_mc:MovieClip;
		public var nodeMax3_mc:MovieClip;
		public var nodeMax4_mc:MovieClip;
		public var nodeMax5_mc:MovieClip;
		public var nodeMax6_mc:MovieClip;
		public var nodeMax7_mc:MovieClip;
		public var nodeMax8_mc:MovieClip;
		public var nodeMax9_mc:MovieClip;
		
		public var lock0:MovieClip;
		public var lock1:MovieClip;
		public var lock2:MovieClip;
		public var lock3:MovieClip;
		public var lock4:MovieClip;
		public var lock5:MovieClip;
		public var lock6:MovieClip;
		public var lock7:MovieClip;
		public var lock8:MovieClip;
		public var lock9:MovieClip;
		
		public var openBloodFx_mc:MovieClip;
		
		public var bloodState_mc:MovieClip;
		public var changeState_mc:MovieClip;
	
		
		public var PanelIndex:int = 0;
		
		public var bloodData:HeavenBloodData;
		var arrBtn:Array = new Array;
		var arrBtnMax:Array = new Array;
		var arrBtnLink:Array = new Array;
		var arrClipLock:Array = new Array;
		
		override protected function configUI():void
		{
			trace(">>>>>>>>>>>>>>> HeavenBloodTabPanel::configUI");
			super.configUI();

trace("#### HeavenBloodTabPanel::configUI 1",bloodtype0,bloodtype1,bloodtype2,bloodtype3,bloodtype4);
trace("#### HeavenBloodTabPanel::configUI 2",bloodtype5,bloodtype6,bloodtype7,bloodtype8,bloodtype9);
			bloodtype0.addEventListener(ButtonEvent.CLICK,ClickLevelBtn0);
			bloodtype1.addEventListener(ButtonEvent.CLICK,ClickLevelBtn1);
			bloodtype2.addEventListener(ButtonEvent.CLICK,ClickLevelBtn2);
			bloodtype3.addEventListener(ButtonEvent.CLICK,ClickLevelBtn3);
			bloodtype4.addEventListener(ButtonEvent.CLICK,ClickLevelBtn4);
			bloodtype5.addEventListener(ButtonEvent.CLICK,ClickLevelBtn5);
			bloodtype6.addEventListener(ButtonEvent.CLICK,ClickLevelBtn6);
			bloodtype7.addEventListener(ButtonEvent.CLICK,ClickLevelBtn7);
			bloodtype8.addEventListener(ButtonEvent.CLICK,ClickLevelBtn8);
			bloodtype9.addEventListener(ButtonEvent.CLICK,ClickLevelBtn9);
			
			bloodtype0.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot0);
			bloodtype0.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype1.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot1);
			bloodtype1.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype2.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot2);
			bloodtype2.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype3.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot3);
			bloodtype3.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype4.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot4);
			bloodtype4.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype5.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot5);
			bloodtype5.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype6.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot6);
			bloodtype6.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype7.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot7);
			bloodtype7.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype8.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot8);
			bloodtype8.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			bloodtype9.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot9);
			bloodtype9.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			
			nodeMax0_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot0);
			nodeMax0_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax1_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot1);
			nodeMax1_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax2_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot2);
			nodeMax2_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax3_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot3);
			nodeMax3_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax4_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot4);
			nodeMax4_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax5_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot5);
			nodeMax5_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax6_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot6);
			nodeMax6_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax7_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot7);
			nodeMax7_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax8_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot8);
			nodeMax8_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			nodeMax9_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot9);
			nodeMax9_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenLevelSlot);
			
			lock0.mouseEnabled = false;
			lock1.mouseEnabled = false;
			lock2.mouseEnabled = false;
			lock3.mouseEnabled = false;
			lock4.mouseEnabled = false;
			lock5.mouseEnabled = false;
			lock6.mouseEnabled = false;
			lock7.mouseEnabled = false;
			lock8.mouseEnabled = false;
			lock9.mouseEnabled = false;
			
			openBloodFx_mc.mouseEnabled = false;
			
			arrBtn.push(bloodtype0);
			arrBtn.push(bloodtype1);
			arrBtn.push(bloodtype2);
			arrBtn.push(bloodtype3);
			arrBtn.push(bloodtype4);
			arrBtn.push(bloodtype5);
			arrBtn.push(bloodtype6);
			arrBtn.push(bloodtype7);
			arrBtn.push(bloodtype8);
			arrBtn.push(bloodtype9);
			
			arrBtnMax.push(nodeMax0_mc);
			arrBtnMax.push(nodeMax1_mc);
			arrBtnMax.push(nodeMax2_mc);
			arrBtnMax.push(nodeMax3_mc);
			arrBtnMax.push(nodeMax4_mc);
			arrBtnMax.push(nodeMax5_mc);
			arrBtnMax.push(nodeMax6_mc);
			arrBtnMax.push(nodeMax7_mc);
			arrBtnMax.push(nodeMax8_mc);
			arrBtnMax.push(nodeMax9_mc);
			
			arrBtnLink.push(bloodLink0_mc);
			arrBtnLink.push(bloodLink1_mc);
			arrBtnLink.push(bloodLink2_mc);
			arrBtnLink.push(bloodLink3_mc);
			arrBtnLink.push(bloodLink4_mc);
			arrBtnLink.push(bloodLink5_mc);
			arrBtnLink.push(bloodLink6_mc);
			arrBtnLink.push(bloodLink7_mc);
			arrBtnLink.push(bloodLink8_mc);
			
			arrClipLock.push(lock0);
			arrClipLock.push(lock1);
			arrClipLock.push(lock2);
			arrClipLock.push(lock3);
			arrClipLock.push(lock4);
			arrClipLock.push(lock5);
			arrClipLock.push(lock6);
			arrClipLock.push(lock7);
			arrClipLock.push(lock8);
			arrClipLock.push(lock9);
			
			trace(">>>>>>>>>>>>>>> HeavenBloodTabPanel::configUI");
		}
		
		function ClickLevelBtn0()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 0,PanelIndex);
		}
		function ClickLevelBtn1()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 1,PanelIndex);
		}
		function ClickLevelBtn2()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 2,PanelIndex);
		}
		function ClickLevelBtn3()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 3,PanelIndex);
		}
		function ClickLevelBtn4()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 4,PanelIndex);
		}
		function ClickLevelBtn5()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 5,PanelIndex);
		}
		function ClickLevelBtn6()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 6,PanelIndex);
		}
		function ClickLevelBtn7()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 7,PanelIndex);
		}
		function ClickLevelBtn8()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 8,PanelIndex);
		}
		function ClickLevelBtn9()
		{
			ExternalInterface.call( "ASClickBtnLevelState", 9,PanelIndex);
		}
		
		public function UpdateBloodPanelState(nPanel:int,nState:int)
		{
			if(bloodData == null)
					return;
			if(PanelIndex == nPanel)
			{
				openBloodFx_mc.gotoAndPlay("start");
				bloodData.bActivate = true;
				this.visible = true;
			}
		}
		public function UpdateBloodSlotState(nPanel:int,nIndex:int,nState:int)
		{
			if(PanelIndex == nPanel)
			{
				if(bloodData == null)
					return;
				if(nState > 0)
					changeState_mc.gotoAndPlay("in");
				
				var nComp:int = bloodData.nCompleteState;
					nComp -= bloodData.arrLevel[nIndex];
					nComp += nState;
					SetBloodCompleteState(nComp);
					bloodData.nCompleteState = nComp;
				
				if(nIndex < 9&&nIndex >= 0)
				{
					if(bloodData.arrLevel[nIndex] == 0&&nState>0)
					{
						arrBtnLink[nIndex].gotoAndPlay("on");
						arrClipLock[nIndex + 1].gotoAndPlay("start");
					}
					
					if((nState > 0))
					{
						//arrClipLock[nIndex].visible = (bloodData.arrLevel[nIndex + 1] > 0);
						arrBtn[nIndex + 1].getChildByName("clickHint").visible = (bloodData.arrLevel[nIndex + 1] < 10);
						arrBtn[nIndex].getChildByName("clickHint").visible = (bloodData.arrLevel[nIndex] < 10);
					}
					else
					{
						if(nIndex == 0)
							arrBtn[0].getChildByName("clickHint").visible = true;
						//arrClipLock[nIndex].visible = (nIndex > 0);
						arrBtn[nIndex+1].getChildByName("clickHint").visible = false;
					}
				}
				
				if(nIndex < 10&&nIndex >= 0)
				{
					bloodData.arrLevel[nIndex] = nState;
					
					if(nState >= 10)
					{
						arrBtn[nIndex].visible = false;
						arrBtnMax[nIndex].visible = true;
						arrBtnMax[nIndex].getChildByName("levelNum_tf").text = nState.toString();
					}
					else if(nState == 0)
					{
						arrBtn[nIndex].visible = true;
						arrBtnMax[nIndex].visible = false;
						arrBtn[nIndex].getChildByName("levelNum_tf").text = "";
					}
					else
					{
						arrBtn[nIndex].visible = true;
						arrBtnMax[nIndex].visible = false;
						arrBtn[nIndex].getChildByName("levelNum_tf").text = nState.toString();
					}
				}
			}
		}
		public function SetBloodPanelIndex( nIndex:int)
		{
			PanelIndex = nIndex;
		}
		public function SetBloodCompleteState(nState:int)
		{
			bloodState_mc.visible = (nState >= 100);
			completeState_tf.text = nState.toString() + "%";
		}
		public function SetLevelStateVisible(bShow:Boolean)
		{
			this.visible = bShow;
		}
		public function SetBloodData(data:HeavenBloodData)
		{
			trace("++++++++++++++++++++++++SetBloodData  0",bloodData);
			bloodData = data;
			if(data)
			{
				SetBloodCompleteState(data.nCompleteState);
				for(var n:int = 0; n < 10; ++n)
				{
					if(n < data.arrLevel.length)
					{
						if(data.arrLevel[n] >= 10)
						{
							arrBtn[n].visible = false;
							arrBtnMax[n].visible = true;
							arrBtnMax[n].getChildByName("levelNum_tf").text = data.arrLevel[n].toString();
							
						}
						else if(data.arrLevel[n] == 0)
						{
							arrBtn[n].visible = true;
							arrBtnMax[n].visible = false;
							arrBtn[n].getChildByName("levelNum_tf").text = "";
						}
						else
						{
							arrBtn[n].visible = true;
							arrBtnMax[n].visible = false;
							arrBtn[n].getChildByName("levelNum_tf").text = data.arrLevel[n].toString();
							
						}
						arrBtn[n].getChildByName("textField").text = data.arrSlotName[n].toString();
						arrBtnMax[n].getChildByName("textField").text = data.arrSlotName[n].toString();
						if(n < 9)
						{
							if((data.arrLevel[n] > 0))
							{
								arrBtnLink[n].gotoAndStop("selected");
								//arrClipLock[n].visible = (data.arrLevel[n + 1] > 0);
								arrBtn[n + 1].getChildByName("clickHint").visible = (data.arrLevel[n + 1] == 0);
								arrBtn[n].getChildByName("clickHint").visible = (data.arrLevel[n] < 10);
							}
							else
							{
								arrBtnLink[n].gotoAndStop("off");
								//arrClipLock[n].visible = (n > 0);
								if(n == 0)
									arrBtn[0].getChildByName("clickHint").visible = true;
								arrBtn[n+1].getChildByName("clickHint").visible = false;
							}
						}
					}
					else
					{
						arrBtn[n].getChildByName("levelNum_tf").text = "";
						arrBtn[n].getChildByName("textField").text = "";
					}
				}
			}
			trace("++++++++++++++++++++++++SetBloodData  1",bloodData);
		}
		function onRollOverHeavenLevelSlot0( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,0,PanelIndex );
		}

		function onRollOverHeavenLevelSlot1( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,1,PanelIndex);
		}

		function onRollOverHeavenLevelSlot2( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,2,PanelIndex);
		}

		function onRollOverHeavenLevelSlot3( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,3,PanelIndex);
		}
		
		function onRollOverHeavenLevelSlot4( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,4,PanelIndex);
		}

		function onRollOverHeavenLevelSlot5( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,5,PanelIndex);
		}

		function onRollOverHeavenLevelSlot6( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,6,PanelIndex);
		}
		
		function onRollOverHeavenLevelSlot7( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,7,PanelIndex);
		}

		function onRollOverHeavenLevelSlot8( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,8,PanelIndex);
		}

		function onRollOverHeavenLevelSlot9( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			ExternalInterface.call("ASShowTips_HeavenBloodSlot",this,9,PanelIndex);
		}

		function onRollOutHeavenLevelSlot( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			ExternalInterface.call("ASHideTips_HeavenBloodSlot" );
		}
	}
}
