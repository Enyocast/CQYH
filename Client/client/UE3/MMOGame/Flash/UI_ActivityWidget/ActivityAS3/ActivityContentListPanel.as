
package UI_ActivityWidget.ActivityAS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;

	public class ActivityContentListPanel extends UIComponent
	{
		public var ActivityItemList:ScrollingList;
		public  var nSelIndex = -1;
		public  var bDefaultOperate:Boolean = true;
		public var tabTitle:MovieClip;

		override protected  function configUI():void 
		{		
			super.configUI();			

			ActivityItemList.addEventListener(ListEvent.INDEX_CHANGE, onDefaultClickItem);
			ActivityItemList.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			tabTitle.titleBtn_Name.addEventListener(MouseEvent.CLICK, onSortBtn0 );
			tabTitle.titleBtn_Time.addEventListener(MouseEvent.CLICK, onSortBtn1 );
			tabTitle.titleBtn_Person.addEventListener(MouseEvent.CLICK, onSortBtn2 );
			tabTitle.titleBtn_Huoyue.addEventListener(MouseEvent.CLICK, onSortBtn3 );
			tabTitle.titleBtn_State.addEventListener(MouseEvent.CLICK, onSortBtn4 );
			tabTitle.titleBtn_Complete.addEventListener(MouseEvent.CLICK, onSortBtn5 );
			tabTitle.titleBtn_StarNum.addEventListener(MouseEvent.CLICK, onSortBtn6 );
			
			//onShowActivityInfoPage();
		}

		public function UCUpdateActivityContentListData( data:Array ):void
		{
			nSelIndex = ActivityItemList.selectedIndex;
			ActivityItemList.selectedIndex = -1;
			if(data != null)
			{
				if(nSelIndex >= data.length )
					nSelIndex = 0;
			}
			ActivityItemList.dataProvider = new DataProvider(data);
			ActivityItemList.validateNow();
			ActivityItemList.invalidateData();
			SetSelectedIndex();
		}		
		
		public function SetSelectedIndex()
		{
			if(nSelIndex < 0 || nSelIndex >= ActivityItemList.rowCount)
				nSelIndex = 0;
			ActivityItemList.selectedIndex = nSelIndex;
		}
		public function onSortBtn0()
		{
			ExternalInterface.call("ASSortActivity", 0 );
		}
		public function onSortBtn1()
		{
			ExternalInterface.call("ASSortActivity", 1 );
		}
		public function onSortBtn2()
		{
			ExternalInterface.call("ASSortActivity", 2 );
		}
		public function onSortBtn3()
		{
			ExternalInterface.call("ASSortActivity", 3 );
		}
		public function onSortBtn4()
		{
			ExternalInterface.call("ASSortActivity", 4 );
		}
		public function onSortBtn5()
		{
			ExternalInterface.call("ASSortActivity", 5 );
		}
		public function onSortBtn6()
		{
			ExternalInterface.call("ASSortActivity", 6 );
		}

		public function onClickItem(e:ListEvent):void
		{
			var item:ActivityListItem = e.itemRenderer as ActivityListItem;
			ActivityItemList.validateNow();
			ActivityItemList.invalidateData();
			ExternalInterface.call("ASClickActivityList", item.activityID);
		}
		public function onDefaultClickItem(e:ListEvent):void
		{
			if(e.itemRenderer == null)
				return;
			var item:ActivityListItem = e.itemRenderer as ActivityListItem;
			ExternalInterface.call("ASClickActivityList", item.activityID);
		}
		//test
/*		public function onShowActivityInfoPage()
		{
			if (1)
			{
				var itemsData:Array = new Array();
				for (var i:int = 1; i < 26; i++)
				{
					
					var tActivityData:ActivityData = new ActivityData  ;
					tActivityData.Id = i;
					tActivityData.Name = String( "寻宝" + i );
					tActivityData.Time = "7:00-9:00";
					tActivityData.PersonNum = String(i);
					tActivityData.Activity = i%4 + 21 ;
					tActivityData.CompleteState = String( i%6 + "/6");
					tActivityData.State = "进行中";
					tActivityData.IsVip = false;
					tActivityData.StarNum = 3;
					tActivityData.Level = "25";
					
					itemsData.push(tActivityData);
					
					trace("***tActivityData", tActivityData, tActivityData);
				}
				UCUpdateActivityContentListData( itemsData );
			}
		}*/
	}
}