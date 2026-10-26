package ActionScript3.Helper
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;

	import ActionScript3.MyScrollBar;
	import scaleform.clik.controls.ScrollingView;

	public class HelperPanel extends MyPanel
	{
		public var helper_list_mc:ScrollingList;
		public var helper_detail_mc:HelperDetailPage;
		public var helper_detail_sb_mc:MyScrollBar;
		
		public var _scrollingView:ScrollingView;

		
		public function HelperPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			//trace(">>>>>>>>>>>>>>> HelperPanel::configUI");
			super.configUI();
			//ExternalInterface.call("ASRegisterHelperPanel", this);			
			
			helper_list_mc.selectedIndex = 0;
			helper_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			helper_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick);
			
			helper_detail_mc.setupScrollBar(this.helper_detail_sb_mc);
			_scrollingView.displayMc = helper_detail_sb_mc;

			// clear the list
			UCUpdateHelperList(new Array());
			/*
			// test
			var helper_list:Array = new Array();
			var helper_list_item:Object = null;
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 0 + "级";
			helper_list_item.index = 0;
			helper_list_item.type = 1;
			helper_list_item.deepth = 0;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 0;		
			helper_list_item.subClass = 0;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 1 + "级";
			helper_list_item.index = 1;
			helper_list_item.type = 1;
			helper_list_item.deepth = 1;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 0;		
			helper_list_item.subClass = 1;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 2 + "级";
			helper_list_item.index = 2;
			helper_list_item.type = 1;
			helper_list_item.deepth = 0;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 1;		
			helper_list_item.subClass = 0;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 3 + "级";
			helper_list_item.index = 3;
			helper_list_item.type = 1;
			helper_list_item.deepth = 1;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 1;		
			helper_list_item.subClass = 1;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 4 + "级";
			helper_list_item.index = 4;
			helper_list_item.type = 1;
			helper_list_item.deepth = 1;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 1;		
			helper_list_item.subClass = 2;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 5 + "级";
			helper_list_item.index = 5;
			helper_list_item.type = 1;
			helper_list_item.deepth = 0;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 2;		
			helper_list_item.subClass = 0;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
			
			helper_list_item = new Object;
			helper_list_item.label = "第" + 6 + "级";
			helper_list_item.index = 6;
			helper_list_item.type = 1;
			helper_list_item.deepth = 1;
			helper_list_item.visible = true;
			helper_list_item.baseClass = 2;		
			helper_list_item.subClass = 1;
			helper_list_item.helper_is_select = false;
			helper_list.push(helper_list_item);
				
			UCUpdateHelperList(helper_list);
			*/
			trace("<<<<<<<<<<<<<<< HelperPanel::configUI");
		}

		public function onListItemChange( event:Event ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		function onListItemClick( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					provider.handleListItemClick( event );
					
					var obj:Object = provider.requestItemAt(event.index) as Object;
					var i:int;
					var item:Object;
					if (obj.deepth == 0)
					{
						for(i = 0; i < provider.length; ++i)
						{
							item = provider.requestItemAt(i) as Object;
							if (item != null)
							{
								if (item.deepth == 0 && item.baseClass == obj.baseClass && item.subClass == obj.subClass)
								{
									item.helper_is_select = !item.helper_is_select;
								}
							}
						}
						
						helper_list_mc.validateNow();
						helper_list_mc.invalidateData();
						
						ExternalInterface.call("ASUpdateHelperDetail", obj.baseClass, obj.subClass);
					}
					else if (obj.deepth == 1)
					{
						for(i = 0; i < provider.length; ++i)
						{
							item = provider.requestItemAt(i) as Object;
							if(item != null)
							{
								if (item.deepth == 1)
								{
									item.helper_is_select = false;
								}
							}
						}

						obj.helper_is_select = true;
						helper_list_mc.validateNow();
						helper_list_mc.invalidateData();
						
						ExternalInterface.call("ASUpdateHelperDetail", obj.baseClass, obj.subClass);
					}
				}
				
				list.validateNow();
			}
		}
		
		public function UCUpdateHelperList(list:Array):void
		{
			helper_list_mc.dataProvider = new TreeDataProvider(list);
			helper_list_mc.validateNow();
			helper_list_mc.invalidateData();
		}
		
		public function UCUpdateHelperDetail(detail_data:Object):void
		{
			if (detail_data)
			{
				this.helper_detail_mc.updateHelperDetailData(detail_data);
			}
			else
			{
				this.helper_detail_mc.visible = false;
			}
		}
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
	}
}