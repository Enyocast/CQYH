package UI_Hang.AS3 {
	
	import scaleform.clik.controls.RadioButton;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.utils.clearInterval;
	import flash.utils.setInterval;
	
	public class BarKey extends RadioButton {
		
		public var keyname:TextField;
		public var keyappend:TextField;
		public var type_id:int;
		//public var btn_left:Button;
		//public var btn_right:Button;
		private var format:TextFormat;
		private var _bool:Boolean=false;
		private var timer:uint;
		
		override protected function configUI():void
		{
			super.configUI();
			format=keyname.getTextFormat();
		}
		
		public function clear():void
		{
			clearInterval(timer);
			_bool=false;
			if(format){
				format.underline=_bool;
				format.color=0xcfdde8;
				keyname.setTextFormat(format);
			}
		}
		
		public function show():void
		{
			clear();
			if(this.selected){
				timer=setInterval(step,600);
			}
		}

		private function step():void
		{
			_bool=!_bool;
			format.underline=_bool;
			format.color=0xFFF5DD;
			keyname.setTextFormat(format);
		}
		
		public function update(dat:String,alt:String,type:int):void
		{
			keyname.visible=true;
			keyappend.text=alt;
			type_id=type;
			if(dat.length>2){
				   format.size=14;
				   keyname.y=17; 
			   }else{
				  keyname.y=12;
				  format.size=20; 
			   }
			   keyname.text=dat;
			   keyname.setTextFormat(format);

		}
		
		public function removeEvent():void
		{
			removeEventListener(MouseEvent.MOUSE_DOWN, handleMousePress, false);
			removeEventListener(MouseEvent.CLICK, handleMouseRelease, false);
			removeEventListener(MouseEvent.DOUBLE_CLICK, handleMouseRelease, false);
		}
	}
	
}
