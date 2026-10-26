
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

	public class MasterPosterListPage extends UIComponent
	{
		public var MasterPoster_list_mc:MasterListControl;

		public var btn_MasterApply:Button;
		public var btn_DenyApply:Button;
		public var btn_Refresh:Button;
		public var tabTitle:MovieClip;
		
		public var tF_tips:TextField;
		
		public var _page:CustomPage;
        private const PAGESIZE:int=13;
		
		public var  nSelectedID:int = 0;
		
		override protected function configUI():void
		{
			super.configUI();
			RefreshControlState();
			tF_tips.visible = false;

			btn_MasterApply.addEventListener(MouseEvent.CLICK, onMasterListApply );
			btn_DenyApply.addEventListener(MouseEvent.CLICK, onMasterListDenyApply );
			btn_Refresh.addEventListener(MouseEvent.CLICK, onRefresh );
			
			
			MasterPoster_list_mc.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			
			tabTitle.Btn_Sort0.addEventListener(MouseEvent.CLICK, onSortBtn0 );
			//tabTitle.Btn_Sort1.addEventListener(MouseEvent.CLICK, onSortBtn1 );
			tabTitle.Btn_Sort2.addEventListener(MouseEvent.CLICK, onSortBtn2 );
			tabTitle.Btn_Sort3.addEventListener(MouseEvent.CLICK, onSortBtn3 );
			tabTitle.Btn_Sort4.addEventListener(MouseEvent.CLICK, onSortBtn4 );
			//_page.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			_page.visible = false;
            //testData();
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
					tMasterData.IsSelected = (i == 1);
					tMasterData.bCanApply = (i%2?false:true);
					itemsData.push(tMasterData);
				}
				updateData( itemsData );
		}
		
		private function pageHandler(evt:ParamEvent):void
		{
			var index:int=evt.param as int;
			ExternalInterface.call("ASMasterPosterListPrevPage",index);
		}
		
		public function onSortBtn0()
		{
			ExternalInterface.call("ASSortMasterPosterList", 0 );
		}
		public function onSortBtn1()
		{
			ExternalInterface.call("ASSortMasterPosterList", 1 );
		}
		public function onSortBtn2()
		{
			ExternalInterface.call("ASSortMasterPosterList", 2 );
		}
		public function onSortBtn3()
		{
			ExternalInterface.call("ASSortMasterPosterList", 3 );
		}
		public function onSortBtn4()
		{
			ExternalInterface.call("ASSortMasterPosterList", 4 );
		}
		
		public function onMasterListApply()
		{
			ExternalInterface.call("ASApplyMasterPosterList",nSelectedID);
		}
		
		public function onMasterListDenyApply()
		{
			ExternalInterface.call("ASCancelMasterPosterList",nSelectedID);
		}

		public function onRefresh()
		{
			ExternalInterface.call("ASMasterPosterListRefresh");
		}
		
		public function onMasterNextPageClick()
		{
			ExternalInterface.call("ASMasterPosterListNextPage");
		}
		
		public function onMasterPrevPageClick()
		{
			ExternalInterface.call("ASMasterPosterListPrevPage");
		}
		
		public function updateData( data:Array ):void
		{
			RefreshControlState();
			var nIndex = MasterPoster_list_mc.selectedIndex;
			//_page.maximum=Math.ceil(data.length/this.PAGESIZE);
			
			MasterPoster_list_mc.dataProvider = new DataProvider(data);
			MasterPoster_list_mc.validateNow();
			MasterPoster_list_mc.invalidateData();
			
			if(nIndex >= data.length)
				nIndex = data.length - 1;
				
			if(nIndex >= 0 && nIndex < data.length)
			{
				MasterPoster_list_mc.selectedIndex = nIndex;
				var StData:MasterData = data[nIndex] as MasterData;
				if(StData)
				{
					btn_MasterApply.visible = StData.bCanApply;
					btn_DenyApply.visible = !StData.bCanApply;
					nSelectedID = StData.Id;
				}
			}
		}
		
		public function RefreshControlState()
		{
			btn_DenyApply.visible = false;
			btn_MasterApply.visible = false;
			nSelectedID = 0;
		}
		public function onClickItem(e:ListEvent)
		{
			var item:MasterPosterListItem = e.itemRenderer as MasterPosterListItem;
			ExternalInterface.call("ASClickMasterPosterList", item.Master_data.Id);
			
			btn_MasterApply.visible = item.Master_data.bCanApply;
			btn_DenyApply.visible = !item.Master_data.bCanApply;
			nSelectedID = item.Master_data.Id;
		}
	}
}