package UI_MsgBall.AS3 {
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.display.Sprite;
	
	public class HintInfoAlert extends Button {

		public var numTF:TextField;
		public var msgNumBg:MovieClip;
		//public var effect:Sprite;
		override protected function configUI():void {
			super.configUI();
/*			effect=new Sprite();
			effect.mouseChildren=false;
			effect.mouseEnabled=false;
			this.addChild(effect);*/
			msgNumBg.mouseChildren=false;
			msgNumBg.mouseEnabled=false;
		}
		
		//重写宽度，这样每帧的图片宽高不一致的问题将解决
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
