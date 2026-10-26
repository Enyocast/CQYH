package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import ActionScript3.Common.CustomScrollBar;
	
	
	public class ConfigHelp extends UIComponent {
		
		public var txt_dec:TextField;
		public var bar:CustomScrollBar;
		override protected function configUI():void
		{
			super.configUI();
			bar.visible=false;
			//trace(txt_dec.getTextFormat().size,this.scaleX,this.scaleY,txt_dec.scaleX,txt_dec.scaleY);
		}
		
		public function setData(dat:String):void
		{
			txt_dec.htmlText=dat;
			//trace(dat,txt_dec.getTextFormat().size,this.scaleX,this.scaleY,txt_dec.scaleX,txt_dec.scaleY);
			if((txt_dec.textHeight)>=320)
			{
				bar.visible=true;  
			}
			else
			{
				bar.visible=false;
			}
		}
	}
	
}
