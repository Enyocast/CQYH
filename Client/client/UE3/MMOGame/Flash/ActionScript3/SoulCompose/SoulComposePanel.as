package ActionScript3.Soul
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.gfx.Extensions;
	import ActionScript3.MyScrollBar;



	public class SoulComposePanel extends MyPanel implements IQuestPanel
	{
		public static const C_Page_Accepted = 0;
		public static const C_Page_Available = 1;
		public static const C_Page_Completed = 2;

		public var tab0_mc:MyTipButton;
		public var tab1_mc:MyTipButton;
		public var tab2_mc:MyTipButton;
		public var btn_accept:Button;
		public var btn_abort:Button;
		
		public var quest_list_ctrl:QuestListControl;

		public var selected_quest_id:int;
		

		public function SoulComposePanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			trace("------SoulComposePanel  super.configUI");
			super.configUI();

			btn_share.addEventListener(MouseEvent.CLICK, onShareQuest);
			btn_abort.addEventListener(MouseEvent.CLICK, onAbortQuest);
			
			ExternalInterface.call("ASRegisterSoulComposePanel", this);

			trace("xxxxxxxxxxx QuestPanel:configUI end");
		}
		
		public function onClickSoulCompose()
		{
			ExternalInterface.call("ASSoulCompose");
		}

		public function onClickCancel()
		{
			ExternalInterface.call("ASSoulCancelCompose");
		}

	}

}