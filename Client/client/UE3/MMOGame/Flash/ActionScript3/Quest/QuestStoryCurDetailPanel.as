package ActionScript3.Quest
{
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	import flash.utils.getDefinitionByName;
	import flash.utils.getTimer;
	
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.SliderEvent;
	import scaleform.gfx.TextEventEx;
	import scaleform.gfx.TextFieldEx;

	public class QuestStoryCurDetailPanel extends MyScrollPanel
	{
		public var _traceScrollbar:MyScrollBar;
		//public var _mouse_wheel_layer:MovieClip;
		
		public var quest_stage_name_tf:TextField;
		public var quest_title_tf:TextField
		public var quest_chapter_icon_mc:UILoader;
		
		public var quest_desc_tf:TextField;
		
		private var targetList:Array=[];

		public var quest_award_select_list_mc:QuestAwardList;
		public var quest_award_other_mc:MovieClip;
		
		public static const quest_target_max_count = 1;
		public static const quest_award_max_count = 4;
		public static const quest_award_select_max_count = 4;
		
		public var quest_award_select_icon_list:Array;
		public var desc:MovieClip;//任务描述
		public var other:MovieClip;//任务其他奖励
		
		public var award_exp_mc:MovieClip;
		public var award_money_mc:MovieClip;
		public var award_money_ex_mc:MovieClip;
		public var award_activity_mc:MovieClip;
		
		public var detail_data:QuestDetailData;
		
		public function QuestStoryCurDetailPanel()
		{

		}

		override protected function configUI():void
		{
			super.configUI();
			var i:int=0;
			quest_desc_tf=desc.getChildByName("quest_desc_tf") as TextField;
			quest_desc_tf.styleSheet = new StyleSheet  ;
			quest_desc_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			quest_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			quest_desc_tf.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);

			other=new (getDefinitionByName("QuestOtherAwardList") as Class)();
			other.y=this.height;
			other.visible=false;
			this.addChild(other)
			quest_award_select_list_mc=other.getChildByName("quest_award_select_list_mc") as QuestAwardList;
			
			quest_award_other_mc=new (getDefinitionByName("QuestStoryAwardList") as Class)();
			quest_award_other_mc.y=this.height;
			quest_award_other_mc.visible=false;
			this.addChild(quest_award_other_mc);
			award_exp_mc = quest_award_other_mc.getChildByName("award_exp_mc") as MovieClip;
			award_money_mc = quest_award_other_mc.getChildByName("award_money_mc") as MovieClip;
			award_money_ex_mc = quest_award_other_mc.getChildByName("award_money_ex_mc") as MovieClip;
			award_activity_mc = quest_award_other_mc.getChildByName("award_activity_mc") as MovieClip;
			
			award_exp_mc.addEventListener("rollOver", onItemRollOver);
			award_exp_mc.addEventListener("rollOut", onItemRollOut);
			award_money_mc.addEventListener("rollOver", onItemRollOver);
			award_money_mc.addEventListener("rollOut", onItemRollOut);
			award_money_ex_mc.addEventListener("rollOver", onItemRollOver);
			award_money_ex_mc.addEventListener("rollOut", onItemRollOut);
			award_activity_mc.addEventListener("rollOver", onItemRollOver);
			award_activity_mc.addEventListener("rollOut", onItemRollOut);

			quest_award_select_icon_list =[];

			for (i = 0; i < quest_award_select_max_count; i ++)
			{
				var select_award_icon:MyItemSlot = quest_award_select_list_mc.getChildByName("award_icon" + i) as MyItemSlot;
				if (select_award_icon)
				{
					quest_award_select_icon_list.push(select_award_icon);
				}
			}
			quest_award_other_mc.visible = false;
			
			// test
			//updateQuestDetailData(testData());
			
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

		private function onLinkCallBack(e:TextEvent):void
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		public function onItemRollOver(e:Event)
		{
			var item_mc:MovieClip = e.currentTarget as MovieClip;
			if (item_mc && detail_data)
			{
				award_exp_mc = quest_award_other_mc.getChildByName("award_exp_mc") as MovieClip;
				award_money_mc = quest_award_other_mc.getChildByName("award_money_mc") as MovieClip;
				award_money_ex_mc = quest_award_other_mc.getChildByName("award_money_ex_mc") as MovieClip;
				award_activity_mc = quest_award_other_mc.getChildByName("award_activity_mc") as MovieClip;
				
				if (item_mc.name == "award_exp_mc")
				{
					var tips:String = "经验奖励：" + detail_data.quest_award_exp.toString();
					ExternalInterface.call("ASShowTips_PlainText_WithString", item_mc, tips);
				}
				else if (item_mc.name == "award_money_mc")
				{
					tips = "金钱奖励：" + String(detail_data.quest_award_money);
					ExternalInterface.call("ASShowTips_PlainText_WithString", item_mc, tips);
				}
				else if (item_mc.name == "award_money_ex_mc")
				{
					tips = "金钱奖励：" + String(detail_data.quest_award_money_ex);
					ExternalInterface.call("ASShowTips_PlainText_WithString", item_mc, tips);
				}
				else if (item_mc.name == "award_activity_mc")
				{
					tips = "活跃度奖励：" + String(detail_data.quest_award_activity.toString());
					ExternalInterface.call("ASShowTips_PlainText_WithString", item_mc, tips);
				}
			}
		}
		
		public function onItemRollOut(e:Event):void
		{
			var item_mc:MovieClip = e.currentTarget as MovieClip;
			if (item_mc)
			{
				ExternalInterface.call("ASHideTips_PlainText", item_mc);
			}
		}
		
		public function setupScrollBar(scrollBar:MyScrollBar):void
		{
			_traceScrollbar = scrollBar;
			if (_traceScrollbar)
			{
				_traceScrollbar.scrollTarget = this;
				_traceScrollbar.height = 340;
				_traceScrollbar.position = 0;
				//this.addEventListener(SliderEvent.VALUE_CHANGE, onScrollChange);
			}
			else
			{
				ExternalInterface.call("ASTrace", "_traceScrollbar is null!");
			}
		}
	
		public function updateQuestStoryOverDesc(desc:String):void
		{
			var i:int = 0;
			quest_desc_tf.htmlText = desc;
		    quest_award_other_mc.visible = false;
			other.visible = false;
		}
		
		public function updateQuestDetailData(data:QuestDetailData):void
		{
			var i:int = 0;
			if (data == null)
			{
				quest_desc_tf.htmlText = "目前没有剧情任务信息";
				(this.parent.getChildByName("quest_chapter_icon_mc") as UILoader).source = "UI_Quest.chapter1";
		        quest_award_other_mc.visible = false;
				other.visible = false;
				return;
			}
			
			detail_data = data;
			//quest_stage_name_tf.text = detail_data.quest_stage_name;
			(this.parent.getChildByName("quest_chapter_icon_mc") as UILoader).source = detail_data.quest_chapter_icon;
			
			// 任务标题
			//quest_title_tf.htmlText = detail_data.quest_caption;
			(this.parent.getChildByName("quest_story_name") as TextField).text=detail_data.quest_stage_name;
			//(this.parent.getChildByName("quest_chapter_icon_mc") as MovieClip).source=detail_data.quest_chapter_icon;
			//(this.parent.getChildByName("quest_title_tf") as TextField).text=detail_data.quest_caption;
						
			// 任务描述
			quest_desc_tf.visible = true;
			quest_desc_tf.autoSize =TextFieldAutoSize.LEFT;
			quest_desc_tf.wordWrap = true;
			quest_desc_tf.htmlText = detail_data.quest_stage_desc;
			quest_desc_tf.height = quest_desc_tf.textHeight;
			quest_award_other_mc.visible = false;
			other.visible = false;
			updateQuestDetailLayout();

			// 需求#15142  剧情面板里不显示任务奖励
			/*
		    quest_award_other_mc.visible = true;
			// 经验
			award_exp_mc = quest_award_other_mc.getChildByName("award_exp_mc") as MovieClip;
			var icon_mc:UILoader = award_exp_mc.getChildByName("icon_mc") as UILoader;
			icon_mc.source = detail_data.quest_award_exp > 0 ? detail_data.quest_award_exp_icon : null;
			award_exp_mc.visible = detail_data.quest_award_exp > 0;
			
			// 货币
			award_money_mc = quest_award_other_mc.getChildByName("award_money_mc") as MovieClip;
			icon_mc = award_money_mc.getChildByName("icon_mc") as UILoader;
			icon_mc.source = detail_data.quest_award_money != "" ? detail_data.quest_award_money_icon : null;
			award_money_mc.visible = detail_data.quest_award_money != "";

			award_money_ex_mc = quest_award_other_mc.getChildByName("award_money_ex_mc") as MovieClip;
			icon_mc = award_money_ex_mc.getChildByName("icon_mc") as UILoader;
			icon_mc.source = detail_data.quest_award_money_ex != "" ? detail_data.quest_award_money_icon_ex : null;
			award_money_ex_mc.visible = detail_data.quest_award_money_ex != "";
			
			// 活跃度
			award_activity_mc = quest_award_other_mc.getChildByName("award_activity_mc") as MovieClip;
			icon_mc = award_activity_mc.getChildByName("icon_mc") as UILoader;
			icon_mc.source = detail_data.quest_award_activity > 0 ? detail_data.quest_award_activity_icon : null;
			award_activity_mc.visible = detail_data.quest_award_activity > 0;
			
			other.visible = false;
			
			var award_icon:MyItemSlot;

			if (detail_data.quest_award_select)
			{
				other.visible = detail_data.quest_award_select.length > 0;
				
				for(i=0;i<quest_award_select_max_count;i++){
					var award_select_data:QuestAwardIconData = detail_data.quest_award_select[i] as QuestAwardIconData;
					award_icon = quest_award_select_icon_list[i] as MyItemSlot;
					if(award_select_data){
			            if (award_select_data.icon_img_name == "")
					    {
						    award_icon.visible = false;
						}else{
						    award_icon.visible = true;
						    award_icon.SetSlotType(19);
						    award_icon.SetData(1, award_select_data.icon_img_name, award_select_data.item_template_id, "", 0, -1, -1);
					    }}else{
						award_icon.visible = false;
					}
				}
			}
			*/
			
		}

		private function updateQuestDetailLayout():void
		{
			// 任务描述
			var lender:int=10;
			
			var next_pos:int=0;
			
			desc.y=next_pos;
			
			// 按照策划需求,不显示任务描述标题，描述内容顶上去
			quest_desc_tf.y = 0;
			next_pos=desc.y+desc.height;
            next_pos+=lender;
			
			// 需求#15142  剧情面板里不显示任务奖励
			/*
			// 钱，经验，帮贡
			quest_award_other_mc.y = next_pos-5;
			award_exp_mc = quest_award_other_mc.getChildByName("award_exp_mc") as MovieClip;
			award_money_mc = quest_award_other_mc.getChildByName("award_money_mc") as MovieClip;
			award_money_ex_mc = quest_award_other_mc.getChildByName("award_money_ex_mc") as MovieClip;
			award_activity_mc = quest_award_other_mc.getChildByName("award_activity_mc") as MovieClip;
			var icon_x:int = 0;
			
			if (award_exp_mc && award_exp_mc.visible)
			{
				award_exp_mc.x = icon_x;
				icon_x += 59; 
			}
			
			if (award_money_mc && award_money_mc.visible)
			{
				award_money_mc.x = icon_x;
				icon_x += 59;
			}
			
			if (award_money_ex_mc && award_money_ex_mc.visible)
			{
				award_money_ex_mc.x = icon_x;
				icon_x += 59;
			}
			
			if (award_activity_mc && award_activity_mc.visible)
			{
				award_activity_mc.x = icon_x;
				icon_x += 59;
			}
			
			next_pos+=quest_award_other_mc.height;
			next_pos+=lender;
			
			// 可选任务奖励
			if (other.visible)
			{
				other.y = next_pos;
				next_pos = other.y + other.height;
			}
            next_pos+=lender;
			*/
			
			this.height = next_pos + 4;
		}
		
/*		public function testData():QuestDetailData
		{
			var testDetailData:QuestDetailData = new QuestDetailData();

			testDetailData.quest_stage_name="第一幕";
			testDetailData.quest_chapter_icon="<img src='img_SysTitleText_warehouse'>";
			testDetailData.quest_caption="杀死比尔";

			testDetailData.quest_id = 888;
			testDetailData.quest_type = 2;
			testDetailData.quest_caption = "任务标题";
			testDetailData.quest_conditions_caption = "任务目标";
			testDetailData.quest_conditions = [];
			for(var k:int = 0; k < 8; k++)
			{
				testDetailData.quest_conditions.push("conditions" + k);
			}
			
			testDetailData.quest_targets = null;
			
			testDetailData.quest_desc_caption = "任务描述";
			testDetailData.quest_stage_desc = "quest_desc<u>underline</u><a href='event:123,12,3.15,4.24,7.2'>伏地魔伏地魔</a>伏地魔伏地魔伏地的的的的得到的大的掉的大的的得到的大的掉的大的的的的得到的大的掉的大魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔伏地魔\n这是测试";
			//
			testDetailData.quest_submit_caption = "交付NPC";
			testDetailData.quest_submit = "完成后找<u><a href='event:,2,6009,2'>村长</a></u>谈话";
			
			testDetailData.quest_award_caption = "任务奖励";
			testDetailData.quest_awards = [];
			testDetailData.quest_is_available=true;
			
			var n:int;
			var iconDat:QuestAwardIconData;
			
			for(n = 0; n <4;  n++)
			{
				iconDat = new QuestAwardIconData();
				iconDat.icon_img_name = "<img src='img://MMO_UIIcon.MoneyIcon.MoneyGold_S'>";
				iconDat.item_template_id = n;
				iconDat.item_index = n;
				testDetailData.quest_awards.push(iconDat);
			}
			
			testDetailData.quest_award_select_caption = "可选奖励";
			testDetailData.quest_award_select = [];
			for(n = 0; n < 3; n++)
			{
				iconDat = new QuestAwardIconData();
				iconDat.icon_img_name = "testImage";
				iconDat.item_template_id = n;
				iconDat.item_index = n;
				testDetailData.quest_award_select.push(iconDat);
			}
			
			
			testDetailData.quest_award_exp_icon = "Item_144.TGA";
			testDetailData.quest_award_exp = 0;				
			testDetailData.quest_award_money_icon = "img_Money.TGA";
			testDetailData.quest_award_money ="1";
			testDetailData.quest_award_money_icon_ex="img_BindMoney.TGA";
			testDetailData.quest_award_money_ex="1";
			testDetailData.quest_award_activity_icon="Item_147.TGA";
			testDetailData.quest_award_activity=1000;
			return testDetailData;

		}*/
	}
}