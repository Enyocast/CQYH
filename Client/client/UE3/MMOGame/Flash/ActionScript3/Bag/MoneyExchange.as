package ActionScript3.Bag
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.display.MovieClip;
	import flash.utils.getDefinitionByName;
	import ActionScript3.Widget.MyTipsText;
	import ActionScript3.MyTipButtonNew;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;

	public class MoneyExchange extends MyPanel
	{
		public var tab0:RadioButton;
		public var tab1:RadioButton;
		public var exchangePanel_mc:ExchangePanel;
		public var logPanel_mc:LogPanel;
		
		

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			
			tab0.addEventListener( MouseEvent.CLICK, clickTab0 );
			tab1.addEventListener( MouseEvent.CLICK, clickTab1 );

			//ExternalInterface.call( "RegisterMoneyExchange", this );
			//this.setCenter();
			clickTab0(null);
			//GameDispathcher.getInstance().addEventListener(ParamEvent.STAGECHANGE,stageChangeHandler);
			//test
			//var data0:Object = { titleName:"金币兑换" , exchangeButtonText:"金币兑换" , cancelButtonText:"取消" , exchangeDescText:"1元宝=100金币"
			//, moneyNameText0:"元宝" , moneyNameText1:"金币" };
			//SetPanelText( data0 );
			
			//var data1:Object = { curMoneyText0:"55元宝" , curMoneyText1:"1188金币" };
			//UpdateCurMoney(data1);
			
			//UpdateShowLog( "您已兑换了13元宝\n您已兑换了31元宝" );
			
		}
		
/*	    private function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth=GameDispathcher.getInstance().StageWidth;
			this.cavasHeight=GameDispathcher.getInstance().StageHeight;
			this.setCenter();
		}*/

		public function SetPanelText( data:Object )
		{
			if (! data)
			{
				return;
			}
			this.SetWindowTitle(data.titleName);
			if(exchangePanel_mc)
			{
				exchangePanel_mc.SetPanelText(data);
			}
			if(logPanel_mc)
			{
				logPanel_mc.SetPanelText(data);
			}
		}
		
		public function UpdateCurMoney( data:Object )
		{
			exchangePanel_mc.UpdateCurMoney(data);
		}
		
		public function UpdateExchangeGold( gold:String )
		{
			exchangePanel_mc.UpdateExchangeGold(gold);
		}
		
		public function UpdateShowLog( log:String )
		{
			if(logPanel_mc)
			{
				logPanel_mc.UpdateShowLog(log);
			}
		}

		function clickTab0(evt:MouseEvent):void
		{
						
			exchangePanel_mc.visible = true;
			logPanel_mc.visible = false;
			
		}
		function clickTab1(evt:MouseEvent):void
		{
			exchangePanel_mc.visible = false;
			logPanel_mc.visible = true;
			
		}
		

		
	}

}