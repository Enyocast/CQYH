package ActionScript3.Quest
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButtonNew;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.gfx.Extensions;
	import ActionScript3.MyScrollBar;
	
	import scaleform.clik.motion.Tween;
	import fl.transitions.easing.*;

	public class QuestItemCollectionPanel extends MyPanel
	{
		//public var MyWindowsFrame_mc:MovieClip;
		public var quest_desc_tf:TextField;
		public var quest_collection_item_mc:MovieClip;
		public var quest_collection_item_name_tf:TextField;
		public var quest_collection_item_ok_mc:MovieClip;
		public var quest_collection_item_cancel_mc:MovieClip;
		
		public var quest_id:int;
		public var quest_item_id:int;
		public var quest_item_index:int;
		
		public function QuestItemCollectionPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("物品提交");
		    quest_id = 0;
		    quest_item_id = 0;
		    quest_item_index = 0;
		
			quest_collection_item_ok_mc.addEventListener(MouseEvent.CLICK, onBtClickOK);
			quest_collection_item_cancel_mc.addEventListener(MouseEvent.CLICK, onBtClickCancel);
		}

		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateQuestData(data:Object)
		{
			quest_id = data.quest_id;
			quest_desc_tf.text = String(data.quest_desc);
		}
		
		public function UCUpdateItemData(data:Object)
		{
			quest_item_id = data.quest_item_id;
			quest_item_index = data.quest_item_index;
			quest_collection_item_name_tf.text = String(data.quest_item_name);
		}
		
		public function onBtClickOK()
		{
			ExternalInterface.call("ASSubmitItem", quest_id, quest_item_id, quest_item_index);
		}
		
		public function onBtClickCancel()
		{
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
	}
}