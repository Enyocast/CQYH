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
	
	public class TeamContent extends UIComponent
	{
		public var TeamMenu_list_mc:ScrollingList;
		
		public var TournamentPageLadder_mc:TournamentPageLadder;
		public var TournamentPageCorps_mc:TournamentPageCorps;
		public var TournamentPageFB_mc:TournamentPageFB;
		public var TournamentPageKill_mc:TournamentPageKill;
		public var TournamentPagePK_mc:TournamentPagePK;
		
		public var Container:Array;
		public var ItemData:TreeListData;
		
		//树节点类型
		public const SUBNODE:int = 0;                                   	//子节点
		public const PARENTNODE_EX:int = 1;							//可展开的父节点
		public const PARENTNODE:int = 2;								//不可展开的父节点
		
		override protected function configUI():void
		{
			super.configUI();
			
			Container = new Array();
			Container.push(TournamentPageLadder_mc);
			Container.push(TournamentPageCorps_mc);
			Container.push(TournamentPageFB_mc);
			Container.push(TournamentPageKill_mc);
			Container.push(TournamentPagePK_mc);
			
			for(var i:int = 1; i < Container.length; i++)
			{
				if(Container[i])
					Container[i].visible = false;
			}
			TeamMenu_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnTreeItemClick);
		}
		
/*		public function Test()
		{
			var itemsData:Array = new Array();
			for (var idx:int = 0; idx < 5; idx++)
			{
				var fbnMarkData:TreeListData = new TreeListData ;
				fbnMarkData.index = idx;
				fbnMarkData.type = SUBNODE;
				fbnMarkData.deepth =0;
				fbnMarkData.visible = true;
				fbnMarkData.label = "副本名字" + idx;
				
				itemsData.push(fbnMarkData);
			}
			LoadTournamentMenuData(itemsData);
		}
		
		function TestData(index:int)
		{
			if(0 == index)
			{
				var TournamentLadderData:Array = new Array();
				for(var index0:int = 0; index0 < 13; ++index0)
				{
					var data0:TournamentLadderItemListData = new TournamentLadderItemListData;
					data0.Id = index0;
					data0.RankIndex = index0.toString();
					data0.OnLine = false;
					data0.RoleName = "饿狼传说";
					data0.Job = "2/1";
					data0.Grades = "无敌" + index0;
					data0.Level = "20000" + index0;
					TournamentLadderData.push(data0);
				}
				UpdateTournamentListData(TournamentLadderData);
			}
			else if(1 == index)
			{
				var tournamentCorpsData:Array = new Array();
				for(var index1:int = 0; index1 < 13; ++index1)
				{
					var data1:TournamentCorpsItemListData = new TournamentCorpsItemListData;
					data1.Id = index1;
					data1.RankIndex = index1.toString();
					data1.CorpsName = "饿狼传说";
					data1.Captain = "2/1";
					data1.Grades = "20000" + index1;
					tournamentCorpsData.push(data1);
				}
				UpdateTournamentListData(tournamentCorpsData);
			}
			else if(2 == index)
			{

			}
			else if(3 == index)
			{
				var TournamentKillData:Array = new Array();
				for(var index3:int = 0; index3 < 13; ++index3)
				{
					var data3:TournamentKillItemListData = new TournamentKillItemListData;
					data3.Id = index3;
					data3.OnLine = false;
					data3.RankIndex = index3.toString();
					data3.RoleName = "饿狼传说";
					data3.Job = "2/1";
					data3.GuildName = "无敌" + index3;
					data3.Level = "20000" + index3;
					data3.KillNum = String(30000 + index3);
					TournamentKillData.push(data3);
				}
				UpdateTournamentListData(TournamentKillData);
			}
			else if(4 == index)
			{
				var TournamentPKData:Array = new Array();
				for(var index4:int = 0; index4 < 13; ++index4)
				{
					var data4:TournamentPKItemListData = new TournamentPKItemListData;
					data4.Id = index4;
					data4.OnLine = false;
					data4.RankIndex = index4.toString();
					data4.RoleName = "饿狼传说";
					data4.Job = "2/1";
					data4.GuildName = "无敌" + index4;
					data4.Level = "20000" + index4;
					data4.PKValue = String(30000 + index4);
					TournamentPKData.push(data4);
				}
				UpdateTournamentListData(TournamentPKData);
			}
			
		}*/
		
		public function UpdateTournamentListData( data:Array ):void
		{
			for(var i:int = 0; i < Container.length; i++)
			{
				Container[i].UpdateTournamentListData(data);
			}
		}
		
		/*public function UpdateTeamListData( data:Array ):void
		{
			if(null != data && Team_list_mc != null)
			{
				Team_list_mc.dataProvider = new DataProvider(data);
				Team_list_mc.validateNow();
				Team_list_mc.invalidateData();
			}
			else
				trace("TeamContent->UpdateJobData failed!");
		}
		
		function OnTeamListItemClick(e:ListEvent):void
		{
			var listItem:ListItem_Team = e.itemRenderer as ListItem_Team;
			if(null != listItem)
				ExternalInterface.call( "ASTeamItemListClick", listItem.teamData.Id);
		}*/
		
		public function LoadTournamentMenuData( data:Array ):void
		{
			if(null != data && TeamMenu_list_mc != null)
			{
				TeamMenu_list_mc.dataProvider = new TreeDataProvider(data);
				TeamMenu_list_mc.validateNow();
				TeamMenu_list_mc.invalidateData();
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
					Provider.handleListItemClick( e );
					ItemData = Provider.requestItemAt(e.index) as TreeListData;

					if( ItemData.type == SUBNODE )
					{
						ExternalInterface.call( "ASTournamentTreeItemClick", ItemData.index );
					}
					else
					{
						targetList.invalidateData();
					}

				}
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
			
		}
		
	}
	
}
