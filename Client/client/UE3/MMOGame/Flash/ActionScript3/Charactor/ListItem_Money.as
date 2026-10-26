package ActionScript3.Charactor
{
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import ActionScript3.Charactor.ListItem_MoneyBar;
	import flash.external.ExternalInterface;

	public class ListItem_Money extends ListItemTreeRenderer
	{
		public var moneyName_tf:TextField;
		public var money_tf:TextField;
		public var moneyBar_mc:ListItem_MoneyBar;
		public var moneyIcon_mc:MovieClip;
		public var text:String;
		public var tipsHtml:String;
		public var tips1:String;
		public var tips2:String;		

		override protected function configUI():void
		{
			super.configUI();
			
			moneyBar_mc.addEventListener(MouseEvent.ROLL_OVER,ShowBarTips);
			moneyName_tf.addEventListener(MouseEvent.ROLL_OVER,ShowNameTips);
			moneyIcon_mc.addEventListener(MouseEvent.ROLL_OVER,ShowIconTips);
			
			moneyBar_mc.addEventListener( MouseEvent.ROLL_OUT, HideTips);
			moneyName_tf.addEventListener( MouseEvent.ROLL_OUT, HideTips);
			moneyIcon_mc.addEventListener(MouseEvent.ROLL_OUT,HideTips);
			
			//增加赋值回调
			if (this && this.updateDataCallBack == null)
			{
				this.updateDataCallBack = updateData;
			}
		}
		
		private function ShowBarTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_PlainText_WithString", moneyBar_mc, tips2 );
		}						
		private function ShowNameTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_PlainText_WithString", moneyName_tf, tips2 );
		}
		private function ShowIconTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_PlainText_WithString", moneyIcon_mc, tips1);
		}		
		private function HideTips(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_Text", this);
		}

		public function updateData(data:Object):void
		{
			if (data)
			{
				visible = true;
				moneyName_tf.text = data.label;
				money_tf.text = data.Money;
				tips2 = data.Tips2;
				tips1 = data.Tips1;
				moneyBar_mc.updateData(data);
				moneyIcon_mc.gotoAndStop(data.MoneyTypeString);
			}
			else
			{
				visible = false;
			}
		}
		
	}
}