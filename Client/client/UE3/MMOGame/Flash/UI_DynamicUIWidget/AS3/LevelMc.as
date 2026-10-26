package UI_DynamicUIWidget.AS3 {
	
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.utils.getDefinitionByName;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.motion.Tween;
	import flash.events.Event;
	
	
	public class LevelMc extends UIComponent {
		
		public var txtLev:MovieClip;
		public function LevelMc() {
			this.addFrameScript(46,handler);
		}
		
		private function handler():void
		{
			this.visible = false;
		    this.gotoAndStop(1);
			this.dispatchEvent(new Event("CloseLevelUp"));
		}
		
		public function updateData(lev:String):void
		{
			clear();
			this.visible=true;
			this.gotoAndPlay(1);
			//sound
			playSound("LevelUp_FX");
			txtLev.alpha=0;
			var tw:Tween=new Tween(400,txtLev,{alpha:1});
			var str:Array=lev.toString().split('');
			var i:int=0;
			var l:int=str.length;
			if(l>0){
				for (i = 0; i < l; i++) 
				{
					var n:int=str[i];
					var bit:Bitmap=new Bitmap( new (getDefinitionByName("Img_"+n)));
					bit.x=i*26;
					(txtLev.lev_1 as MovieClip).addChild(bit);
				}
			}
		}
		
		private function clear():void
		{
			var l:int=(txtLev.lev_1 as MovieClip).numChildren;
			var i:int=0;
			for (i = 0; i < l; i++) 
			{
				(txtLev.lev_1 as MovieClip).removeChildAt(0);
			}
		}
	}
	
}
