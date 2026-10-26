package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip
	import ActionScript3.Widget.MySkillConsole;
	import ActionScript3.Widget.MySkillActiveModify;
	import ActionScript3.Widget.MySkillPassiveModify;
	import ActionScript3.Widget.MySkillAvartaModify;
	import scaleform.clik.core.UIComponent;
	
	public class MySkillPanel extends MyPanel
	{
		
		public var SpellConsole:MySkillConsole;
		public var ActiveModify:MySkillActiveModify;
		public var PassiveModify:MySkillPassiveModify;
		public var AvartaModify:MySkillAvartaModify;
		
		function init()
		{
			trace("MySkillPanel init:");
			//mapScroll_mc.SetHeight(530);
			
		}
		override protected  function configUI():void
		{
			trace("MySkillPanel configUI:");
			
			super.configUI();
			
			//trace("MySkillPanel::configUI");		
			
			//trace("configUI::Size setted");	

			//trace("configUI set visiblility");
			/*w = 498;
			h = 512;
			x_edge = 40;*/
			
			
			//trace("MySkillPanel::configUI ended");	
			ExternalInterface.call( "RegisterSkill", this);	
			SpellConsole.visible = true;
			trace("SpellConsole::visible true");
			ActiveModify.visible=false;
			PassiveModify.visible=false;
			AvartaModify.visible=false;
		}	
	}
}