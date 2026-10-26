//
// 家族外交信息
//
package ActionScript3.Guild
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;

	public class GuildAllyInfoPanel extends UIComponent
	{
		public var guild_ally_info_list_mc:ScrollingList;
		public var guild_ally_info_data : Object;
		
		public var guild_apply_ally_agree_mc:Button;
		public var guild_apply_ally_refuse_mc:Button;
		public var tabTitle:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
			guild_ally_info_list_mc.selectedIndex = 0;
			guild_ally_info_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			guild_ally_info_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			
			guild_apply_ally_agree_mc.addEventListener(MouseEvent.CLICK, onBtClickAgree);
			guild_apply_ally_refuse_mc.addEventListener(MouseEvent.CLICK, onBtClickRefuse);
			updateGuildApplyAllyList([]);
			//testData();
		}
		
/*		public function testData():void
		{
			var arr:Array=[];
			var i:int=0;
			for(i=0;i<12;i++)
			{
				var obj:Object={};
				obj.guild_id=i;
				obj.guild_name="玩家"+i;
				obj.guild_level=i;
				obj.guild_leader_name="职业"+i;
				obj.guild_member_count="20"+i;
				obj.guild_left_time="2010";
				arr.push(obj);
			}
			updateGuildApplyAllyList(arr);
		}*/
		
		public function onListItemChange( evt:ListEvent ):void
		{
			var list:ScrollingList = evt.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}
		
		public function onListItemClick(evt:ListEvent):void
		{
			var list:ScrollingList = evt.target as ScrollingList;
			if (list != null)
			{
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{
					guild_ally_info_data = provider.requestItemAt(evt.index);
				}
				
				list.invalidateData();
			}
		}

		public function onBtClickAgree(evt:MouseEvent):void
		{
			if (guild_ally_info_data != null)
			{
				trace(guild_ally_info_data.guild_id);
				ExternalInterface.call("ASAgreeAlly", guild_ally_info_data.guild_id);
			}
		}
		
		public function onBtClickRefuse(evt:MouseEvent):void
		{
			if (guild_ally_info_data != null)
			{
				ExternalInterface.call("ASRefuseAlly", guild_ally_info_data.guild_id);
			}
		}
		
		public function updateGuildApplyAllyList(dat:Array):void
		{
			guild_ally_info_list_mc.dataProvider = new DataProvider(dat);
			guild_ally_info_list_mc.validateNow();
			guild_ally_info_list_mc.invalidateData();
			if(dat.length>0)
			{
				guild_ally_info_data=dat[0];
				guild_ally_info_list_mc.selectedIndex = 0;
			}
		}
		
		public function updateGuildBaseInfo(data:Object)
		{
			guild_apply_ally_agree_mc.enabled = data.guild_rights_foreign;
			guild_apply_ally_refuse_mc.enabled = data.guild_rights_foreign;
			
			// 这里有诡异事情: 拒绝按钮无论设置有效还是无效, 表现都是灰态, 这里强制设一下状态
			if (guild_apply_ally_refuse_mc.enabled)
			{
				guild_apply_ally_refuse_mc.gotoAndStop("up");
			}
			else
			{
				guild_apply_ally_refuse_mc.gotoAndStop("disabled");
			}
		}
	}
}


























