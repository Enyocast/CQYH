package UI_TradeP2P.TradeP2PAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.TextInput;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import UI_TradeP2P.TradeP2PAS3.ItemSlotContainer;
	
	public class TradeItemSlotContainer extends UIComponent
	{
		public var tf_playerName:TextField;
		public var tradeLock_mc:MovieClip;
		public var btnInputMny:Button;
		
		public var tradeItem0:ItemSlotContainer;
		public var tradeItem1:ItemSlotContainer;
		public var tradeItem2:ItemSlotContainer;
		public var tradeItem3:ItemSlotContainer;
		public var tradeItem4:ItemSlotContainer;
		public var tradeItem5:ItemSlotContainer;

		
		override protected  function configUI():void
		{
			super.configUI();
			//
			mouseChildren = true;
			
			tradeLock_mc.visible = false;
			tradeLock_mc.mouseEnabled = false;
			tradeLock_mc.mouseChildren = true;
			btnInputMny.addEventListener( MouseEvent.CLICK, InputTradeMoney );
		}
		//
		function InputTradeMoney( e:Event )
		{
			ExternalInterface.call( "ASInputP2PTradeMoney" );
		}
	}
}