
package UI_ActivityWidget.ActivityAS3
{
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.constants.InvalidationType;
    import scaleform.clik.core.UIComponent;
    import flash.text.TextField;
    import flash.display.MovieClip;
    import ActionScript3.Common.Utils.StyleType;
	
	public class ActivityRewardBarItem extends UIComponent
	{
		//public var BarItem:UILoader;
		public var barPos:TextField;
		public var BarItem:MovieClip;
		
		public  var ItemData:ActivityRewardBarItemData;
		
		override protected function configUI():void
		{
			super.configUI();
			BarItem.filters=[StyleType.getInstance().getBlackFilter()];
			
			//BarItem.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardBarItem);
			//BarItem.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardBarItem);
			//BarItem.addEventListener(MouseEvent.CLICK, 		onCLickGetReward );
		}
		
		public function UpdateItem(data:Object):void
		{
			ItemData = data as ActivityRewardBarItemData;
			if( !ItemData ){
				visible = false;
				return;
			}
			visible = true;
			barPos.text = String(ItemData.Pos);

			if(ItemData.nState == 2)
			    BarItem.gotoAndStop(ItemData.nType+"_on");
			else
				BarItem.gotoAndStop(ItemData.nType+"_off");
		}
		
		//=====================================================================
		function onRollOverRewardBarItem( e:Event )
		{
			if( !ItemData ){
				return;
			}
			//
			ExternalInterface.call("ASShowTips_ActivityRewardItemBar", this ,ItemData.nIndex);
		}

		function onRollOutRewardBarItem( e:Event )
		{
			if( !ItemData ){
				return;
			}
			//
			ExternalInterface.call("ASHideTips_ActivityRewardItemBar" );
		}
		public function onCLickGetReward()
		{
			if(ItemData != null)
				ExternalInterface.call("ASClickQuitGetReward", ItemData.nIndex);
		}
	}

}