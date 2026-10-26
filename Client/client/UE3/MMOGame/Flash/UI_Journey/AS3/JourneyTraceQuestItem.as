package UI_Journey.AS3
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Dictionary;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.Quest.QuestAwardIconData;
	import ActionScript3.Quest.QuestTraceData;
	import ActionScript3.Quest.QuestTraceListItemEvent;
	import ActionScript3.Quest.QuestTraceTarget;
	
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextEventEx;

	public class JourneyTraceQuestItem extends JourneyTraceItemContentDetail
	{
		public var quest_trace_data:QuestTraceData;
		public var quest_trace_new_mc:QuestTraceListItemNewMark;
		public var quest_trace_caption_tf:TextField;
		public var quest_trace_type_mc:MovieClip;
//		public var quest_trace_item_mc:MyIcon;
		public var quest_trace_detail_tf:TextField;
		public var quest_trace_expand_mc:MovieClip;
		public var quest_trace_reduce_mc:MovieClip;
		public var quest_trace_level_tf:TextField;
//		public var quest_trace_complete_mc:MovieClip;
		public var quest_trace_award_0_mc:MovieClip;
		public var quest_trace_award_1_mc:MovieClip;
		public var quest_trace_award_2_mc:MovieClip;
		public var quest_trace_award_3_mc:MovieClip;
		public var quest_trace_award_item_mc:MovieClip;
		
		public var quest_trace_target_0_tf:MovieClip;
		public var quest_trace_target_1_tf:MovieClip;
		public var quest_trace_target_2_tf:MovieClip;
		public var quest_trace_target_3_tf:MovieClip;
		public var quest_trace_target_4_tf:MovieClip;
		public var quest_trace_target_5_tf:MovieClip;
		public var quest_trace_target_6_tf:MovieClip;
		public var quest_trace_target_7_tf:MovieClip;
		public static const max_quest_trace_target_count = 8;
		public static const max_quest_trace_award_item_count = 4;
		
		public var quest_trace_time_tf:TextField;
		public var quest_trace_expand:Boolean;
		private var _curQuestType:int = 0;
		
		public function JourneyTraceQuestItem()
		{
			quest_trace_level_tf.text = "";
			
			quest_trace_award_0_mc.visible = false;
			quest_trace_award_1_mc.visible = false;
			quest_trace_award_2_mc.visible = false;
			quest_trace_award_3_mc.visible = false;
			quest_trace_award_item_mc.visible = false;
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren = true;

			quest_trace_caption_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_trace_caption_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			quest_trace_caption_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			quest_trace_caption_tf.styleSheet = new StyleSheet  ;
			quest_trace_caption_tf.autoSize = flash.text.TextFieldAutoSize.NONE;// 自动高度
			quest_trace_caption_tf.wordWrap = false;
			
			quest_trace_detail_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_trace_detail_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			quest_trace_detail_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			quest_trace_detail_tf.styleSheet = new StyleSheet  ;
			quest_trace_detail_tf.autoSize = flash.text.TextFieldAutoSize.LEFT;
			quest_trace_detail_tf.wordWrap = true;
			
			quest_trace_new_mc.addEventListener(QuestTraceListItemEvent.PlayAnimCompleted, onPlayNewAnimCompleted);

		   	quest_trace_expand_mc.alpha = 0.0;
		    quest_trace_reduce_mc.alpha = 0.0;
			quest_trace_expand_mc.addEventListener(MouseEvent.CLICK, onExpand);
			quest_trace_reduce_mc.addEventListener(MouseEvent.CLICK, onReduce);
			quest_trace_expand = true;
		}

		public function RemoveAll():void
		{
			quest_trace_caption_tf.removeEventListener(TextEvent.LINK, onLinkCallBack);
			quest_trace_caption_tf.removeEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			quest_trace_caption_tf.removeEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			
			quest_trace_detail_tf.removeEventListener(TextEvent.LINK, onLinkCallBack);
			quest_trace_detail_tf.removeEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			quest_trace_detail_tf.removeEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);

			quest_trace_new_mc.removeEventListener(QuestTraceListItemEvent.PlayAnimCompleted, onPlayNewAnimCompleted);
//			quest_trace_item_mc.removeEventListener(MouseEvent.CLICK, onUseItem);

			quest_trace_data.RemoveAll();
			quest_trace_new_mc.RemoveAll();
//			quest_trace_item_mc.RemoveAll();

			quest_trace_data = null;
			quest_trace_new_mc = null;
			quest_trace_caption_tf = null;
			quest_trace_type_mc = null;
//			quest_trace_item_mc = null;
			quest_trace_detail_tf = null;
			quest_trace_time_tf = null;
			
			quest_trace_target_0_tf = null;
			quest_trace_target_1_tf = null;
			quest_trace_target_2_tf = null;
			quest_trace_target_3_tf = null;
			quest_trace_target_4_tf = null;
			quest_trace_target_5_tf = null;
			quest_trace_target_6_tf = null;
			quest_trace_target_7_tf = null;
		}

		private function onPlayNewAnimCompleted():void
		{
			this.quest_trace_data.quest_is_new = false;
		}

		private function pushQuestDetail(detail:String):void
		{
			if (detail != "")
			{
				quest_trace_detail_tf.htmlText +=  detail;
				//quest_trace_detail_tf.htmlText += "<br>";
			}
		}
		
		public function updateTimeLimit(sceond:int):void
		{
			if (sceond <= 0)
			{
				quest_trace_time_tf.visible = false;
				return;
			}
			quest_trace_time_tf.visible = true;
			var hp:String = "";
			var mp:String = "";
			var sp:String = "";
			var h:int=Math.floor(sceond/3600);
			var sec:int=sceond-(3600*h);
			var m:int=Math.floor(sec/60);
			var s:int=sec-(60*m);
			if (h < 10)
			{
				hp = "0";
			}

			if (m < 10)
			{
				mp = "0";
			}

			if (sec < 10)
			{
				sp = "0";
			}
			quest_trace_time_tf.text = "剩余时间:" + hp + h.toString() + ":" + mp + m.toString() + ":" + sp + s.toString();
		}

		private function setQuestType(quest_type:int):void
		{
			if(_curQuestType == quest_type)
			{
				return;
			}
			switch (quest_type)
			{
				case 0 :
					quest_trace_type_mc.gotoAndStop("trunk");
					break;
				case 1 :
					quest_trace_type_mc.gotoAndStop("branch");
					break;
				case 2 :
					quest_trace_type_mc.gotoAndStop("daily");
					break;
				case 3 :
					quest_trace_type_mc.gotoAndStop("reward");
					break;
				case 4 :
					quest_trace_type_mc.gotoAndStop("circle");
					break;
				case 5 :
					quest_trace_type_mc.gotoAndStop("activity");
					break;
				case 6 :
					quest_trace_type_mc.gotoAndStop("guild");
					break;
				case 7 :
					quest_trace_type_mc.gotoAndStop("master");
					break;
				case 8 :
					quest_trace_type_mc.gotoAndStop("wedding");
					break;
				case 9 :
					quest_trace_type_mc.gotoAndStop("adventure");
					break;
				case 10 :
					quest_trace_type_mc.gotoAndStop("guide");
					break;
				case 11 :
					quest_trace_type_mc.gotoAndStop("emergency");
					break;
			}
			_curQuestType = quest_type;
		}

		override public function updateItemData(data:Object, toUpdateParentLayout:Boolean = false):void
		{
			quest_trace_data = data as QuestTraceData;
			
			if (quest_trace_data != null)
			{
				var item_height:int = 0;
				var next_pos:int = 0;
				
				// 新任务
				quest_trace_new_mc.visible = quest_trace_data.quest_is_new;
				if (quest_trace_data.quest_is_new)
				{
					quest_trace_new_mc.startPlay();
					quest_trace_data.quest_is_new = false;
				}
				
				// 任务道具
//				quest_trace_item_mc.visible = false;
//				if (quest_trace_data.quest_item_id > 0)
//				{
//					quest_trace_item_mc.visible = quest_trace_expand;
//					quest_trace_item_mc.ItemTemplateID = quest_trace_data.quest_item_id;
//					quest_trace_item_mc.index = -1;
//					quest_trace_item_mc.setIconImg("img://" + quest_trace_data.quest_item_icon);
//				}
				
				// 任务标题
				//quest_trace_caption_tf.y = 0;
				//quest_trace_type_mc.visible = true;
				setQuestType(quest_trace_data.quest_type);
			//	quest_trace_caption_tf.visible = true;
				quest_trace_caption_tf.htmlText = quest_trace_data.quest_caption;
			//	quest_trace_level_tf.y = 0;
			//	quest_trace_level_tf.visible = true;
				quest_trace_level_tf.htmlText = quest_trace_data.quest_level;
				
				item_height += quest_trace_caption_tf.height;
				next_pos = quest_trace_caption_tf.y + quest_trace_caption_tf.height;
				
				// 延迟完成按钮
//				quest_trace_complete_mc.visible = quest_trace_data.quest_is_delay_complete;
				
				// 任务描述
				quest_trace_detail_tf.y = next_pos;
				quest_trace_detail_tf.visible = quest_trace_expand && !quest_trace_data.quest_is_delay_complete;
				quest_trace_detail_tf.htmlText = quest_trace_data.quest_detail;
				
				if (quest_trace_detail_tf.visible)
				{
					item_height += quest_trace_detail_tf.textHeight + 3;
					next_pos = quest_trace_detail_tf.y + quest_trace_detail_tf.textHeight + 3;
				}
				
				// 任务目标
				var i:int = 0;
				for (i = 0; i < max_quest_trace_target_count; ++ i)
				{
					var target_mc:QuestTraceTarget = this["quest_trace_target_" + i + "_tf"] as QuestTraceTarget;
					if (target_mc)
					{
						target_mc.visible = false;
						if (quest_trace_data.quest_targets)
						{
							if (i < quest_trace_data.quest_targets.length)
							{
								target_mc.y = next_pos;
								target_mc.visible = quest_trace_expand && !quest_trace_data.quest_is_delay_complete;
								if(target_mc.quest_trace_target_data && target_mc.isLine==true && quest_trace_data.quest_id==target_mc.quest_id)
								{//当前只更新数量
								    
									target_mc.quest_trace_target_data.quest_target_progress_cur=quest_trace_data.quest_targets[i].quest_target_progress_cur;
									target_mc.updateProgressData();
								}
								else
								{
									target_mc.quest_id=quest_trace_data.quest_id;//设置任务ID
									target_mc.setQuestTraceTargetData(quest_trace_data.quest_targets[i]);
								}
								
								
								if (target_mc.visible)
								{
									item_height += target_mc.height + 2;
									next_pos = target_mc.y + target_mc.height + 2;
								}
							}
						}
					}
				}
				
				// 限时任务
				quest_trace_time_tf.y = next_pos;
				updateTimeLimit(quest_trace_data.quest_time_limit);//更新时间
				quest_trace_time_tf.visible = quest_trace_time_tf.visible && quest_trace_expand && !quest_trace_data.quest_is_delay_complete;
				if (quest_trace_time_tf.visible)
				{
					item_height += quest_trace_time_tf.textHeight;
					next_pos = quest_trace_time_tf.y + quest_trace_time_tf.height + 2;
				}
				
				if (quest_trace_data.quest_is_delay_complete)
				{
					quest_trace_expand = true;
					quest_trace_expand_mc.visible = false;
					quest_trace_reduce_mc.visible = false;
				}
				
				// 任务奖励
		 		quest_trace_award_0_mc.visible = false;
				quest_trace_award_1_mc.visible = false;
				quest_trace_award_2_mc.visible = false;
		 		quest_trace_award_3_mc.visible = false;
				
				var award_mc:MovieClip;
				var award_icon_mc:MovieClip;
				var award_text_tf:TextField;
				var award_index:int = 0;
				
				if (quest_trace_data.quest_award_money != "")
				{
					award_mc = this["quest_trace_award_" + award_index + "_mc"] as MovieClip;
					if (award_mc)
					{
						award_mc.visible = true;
						award_icon_mc = award_mc["icon_mc"] as UILoader;
						award_text_tf = award_mc["count_tf"] as TextField;
						award_icon_mc.source = quest_trace_data.quest_award_money_icon;
						award_text_tf.htmlText = String(quest_trace_data.quest_award_money);
						award_index++;
					}
				}
				if (quest_trace_data.quest_award_money_ex != "")
				{
					award_mc = this["quest_trace_award_" + award_index + "_mc"] as MovieClip;
					if (award_mc)
					{
						award_mc.visible = true;
						award_icon_mc = award_mc["icon_mc"] as UILoader;
						award_text_tf = award_mc["count_tf"] as TextField;
						award_icon_mc.source = quest_trace_data.quest_award_money_icon_ex;
						award_text_tf.htmlText = String(quest_trace_data.quest_award_money_ex);
						award_index++;
					}
				}
				if (quest_trace_data.quest_award_exp > 0)
				{
					award_mc = this["quest_trace_award_" + award_index + "_mc"] as MovieClip;
					if (award_mc)
					{
						award_mc.visible = true;
						award_icon_mc = award_mc["icon_mc"] as UILoader;
						award_text_tf = award_mc["count_tf"] as TextField;
						award_icon_mc.source = quest_trace_data.quest_award_exp_icon;
						award_text_tf.htmlText = String(quest_trace_data.quest_award_exp);
						award_index++;
					}
				}
				if (quest_trace_data.quest_award_activity > 0)
				{
					award_mc = this["quest_trace_award_" + award_index + "_mc"] as MovieClip;
					if (award_mc)
					{
						award_mc.visible = true;
						award_icon_mc = award_mc["icon_mc"] as UILoader;
						award_text_tf = award_mc["count_tf"] as TextField;
						award_icon_mc.source = quest_trace_data.quest_award_activity_icon;
						award_text_tf.htmlText = String(quest_trace_data.quest_award_activity);
						award_index++;
					}
				}
				
				if (quest_trace_award_0_mc.visible)
				{
					quest_trace_award_0_mc.y = next_pos;
					quest_trace_award_1_mc.y = next_pos;
					item_height += quest_trace_award_0_mc.height;
					next_pos = quest_trace_award_0_mc.y + quest_trace_award_0_mc.height + 2;
				}
				
				if (quest_trace_award_2_mc.visible)
				{
					quest_trace_award_2_mc.y = next_pos;
					quest_trace_award_3_mc.y = next_pos;
					item_height += quest_trace_award_2_mc.height;
					next_pos = quest_trace_award_2_mc.y + quest_trace_award_2_mc.height + 2;
				}
				
				quest_trace_award_item_mc.visible = false;
				if (quest_trace_data.quest_awards)
				{
					quest_trace_award_item_mc.visible = (quest_trace_data.quest_awards.length > 0);
					for (i = 0; i < max_quest_trace_award_item_count; ++ i)
					{
						var item_mc:MyItemSlot = quest_trace_award_item_mc["award_item_" + i + "_mc"] as MyItemSlot;
						if (item_mc)
						{
							item_mc.visible = false;
							if (i < quest_trace_data.quest_awards.length)
							{
								item_mc.visible = true;
								item_mc.SetSlotType(19);
								var award_data:QuestAwardIconData = quest_trace_data.quest_awards[i] as QuestAwardIconData;
								item_mc.SetData(1, award_data.icon_img_name, award_data.item_template_id, "", 0, -1, -1);
							}
						}
					}
				}
				
				if (quest_trace_award_item_mc.visible)
				{
					quest_trace_award_item_mc.y = next_pos;
					item_height += quest_trace_award_item_mc.height;
					next_pos = quest_trace_award_item_mc.y + quest_trace_award_item_mc.height + 2;
				}
				
				item_height += 10;
				this.height = item_height;
			}
			
			if(toUpdateParentLayout)
			{
				(parent as JourneyTraceItemContent).updateLayout(false);
			}
		}
		
		private function onLinkCallBack(e:TextEvent):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}


		private function onLinkOverCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		private function onLinkOutCallBack(e:TextEventEx):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		private function onUseItem(e:MouseEvent):void
		{
			if (quest_trace_data != null)
			{
				if (quest_trace_data.quest_item_id > 0)
				{
					ExternalInterface.call( "ASUseQuestItem", quest_trace_data.quest_id, quest_trace_data.quest_item_id);
				}
			}
		}
		
		override public function setExpand(expand:Boolean, toUpdateParentLayout:Boolean = true):void
		{
			quest_trace_expand = expand;
			quest_trace_expand_mc.visible = !expand;
			quest_trace_reduce_mc.visible = expand;
			updateItemData(quest_trace_data);
			if(toUpdateParentLayout)
			{
				(parent as JourneyTraceItemContent).updateLayout(true);
			}
		}
		
		private function onExpand(e:MouseEvent):void
		{
			setExpand(true);
		}
		
		private function onReduce(e:MouseEvent):void
		{
			setExpand(false);
		}
		
		private function onComplete(e:MouseEvent):void
		{
			ExternalInterface.call("ASDelayComplete", quest_trace_data.quest_id);
		}
	}
}