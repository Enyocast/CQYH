//
// 家族创建
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import UI_ChatWidget.AS3.ChatTextField;
	import flash.events.FocusEvent;

	public class GuildCreatePanel extends MyPanel
	{
		public var guild_create_name_mc:ChatTextField;
		public var guild_create_gold_req_tf : TextField;
		public var guild_create_item_req_tf : TextField;
		public var guild_create_item_icon_mc:MyItemSlot;
		public var guild_create_announce_mc:ChatTextField;
		
		public var guild_create_ok_mc : Button;
		public var guild_create_cancel_mc : Button;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
            guild_create_name_mc.textField.maxChars=12;
			MyWindowsFrame_mc.tF_windowTitle.text="创建公会 ";
			guild_create_ok_mc.addEventListener(MouseEvent.CLICK, onBtClickOk);
			guild_create_cancel_mc.addEventListener(MouseEvent.CLICK, onBtClickClose);
			btn_close.RemoveAddedEventListener();
			btn_close.addEventListener(MouseEvent.CLICK , onBtClickClose);
			guild_create_announce_mc.textField.wordWrap=true;
			guild_create_announce_mc.textField.multiline=true;
			guild_create_name_mc.defaultText="(最多8个汉字)";
			guild_create_announce_mc.defaultText="请输入公会宣言（最多30个汉字）";
			updateTextFormat(true,guild_create_name_mc);
			updateTextFormat(true,guild_create_announce_mc);
			guild_create_name_mc.addEventListener(FocusEvent.FOCUS_IN,focusinHandler);
			guild_create_name_mc.addEventListener(FocusEvent.FOCUS_OUT,focusoutHandler);
			guild_create_announce_mc.addEventListener(FocusEvent.FOCUS_IN,focusinHandler);
			guild_create_announce_mc.addEventListener(FocusEvent.FOCUS_OUT,focusoutHandler);
			guild_create_name_mc.addEventListener(Event.CHANGE,changeHandler);
			guild_create_announce_mc.addEventListener(Event.CHANGE,changeHandler);
		}
		
		private function changeHandler(evt:Event):void
		{
			var input:ChatTextField=evt.currentTarget as ChatTextField;
			updateTextFormat(false,input);
		}
		
		private function focusinHandler(evt:FocusEvent):void
		{
			var input:ChatTextField=evt.currentTarget as ChatTextField;
			updateTextFormat(false,input);
		}
		private function focusoutHandler(evt:FocusEvent):void
		{
			var input:ChatTextField=evt.currentTarget as ChatTextField;
			if(input.text!="")
			{
				updateTextFormat(false,input);
			}
			else
			{
				updateTextFormat(true,input);
			}
		}
		
		private function updateTextFormat(bl:Boolean,input:ChatTextField):void
		{
			if(input==guild_create_name_mc)
			{
				input.textField.maxChars=12;
			}
			else
			{
				input.textField.maxChars=30;
			}
			
			if(bl)
			{
				input.defaultTextFormat.color=0x85919E;
				input.textField.setTextFormat(input.defaultTextFormat);
			}
			else
			{
				input.defaultTextFormat.color=0xFFFFFF;
				input.textField.setTextFormat(input.defaultTextFormat);
			}
		}
		public function onBtClickClose(evt:MouseEvent):void
		{
			guild_create_name_mc.text = "";
			updateTextFormat(true,guild_create_name_mc);
			guild_create_announce_mc.text = "";
			updateTextFormat(true,guild_create_announce_mc);
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
		
		private function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASCreateGuild", guild_create_name_mc.text, guild_create_announce_mc.text);
		}
		
		// UC
		public function UCSetMoneyRequest(money:String):void
		{
			guild_create_gold_req_tf.htmlText = money;
		}
		
		public function UCSetItemRequest(item_name:String, item_icon:String, item_id:int):void
		{
			guild_create_item_req_tf.htmlText = item_name;
			guild_create_item_icon_mc.SetSlotType(19);
			guild_create_item_icon_mc.SetData(1, item_icon, item_id, "", 0, -1, -1);
		}
		
		public function UCCreateSuccess():void
		{
			ExternalInterface.call("ASOnPanelClose" , this.PanelName);
		}
	}
}


























