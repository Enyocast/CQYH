package ActionScript3.UndergroundTrade
{
	import ActionScript3.TreeListData;
	import scaleform.clik.core.UIComponent;	
	import flash.text.TextField;
	
	public class TreeListItem_3rd extends UIComponent
	{
		public var name_txt_mc:TextField;
		public var itemData_3rd:TreeListData;
		public function TreeListItem_3rd()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
		}
		
		function UpdateData(data:Object):void
		{
			itemData_3rd = data as TreeListData;
			if (itemData_3rd && itemData_3rd.deepth ==2)
			{
				visible = true;
				name_txt_mc.text = itemData_3rd.label;
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
