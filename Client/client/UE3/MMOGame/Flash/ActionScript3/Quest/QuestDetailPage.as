package ActionScript3.Quest
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	
	import ActionScript3.MyScrollPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.SliderEvent;
	import scaleform.gfx.TextEventEx;
	import scaleform.gfx.TextFieldEx;

	public class QuestDetailPage extends MyScrollPanel
	{
		public var _traceScrollbar:ScrollBar;
		public var _mouse_wheel_layer:MovieClip;
		
		public var quest_title_tf:TextField
		public var quest_desc_caption_mc:MovieClip;
		public var quest_desc_tf:TextField;
		public var quest_circle_tf:TextField;
		
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
		public var quest_award_select_caption_tf:TextField;
		public var quest_award_select_list_mc:QuestAwardList;
		public var quest_award_other_mc:MovieClip;
		public var quest_urgent_tf:TextField;
		public var quest_urgent_num:TextField;
		public static const quest_target_max_count = 8;
		public static const quest_award_max_count = 4;
		public static const quest_award_select_max_count = 4;
		
		public var quest_award_icon_list:Array;
		public var quest_award_select_icon_list:Array;
		
		override protected function configUI():void
		{
			super.configUI();

			_mouse_wheel_layer.addEventListener(MouseEvent.MOUSE_WHEEL, onWheel);
			
			quest_desc_tf.wordWrap = true;
			quest_desc_tf.autoSize = flash.text.TextFieldAutoSize.LEFT;
			quest_desc_tf.styleSheet = new StyleSheet;
			quest_desc_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			quest_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);

			quest_submit_tf.wordWrap = true;
			quest_submit_tf.autoSize = flash.text.TextFieldAutoSize.LEFT;
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
			quest_award_select_icon_list = new Array;

			for (i = 0; i < quest_award_max_count; i ++)
			{
				var award_icon:MyItemSlot = quest_award_list_mc.getChildByName("award_icon" + i) as MyItemSlot;
				if (award_icon)
				{
					quest_award_icon_list.push(award_icon);
				}
			}
			
			for (i = 0; i < quest_award_select_max_count; i ++)
			{
				var select_award_icon:MyItemSlot = quest_award_select_list_mc.getChildByName("award_icon" + i) as MyItemSlot;
				if (select_award_icon)
				{
					quest_award_select_icon_list.push(select_award_icon);
				}
			}

			updateQuestDetailLayout();
		}
		
		private function onWheel(e:MouseEvent):void
		{
			this._traceScrollbar.position -= e.delta * 4;
		}

		private function onScrollChange(evt:SliderEvent):void
		{
			var percent:Number = evt.value;
			y =  -  this["quest_title_tf"].height - percent + 100;
		}

		private function onLinkOverCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		private function onLinkOutCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		private function onLinkCallBack(e:TextEvent):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		public function setupScrollBar(scrollBar:ScrollBar):void
		{
			_traceScrollbar = scrollBar;
			if (_traceScrollbar)
			{
				_traceScrollbar.position = 0;
			}
		}
		
		override public function clear():void
		{//切换标签页的时候清空上一个
			quest_title_tf.htmlText="";
			quest_desc_caption_mc.visible=false;
			quest_desc_tf.htmlText = "";
			quest_circle_tf.visible = false;
			quest_circle_tf.text = "";
			quest_target_caption_mc.visible = false;
			quest_submit_caption_mc.visible = false;
			quest_submit_tf.htmlText = "";
			quest_award_caption_mc.visible = false;
			quest_award_list_mc.visible = false;
			quest_award_select_caption_tf.visible = false;
			quest_award_select_list_mc.visible = false;
			quest_award_other_mc.visible=false;
		}

		public function updateQuestDetailData(detail_data:QuestDetailData):void
		{
			// 任务标题
			quest_title_tf.htmlText = detail_data.quest_caption;
			
			// 任务描述
			quest_desc_caption_mc.visible=true;
			var title_tf:TextField = quest_desc_caption_mc.getChildByName("textField") as TextField;
			title_tf.htmlText = detail_data.quest_desc_caption;
			
			quest_desc_tf.htmlText = detail_data.quest_desc;

			// 环任务描述
			quest_circle_tf.visible = false;
			quest_circle_tf.text = "";
			if (detail_data.quest_circle != "")
			{
				quest_circle_tf.visible = true;
				quest_circle_tf.text = detail_data.quest_circle;
			}
			
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
					//quest_target_caption_mc.visible = detail_data.quest_conditions.length > 0;
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
			quest_submit_caption_mc.visible = false;
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
			quest_award_select_caption_tf.visible = false;
			quest_award_select_list_mc.visible = false;
				
				
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
							award_icon.SetSlotType(19);
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

			if (detail_data.quest_award_select)
			{
				quest_award_select_caption_tf.visible = detail_data.quest_award_select.length > 0;
				quest_award_select_caption_tf.htmlText = detail_data.quest_award_select_caption;
				
				quest_award_select_list_mc.visible = detail_data.quest_award_select.length > 0;
				for (i = 0; i < detail_data.quest_award_select.length; ++ i)
				{
					var award_select_data:QuestAwardIconData = detail_data.quest_award_select[i] as QuestAwardIconData;
					award_icon = quest_award_select_icon_list[i] as MyItemSlot;
					if (award_select_data.icon_img_name == "")
					{
						award_icon.visible = false;
					}
					else
					{
						award_icon.visible = true;
						award_icon.SetSlotType(19);
						award_icon.SetData(1, award_select_data.icon_img_name, award_select_data.item_template_id, "", 0, -1, -1);
					}
				}
			
				for (; i < quest_award_select_max_count; ++ i)
				{
					award_icon = quest_award_select_icon_list[i] as MyItemSlot;
					award_icon.visible = false;
				}
			}
			quest_award_other_mc.visible=true;
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
			quest_urgent_tf.visible=detail_data.quest_is_urgent;
			quest_urgent_num.visible=detail_data.quest_is_urgent;
			if(detail_data.quest_is_urgent==true)
			  quest_urgent_num.text=detail_data.quest_urgent;
			//maxScrollV = 0;
			updateQuestDetailLayout();
		}

		private function updateQuestDetailLayout():void
		{
			var title_heigh = 29;
			var section_spacing = 10;

			// 任务标题
			var next_pos:int = quest_title_tf.y + quest_title_tf.height + section_spacing;
			next_pos += section_spacing * 2;

			// 任务描述
			quest_desc_caption_mc.y = next_pos;
			quest_desc_tf.y = quest_desc_caption_mc.y + title_heigh;
			next_pos = quest_desc_tf.y + quest_desc_tf.height;

			// 环任务描述
			if (quest_circle_tf.visible)
			{
				quest_circle_tf.y = next_pos;
				next_pos = quest_circle_tf.y + quest_circle_tf.height;
				//next_pos += section_spacing * 2;
			}

			for (var i:int = 0; i < quest_target_max_count; ++i)
			{
				var target_mc:MovieClip = this.getChildByName("quest_target_" + i + "_mc") as MovieClip;
				if (target_mc.visible)
				{
					target_mc.y = next_pos;
					next_pos = target_mc.y + target_mc.height;
				}
			}
			//next_pos += section_spacing * 2;

			// 任务交付
			//quest_submit_caption_mc.y = next_pos + section_spacing;
			//next_pos = quest_submit_caption_mc.y + title_heigh;

			quest_submit_tf.y = next_pos;
			next_pos = quest_submit_tf.y + quest_submit_tf.textHeight;

			next_pos += section_spacing * 2;

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

			// 可选任务奖励
			if (quest_award_select_caption_tf.visible)
			{
				quest_award_select_caption_tf.y = next_pos;
				quest_award_select_list_mc.y = quest_award_select_caption_tf.y + quest_award_select_caption_tf.height;
				next_pos = quest_award_select_list_mc.y + quest_award_select_list_mc.height;
				next_pos += section_spacing;
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
			if(quest_award_other_mc.visible)
			{
				this.height = next_pos + quest_award_other_mc.height+4;
			}
			else
			{
				this.height = next_pos +4;
			}
			if(this.quest_urgent_tf.visible)
			{
				if(this.height>380)
				{
					this.quest_urgent_tf.y=this.quest_urgent_num.y=this.height;
					this.height+=this.quest_urgent_tf.height+4;
				}
				else{
					this.quest_urgent_tf.y=this.quest_urgent_num.y=380-this.quest_urgent_tf.height-5;
				}
			}
           (this.parent.getChildByName("_scrollingView") as ScrollingView).displayMc= this.parent.getChildByName("quest_detail_mc");
			
		}
	}
}