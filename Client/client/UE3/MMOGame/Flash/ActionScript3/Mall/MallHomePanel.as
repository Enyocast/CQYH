
package ActionScript3.Mall
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
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import flash.text.TextField;
	import flash.events.MouseEvent;

	public class MallHomePanel extends UIComponent
	{

		public var homeCheckIn_mc:MyTipButton;
		public var buyVipBtn_mc:MyTipButton;
		public var VipBtn_mc:MyTipButton;
		public var btnAddGold_mc:Button;
		public var money1_gold:TextField;
		public var tf_vipdec:TextField;
		
		public var mallAdv_mc:MallHomeShowUnit;

		override protected  function configUI():void 
		{		
			trace("------MallHomePanel  super.configUI:");
			super.configUI();			

			homeCheckIn_mc.addEventListener(MouseEvent.CLICK, 		onClickCheckIn );
			buyVipBtn_mc.addEventListener(MouseEvent.CLICK, 		onClickBuyVip );
			btnAddGold_mc.addEventListener(MouseEvent.CLICK, 		onClickAddMoney );
			VipBtn_mc.addEventListener(MouseEvent.CLICK,onVip);
			ExternalInterface.call( "ASTrace", "MallHomePanel");
			
			buyVipBtn_mc.visible = false;
			VipBtn_mc.visible = false;
			tf_vipdec.visible = false;
		}
		
		public function onVip(e:MouseEvent):void
		{
			ExternalInterface.call("ASClickBtnBuyVip", this);
		}
		
		public function UpdateMoney(nMoney:int):void
		{
			money1_gold.htmlText = nMoney.toString()+"<IMG SRC='img://MMO_UIIcon.MoneyIcon.MoneyBullion'>";
		}
		public function onClickBuyVip()
		{
			ExternalInterface.call("ASClickBtnBuyVip", this);
		}
		
		public function onClickCheckIn()
		{
			ExternalInterface.call("ASClickBtnCheckIn", this);
		}
		
		public function onClickAddMoney()
		{
			ExternalInterface.call("ASAddGoldMoney", this);
		}
		public function UpdateMallHomeShowData( data:Array )
		{
			ExternalInterface.call( "ASTrace", " MallHomePanel  UpdateMallShowData");
			mallAdv_mc.UpdateMallShowData(data);
		}
	}
}