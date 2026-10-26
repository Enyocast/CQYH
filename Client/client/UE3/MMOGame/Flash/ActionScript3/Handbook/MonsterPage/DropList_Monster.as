package ActionScript3.Handbook.MonsterPage
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import ActionScript3.Common.ItemGrid;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.core.UIComponent;
	
	public class DropList_Monster extends UIComponent
	{
		public var monster_drop_title_tf:TextField;
		public var check_useable_only:CheckBox;
		public var dropItemGrid_mc:ItemGrid;
		
		public function DropList_Monster()
		{
			super();
		}
		
		public function updateFrameSize():void
		{
			_width = dropItemGrid_mc.x + dropItemGrid_mc.width;
			_height = dropItemGrid_mc.y + dropItemGrid_mc.height;
		}
	}
}