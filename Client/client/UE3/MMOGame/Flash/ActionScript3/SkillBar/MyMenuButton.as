package ActionScript3.SkillBar {
	
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.utils.getDefinitionByName;
	
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import ActionScript3.Common.Utils.StyleType;
	import flash.filters.GlowFilter;
	
	public class MyMenuButton extends Button {
		
		public var componentList:Array=null;
		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(MouseEvent.ROLL_OUT,rollOutHandler)
			this.addEventListener(MouseEvent.ROLL_OVER,rollOverHandler);
		}
		
		private function rollOutHandler(evt:MouseEvent):void
		{
			this.filters=null;
		}

		public function getGlow():GlowFilter
		{
			var glow:GlowFilter=new GlowFilter(0xffffff,1,2,2,2,1,false,false);
			return glow;
		}
		
	    private function rollOverHandler(evt:MouseEvent):void
		{
			this.filters= [getGlow()];
		}

		//闪烁
		public function Flicker()
		{
			
		}
		
/*		public function clearComponent()
		{
			for( var i:int = 0 ; i < componentList.length ; i++ )
			{
				var mc:DisplayObject =  componentList[i] as DisplayObject;
				if(mc)
				{
					this.removeChild( mc );
				}				
			}
			componentList.splice( 0 , componentList.length );
		}*/
		
		//添加子菜单
		public function AddComponent( comp:String ):void
		{
			componentList=[];
			var compClass:Class = getDefinitionByName(comp) as Class;
			if( compClass )
			{
				var newComp:MovieClip = new compClass;
				newComp.visible=false;
				newComp.name = comp;
				this.addChild( newComp );
				componentList.push(newComp);
			}
		}
		
		public function effect(pl:Boolean):void
		{
			if(pl){
				((this.getChildByName("icon") as MovieClip)._item as MovieClip).gotoAndPlay(1);
			}else{
				((this.getChildByName("icon") as MovieClip)._item as MovieClip).gotoAndStop(1);
			}
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
