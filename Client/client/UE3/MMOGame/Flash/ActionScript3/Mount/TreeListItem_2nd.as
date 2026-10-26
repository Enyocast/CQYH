package ActionScript3.Mount
{
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.TreeListData;
	
	public class TreeListItem_2nd extends UIComponent
	{
		public var name_txt_mc:TextField;
		public function TreeListItem_2nd()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function setState(state:String):void {
			gotoAndPlay(state);
		}

		function UpdateData(data:Object):void
		{
			//var itemData:TreeListData = data as TreeListData;
			var itemData:Object = data ;
			if (itemData && itemData.deepth ==1)
			{
				visible = true;
				name_txt_mc.text = itemData.label;
				trace("UpdateData"+itemData.label);
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
