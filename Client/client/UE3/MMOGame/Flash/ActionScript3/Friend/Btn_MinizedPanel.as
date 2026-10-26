package ActionScript3.Friend {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	
	
	public class Btn_MinizedPanel extends Button {
		public var effect:MovieClip;
		public var head:MovieClip;
		override protected function configUI():void {
			super.configUI();
			effect.mouseChildren=false;
			effect.mouseEnabled=false;
		}
		
		public function setHeadImg(frame:int):void
		{
			head.gotoAndStop(frame);
		}
		override public function setActualSize(newWidth:Number, newHeight:Number):void {
				if (super.width != newWidth || _width != newWidth) {
					super.width = _width = newWidth;
				}

				if (super.height != newHeight || _height != newHeight) {
					super.height = _height = newHeight;
				}
		}
	}
	
}
