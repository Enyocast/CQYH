package UI_CharactorWidget.CharactorWidgetAS3
{
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	
	public class ListItem_MoneyBar extends UIComponent
	{
		var ProcessBar_fill:MovieClip;
		var textName:TextField;
		var ProcesBarMask:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
		}

		public function updateData(data:Object):void
		{
			if (data)
			{
				ProcesBarMask.width = ProcessBar_fill.width * data.WeeklyMoney / data.WeeklyMoneyLimit;
				textName.text = "" + data.WeeklyMoney + "//" + data.WeeklyMoneyLimit;
			}
		}


	}
}