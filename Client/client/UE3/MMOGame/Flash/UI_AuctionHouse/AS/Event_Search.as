package UI_AuctionHouse.AS
{
    import flash.events.Event;

    
    public class Event_Search extends Event
	{        
    // Constants:
        public static const RESET:String = "resetFilter";        
        
    // Initialization:
        public function Event_Search(type:String, bubbles:Boolean = true, cancelable:Boolean = false)
		{
            super(type, bubbles, cancelable);            
        }
        
    // Public getter / setters:
        
    // Public Methods:
        override public function clone():Event {
            return new Event_Search(type, bubbles, cancelable);
        }
        
        override public function toString():String 
		{
            return formatToString("Event_Search", "type", "bubbles", "cancelable");
        }
        
    // Protected Methods:
	}
    
}