package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip
	import flashx.textLayout.formats.Float;
	import ActionScript3.MyRuneButton;
	import ActionScript3.MyRuneActiveButton;
	import ActionScript3.Widget.MySkillPanel;
	import scaleform.clik.core.UIComponent;
	
	public class MySkillConsole extends UIComponent
	{
		public var ActiveSkill0:Button;
		public var ActiveSkill1:Button;
		public var ActiveSkill2:Button;
		public var ActiveSkill3:Button;
		public var ActiveSkill4:Button;
		public var ActiveSkill5:Button;

		public var PassiveSkill0:Button;
		public var PassiveSkill1:Button;
		public var PassiveSkill2:Button;

		public var AvartaSkill0:Button;
		public var AvartaSkill1:Button;
		public var AvartaSkill2:Button;

		public var SelectedId:Number;

		function init()
		{
			//mapScroll_mc.SetHeight(530);
			
		}
		override protected  function configUI():void
		{
			super.configUI();

			ActiveSkill0['spellBtnKey'].gotoAndStop(1);
			ActiveSkill1['spellBtnKey'].gotoAndStop(2);
			ActiveSkill2['spellBtnKey'].gotoAndStop(3);
			ActiveSkill3['spellBtnKey'].gotoAndStop(4);
			ActiveSkill4['spellBtnKey'].gotoAndStop(5);
			ActiveSkill5['spellBtnKey'].gotoAndStop(6);

			ActiveSkill0['SpellSlotId']=10;
			ActiveSkill1['SpellSlotId']=11;
		}	
	}
}