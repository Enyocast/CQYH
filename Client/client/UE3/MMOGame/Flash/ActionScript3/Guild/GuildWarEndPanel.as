//
// 家族查找
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	
	import ActionScript3.MyPanel;

	public class GuildWarEndPanel extends MyPanel
	{
		public var guild_war_end_list_mc:ScrollingList;
		public var guild_war_end_close_mc:Button;
		public var guild_war_end_time_tf:TextField;
		public var tabTitle:MovieClip;
		override protected function configUI():void
		{
			super.configUI();

			guild_war_end_list_mc.selectedIndex = 0;
			guild_war_end_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			guild_war_end_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			guild_war_end_list_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, onListItemRollOver, false, 0, true);
			guild_war_end_list_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, onListItemRollOut, false, 0, true);
			
			guild_war_end_close_mc.addEventListener(MouseEvent.CLICK, onBtClickClose);
		}
		
		public function onBtClickClose()
		{
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		public function onListItemChange( event:ListEvent ):void
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
		}
		
		public function onListItemRollOver(event:ListEvent ):void
		{
		}

		public function onListItemRollOut(event:ListEvent ):void
		{
		}
		
		public function UCUpdateGuildWarEndList(dat:Array):void
		{
			guild_war_end_list_mc.dataProvider = new DataProvider(dat);
			guild_war_end_list_mc.validateNow();
			guild_war_end_list_mc.invalidateData();
		}
		
		public function UCUpdateGuildWarEndTime(time:String)
		{
			guild_war_end_time_tf.text = time;
		}
		
		private function testData():Array
		{
			var obj:Object;
			var arr:Array=[];
			var i:int=0;
			for(i=0;i<20;i++){
				obj={};
				obj.member_name="金戒指"+i;
				obj.member_level=i;
				obj.member_job="法师";
				obj.member_kill_count=i;
				obj.member_dead_times=i;
				obj.member_achieve=i;
				arr.push(obj);
			}
           return arr;
		}
	}
}


























