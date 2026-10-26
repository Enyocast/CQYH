
package UI_ActivityWidget.ActivityAS3
{
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.constants.InvalidationType;
    import scaleform.clik.core.UIComponent;
    import scaleform.clik.events.ComponentEvent;
    import flash.text.TextField;
    import flash.display.MovieClip;
	
	public class ActivityRewardBar extends UIComponent
	{
		public var todayHuoyueNum:TextField;
		public var barMask_mc:MovieClip;
		public var heavenExpBarRuler_mc:MovieClip;
		public var heavenExpBarHead_mc:MovieClip;
		
		public var rewardBarItemHint0:ActivityRewardBarItem;
		public var rewardBarItemHint1:ActivityRewardBarItem;
		public var rewardBarItemHint2:ActivityRewardBarItem;
		public var rewardBarItemHint3:ActivityRewardBarItem;
		public var rewardBarItemHint4:ActivityRewardBarItem;
		//public var rewardBarItemHint5:ActivityRewardBarItem;
		
		public var tArrIconItemBar:Array;
		public var IsBtnEnable:Boolean = false;
		public var MaxBarLength = 200;
		
		override protected function configUI():void
		{
			super.configUI();
			trace("ActivityRewardBar");
			
			tArrIconItemBar = new Array;
			tArrIconItemBar.push(rewardBarItemHint0);
			tArrIconItemBar.push(rewardBarItemHint1);
			tArrIconItemBar.push(rewardBarItemHint2);
			tArrIconItemBar.push(rewardBarItemHint3);
			tArrIconItemBar.push(rewardBarItemHint4);
			//tArrIconItemBar.push(rewardBarItemHint5);
			
			for(var n:int = 0; n < 5; ++n)
			{
				tArrIconItemBar[n].visible = false;
			}
			
			/*UpdateHuoyueValue(20,500);
			var bar:Array = [];
			
			for(var i:int = 0; i < 5; ++i)
			{
				var item:ActivityRewardBarItemData = new ActivityRewardBarItemData;
				item.Pos = i*50 + 20;
				item.nState = i%3;
				item.nType = i%3;
				bar.push(item);
			}
			UpdateRewardBarInfo(bar);*/
		}
		
		public function UpdateHuoyueValue(nCurValue:int,nMaxValue:int)
		{
			todayHuoyueNum.text = String(nCurValue);
			barMask_mc.width = heavenExpBarRuler_mc.width*nCurValue/nMaxValue;
			heavenExpBarHead_mc.x = heavenExpBarRuler_mc.x + barMask_mc.width;
			MaxBarLength = nMaxValue;
		}
		
		public function UpdateRewardBarInfo(data:Array)
		{
			IsBtnEnable = false;
			for(var n:int = 0; n < 5; ++n)
			{
				tArrIconItemBar[n].visible = false;
			}
			if(data)
			{
				for(var i:int = 0; i < data.length && i < 5; ++i)
				{
					tArrIconItemBar[i].visible = true;
					var itemData:ActivityRewardBarItemData = data[i] as ActivityRewardBarItemData;
					tArrIconItemBar[i].UpdateItem(itemData);
					//tArrIconItemBar[i].x = heavenExpBarRuler_mc.x + heavenExpBarRuler_mc.width*itemData.Pos/MaxBarLength;
					if(itemData.nState == 1)
						IsBtnEnable = true;
				}
			}
		}
	}
}