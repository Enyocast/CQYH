package ActionScript3.Widget{
	
	import flash.events.Event;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextEventEx;

	
	public class ChatListItem extends UIComponent
	{
		public var listItem_tf:TextField;
		public var line:int;//每行文本行数
		public var blFace:Boolean=false;
		override protected function configUI():void
		{
			super.configUI();
			onRmoved();
			listItem_tf.mouseWheelEnabled=false;
			listItem_tf.wordWrap=true;
			listItem_tf.addEventListener(TextEvent.LINK, onLinkCallBack);
			listItem_tf.addEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			listItem_tf.addEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			listItem_tf.styleSheet=new StyleSheet();
		}
		
		public function onRmoved():void
		{
			listItem_tf.removeEventListener(TextEvent.LINK, onLinkCallBack);
			listItem_tf.removeEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			listItem_tf.removeEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);			
		}

		function onLinkOverCallBack(e:TextEventEx):void
		{
			//this.dispatchEvent(new Event("test123"));
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			//ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx):void
		{
			//this.dispatchEvent(new Event("test124"));
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			//ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent):void
		{
			if( (e is TextEventEx) )
			{
				var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
				var buttonIdx:int = (e as TextEventEx).buttonIdx;
				ExternalInterface.call( "ASLinkCallBack" , commandParameter , buttonIdx );
			}
		}
		
		public function UpdateData( data:Object ):void
		{
			listItem_tf.height=150;
			//listItem_tf.htmlText = "<img src='img://MMO_UIIcon.ChatChannelIcon.ChatChannelNear'><FONT COLOR='#f6f6f6'> 大剑战士 : 锤炼筋骨！ </FONT><br>";
			listItem_tf.htmlText = data.htmlText;
			listItem_tf.visible  = true;
			line=listItem_tf.numLines;
			if(listItem_tf.textHeight/line>24)
			{//判断文字中是否有表情（如果有表情一行文本占据2）
				listItem_tf.height=listItem_tf.textHeight+3;//固定每行22像素
				blFace=true;
			}
			else
			{
				blFace=false;
			    listItem_tf.height=line*22;//固定每行22像素
			}

			height = listItem_tf.height;
		}
	}
}


