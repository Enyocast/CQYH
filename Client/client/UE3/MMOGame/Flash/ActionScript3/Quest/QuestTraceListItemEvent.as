package ActionScript3.Quest
{

	import flash.display.InteractiveObject;
    import flash.events.Event;
    import flash.events.MouseEvent;
	import flash.external.ExternalInterface;

	public class QuestTraceListItemEvent extends Event
	{
		public static const PlayAnimCompleted:String = "PlayAnimCompleted";
		public var quest_id:int;
		
		 // Initialization:
        public function QuestTraceListItemEvent(questID:int, bubbles:Boolean = true, cancelable:Boolean = false)
		{
            super(PlayAnimCompleted, bubbles, cancelable);
			quest_id = questID;
			
			ExternalInterface.call("ASTrace", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~QuestTraceListItemEvent::QuestTraceListItemEvent");
        }
        
    // Public getter / setters:
        
    // Public Methods:
        override public function clone():Event {
            return new QuestTraceListItemEvent(quest_id, bubbles, cancelable);
			ExternalInterface.call("ASTrace", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~QuestTraceListItemEvent::clone()");
        }
        
        override public function toString():String {
            return formatToString("QuestListItemEvent", "type", "bubbles", "cancelable", "quest_id");
			ExternalInterface.call("ASTrace", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~QuestTraceListItemEvent::toString()");
        }
	}

}