
package scaleform.clik.core {
	import flash.events.Event;
	public class UIComponentFullScreen extends UIComponent {
        private var _w:int;
		private var _h:int;
        override protected function configUI():void
		{
			super.configUI();
			root.stage.addEventListener( Event.RESIZE , _ReSizeStage );
			_ReSizeStage(null);
		}
		
		public function _ReSizeStage(evt:Event):void
		{
			_w=root.stage.stageWidth;
			_h=root.stage.stageHeight;
			layou();
		}
		
        protected function layou():void
		{			
		    this.width = _w;
			this.height = _h;
			this.scaleX = _w / 1280;
			this.scaleY = _h / 720;
		}

	}

}
