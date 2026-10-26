package ActionScript3.Quest
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import fl.motion.easing.Back;
	import scaleform.clik.core.CLIK;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;

	public class QuestRewardListItem extends ListItemTreeRenderer
	{
		public var quest_data:QuestData;
		public var quest_title_tf:TextField;
		public var quest_stars_mc:MovieClip;
		public var quest_accept_bt_mc:MovieClip;
		public var quest_abandon_bt_mc:MovieClip;
		public var quest_status_mc:MovieClip;
		
		public static const quest_stars_max_count = 5;

		public function QuestRewardListItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			quest_accept_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickAccept);
			quest_abandon_bt_mc.addEventListener(MouseEvent.CLICK, onBtClickAbandon);
			
			// 这里一定要注意设置回调处理函数;
			setUpdateDataCallBack(updateData);
		}
		
		public function updateData(data:Object):void
		{
			quest_data = data as QuestData;
			if (quest_data)
			{
				visible = true;
				
				quest_accept_bt_mc.visible = false;
				quest_abandon_bt_mc.visible = false;
				quest_title_tf.htmlText = quest_data.quest_caption;
				quest_status_mc.visible = false;
				
				var i:int = 0;
				for (i = 0; i < quest_stars_max_count; ++ i)
				{
					var star_mc:MovieClip = quest_stars_mc.getChildByName("quest_star_" + i + "_mc") as MovieClip;
					star_mc.visible = i < quest_data.quest_stars;
				}
				
				if (quest_data.quest_is_available)
				{
					quest_accept_bt_mc.visible = true;
					quest_abandon_bt_mc.visible = false;
					
					quest_status_mc.visible = true;
					quest_status_mc.gotoAndPlay("available");
				}
				else if (quest_data.quest_is_accepted)
				{
					quest_accept_bt_mc.visible = false;
					quest_abandon_bt_mc.visible = true;
					
					quest_status_mc.visible = true;
					quest_status_mc.gotoAndPlay("accepted");
				}
				else if (quest_data.quest_is_compassable)
				{
					quest_accept_bt_mc.visible = false;
					quest_abandon_bt_mc.visible = true;
					
					quest_status_mc.visible = true;
					quest_status_mc.gotoAndPlay("compassable");
				}
				else if (quest_data.quest_is_completed)
				{
					quest_accept_bt_mc.visible = false;
					quest_abandon_bt_mc.visible = false;
					
					quest_status_mc.visible = true;
					quest_status_mc.gotoAndPlay("finished");
				}
			}
			else
			{
				visible = false;
			}
		}
		
		public function onBtClickAccept():void
		{
			if (quest_data)
			{
				if (quest_data.quest_id > 0)
				{
					ExternalInterface.call("ASAcceptRewardQuest", quest_data.quest_id);
				}
			}
		}
		
		public function onBtClickAbandon():void
		{
			if (quest_data)
			{
				if (quest_data.quest_id > 0)
				{
					ExternalInterface.call("ASAbandonRewardQuest", quest_data.quest_id);
				}
			}
		}
	}
}