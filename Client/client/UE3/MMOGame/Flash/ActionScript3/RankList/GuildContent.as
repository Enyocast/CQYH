package ActionScript3.RankList 
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
	import scaleform.clik.controls.RadioButton;
	
	
	public class GuildContent extends UIComponent 
	{
		public var guildmenu_list_mc:ScrollingList;
		
		public var GuildPageLevel_mc:GuildPageLevel;
		//public var GuildPageExp_mc:GuildPageExp;
		public var GuildPageFound_mc:GuildPageFound;
		//public var GuildPageResource_mc:GuildPageResource;
		public var GuildPagePower_mc:GuildPagePower;
		
		public var Container:Array;
		public var ItemData:TreeListData;
		public var updateRank_txt_mc:TextField;
		public var myrank_txt_mc:TextField;
		public var pagectrl_mc:MovieClip;
		public var range0_radio_mc:RadioButton;
		public var range1_radio_mc:RadioButton;
		public var range2_radio_mc:RadioButton;
		public var range3_radio_mc:RadioButton;
		//树节点类型
		public const SUBNODE:int = 0;                                   	//子节点
		public const PARENTNODE_EX:int = 1;							//可展开的父节点
		public const PARENTNODE:int = 2;								//不可展开的父节点
		
		public var IsShowRank:Boolean=false;//是否显示排名
		
		override protected function configUI():void
		{
			super.configUI();
			
			Container = new Array();
			Container.push(GuildPagePower_mc);
			Container.push(GuildPageLevel_mc);
			//Container.push(GuildPageExp_mc);
			Container.push(GuildPageFound_mc);
			//Container.push(GuildPageResource_mc);
			var i:int=0;
			for(i=0;i<4;i++)
			{
				var mc:RadioButton=this.getChildByName("range"+i+"_radio_mc") as RadioButton;
				if(mc)
				{
					mc.itemid=i;
					mc.addEventListener(MouseEvent.CLICK, OnPersonRangeClick);
				}
			}
			
			for(i= 1; i < Container.length; i++)
				Container[i].visible = false;
			//Container[1].visible = true;

			guildmenu_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnTreeItemClick);
			guildmenu_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onCategoryListChange);
			var prevPage:Button = pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != prevPage)
				prevPage.addEventListener(MouseEvent.CLICK, OnPrevPageClick);
			var nextPage:Button = pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != nextPage)
				nextPage.addEventListener(MouseEvent.CLICK, OnNextPageClick);
			//Test();
			//TestData(0);
		}
		
		public function hide(bl:Boolean):void
		{
			IsShowRank=bl;
			updateRank_txt_mc.visible=bl;
			myrank_txt_mc.visible=bl;
			pagectrl_mc.visible=bl;
		}
		
		private function OnPersonRangeClick(evt:MouseEvent):void
		{
			if(IsShowRank==true)
			{
				var mc:RadioButton=evt.target as RadioButton;
			    if(mc)
			    {
				    var index:int=int(mc.itemid);
				    ExternalInterface.call("ASRangeClick", index);
			    }
			}
		}

        protected function onCategoryListChange( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}

		public function UpdateGuildListData( data:Array ):void
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				Container[i].UpdateGuildListData(data);
			}
		}
		
		public function LoadGuildMenuData( data:Array ):void
		{
			if(null != data && guildmenu_list_mc != null)
			{
				guildmenu_list_mc.dataProvider = new TreeDataProvider(data);
				guildmenu_list_mc.validateNow();
				guildmenu_list_mc.invalidateData();
				this.guildmenu_list_mc.selectedIndex=0;
			}
				
		}
		
		private function OnTreeItemClick(e:ListEvent):void
		{
			clear();
			if(IsShowRank==true)
			{
				var targetList:ScrollingList = e.target as ScrollingList;
			    if (targetList != null)
			    {
				    var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;
				    if( Provider != null )
				    {
					    Provider.handleListItemClick( e );
					    ItemData = Provider.requestItemAt(e.index) as TreeListData;
					
					    if( ItemData.type == SUBNODE )
					    {
						    ExternalInterface.call( "ASGuildTreeItemClick", ItemData.index );
					     }
					     else
					     {
						     targetList.invalidateData();
					     }
				    }
			     }
			}
		}
		
		private function UpdatePage(data:Object):void
		{
			var tF_pageNum:TextField = pagectrl_mc.getChildByName("tF_pageNum") as TextField;
			if(null != tF_pageNum)
				tF_pageNum.text = data.PageNumTxt;
						
			var btn_prev:Button =  pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != btn_prev)
				btn_prev.enabled = data.preEnable;
						
			var btn_next:Button =  pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != btn_next)
				btn_next.enabled = data.nextEnable;
					
			var maxPage:int = data.MaxPage;
			var range0:Boolean,range1:Boolean ,range2:Boolean ,range3:Boolean , range4:Boolean , range5:Boolean = false;
			//更新rangeRadiobtn
			if(maxPage > 15)
			{
				range0 = range1 = range2 = range3 = range4 = range5 = true;
			}
			else if(maxPage > 10 &&  maxPage <= 15)
			{
				range0 = range1 = range2 = range3 = range4 = true;
				range5 = false;
			}
			else if(maxPage > 5 && maxPage <= 10)
			{
				range0 = range1 = range2 = range3 = true;
				range4 = range5 = false;
			}
			else if(maxPage > 2 && maxPage <= 5)
			{
				range0 = range1 = range2 =  true;
				range3 = range4 = range5 = false;
			}
			else if (maxPage >1 && maxPage <= 2)
			{
				range0 = range1 =  true;
				range2 = range3 = range4 = range5 = false;
			}
			else
			{
				range0 = true;
				range1 = range2 = range3 = range4 = range5 = false;
			}
			range0_radio_mc.visible = range0;
			range1_radio_mc.visible = range1;
			range2_radio_mc.visible = range2;
			range3_radio_mc.visible = range3;
		}
		
		private function OnPrevPageClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASPrevPageClick");
		}
		
		private function OnNextPageClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNextPageClick");
		}
		
		public function UpdateMyRank(Rank:String):void
		{
			myrank_txt_mc.htmlText = Rank;
		}
		
		public function UpdateRangeRdoSelect(nIndex:int):void
		{
			switch(nIndex)
			{
				case 0:
				    range0_radio_mc.selected = true;
				break;
				case 1:
					range1_radio_mc.selected = true;
				break
				case 2:
					range2_radio_mc.selected = true;
				break;
				case 3:
					range3_radio_mc.selected = true;
				break;
/*				case 4:
					range4_radio_mc.selected = true;
				break;
				case 5:
					range5_radio_mc.selected = true;
				break;*/
			}
		}
		
		public function clear():void
		{
			range0_radio_mc.selected=true;
			(pagectrl_mc.getChildByName("tF_pageNum") as TextField).text="1/5";
			var i:int=0;
			var l:int=0;
			if(Container)
			{
				l=Container.length;
				for(i=0; i < l; i++)
				{
					Container[i].clear();
				}
			}
			//onTabClick();
		}
		public function onTabClick():void
		{
			guildmenu_list_mc.selectedIndex=0;
		}
		
		public function UCUpdateTime(timeUpdate:String):void
		{
			updateRank_txt_mc.text = timeUpdate;
		}

/*		public function Test()
		{
			var itemsData:Array = new Array();
			for (var idx:int = 0; idx < 1; idx++)
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
			LoadGuildMenuData(itemsData);
		}
		function TestData(index:int)
		{
			if(0 == index)
			{
				var guildLevelData:Array = new Array();
				guildLevelData.push(23);
				for(var index0:int = 0; index0 < 10; ++index0)
				{
					var data0:GuildLevelItemListData = new GuildLevelItemListData;
					data0.Id = index0;
					data0.RankIndex = index0.toString();
					data0.GuildName = "饿狼传说";
					data0.Num = "2/1";
					data0.GuilderName = "无敌" + index0;
					data0.Level = "20000" + index0;
					guildLevelData.push(data0);
				}
				UpdateGuildListData(guildLevelData);
			}
		}*/
		
		
	}
	
}
