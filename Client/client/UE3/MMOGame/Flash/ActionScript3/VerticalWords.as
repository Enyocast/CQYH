package ActionScript3
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.utils.Timer;
	
	public class VerticalWords extends MovieClip
	{
		var _ColumWorldsNum:int = 15;
		
		var _TextField:TextField;
		var _OriginalStr:String;
		var _OriginalStrArray:Array;
		var _RowArray:Array;
		var _CurIndex:int = 0;
		var _OriginalWordsCnt:int;
		var _CurWord:String;
		var _AnimTimer:Timer;
		
		public function VerticalWords()
		{
			super();
			
			_TextField = getChildByName( "_TextField" ) as TextField;

			/*
			_TextField = new TextField();
			this.addChild( _TextField );
			
			_TextField.selectable = false;
			_TextField.mouseEnabled = false;
			
			_TextField.x = 0;
			_TextField.y = 0;
			_TextField.width = width;
			_TextField.height = height;
			_TextField.wordWrap = true;
			_TextField.multiline = true;
			
			var textFmt:TextFormat = new TextFormat();
			textFmt.color = 0xA89787;
			//textFmt.font = "$NewContentFont*";
			textFmt.align = "right";
			textFmt.size = 14;
			_TextField.defaultTextFormat = textFmt;
			*/
			
			//var textStyleSheet:StyleSheet = new StyleSheet();
			//var styleObj:Object = new Object();
			//styleObj.color = "#A89787";
			//styleObj.fontFamily = "$NewContentFont*";
			//styleObj.fontSize = 14;
			//styleObj.textAlign = "right"
			
			//textStyleSheet.setStyle( ".defStyle", styleObj );
			//_TextField.styleSheet = textStyleSheet;
		}
		
		//
		public function SetWorlds( str:String, columWorldCnt:int, animClipTime:int, letterSpacing:int ):void
		{
			var textFmt:TextFormat=_TextField.getTextFormat();
			textFmt.letterSpacing = letterSpacing;
			_TextField.defaultTextFormat = textFmt;
			_TextField.setTextFormat(textFmt);
			_ColumWorldsNum = columWorldCnt;
			_CurIndex = 0;
			
			_OriginalStr = str;
			_OriginalWordsCnt = _OriginalStr.length;
			_OriginalStrArray = _OriginalStr.split("");
			//trace( "================_OriginalStrArray", _OriginalStrArray );
			//trace( "================_OriginalStr", _OriginalStr );

			_RowArray = [];
			
			for( var i:int = 0; i < _ColumWorldsNum; ++i ){
				_RowArray.push("\n");
			}
			
			//
			if( animClipTime <= 0 ){
				for( var j:int = 0; j < _OriginalWordsCnt; ++j ){
					onFrameHandler(null)
				}
			}
			else{
				if( _AnimTimer != null ){
					_AnimTimer.stop();
					_AnimTimer.removeEventListener( TimerEvent.TIMER, onFrameHandler );
					_AnimTimer.removeEventListener( TimerEvent.TIMER_COMPLETE, onComplateHandler );
				}
				_AnimTimer = new Timer( animClipTime, _OriginalWordsCnt );
				//_AnimTimer = new Timer( animClipTime, 11 );
				_AnimTimer.addEventListener( TimerEvent.TIMER, onFrameHandler );
				_AnimTimer.addEventListener( TimerEvent.TIMER_COMPLETE, onComplateHandler );
				_AnimTimer.start();
			}
		}
		
		//
		function onFrameHandler( evt:TimerEvent ):void
		{
			_CurWord = "";
			_RowArray[ _CurIndex % _ColumWorldsNum ] = _OriginalStrArray[ _CurIndex ] + _RowArray[ _CurIndex % _ColumWorldsNum ];
			
			for( var i:int = 0; i < _ColumWorldsNum; ++i ){
				_CurWord += _RowArray[i];
				//trace( "ROW"+i+":", _RowArray[i], _RowArray[i].length );
			}
			_TextField.text = _CurWord;
			++_CurIndex;
		}
		
		//
		function onComplateHandler( evt:TimerEvent ):void
		{
			_AnimTimer.stop();
			_AnimTimer.removeEventListener( TimerEvent.TIMER, onFrameHandler );
			_AnimTimer.removeEventListener( TimerEvent.TIMER_COMPLETE, onComplateHandler );
			_AnimTimer = null;
		}
	}
}