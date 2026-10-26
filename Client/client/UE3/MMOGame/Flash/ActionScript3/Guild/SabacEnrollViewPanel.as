//
// 家族查看
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;

	import ActionScript3.MyPanel;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.Utils.Page;
	import ActionScript3.Common.Events.ParamEvent;

	public class SabacEnrollViewPanel extends MyPanel
	{
		public var guild_sabac_list_mc:ScrollingList;
		public var tabTitle:MovieClip;
		
		public var guild_view_page_mc:CustomPage;
		public var tf_dec:TextField;
		public var _pages:Page;
		public static const MAX_COUNT = 12;

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			_pages=new Page(MAX_COUNT);
			guild_view_page_mc.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			
			//guild_view_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			//guild_view_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);

			tabTitle.txt_sort0.text="攻城时间";
			tabTitle.txt_sort1.text="公会名称";
			UCUpdateSabacEnrollList([],1);
			//testData();
		}
		
		private function pageHandler(e:ParamEvent):void
		{
			var p:int=e.param as int;
			updateData(p);
		}
		
/*		public function testData():void
		{
			var arr:Array=[];
			var i:int=0;
			for(i=0;i<3;i++)
			{
				var obj:Object={};
				obj.guild_name="公会名"+i;
				obj.guild_start_time="2010年2月5日";
				obj.guild_level=i;
				obj.guild_member_count=i;
				obj.guild_leader_name="玩家名"+i;
				obj.guild_create_time="2010年2月5日";
				arr.push(obj);
			}
			UCUpdateSabacEnrollList(arr,1);
		}*/

/*		public function onListItemChange( event:Event ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onListItemClick(event:ListEvent):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}*/
		
		public function UCUpdateDec(dat:String):void
		{
			tf_dec.htmlText=dat;
		}
		
		public function UCUpdateSabacEnrollList(dat:Array, page_index:int):void
		{
			this._pages.datas=dat;
			updateData(1);
		}
		
		private function updateData(p:int):void
		{
			var arr:Array=this._pages.getPageData(p);
			guild_sabac_list_mc.dataProvider = new DataProvider(arr);
			guild_sabac_list_mc.validateNow();
			guild_sabac_list_mc.invalidateData();
			guild_view_page_mc.maximum=this._pages.getTotalPages();
			if(guild_view_page_mc.maximum<1)
			{
				guild_view_page_mc.maximum=1;
			}
			guild_view_page_mc.value=p;
		}
		
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
	}
}


























