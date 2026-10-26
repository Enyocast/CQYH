package ActionScript3
{
    import flash.events.Event;

    
    public class MoneyInput_Event extends Event
	{        
    // Constants:
        public static const INPUT_CHANGE:String = "inputChange";
		protected var _moneyCount:int = 0;
        
    // Initialization:
        public function MoneyInput_Event(type:String, moneyCount:int, bubbles:Boolean = true, cancelable:Boolean = false)
		{
			_moneyCount = moneyCount;
            super(type, bubbles, cancelable);            
        }
        
    // Public getter / setters:
        
    // Public Methods:
        override public function clone():Event {
            return new MoneyInput_Event(type, _moneyCount, bubbles, cancelable);
        }
        
        override public function toString():String 
		{
            return formatToString("MoneyInput_Event", "type", "bubbles", "cancelable");
        }
				
		public function get moneyCount():int
		{
			return _moneyCount;
		}
        
    // Protected Methods:
	}
    
}