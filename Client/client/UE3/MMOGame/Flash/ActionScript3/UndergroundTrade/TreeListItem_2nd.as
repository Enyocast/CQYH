package ActionScript3.UndergroundTrade
{
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;	
	import ActionScript3.TreeListData;
	
	public class TreeListItem_2nd extends UIComponent
	{
		public var name_txt_mc:TextField;
		public var itemData_2nd:TreeListData;
		
		public function TreeListItem_2nd()
		{
			// constructor code
		}
		
		override protected function configUI():void 
		{
			super.configUI();
			
		}

		function UpdateData(data:Object):void
		{
			itemData_2nd = data as TreeListData;
			if (itemData_2nd && itemData_2nd.deepth ==1)
			{
				visible = true;
				name_txt_mc.text = itemData_2nd.label;
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
