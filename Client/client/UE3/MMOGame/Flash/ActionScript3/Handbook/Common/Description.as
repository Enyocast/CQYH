package ActionScript3.Handbook.Common
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class Description extends UIComponent
	{
		public var textField:TextField;
		public var desc_tf:TextField;
		public var btn_decription_sound:Button;
		public var frame_mc:MovieClip;
		
		protected var _soundAvaliable:Boolean = true;
		
		private static const MIN_HEIGHT:Number = 0;//default height in fla is 111 
		private static const MARGIN:Number = 13;
		private static const TEXT_HEIGHT_ONE_LINE:Number = 21;
		
		public function Description()
		{
			super();
		}
		
		public function get soundAvaliable():Boolean
		{
			return _soundAvaliable;
		}

		public function set soundAvaliable(value:Boolean):void
		{
			_soundAvaliable = value;
			btn_decription_sound.visible = _soundAvaliable;
		}

		override protected function configUI():void
		{
			super.configUI();
			btn_decription_sound.addEventListener(MouseEvent.CLICK, onSoundButtonClick, false, 0, true);
		}
		
		private function onSoundButtonClick(evt:MouseEvent):void
		{
			ExternalInterface.call("ASPlayDesciptionSound");
		}
		
		public function setTitle(lable:String):void
		{
			textField.text = lable;
		}
		
		public function updateDescription(info:String):void
		{
			desc_tf.htmlText = info;
			var bottom:Number = desc_tf.numLines * TEXT_HEIGHT_ONE_LINE;
			desc_tf.height = bottom  + MARGIN;
			if(_soundAvaliable){
				btn_decription_sound.y = desc_tf.y + bottom - 6;
				_height = frame_mc.height =  Math.max(MIN_HEIGHT, btn_decription_sound.y + btn_decription_sound.height + MARGIN);
			}else{
				_height = frame_mc.height =  Math.max(MIN_HEIGHT, desc_tf.y + desc_tf.height);
			}
		}
	}
}