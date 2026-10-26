package ActionScript3.RankList 
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ComponentEvent;
	import flash.display.MovieClip;
	
	public class Rank extends MyPanel
	{
		public var person_tab_mc:RadioButton;
		public var guild_tab_mc:RadioButton;
		public var active_tab_mc:RadioButton;

		//public var tournament_mc:RankContent_Team;
		public var person_mc:RankContent_Person;
		public var guild_mc:RankContent_Guild;
		public var active_mc:ActiveContent;
		
		public var _listbg:MovieClip;
		public var _norank:MovieClip;
		public var IsShowRank:Boolean=false;//是否显示排名
		//public var power_mc:RankContent_Power;
		
		//public var updateRank_txt_mc:TextField;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			person_mc.visible = true;
			guild_mc.visible = false;
			active_mc.visible=false;
			//tournament_mc.visible = false;
			//power_mc.visible = false;

			ExternalInterface.call("SetTextByID", MyWindowsFrame_mc.tF_windowTitle, "MMOGame.Rank.Title");
			ExternalInterface.call("SetLabelByID", person_tab_mc, "MMOGame.Rank.TabPerson");
			ExternalInterface.call("SetLabelByID", guild_tab_mc, "MMOGame.Rank.TabGuild");
			
			person_tab_mc.addEventListener(MouseEvent.CLICK, OnPersonTabClick);
			guild_tab_mc.addEventListener(MouseEvent.CLICK, OnGuildTabClick);
			active_tab_mc.addEventListener(MouseEvent.CLICK, OnActiveTabClick);
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
			//tournament_tab_mc.addEventListener(MouseEvent.CLICK, OnTournamentTabClick);
			//power_tab_mc.addEventListener(MouseEvent.CLICK, OnPowerTabClick);
			UCShowRank(false);
		}
		
		public function UCShowRank(bl:Boolean):void
		{
			IsShowRank=bl;
			if(bl==false)
			{
				_listbg.visible=false;
				_norank.visible=true;
			}
			else
			{
				_listbg.visible=true;
				_norank.visible=false;
			}
			person_mc.hide(bl);
			guild_mc.hide(bl);
			active_mc.hide(bl);
		}
		
		public function UCOnPersonTabClick():void
		{
			person_mc.visible = true;
			guild_mc.visible = false;
			active_mc.visible=false;
			//tournament_mc.visible = false;
			//power_mc.visible = false;
			person_mc.clear();
			if(IsShowRank==true)
			   ExternalInterface.call("ASPersonTabClick");
		}
		
		private function OnActiveTabClick(evt:MouseEvent):void
		{
			person_mc.visible = false;
			guild_mc.visible = false;
			active_mc.visible=true;
			//tournament_mc.visible = false;
			//power_mc.visible = false;
			active_mc.clear();
			if(IsShowRank==true)
			   ExternalInterface.call("ASActivityTabClick");// 打开活动榜单
		}
		
		private function OnPersonTabClick(evt:MouseEvent):void
		{
			UCOnPersonTabClick();
		}
		
		private function OnGuildTabClick(evt:MouseEvent):void
		{
			person_mc.visible = false;
			guild_mc.visible = true;
			active_mc.visible=false;
			//tournament_mc.visible = false;
			//power_mc.visible = false;
			guild_mc.clear();
			if(IsShowRank==true)
			   ExternalInterface.call("ASGuildTabClick");
		}
		
/*		public function OnTournamentTabClick():void
		{
			person_mc.visible = false;
			guild_mc.visible = false;
			tournament_mc.visible = false;
			power_mc.visible = true;
			ExternalInterface.call("ASTournamentTabClick");
		}
		
		public function OnPowerTabClick():void
		{
			person_mc.visible = false;
			guild_mc.visible = false;
			tournament_mc.visible = false;
			power_mc.visible = true;
			power_mc.UpdateCategory();
			ExternalInterface.call("ASPowerTabClick");
		}*/
		
		public function UCLoadPersonMenuData( data:Array)
		{
			person_mc.LoadPersonMenuData(data);
		}
		
		public function UCLoadGuildMenuData( data:Array)
		{
			guild_mc.LoadGuildMenuData(data);
		}
		
		public function UCLoadTournamentMenuData( data:Array)
		{
			//tournament_mc.LoadTournamentMenuData(data);
		}
		public function UCLoadPowerMenuData( data:Array)
		{
			//power_mc.LoadPowerMenuData(data);
		}
		
		public function UCLoadActiveMenuData( data:Array)
		{
			active_mc.LoadActiveMenuData(data);
		}
		
		public function UCUpdatePersonListData( data:Array ):void
		{
			person_mc.UpdatePersonListData(data);
		}
		
		public function UCUpdateGuildListData( data:Array ):void
		{
			guild_mc.UpdateGuildListData(data);
		}
		
		public function UCUpdateTournamentListData( data:Array ):void
		{
			//tournament_mc.UpdateTournamentListData(data);
		}
		public function UCUpdatePowerListData( data:Array ):void
		{
			//power_mc.UpdatePowerListData(data);
		}
		public function UCUpdateActiveListData( data:Array ):void
		{
			active_mc.UpdateActiveListData(data);
		}
		
		public function UCSetRankPageButton(data:Object):void
		{
			if(person_mc.visible)
				person_mc.UpdatePage(data);
			else if(guild_mc.visible)
				guild_mc.UpdatePage(data);
			else if(active_mc.visible)
				active_mc.UpdatePage(data);
/*			else if(tournament_mc.visible)
				tournament_mc.UpdatePage(data);
			else if(power_mc.visible)
				power_mc.UpdatePage(data);*/
		}
		
		public function UCUpdateMyRank(Rank:String,CurrentRank:int=0,LastRank:int=0):void
		{
			if(person_mc.visible)
				person_mc.UpdateMyRank(Rank,CurrentRank,LastRank);
			else if(guild_mc.visible)
				guild_mc.UpdateMyRank(Rank);
			else if(active_mc.visible)
				active_mc.UpdateMyRank(Rank,CurrentRank,LastRank);
				
/*			else if(tournament_mc.visible)
				tournament_mc.UpdateMyRank(Rank);
			else if(power_mc.visible)
				power_mc.UpdateMyRank(Rank);*/
		}
		
		public function UCUpdateRangeRdoSelect(nIndex:int):void
		{
			if(person_mc.visible)
				person_mc.UpdateRangeRdoSelect(nIndex);
			else if(guild_mc.visible)
				guild_mc.UpdateRangeRdoSelect(nIndex);
			//else if(active_mc.visible)
				//active_mc.UpdateRangeRdoSelect(nIndex);
/*			else if(tournament_mc.visible)
				tournament_mc.UpdateRangeRdoSelect(nIndex);
			else if(power_mc.visible)
				power_mc.UpdateRangeRdoSelect(nIndex);*/
		}
		
		public function UCUpdateTime(timeUpdate:String):void
		{
			//var now:Date = new Date();
			//var year:Number = now.getFullYear();
			//var month:Number = now.getMonth()+1;
			//var day:Number = now.getDate();
			//var hours:Number = now.getHours()+1;
			
			//var time_Text:String = year + "-" + month + "-" + day + " " + hours +":00" + " " +"更新榜单"
			//updateRank_txt_mc.text = timeUpdate;
			
		}
		
		private function hideHandler(evt:Event):void
		{
			person_tab_mc.selected=true;
			person_mc.visible = true;
			guild_mc.visible = false;
			active_mc.visible = false;
			//tournament_mc.visible = false;
			//power_mc.visible = false;
			person_mc.clear();
			guild_mc.clear();
			active_mc.clear();
		}
		
		public function UCUpdateCategoryButton()
		{
			
		}
		
		public function UCUpdateActivityRdo(idx:int):void
		{
			active_mc.setRdo(idx);
		}
		
		public function UCSetMaxLevel(lv:String):void
		{
			person_mc.SetMaxLevel(lv);
		}
	}
	
}
