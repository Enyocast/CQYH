package UI_CharactorWidget.CharactorWidgetAS3
{
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import UI_CharactorWidget.CharactorWidgetAS3.ListItem_MoneyBar;

	public class ListItem_Money extends ListItemTreeRenderer
	{
		public var moneyName_tf:TextField;
		public var money_tf:TextField;
		public var moneyBar_mc:ListItem_MoneyBar;
		public var moneyIcon_mc:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
			//增加赋值回调
			if (this && this.updateDataCallBack == null)
			{
				this.updateDataCallBack = updateData;
			}
		}
		
		public function updateData(data:Object):void
		{
			if (data)
			{
				visible = true;
				moneyName_tf.text = data.label;
				money_tf.text = data.Money;
				moneyBar_mc.updateData(data);
			}
			else
			{
				visible = false;
			}
		}
		
	}
}