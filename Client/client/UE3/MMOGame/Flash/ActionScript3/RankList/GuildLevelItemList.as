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
	
	public class GuildLevelItemList extends BaseGuildItemList 
	{
		public var LevelData:GuildLevelItemListData;

		override protected function configUI():void
		{
			super.configUI();
			level_txt_mc.textColor = 0xffd100;
			setUpdateDataCallBack(UpdateData);
		}
		
		protected function UpdateData(dat:Object):void
		{
			LevelData = dat as GuildLevelItemListData;
			if(null != LevelData)
			{
				this.UpdateBaseData(LevelData);
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
