package ActionScript3
{
	import flash.events.Event
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.FaceMap;
	
	public class MyBubbleText extends UIComponent
	{
		public var tf_TalkContent:TextField;
		public var bg_mc:MovieClip;
		
		static var MAX_TIME:int = 4000;
		//static var OriginText_W:int = 13;
		static var ORIGIN_TEXT_H:int = 20;
		static var ONE_WORD_W:int = 6;
		static var WORD_SPACING:int = 1;
		static var ONE_WORD_H:int = 16;
		static var MAX_WIDTH:int = 160;
		static var MIN_WIDTH:int = 58;
		static var BUBBLE_BOTTOM_H:int = 20;
		static var SPACE_X:int = 9;
		static var SPACE_Y:int = 3;
		public var bCanShow:Boolean = false;
		
		var IsInitTime:Boolean = false;
		var TextW:Number;
		var TextH:Number;
		var showTime:int = MAX_TIME;
		var showTimerCountDown:Timer = new Timer(50);
		
		override protected function configUI():void
		{
			super.configUI();
			IsInitTime = false;
			//
			//BeginToShowBubble( "万一碰到顶拔猫，阿金也只有" );
			//BeginToShowBubble( "eee" );
		}
		//
		public function ShowBubble( bubbleText:String )
		{
			var charCnt:uint;
			//所有字数宽度
			tf_TalkContent.width = 4098;
			tf_TalkContent.htmlText = bubbleText;
			var inputTextW = tf_TalkContent.textWidth + 16;
			var inputTextH = tf_TalkContent.textHeight;
			//tf_TalkContent.text = bubbleText;
			
			if( MAX_WIDTH > inputTextW ){
				TextW = inputTextW;
				TextH = inputTextH + 5;
			}
			else{
				TextW = MAX_WIDTH;
				tf_TalkContent.htmlText = bubbleText;
				TextH = Math.ceil( inputTextW / TextW ) * inputTextH + 5;
			}
			
			tf_TalkContent.width = TextW;
			tf_TalkContent.height = TextH;
			tf_TalkContent.y = -BUBBLE_BOTTOM_H - TextH - SPACE_Y;
			
			//container
			width = TextW + SPACE_X + SPACE_X;
			height = TextH + BUBBLE_BOTTOM_H + SPACE_Y + SPACE_Y+SPACE_Y;
			//x = -height;
			
			//background
			bg_mc.width = width;
			bg_mc.height = height;
		}
		
		public function BeginToShowBubble( bubbleText:String ):void
		{

			var charCnt:uint;
			//
			bCanShow = true;
			//显示倒计时
			showTime = MAX_TIME;
			if( !IsInitTime ){
				IsInitTime = true;
				showTimerCountDown.addEventListener(TimerEvent.TIMER, ShowTimerHandle);
			}
			showTimerCountDown.start();
			
			this.alpha = 1;
			
			//所有字数宽度
			tf_TalkContent.width = MAX_WIDTH;
			
			var fomatedBubbleText:String = FormatBubbleText( bubbleText );
			tf_TalkContent.htmlText = fomatedBubbleText;
			var inputTextW = tf_TalkContent.textWidth + 4;
			var inputTextH = tf_TalkContent.textHeight;
			if( MAX_WIDTH > inputTextW ){
				TextW = inputTextW;
				TextH = inputTextH + 5;
			}
			else{
				TextW = MAX_WIDTH;
				tf_TalkContent.htmlText = fomatedBubbleText;
				TextH = Math.ceil( inputTextW / TextW ) * inputTextH + 5;
			}
			
			tf_TalkContent.width = TextW;
			tf_TalkContent.height = TextH;
			tf_TalkContent.y = -BUBBLE_BOTTOM_H - TextH - SPACE_Y+2;
			
			//container
			width = TextW + SPACE_X + SPACE_X;
			height = TextH + BUBBLE_BOTTOM_H + SPACE_Y + SPACE_Y+SPACE_Y;
			//x = -height;
			
			//background
			bg_mc.width = width;
			bg_mc.height = height;
           trace(tf_TalkContent.textWidth+"Bubble Text :" + tf_TalkContent.width + ", " + tf_TalkContent.height + ", BG :" + bg_mc.width + "," + bg_mc.height);
			//bg_mc.x = 0;
			//bg_mc.x = tf_TalkContent.x;
			//
			//tf_TalkContent.x = -50.45;
			//
			ExternalInterface.call( "ASTrace", "Bubble Text :" + tf_TalkContent.width + ", " + tf_TalkContent.height + ", BG :" + bg_mc.width + "," + bg_mc.height);
		}

		function FormatBubbleText( bubbleText:String ):String
		{
			var faceCount:int = FaceMap.getFaceMapCount();
			
			for( var i:int = 0 ; i < faceCount ; i++ )
			{
				var faceString:String = FaceMap.getFaceString(i);
				
				var pos:int = bubbleText.indexOf(faceString);
				//ExternalInterface.call( "ASTrace", "Bubble text has Img: "+faceString+" in:"+pos );
				while( pos >= 0 )
				{
					bubbleText = bubbleText.slice( 0 , pos ) + "<IMG SRC='img://MMO_UIFace."+i+"'>" + bubbleText.slice( pos + faceString.length ); 
					pos = bubbleText.indexOf(faceString);
				}
			}
			//ExternalInterface.call( "ASTrace", bubbleText );
			return bubbleText;
		}
		//----------------------------------------------------------------------
		function ShowTimerHandle( e:Event )
		{
			if(showTime <= 1000)
			{
				this.alpha -= 0.05;
			}
			showTime = showTime - 50;
			
			if (showTime <= 0 && this.alpha <= 0)
			{
				showTime = 0;
				showTimerCountDown.stop();
				bCanShow = false;
				visible = false;
				ExternalInterface.call( "ASTrace", "Bubble hide :"+ visible );
				ExternalInterface.call( "BubbleShowedOver", this );
			}
		}
		//
		function TuneTextFieldWidth( text:String )
		{
			var rtnWidth:uint = 0;
			var chnW:uint = ONE_WORD_W + ONE_WORD_W + WORD_SPACING;
			var enW:uint = ONE_WORD_W + WORD_SPACING;
			var isCharChn:Boolean = false;
			var lastCharW:uint = 0;
			//var char:String;
			//var pattern:RegExp = /^[\u4E00-\u9FA5\uF900-\uFA2D]+$/;
			
			for( var i:int = 0; i < text.length; ++i )
			{
				//char = text.charAt( i );
				//isCharChn = pattern.test( char );
				isCharChn = ( text.charCodeAt( i ) >= 1000 );
				if( isCharChn ){
					rtnWidth += chnW;
					//trace(char +"is C");
				}
				else{
					rtnWidth += enW;
					//trace(char +"is NC");
				}
				
				//
				if( rtnWidth > MAX_WIDTH ){
					rtnWidth = MAX_WIDTH;
					break;
				}
			}
			
			TextW = rtnWidth;
			
			//太短
			if( TextW < MIN_WIDTH ){
				TextW = MIN_WIDTH;
			}
		}
		//
		function TuneTextFieldWH( text:String ):uint
		{
			var rtnWidth:uint = 0;
			var chnW:uint = ONE_WORD_W + ONE_WORD_W + WORD_SPACING;
			var enW:uint = ONE_WORD_W + WORD_SPACING;
			var isCharChn:Boolean = false;
			var lastCharW:uint = 0;
			var firstLineWidth:uint = 0;
			//var char:String;
			//var pattern:RegExp = /^[\u4E00-\u9FA5\uF900-\uFA2D]+$/;
			
			for( var i:int = 0; i < text.length; ++i )
			{
				//char = text.charAt( i );
				//isCharChn = pattern.test( char );
				isCharChn = ( text.charCodeAt( i ) >= 1000 );
				if( isCharChn ){
					rtnWidth += chnW;
					//trace(char +"is C");
				}
				else{
					rtnWidth += enW;
					//trace(char +"is NC");
				}
				
				//
				if( firstLineWidth == 0 && rtnWidth > MAX_WIDTH ){
					firstLineWidth = rtnWidth;
					trace( "first Line Width : " + firstLineWidth );
				}
			}
			
			TextW = rtnWidth;
			TextH = ORIGIN_TEXT_H;
			
			//修正宽高
			lastCharW = ( isCharChn ? chnW : enW );
			if( TextW > MAX_WIDTH ){
				//太宽
				TextH += Math.floor( ( TextW -1 ) / MAX_WIDTH ) * ONE_WORD_H + ONE_WORD_H;
				//trace( "Too wide : " + Math.floor( TextW / MAX_WIDTH ) + "width: " + TextW );
				TextW = MAX_WIDTH;
			}
			//太短
			if( TextW < MIN_WIDTH ){
				TextW = MIN_WIDTH;
			}
			
			return rtnWidth;
		}
		//
		function GetTextCount( text:String ):uint
		{
			var rtnCnt:uint = 0;
			//var char:String;
			//var pattern:RegExp = /^[\u4E00-\u9FA5\uF900-\uFA2D]*$/;
			
			for( var i:int = 0; i < text.length; ++i )
			{
				//char = text.charAt( i );
				//if( pattern.test( char ) ){
				if( text.charCodeAt( i ) >= 1000 ){
					rtnCnt += 2;
					//trace(char +"is C");
				}
				else{
					rtnCnt +=1;
					//trace(char +"is NC");
				}
			}
			
			return rtnCnt;
		}
	}//end of class
}