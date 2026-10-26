package ActionScript3.RankList {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	
	
	public class MyRankTxt extends UIComponent {
		
		public var myrank_txt_mc:TextField;
		public var txt_last:TextField;
		public var mc_rank:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
			this.visible=false;
		}
		
		public function updateData(Rank:String,CurrentRank:int,LastRank:int):void
		{
			this.visible=true;
			var gb:int=LastRank-CurrentRank;
			var pl:int=1;
			if(gb>0)
			{
				pl=2;
			}
			if(gb==0 || LastRank==0)
			{
				txt_last.text="";
				pl=3;
			}
			else
			{
				txt_last.text=gb.toString();
			}
			myrank_txt_mc.htmlText=Rank;
			mc_rank.gotoAndStop(pl);
		    
		}
	}
	
}
