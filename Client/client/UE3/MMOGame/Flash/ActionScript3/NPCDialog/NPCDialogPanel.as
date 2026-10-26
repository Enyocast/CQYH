package ActionScript3.NPCDialog
{

	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Quest.QuestAwardIconData;
	import ActionScript3.Quest.QuestDetailData;
	
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import ActionScript3.MyCloseButton;


	public class NPCDialogPanel extends MyPanel implements INPCDialogPanel
	{

		public static const C_MinDiagHeight = 144;
		public static const C_MinDiagPadding = 6;
		public var avatar_mc:MovieClip;
		public var _dialog_content_mc:NPCDialogContent;
		//public var _diag_bg_mc:MovieClip;
		public var _npcNameTxt:TextField;
		
		override protected function configUI():void
		{
			//trace("------NpcDialogPanel  super.configUI");
			super.configUI();
            btn_close.RemoveAddedEventListener();
			btn_close.addEventListener(MouseEvent.CLICK,closeHandler);
			_dialog_content_mc._parentPanel = this;
			if (1)
			{// 正式导出或上传前注释掉这行
				
				_npcNameTxt.text = "村民";
				var dataArr:Array = new Array  ;

				var dat:NPCDialogData = new NPCDialogData  ;
				dat.diag_type = NPCDialogData.DiagDataType_Dialog;
				dat.diag_text = "最小对话界面";
				dat.diag_npc_name = "NPC1";
				dataArr.push(dat);


				dataArr.push(testOption(2));
				dataArr.push(testOption(4));


				dat = new NPCDialogData  ;
				dat.diag_npc_name = "NPC3";
				dat.diag_type = NPCDialogData.DiagDataType_Dialog;
				dat.diag_text = "下面有很多对话段:<br>";
				for (var j:int = 0; j < 4; ++j)
				{
					dat.diag_text +=  j.toString() + "-年青人，又见面了!<br>";
				}

				dat.diag_text +=  "<br>最后，年青人，又见面了!<br><a href='event:1,2,3'><U>村长</U></a>正在找你呢，快点去他那里领取任务开始探险吧！";
				dataArr.push(dat);


				
				dataArr.push(testQuest(false, false, false, false));
				//dataArr.push(testQuest(true, true, true, true));				
				//dataArr.push(testQuest(true, false, false, false));
				//dataArr.push(testQuest(true, false, false, true));
				//dataArr.push(testQuest(true, false, true, true));
				//dataArr.push(testQuest(false, true, true, true));
								

				UCUpdateDiagData(dataArr);
			}
			else
			{
				UCUpdateDiagData([]);
			}
			
		}
		
		private function closeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASCloseDialog");
			//ExternalInterface.call( "ASOnPanelClose" , this.name );
		}

		function testOption(cnt:int):NPCDialogData
		{
			var dat:NPCDialogData = new NPCDialogData  ;
			dat.diag_npc_name = "NPC2";
			dat.diag_type = NPCDialogData.DiagDataType_Dialog;
			
			dat.diag_text = "年青人，好久不见了，<a href='event:1,2,3'><U>村长</U></a>正在找你呢，快点去他那里领取任务开始探险吧！";
			dat.option_list = new Array  ;
			for (var i:int = 0; i < cnt; ++i)
			{
				var opt:NPCDialogOptionData = new NPCDialogOptionData  ;
				opt.option_type = i % 2;
				opt.option_id = i;
				opt.option_label = "选项测试" + i;

				dat.option_list.push(opt);
			}

			return dat;
		}

		function testQuest(showAward:Boolean, showSelectAward:Boolean, canComplete:Boolean, isAccept:Boolean):NPCDialogData
		{
			var dat:NPCDialogData = new NPCDialogData  ;
			dat.diag_npc_name = "NPC4";
			dat.diag_type = NPCDialogData.DiagDataType_QuestAccept;
			dat.quest_detail_data = new QuestDetailData  ;
			dat.quest_detail_data.quest_id = 104;
			dat.quest_detail_data.quest_caption = "任务标题";
			dat.quest_detail_data.quest_desc = "如果你接受并完成这个任务就可以从<a href='event:1,2,3'><U>村长</U></a>获得以下奖励";
			//dat.quest_detail_data.quest_complete_desc = "可以从<a href='event:1,2,3'><U>村长</U></a>获得以下奖励";

			dat.quest_detail_data.quest_is_accepted = isAccept;
			dat.quest_detail_data.quest_is_compassable = canComplete;
			dat.quest_detail_data.quest_awards = new Array  ;
			dat.quest_detail_data.quest_award_select = new Array  ;
			dat.quest_detail_data.quest_award_money_caption = "奖励很长的很长的金钱：";
			dat.quest_detail_data.quest_award_money = "88888888";
			dat.quest_detail_data.quest_award_exp_caption = "奖励经验：";
			dat.quest_detail_data.quest_award_exp = 666666;
			//dat.quest_detail_data.quest_accept_desc = "接任务对话：！！！";
			
			for (var k:int = 0; k < 4; ++k)
			{
				var award:QuestAwardIconData = new QuestAwardIconData  ;
				award.item_name = "ItemName" + k;
				award.item_count = k;
				award.item_template_id = 4000 + k;

				if (showSelectAward)
				{
					dat.quest_detail_data.quest_award_select.push(award);
				}

				if (showAward)
				{
					dat.quest_detail_data.quest_awards.push(award);
				}
			}

			return dat;
		}

		public function UCUpdateDiagData(dat:Array)
		{
			_dialog_content_mc.updateDiagData(dat);
		}
		
		public function UCUpdateDiagPage(page:int)
		{
			_dialog_content_mc.updateToPage(page);
		}
		public function updatePanelHeight():void
		{
/*			if (h > C_MinDiagHeight)
			{
				//_diag_bg_mc.height = h + C_MinDiagPadding;
				//InfoDragButton_mc.height = h + C_MinDiagPadding;
			}
			else
			{
				//_diag_bg_mc.height = C_MinDiagHeight;
				//InfoDragButton_mc.height = C_MinDiagHeight;
			}*/
		}

		public function setNPCName(s:String)
		{
			_npcNameTxt.htmlText = s;
		}
		
		public function UCPlay(timer:int):void
		{
			_dialog_content_mc.PlayAnimation(timer);
		}
	}

}