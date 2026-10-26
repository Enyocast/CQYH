package ActionScript3.Mail
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	import ActionScript3.MoneyIcon;
	import ActionScript3.MyCombox;
	
	import UI_ChatWidget.AS3.ChatTextField;
	
	import scaleform.clik.constants.InputValue;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.ui.InputDetails;

	public class SendMailPage extends UIComponent
	{
		public var btn_send:Button;
		public var mail_title_txt:ChatTextField;
		public var mail_content_txt:ChatTextField;
		public var mail_cost_txt:TextField;
		public var money_mc:MoneyIcon;
		public var recentPlayers_scrolllist_mc:ScrollingList;
		public var recentPlayers_combox_mc:MyCombox;
		
		override protected function configUI():void
		{ 
			super.configUI();
			btn_send.addEventListener(MouseEvent.CLICK, onSendMail);
			mail_content_txt.addEventListener(InputEvent.INPUT, onInput);
			//var itemsData:Array = new Array();
			//for(var i:int = 0; i<10; i++)
			//itemsData.push(String("Hello") + i);
			//AddRecentPlayers(itemsData);
		}

		public function onShow():void
		{
			mail_title_txt.textField.maxChars=20;
			mail_content_txt.textField.maxChars=140;
			mail_content_txt.textField.multiline=true;
			mail_content_txt.defaultTextFormat.indent=22;
			mail_content_txt.textField.defaultTextFormat=mail_content_txt.defaultTextFormat;
			mail_content_txt.textField.setTextFormat(mail_content_txt.defaultTextFormat);
		    mail_content_txt.textField.wordWrap=true;
			recentPlayers_combox_mc.TextInputMaxChar = 12;
			if (null == recentPlayers_combox_mc.text || recentPlayers_combox_mc.text == "")
			{
				FocusHandler.getInstance().setFocus(recentPlayers_combox_mc.txt_combox_mc.textField);
			}
			else if (null == mail_title_txt.text || mail_title_txt.text == "")
			{
				FocusHandler.getInstance().setFocus(mail_title_txt.textField);
			}
			else if (null == mail_content_txt.text || mail_content_txt.text == "")
			{
				FocusHandler.getInstance().setFocus(mail_content_txt.textField);
			}
		}
		
		public function onHide():void
		{
			if(recentPlayers_combox_mc.dropdown_combox_mc.selected==true)
			{
				recentPlayers_combox_mc.close();
			}
		}

		public function onSendMail(evt:MouseEvent):void
		{
			ExternalInterface.call("ASSendMail", recentPlayers_combox_mc.text, mail_title_txt.text, mail_content_txt.textField.text);
		}

		public function ClearSendContent():void
		{
			mail_title_txt.text = "";
			mail_content_txt.text = "";
			recentPlayers_combox_mc.text = "";
		}

		public function AddRecentPlayers(data:Array):void
		{
			if(data.length <= 0)
			{
				recentPlayers_combox_mc.dropdown_combox_mc.visible = false;
			}
			else
			{
				recentPlayers_combox_mc.dropdown_combox_mc.visible = true;
				recentPlayers_combox_mc.UpdateComboxData(data);
				
			}
		}
		
		public function SetPlayerName(n:String):void
		{
			recentPlayers_combox_mc.txt_combox_mc.text = n;
		}
		
		private function onInput(event:InputEvent):void
		{ 
			var details:InputDetails = event.details;
			if(details.value == InputValue.KEY_UP)
			{
				if(mail_content_txt.length >= mail_content_txt.textField.maxChars)
				{
					ExternalInterface.call("ASMessageMailContentTooLong");
				}
			}
		}
	}

}