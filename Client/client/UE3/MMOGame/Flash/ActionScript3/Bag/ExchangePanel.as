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
	import scaleform.clik.controls.TextInput;

	public class ExchangePanel extends UIComponent
	{
		public var getMoneyText:TextField;
		public var inputMoney:TextInput;
		public var exchangeButton:Button;
		public var cancelButton:Button;
		public var descText:TextField;
		
		public var moneyName0:TextField;
		public var moneyName1:TextField;
		public var curMoneyText0:TextField;
		public var curMoneyText1:TextField;

		override protected function configUI():void
		{
			super.configUI();
			
			exchangeButton.addEventListener( MouseEvent.CLICK , OnExchange );
			cancelButton.addEventListener( MouseEvent.CLICK , OnClose );
			
			inputMoney.addEventListener( Event.CHANGE , InputChange );
			inputMoney.textField.restrict = "0-9";
		}
		
		function OnExchange( e:Event )
		{
			
			ExternalInterface.call( "ASMoneyExchangeOk" );			
		}
		
		function OnClose( e:Event )
		{
			if( parent is MyPanel )
			{
				ExternalInterface.call( "ASOnPanelClose" , (parent as MyPanel).PanelName );			
			}
			
		}
		
		function InputChange()
		{
			if(inputMoney)
			{
				var money:int = int(inputMoney.text);
				if( money > 100000 )
				{
					inputMoney.text = "100000";
				}
			}
			ExternalInterface.call( "ASMoneyExchangeInputChange" );			
			//trace( inputMoney.text );
		}

		public function SetPanelText( data:Object )
		{
			if (! data)
			{
				return;
			}

			if(exchangeButton)
			{
				exchangeButton.label = data.exchangeButtonText;				
			}
			
			if(cancelButton)
			{
				cancelButton.label = data.cancelButtonText;
			}
			
			if(descText)
			{
				descText.htmlText = data.exchangeDescText;
			}
			if( moneyName0 )
			{
				moneyName0.htmlText = data.moneyNameText0;
			}
			if(moneyName1)
			{
				moneyName1.htmlText = data.moneyNameText1;
			}
		}
		
		public function UpdateCurMoney( data:Object )
		{
			if(curMoneyText0)
			{
				curMoneyText0.htmlText = data.curMoneyText0;
			}
			if(curMoneyText1)
			{
				curMoneyText1.htmlText = data.curMoneyText1;
			}
		}
		
		public function UpdateExchangeGold(gold:String)
		{
			getMoneyText.htmlText = gold;
		}
		
	}

}