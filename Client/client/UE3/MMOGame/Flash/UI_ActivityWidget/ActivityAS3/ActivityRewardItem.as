
package UI_ActivityWidget.ActivityAS3
{
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.UILoader;
	
	public class ActivityRewardItem extends UILoader
	{
		public var ItemData:ActivityRewardItemData;
		public var ItemID:int;
		
		override protected function configUI():void
		{
			super.configUI();
			
			mouseChildren = true;
			
			this.addEventListener(MouseEvent.ROLL_OVER, onRollOverRewardItemSlot);
			this.addEventListener(MouseEvent.ROLL_OUT, onRollOutRewardItemSlot);
			
		}
		
		public function UpdateItem(data:Object):void
		{
			ItemData = data as ActivityRewardItemData;
			if( !ItemData ){
				this.source = "";
				visible = false;
				return;
			}
			visible = true;
			ItemID = ItemData.ItemId;
			
			if( ItemData.IconName.length == 0 ){
				this.source = "img://MMO_UIIcon.icon.blank";
			}
			else{
				this.source = "test.png";//"img://" + ListItemData.SkillIconName;
			}
		}
		
		//=====================================================================
		function onRollOverRewardItemSlot( e:Event )
		{
			if( !ItemData ){
				return;
			}
			//
			ExternalInterface.call("ASShowTips_ActivityRewardItem", this );
		}

		function onRollOutRewardItemSlot( e:Event )
		{
			if( !ItemData ){
				return;
			}
			//
			ExternalInterface.call("ASHideTips_ActivityRewardItem" );
		}
		
	}

}