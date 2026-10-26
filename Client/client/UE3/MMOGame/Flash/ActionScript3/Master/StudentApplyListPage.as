
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

	public class StudentApplyListPage extends UIComponent
	{
		public var StudentApply_list_mc:MasterListControl;

		public var btn_AcceptApply:Button;
		public var btn_DenyApply:Button;
		public var btn_ClearAll:Button;

		public var tabTitle:MovieClip;
		public var _page:CustomPage;
		
		private const PAGESIZE:int=12;
		public var  nSelectedID:int = 0;
		override protected function configUI():void
		{
			super.configUI();
			RefreshControlState();
			
			btn_AcceptApply.addEventListener(MouseEvent.CLICK, onAcceptApplicate );
			btn_DenyApply.addEventListener(MouseEvent.CLICK, onDenyApplicate );
			btn_ClearAll.addEventListener(MouseEvent.CLICK, onClearAll );
			
			StudentApply_list_mc.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			//_page.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			_page.visible = false;
			tabTitle.Btn_Sort0.addEventListener(MouseEvent.CLICK, onSortBtn0 );
			//tabTitle.Btn_Sort1.addEventListener(MouseEvent.CLICK, onSortBtn1 );
			tabTitle.Btn_Sort2.addEventListener(MouseEvent.CLICK, onSortBtn2 );
			//testData();
		}
		
		private function testData():void
		{
				var itemsData:Array = new Array();
				for (var i:int = 1; i < 100; i++)
				{
					var tStudentData:StudentData = new StudentData  ;
					tStudentData.Id = i;
					tStudentData.Name = String( "Panda" + i );
					tStudentData.Level = i % 4;
					tStudentData.Profession = "战士" ;
					tStudentData.IsSelected = false;
					itemsData.push(tStudentData);
				}
				updateData( itemsData );
		}
		
		private function pageHandler(evt:ParamEvent):void
		{
			var index:int=evt.param as int;
			ExternalInterface.call("ASStudentApplyListPage",index);
		}
		
		public function onSortBtn0()
		{
			ExternalInterface.call("ASSortStudentApplyList", 0 );
		}
		public function onSortBtn1()
		{
			ExternalInterface.call("ASSortStudentApplyList", 1 );
		}
		public function onSortBtn2()
		{
			ExternalInterface.call("ASSortStudentApplyList", 2 );
		}

		public function onAcceptApplicate()
		{
			ExternalInterface.call("ASAcceptStudentApplyList",nSelectedID);
		}

		public function onDenyApplicate()
		{
			ExternalInterface.call("ASDenyStudentApplyList",nSelectedID);
		}
		
		public function onClearAll()
		{
			ExternalInterface.call("ASClearStudentApplyList");
		}
		public function RefreshControlState()
		{
			btn_AcceptApply.visible = false;
			btn_DenyApply.visible = false;
			btn_ClearAll.visible = false;
			nSelectedID = 0;
		}

		public function updateData( data:Array ):void
		{
			RefreshControlState();
			var nIndex:int = 1;//StudentApply_list_mc.selectedIndex;
            // _page.maximum=Math.ceil(data.length/this.PAGESIZE);
			StudentApply_list_mc.dataProvider = new DataProvider(data);
			StudentApply_list_mc.validateNow();
			StudentApply_list_mc.invalidateData();
			
			if(data.length > 0)
				btn_ClearAll.visible = true;
			
			if(nIndex >= data.length)
				nIndex = data.length - 1;
				
			if(nIndex >= 0&&nIndex < data.length)
			{
				StudentApply_list_mc.selectedIndex = nIndex;
				btn_AcceptApply.visible = true;
				btn_DenyApply.visible = true;
				var selData:StudentData = data[nIndex] as StudentData;
				nSelectedID = selData.Id;
			}
		}

		public function onClickItem(e:ListEvent)
		{
			if(e == null)
				return;
			var item:StudentApplyListItem = e.itemRenderer as StudentApplyListItem;
			ExternalInterface.call("ASClickStudentApplyList", item.Student_data.Id);
			
			btn_AcceptApply.visible = true;
			btn_DenyApply.visible = true;
			nSelectedID = item.Student_data.Id;
		}
		
		public function selectItem(index:int,id:int)
		{
			StudentApply_list_mc.selectedIndex = index;
			btn_AcceptApply.visible = true;
			btn_DenyApply.visible = true;
			nSelectedID = id;
		}
	}
}