package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	import flash.display.MovieClip;
	
	public class TournamentKillItemList extends BaseRankItemList 
	{
		public var obj:TournamentKillItemListData;

		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		protected function UpdateData(dat:Object):void
		{
			obj = dat as TournamentKillItemListData;
			if (obj)
			{
				UpdateBaseData(obj);
				txt_num.text = obj.KillNum;
			}
			else
			{
				visible = false;
			}
		}
		
	}
	
}
