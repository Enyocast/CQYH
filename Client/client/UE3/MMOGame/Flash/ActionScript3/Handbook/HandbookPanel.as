package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.clearTimeout;
	import flash.utils.getTimer;
	import flash.utils.setTimeout;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.TextInput_Advanced;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.events.ListEvent;

	public class HandbookPanel extends MyPanel
	{
		public var handbook_tab_monster_mc:RadioButton;
		public var handbook_tab_npc_mc:RadioButton;
		public var handbook_tab_map_mc:RadioButton;
		public var handbook_tab_item_mc:RadioButton;
		public var handbook_tab_equip_mc:RadioButton;
		public var handbook_tab_rune_mc:RadioButton;
		public var handbook_tab_spirit_mc:RadioButton;
		public var handbook_type_mc:DropdownMenu;
		public var handbook_list_mc:ScrollingList;
		public var handbook_progress_mc:MovieClip;
		public var handbook_progress_tf:TextField;
		public var handbook_award_tf:TextField;
		public var handbook_search_mc:TextInput_Advanced;
		public var handbook_search_bt_mc:Button;
		public var handbook_achievement_bt_mc:Button;
		
		public var handbook_suit_page_mc:MovieClip;
		public var handbook_story_page_mc:MovieClip;
		public var handbook_stone_page_mc:MovieClip;
		public var handbook_spirit_page_mc:MovieClip;
		public var handbook_rune_page_mc:MovieClip;
		public var handbook_npc_page_mc:MovieClip;
		public var handbook_monster_page_mc:MovieClip;
		public var handbook_map_page_mc:MovieClip;
		public var handbook_equip_page_mc:MovieClip;
		public var handbook_compose_page_mc:MovieClip;
		
		public var scrolling_view_right_page:ScrollingView;
		public var scroll_bar_right_page:ScrollBar;
		
		public var btn_back:Button;
		public var left_page_mask_top_mc:MovieClip;
		public var progress_achievement_mc:ProgressAchievement;
		
		protected var handbook_progress_source_scale:Number;
		
		protected var _listData:DataProvider = new DataProvider();
		protected var _toUpdateListData:Boolean = false;
		protected var _hasAchievementView:Boolean = true;
		protected var _handbook_list_resized:Boolean = false;
		
		//these pages need hide popuped dropdown menu when scrolling
		protected var _pagesHasDropdownMenu:Array;
		protected var _tabButtons:Array;
		
		public static const handbook_monster = 1;
		public static const handbook_npc = 2;
		public static const handbook_map = 3;
		public static const handbook_story = 4;
		public static const handbook_compose = 5;
		public static const handbook_stone = 6;
		public static const handbook_equip = 7;
		public static const handbook_suit = 8;
		public static const handbook_rune = 9;
		public static const handbook_spirit = 10;
		
		private var _activatePage:MovieClip
		
		public function HandbookPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			//ExternalInterface.call("ASRegisterHandbookPanel", this);
			_tabButtons = [handbook_tab_monster_mc, //0
				handbook_tab_npc_mc, 	  //1
				handbook_tab_map_mc,	//2
				handbook_tab_item_mc,	//3
				handbook_tab_equip_mc,	//4
				handbook_tab_rune_mc,	//5
				handbook_tab_spirit_mc];//6
			_pagesHasDropdownMenu = [handbook_stone_page_mc, handbook_rune_page_mc, handbook_spirit_page_mc]
			//reference
			handbook_progress_mc 		= progress_achievement_mc.handbook_progress_mc;
			handbook_progress_tf 		= progress_achievement_mc.handbook_progress_tf;
			handbook_award_tf 			= progress_achievement_mc.handbook_award_tf;
			handbook_achievement_bt_mc 	= progress_achievement_mc.handbook_achievement_bt_mc;
			btn_back.addEventListener(MouseEvent.CLICK, onBackButtonClick, false, 0, true);
			handbook_achievement_bt_mc.addEventListener(MouseEvent.CLICK, onAchievementButtonClick, false, 0, true);
			
			handbook_search_bt_mc.addEventListener(MouseEvent.CLICK, onSearch);
			
			handbook_tab_monster_mc.addEventListener(MouseEvent.CLICK, onTabClickMonster);
			handbook_tab_npc_mc.addEventListener(MouseEvent.CLICK, onTabClickNpc);
			handbook_tab_map_mc.addEventListener(MouseEvent.CLICK, onTabClickMap);
			handbook_tab_item_mc.addEventListener(MouseEvent.CLICK, onTabClickItem);
			handbook_tab_equip_mc.addEventListener(MouseEvent.CLICK, onTabClickEquip);
			handbook_tab_rune_mc.addEventListener(MouseEvent.CLICK, onTabClickRune);
			handbook_tab_spirit_mc.addEventListener(MouseEvent.CLICK, onTabClickSpirit);
			
			// 临时屏蔽
			handbook_tab_spirit_mc.visible = false;
			
			//handbook_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListIndexChanged, false, 0, true);
			
			//right page scroll event
			scroll_bar_right_page.addEventListener(Event.SCROLL, handleRightPageScroll, false, 0, true);
			scroll_bar_right_page.addEventListener(Event.CHANGE, handleRightPageScroll, false, 0, true);
			
			handbook_type_mc.dataProvider = new DataProvider();
			handbook_type_mc.addEventListener(ListEvent.INDEX_CHANGE,onChangeSelect);
			
			handbook_suit_page_mc.visible = false;
			handbook_story_page_mc.visible = false;
			handbook_stone_page_mc.visible = false;
			handbook_spirit_page_mc.visible = false;
			handbook_rune_page_mc.visible = false;
			handbook_npc_page_mc.visible = false;
			handbook_monster_page_mc.visible = false;
			handbook_map_page_mc.visible = false;
			handbook_equip_page_mc.visible = false;
			handbook_compose_page_mc.visible = false;
			
			var progress_mask_mc:MovieClip = handbook_progress_mc.getChildByName("progress_mask_mc") as MovieClip;
			handbook_progress_source_scale = progress_mask_mc.scaleX;
			
			//initialize
			handbook_tab_monster_mc.selected = true;
			
			UCSetMainPageType(false);
			
			UCUpdateHandbookList(null, 0, 0, 0);
			delayCall(300,
				function():void
				{
/*					var type_list:Array = new Array();
					type_list.push("普通");
					type_list.push("精英");
					type_list.push("BOSS");
					UCUpdateHandbookType(type_list);
					UCUpdateHandbookProgress(2, 10);*/
					handbook_type_mc.selectedIndex = 0;
				});
			
			//TestMonsterPage();
			
			//TestNpcPage();
			
			//TestMapPage();
			
			//TestStoryPage();
			
			//TestComposePage();
			
			//TestStonePage();
			
			//TestSuitPage();
			
			//TestEquipPage();
			
			//TestRunePage();
			
			//TestSpiritPage();
		}
		
		override public function set visible(value:Boolean):void
		{
			super.visible = value;
			if(!value && handbook_type_mc.selected){
				handbook_type_mc.close();
			}
		}
		
		private function delayCall(delayTime:int, callFunciton:Function, ...parameters):void
		{
			var delay:int = setTimeout(
				function():void
				{
					clearTimeout(delay);
					callFunciton.apply(null, parameters);
				}, delayTime);
		}
		
		private function onBackButtonClick(evt:MouseEvent):void
		{
			ExternalInterface.call("ASBackButtonClick");
			btn_back.visible = false;
		}
		
		private function onSearch(evt:Event):void
		{
			if (handbook_search_mc.text != "")
			{
				ExternalInterface.call("ASSearchByKey", handbook_search_mc.text);
			}
		}
		
		private function handleRightPageScroll(evt:Event):void
		{
			if(_activatePage != null && _pagesHasDropdownMenu.indexOf(_activatePage) != -1)
			{
				try
				{
					_activatePage.hideDropdownList();
				} 
				catch(error:Error) 
				{
					//call failed;
				}
			}
		}
		
		private function onAchievementButtonClick(evt:MouseEvent):void
		{
			ExternalInterface.call("ASGetAchievement");
		}

		private function onTabClickMonster(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 1);
		}

		private function onTabClickNpc(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 2);
		}
		
		private function onTabClickMap(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 3);
		}
		
		private function onTabClickItem(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 4);
		}
		
		private function onTabClickEquip(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 5);
		}
		
		private function onTabClickRune(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 6);
		}
		
		private function onTabClickSpirit(evt:MouseEvent):void
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookClass", 7);
		}
		
		public function onChangeSelect()
		{
			_toUpdateListData = true;
			ExternalInterface.call("ASSetHandbookType", handbook_type_mc.selectedIndex);
			//UCSetMainPageType();
			//TestMainPage();
		}
		
		public function UCSetMainPageType(hasAchievementView:Boolean = false):void
		{
			if(_hasAchievementView != hasAchievementView){
				_hasAchievementView = hasAchievementView
				if(_hasAchievementView){
					progress_achievement_mc.visible = true;
					left_page_mask_top_mc.y = 157;
					handbook_list_mc.y = 164;
					handbook_list_mc.rowCount = 4;
					handbook_list_mc.height = 344;//4*87 = 348, 344 for scroll bar height
				}else{
					progress_achievement_mc.visible = false;
					left_page_mask_top_mc.y = 65;
					handbook_list_mc.y = 72;
					handbook_list_mc.rowCount = 5;
					handbook_list_mc.height = 432;//5*87 = 435, 432 for scroll bar height
				}
				_handbook_list_resized = true;
				handbook_list_mc.validateNow();
			}
		}
		
		public function UCSetWindowTitle(title:String)
		{
			if(MyWindowsFrame_mc is HandbookWindow)
			{
				(MyWindowsFrame_mc as HandbookWindow).SetWindowTitle(title);
			}
		}
		
		public function UCUpdateHandbookType(data_list:Array)
		{
			handbook_type_mc.dataList = data_list;
			handbook_type_mc.SplitData();
			if(data_list){
				handbook_type_mc.menuRowCount = data_list.length;
			}
		}
		
		public function UCUpdateHandbookProgress(cur:int,max:int)
		{
			var progress_mask_mc:MovieClip = handbook_progress_mc.getChildByName("progress_mask_mc") as MovieClip;
			var percent:Number = cur / max;
			progress_mask_mc.scaleX = handbook_progress_source_scale * percent;
			
			var progress_indicator_mc:MovieClip = handbook_progress_mc.getChildByName("progress_indicator_mc") as MovieClip;
			if (progress_indicator_mc)
			{
				if (percent <= 0)
				{
					progress_indicator_mc.visible = false;
				}
				else
				{
					progress_indicator_mc.x = progress_mask_mc.width;
					progress_indicator_mc.visible = true;
				}
			}
			
			handbook_progress_tf.text = cur.toString() + "/" + max.toString();
		}
		
		public function UCUpdateHandbookList(data:Array, type_index:int, line_index:int, row_index:int = 0)
		{
			if(data && data.length > 0){
				if(_handbook_list_resized){
					_handbook_list_resized = false;
					delayCall(50,UCUpdateHandbookList, data, type_index, line_index, row_index);//delay update data if list size changed
					return;
				}
				_listData.cleanUp();
				_listData.setSource(data);
				handbook_list_mc.invalidateData();
				handbook_list_mc.dataProvider = _listData;
				var listItemSelectedIndex:int = 0;
				var singleItemSelectedIndex:int = 0;
				var item_data_name:String = "handbook_item_data" + String(row_index);
				var firstPageData:HandbookData = data[line_index][item_data_name] as HandbookData;
				if(firstPageData){
					var handbook_class:int = firstPageData.handbook_class;
					var handbook_type:int = firstPageData.handbook_type;
					var handbook_index:int = firstPageData.handbook_index;
					var handbook_ui_type:int  = firstPageData.handbook_ui_type;
					setSelectedTab(handbook_class - 1);
					setDropdownListSelectedIndex(type_index);
					if(handbook_ui_type == ConstansDefine.handbook_map){
						listItemSelectedIndex =  handbook_index;
						singleItemSelectedIndex = ConstansDefine.NUM_OF_SINGLE_ITEM - 1;
					}else{
						listItemSelectedIndex = Math.floor(handbook_index / (ConstansDefine.NUM_OF_SINGLE_ITEM - 1));//ConstansDefine.NUM_OF_SINGLE_ITEM - 1 = 4;
						singleItemSelectedIndex = handbook_index % (ConstansDefine.NUM_OF_SINGLE_ITEM - 1);
					}
				}
				resetListItemState(singleItemSelectedIndex);
			}
			handbook_list_mc.selectedIndex = listItemSelectedIndex;
			handbook_list_mc.scrollToSelected();
			handbook_list_mc.validateNow();
		}
		
		public function UCCanBack()
		{
			btn_back.visible = true;
		}
		
		public function UCUpdateHandbookInfo(data:HandbookData)
		{
			handbook_suit_page_mc.visible = false;
			handbook_story_page_mc.visible = false;
			handbook_stone_page_mc.visible = false;
			handbook_spirit_page_mc.visible = false;
			handbook_rune_page_mc.visible = false;
			handbook_npc_page_mc.visible = false;
			handbook_monster_page_mc.visible = false;
			handbook_map_page_mc.visible = false;
			handbook_equip_page_mc.visible = false;
			handbook_compose_page_mc.visible = false;
			
			if(_activatePage != null){
				_activatePage.mask = null;
			}
			
			if (data)
			{
				if(MyWindowsFrame_mc is HandbookWindow)
				{
					(MyWindowsFrame_mc as HandbookWindow).setViewType(data.handbook_ui_type);
				}
				//update handbook name
				UCSetWindowTitle(data.handbook_name);
				switch (data.handbook_ui_type)
				{
				case handbook_monster :
					_activatePage = handbook_monster_page_mc;
					handbook_monster_page_mc.visible = true;
					handbook_monster_page_mc.updateHandbookData(data);
					break;
				case handbook_npc :
					_activatePage = handbook_npc_page_mc;
					handbook_npc_page_mc.visible = true;
					handbook_npc_page_mc.updateHandbookData(data);
					break;
				case handbook_map :
					_activatePage = handbook_map_page_mc;
					handbook_map_page_mc.visible = true;
					handbook_map_page_mc.updateHandbookData(data);
					break;
				case handbook_story :
					_activatePage = handbook_story_page_mc;
					handbook_story_page_mc.visible = true;
					handbook_story_page_mc.updateHandbookData(data);
					break;
				case handbook_compose :
					_activatePage = handbook_compose_page_mc;
					handbook_compose_page_mc.visible = true;
					handbook_compose_page_mc.updateHandbookData(data);
					break;
				case handbook_stone :
					_activatePage = handbook_stone_page_mc;
					handbook_stone_page_mc.visible = true;
					handbook_stone_page_mc.updateHandbookData(data);
					break;
				case handbook_equip :
					_activatePage = handbook_equip_page_mc;
					handbook_equip_page_mc.visible = true;
					handbook_equip_page_mc.updateHandbookData(data);
					break;
				case handbook_suit :
					_activatePage = handbook_suit_page_mc;
					handbook_suit_page_mc.visible = true;
					handbook_suit_page_mc.updateHandbookData(data);
					break;
				case handbook_rune :
					_activatePage = handbook_rune_page_mc;
					handbook_rune_page_mc.visible = true;
					handbook_rune_page_mc.updateHandbookData(data);
					break;
				case handbook_spirit :
					_activatePage = handbook_spirit_page_mc;
					handbook_spirit_page_mc.visible = true;
					handbook_spirit_page_mc.updateHandbookData(data);
					break;
				} //end of switch
			}//end of if
			updateRightPageView();
		}
		
		public function updateRightPageView():void
		{
			_activatePage.y = scrolling_view_right_page.y;
			_activatePage.mask = scrolling_view_right_page;
			scrolling_view_right_page.displayMc = _activatePage;
			scrolling_view_right_page.scrollBar = scroll_bar_right_page;
		}
		
		private function setSelectedTab(selectedIndex:int):void
		{
			if(selectedIndex >=0 && selectedIndex < _tabButtons.length){
				//LOG('setSelectedTab: ', _tabButtons[_tabButtons]);
				(_tabButtons[selectedIndex] as RadioButton).selected = true;
			}
		}
		
		private function setDropdownListSelectedIndex(selectedIndex:int):void
		{
			if(selectedIndex >=0 && selectedIndex < handbook_type_mc.menuRowCount){
				handbook_type_mc.selectedIndex = selectedIndex;
			}
		}
		
		private function TestMainPage():void
		{
			// test
			var handbook_list:Array = new Array();
			var handbook_list_data:Object = null;
			var i:int = 0;
			var handbook_class:int = int(6 * Math.random()) + 1;
			var handbook_ui_type:int = int(10 * Math.random());
			const dataLength:int = 6;
			for (i = 0; i < dataLength; ++ i)
			{
				handbook_list_data = new Object;
				handbook_list_data.label = "第" + i + "级";
				handbook_list_data.index = i;
				handbook_list_data.type = 1;
				handbook_list_data.deepth = 0;
				handbook_list_data.visible = true;
				for(var j:int = 0; j < 4; j++)
				{
					handbook_list_data['handbook_item_data' + j] = new HandbookData();
					(handbook_list_data['handbook_item_data' + j] as HandbookData).handbook_class = handbook_class;
					//(handbook_list_data['handbook_item_data' + j] as HandbookData).handbook_type = handbook_type;
					(handbook_list_data['handbook_item_data' + j] as HandbookData).handbook_ui_type = handbook_ui_type;
					(handbook_list_data['handbook_item_data' + j] as HandbookData).handbook_obtain = (Math.random() > 0.5);
					handbook_list_data['handbook_item_data' + j].handbook_icon = (Math.random() > 0.5 ? "0.tga" : "1.tga");
					if(handbook_ui_type == ConstansDefine.handbook_map){
						(handbook_list_data['handbook_item_data' + j] as HandbookData).handbook_index = 0;
						break;
					}else{
						(handbook_list_data['handbook_item_data' + j] as HandbookData).handbook_index = j;
					}
				}
				handbook_list.push(handbook_list_data);
			}
			UCUpdateHandbookList(handbook_list, 0, dataLength * Math.random(), 0);
		}
		
		private function resetListItemState(singleItemSelectedIndex:int):void
		{
			var rowCount:int = handbook_list_mc.rowCount;
			for (var i:int = 0; i < rowCount; i ++)
			{
				var list_item:HandbookListItem = handbook_list_mc.getRendererAt(i) as HandbookListItem;
				if (list_item){
					list_item.selected = false;
					list_item.globalSelectedItemIndex = singleItemSelectedIndex;
				}
			}
		}
		
		private function TestMonsterPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_monster;
			handbook_data.handbook_text0 = "10-20";
			handbook_data.handbook_text1 = "矿洞一层";
			handbook_data.handbook_text2 = "矿洞一层有个怪物，很难被打死，击杀能掉不少好装备，需要组队前往。矿洞一层有个怪物，很难被打死，击杀能掉不少好装备，需要组队前往。矿洞一层有个怪物，很难被打死，击杀能掉不少好装备，需要组队前往。矿洞一层有个怪物，很难被打死，击杀能掉不少好装备，需要组队前往。矿洞一层有个怪物，很难被打死，击杀能掉不少好装备，需要组队前往。矿洞一层有个怪物，很难被打死，击杀能掉不少好装备，需要组队前往。";
			var i:int = 0;
			handbook_data.handbook_data0 = new Array();
//			var skillObj:Object;
//			for (i = 0; i < 5; ++ i)
//			{
//				skillObj = new Object();
//				skillObj['skill_icon'] = i % 2 > 0 ? "0.tga" : "1.tga";
//				skillObj['skill_id'] = i;
//				handbook_data.handbook_data0.push(skillObj);
//			}
			
			handbook_data.handbook_data1 = new Array();
			var dropObj:Object;
			for (i = 0; i < 12; ++ i)
			{
				dropObj = new Object();
				dropObj['item_icon'] = i % 2 > 0 ? "1.tga" : "0.tga";
				dropObj['item_id'] = i;
				handbook_data.handbook_data1.push(dropObj);
			}
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestMapPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_map;
			handbook_data.handbook_text0 = "0.tga";
			handbook_data.handbook_text1 = "矿洞一层,是比奇矿区的入口，遍布各种初级僵尸怪，当然也有不少值得挑战的小BOSS,越是深入,越能发现不少奇怪的生物，矿洞一层,是比奇矿区的入口，遍布各种初级僵尸怪，当然也有不少值得挑战的小BOSS,越是深入,越能发现不少奇怪的生物，矿洞一层,是比奇矿区的入口，遍布各种初级僵尸怪，当然也有不少值得挑战的小BOSS,越是深入,越能发现不少奇怪的生物，";
			var i:int = 0;
			handbook_data.handbook_data0 = new Array();
			var resourceObj:Object;
			for (i = 0; i < 5; ++ i)
			{
				resourceObj = new Object();
				resourceObj['item_icon'] = i % 2 > 0 ? "0.tga" : "1.tga";
				resourceObj['item_id'] = i;
				handbook_data.handbook_data0.push(resourceObj);
			}
			
			handbook_data.handbook_data1 = new Array();
			var bossObj:Object;
			for (i = 0; i < 4; ++ i)
			{
				bossObj = new Object();
				bossObj['npc_icon'] = i % 2 > 0 ? "1.tga" : "0.tga";
				bossObj['npc_name'] = "BOSS" + i;
				handbook_data.handbook_data1.push(bossObj);
			}
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestNpcPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_npc;
			handbook_data.handbook_text0 = "一个机智的少年";
			handbook_data.handbook_text1 = "<u>矿洞一层<u>";
			handbook_data.handbook_text2 = "父亲在矿洞失踪，每时每刻都在想着去矿洞深处寻找父亲。";
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestStoryPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_story;
			handbook_data.handbook_text0 = "矿洞一层,是比奇矿区的入口，遍布各种初级僵尸怪，当然也有不少值得挑战的小BOSS,越是深入,越能发现不少奇怪的生物，";
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestComposePage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_compose;
			handbook_data.handbook_text0 = "12,3456@";
			handbook_data.handbook_data0 = [];
			var compObj:Object;
			var i:int;
			for (i = 0; i < 7; ++ i)
			{
				compObj = new Object();
				compObj['item_icon'] = i % 2 > 0 ? "1.tga" : "0.tga";
				compObj['item_id'] 	 = i;
				compObj['item_info'] = "item_info" + i;
				handbook_data.handbook_data0.push(compObj);
			}
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestStonePage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_stone;
			handbook_data.handbook_text0 = "卷轴合成，怪物掉落";
			handbook_data.handbook_text2 = "比奇矿洞一层,是比奇矿区的入口，遍布各种初级僵尸怪，当然也有不少值得挑战的小BOSS,越是深入,越能发现不少奇怪的生物，杀死这些怪物，能有不错的收获，特别是灵石，为装备镶嵌灵力强大的宝石，能让你的升级降魔之路增添不少助力，其中，对于一个使用近程武器的战士来说，最为重要的宝石就是力量宝石了。杀死这些怪物，能有不错的收获，特别是灵石，为装备镶嵌灵力强大的宝石，能让你的升级降魔之路增添不少助力，其中，对于一个使用近程武器的战士来说，最为重要的宝石就是力量宝石了。杀死这些怪物，能有不错的收获，特别是灵石，为装备镶嵌灵力强大的宝石，能让你的升级降魔之路增添不少助力，其中，对于一个使用近程武器的战士来说，最为重要的宝石就是力量宝石了。";
			handbook_data.handbook_data0 = new Array();
			handbook_data.handbook_data1 = new Array();
			var levelStr:String;
			var stoneObj:Object;
			var i:int = 0;
			for (i = 0; i < 9; ++ i)
			{
				levelStr = (i + 1).toString() + "级";
				handbook_data.handbook_data1.push(levelStr);
				stoneObj = new Object();
				stoneObj['stone_icon'] = i % 2 > 0 ? "0.tga" : "1.tga";
				stoneObj['stone_id']   = i;
				stoneObj['stone_effect']   = "体力上限 +" + 100 * (i + 1);
				handbook_data.handbook_data0.push(stoneObj);
			}
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestSuitPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_suit;
			handbook_data.handbook_data0 = [];
			var suitObj:Object;
			var i:int;
			for (i = 0; i < 10; ++ i)
			{
				suitObj = new Object();
				suitObj['item_icon'] = i % 2 > 0 ? "1.tga" : "0.tga";
				suitObj['item_id'] 	 = i;
				handbook_data.handbook_data0.push(suitObj);
			}
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestEquipPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_equip;
			handbook_data.handbook_name = "TestEquipPage";
			handbook_data.handbook_sound = "1";
			handbook_data.handbook_data0 = [];
			var equipObj:Object = {};
			equipObj['equip_icon'] = "1.tga";
			equipObj['equip_id'] = 1;
			equipObj['equip_part'] = '双手剑';
			equipObj['equip_class'] = '战士';
			equipObj['equip_level'] = 35;
			equipObj['equip_rune'] = 5;
			equipObj['equip_prop'] = '150-666';
			equipObj['equip_suit_prop'] = '2件：力量+80\n4件：力量+200\n6件：力量+350\n8件：力量+500';
			handbook_data['handbook_text2'] = '一直以来，战士中级套装就是为此而存在，它比新手套装的品级要高得多，<br>整个套装的属性加成总共超过1000点力量，对于刚刚出道的战士们，是相当不错的。';
			handbook_data.handbook_data0[0] = equipObj;
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestRunePage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_rune;
			handbook_data.handbook_name = "TestRunePage";
//			handbook_data.handbook_data0 = new Array();
//			handbook_data.handbook_data1 = new Array();
//			var levelStr:String;
//			var runeObj:Object;
//			var i:int = 0;
//			for (i = 0; i < 9; ++ i)
//			{
//				levelStr = (i + 1).toString() + "级";
//				handbook_data.handbook_data1.push(levelStr);
//				runeObj = new Object();
//				runeObj['skill_icon'] = i % 2 > 0 ? "1.tga" : "0.tga";
//				runeObj['skill_id'] = i;
//				runeObj['skill_effect'] = "降低敌人50%的移动，持续3秒攻击造成" + 35 * (i+1) + "%的伤害";;
//				runeObj['rune_icon'] = i % 2 > 0 ? "0.tga" : "1.tga";
//				runeObj['rune_id'] = i;
//				runeObj['rune_class'] = '战士';
//				runeObj['rune_weapon'] = '剑盾';
//				runeObj['rune_color'] = "紫色";
//				runeObj['rune_effect']   = "发动技能时，可将最多" + 9 * (i + 1) + "个敌人, 一直以来，从出生到现在，作为一名战士都渴望拥有一套能大幅提升自己属性的装备，战士中级套装就是为此而存在，它比新手套装的品级要高得多，整个套装的属性加成总共超过1000点力量，对于刚刚出道的战士们，是相当不错的。一直以来，从出生到现在，作为一名战士都渴望拥有一套能大幅提升自己属性的装备，战士中级套装就是为此而存在，它比新手套装的品级要高得多，整个套装的属性加成总共超过1000点力量，对于刚刚出道的战士们，是相当不错的。";//拉到身边，击中后下次攻击该敌人必暴击。";
//				handbook_data.handbook_data0.push(runeObj);
//			}
			var runeObj:Object = {};
			runeObj['rune_icon'] = "1.tga";
			runeObj['rune_id'] = 0;
			handbook_data.handbook_data0 = [];
			handbook_data.handbook_data0[0] = runeObj;
			handbook_data.handbook_text0 = "将精神之力附着在护身符上，远程攻击目标";
			handbook_data.handbook_text1 = "可伤害目标灵魂，夺取其能量恢复自身。";
			
			UCUpdateHandbookInfo(handbook_data);
		}
		
		private function TestSpiritPage():void
		{
			var handbook_data:HandbookData = new HandbookData;
			handbook_data.handbook_ui_type = handbook_spirit;
			handbook_data.handbook_text0 = "龙卫心法练气合成";
			handbook_data.handbook_text1 = "比奇矿洞一层,是比奇矿区的入口，遍布各种初级僵尸怪，当然也有不少值得挑战的小BOSS,越是深入,越能发现不少奇怪的生物，杀死这些怪物，能有不错的收获，特别是灵石，为装备镶嵌灵力强大的宝石，能让你的升级降魔之路增添不少助力，其中，对于一个使用近程武器的战士来说，最为重要的宝石就是力量宝石了。";
			handbook_data.handbook_data0 = new Array();
			handbook_data.handbook_data1 = new Array();
			var levelStr:String;
			var spiritObj:Object;
			var i:int = 0;
			for (i = 0; i < 9; ++ i)
			{
				levelStr = (i + 1).toString() + "级";
				handbook_data.handbook_data1.push(levelStr);
				spiritObj = new Object();
				spiritObj['spirit_icon'] = i % 2 > 0 ? "0.tga" : "1.tga";
				spiritObj['spirit_effect']   = "怒气满时，提升" + (7 * (i + 1)) + "%的移动速度";
				handbook_data.handbook_data0.push(spiritObj);
			}
			UCUpdateHandbookInfo(handbook_data);
		}
	}
}