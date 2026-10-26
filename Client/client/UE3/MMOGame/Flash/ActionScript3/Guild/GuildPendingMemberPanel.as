//
// 家族信息——待定成员
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


	public class GuildPendingMemberPanel extends UIComponent
	{
		public var guild_info_pending_member_list_mc : ScrollingList;
		
		public var guild_info_invite_mc : MovieClip;
		public var guild_info_agree_mc : MovieClip;
		public var guild_info_refuse_mc : MovieClip;
		
		public var guild_invite_panel_mc : GuildInvitePanel;
		
		public var guild_info_pending_member_data : Object;

		override protected function configUI():void
		{
			super.configUI();

			guild_info_invite_mc.addEventListener(MouseEvent.CLICK, onBtClickInvite);
			guild_info_agree_mc.addEventListener(MouseEvent.CLICK, onBtClickAgree);
			guild_info_refuse_mc.addEventListener(MouseEvent.CLICK, onBtClickRefuse);
			
			guild_info_pending_member_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			guild_info_pending_member_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			
			guild_invite_panel_mc.visible = false;
			updateGuildPendingMemberList([]);
		}
		
/*		public function testData():void
		{
			var arr:Array=[];
			var i:int=0;
			for(i=0;i<12;i++)
			{
				var obj:Object={};
				obj.member_id=i;
				obj.member_name="玩家"+i;
				obj.member_level=i;
				obj.member_job="职业"+i;
				obj.member_time="2010年";
				arr.push(obj);
			}
			updateGuildPendingMemberList(arr);
		}*/
		
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
				var provider:DataProvider = list.dataProvider as DataProvider;
				if (provider!=null)
				{   
					guild_info_pending_member_data = provider.requestItemAt(event.index);
				}
				
				list.invalidateData();
			}
		}
		
		public function onBtClickInvite(evt:MouseEvent):void
		{
			guild_invite_panel_mc.visible = true;
			guild_invite_panel_mc.show();
		}
		
		public function onBtClickAgree(evt:MouseEvent):void
		{
			if (guild_info_pending_member_data != null)
			{
				ExternalInterface.call("ASAgreeToJoin", guild_info_pending_member_data.member_id);
				guild_info_pending_member_data=null;
				guild_info_pending_member_list_mc.selectedIndex=-1;
				
			}
		}
		
		public function onBtClickRefuse(evt:MouseEvent):void
		{
			if (guild_info_pending_member_data != null)
			{
				ExternalInterface.call("ASRefuseToJoin", guild_info_pending_member_data.member_id);
				guild_info_pending_member_data=null;
				guild_info_pending_member_list_mc.selectedIndex=-1;
			}
		}
		
		public function updateGuildPendingMemberList(dat:Array):void
		{
			guild_info_pending_member_list_mc.dataProvider = new DataProvider(dat);
			guild_info_pending_member_list_mc.validateNow();
			guild_info_pending_member_list_mc.invalidateData();
			if(dat.length>0)
			{
				guild_info_pending_member_data=dat[0]
				guild_info_pending_member_list_mc.selectedIndex = 0;
			}
		}
		
		public function updateGuildBaseInfo(data:Object):void
		{
			guild_info_invite_mc.enabled = data.guild_rights_invite;
			guild_info_agree_mc.enabled = data.guild_rights_recruit;
			guild_info_refuse_mc.enabled = data.guild_rights_recruit;
		}
	}
}


























