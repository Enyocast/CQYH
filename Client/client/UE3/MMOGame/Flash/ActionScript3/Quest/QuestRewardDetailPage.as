package ActionScript3.Quest
{
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.events.SliderEvent;
	import ActionScript3.MyScrollBar;
	import flash.external.ExternalInterface;
	import ActionScript3.MyScrollPanel;
	import flash.events.TextEvent;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import ActionScript3.ItemSlot.MyItemSlot;

	public class QuestRewardDetailPage extends MyScrollPanel
	{
		public var _traceScrollbar:MyScrollBar;
		public var _mouse_wheel_layer:MovieClip;
		
		public var quest_desc_caption_mc:MovieClip;
		public var quest_desc_tf:TextField;
		
		public var quest_target_caption_mc:MovieClip;
		public var quest_target_0_mc:MovieClip;
		public var quest_target_1_mc:MovieClip;
		public var quest_target_2_mc:MovieClip;
		public var quest_target_3_mc:MovieClip;
		public var quest_target_4_mc:MovieClip;
		public var quest_target_5_mc:MovieClip;
		public var quest_target_6_mc:MovieClip;
		public var quest_target_7_mc:MovieClip;

		public var quest_submit_caption_mc:MovieClip;
		public var quest_submit_tf:TextField;
		
		public var quest_award_caption_mc:MovieClip;
		public var quest_award_list_mc:QuestAwardList;
		public var quest_award_other_mc:MovieClip;
		
		public static const quest_target_max_count = 8;
		public static const quest_award_max_count = 4;
		
		public var quest_award_icon_list:Array;
		
		public function QuestRewardDetailPage()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();

			_mouse_wheel_layer.addEventListener(MouseEvent.MOUSE_WHEEL, onWheel);
			
			quest_desc_tf.styleSheet = new StyleSheet  ;
			quest_desc_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			quest_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);

			quest_submit_tf.styleSheet = new StyleSheet  ;
			quest_submit_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_submit_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			quest_submit_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
		
			var i:int;
			for (i = 0; i < quest_target_max_count; i ++)
			{
				var target_name:String = "quest_target_" + i.toString() + "_mc";
				var target_mc:MovieClip = this.getChildByName(target_name) as MovieClip;
				if (target_mc != null)
				{
					var quest_target_tf:TextField = target_mc.getChildByName("tf_requirement") as TextField;
					
					quest_target_tf.styleSheet = new StyleSheet  ;
					quest_target_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
					quest_target_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
					quest_target_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
				}
			}
			
			quest_award_icon_list = new Array;

			for (i = 0; i < quest_award_max_count; i ++)
			{
				var award_icon:MyItemSlot = quest_award_list_mc.getChildByName("award_icon" + i) as MyItemSlot;
				if (award_icon)
				{
					quest_award_icon_list.push(award_icon);
				}
			}
			
			updateQuestDetailLayout();
		}
		
		function onWheel(e:MouseEvent):void
		{
			this._traceScrollbar.position -= e.delta * 4;
		}

		function onScrollChange(evt:SliderEvent):void
		{
			var percent:Number = evt.value;
			y =  -  this["quest_desc_caption_mc"].height * 1 - percent + 100;
		}

		function onLinkOverCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		public function setupScrollBar(scrollBar:MyScrollBar):void
		{
			_traceScrollbar = scrollBar;
			if (_traceScrollbar)
			{
				_traceScrollbar.scrollTarget = this;
				addEventListener(SliderEvent.VALUE_CHANGE, onScrollChange);
				//_traceScrollbar.height = 450;
				_traceScrollbar.position = 0;
			}
			else
			{
				ExternalInterface.call("ASTrace", "_traceScrollbar is null!");
			}
		}

		public function updateQuestDetailData(detail_data:QuestDetailData):void
		{
			// 任务描述
			var title_tf:TextField = quest_desc_caption_mc.getChildByName("textField") as TextField;
			title_tf.htmlText = detail_data.quest_desc_caption;

			quest_desc_tf.autoSize = flash.text.TextFieldAutoSize.LEFT;
			quest_desc_tf.wordWrap = true;
			quest_desc_tf.htmlText = detail_data.quest_desc;
			quest_desc_tf.height = quest_desc_tf.textHeight;

			// 任务条件/目标
			var i:int = 0;
			var target_mc:MovieClip;
			var target_tf:TextField;
			
			quest_target_caption_mc.visible = false;
			for (i = 0; i < quest_target_max_count; ++ i)
			{
				target_mc = this.getChildByName("quest_target_" + i + "_mc") as MovieClip;
				target_mc.visible = false;
			}

			title_tf = quest_target_caption_mc.getChildByName("textField") as TextField;
			if (detail_data.quest_is_available)
			{
				if (detail_data.quest_conditions)
				{
					quest_target_caption_mc.visible = detail_data.quest_conditions.length > 0;
					title_tf.text = detail_data.quest_conditions_caption;

					for (i = 0; i < detail_data.quest_conditions.length; ++i)
					{
						target_mc = this.getChildByName("quest_target_" + i + "_mc") as MovieClip;
						target_mc.visible = true;
						target_tf = target_mc.getChildByName("tf_requirement") as TextField;
						target_tf.htmlText = detail_data.quest_conditions[i];
					}
				}
			}
			else
			{
				if (detail_data.quest_targets)
				{
					quest_target_caption_mc.visible = detail_data.quest_targets.length > 0;
					title_tf.text = detail_data.quest_targets_caption;

					for (i = 0; i < detail_data.quest_targets.length; ++i)
					{
						target_mc = this.getChildByName("quest_target_" + i + "_mc") as MovieClip;
						target_mc.visible = true;
						target_tf = target_mc.getChildByName("tf_requirement") as TextField;
						target_tf.htmlText = detail_data.quest_targets[i];
					}
				}
			}

			// 任务交付
			title_tf = quest_submit_caption_mc.getChildByName("textField") as TextField;  
			title_tf.autoSize = flash.text.TextFieldAutoSize.LEFT;
			title_tf.wordWrap = true;				
			title_tf.text = detail_data.quest_submit_caption;
			
			quest_submit_tf.htmlText = detail_data.quest_submit;
			quest_submit_tf.height = quest_submit_tf.textHeight;
			
			// 任务奖励
			quest_award_caption_mc.visible = true;
			title_tf = quest_award_caption_mc.getChildByName("textField") as TextField;
			title_tf.htmlText = detail_data.quest_award_caption;
			
			quest_award_list_mc.visible = false;
			
			var award_icon:MyItemSlot;
			if (detail_data.quest_awards)
			{
				quest_award_list_mc.visible = detail_data.quest_awards.length > 0;
				for (i = 0; i < detail_data.quest_awards.length; ++ i)
				{
					if (i < quest_award_max_count)
					{
						var award_data:QuestAwardIconData = detail_data.quest_awards[i] as QuestAwardIconData;
						award_icon = quest_award_icon_list[i] as MyItemSlot;
						if (award_data.icon_img_name == "")
						{
							award_icon.visible = false;
						}
						else
						{
							award_icon.visible = true;
							award_icon.SetSlotType(18);
							award_icon.SetData(1, award_data.icon_img_name, award_data.item_template_id, "", 0, -1, -1);
						}
					}
				}
			
				for (; i < quest_award_max_count; ++ i)
				{
					award_icon = quest_award_icon_list[i] as MyItemSlot;
					award_icon.visible = false;
				}
			}
			
            // 经验
			var exp_title_tf:TextField = quest_award_other_mc.getChildByName("award_exp_title") as TextField;
			exp_title_tf.text = detail_data.quest_award_exp_caption;
			exp_title_tf.width = exp_title_tf.textWidth + 5;
			var exp_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_exp") as TextField;
			exp_tf.text = detail_data.quest_award_exp.toString();
			exp_tf.x = exp_title_tf.x + exp_title_tf.width;
			exp_title_tf.visible = detail_data.quest_award_exp > 0;
			exp_tf.visible = detail_data.quest_award_exp > 0;
			
			// 货币
			var money_title_tf:TextField = quest_award_other_mc.getChildByName("award_money_caption") as TextField;
			money_title_tf.text = detail_data.quest_award_money_caption;
			money_title_tf.width = money_title_tf.textWidth + 5;
			var money_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_gold") as TextField;
			money_tf.htmlText = String(detail_data.quest_award_money);
			money_tf.x = money_title_tf.x + money_title_tf.width;
			money_title_tf.visible = detail_data.quest_award_money != "";
			money_tf.visible = detail_data.quest_award_money != "";
			
			money_title_tf = quest_award_other_mc.getChildByName("award_money_caption_ex") as TextField;
			money_tf = quest_award_other_mc.getChildByName("tf_taskaward_gold_ex") as TextField;
			money_title_tf.text = detail_data.quest_award_money_caption_ex;
			money_title_tf.width = money_title_tf.textWidth + 5;
			money_tf.htmlText = String(detail_data.quest_award_money_ex);
			money_tf.x = money_title_tf.x + money_title_tf.width;
			money_title_tf.visible = detail_data.quest_award_money_ex != "";
			money_tf.visible = detail_data.quest_award_money_ex != "";
			
			// 活跃度
			var act_title_tf:TextField = quest_award_other_mc.getChildByName("award_activity_title") as TextField;
			act_title_tf.text = detail_data.quest_award_activity_caption;
			act_title_tf.width = act_title_tf.textWidth + 5;
			var act_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_activity") as TextField;
			act_tf.text = detail_data.quest_award_activity.toString();
			act_tf.x = act_title_tf.x + act_title_tf.width;
			act_title_tf.visible = detail_data.quest_award_activity > 0;
			act_tf.visible = detail_data.quest_award_activity > 0;
			
			maxScrollV = 0;
			updateQuestDetailLayout();
		}

		function updateQuestDetailLayout():void
		{
			var title_heigh = 29;
			var section_spacing = 10;
			var next_pos:int = 0;
			
			// 任务描述
			quest_desc_caption_mc.y = next_pos+20;
			quest_desc_tf.y = quest_desc_caption_mc.y + title_heigh;
			next_pos = quest_desc_tf.y + quest_desc_tf.height;
			next_pos += section_spacing * 2;

			// 任务目标
			if (quest_target_caption_mc.visible)
			{
				quest_target_caption_mc.y = next_pos;
				next_pos = quest_target_caption_mc.y + title_heigh;

				for (var i:int = 0; i < quest_target_max_count; ++i)
				{
					var target_mc:MovieClip = this.getChildByName("quest_target_" + i + "_mc") as MovieClip;
					if (target_mc.visible)
					{
						target_mc.y = next_pos;
						next_pos = target_mc.y + target_mc.height;
					}
				}
			}
			next_pos += section_spacing * 2;

			// 任务交付
			if(quest_submit_caption_mc.visible)
			{
				quest_submit_caption_mc.y = next_pos + section_spacing;
				next_pos = quest_submit_caption_mc.y + title_heigh;

				quest_submit_tf.y = next_pos;
				next_pos = quest_submit_tf.y + quest_submit_tf.textHeight;

				next_pos += section_spacing * 2;
			}

			// 任务奖励
			quest_award_caption_mc.y = next_pos;
			if (quest_award_list_mc.visible)
			{
				quest_award_list_mc.y = quest_award_caption_mc.y + title_heigh;
				next_pos = quest_award_list_mc.y + quest_award_list_mc.height;
				next_pos += section_spacing;
			}
			else
			{
				next_pos = quest_award_caption_mc.y + title_heigh;
			}

			// 钱，经验，帮贡
			quest_award_other_mc.y = next_pos;
			var sub_pos:int = 0;
			var exp_title_tf:TextField = quest_award_other_mc.getChildByName("award_exp_title") as TextField;
			var exp_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_exp") as TextField;
			if (exp_title_tf.visible)
			{
				exp_title_tf.y = sub_pos;
				exp_tf.y = sub_pos;
				sub_pos = exp_title_tf.y + exp_title_tf.height;
			}
				
			var money_title_tf:TextField = quest_award_other_mc.getChildByName("award_money_caption") as TextField;
			var money_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_gold") as TextField;
			if (money_title_tf.visible)
			{
				money_title_tf.y = sub_pos;
				money_tf.y = sub_pos;
				sub_pos = money_title_tf.y + money_title_tf.height;
			}
			
			var money_ex_title_tf:TextField = quest_award_other_mc.getChildByName("award_money_caption_ex") as TextField;
			var money_ex_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_gold_ex") as TextField;
			if (money_ex_title_tf.visible)
			{
				money_ex_title_tf.y = sub_pos;
				money_ex_tf.y = sub_pos;
				sub_pos = money_ex_title_tf.y + money_ex_title_tf.height;
			}
				
			var act_title_tf:TextField = quest_award_other_mc.getChildByName("award_activity_title") as TextField;
			var act_tf:TextField = quest_award_other_mc.getChildByName("tf_taskaward_activity") as TextField;
			if (act_title_tf.visible > 0)
			{
				act_title_tf.y = sub_pos;
				act_tf.y = sub_pos;
				sub_pos = act_title_tf.y + act_title_tf.height;
			}

			this.height = next_pos + quest_award_other_mc.height;
			this.maxScrollV = (quest_award_other_mc.y + quest_award_other_mc.height) - this.height + 200;
		}
	}
}