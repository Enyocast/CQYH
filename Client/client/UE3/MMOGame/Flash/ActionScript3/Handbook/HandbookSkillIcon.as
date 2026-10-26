
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	import ActionScript3.Common.Utils.StyleType;
	import scaleform.clik.interfaces.IUIComponent;
	
	public class HandbookSkillIcon extends UIComponent
	{
		public var icon_mc:MovieClip;
		public var UniqueSkillID:int;
		
		public function HandbookSkillIcon()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			icon_mc.source = null;
			UniqueSkillID = 0;
		}

		public function SetData(skill_id:int, skill_icon:String):void
		{
			UniqueSkillID = skill_id;
			icon_mc.source = skill_icon;
		}
	}
}