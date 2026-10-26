/********************************************************************
Created:2013/04/18
Filename: CommonTip
file ext:as
Author:hemu@snda
Purpose:Tips系统View CommonTip控件
*********************************************************************/

package ActionScript3.Tips
{

	import ActionScript3.MyPanel;

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextFieldEx;
	import ActionScript3.Tips.CommonTipData;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextFormat;

	public class CommonTip extends MyPanel
	{
		public var tips_item_text:TextField;
	    public var tips_item_text2:TextField;
		public var tips_item_text3:TextField;
		public var TipsBg:MovieClip;
		
		public var TipHeight:int;
		public var TipWidth:int = 134;
		public var SpacingH:int = 20;
		public var OrigTextFieldWidth:int = TipWidth - SpacingH;
		
		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren=false;
			this.mouseEnabled=false;
			tips_item_text2.visible=false;
			tips_item_text3.visible=false;
			tips_item_text.autoSize = TextFieldAutoSize.LEFT;
			tips_item_text.wordWrap = true;
			
			//trace(this.y+"------CommonTip  configUI:"+this.x);
/*            var testString = "asd所有部位强化为所有部位强化为所有部位强化为强<BR>化激\n活sadsadsad<p><font color='#1eff00' size='18' > - <font color='#0070dd'>飞鹰</font></font></p>";
			testString += "<p><font color='#1eff00' size='13'>条件：所有部位强化为s所有部<font color='#0070dd'>飞鹰纹</font></font></p>";
			testString += "<p align='left'><font color='#1eff00'>效果：力量+5</font></p>";
			testString += "<p>            <font color='#1eff00'>耐力+500</font></p>";*/

/*			var testString:String ="比奇省";
			SetConstWidthTips( testString ,1);*/
			
			//SetAutoSizeContent( "c" );
			var str:String = "订单号:14696994301469699430<br/>挂单时间:17:52<br/>挂单总量:1<br/>成交量:0";
			SetConstWidthTips(str)
		}
		
		public function SetConstWidthTips( str:String,type:int=0 ):void
		{
			if(type==1)
			{
				tips_item_text2.visible=true;
				tips_item_text3.visible=false;
				tips_item_text.visible=false;
				this.gotoAndStop(2);
			    tips_item_text2.htmlText = str;
				TipWidth=133;
				TipHeight=38;
				updateForMat();
			}
			else if(type==2)
			{
				tips_item_text.visible=false;
				tips_item_text2.visible=false;
				tips_item_text3.visible=true;
				tips_item_text3.htmlText=str;
				TipHeight=25;
				this.gotoAndStop(3);
				if(tips_item_text3.text.length>5)
				{
			        TipWidth = tips_item_text3.textWidth+4;
				}
				else
				{
					TipWidth=115;
				}
				tips_item_text3.width=TipWidth;
			    this.width = TipWidth;
			    TipsBg.width=TipWidth;
			}
			else
			{
				tips_item_text.wordWrap = true;
				tips_item_text.visible=true;
				tips_item_text2.visible=false;
				tips_item_text3.visible=false;
				this.gotoAndStop(1);
			    tips_item_text.htmlText = str;
				DefineWidthByMaxLine(str);
			    Resize();
			}
		}

		public function updateForMat():void
		{
			var format:TextFormat=tips_item_text2.defaultTextFormat;
			if(tips_item_text2.text.length<4)
			{
				format.letterSpacing=2;
			}
			else
			{
			    format.letterSpacing=0;
			}
			tips_item_text2.setTextFormat(format);
			tips_item_text2.defaultTextFormat=format;
		}
		public function updateContent(str:String):void
		{//如果文本长度大于9的话，将自动换行
			if(tips_item_text.text.length>9)
			{
				tips_item_text.width=130;
				tips_item_text.htmlText=str;
			}
			else
			{
				tips_item_text.wordWrap = true;
			    tips_item_text.htmlText = str;
			    tips_item_text.autoSize = TextFieldAutoSize.LEFT;
			}
		}

        //更新多行文本
		public function SetAutoSizeContent( str:String )
		{
			tips_item_text.visible=true;
			tips_item_text2.visible=false;
			tips_item_text.wordWrap = false;
			tips_item_text.htmlText = str;
			tips_item_text.autoSize = TextFieldAutoSize.LEFT;
			Resize();
		}
		
		function CutString( txt:String , skiptextStart:String ,skiptextEnd:String):String
		{
			while(1)
			{
				var startpos = txt.indexOf( skiptextStart, 0 );
				if(startpos < 0)
					break;
				var endpos = txt.indexOf( skiptextEnd, startpos+1);
				if(endpos < 0)
					break;
				txt = txt.slice( 0,startpos) + txt.slice( endpos+1 );
			}
			return txt;
		}
		function DefineWidthByMaxLine(txt:String)
		{
			txt = CutString( txt,"<font",">" );		
			txt = CutString( txt,"</font",">" );			
			txt = CutString( txt,"<p",">" );
			txt = CutString( txt,"<FONT",">" );		
			txt = CutString( txt,"</FONT",">" );			
			txt = CutString( txt,"<P",">" );
			
			var offPos:int = 0;
			//trace("DefineWidthByMaxLine+++++++" +txt  );
			var strMaxLine : String = new String;
			var strTemp : String = new String;
			while(1)
			{
				var pPos = txt.indexOf( "</P" , offPos );
				var pospp =  txt.indexOf( "</p" , offPos );
				var posBr = txt.indexOf( "<BR>" , offPos );
				var posbr = txt.indexOf( "<br>" , offPos );
				var posn = txt.indexOf( "\n" , offPos );
				
				if((pPos > pospp&&pospp >= 0)||(pPos < 0))
					pPos = pospp;
				if((pPos > posBr&&posBr >= 0)||(pPos < 0))
					pPos = posBr;
				if((pPos > posbr&&posbr >= 0)||(pPos < 0))
					pPos = posbr;
				if((pPos > posn&&posn >= 0)||(pPos < 0))
					pPos = posn;
				
				if(pPos < 0)
				{
					strTemp = txt.slice( offPos );
					if(strMaxLine.length < strTemp.length)
						strMaxLine = strTemp;
					break;
				}
				
				if(pPos >= 0)
				{
					strTemp = txt.slice( offPos , pPos );
					offPos = pPos+1;
					//trace("offPos = " +offPos + "pPos = "  + pPos);
				}
		
				if(strMaxLine.length < strTemp.length)
					strMaxLine = strTemp;
				
			}
			//trace("strMaxLine+++++++" +strMaxLine  );
			if(strMaxLine.length > 36)
				tips_item_text.width = OrigTextFieldWidth*2;
			else if(strMaxLine.length > 24)
				tips_item_text.width = OrigTextFieldWidth*1.5;
			else
				tips_item_text.width = OrigTextFieldWidth;
		}
		
		public function Resize():void
		{
			TipHeight = tips_item_text.textHeight + SpacingH;
			TipWidth = tips_item_text.textWidth + SpacingH;
			
			this.width = TipWidth;
			this.height = TipHeight;
			
			TipsBg.height = TipHeight;
			TipsBg.width = TipWidth;
		}
	}
}