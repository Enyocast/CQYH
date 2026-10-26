package ActionScript3.Common  {
	import flash.text.TextField;
	import flash.filters.GlowFilter;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	public class CustomTextField extends TextField {
        private var _textFormat:TextFormat;
        private var _glowFilter:GlowFilter;
		public function CustomTextField() {
			super();
			_textFormat=new TextFormat();
			_glowFilter=new GlowFilter(0x000000,1,1,1,10);
			this.filters=[_glowFilter];
			this.defaultTextFormat=_textFormat;
		}
		
		public function set Glow(value:uint):void
		{
			_glowFilter.color=value;
			this.filters=[_glowFilter];
		}
		
		public function set align(value:TextFormatAlign):void
		{
			_textFormat.align=value;
			defaultTextFormat=_textFormat;
		}
		
		public function set color(value:uint):void
		{
			_textFormat.color=value;
			defaultTextFormat=_textFormat;
		}
		
		override public function defaultTextFormat(format:TextFormat):void
		{
			if(this.styleSheet!=null){
				this.styleSheet=null;
			}
			super.defaultTextFormat=format;
		}

	}
	
}
