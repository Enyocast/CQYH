package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import ActionScript3.TreeListData;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class TreeListItem extends ListItemTreeRenderer 
	{
		public var TreeListItem1st_mc:TreeListItem_1st;
		public var TreeListItem2nd_mc:TreeListItem_2nd;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//addEventListener(MouseEvent.ROLL_OVER, OnRollOverListItem);
			//addEventListener(MouseEvent.ROLL_OUT, OnRollOutListItem);
			setUpdateDataCallBack(UpdateData);
		}
		
		function UpdateData(data:Object):void
		{
			if(null != data)
			{
				showItem();
				if(!visible) visible = true;
				if( data.deepth == 0 )
				{
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.visible = true;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.visible = false;
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.UpdateData(data);
				}
				else if( data.deepth == 1 )
				{
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.visible = false;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.visible = true;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.UpdateData( data );
				}
			}
			else
				visible = false;
		}
		
		function showItem():void
		{			
			TreeListItem1st_mc.selected = this.selected;
			TreeListItem2nd_mc.selected = this.selected;
		}
		
		function OnRollOverListItem( e:Event )
		{
			//TreeListItem1st_mc.gotoAndStop("over");
			//TreeListItem2nd_mc.gotoAndStop("over");
			
			
			if(null != TreeListItem1st_mc && TreeListItem1st_mc.visible)
			{
				TreeListItem1st_mc.gotoAndStop("over");
			}
			else if(null != TreeListItem2nd_mc && TreeListItem2nd_mc.visible)
			{
				TreeListItem2nd_mc.gotoAndStop("over");
			}
			
		}

		function OnRollOutListItem( e:Event )
		{
			//TreeListItem1st_mc.gotoAndStop("up");
			//TreeListItem2nd_mc.gotoAndStop("up");
			
			if(null != TreeListItem1st_mc && TreeListItem1st_mc.visible)
			{
					TreeListItem1st_mc.gotoAndStop("up");
			}
			else if(null != TreeListItem2nd_mc && TreeListItem2nd_mc.visible)
			{
				TreeListItem2nd_mc.gotoAndStop("up");
			}
		}
		
	}
}
