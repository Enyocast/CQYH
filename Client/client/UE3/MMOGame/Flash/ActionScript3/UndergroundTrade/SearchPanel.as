package ActionScript3.UndergroundTrade
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import ActionScript3.TreeListData;
	import flash.text.TextField;
	
	import ActionScript3.UndergroundTrade.UTListItemRender;
	import ActionScript3.UndergroundTrade.UTListItemData;
	
	
	public class SearchPanel extends UIComponent
	{
		public var equipname_inptxt_mc:TextInput;
		public var startlev_inputtxt_mc:TextInput;
		public var endlev_inputtxt_mc:TextInput;
		public var job_DropdownMenu_mc:DropdownMenu;
		public var quality_DropdownMenu_mc:DropdownMenu;
		public var canuse_checkbtn_mc:Button;
		public var search_btn_mc:Button;
		public var reset_btn_mc:Button;
		public var equip_list_mc:ScrollingList;
		
		public var equipname_btn_mc:Button;
		public var level_btn_mc:Button;
		public var signer_btn_mc:Button;
		public var price_btn_mc:Button;
		public var lefttime_btn_mc:Button;
		public var search_list_mc:ScrollingList;
		
		public var bid_btn_mc:Button;
		public var gold_txt_mc:TextField;
		public var prevpage_btn_mc:Button;
		public var nextpage_btn_mc:Button;
		public var page_txt_mc:TextField;
		
		//树节点类型
		public const SUBNODE:int = 0;                                   	//子节点
		public const PARENTNODE_EX:int = 1;							//可展开的父节点
		public const PARENTNODE:int = 2;								//不可展开的父节点
		
		public function SearchPanel()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("------SearchPanel  super.configUI:");
			super.configUI();
			
			InitData();
			
			var itemsData:Array = new Array();
			for (var idx:int = 0; idx < 15; idx++)
			{
				var fbnMarkData:TreeListData = new TreeListData ;
				fbnMarkData.index = idx;
				fbnMarkData.type = SUBNODE;
				fbnMarkData.deepth =1;
				fbnMarkData.visible = true;
				fbnMarkData.label = "副本名字" + idx;
				
				itemsData.push(fbnMarkData);
			}
			itemsData[0].type = PARENTNODE_EX;
			itemsData[0].deepth = 0;
			itemsData[3].type = PARENTNODE_EX;
			itemsData[3].deepth = 0;
			
			itemsData[5].type = PARENTNODE_EX;
			itemsData[5].deepth = 0;
			itemsData[6].type = PARENTNODE_EX;
			itemsData[6].deepth = 1;
			itemsData[7].type = SUBNODE;
			itemsData[7].deepth = 2;
			itemsData[8].type = SUBNODE;
			itemsData[8].deepth = 2;

			UpdateEquipListData(itemsData);
			
			var searchItemData:Array = new Array();
			for(var index:int = 0; index < 15; ++index)
			{
				var data:UTListItemData = new UTListItemData;
				data.iconName = "" ;
				data.equipName = "屠龙刀" + index;
				data.level = index.toString() ;
				data.signer = "张无忌" + index;
				data.all = (3000 + index).toString();
				data.leftTime = "2013-12-" + index;
				searchItemData.push(data);
			}
			UpdateSearchData(searchItemData);
			
		}
		
		private function InitData():void
		{
			if(null != startlev_inputtxt_mc)
				startlev_inputtxt_mc.text = "1";
			if(null != endlev_inputtxt_mc)
				endlev_inputtxt_mc.text = "99";
				
			if(null != job_DropdownMenu_mc)
			{
				job_DropdownMenu_mc.addEventListener(ListEvent.INDEX_CHANGE, OnJobChange);
				var jobData:Array = ["全部",  "战士", "刺客", "法师","弓手"];
				UpdateJobData(jobData);
			}
			
			if(null != quality_DropdownMenu_mc)
			{
				quality_DropdownMenu_mc.addEventListener(ListEvent.INDEX_CHANGE, OnQualityChange);
				var qualityData:Array = ["全部",  "普通", "精通", "稀有","史诗", "传承"];
				UpdateQualityData(qualityData);
			}
			
			if(null != canuse_checkbtn_mc)
			{
				canuse_checkbtn_mc.label = "可用装备";
				canuse_checkbtn_mc.selected = false;
				canuse_checkbtn_mc.addEventListener(MouseEvent.CLICK, OnCanUse);
			}
			
			if(null != search_btn_mc)
			{
				search_btn_mc.label = "搜索";
				search_btn_mc.addEventListener(MouseEvent.CLICK, OnSearch);
			}
			
			if(null != reset_btn_mc)
			{
				reset_btn_mc.label = "重置";
				reset_btn_mc.addEventListener(MouseEvent.CLICK, OnReset);
			}
			
			if(null != equip_list_mc)
			{
				equip_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnTreeItemClick);
			}
			
			if(null != bid_btn_mc)
			{
				bid_btn_mc.label = "竞标";
				bid_btn_mc.addEventListener(MouseEvent.CLICK, OnBid);
			}
			
			if(null != search_list_mc)
			{
				search_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnSearchListItemClick);
			}
			
			if(null != equipname_btn_mc)
			{
				equipname_btn_mc.label = "装备名字";
				equipname_btn_mc.addEventListener(MouseEvent.CLICK, OnEqiupNameSort);
			}
			
			if(null != level_btn_mc)
			{
				level_btn_mc.label = "等级";
				level_btn_mc.addEventListener(MouseEvent.CLICK, OnLevelSort);
			}
			
			if(null != signer_btn_mc)
			{
				signer_btn_mc.label = "签名人";
				signer_btn_mc.addEventListener(MouseEvent.CLICK, OnSignerSort);
			}
			
			if(null != price_btn_mc)
			{
				price_btn_mc.label = "当前价格";
				price_btn_mc.addEventListener(MouseEvent.CLICK, OnPriceSort);
			}
			
			if(null != lefttime_btn_mc)
			{
				lefttime_btn_mc.label = "剩余时间";
				lefttime_btn_mc.addEventListener(MouseEvent.CLICK, OnLeftTimeSort);
			}
			
			if(null != prevpage_btn_mc)
				prevpage_btn_mc.addEventListener(MouseEvent.CLICK, OnPrevPage);
			if(null != nextpage_btn_mc)
				nextpage_btn_mc.addEventListener(MouseEvent.CLICK, OnNextPage);
			
		}
		
		function OnJobChange(e:Event)
		{
			if(null != job_DropdownMenu_mc)
			{
				var job:String = job_DropdownMenu_mc.dataProvider.requestItemAt(job_DropdownMenu_mc.selectedIndex) as String;
				ExternalInterface.call("ASChangeJob", job);
			}
		}
		
		function OnQualityChange(e:Event)
		{
			if(null != quality_DropdownMenu_mc)
				ExternalInterface.call("ASChangeQuality", quality_DropdownMenu_mc.selectedIndex);
		}
		
		function OnCanUse():void
		{
			if(null != canuse_checkbtn_mc)
				canuse_checkbtn_mc.selected = !canuse_checkbtn_mc.selected;
		}
		
		function OnSearch():void
		{
			
		}
		
		function OnReset():void
		{
			
		}
		
		function OnTreeItemClick(e:ListEvent):void
		{
			
			var targetList:ScrollingList = e.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;

				if( Provider != null )
				{
					//trace(e);
					Provider.handleListItemClick( e );
					var itemData:TreeListData = Provider.requestItemAt(e.index) as TreeListData;
					//trace(itemData);
					
					if( itemData.type == SUBNODE )
					{
						ExternalInterface.call( "ASSearchEquip", itemData.index );
					}
					else
					{
						targetList.invalidateData();
					}
					
				}
			}
		}

		public function UpdateEquipListData( data:Array ):void
		{
			if(null != data && equip_list_mc != null)
			{
				equip_list_mc.dataProvider = new TreeDataProvider(data);
				equip_list_mc.validateNow();
				equip_list_mc.invalidateData();
			}
			else
				trace("SearchPanel->UpdateEquipListData failed!");
		}
		
		public function UpdateJobData( data:Array ):void
		{
			if(null != data && job_DropdownMenu_mc != null)
			{
				job_DropdownMenu_mc.dataProvider = new DataProvider(data);
				job_DropdownMenu_mc.validateNow();
				job_DropdownMenu_mc.invalidateData();
				job_DropdownMenu_mc.selectedIndex = 0;
			}
			else
				trace("SearchPanel->UpdateJobData failed!");
		}
		
		public function UpdateQualityData( data:Array ):void
		{
			if(null != data && quality_DropdownMenu_mc != null)
			{
				quality_DropdownMenu_mc.dataProvider = new DataProvider(data);
				quality_DropdownMenu_mc.validateNow();
				quality_DropdownMenu_mc.invalidateData();
				quality_DropdownMenu_mc.selectedIndex = 0;
			}
			else
				trace("SearchPanel->UpdateQualityData failed!");
		}
		
		function OnBid():void
		{
			
		}
		
		function OnEqiupNameSort():void
		{
			
		}
		
		function OnLevelSort():void
		{
			
		}
		
		function OnSignerSort():void
		{
			
		}
		
		function OnPriceSort():void
		{
			
		}
		
		function OnLeftTimeSort():void
		{
			
		}
		
		function OnSearchListItemClick(e:ListEvent):void
		{
			var listItem:UTListItemRender = e.itemRenderer as UTListItemRender;
			//if(null != listItemSearch)
				//listItemSearch.SearchListItemData.
		}
		
		public function UpdateSearchData( data:Array ):void
		{
			if(null != data && search_list_mc != null)
			{
				search_list_mc.dataProvider = new DataProvider(data);
				search_list_mc.validateNow();
				search_list_mc.invalidateData();
			}
			else
				trace("SearchPanel->UpdateJobData failed!");
		}
		
		function OnPrevPage():void
		{
			
		}
		
		function OnNextPage():void
		{
			
		}
		
	}
	
}
