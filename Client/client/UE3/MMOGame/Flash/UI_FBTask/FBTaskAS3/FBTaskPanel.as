package UI_FBTask.FBTaskAS3
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	import UI_FBTask.FBTaskAS3.FBTaskListItemData;
	
	public class FBTaskPanel extends MyPanel
	{
		//副本
		public var FBTitleTf:TextField;
		//副本进度列表
		public var FBTaskScrollListMc:ScrollingList;
		
		override protected function configUI():void
		{
			super.configUI();
			//
			ExternalInterface.call( "RegisterFBTask", this );
			
			//FBTaskScrollListMc.addEventListener(ListEvent.ITEM_CLICK, onClickSkill);
			
			UpdateFBTaskScrollList( null );
			
			//
			//Test();
		}
		//
		public function UpdateFBTaskScrollList( data:Array ):void
		{
			FBTaskScrollListMc.selectedIndex = -1;
			FBTaskScrollListMc.dataProvider = new DataProvider(data);
			FBTaskScrollListMc.validateNow();
			FBTaskScrollListMc.invalidateData();
		}
		//
		function Test()
		{
			FBTitleTf.text = "副本： 牛逼副本";
			
			var itemsData:Array = new Array();
			for (var i:int = 1; i <= 5; i++)
			{
				var itemData:FBTaskListItemData = new FBTaskListItemData ;
				itemData.TaskTitle = ( i <= 1 ? "牛叉进度" : "进度条件"+i );
				itemData.CurInt = ( i <= 1 ? 0 : 7 - i );
				itemData.TargetInt = 5;
				
				itemData.IsFailed = false;
				
				itemData.ID = i;
				itemData.TaskType = ( i <= 1 ? 1 : 2 );
				
				itemsData.push( itemData );
			}
			
			UpdateFBTaskScrollList( itemsData );
		}
	}
}