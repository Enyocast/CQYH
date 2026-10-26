package UI_BattleSummary.BattleSummaryAS3
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;

	//import scaleform.clik.controls.TreeScrollingList;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import ActionScript3.NumUi;

	//import ActionScript3.TreeListData;
	
	public class BtlScoreListPanel extends UIComponent
	{
		//分数列表
		public var ScoreList_mc:ScrollingList;
		//public var ScoreList_mc:TreeScrollingList;
		
		//public var ColTitle_tf7:TextField;
		//public var ColTitle_tf8:TextField;
		
		override protected function configUI():void
		{
			//trace("------BtlScoreListPanel  super.configUI:", TeamScore_mc.teamNum_mc1, TeamScore_mc.teamNum_mc2);
			super.configUI();
			
			updateScoreList( null );
			/*
			//test
			var itemsData:Array = new Array();
			var idx:int = 0;
			for (var i:int = 1; i <= 20; i++)
			{
				if( i == 1 || i == 11 ){
					
					trace( "add scoreItemTitleData"+idx );
					var scoreItemTitleData:BtlScoreListTitleData = new BtlScoreListTitleData ;
					scoreItemTitleData.index = idx;
					scoreItemTitleData.type = 2;
					scoreItemTitleData.deepth = 0;
					scoreItemTitleData.visible = true;
				
					scoreItemTitleData.WinTeamID = -1;
					scoreItemTitleData.IsMyTeam = (i==1);
					scoreItemTitleData.TeamID = int(i-1);
					scoreItemTitleData.TeamName = "队伍"+i;
					itemsData.push(scoreItemTitleData);
					++idx;
					
					
				}
				trace( "add scoreItemData"+idx );
				var scoreItemData:BtlScoreListItemData = new BtlScoreListItemData ;
				scoreItemData.index = idx;
				scoreItemData.type = 0;
				scoreItemData.deepth = 1;
				scoreItemData.visible = true;
				
				scoreItemData.PlayerClassName = ( i%2 ? "warrior" : "mage");
				scoreItemData.PlayerIconIdx = i%2;
				scoreItemData.TeamID = int(i/20);
				scoreItemData.PlayerLv = i;
				scoreItemData.PlayerName = "人员: " + i;
				scoreItemData.Hunted = i*10;
				scoreItemData.BeKilled = i;
				scoreItemData.Damages = i*100;
				scoreItemData.Heals = i*10;
				scoreItemData.BattleScore = i*100;
				scoreItemData.AwardPoints = i*1000;
				
				itemsData.push(scoreItemData);
				++idx;
			}
			updateScoreList(itemsData);
			//test end
			*/
		}
		//
		public function updateScoreList( data:Array ):void
		{
			//trace("======BattleRandomSelect::updateBattlesList" , ScoreList_mc , data);
			
			//ScoreList_mc.dataProvider = new TreeDataProvider(data);
			ScoreList_mc.dataProvider = new DataProvider(data);
			ScoreList_mc.validateNow();
			ScoreList_mc.invalidateData();
		}
	}
}