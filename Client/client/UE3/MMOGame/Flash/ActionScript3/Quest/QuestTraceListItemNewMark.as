package ActionScript3.Quest
{

	import flash.display.InteractiveObject;
    import flash.events.Event;
    import flash.events.MouseEvent;
    import scaleform.clik.core.UIComponent;

	public class QuestTraceListItemNewMark extends UIComponent
	{
		public var _quest_id:int;
		
		// 这个类的控制在帧上
		public function startPlay()
		{
			this.gotoAndPlay(2);
		}
		public function RemoveAll()
		{
		}		
	}

}