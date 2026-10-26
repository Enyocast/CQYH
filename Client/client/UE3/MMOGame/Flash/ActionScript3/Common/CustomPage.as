package ActionScript3.Common {

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import ActionScript3.Common.Events.ParamEvent;
	import scaleform.clik.events.ButtonEvent;
	import flash.text.TextField;
	
	
	public class CustomPage extends UIComponent {
		
		protected var _maximum:int = 1;
		protected var _value:int = 1;
		public var textField:TextField;
        /** A reference to the next button instance used to increment the {@code selectedIndex}. */
        public var nextBtn:Button;
        /** A reference to the previous button instance used to decrement the {@code selectedIndex}. */
        public var prevBtn:Button;
		public function CustomPage() {
			super();
		}
		
		override protected function configUI():void {
            nextBtn.addEventListener(ButtonEvent.CLICK, onNext, false, 0, true);
            prevBtn.addEventListener(ButtonEvent.CLICK, onPrev, false, 0, true);
			updateText();
		}
		protected function onNext( event:ButtonEvent ):void {
            if(this.value>=this.maximum){
				return;
			}
			this.value++;
			updateText();
			this.dispatchEvent(new ParamEvent(ParamEvent.PAGE_CHANGE,value));
        }
        
        protected function onPrev( event:ButtonEvent ):void {
            if(this.value<=1){
				return;
			}
			this.value--;
			updateText();
		    this.dispatchEvent(new ParamEvent(ParamEvent.PAGE_CHANGE,value));
        }
		
		public function get maximum():int { return _maximum; }
        public function set maximum(value:int):void {
            _maximum = value;
            value = _value;
			updateText();
        }    
		
		public function get value():int { return _value; }
        public function set value(v:int):void {
            if (v == _value) { return; }
            _value = v;
            updateText();
        }
		
		private function updateText():void
		{
			textField.text=this.value+"/"+this.maximum;
			if(this.value==this.maximum){
				this.nextBtn.enabled=false;
			}else{
				this.nextBtn.enabled=true;
			}
			if(this.value==1){
				this.prevBtn.enabled=false;
			}else{
				this.prevBtn.enabled=true;
			}
		}
	}
	
}
