package UI_SkillbarWidget.AS3 {

	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	
	
	public class MenuSlotBtn extends Button {
		
		
		override protected function configUI():void
		{
			super.configUI();
			(this.getChildByName("_item") as MovieClip).gotoAndStop(1);
			(this.getChildByName("_item") as MovieClip).mouseChildren=false;
			(this.getChildByName("_item") as MovieClip).mouseEnabled=false;
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
