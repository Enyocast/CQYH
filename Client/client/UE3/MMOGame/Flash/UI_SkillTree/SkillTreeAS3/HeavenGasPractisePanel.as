package UI_SkillTree.SkillTreeAS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.data.DataBinding;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.MyPanel;

	public class HeavenGasPractisePanel extends MyPanel
	{
		public var gasPic1_mc:MovieClip;
		public var gasPic2_mc:MovieClip;
		public var gasPic3_mc:MovieClip;
		public var gasPic4_mc:MovieClip;
		public var gasPic5_mc:MovieClip;
		public var btn_PractiseGas1:Button;
		public var btn_PractiseGas2:Button;
		public var btn_PractiseGas3:Button;
		public var btn_PractiseGas4:Button;
		public var btn_PractiseGas5:Button;
		public var oneKeyBtnPractiseGas_mc:Button;
		public var openBtnGasExchange_mc:Button;
		public var XiuLianValue_tf:TextField;
		public var gasMoneyMc:MovieClip;
		public var getGasFx_mc:MovieClip;
		
		public var nCurState:int;

		override protected function configUI():void
		{
			super.configUI();
	
			btn_PractiseGas1.addEventListener(ButtonEvent.CLICK,ClickPractiseGas0);
			btn_PractiseGas2.addEventListener(ButtonEvent.CLICK,ClickPractiseGas1);
			btn_PractiseGas3.addEventListener(ButtonEvent.CLICK,ClickPractiseGas2);
			btn_PractiseGas4.addEventListener(ButtonEvent.CLICK,ClickPractiseGas3);
			btn_PractiseGas5.addEventListener(ButtonEvent.CLICK,ClickPractiseGas4);
			
			oneKeyBtnPractiseGas_mc.addEventListener(ButtonEvent.CLICK,ClickOneKeyPractise);
			openBtnGasExchange_mc.addEventListener(ButtonEvent.CLICK,ClickOpenExchangePanel);
			
			nCurState = 0;
			UCSetCurPractiseBtnState(1,0);
			UCSetCurPractiseBtnState(2,0);
			UCSetCurPractiseBtnState(3,0);
			UCSetCurPractiseBtnState(4,0);
			ExternalInterface.call( "ASTrace", "HeavenGasPractisePanel.configUI");
			ExternalInterface.call( "RegisterHeavenGasPractise", this);
		}
		
		public function ClickPractiseGas0()
		{
			ExternalInterface.call( "ASClickBtnPractiseGas", 1);
		}
		public function ClickPractiseGas1()
		{
			ExternalInterface.call( "ASClickBtnPractiseGas", 2);
		}
		public function ClickPractiseGas2()
		{
			ExternalInterface.call( "ASClickBtnPractiseGas", 3);
		}
		public function ClickPractiseGas3()
		{
			ExternalInterface.call( "ASClickBtnPractiseGas", 4);
		}
		public function ClickPractiseGas4()
		{
			ExternalInterface.call( "ASClickBtnPractiseGas", 5);
		}
		public function ClickOneKeyPractise()
		{
			ExternalInterface.call( "ASClickOneKeyPractise", this);
		}
		
		public function ClickOpenExchangePanel()
		{
			ExternalInterface.call( "ASClickOpenExchangePanel", this);
		}
		//播放动画类型
		public function UCPlayPractiseAnimation(nIndex:int)
		{
			 getGasFx_mc.gotoAndPlay("start");
		}
		public function UCSetXiuLianValue( data:int ):void
		{
			//XiuLianValue_tf.text = data.toString();
		}
		public function UCUpdateGasMoney( nNum:int )
		{
			XiuLianValue_tf.text = nNum.toString();
		}
		public function UCSetCurPractiseBtnState(curIndex:int,shwoState:int)
		{
			nCurState = curIndex;

			gasPic1_mc.visible = true;
			btn_PractiseGas1.enabled =  true;
			
			if(nCurState == 1)
			{
				gasPic2_mc.visible = (shwoState > 0);
				btn_PractiseGas2.enabled = (shwoState > 0);
			}
			else if(nCurState == 2)
			{
				gasPic3_mc.visible = (shwoState > 0);
				btn_PractiseGas3.enabled = (shwoState > 0);
			}
			else if(nCurState == 3)
			{
				gasPic4_mc.visible = (shwoState > 0);
				btn_PractiseGas4.enabled = (shwoState > 0);
			}
			else if(nCurState == 4)
			{
				gasPic5_mc.visible = (shwoState > 0);
				btn_PractiseGas5.enabled = (shwoState > 0);
			}
		}
	}
}