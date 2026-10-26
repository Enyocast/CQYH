//
// 家族查看
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
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.ItemSlot.MyItemSlot;

	public class GuildWelfarePanel extends MyPanel
	{
		public var guild_welfare_group_0_mc:MovieClip;
		public var guild_welfare_group_1_mc:MovieClip;
		public var guild_welfare_group_2_mc:MovieClip;
		public var guild_welfare_group_3_mc:MovieClip;
		
		public var guild_welfare_condition_tf:TextField;
		public var guild_welfare_left_times_tf:TextField;
		public var guild_welfare_consume_tf:TextField;
		public var guild_welfare_purchase_mc:MovieClip;
		public var guild_welfare_id:int;
		public var guild_welfare_panel_mc:MyWindowsFrame;
		public var guild_welfare_page_mc:MovieClip
		
		var guild_welfare_list:Array;
		
		public static const page_max_group = 4;
		public static const group_max_count = 5;
		
		var guild_select_group:int;
		var guild_select_item:int;
		
		override protected function configUI():void
		{
			super.configUI();
			
			guild_welfare_purchase_mc.addEventListener(MouseEvent.CLICK, onBtClickPurchase);
			
			var i:int = 0;
			for (i = 0; i < page_max_group; ++ i)
			{
				var welfare_group_mc:MovieClip = this.getChildByName("guild_welfare_group_" + i + "_mc") as MovieClip;
				var j:int = 0;
				for (j = 0; j < group_max_count; ++ j)
				{
					var item_mc:GuildWelfareItem = welfare_group_mc.getChildByName("item_" + j + "_mc") as GuildWelfareItem;
					item_mc.addEventListener(MouseEvent.CLICK, onBtClickItem);
					item_mc.addEventListener("rollOver", function _showTips(e:Event){ showTips(e);});
					item_mc.addEventListener("rollOut", onItemRollOut);
					item_mc.select = false;
				}
			}
			guild_select_group = -1;
			guild_select_item = -1;
			
			guild_welfare_condition_tf.text = "";
			guild_welfare_left_times_tf.text = "";
			guild_welfare_consume_tf.htmlText = "";
			
			var page_up_mc:Button = guild_welfare_page_mc.getChildByName("btn_prev") as Button;
			var page_down_mc:Button = guild_welfare_page_mc.getChildByName("btn_next") as Button;
			var page_num_tf:TextField = guild_welfare_page_mc.getChildByName("tF_pageNum") as TextField;
			
			page_up_mc.addEventListener(MouseEvent.CLICK, onBtClickPageUp);
			page_down_mc.addEventListener(MouseEvent.CLICK, onBtClickPageDown);
			page_num_tf.text = String("1");
			
		}
		
		function showTips(e:Event)
		{
			var item_mc:GuildWelfareItem = e.currentTarget as GuildWelfareItem;
			item_mc.showTips();
		}
		
		public function onItemRollOut(e:Event)
		{
			var item_mc:GuildWelfareItem = e.currentTarget as GuildWelfareItem;
			item_mc.hideTips();
		}
		
		public function onBtClickPageUp()
		{
			ExternalInterface.call("ASWelfarePageUp");
		}
		
		public function onBtClickPageDown()
		{
			ExternalInterface.call("ASWelfarePageDown");
		}
		
		public function onBtClickItem(e:Event)
		{
			var i:int = 0;
			for (i = 0; i < page_max_group; ++ i)
			{
				var welfare_group_mc:MovieClip = this.getChildByName("guild_welfare_group_" + i + "_mc") as MovieClip;
				var j:int = 0;
				for (j = 0; j < group_max_count; ++ j)
				{
					var item_mc:GuildWelfareItem = welfare_group_mc.getChildByName("item_" + j + "_mc") as GuildWelfareItem;
					var click_item:MovieClip = e.currentTarget as MovieClip;
	
					if (click_item == item_mc)
					{
						item_mc.select = true;
						guild_select_group = i;
						guild_select_item = j;
						
						updateConditionInfo(i, j);
					}
					else
					{
						item_mc.select = false;
					}
				}
			}
		}
		
		public function updateConditionInfo(group:int, item:int)
		{
			guild_welfare_condition_tf.text = "";
			guild_welfare_left_times_tf.text = "";
			guild_welfare_consume_tf.htmlText = "";
					
			if (guild_welfare_list)
			{
				var welfare_data:Array = guild_welfare_list[group].guild_wel_group as Array;
				if (welfare_data)
				{
					guild_welfare_id = welfare_data[item].guild_wel_id;
					guild_welfare_condition_tf.text = welfare_data[item].guild_wel_level_req;
					guild_welfare_left_times_tf.text = welfare_data[item].guild_wel_left_time;
					guild_welfare_consume_tf.htmlText = welfare_data[item].guild_wel_money_req;
					guild_welfare_purchase_mc.enabled = welfare_data[item].guild_wel_level > 0;
				}
			}
		}
		
		public function onBtClickPurchase()
		{
			ExternalInterface.call("ASPurchaseWelfare" , guild_welfare_id);
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCSetGuildWelfarePage(cur_page:int, max_page:int)
		{
			var i:int = 0;
			for (i = 0; i < page_max_group; ++ i)
			{
				var welfare_group_mc:MovieClip = this.getChildByName("guild_welfare_group_" + i + "_mc") as MovieClip;
				var j:int = 0;
				for (j = 0; j < group_max_count; ++ j)
				{
					var item_mc:GuildWelfareItem = welfare_group_mc.getChildByName("item_" + j + "_mc") as GuildWelfareItem;
					item_mc.select = false;
				}
			}
			guild_select_group = -1;
			guild_select_item = -1;
			
			guild_welfare_condition_tf.text = "";
			guild_welfare_left_times_tf.text = "";
			guild_welfare_consume_tf.htmlText = "";
			
			guild_welfare_purchase_mc.enabled = false;
			
			var page_num_tf:TextField = guild_welfare_page_mc.getChildByName("tF_pageNum") as TextField;
			page_num_tf.text = String(cur_page) + "/" + String(max_page);
			
			var page_bt_pre_mc:MovieClip = guild_welfare_page_mc.getChildByName("btn_prev") as MovieClip;
			var page_bt_next_mc:MovieClip = guild_welfare_page_mc.getChildByName("btn_next") as MovieClip;
			page_bt_pre_mc.enabled = true;
			page_bt_next_mc.enabled = true;
			
			if (cur_page == 1)
			{
				page_bt_pre_mc.enabled = false;
			}
			if (cur_page == max_page)
			{
				page_bt_next_mc.enabled = false;
			}
		}
		
		public function UCUpdateGuildWelfarePurchaseList(data:Array)
		{
			guild_welfare_list = data;
			var i:int = 0;
			for (i = 0; i < page_max_group; ++ i)
			{
				var welfare_data:Array = guild_welfare_list[i].guild_wel_group as Array;
				var welfare_group_mc:MovieClip = this.getChildByName("guild_welfare_group_" + i + "_mc") as MovieClip;
				var j:int = 0;
				for (j = 0; j < group_max_count; ++ j)
				{
					var item_mc:GuildWelfareItem = welfare_group_mc.getChildByName("item_" + j + "_mc") as GuildWelfareItem;
					
					if (j <　welfare_data.length)
					{
						item_mc.visible = true;
						//item_mc.guild_welfare_name_tf.visible = false;
						item_mc.updateItemData(welfare_data[j]);
					}
					else
					{
						item_mc.visible = false;
					}
				}
			}
			
			updateConditionInfo(guild_select_group, guild_select_item);
		}
	}
}


























