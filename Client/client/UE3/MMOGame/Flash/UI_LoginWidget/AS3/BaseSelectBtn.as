package UI_LoginWidget.AS3 {
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip;
	
	public class BaseSelectBtn extends RadioButton {

		override protected function configUI():void
		{
			super.configUI();
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
