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
	import scaleform.clik.events.ButtonEvent;
	
	public class PersonContent extends UIComponent
	{
		public var personmenu_list_mc:ScrollingList;

		public var Container:Array;
		public var ItemData:TreeListData;
		
		//public var PersonPageExp_mc:PersonPageExp;
		public var PersonPageLevel_mc:PersonPageLevel;
		public var PersonPagePower_mc:PersonPagePower;
		public var PersonPageRich_mc:PersonPageRich;
		public var PersonPageAchievement_mc:PersonPageAchievement;
		public var PersonPageMaster_mc:PersonPageMaster;
		//public var PersonPageKill_mc:PersonPageKill;
		public var PersonPagePK_mc:PersonPagePK;
		//public var PersonPageEquipPower_mc:PersonPagePower;
		//public var PersonPageHeavenPower_mc:PersonPagePower;
		public var updateRank_txt_mc:TextField;
		public var myrank_mc:MyRankTxt;
		public var pagectrl_mc:MovieClip;
		
		//排名
		public var range0_radio_mc:RadioButton;
		public var range1_radio_mc:RadioButton;
		public var range2_radio_mc:RadioButton;
		public var range3_radio_mc:RadioButton;
		public var range4_radio_mc:RadioButton;
		public var range5_radio_mc:RadioButton;
		public var range6_radio_mc:RadioButton;
		//树节点类型
		public const SUBNODE:int = 0;                                   	//子节点
		public const PARENTNODE_EX:int = 1;							//可展开的父节点
		public const PARENTNODE:int = 2;						//不可展开的父节点
		public var IsShowRank:Boolean=false;//是否显示排名

		override protected function configUI():void
		{
			super.configUI();
			Container = new Array();
			//Container.push(PersonPageExp_mc);
			Container.push(PersonPagePower_mc);
			Container.push(PersonPageLevel_mc);
			//Container.push(PersonPageKill_mc);
			Container.push(PersonPagePK_mc);
			Container.push(PersonPageRich_mc);
			Container.push(PersonPageAchievement_mc);
			Container.push(PersonPageMaster_mc);
			var i:int=0;
			for(i = 1; i < Container.length; i++)
			{
				Container[i].visible = false;
			}
			for(i=0;i<7;i++)
			{
				var mc:RadioButton=this.getChildByName("range"+i+"_radio_mc") as RadioButton;
				if(mc)
				{
					mc.itemid=i;
					mc.addEventListener(MouseEvent.CLICK, OnPersonRangeClick);
				}
			}
			var prevPage:Button = pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != prevPage)
				prevPage.addEventListener(MouseEvent.CLICK, OnPrevPageClick);
			var nextPage:Button = pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != nextPage)
				nextPage.addEventListener(MouseEvent.CLICK, OnNextPageClick);
			personmenu_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnTreeItemClick);
		    personmenu_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onCategoryListChange);
			//Test();
			//TestData(4);
		}
		
		public function hide(bl:Boolean):void
		{
			IsShowRank=bl;
			updateRank_txt_mc.visible=bl;
			myrank_mc.visible=bl;
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
		
		protected function onCategoryListChange( evt:ListEvent ):void
		{
			if(IsShowRank==true)
			{
				var targetList:ScrollingList = evt.target as ScrollingList;
			    if (targetList != null)
			    {
				    var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;
				    if(Provider)
				    {
					    ItemData = Provider.requestItemAt(evt.index) as TreeListData;
					    if( ItemData.type == SUBNODE)
					    {
						   ExternalInterface.call( "ASPersonTreeItemClick", ItemData.index );
					    }
				     }
				    targetList.invalidateData();
			    }
			}
		}

		public function UpdatePersonListData( data:Array ):void
		{
			if(data){
				var type:int = data[0] as int;
				data.shift();
			}
			for(var i:int = 0; i < Container.length; i++)
			{
				if(Container[i].rlType==type){
					Container[i].visible = true;
					Container[i].UpdatePersonListData(data);
				}else{
					Container[i].visible = false;
				}
				
			}
		}
		
		public function LoadPersonMenuData( data:Array ):void
		{
			if(null != data && personmenu_list_mc != null)
			{
				personmenu_list_mc.dataProvider = new TreeDataProvider(data);
				personmenu_list_mc.validateNow();
				personmenu_list_mc.invalidateData();
				personmenu_list_mc.selectedIndex=0;
			}
		}
		
		private function OnTreeItemClick(e:ListEvent):void
		{
			clear();//每次切换标签页的时候也重置 
			var targetList:ScrollingList = e.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;
				if( Provider != null )
				{
					Provider.handleListItemClick( e );
					targetList.invalidateData();
				}
			}
		}
		
		public function UpdatePage(data:Object):void
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
					
			var range0:Boolean,range1:Boolean ,range2:Boolean ,range3:Boolean , range4:Boolean , range5:Boolean, range6:Boolean = false;
					//更新rangeRadiobtn
			if(maxPage > 30)
			{
				range0 = range1 = range2 = range3 = range4 = range5 = range6 = true;
			}
			else if(maxPage > 20 &&  maxPage <= 30)
			{
				range0 = range1 = range2 = range3 = range4 = range5 = true;
				range6 = false;
			}
			else if(maxPage > 10 &&  maxPage <= 20)
			{
				range0 = range1 = range2 = range3 = range4 = true;
				range5 = range6 = false;
			}
			else if(maxPage > 5 && maxPage <= 10)
			{
				range0 = range1 = range2 = range3 = true;
				range4 = range5 = range6 =false;
			}
			else if(maxPage > 2 && maxPage <= 5)
			{
				range0 = range1 = range2 =  true;
				range3 = range4 = range5 = range6 = false;
			}
			else if (maxPage >1 && maxPage <= 2)
			{
				range0 = range1 =  true;
				range2 = range3 = range4 = range5 = range6 = false;
			}
			else
			{
				range0 = true;
				range1 = range2 = range3 = range4 = range5 = range6 = false;
			}
			range0_radio_mc.visible = range0;
			range1_radio_mc.visible = range1;
			range2_radio_mc.visible = range2;
			range3_radio_mc.visible = range3;
			range4_radio_mc.visible = range4;
			range5_radio_mc.visible = range5;
			range6_radio_mc.visible = range6;
		}
		
		public function UpdateMyRank(Rank:String , CurrentRank:int, LastRank:int):void
		{
			myrank_mc.updateData(Rank,CurrentRank,LastRank);
/*			for(var i:int = 0; i < Container.length; i++)
			{
				if(Container[i] && Container[i].visible)
				{
					Container[i].updateMyRank(Rank,CurrentRank,LastRank);
					return;
				}
			}*/
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
				case 4:
					range4_radio_mc.selected = true;
				break;
				case 5:
					range5_radio_mc.selected = true;
				break
			}
		}
		
		public function onTabClick():void
		{
			personmenu_list_mc.selectedIndex=0;//每次打开选中第一个
		}
		
		public function clear():void
		{//每次打开都选中全部
			PersonPagePower_mc.category0_btn_mc.selected = true;
			range0_radio_mc.selected=true;
			(pagectrl_mc.getChildByName("tF_pageNum") as TextField).text="1/5";
			onTabClick();
/*			var i:int=0;
			if(Container)
			{
				var l:int=Container.length;
				for(i; i < l; i++)
				{
					Container[i].clear();
				}
			}*/
		}
		
		public function UCUpdateTime(timeUpdate:String):void
		{
			updateRank_txt_mc.text = timeUpdate;
		}
				
		private function OnPrevPageClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASPrevPageClick");
		}
		
		private function OnNextPageClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNextPageClick");
		}		
		
		public function SetMaxLevel(lv:String):void
		{
			PersonPageLevel_mc.SetMaxLevel(lv);
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
			itemsData[1].type = SUBNODE;
			itemsData[1].deepth = 0;
			itemsData[2].type = SUBNODE;
			itemsData[2].deepth = 1;
			itemsData[3].type = SUBNODE;
			itemsData[3].deepth = 1;

			LoadPersonMenuData(itemsData);
			
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
				UpdatePersonListData(personLevelData);
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
				UpdatePersonListData(personPowerData);
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
				UpdatePersonListData(personRichData);
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
				UpdatePersonListData(personAchievementData);
			}
			else if(4 == index)
			{
				var personMasterData:Array = new Array();
				personMasterData.push(6);
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
				UpdatePersonListData(personMasterData);
			}
			
		}*/
		
		
	}
	
}
