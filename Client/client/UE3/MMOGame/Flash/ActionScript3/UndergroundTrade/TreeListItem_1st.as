package ActionScript3.UndergroundTrade
{
	import ActionScript3.TreeListData;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;

	public class TreeListItem_1st extends UIComponent
	{
		public var name_txt_mc:TextField;
		public var itemData_1st:TreeListData;
		
		public function TreeListItem_1st()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
		}

		function UpdateData(data:Object):void
		{
			itemData_1st = data as TreeListData;
			if (itemData_1st && itemData_1st.deepth ==0)
			{
				visible = true;
				name_txt_mc.text = itemData_1st.label;
			}
			else
			{
				visible = false;
			}
		}
	}

}