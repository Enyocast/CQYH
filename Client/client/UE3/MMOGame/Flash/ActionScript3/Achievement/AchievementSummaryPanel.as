package ActionScript3.Achievement
{
	import flash.display.ActionScriptVersion;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.StaticText;
	import flash.text.TextField;
	
	import ActionScript3.Achievement.AchievementProgressBar;
	import ActionScript3.Achievement.AchievementSummaryIcon;
	
	import flashx.textLayout.formats.Float;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;

	public class AchievementSummaryPanel extends UIComponent
	{
		public var achievement_sum_total_progress_bar_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_0_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_1_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_2_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_3_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_4_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_5_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_6_mc:AchievementProgressBar;
		public var achievement_sum_detail_progress_bar_7_mc:AchievementProgressBar;

		public var achievement_sum_detail_data:Array;
		
		public var achievement_sum_recent_title_tf:TextField;
		
		private static const NUMBER_OF_RECENT_ICON:int = 6;
		public var achievement_sum_recent_icon_0_mc:AchievementSummaryIcon;
		public var achievement_sum_recent_icon_1_mc:AchievementSummaryIcon;
		public var achievement_sum_recent_icon_2_mc:AchievementSummaryIcon;
		public var achievement_sum_recent_icon_3_mc:AchievementSummaryIcon;
		public var achievement_sum_recent_icon_4_mc:AchievementSummaryIcon;
		public var achievement_sum_recent_icon_5_mc:AchievementSummaryIcon;
		public var achievement_sum_recent_null_mc:MovieClip;
		

		public function AchievementSummaryPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			//trace(">>>>>>>>>>>>>>> AchievementSummaryPanel::configUI");
			super.configUI();
			
			achievement_sum_detail_progress_bar_0_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_1_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_2_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_3_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_4_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_5_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_6_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			achievement_sum_detail_progress_bar_7_mc.addEventListener(MouseEvent.CLICK, onBtClickDetailProgress);
			
			// 暂时隐藏
			achievement_sum_detail_progress_bar_6_mc.visible = false;
			achievement_sum_detail_progress_bar_7_mc.visible = false;

			for (var i:int = 0; i < NUMBER_OF_RECENT_ICON; i ++)
			{
				var recent_mc:AchievementSummaryIcon = getChildByName("achievement_sum_recent_icon_" + String(i) + "_mc") as AchievementSummaryIcon;
				if(recent_mc != null){
					recent_mc.addEventListener(MouseEvent.CLICK, onBtClickRecentIcon);
					recent_mc.setIconCaption("");
					recent_mc.setIconDate("")
				}
			}
			
			//trace("<<<<<<<<<<<<<<< AchievementSummaryPanel::configUI");
		}

		public function onBtClickDetailProgress(event:Event)
		{
			if(achievement_sum_detail_data == null)
			{
				return;
			}
			var control:Button = event.target as Button;
			if (control != null)
			{
				var progress_bar:AchievementProgressBar = control as AchievementProgressBar;
				if (progress_bar != null)
				{
					switch (progress_bar)
					{
						case achievement_sum_detail_progress_bar_0_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[0].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_1_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[1].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_2_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[2].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_3_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[3].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_4_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[4].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_5_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[5].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_6_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[6].summary_base_class, 1);
							break;
						case achievement_sum_detail_progress_bar_7_mc :
							ExternalInterface.call("ASShowAchievementListByClass", achievement_sum_detail_data[7].summary_base_class, 1);
							break;
					}
				}
			}
		}

		public function onBtClickRecentIcon(event:Event)
		{
			var control:Button = event.target as Button;
			if (control != null)
			{
				var recent_mc:AchievementSummaryIcon = control as AchievementSummaryIcon;
				if (recent_mc != null)
				{
					ExternalInterface.call("ASShowAchievementListById", recent_mc.user_data);
				}
				
				//test
				//(parent as AchievementPanel).testUpdateListItemPanelData();
			}
		}

		public function setTotal(cur:int, max:int)
		{
			achievement_sum_total_progress_bar_mc.setScore(cur, max);
			var percent:Number = cur / max;
			achievement_sum_total_progress_bar_mc.setProgressPercent(percent);
		}

		public function setDetail(detail_data:Array)
		{
			for (var i:int = 0; i < 8; i ++)
			{
				var progress_mc:AchievementProgressBar = getChildByName("achievement_sum_detail_progress_bar_" + String(i) + "_mc") as AchievementProgressBar;
				if(progress_mc != null){
					progress_mc.setTitle("");
					progress_mc.setScore(0, 0);
					progress_mc.setProgressPercent(0);
					progress_mc.visible = false;
				}
			}

			for (i = 0; i < detail_data.length; i ++)
			{
				progress_mc = getChildByName("achievement_sum_detail_progress_bar_" + String(i) + "_mc") as AchievementProgressBar;
				if(progress_mc != null){
					progress_mc.setTitle(String(detail_data[i].summary_sub_name));
					progress_mc.setScore(detail_data[i].summary_sub_cur, detail_data[i].summary_sub_max);
					var percent:Number = detail_data[i].summary_sub_cur / detail_data[i].summary_sub_max;
					progress_mc.setProgressPercent(percent);
					progress_mc.visible = true;
				}
			}
					
			achievement_sum_detail_data = detail_data;
		}

		public function setRecent(recent_title:String, recent_data:Array)
		{
			achievement_sum_recent_title_tf.text = recent_title;
			
			achievement_sum_recent_icon_0_mc.visible = false;
			achievement_sum_recent_icon_1_mc.visible = false;
			achievement_sum_recent_icon_2_mc.visible = false;
			achievement_sum_recent_icon_3_mc.visible = false;
			achievement_sum_recent_icon_4_mc.visible = false;
			achievement_sum_recent_icon_5_mc.visible = false;
			
			if (recent_data.length > 0)
			{
				achievement_sum_recent_null_mc.visible = false;
				
				for (var i:int = 0; i < recent_data.length; i ++)
				{
					if(i < NUMBER_OF_RECENT_ICON){
						var recent_mc:AchievementSummaryIcon = getChildByName("achievement_sum_recent_icon_" + String(i) + "_mc") as AchievementSummaryIcon;
						if(recent_mc != null){
							recent_mc.setIconCaption(String(recent_data[i].summary_recent_name));
							recent_mc.setIconDate(String(recent_data[i].summary_recent_date))
							recent_mc.setIconImage(String(recent_data[i].summary_recent_icon));
							recent_mc.user_data = int(recent_data[i].summary_recent_id);
							recent_mc.visible = true;
						}
					}
				}
			}
			else
			{
				achievement_sum_recent_null_mc.visible = true;
			}
		}
	}
}