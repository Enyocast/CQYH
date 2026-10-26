package ActionScript3.RankList {
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	
	public class BaseGuildItemList extends ListItemTreeRenderer {
        
		public var GuildID:int;
		public var rankindex_txt_mc:TextField;
		public var guildname_txt_mc:TextField;
		public var num_txt_mc:TextField;
		public var guildername_txt_mc:TextField;
		public var level_txt_mc:TextField;
		
		public var rank_icon1_mc:MovieClip;
		public var rank_ranking_mc:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
			this.visible = false;
			this.addEventListener(MouseEvent.CLICK, OnRightClick);
			rank_icon1_mc.visible = false;
		}
		
		protected function OnRightClick(e:MouseEvent):void
		{
			if (1 == (e as MouseEventEx).buttonIdx)
			{
				ExternalInterface.call("ASRightClick2Menu", GuildID);
			}
		}
		
		protected function UpdateBaseData(dat:Object):void
		{
			this.visible = true;
			GuildID=dat.Id;
			rankindex_txt_mc.text = dat.RankIndex;
			guildname_txt_mc.text = dat.GuildName;
			num_txt_mc.text = dat.Num;
			guildername_txt_mc.text = dat.GuilderName;
			level_txt_mc.text = dat.Level;
			UpdateUiloader(int(dat.RankIndex));
			UpdateRanking(dat.Ranking);
		}
		
		private function UpdateUiloader(nIndex:int):void
		{
			if(nIndex>3){
				rankindex_txt_mc.visible = true;
				rank_icon1_mc.visible = false;
			}else{
				rankindex_txt_mc.visible = false;
				rank_icon1_mc.visible = true;
				rank_icon1_mc.gotoAndStop(nIndex);
			}
		}
		
		private function UpdateRanking(nRanking:int):void
		{
			if(nRanking == 0)
			{
				rank_ranking_mc.visible = false;
			}
			else
			{
				rank_ranking_mc.gotoAndStop(nRanking);
				rank_ranking_mc.visible = true;
			}
		}

	}
	
}
