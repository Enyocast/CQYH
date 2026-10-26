
package UI_ActivityWidget.ActivityAS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
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
	
	public class ActivityFBListPanel extends UIComponent
	{
		public var ActivityItemList:ScrollingList;
		
/*		public  var titleBtn_Name:Button;
		public  var titleBtn_Person:Button;
		public  var titleBtn_Level:Button;
		public  var titleBtn_CostHuoyue:Button;
		public  var titleBtn_Complete:Button;*/
		public  var nSelIndex = -1;
		public  var bDefaultOperate:Boolean = true;
		public var tabTitle:MovieClip;
		
		override protected  function configUI():void 
		{		
			trace("------ActivityFBListPanel  super.configUI:");
			super.configUI();			

			ActivityItemList.addEventListener(ListEvent.INDEX_CHANGE, onDefaultClickItem);
			ActivityItemList.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			ActivityItemList.addEventListener(ListEvent.ITEM_ROLL_OVER,overHandler);
			ActivityItemList.addEventListener(ListEvent.ITEM_ROLL_OUT,outHandler);
			tabTitle.titleBtn_Name.addEventListener(MouseEvent.CLICK, onSortBtn0 );
			tabTitle.titleBtn_Person.addEventListener(MouseEvent.CLICK, onSortBtn1 );
			tabTitle.titleBtn_Level.addEventListener(MouseEvent.CLICK, onSortBtn2 );
			tabTitle.titleBtn_CostHuoyue.addEventListener(MouseEvent.CLICK, onSortBtn3 );
			tabTitle.titleBtn_Complete.addEventListener(MouseEvent.CLICK, onSortBtn4 );
			
			//onShowActivityInfoPage();
		}

		public function UCUpdateActivityFBListData( data:Array ):void
		{
			trace("------UCUpdateActivityListData",ActivityItemList);
		
			nSelIndex = ActivityItemList.selectedIndex;
			ActivityItemList.selectedIndex = -1;
			if(data != null)
			{
				if(nSelIndex >= data.length)
					nSelIndex = 0;
			}
			ActivityItemList.dataProvider = new DataProvider(data);
			ActivityItemList.validateNow();
			ActivityItemList.invalidateData();
			SetSelectedIndex();
		}		
		
		public function SetSelectedIndex()
		{
			if(nSelIndex < 0|| nSelIndex >= ActivityItemList.rowCount)
				nSelIndex = 0;
			ActivityItemList.selectedIndex = nSelIndex;
		}
		
		public function onSortBtn0()
		{
			ExternalInterface.call("ASSortActivity", 0 );
		}
		public function onSortBtn1()
		{
			ExternalInterface.call("ASSortActivity", 2 );
		}
		public function onSortBtn2()
		{
			ExternalInterface.call("ASSortActivity", 7 );
		}
		public function onSortBtn3()
		{
			ExternalInterface.call("ASSortActivity", 8 );
		}
		public function onSortBtn4()
		{
			ExternalInterface.call("ASSortActivity", 4 );
		}
		
		public function onClickItem(e:ListEvent):void
		{
			trace(ActivityItemList.selectedIndex+"------ASClickActivityFBList"+e.buttonIdx);
			var item:ActivityFBListItem = e.itemRenderer as ActivityFBListItem;
/*			var act:ActivityFBListItem= (ActivityItemList.getRendererAt(ActivityItemList.selectedIndex) as ActivityFBListItem);
			if(act && act.selected==true){
				act.setColor(0);
			}*/
			item.setColor(2);
			ExternalInterface.call("ASClickActivityFBList", item.activityID);
		}
		public function onDefaultClickItem(e:ListEvent):void
		{
			if(e.itemRenderer == null)
				return;
			var item:ActivityFBListItem = e.itemRenderer as ActivityFBListItem;
			ExternalInterface.call("ASClickActivityFBList", item.activityID);
		}
		
		public function overHandler(e:ListEvent):void
		{
			var item:ActivityFBListItem = e.itemRenderer as ActivityFBListItem;
			item.setColor(1);
		}
		public function outHandler(e:ListEvent):void
		{
			var item:ActivityFBListItem = e.itemRenderer as ActivityFBListItem;
			item.setColor(0);
/*			if(item.selected==false){
				item.setColor(0);
			}*/
		}
		public function onShowActivityInfoPage()
		{
			// test
			if (1)
			{
				var itemsData:Array = new Array();
				for (var i:int = 1; i < 26; i++)
				{
					
					var tActivityData:ActivityData = new ActivityData  ;
					tActivityData.Id = i*3;
					tActivityData.Name = String( "寻宝" + i );
					tActivityData.PersonNum = String(i);
					tActivityData.Activity = i%4 + 21 ;
					tActivityData.CompleteState = String( i%6 + "/6");
					tActivityData.State = "进行中";
					
					itemsData.push(tActivityData);
					
					trace("***tActivityData", tActivityData, tActivityData);
				}
				UCUpdateActivityFBListData( itemsData );
			}
		}
	}
}