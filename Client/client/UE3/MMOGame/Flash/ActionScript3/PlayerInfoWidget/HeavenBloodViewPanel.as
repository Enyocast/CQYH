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
	import ActionScript3.MyTipButton;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.controls.UILoader;

	public class HeavenBloodViewPanel extends UIComponent
	{
		
		public var tabBlood1_mc:MyTipButton;
		public var tabBlood2_mc:MyTipButton;
		public var tabBlood3_mc:MyTipButton;
		public var tabBlood4_mc:MyTipButton;
		
		public var activeBloodBtn_mc:Button;
		
		public var  bloodTapPanel1:HeavenBloodViewTabPanel;
		public var  bloodTapPanel2:HeavenBloodViewTabPanel;
		public var  bloodTapPanel3:HeavenBloodViewTabPanel;
		public var  bloodTapPanel4:HeavenBloodViewTabPanel;
		
		public var bloodBackPic_mc:UILoader;
		
		public var nCurIndexPanel:int  = 0;
		
		public var arrTabBloodData:Array;
		
		override protected function configUI():void
		{
			super.configUI();
	
			tabBlood1_mc.addEventListener(ButtonEvent.CLICK,ClickBloodPanelTap0);
			tabBlood2_mc.addEventListener(ButtonEvent.CLICK,ClickBloodPanelTap1);
			tabBlood3_mc.addEventListener(ButtonEvent.CLICK,ClickBloodPanelTap2);
			tabBlood4_mc.addEventListener(ButtonEvent.CLICK,ClickBloodPanelTap3);

			bloodTapPanel1.SetBloodPanelIndex(0);
			bloodTapPanel2.SetBloodPanelIndex(1);
			bloodTapPanel3.SetBloodPanelIndex(2);
			bloodTapPanel4.SetBloodPanelIndex(3);
			
			/*
			var ArrData:Array = new Array;
			
			for(var n:int = 0; n < 4; ++n)
			{
				var nData:HeavenBloodData = new HeavenBloodData;
				nData.bActivate = false;
				nData.sName = "sds";
				nData.arrLevel = new Array;
				nData.arrSlotName = new Array;
				ArrData.push(nData);
			}
			UpdateHeavenBloodInfo(ArrData);*/
			trace(">>>>>>>>>>>>>>> HeavenBloodTabPanel::configUI  end ");
		}
		
		//播放动画类型
		public function UCUpdateBloodSlotState(nPanel:int,nIndex:int,nState:int)
		{
			 if(nCurIndexPanel == 0)
			 	bloodTapPanel1.UpdateBloodSlotState(nPanel,nIndex,nState);
			 else  if(nCurIndexPanel == 1)
			 	bloodTapPanel2.UpdateBloodSlotState(nPanel,nIndex,nState);
			 else  if(nCurIndexPanel == 2)
			 	bloodTapPanel3.UpdateBloodSlotState(nPanel,nIndex,nState);
			 else  if(nCurIndexPanel == 3)
			 	bloodTapPanel4.UpdateBloodSlotState(nPanel,nIndex,nState);
		}
		
		public function UCUpdateBloodPanelState(nPanel:int,nState:int)
		{
			 if(nCurIndexPanel == 0)
			 	bloodTapPanel1.UpdateBloodPanelState(nPanel,nState);
			 else  if(nCurIndexPanel == 1)
			 	bloodTapPanel2.UpdateBloodPanelState(nPanel,nState);
			 else  if(nCurIndexPanel == 2)
			 	bloodTapPanel3.UpdateBloodPanelState(nPanel,nState);
			 else  if(nCurIndexPanel == 3)
			 	bloodTapPanel4.UpdateBloodPanelState(nPanel,nState);
			activeBloodBtn_mc.visible = false;
		}
		
		function ClickBloodPanelTap0()
		{
			ShowPanelByIndex(0);
		}
		function ClickBloodPanelTap1()
		{
			ShowPanelByIndex(1);
		}
		function ClickBloodPanelTap2()
		{
			ShowPanelByIndex(2);
		}
		function ClickBloodPanelTap3()
		{
			ShowPanelByIndex(3);
		}

		function ShowPanelByIndex(nIndex:int)
		{ 
			nCurIndexPanel = nIndex;
			bloodTapPanel1.visible = (nIndex == 0);
			bloodTapPanel2.visible = (nIndex == 1);
			bloodTapPanel3.visible = (nIndex == 2);
			bloodTapPanel4.visible = (nIndex == 3);
			trace("ShowPanelByIndex",arrTabBloodData);
			if(arrTabBloodData)
			{
				var data:HeavenBloodViewData = arrTabBloodData[nCurIndexPanel] as HeavenBloodViewData;
				if(data)
				{
					trace("ShowPanelByIndex",data);
					activeBloodBtn_mc.visible = !data.bActivate;
					if(nCurIndexPanel == 0)
					{
						bloodTapPanel1.SetLevelStateVisible(data.bActivate);
						bloodBackPic_mc.source = "img://MMO_UIImg.heaven_fire";
					}
					else if(nCurIndexPanel == 1)
					{
						bloodTapPanel2.SetLevelStateVisible(data.bActivate);
						bloodBackPic_mc.source = "img://MMO_UIImg.heaven_wind";
					}
					else if(nCurIndexPanel == 2)
					{
						bloodTapPanel3.SetLevelStateVisible(data.bActivate);
						bloodBackPic_mc.source = "img://MMO_UIImg.heaven_water";
					}
					else if(nCurIndexPanel == 3)
					{
						bloodTapPanel4.SetLevelStateVisible(data.bActivate);
						bloodBackPic_mc.source = "img://MMO_UIImg.heaven_earth";
					}
					var conditionTf:TextField = activeBloodBtn_mc.getChildByName("activeCondition_tf") as TextField;
					if(conditionTf)
						conditionTf.text = data.sConditionHint;
					var stateTf:TextField = activeBloodBtn_mc.getChildByName("bloodName_tf") as TextField;
					if(stateTf)
						stateTf.text = data.sName;
				}   
			}
			else
				activeBloodBtn_mc.visible = false;
		}
		public function UpdateHeavenBloodInfo(data:Array)
		{
			trace("---------------------UCUpdateHeavenBloodInfo");
			arrTabBloodData = data;
			if(arrTabBloodData)
			{
				trace("++++++++++++++++++++++++UCUpdateHeavenBloodInfo  0",bloodTapPanel1);
				bloodTapPanel1.SetBloodData(arrTabBloodData[0]);
				trace("++++++++++++++++++++++++UCUpdateHeavenBloodInfo  1",bloodTapPanel2);
				bloodTapPanel2.SetBloodData(arrTabBloodData[1]);
				trace("++++++++++++++++++++++++UCUpdateHeavenBloodInfo  2",bloodTapPanel3);
				bloodTapPanel3.SetBloodData(arrTabBloodData[2]);
				trace("++++++++++++++++++++++++UCUpdateHeavenBloodInfo  3",bloodTapPanel4);
				bloodTapPanel4.SetBloodData(arrTabBloodData[3]);
			}
			trace("++++++++++++++++++++++++UCUpdateHeavenBloodInfo  4");
			ShowPanelByIndex(0);
		}
	}
}