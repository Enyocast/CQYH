package ActionScript3.RankList {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	
	
	public class ActiveTGItemList extends ListItemTreeRenderer {
		
		public var mc_rankIndex:MovieClip;
		public var rank_ranking_mc:MovieClip;
		public var txt_rankIndex:TextField;
		public var txt_roleName:TextField;
		public var txt_job:TextField;
		public var txt_layer:TextField;
		public var txt_num:TextField;
		public var RoleID:int;
		public var obj:ActiveTGItemData;
		
		override protected function configUI():void
		{
			super.configUI();
			if(txt_num)
			{
				txt_num.textColor = 0xf7d53b;
			}
			setUpdateDataCallBack(UpdateBaseData);
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
			if(dat)
			{
				this.visible = true;
			    RoleID=dat.Id;
			    txt_roleName.text = dat.RoleName;
			    txt_job.text = dat.Job;
			    txt_layer.text = dat.Layer;
				txt_num.text= GetTime (dat.TextTimer);
			    UpdateRanking(dat.Ranking);
			    UpdateUiloader(dat.RankIndex);
			    UpdateMyTxt(dat.IsPlayer);
			}
			else
			{
				this.visible=false;
			}
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
				txt_layer.textColor=0xffffff;
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
				txt_layer.textColor=0x3dcfff;
				if(txt_num)
				{
					txt_num.textColor=0x3dcfff;
				}
			}
		}
		
		public function GetTime(t:int):String
		{
			var res:String;
			//var time:int  = t / 1000 ;
			var hour:int = Math.floor(t / 3600 );
			var min:int = Math.floor( (t - hour * 3600 ) / 60 );
			var sec:int = t - hour * 3600 - min * 60;
			
			res = hour + "时" + min + "分" + sec + "秒";
			
			return res;
			
		}
	}
	
}
