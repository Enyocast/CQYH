package ActionScript3.Mail{
	
	import ActionScript3.MyPanel;
	
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButtonNew;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ScrollingList;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	
	public class MailPanel extends MyPanel
	{
		public var send_mail_page_mc:SendMailPage;
		public var mail_list_page_mc:MailListPage;
		
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		
		override protected  function configUI():void 
		{			
			ShowMode="BC";
			super.configUI();			
			ExternalInterface.call("SetTextByID", MyWindowsFrame_mc.tF_windowTitle, "MMOGame.Mail.Title");
			
			onShowMailListPage();
			
			tab0_mc.addEventListener(ButtonEvent.CLICK, onShowMailListPage);
			tab1_mc.addEventListener(ButtonEvent.CLICK, onShowMailSendPage);
			
			tab0_mc.selected = true;
			this.addEventListener(ComponentEvent.HIDE, onHide);
			
			//UCUpdateSelectAllState(true);
		}
		
		override public function UCGetWidth():int
		{
			if(MyWindowsFrame_mc){
				return MyWindowsFrame_mc.width;//fix new window use mask in background 
			}
			return this.OrignW;
		}
		
		private function onHide(evt:Event):void
		{
			send_mail_page_mc.onHide();
		}
		
		public function onShowReply():void
		{
			UCReplyMail("test player", "reply:subject....");
		}
		
		public function onShowMailListPage(evt:ButtonEvent=null):void
		{
			tab0_mc.selected = true;
			tab1_mc.selected = false;
			send_mail_page_mc.visible = false;
			mail_list_page_mc.visible = true;
		}
		
		public function onShowMailSendPage(evt:ButtonEvent=null):void
		{
			tab0_mc.selected = false;
			tab1_mc.selected = true;
			send_mail_page_mc.visible = true;
			send_mail_page_mc.onShow();
			mail_list_page_mc.visible = false;
		}
		
		public function UCUpdateMailData(mailData:Array):void
		{
			mail_list_page_mc.updateMailData(mailData);
		}		
		
		
		public function UCReplyMail(toPlayer:String, mailTitle:String):void
		{
			send_mail_page_mc.recentPlayers_combox_mc.txt_combox_mc.text = toPlayer;			
			send_mail_page_mc.mail_title_txt.text = mailTitle;			
			
			onShowMailSendPage();
		}
		
		public function UCClearSendContent():void
		{
			send_mail_page_mc.ClearSendContent();
		}
		
		public function UCShowTabPage(idx:int):void
		{
			if(idx == 0)
			{
				tab0_mc.selected = true;
				onShowMailListPage();
			}
			else
			{
				tab1_mc.selected = true;
				onShowMailSendPage();
			}
		}
		
		public function UCAddRecentPlayers(data:Array):void
		{
			send_mail_page_mc.AddRecentPlayers(data);
		}
		
		public function UCSetPlayerName(n:String):void
		{
			send_mail_page_mc.SetPlayerName(n);
		}
		
		public function  UCUpdateSelectAllState(v:Boolean):void
		{
			mail_list_page_mc.UpdateSelectAllState(v);
		}
		
	}

}