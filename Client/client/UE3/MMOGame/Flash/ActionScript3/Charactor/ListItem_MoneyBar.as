package ActionScript3.Charactor
{
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	
	public class ListItem_MoneyBar extends UIComponent
	{
		public var ProcessBar_fill:MovieClip;
		public var textName:TextField;
		public var ProcesBarMask:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
		}

		public function updateData(data:Object):void
		{
			if (data)
			{
				
				if(data.WeeklyMoneyLimit<=0)
				{
					ProcesBarMask.width = 0;
					textName.text = "" + data.WeeklyMoney;
				}
				else if(data.WeeklyMoney / data.WeeklyMoneyLimit >1)
				{
					ProcesBarMask.width = ProcessBar_fill.width;
					textName.text = "" +data.WeeklyMoneyLimit + "/" + data.WeeklyMoneyLimit;
				}
				else{
					ProcesBarMask.width = ProcessBar_fill.width * data.WeeklyMoney / data.WeeklyMoneyLimit;
					textName.text = "" + data.WeeklyMoney + "/" + data.WeeklyMoneyLimit;
				}
			}
		}
		
	}
}