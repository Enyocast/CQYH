package UI_EquipLevelUp.AS3
{
	import flash.text.TextField;
	
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.UILoader;
	
	public class UpgradeCompensationItem extends ListItemRenderer
	{
		public var txt_info:TextField;
		public var loader_mc:UILoader;
		
		public function UpgradeCompensationItem()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			var comdata:UpgradeCompensationItemData = data as UpgradeCompensationItemData;
			if(comdata == null) return;
			txt_info.text = comdata.materialInfo;
			loader_mc.source = comdata.materialSrc;
		}
	}
}