package ActionScript3.UndergroundTrade
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import ActionScript3.TreeListData;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class TreeListItem extends ListItemTreeRenderer 
	{
		public var TreeListItem1st_mc:TreeListItem_1st;
		public var TreeListItem2nd_mc:TreeListItem_2nd;
		public var TreeListItem3rd_mc:TreeListItem_3rd;
		
		public function TreeListItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("override protected function configUI():void");
			super.configUI();
			
			addEventListener(MouseEvent.ROLL_OVER, OnRollOverListItem);
			addEventListener(MouseEvent.ROLL_OUT, OnRollOutListItem);
			
			setUpdateDataCallBack(UpdateData);
		}
		
		function UpdateData(data:Object):void
		{
			if(null != data)
			{
				if(!visible) visible = true;
				if( data.deepth == 0 )
				{
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.visible = true;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.visible = false;
					if(null != TreeListItem3rd_mc)
						TreeListItem3rd_mc.visible = false;
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.UpdateData(data);
				}
				else if( data.deepth == 1 )
				{
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.visible = false;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.visible = true;
					if(null != TreeListItem3rd_mc)
						TreeListItem3rd_mc.visible = false;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.UpdateData( data );
				}
				else if(data.deepth == 2)
				{
					if(null != TreeListItem1st_mc)
						TreeListItem1st_mc.visible = false;
					if(null != TreeListItem2nd_mc)
						TreeListItem2nd_mc.visible = false;
					if(null != TreeListItem3rd_mc)
						TreeListItem3rd_mc.visible = true;
					if(null != TreeListItem3rd_mc)
						TreeListItem3rd_mc.UpdateData( data );
				}
			}
			else
				visible = false;
		}
		
		function OnRollOverListItem( e:Event )
		{
			
			if(null != TreeListItem1st_mc && TreeListItem1st_mc.visible)
			{
				TreeListItem1st_mc.gotoAndStop("over");
			}
			else if(null != TreeListItem2nd_mc && TreeListItem2nd_mc.visible)
			{
				TreeListItem2nd_mc.gotoAndStop("over");
			}
			else
			{
				if(null != TreeListItem3rd_mc)
					TreeListItem3rd_mc.gotoAndStop("over");
			}
			
		}

		function OnRollOutListItem( e:Event )
		{
			
			if(null != TreeListItem1st_mc && TreeListItem1st_mc.visible)
			{
					TreeListItem1st_mc.gotoAndStop("up");
			}
			else if(null != TreeListItem2nd_mc && TreeListItem2nd_mc.visible)
			{
				TreeListItem2nd_mc.gotoAndStop("up");
			}
			else
			{
				if(null != TreeListItem3rd_mc)
					TreeListItem3rd_mc.gotoAndStop("up");
			}
		}
		
	}
}
