package ActionScript3.Mail
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.controls.StateUIComponent;
	import flash.display.DisplayObject;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ComponentEvent;

	public class MailListItem extends ListItemTreeRenderer
	{		
		public var mail_icon:MovieClip;
		public var mail_from_txt:TextField;
		public var mail_title_txt:TextField;
		public var mail_valid_days_txt:TextField;
		public var mail_has_items_mc:MovieClip;
		public var mail_select_checkbox:Button;
		public var transparence_btn_mc:Button;
		//public var listup:MovieClip;
		//public var readBtn:RadioButton;
		//public var noreadBtn:RadioButton;
		
		public var mail_data:MailData;

		public function MailListItem()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			mouseChildren = true;
			mouseEnabled = true;
			mail_select_checkbox.label = "";
			mail_select_checkbox.addEventListener(MouseEvent.CLICK, onSelectMail);
			transparence_btn_mc.doubleClickEnabled = true;
			transparence_btn_mc.addEventListener(MouseEvent.CLICK, onItemDoubleClick);
			//this.addEventListener(ComponentEvent.STATE_CHANGE,stateChange);
								  
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}
		
		function onItemDoubleClick()
		{
			ExternalInterface.call("ASReadMail", mail_data.mail_id);
		}

		function onSelectMail()
		{
			mail_select_checkbox.selected = !mail_select_checkbox.selected;
			ExternalInterface.call("ASSelectMail", mail_data.mail_id, mail_select_checkbox.selected);
		}
		
		function updateData(data:Object):void
		{
				  
			mail_data = data as MailData;
			
			if (mail_data)
			{				
				visible = true;
				var iconFrm:String;
				if(mail_data.mail_icon == 0)
				{
					iconFrm = "new_mail";
					mail_title_txt.textColor=0xf1fcff;
					mail_valid_days_txt.textColor=0xf1fcff;
				}
				else if(mail_data.mail_icon == 1)
				{
					iconFrm = "old_mail";
					mail_title_txt.textColor=0x7e7e7e;
					mail_valid_days_txt.textColor=0xadadad;
				}
				else if(mail_data.mail_icon == 2)
				{
					iconFrm = "sys_mail";
				}
				
				mail_icon.gotoAndStop(iconFrm);
				if(mail_data.mail_icon == 1){
					mail_from_txt.htmlText = "<font color='#adadad'>"+mail_data.mail_from_txt+"</font>";
				}else{
					mail_from_txt.htmlText = "<font color='#f1fcff'>"+mail_data.mail_from_txt+"</font>";
				}
				
				mail_title_txt.htmlText = mail_data.mail_title_txt;
				
				mail_valid_days_txt.text = mail_data.mail_valid_days_txt;
				mail_has_items_mc.visible = mail_data.mail_has_items_mc;
				mail_select_checkbox.selected = mail_data.mail_selected;
			}
			else
			{
				visible = false;
			}
		}
		
		override public function setActualSize(newWidth:Number, newHeight:Number):void 
		{
			if (super.width != newWidth || _width != newWidth) 
			{
				super.width = _width = newWidth;
			}

		    if (super.height != newHeight || _height != newHeight) 
			{
				super.height = _height = newHeight;
			}
		}
	}

}