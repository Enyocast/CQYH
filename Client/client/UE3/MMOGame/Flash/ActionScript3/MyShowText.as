

package ActionScript3
{
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.utils.Constraints;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.Button;
	import scaleform.clik.ui.InputDetails;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	import scaleform.gfx.Extensions;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.text.StyleSheet;
	import flash.events.TextEvent;
	import ActionScript3.FaceMap;
	import scaleform.clik.controls.TextArea;
	
	public class MyShowText extends TextArea
	{
		var _CurNo:Number;

		var LimitLine:int;
		override protected function configUI():void 
		{
			super.configUI();
			_usingDefaultTextFormat=false;
			Extensions.enabled = true;
			LimitLine = 100;
			_isHtml = true;
			this.defaultTextFormat
			this.textField.addEventListener(TextEvent.LINK, onLinkCallBack);
			this.textField.addEventListener(TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			this.textField.addEventListener(TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			this.textField.styleSheet = new StyleSheet;
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
			if( (e is TextEventEx) )
			{
				var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
				var buttonIdx:int = (e as TextEventEx).buttonIdx;
				ExternalInterface.call( "ASLinkCallBack" , commandParameter , buttonIdx );
			}
		}
		
		public function NewAppendHtml( addtext:String ):void
		{
			_text = "";
			
			var faceCount:int = FaceMap.getFaceMapCount();
			for( var i:int = 0 ; i < faceCount ; i++ )
			{
				var faceString:String = FaceMap.getFaceString(i);
				var pos:int = addtext.indexOf(faceString);
				while( pos >= 0 )
				{
					addtext = addtext.slice( 0 , pos ) + "<IMG SRC='img://MMO_UIFace."+i+"'>" + addtext.slice( pos + faceString.length ); 
					pos = addtext.indexOf(faceString);
				}
			}
			//这里for下
			appendHtml(addtext);
			turnToBottom(); //移到最下
		}

		override public function appendHtml( addtext:String):void 
		{
			_text += addtext  ;
			_CurNo = 0;
			textField.htmlText = _text;
		}
		
		private function turnToBottom():void
		{
			position = textField.maxScrollV; //add by york
		}
		
		override protected function handleTextChange(event:Event):void {
			
			turnToBottom();
            super.handleTextChange(event);
        }

		public function preProcessSendContent():Boolean
		{ 
		    return false;
	     }
		
	}
}