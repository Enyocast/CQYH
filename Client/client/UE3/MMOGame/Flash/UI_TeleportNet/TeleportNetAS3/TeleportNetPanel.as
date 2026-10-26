package UI_TeleportNet.TeleportNetAS3
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.Button;
	
	import flash.events.Event;
	import scaleform.clik.events.ListEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import scaleform.clik.controls.ScrollingList;
	
	import ActionScript3.TreeListData;
	import scaleform.clik.data.TreeDataProvider;
	import UI_TeleportNet.TeleportNetAS3.TeleportMapData;
	
	//import UI_TeleportNet.TeleportNetAS3.TreeListData;
	
	public class TeleportNetPanel extends MyPanel
	{
		public var iCurTab:int;
		public var tab_mc0:RadioButton;
		public var tab_mc1:RadioButton;
		public var tab_mc2:RadioButton;
		public var tab_mc3:RadioButton;
		//
		public var TeleportNodesList_mc:ScrollingList;
		
		override protected function configUI():void
		{
			super.configUI();
			//
			ExternalInterface.call( "RegisterTeleportNet", this );
			//
			tab_mc0.addEventListener( MouseEvent.CLICK, function _contentChange(e:Event){ contentChange(e,0);} );
			tab_mc1.addEventListener( MouseEvent.CLICK, function _contentChange(e:Event){ contentChange(e,1);} );
			tab_mc2.addEventListener( MouseEvent.CLICK, function _contentChange(e:Event){ contentChange(e,2);} );
			tab_mc3.addEventListener( MouseEvent.CLICK, function _contentChange(e:Event){ contentChange(e,3);} );
			
			TeleportNodesList_mc.addEventListener(ListEvent.ITEM_CLICK, onClickTeleportNode);
			////test
			//UCUpdateTab(0);

			UCUpdateTeleportNodesList( new Array() );
			TestData(6);
		}
		//
		function contentChange( e:Event, idx:int )
		{
			//Test
			//UCUpdateTab(idx);
			
			iCurTab = idx;
			ExternalInterface.call( "ASUpdateTeleportNetPanel", idx );
		}
		//
		public function UCUpdateTeleportNodesList( data:Array ):void
		{
			TeleportNodesList_mc.dataProvider = new TreeDataProvider(data);
			TeleportNodesList_mc.validateNow();
			TeleportNodesList_mc.invalidateData();
		}
		//
		public function onClickTeleportNode(e:ListEvent):void
		{
			var targetList:ScrollingList = e.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;
				if( Provider != null )
				{
					Provider.handleListItemClick( e );
					//trace( "Provider.requestItemAt(e.index) as TeleportNodesData : " ,Provider.requestItemAt(e.index) as TeleportNodesData )
					var itemData:TreeListData = Provider.requestItemAt(e.index) as TreeListData;//TeleportNodesData;
					
					if( itemData.type == 0 )
					{
						var netNodeData:TeleportNodesData = itemData as TeleportNodesData;
						if( netNodeData ){
							ExternalInterface.call( "ASToThisTeleportNode", netNodeData.NodeID );
						}
					}
					else
					{
						targetList.invalidateData();
					}
				}
			}
		}
		//
		public function UCUpdateTab( idx:int ):void
		{			
			switch( idx )
			{
				case 0:
				tab_mc0.selected = true;
				//TestData(6);
				break;
				
				case 1:
				tab_mc1.selected = true;
				//TestData(1);
				break;
				
				case 2:
				tab_mc2.selected = true;
				//TestData(3);
				break;
				
				case 3:
				tab_mc3.selected = true;
				//TestData(4);
				break;
			}
		}
		//
		function TestData( num:int )
		{
			//test
			var itemsData:Array = new Array();
			for (var i:int = 1; i <= num; i++)
			{
				var nodeMapItemData:TeleportMapData = new TeleportMapData ;
				nodeMapItemData.type = 2;
				nodeMapItemData.deepth = 0;
				nodeMapItemData.visible = true;
					
				nodeMapItemData.MapName = "地图" + i;
				itemsData.push(nodeMapItemData);
					
				for (var j:int = 1; j <= i; j++)
				{
					if( i==num && j==num ){
						var curNodeItemData:TreeListData = new TreeListData ;
						curNodeItemData.type = 0;
						curNodeItemData.deepth = 1;
						curNodeItemData.visible = true;
						
						itemsData.push(curNodeItemData);
					}
					
					var nodeItemData:TeleportNodesData = new TeleportNodesData ;
					nodeItemData.type = 0;
					nodeItemData.deepth = 1;
					nodeItemData.visible = true;
					
					nodeItemData.NodeID = i*100 + j;
					nodeItemData.CostType = j%2;
					nodeItemData.Cost = j*10;
					nodeItemData.NodeName = "传送点" + j;
					//nodeItemData.PicName = "DstPb0" + (j%2+1);
					nodeItemData.ShowState = (int)(i==num && j==num);
					
					itemsData.push(nodeItemData);
				}
			}
			
			UCUpdateTeleportNodesList(itemsData);
			//test end
		}
	}
}