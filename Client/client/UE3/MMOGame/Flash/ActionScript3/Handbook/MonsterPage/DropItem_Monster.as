package ActionScript3.Handbook.MonsterPage
{
	import flash.display.MovieClip;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.ListItemRenderer;
	
	public class DropItem_Monster extends ListItemRenderer
	{
		public var monster_drop_mc:MyItemSlot;
		
		public function DropItem_Monster()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren = true;
			this.mouseEnabled = true;
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			monster_drop_mc.SetData(0, data.item_icon, data.item_id, "", 0, -1, -1);
		}
	}
}