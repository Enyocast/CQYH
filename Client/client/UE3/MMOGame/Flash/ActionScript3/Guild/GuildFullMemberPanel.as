//
// 家族信息——正式成员
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
	import ActionScript3.MyTipButton;
	import scaleform.clik.controls.CheckBox;

	public class GuildFullMemberPanel extends UIComponent
	{
		public var guild_info_full_member_list_mc : ScrollingList;

		public var tabTitle:MovieClip;
		public var guild_info_show_online_member_mc:CheckBox;
		public var guild_info_online_member_notify_mc : CheckBox;
		
		public var guild_info_online_member_count_tf : TextField;
		public var guild_info_max_member_count_tf : TextField;
		
		public var guild_info_invite_mc:Button;
		public var guild_info_post_change_mc:Button;
		public var guild_info_expel_mc:Button;
		
		public var guild_invite_panel_mc : GuildInvitePanel;
		public var guild_post_change_panel_mc : GuildPostChangePanel;
		
		public var guild_info_full_member_data : Object;
		private var sort0:Boolean=false;
		private var sort1:Boolean=false;
		private var sort2:Boolean=false;
		private var sort3:Boolean=false;
		
		override protected function configUI():void
		{
			super.configUI();
			var i:int=0;
			for(i;i<4;i++)
			{
				var mc:MovieClip=tabTitle.getChildByName("btn_sort"+i) as MovieClip;
				mc.visible=false;
				var txt:TextField=tabTitle.getChildByName("txt_sort"+i) as TextField;
				txt.addEventListener(MouseEvent.CLICK,clickHandler);
			}
/*			tabTitle.btn_sort1.addEventListener(ButtonEvent.CLICK, onBtClickSortLevel);
			tabTitle.btn_sort2.addEventListener(ButtonEvent.CLICK, onBtClickSortJob);
			tabTitle.btn_sort3.addEventListener(ButtonEvent.CLICK, onBtClickSortPost);
			tabTitle.btn_sort5.addEventListener(ButtonEvent.CLICK, onBtClickSortTime);*/
			guild_info_invite_mc.addEventListener(MouseEvent.CLICK, onBtClickInvite);
			guild_info_post_change_mc.addEventListener(MouseEvent.CLICK, onBtClickPostChange);
			guild_info_expel_mc.addEventListener(MouseEvent.CLICK, onBtClickExpel);
			
			guild_info_show_online_member_mc.selected = false;
			guild_info_online_member_notify_mc.selected = true;
			guild_info_show_online_member_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_info_online_member_notify_mc.addEventListener(ButtonEvent.CLICK, onToggleNotifyClick);
			guild_info_online_member_notify_mc.visible = false;
			
			guild_info_full_member_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			guild_info_full_member_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick, false, 0, true);
			
			guild_invite_panel_mc.visible = false;
			guild_post_change_panel_mc.visible = false;
			updateGuildFullMemberList([]);
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			var txt:TextField=evt.currentTarget as TextField;
			var str:String=txt.name;
			var idx:int=int(str.substring(str.length-1,str.length));
			var mc:MovieClip=tabTitle.getChildByName("btn_sort"+idx) as MovieClip;
			switch(idx)
			{
				case 0:
				{
					sort0=!sort0;
					mc.visible=sort0;
					ExternalInterface.call("ASSortMember", 0, sort0);
					break;
				}
				case 1:
				{
					sort1=!sort1;
					mc.visible=sort1;
					ExternalInterface.call("ASSortMember", 1, sort1);
					break;
				}
				case 2:
				{
					sort2=!sort2;
					mc.visible=sort2;
					ExternalInterface.call("ASSortMember", 2, sort2);
					break;
				}
				case 3:
				{
					sort3=!sort3;
					mc.visible=sort3;
					ExternalInterface.call("ASSortMember", 3, sort3);
					break;
				}
			}
		}
		
		public function onListItemChange( event:Event ):void
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
					guild_info_full_member_data = provider.requestItemAt(event.index);
				}
				list.invalidateData();
			}
		}

/*		private function onBtClickSortLevel(e:ButtonEvent):void
		{
			tabTitle.btn_sort1.selected=!tabTitle.btn_sort1.selected;
			
			if (tabTitle.btn_sort1.selected==false)
			{
				ExternalInterface.call("ASSortMember", 0, false);
			}
			else
			{
				ExternalInterface.call("ASSortMember", 0, true);
			}
		}
		
		private function onBtClickSortJob(e:ButtonEvent):void
		{
			tabTitle.btn_sort2.selected=!tabTitle.btn_sort2.selected;
			if (tabTitle.btn_sort2.selected==false)
			{
				ExternalInterface.call("ASSortMember", 1, false);
			}
			else
			{
				ExternalInterface.call("ASSortMember", 1, true);
			}
		}
		
		private function onBtClickSortPost(e:ButtonEvent):void
		{
			tabTitle.btn_sort3.selected=!tabTitle.btn_sort3.selected;
			if (tabTitle.btn_sort2.selected==false)
			{
				ExternalInterface.call("ASSortMember", 2, false);
			}
			else
			{
				ExternalInterface.call("ASSortMember", 2, true);
			}
		}
		
		private function onBtClickSortTime(e:ButtonEvent):void
		{
            tabTitle.btn_sort5.selected=!tabTitle.btn_sort5.selected;
			if (tabTitle.btn_sort5.selected==false)
			{
				ExternalInterface.call("ASSortMember", 3, false);
			}
			else
			{
				ExternalInterface.call("ASSortMember", 3, true);
			}
		}*/
		
		private function onBtClickInvite(evt:MouseEvent):void
		{
			guild_invite_panel_mc.visible = true;
			guild_invite_panel_mc.show();
		}
		
		private function onBtClickPostChange(evt:MouseEvent):void
		{
			if (guild_info_full_member_data != null)
			{
				guild_post_change_panel_mc.setRoleId(guild_info_full_member_data.member_id);
				guild_post_change_panel_mc.visible = true;
			}
		}
		
		private function onBtClickExpel(evt:MouseEvent):void
		{
			if (guild_info_full_member_data != null)
			{
				ExternalInterface.call("ASExpelMember", guild_info_full_member_data.member_id);
			}
		}
		
		private function onToggleClick(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASShowOnlineMember", guild_info_show_online_member_mc.selected);
		}
		
		private function onToggleNotifyClick(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASOnlineMemberNotify", guild_info_online_member_notify_mc.selected);
		}
		
		public function updateGuildFullMemberList(data:Array):void
		{
			var member_online_count:int = 0;
			for (var i:int = 0; i < data.length; i ++)
			{
				if (data[i].member_online == true)
				{
					member_online_count ++;
				}
			}
			guild_info_online_member_count_tf.text = String(member_online_count) + "/" + String(data.length);
			
			guild_info_full_member_list_mc.dataProvider = new DataProvider(data);
			guild_info_full_member_list_mc.validateNow();
			guild_info_full_member_list_mc.invalidateData();
			if(data.length>0)
			{
				guild_info_full_member_list_mc.selectedIndex=0;
			}
		}
		
		public function updateGuildBaseInfo(data:Object):void
		{
			guild_info_max_member_count_tf.text = String(data.guild_max_member_count);
			guild_info_invite_mc.enabled = data.guild_rights_invite;
			guild_info_post_change_mc.enabled = data.guild_rights_change_pos;
			guild_info_expel_mc.enabled = data.guild_rights_banish;
		}
		
		public function clear():void
		{
			guild_info_show_online_member_mc.selected = false;
		}
	}
}


























