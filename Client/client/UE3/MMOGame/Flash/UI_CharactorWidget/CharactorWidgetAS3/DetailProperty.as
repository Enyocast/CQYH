package UI_CharactorWidget.CharactorWidgetAS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyScrollPanel;
    import ActionScript3.Common.CustomScrollBar;
    import scaleform.clik.controls.ScrollingView;
	
	public class DetailProperty extends UIComponent {

		public var AttributeContent:MyScrollPanel;
		public var _scrollingView:ScrollingView;
		public var scrollBar:CustomScrollBar;
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function update():void
		{
			_scrollingView.displayMc=AttributeContent;
		}
		
		public function clear():void
		{
			_scrollingView.scrollBar.position=0;
		}
	}
	
}
