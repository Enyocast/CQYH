package UI_ChatWidget.AS3 {
	import flash.desktop.Clipboard;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.system.System;
	import flash.text.TextField;
	import flash.text.TextFieldType;
	import flash.text.TextFormat;
	import flash.ui.Keyboard;
	import flash.ui.KeyboardType;
	
	import ActionScript3.FaceMap;
	
	import scaleform.clik.constants.InputValue;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.managers.FocusHandler;
	import scaleform.clik.ui.InputDetails;
	import scaleform.gfx.Extensions;
	import scaleform.gfx.SystemEx;
	import flash.events.TextEvent;
	
	public class ChatTextField extends TextInput {

		public var ctrlPush:Boolean=false;
		private var _caretIndex:int;//纪录每次赋值的光标
		override protected function configUI():void { 
			super.configUI();
			_usingDefaultTextFormat=false;
			Extensions.enabled = true;
			textField.maxChars=120;
			textField.addEventListener(MouseEvent.CLICK,MClickCallBack);
			this.addEventListener(KeyboardEvent.KEY_UP,KUpCallBack);
			this.addEventListener(KeyboardEvent.KEY_DOWN,KDownCallBack);	
		}
		
		public function MClickCallBack(evt:MouseEvent):void
		{
			if(textField.length>0){
				setTextFieldFocus();
				getCaretStr(textField.caretIndex-1,false);//设置光标
			}else{
				setTextFieldFocus();
			}
			SetcaretIndex();
			
		}
		
		private function setTextFieldFocus():void
		{
			if(root.stage.focus!=textField)
			{
				FocusHandler.getInstance().setFocus( textField );
			}
		}
		public function clear():void
		{
			textField.htmlText="";
			textField.text="";
			this._isHtml=false;
			_text="";
		}
		
		private function SetcaretIndex():void
		{
			_caretIndex=textField.caretIndex;
		}
		
		override public function handleInput(event:InputEvent):void
		{
			super.handleInput(event);
			var details:InputDetails = event.details;
			if (details.code == Keyboard.CONTROL)
			{
				if(details.value == InputValue.KEY_DOWN)
				{
					ctrlPush = true;
					textField.type = TextFieldType.DYNAMIC;
				}
				else if(details.value == InputValue.KEY_UP)
				{
					ctrlPush = false;
					textField.type = TextFieldType.INPUT;
				}
			}
		}
		
		public function getCaretStr(caretIndex:int,bool:Boolean=false,left:Boolean=false):void
		{
			var str:String=textField.text.substr();
			var str1:String="";
			var endPos:int;
			var lastPos:int;
			var startPos:int;
			var i:int=0;
			for(i=0;i<6;i++){
				if(str.indexOf("<")>-1 && str.indexOf(">")>-1){
					if((caretIndex>=(str.indexOf("<")+lastPos)) && (caretIndex<=(str.indexOf(">")+lastPos))){
						startPos=str.indexOf("<")+lastPos;
						endPos=str.indexOf(">")+lastPos+2;
						str1=str.slice(str.indexOf("<")+1,str.indexOf(">"));
						if(_text.indexOf(str1)>-1){
							if(bool==false){
								if(left==true){
									var pos:int=startPos;
									if(pos<0){
										pos=0;
									}
									textField.setSelection(pos,pos);
								}else{
									textField.setSelection(endPos,endPos+1);
								}
							}else{
								textField.setSelection(startPos,endPos);
							}
						}
					}else{
						lastPos+=str.indexOf(">")+1;
						str=str.slice(str.indexOf(">")+1);
					}
				}else{
					break;
				}
			}
		}
		
		public function filterNewLine(b:Boolean):void
		{
			var txt:String = text;
			if(b==true){
				txt = CutKerning( txt," FACE=\"Source Han Sans CN Medium\"");
				txt = CutKerning( txt," FACE=\"$NewContentFont\"");
				txt = CutString( txt,"SIZE="," " );
				txt = CutKerning( txt,"KERNING=\"0\"");
				txt = CutKerning( txt,"COLOR=\"#FFF9F2\"");
			}else{
				txt = CutString( txt,"<FONT",">" );		
				txt = CutString( txt,"</FONT",">" );			
			}
			txt = CutString( txt,"<P",">" );
			txt = CutString( txt,"</P",">" );
			txt = CutString( txt,"<TEXTFORMAT",">" );		
			txt = CutString( txt,"</TEXTFORMAT",">" );
			text = txt;
		}
		
		public function CutKerning( txt:String , skiptextStart:String ):String
		{
			while( txt.indexOf( skiptextStart, 0 ) >=0 )
			{
				var startpos:int = txt.indexOf( skiptextStart);
				var endpos:int=startpos+skiptextStart.length;
				txt = txt.slice( 0,startpos)+txt.slice( endpos);
			}
			return txt;
		}
		
		function CutString( txt:String , skiptextStart:String ,skiptextEnd:String):String
		{
			while( txt.indexOf( skiptextStart, 0 ) >=0 )
			{
				var startpos = txt.indexOf( skiptextStart, 0 );
				var endpos = txt.indexOf( skiptextEnd, startpos+1);
				txt = txt.slice( 0,startpos) + txt.slice( endpos+1 );
			}
			return txt;
		}

		
		private function KUpCallBack(e:KeyboardEvent):void
		{
			var txt:TextField = e.target as TextField;
			if(txt==null)
			{
				return;
			}
			if(e.keyCode == Keyboard.LEFT || e.keyCode==Keyboard.RIGHT){
				
				var left:Boolean=false;
				var car:int=txt.caretIndex;
				if(e.keyCode==Keyboard.LEFT){
					left=true;
					car-=2;
				}else{
					car-=1;
				}
				getCaretStr(car,false,left);
				SetcaretIndex();
			}
			if((e.keyCode>47 && e.keyCode<58) || (e.keyCode>185 && e.keyCode<223))
			{
			    if(_caretIndex==txt.caretIndex)
				{
					txt.setSelection(txt.caretIndex+1,txt.caretIndex+1);
				}
			}
			_caretIndex=txt.caretIndex;
		}
		
		private function KDownCallBack(e:KeyboardEvent):void
		{
			var txt:TextField = e.target as TextField;
			var selectedString:String;
			
			if (e.keyCode == 8)
			{
				getCaretStr(textField.caretIndex-2,true);
				SetcaretIndex();
			}
			else if( e.keyCode == 67 && ctrlPush ) //C
			{
				if(txt.selectionBeginIndex!=txt.selectionEndIndex )
				{
					selectedString = txt.text.slice( txt.selectionBeginIndex , txt.selectionEndIndex );
					copyToClipboard( selectedString );
				}
				SetcaretIndex();
			}
			else if(e.keyCode == 86 && ctrlPush ) //v
			{
				var allTxt:String=textField.text;
				var pasteTxt:String = pasteFromClipboard();
				var pasteTxtleng:int=pasteTxt.length;
				var maxTxt:int=textField.maxChars;//文本上限
				if(allTxt.length>0)
				{
					if(txt.selectionBeginIndex!=txt.selectionEndIndex)
					{
						selectedString = allTxt.slice( textField.selectionBeginIndex , textField.selectionEndIndex );//选中的文本
					    var selectB:String=allTxt.substring(0,textField.selectionBeginIndex);
					    var selectG:String=allTxt.substring(textField.selectionEndIndex);
						allTxt=selectB+selectG;
					}
				   var careB:String=allTxt.substring(0,textField.caretIndex);//光标前文本
				   var careG:String=allTxt.substring(textField.caretIndex);//光标后文本
				   var line:int=textField.caretIndex+pasteTxtleng;
				   var max:int=textField.text.length+pasteTxtleng;
				   var gbwb:int=careB.length+careG.length+pasteTxtleng;
				   if(gbwb>=maxTxt)
				   {//当所有文本上限等于可输入上限的时候，特殊处理
					   var dyzf:int=(gbwb-maxTxt);
					   if(dyzf>=0)
					   {
						   pasteTxt=pasteTxt.substr(0,pasteTxtleng-dyzf);
					   }
					   else
					   {
						   pasteTxt="";
					   }
					   pasteTxtleng=pasteTxt.length;
					   line=textField.caretIndex+pasteTxtleng;
				   }
				  clear();
				  appendText(careB+pasteTxt+careG);
				  textField.setSelection(line,line);
				}
				else
				{
					if(pasteTxtleng>maxTxt)
					{
					    pasteTxt=pasteTxt.substr(0,maxTxt);
						pasteTxtleng=pasteTxt.length;
					}
					appendText(pasteTxt);
				    MoveToEnd();
				}
				SetcaretIndex();
			}
			else if( e.keyCode == 88 && ctrlPush ) //x
			{
				if(txt.selectionBeginIndex!=txt.selectionEndIndex)
				{
					selectedString = txt.text.slice( txt.selectionBeginIndex , txt.selectionEndIndex );
					copyToClipboard( selectedString );
					var begin:int=txt.selectionBeginIndex;
					var str:String= txt.text.slice( 0 , txt.selectionBeginIndex ) + txt.text.slice( txt.selectionEndIndex );
					clear();
					appendText(str);
					textField.setSelection(begin,begin);
				}
				else
				{
					MoveToEnd();
				}
				SetcaretIndex();
			}
		   this.dispatchEvent(new Event("inputcopy"));//通知上层使用了复制粘贴的功能
		   this.setTextFieldFocus();
		   
		}
		
		override protected function handleTextFieldFocusIn(e:FocusEvent):void {
			this.setState("focused");
			if(textField.text==defaultText)
			{
				textField.text="";
			}
			MoveToEnd();
			ExternalInterface.call( "ASFocusInTextInput" , true );
		}
		
		override protected function handleTextFieldFocusOut(e:FocusEvent):void{
			this.setState("default");
			textField.type = TextFieldType.INPUT;
			if(text=="" && defaultText!="")
			{
				textField.text=defaultText;
			}
			ExternalInterface.call( "ASFocusInTextInput" , false );
		}
		
		public function copyToClipboard( txt:String ):void
		{ 
			ExternalInterface.call( "ASCopyToClipboard" , txt );
		}
		
		public function pasteFromClipboard():String
		{
			var ret:String =ExternalInterface.call( "ASPasteFromClipboard" );
			return ret;
		}
		
		override public function appendHtml(value:String):void {
			_isHtml = true;
			_text+=value;
		    textField.htmlText+=value;
			//textField.type = TextFieldType.INPUT;
			MoveToEnd();
		}
		
		public function MoveToEnd():void
		{
			textField.setSelection(textField.text.length,textField.text.length);
			SetcaretIndex();
		}
		
		override public function appendText(value:String):void {
			_text += value;
			_isHtml = false;
			textField.appendText(value);
		}
		override protected function updateTextField():void {
			if (textField.hasEventListener(FocusEvent.FOCUS_IN)) { 
				textField.removeEventListener(FocusEvent.FOCUS_IN, handleTextFieldFocusIn, false);
			}
			textField.addEventListener(FocusEvent.FOCUS_IN, handleTextFieldFocusIn, false, 0, true);
		}
		
		override protected function handleTextChange(event:Event):void {
			_text = _isHtml ? textField.htmlText : textField.text;
			if(_text==""){
		       clear();
			}
			dispatchEvent(new Event(Event.CHANGE));
		}
		
		public function InsertFace( FaceId:int ):void
		{
			var faceString:String = FaceMap.getFaceString(FaceId);
			appendHtml(faceString);
		}
		
	}
	
}
