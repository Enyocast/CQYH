package ActionScript3.RankList {
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	
	public class BaseRankItemList extends ListItemTreeRenderer {

        public var mc_rankIndex:MovieClip;
		public var rank_ranking_mc:MovieClip;
		public var txt_rankIndex:TextField;
		public var txt_roleName:TextField;
		public var txt_job:TextField;
		public var txt_guildName:TextField;
		public var txt_num:TextField;
		public var RoleID:int;
		override protected function configUI():void
		{
			super.configUI();
			if(txt_num)
			{
				txt_num.textColor = 0xf7d53b;
			}
			this.addEventListener(MouseEvent.CLICK, OnRightClick);
			visible = false;
			mc_rankIndex.visible = false;
			rank_ranking_mc.visible = false;
		}
		
		protected function OnRightClick(e:MouseEvent):void
		{
			if (1 == (e as MouseEventEx).buttonIdx)
			{
				ExternalInterface.call("ASRightClick1Menu", RoleID);
			}
		}
		
		protected function UpdateBaseData(dat:Object):void
		{
			this.visible = true;
			RoleID=dat.Id;
			txt_roleName.text = dat.RoleName;
			txt_job.text = dat.Job;
			txt_guildName.text = dat.GuildName;
			UpdateRanking(dat.Ranking);
			UpdateUiloader(dat.RankIndex);
			UpdateMyTxt(dat.IsPlayer);
		}
		
		protected function UpdateUiloader(nIndex:String):void
		{//更新排名
			var index:int=int(nIndex);
			if(index>3){
				txt_rankIndex.text=nIndex;
				txt_rankIndex.visible = true;
				mc_rankIndex.visible = false;
			}else{
				txt_rankIndex.text="";
				txt_rankIndex.visible = false;
				mc_rankIndex.visible = true;
				mc_rankIndex.gotoAndStop(index);
			}
		}
		
		protected function UpdateRanking(nRanking:int):void
		{//更新升降级
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
		
		protected function UpdateMyTxt(isRole:Boolean=false):void
		{
			if(isRole==false)
			{
				txt_rankIndex.textColor=0xffffff;
				txt_roleName.textColor=0xffffff;
				txt_job.textColor=0xffffff;
				txt_guildName.textColor=0xffffff;
				if(txt_num)
				{
					txt_num.textColor=0xf7d53b;
				}
			}
			else
			{
				txt_rankIndex.textColor=0x3dcfff;
				txt_roleName.textColor=0x3dcfff;
				txt_job.textColor=0x3dcfff;
				txt_guildName.textColor=0x3dcfff;
				if(txt_num)
				{
					txt_num.textColor=0x3dcfff;
				}
			}
		}
	}
	
}
