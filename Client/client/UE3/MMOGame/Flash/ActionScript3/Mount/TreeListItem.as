package ActionScript3.Mount
{
	import ActionScript3.Common.TreeListItemBase;
	import ActionScript3.RankList.TreeListItem_1st;
	import ActionScript3.RankList.TreeListItem_2nd;
	import ActionScript3.UndergroundTrade.TreeListItem_3rd;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	
	public class TreeListItem extends ListItemTreeRenderer 
	{
		public var TreeListItem1st_mc:TreeListItemBase;
		public var TreeListItem2nd_mc:TreeListItemBase;
		public var TreeListItem3rd_mc:TreeListItemBase;
		
		public function TreeListItem()
		{
		}
		
		override protected function configUI():void
		{
			trace("override protected function configUI():void");
			super.mouseChildren = true;
			super.mouseEnabled  = true;
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		override protected function setState(state:String):void {
			super.setState(state);
			if(super._newFrame){
				TreeListItem1st_mc.setState(super._newFrame);
				TreeListItem2nd_mc.setState(super._newFrame);
				TreeListItem3rd_mc.setState(super._newFrame);
			}
		}
		
		function UpdateData(data:Object):void
		{
			trace("UpdateData:"+data);
			TreeListItem1st_mc.UpdateData(data);
			TreeListItem2nd_mc.UpdateData(data);	
			TreeListItem3rd_mc.UpdateData(data);
		}
		
	}
	
}
