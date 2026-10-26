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
	
	public class PowerContent extends UIComponent
	{
		public var powermenu_list_mc:ScrollingList;
		
		
		public var Container:Array;
		public var ItemData:TreeListData;
		
		public var PowerPagePower_mc:PowerPagePower;
		public var PowerPageAmbit_mc:PowerPageAmbit;
		public var PowerPageBuild_mc:PowerPageBuild;
		public var PowerPageEquip_mc:PowerPageEquip;
		
		//public var PersonPageEquipPower_mc:PersonPagePower;
		//public var PersonPageHeavenPower_mc:PersonPagePower;
		
		//树节点类型
		public const SUBNODE:int = 0;                                   	//子节点
		public const PARENTNODE_EX:int = 1;							//可展开的父节点
		public const PARENTNODE:int = 2;								//不可展开的父节点
		
		public function PowerContent()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			Container = new Array();
			Container.push(PowerPagePower_mc);
			Container.push(PowerPageEquip_mc);
			Container.push(PowerPageBuild_mc);
			Container.push(PowerPageAmbit_mc);
			
			for(var i:int = 1; i < Container.length; i++)
			{
				trace(Container[i]);
				Container[i].visible = false;
			}
			//Container[4].visible = true;
			
			powermenu_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnTreeItemClick);
			powermenu_list_mc.addEventListener(ListEvent.ITEM_CLICK, onCategoryListChange);
			//Test();
			//TestData(4);
		}
		protected function onCategoryListChange( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
/*		public function Test()
		{
			var itemsData:Array = new Array();
			for (var idx:int = 0; idx < 7; idx++)
			{
				var fbnMarkData:TreeListData = new TreeListData ;
				fbnMarkData.index = idx;
				fbnMarkData.type = SUBNODE;
				fbnMarkData.deepth =0;
				fbnMarkData.visible = true;
				fbnMarkData.label = "副本名字" + idx;
				
				itemsData.push(fbnMarkData);
			}
			itemsData[1].type = PARENTNODE_EX;
			itemsData[1].deepth = 0;
			itemsData[2].type = SUBNODE;
			itemsData[2].deepth = 1;
			itemsData[3].type = SUBNODE;
			itemsData[3].deepth = 1;

			LoadPowerMenuData(itemsData);
			
		}
		
		function TestData(index:int)
		{
			if(0 == index)
			{
				var personLevelData:Array = new Array();
				for(var index0:int = 0; index0 < 13; ++index0)
				{
					var data0:PersonLevelItemListData = new PersonLevelItemListData;
					data0.Id = index0;
					data0.RankIndex = index0.toString();
					data0.OnLine = false;
					data0.RoleName = "饿狼传说";
					data0.Job = "2/1";
					data0.GuildName = "无敌" + index0;
					data0.Level = "20000" + index0;
					personLevelData.push(data0);
				}
				UpdatePowerListData(personLevelData);
			}
			else if(1 == index)
			{
				var personPowerData:Array = new Array();
				for(var index1:int = 0; index1 < 13; ++index1)
				{
					var data1:PersonPowerItemListData = new PersonPowerItemListData;
					data1.Id = index1;
					data1.RankIndex = index1.toString();
					data1.RoleName = "饿狼传说";
					data1.Job = "2/1";
					data1.GuildName = "无敌" + index1;
					data1.Level = "20000" + index1;
					data1.Power = String(30000 + index1);
					personPowerData.push(data1);
				}
				UpdatePowerListData(personPowerData);
			}
			else if(2 == index)
			{
				var personRichData:Array = new Array();
				for(var index2:int = 0; index2 < 13; ++index2)
				{
					var data2:PersonRichItemListData = new PersonRichItemListData;
					data2.Id = index2;
					data2.OnLine = false;
					data2.RankIndex = index2.toString();
					data2.RoleName = "饿狼传说";
					data2.Job = "2/1";
					data2.GuildName = "无敌" + index2;
					data2.Level = "20000" + index2;
					data2.Found = int(30000 + index2);
					personRichData.push(data2);
				}
				UpdatePowerListData(personRichData);
			}
			else if(3 == index)
			{
				var personAchievementData:Array = new Array();
				for(var index3:int = 0; index3 < 13; ++index3)
				{
					var data3:PersonAchievementItemListData = new PersonAchievementItemListData;
					data3.Id = index3;
					data3.OnLine = false;
					data3.RankIndex = index3.toString();
					data3.RoleName = "饿狼传说";
					data3.Job = "2/1";
					data3.GuildName = "无敌" + index3;
					data3.Level = "20000" + index3;
					data3.Grades = String(30000 + index3);
					personAchievementData.push(data3);
				}
				UpdatePowerListData(personAchievementData);
			}
			else if(4 == index)
			{
				var personMasterData:Array = new Array();
				personMasterData.push(22);
				for(var index4:int = 0; index4 < 10; ++index4)
				{
					var data4:PersonMasterItemListData = new PersonMasterItemListData;
					data4.Id = index4;
					data4.OnLine = false;
					data4.RankIndex = index4.toString();
					data4.RoleName = "饿狼传说";
					data4.Job = "2/1";
					data4.GuildName = "无敌" + index4;
					data4.Level = "20000" + index4;
					data4.Grades = String(30000 + index4);
					personMasterData.push(data4);
				}
				UpdatePowerListData(personMasterData);
			}
			
		}*/
		
		public function UpdatePowerListData( data:Array ):void
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				Container[i].UpdatePowerListData(data);
			}
		}
		
		public function LoadPowerMenuData( data:Array ):void
		{
			if(null != data && powermenu_list_mc != null)
			{
				powermenu_list_mc.dataProvider = new TreeDataProvider(data);
				powermenu_list_mc.validateNow();
				powermenu_list_mc.invalidateData();
				powermenu_list_mc.selectedIndex=0;
			}
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
					ItemData = Provider.requestItemAt(e.index) as TreeListData;
					//trace(ItemData);
					
					if( ItemData.type == SUBNODE)
					{
						ExternalInterface.call( "ASPowerTreeItemClick", ItemData.index );
					}
					else
					{
						targetList.invalidateData();
					}
					
					//TestData(ItemData.index);
				}
				UpdateCategory();
			}
			
		}
		
		function UpdatePage(data:Object)
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				if(Container[i] && Container[i].visible)
				{
					var tF_pageNum:TextField = Container[i].pagectrl_mc.getChildByName("tF_pageNum");
					if(null != tF_pageNum)
						tF_pageNum.text = data.PageNumTxt;
						
					var btn_prev:Button =  Container[i].pagectrl_mc.getChildByName("btn_prev");
					if(null != btn_prev)
						btn_prev.enabled = data.preEnable;
						
					var btn_next:Button =  Container[i].pagectrl_mc.getChildByName("btn_next");
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
					Container[i].range0_radio_mc.visible = range0;
					Container[i].range1_radio_mc.visible = range1;
					Container[i].range2_radio_mc.visible = range2;
					Container[i].range3_radio_mc.visible = range3;
					Container[i].range4_radio_mc.visible = range4;
					Container[i].range5_radio_mc.visible = range5;
					return ;
				}
			}
		}
		
		function UpdateMyRank(Rank:String)
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				if(Container[i] && Container[i].visible)
				{
					Container[i].myrank_txt_mc.htmlText = Rank;
					return;
				}
			}
		}
		
		function UpdateRangeRdoSelect(nIndex:int)
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				if(Container[i] && Container[i].visible)
				{
					switch(nIndex)
					{
						case 0:
							Container[i].range0_radio_mc.selected = true;
						break;
						case 1:
							Container[i].range1_radio_mc.selected = true;
						break
						case 2:
							Container[i].range2_radio_mc.selected = true;
						break;
						case 3:
							Container[i].range3_radio_mc.selected = true;
						break;
						case 4:
							Container[i].range4_radio_mc.selected = true;
						break;
						case 5:
							Container[i].range5_radio_mc.selected = true;
						break
					}
					return;
				}
			}
		}
		
		function UpdateCategory()
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				Container[i].category0_btn_mc.selected = true;
				Container[i].category1_btn_mc.selected = false;
				Container[i].category2_btn_mc.selected = false;
				Container[i].category3_btn_mc.selected = false;
				Container[i].category4_btn_mc.selected = false;
			}
		}
		
	}
	
}
