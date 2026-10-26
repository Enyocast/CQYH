package UI_GuildTerritoryWidget.AS3 {
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.Utils.Page;
	import ActionScript3.Common.Events.ParamEvent;
	import scaleform.clik.data.DataProvider;
	
	public class GuildTerritoryEnterPanel extends MyPanel {
        
		public var page_mc:CustomPage;
		public var _pages:Page;
		public var list:ScrollingList;
		public var title_mc:MovieClip;
		public static const PAGESIZE = 11;
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("结盟公会");
			_pages=new Page(PAGESIZE);
			page_mc.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
/*			var i:int=0;
			var arr:Array=[];
			for(i;i<13;i++)
			{
				var obj:Object=new Object();
				obj.Id=i;
				obj.guild_name="gongh"+i;
				obj.guild_level=i;
				obj.timer=3600;
				obj.Num=1+i;
				arr.push(obj);
			}
			UCUpdateGuildTerritoryList(arr);*/
		}
		
		private function pageHandler(e:ParamEvent):void
		{
			var p:int=e.param as int;
			update(p);
		}

		public function UCUpdateGuildTerritoryList(dat:Array):void
		{
			this._pages.datas=dat;
			page_mc.maximum=this._pages.getTotalPages();
			update(1);
		}
		
		private function update(p:int):void
		{
		    var arr:Array=this._pages.getPageData(p);
			list.dataProvider=new DataProvider(arr);
			list.validateNow();
			list.invalidateData();
		}
	}
	
}
