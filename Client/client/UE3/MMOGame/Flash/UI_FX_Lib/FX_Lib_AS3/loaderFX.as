package UI_FX_Lib.FX_Lib_AS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flashx.textLayout.formats.Float;
	import scaleform.clik.controls.UILoader;
	
	public class loaderFX extends UIComponent
	{
		public var loader_mc:UILoader;
		
		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			
			//width = 64;
			//height = 64;
		}
		
        /** Set the source of the content to be loaded. */
        [Inspectable(defaultValue="")]
        public function get source():String { trace("=======loaderFX"); return loader_mc.source; }
        public function set source(value:String):void { 
				loader_mc.source = value;
        }		
		
		public function onRmoved(e:Event)
		{
			loader_mc.unload();
			loader_mc = null;
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
		}
		
		public function SetMouseEnabled(e:Boolean)
		{
			loader_mc.mouseEnabled = e;
			if(loader_mc.loader)
				loader_mc.loader.mouseEnabled = e;
			mouseEnabled = e;
		}
	}
}