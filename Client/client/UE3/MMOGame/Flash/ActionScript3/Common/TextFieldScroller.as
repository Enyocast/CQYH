package ActionScript3.Common
{
	import flash.display.DisplayObject;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.ScrollIndicator;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.interfaces.IScrollBar;
	
	/**
	 * Dynamically create scroll bar if need to scrolling view the textfield and hide the scroll bar if no need.
	 * @author wangpenghe.phil
	 * 
	 */	
	public class TextFieldScroller extends UIComponent
	{
		// UI Elements:
		protected var _scrollBar:ScrollIndicator;
		protected var _scrollingTextField:TextField;
		protected var _scrollBarValue:Object;
		
		protected var _TF_origWidth:Number
		protected var _TF_origHeight:Number
		
		public function TextFieldScroller()
		{
			super();
		}
		
		[Inspectable(type = "String")]
		public function get scrollingTextField():Object
		{
			return _scrollingTextField;
		}
		public function set scrollingTextField(value:Object):void
		{
			if (value is String) {
				if (value.toString() == "" || parent == null) { return; }
				value = parent.getChildByName(value.toString());
				if (value == null) { return; }
				_scrollingTextField = value as TextField;
				_TF_origWidth = _scrollingTextField.width;
				_TF_origHeight = _scrollingTextField.height;
			}			
		}
		
		[Inspectable(type = "String")]
		public function get scrollBar():Object
		{
			return _scrollBar;
		}
		public function set scrollBar(value:Object):void
		{
			_scrollBarValue = value;
			invalidate(InvalidationType.SCROLL_BAR);
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function updateScrollingView():void
		{
			draw();
		}
		
		/**
		 * Adjust the size of textfield to show the scroll bar or display the original size of target.
		 * 
		 */		
		override protected function draw():void
		{
			if(_scrollingTextField){
				//check if need scrolling to view.
				if(_scrollingTextField.maxScrollV > _scrollingTextField.bottomScrollV)
				{
					//resize textfield according the size of scroller as template.
					_scrollingTextField.wordWrap = true;
					_scrollingTextField.width = this.x + this.width - _scrollingTextField.x;
					_scrollingTextField.height = this.height;
					//check if need scrolling after size changed.
					if(_scrollingTextField.maxScrollV > _scrollingTextField.bottomScrollV)
					{
						if(_scrollBar == null){
							createScrollBar();
						}
						updateScrollBar();
					}
				}else{
					if(_scrollBar != null){
						_scrollBar.visible = false;
					}
					_scrollingTextField.width = _TF_origWidth;
					_scrollingTextField.height = _TF_origHeight;
				}
			}
			super.draw();
		}
		
		/**
		 *Create scroll bar by the class name or instance name. 
		 * 
		 */		
		protected function createScrollBar():void
		{
			var sb:IScrollBar;
			if (_scrollBarValue is String)
			{
				if (parent != null)
				{
					sb = parent.getChildByName(_scrollBarValue.toString()) as IScrollBar;
				}
				if (sb == null)
				{
					var classRef:Class = getDefinitionByName(_scrollBarValue.toString()) as Class;
					if (classRef)
					{
						sb = new classRef() as IScrollBar;
					}
					if (sb)
					{
						sb.addEventListener(MouseEvent.MOUSE_WHEEL, blockMouseWheel, false, 0, true);// Prevent duplicate scroll events
						//if (sb.scale9Grid == null) { sb.scale9Grid = new Rectangle(0,0,1,1); } // Prevent scaling
						if (parent != null){
							parent.addChild(sb as DisplayObject);
						}
					}
				}
			}
			_scrollBar = sb as ScrollIndicator;
			
			if (_scrollBar == null)
			{
				return;
			}
			_scrollBar.focusTarget = this;
			_scrollBar.tabEnabled = false;
			
			_scrollBar.x = this.x + width;
			_scrollBar.y = this.y;
			_scrollBar.height = this.height;
			_scrollBar.validateNow();
		}
		
		/**
		 * 
		 * 
		 */		
		public function updateScrollBar():void
		{
			if (_scrollBar == null || _scrollingTextField == null)return;
			_scrollBar.visible = true;
			_scrollBar.scrollTarget = _scrollingTextField;
		}
		
		protected function handleMouseWheel(event:MouseEvent):void {
			if(_scrollBar){
				_scrollBar.position -= (event.delta > 0 ? 1 : -1);
			}
		}
		
		protected function blockMouseWheel(event:MouseEvent):void
		{
			event.stopPropagation();
		}
	}
}