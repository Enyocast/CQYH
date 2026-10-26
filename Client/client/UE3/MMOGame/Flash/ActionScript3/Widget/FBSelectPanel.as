package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip;
	import scaleform.clik.controls.DropdownMenu;
	
	public class FBSelectPanel extends MyPanel
	{

//		public var EnterMap_mc:Button;
//		public var Cancel_mc:Button;
		public var btn_close:Button;
		
		public var btn_diff0:RadioButton;
		public var btn_diff1:RadioButton;
		public var btn_diff2:RadioButton;
		public var btn_diff3:RadioButton;
		public var btn_dungeonEnter:Button;
		
		
		//public var MWindow:MovieClip;
		public var dropdownmenu_difficulty:DropdownMenu;
		
		override protected  function configUI():void 
		{
			super.configUI();
			btn_dungeonEnter.addEventListener("click",clickEnterMap );
//			Cancel_mc.addEventListener("click", clickCancel );
			dropdownmenu_difficulty.addEventListener("change",clickchange);
			
/*			if( MWindow )
			{
				MWindow.MWTitleIcon.gotoAndStop(11);
				MWindow.MWTitleText.gotoAndStop(11);
				MWindow.tab0.visible = false;
				MWindow.tab1.visible = false;
				MWindow.tab2.visible = false;
				MWindow.tab3.visible = false;
			
				MWindow.Resize( 500,510);
			}
*/
			
		}
		
		function clickEnterMap()
		{
			ExternalInterface.call("ASEnterMap");
		}

		function clickCancel()
		{
			visible = false;
		}

		//dropdownmenu_difficulty.dataProvider = ["简单","普通","困难","地狱","炼狱"];

		

		function clickchange( event)
		{
			ExternalInterface.call("ASMapDiffChange",event.index );
		}


	}
	
}