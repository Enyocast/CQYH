package ActionScript3
{
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.SliderEvent;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.geom.Rectangle;
	
	public class MyScrollPanel extends UIComponent
	{
		public var _scrollV:Number = 1;
		public var _bottomScrollV:Number = 100;
		public var maxScrollV:Number = 100;
		
		public var _textheight:Number=0;
		public var _textwidth:Number=0;
		
		 override protected function configUI():void {
			scrollV = 1;
			bottomScrollV = 100;
			maxScrollV = 100; 
            super.configUI();			
		 }
		 
		 override public function set width(value:Number):void{
			 _textwidth=value;
		 }
		 override public function get width():Number{
			 return _textwidth;;
			 
		 }
		 
		override public function set height(value:Number):void{
			 _textheight=value;
		 }
		 override public function get height():Number{
			 return _textheight;
		 }
		 

		 public function clear():void
		 {
			 var i:int=0;
			 var l:int=this.numChildren;
			 for(i=0;i<l;i++){
				  this.removeChildAt(0);
			 }
			 _textheight=0;
			 _textwidth=0;
			 y=0;
		 }
		 
		 override public function addChild(child:DisplayObject):DisplayObject
		 {
			 _textheight+=child.height;
			 return super.addChild(child);
		 }
		 
		 override public function removeChild(child:DisplayObject):DisplayObject
		 {
			
			 if(this.contains(child)){
				 _textheight-=child.height;
				 if(_textheight<0){
					 _textheight=0;
				 }
				 return super.removeChild(child);
			 }
			 return null;
		 }
		public function set bottomScrollV( value:Number ):void {
			_bottomScrollV = value;
		}
		public function get bottomScrollV():Number {
			return _bottomScrollV;
		}
		
		public function set scrollV( value:Number ):void {
			_scrollV = value;
			
			//原来是1-100，要弄成0-100
			var percent = (value-1)*100/99;
			dispatchEvent( new SliderEvent(SliderEvent.VALUE_CHANGE, false, true, percent) );
		}
		public function get scrollV():Number {
			return _scrollV;
		}
	}
}