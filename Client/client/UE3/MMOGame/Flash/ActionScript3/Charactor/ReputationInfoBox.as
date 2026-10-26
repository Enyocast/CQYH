package ActionScript3.Charactor
{
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import flash.utils.getDefinitionByName;
	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.events.ButtonEvent;	
	
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;	
	import flash.text.StyleSheet;
	import flash.events.TextEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.Common.CustomScrollBar;


	public class ReputationInfoBox extends UIComponent
	{
		public var tf_Message:TextField;
		public var sb_Message:CustomScrollBar;
		//public var btn_Close:Button;
		public var _bg:MyWindowsFrame;
		public var title_name:TextField;

		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			_bg.btn_close.addEventListener("click", handleOnClosed, false ,0, true);
			tf_Message.addEventListener(TextEvent.LINK, onLinkCallBack);
			tf_Message.addEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			tf_Message.addEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			tf_Message.styleSheet = new StyleSheet;
			sb_Message.scrollTarget=tf_Message;
/*			var Message:String="额鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅谔\n谔鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n额鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅谔\n谔鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅谔谔鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅谔谔鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅谔谔\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅谔谔鹅\n鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅鹅额";
			tf_Message.htmlText = Message;*/
		}
		
		public function onRmoved(e:Event)
		{
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			_bg.btn_close.removeEventListener("click", handleOnClosed);
			
			tf_Message.removeEventListener(TextEvent.LINK, onLinkCallBack);
			tf_Message.removeEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			tf_Message.removeEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);						
		}
			
		public function setInfoData(TitleName:String, Message:String, bShow:Boolean):void
		{
				title_name.text	= TitleName;
				tf_Message.htmlText = Message;
				visible = bShow;			
		}
		
		public function updateInfoData(TitleName:String, Message:String):void
		{
				if( TitleName == _bg.tF_windowTitle.text)
				{
					title_name.text = "";
					visible = false;
				}
				else{
					title_name.text = TitleName;
					tf_Message.htmlText = Message;
					visible = true;
				}
		}		
		
		public function updateData(data:Object):void
		{
			if (data)
			{
				title_name.text	= data.TitleName;
				tf_Message.htmlText = data.Message;
				visible = true;
			}
			else
			{
				title_name.text	 = "";
				tf_Message.htmlText = "";
			}
		}

		public function handleOnClosed( event:Event ):void
		{
			visible = false;
		}
		
		

		function onLinkOverCallBack(e:TextEventEx)
		{
			trace("+++++++++++onLinkOverCallBack");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx)
		{
			trace("-----------onLinkOverCallBack");
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组

			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent)
		{
			trace("-----------onLinkCallBack");
			if( (e is TextEventEx) )
			{
				var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
				var buttonIdx:int = (e as TextEventEx).buttonIdx;
				ExternalInterface.call( "ASLinkCallBack" , commandParameter , buttonIdx );
			}
		}				
	}
}


