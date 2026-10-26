package ActionScript3.Common
{
	import flash.text.TextField;
	
	import ActionScript3.TreeListData;
	import ActionScript3.controls.StateUIComponent;
	
	public class TreeListItemBase extends StateUIComponent
	{
		public var name_txt_mc:TextField;
		
		[Inspectable(name = "_deepth",defaultValue = false)]
		public var _deepth:int;
		
		public function TreeListItemBase()
		{
			// constructor code
		}
		
		public function setState(state:String):void {
			gotoAndPlay(state);
		}
		
		public function UpdateData(data:Object):void
		{
			var itemData:TreeListData = data as TreeListData;
			if (itemData && itemData.deepth == _deepth)
			{
				visible = true;
				name_txt_mc.text = itemData.label;
			}
			else
			{
				visible = false;
			}
		}
	}
}