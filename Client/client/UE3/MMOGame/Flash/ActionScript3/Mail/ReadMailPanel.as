package ActionScript3.Mail{
	
	import ActionScript3.MyPanel;
	
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.MyScrollBar;

	public class ReadMailPanel extends MyPanel
	{
		public var mail_sender_txt:TextField;
		public var mail_title_txt:TextField;
		public var mail_content_txt:TextField;
		
		public var btn_reply:Button;
		public var btn_delete:Button;
		public var btn_acquire:Button;
		
		public var mail_item_0:MyItemSlot;
		public var tl_itemcount:TextField;
		public var itembg:MovieClip;
		public var mail_id:int;
		
		private const USERTYPE:int = 0;
		private const SYSTEMTYPE:int = 1;
		public var scrollbar:MyScrollBar;
		
		public var MAIL_WIDTH:int = 425;
		public var MAIL_HEIGHT:int = 576;
		
		override protected  function configUI():void 
		{			
			ShowMode="BC";//居中往左偏
			super.configUI();
			btn_reply.addEventListener(MouseEvent.CLICK, onReplyMail);
			btn_delete.addEventListener(MouseEvent.CLICK, onDeleteMail);
			btn_acquire.addEventListener(MouseEvent.CLICK, onAcquireMailItems);			
			itembg.visible = false;
			mail_item_0.visible = false;
			btn_acquire.visible = false;
			tl_itemcount.visible = false;
		}
		
		public function onReplyMail(e:MouseEvent):void
		{
			ExternalInterface.call("ASReplyMail", this.mail_id);
		}
		
		public function onDeleteMail(e:MouseEvent):void
		{
			ExternalInterface.call("ASDeleteMail", this.mail_id);
		}
		
		public function onAcquireMailItems(e:MouseEvent):void
		{
			ExternalInterface.call("ASAcquireMailItems", this.mail_id);
		}
		
		public function UCUpdateMailInfo(mailID:int, mailType:int, mailAttachmentItemID:int, mailSender:String, mailTitle:String, mailContent:String ):void
		{
			mail_id = mailID;
			mail_sender_txt.htmlText = mailSender;
			mail_title_txt.htmlText = mailTitle;

			if(SYSTEMTYPE == mailType)
			{
				if(btn_reply.enabled)
					btn_reply.enabled = false;
			}
			else
			{
				if(!btn_reply.enabled)
					btn_reply.enabled = true;
			}
			
			if(SYSTEMTYPE == mailType && mailAttachmentItemID >= 0)
			{
				itembg.visible = true;
				btn_acquire.visible = true;
				mail_item_0.visible = true;
				tl_itemcount.visible = true;
				mail_content_txt.height=178;
				scrollbar.height=178;
			}
			else
			{
				mail_content_txt.height=258;
				scrollbar.height=258;
				itembg.visible = false;
				btn_acquire.visible = false;
				mail_item_0.visible = false;
				tl_itemcount.visible = false;
			}
			mail_content_txt.htmlText = mailContent;
		}
		
		public function UCUpdateAcquireAttachment():void
		{
			if(btn_acquire.visible)
				btn_acquire.visible = false;
			if(itembg.visible)
				itembg.visible = false;
			if(mail_item_0.visible)
				mail_item_0.visible = false;
			if(tl_itemcount.visible)
				tl_itemcount.visible = false;
		}
		
		public function UCSetReadPanelPostion(posX:int, posY:int):void
		{
			this.x = posX + MAIL_WIDTH;
			this.y = posY + ( ( MAIL_HEIGHT - this.height ) * 0.5 );
		}
	}

}