
package ActionScript3.Master
{

	import ActionScript3.MyPanel;

	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.text.TextField;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.Events.ParamEvent;

	public class MasterApplyListPage extends UIComponent
	{
		public var MasterApply_list_mc:MasterListControl;

		public var btn_ClearAll:Button;
		public var btn_AcceptApply:Button;
		public var btn_DenyApply:Button;
		public var tabTitle:MovieClip;
		
		public var _page:CustomPage;
        private const PAGESIZE:int=13;
		public var  nSelectedID:int = 0;
		override protected function configUI():void
		{
			super.configUI();
			
			btn_ClearAll.addEventListener(MouseEvent.CLICK, 	onClearMasterApply );
			btn_AcceptApply.addEventListener(MouseEvent.CLICK,  onAcceptApply );
			btn_DenyApply.addEventListener(MouseEvent.CLICK,    onDenyApply );
			
			MasterApply_list_mc.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			
			tabTitle.Btn_Sort0.addEventListener(MouseEvent.CLICK, onSortBtn0 );
			//tabTitle.Btn_Sort1.addEventListener(MouseEvent.CLICK, onSortBtn1 );
			tabTitle.Btn_Sort2.addEventListener(MouseEvent.CLICK, onSortBtn2 );
			tabTitle.Btn_Sort3.addEventListener(MouseEvent.CLICK, onSortBtn3 );
			//
			//_page.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			_page.visible = false;
			btn_AcceptApply.visible = false;
			btn_DenyApply.visible = false;
           // testData();
		}
		
		private function testData():void
		{
				var itemsData:Array = new Array();
				for (var i:int = 1; i < 15; i++)
				{
					
					var tMasterData:MasterData = new MasterData  ;
					tMasterData.Id = i*3;
					tMasterData.Name = String( "God" + i );
					tMasterData.Level = i;
					tMasterData.Profession = "法师";
					tMasterData.Score = 100 ;
					tMasterData.Status = "可申请";
					tMasterData.IsSelected = false;
					itemsData.push(tMasterData);
				}
				updateData( itemsData );
		}
		
		private function pageHandler(evt:ParamEvent):void
		{
			var index:int=evt.param as int;
			ExternalInterface.call("ASMasterApplyListPrevPage",index);
		}
		
		public function onSortBtn0()
		{
			ExternalInterface.call("ASSortMasterApplyList", 0 );
		}
		public function onSortBtn1()
		{
			ExternalInterface.call("ASSortMasterApplyList", 1 );
		}
		public function onSortBtn2()
		{
			ExternalInterface.call("ASSortMasterApplyList", 2 );
		}
		public function onSortBtn3()
		{
			ExternalInterface.call("ASSortMasterApplyList", 3 );
		}
		public function onSortBtn4()
		{
			ExternalInterface.call("ASSortMasterApplyList", 4 );
		}
		
		public function onClearMasterApply()
		{
			ExternalInterface.call("ASClearMasterApplyList");
		}

		public function onAcceptApply()
		{
			ExternalInterface.call("ASAcceptMasterApplyList",nSelectedID);
		}
		
		public function onDenyApply()
		{
			ExternalInterface.call("ASDenyMasterApplyList",nSelectedID);
		}
		
		public function onMasterNextPageClick()
		{
			ExternalInterface.call("ASMasterApplyListNextPage");
		}
		
		public function onMasterPrevPageClick()
		{
			ExternalInterface.call("ASMasterApplyListPrevPage");
		}
		
		public function updateData( data:Array ):void
		{
			nSelectedID = 0;
			btn_AcceptApply.visible = false;
			btn_DenyApply.visible = false;
			var nIndex:int = MasterApply_list_mc.selectedIndex;
			
			//_page.maximum=Math.ceil(data.length/this.PAGESIZE);
			MasterApply_list_mc.dataProvider = new DataProvider(data);
			MasterApply_list_mc.validateNow();
			MasterApply_list_mc.invalidateData();
			
			btn_ClearAll.visible = (data.length > 0);
			
			if(nIndex >= data.length)
				nIndex = data.length - 1;
			if(nIndex >= 0 && nIndex < data.length)
			{
				MasterApply_list_mc.selectedIndex = nIndex;
				btn_AcceptApply.visible = true;
				btn_DenyApply.visible = true;
				
				var SelData:MasterData = data[nIndex] as MasterData;
				nSelectedID = SelData.Id;
			}
		}
		
		public function onClickItem(e:ListEvent)
		{
			var item:MasterApplyListItem = e.itemRenderer as MasterApplyListItem;
			ExternalInterface.call("ASClickMasterList", item.Master_data.Id);
			
			btn_AcceptApply.visible = true;
			btn_DenyApply.visible = true;
			nSelectedID = item.Master_data.Id;
		}
		
		public function selectItem(index:int,id:int)
		{
			MasterApply_list_mc.selectedIndex = index;
			btn_AcceptApply.visible = true;
			btn_DenyApply.visible = true;
			nSelectedID = id;
		}
	}
}