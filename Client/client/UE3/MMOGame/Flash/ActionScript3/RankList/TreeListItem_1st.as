package ActionScript3.RankList
{
	import ActionScript3.TreeListData;
	import flash.text.TextField;
	import ActionScript3.controls.StateUIComponent;

	public class TreeListItem_1st extends StateUIComponent
	{
		public var textField:TextField;
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
				textField.text = itemData_1st.label;
			}
			else
			{
				visible = false;
			}
			
		}
	}

}