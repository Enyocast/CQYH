package UI_BattleSummary.BattleSummaryAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;

	public class BtlScoreListRowItem extends ListItemTreeRenderer
	{
		public var isDetailItem:Boolean;
		
		public var ListItemTitle_mc:BtlScoreListTitle;
		public var ListItemDetail_mc:BtlScoreListItem;
		
		override protected function configUI():void
		{
			super.configUI();
			
			this.addEventListener(MouseEvent.ROLL_OVER, onRollOverListItem);
			this.addEventListener(MouseEvent.ROLL_OUT, onRollOutListItem);
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}

		function updateData(data:Object):void
		{
			if( !data || data.deepth >1 ){
				isDetailItem = false;
				visible = false;
				return;
			}
			
			visible = true;
			if( data.deepth == 0 ){
				
				ListItemTitle_mc.visible = true;
				ListItemDetail_mc.visible = false;
				
				ListItemTitle_mc.updateData( data );
				
			}
			else if( data.deepth == 1 ){

				if( data is BtlScoreListItemData ){
					ListItemTitle_mc.visible = false;
					ListItemDetail_mc.visible = true;
				
					ListItemDetail_mc.updateData( data );
					isDetailItem = true;
				}
				else{
					ListItemTitle_mc.visible = false;
					ListItemDetail_mc.visible = false;
					
					isDetailItem = false;
				}
			}
		}
		//
		function onRollOverListItem( e:Event )
		{
			//trace("onRollOverListItem",isDetailItem);
			if( isDetailItem ){
				ListItemDetail_mc.gotoAndStop("over");
			}
			/*
			else{
				if( ListItemTitle_mc.listClassData.type == 1 ){
					ListItemTitle_mc.gotoAndStop("over");
				}
				else{
					ListItemTitle_mc.gotoAndStop("selected_over");
				}
			}
			*/
		}

		function onRollOutListItem( e:Event )
		{
			//trace("onRollOutListItem",isDetailItem);
			if( isDetailItem ){
				ListItemDetail_mc.gotoAndStop("up");
			}
			/*
			else{
				if( ListItemTitle_mc.listClassData.type == 1 ){
					ListItemTitle_mc.gotoAndStop("up");
				}
				else{
					ListItemTitle_mc.gotoAndStop("selected_up");
				}
			}
			*/
		}
	}

}