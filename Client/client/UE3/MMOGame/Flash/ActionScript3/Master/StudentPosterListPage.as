
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

	public class StudentPosterListPage extends UIComponent
	{
		public var StudentPoster_list_mc:MasterListControl;

		public var btn_StudentApply:Button;
		public var btn_DenyApply:Button;
		public var btn_Refresh:Button;
		public var tabTitle:MovieClip;
		
		public var _page:CustomPage;
		public var  nSelectedID:int = 0;
		
		private const PAGESIZE:int=12;
		public var tF_tips:TextField;

		override protected function configUI():void
		{
			super.configUI();
			
			tF_tips.visible = false;
			
			RefreshControlState();
			
			btn_StudentApply.addEventListener(MouseEvent.CLICK, onAcceptApplicate );
			btn_DenyApply.addEventListener(MouseEvent.CLICK, onDenyApplicate );
			btn_Refresh.addEventListener(MouseEvent.CLICK, onClearAll );
			
			StudentPoster_list_mc.addEventListener(ListEvent.ITEM_CLICK, onClickItem);
			//_page.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			_page.visible = false;
			tabTitle.txt_sort3.text="状态 ";
			tabTitle.Btn_Sort0.addEventListener(MouseEvent.CLICK, onSortBtn0 );
			//tabTitle.Btn_Sort1.addEventListener(MouseEvent.CLICK, onSortBtn1 );
			tabTitle.Btn_Sort2.addEventListener(MouseEvent.CLICK, onSortBtn2 );
			tabTitle.Btn_Sort3.addEventListener(MouseEvent.CLICK, onSortBtn3 );
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
					tStudentData.bCanApply = (i%2? false:true);
					itemsData.push(tStudentData);
				}
				updateData( itemsData );
		}
		
		private function pageHandler(evt:ParamEvent):void
		{
			var index:int=evt.param as int;
			ExternalInterface.call("ASStudentPostListPage",index);
		}
		
		public function onSortBtn0()
		{
			ExternalInterface.call("ASSortStudentPosterList", 0 );
		}
		public function onSortBtn1()
		{
			ExternalInterface.call("ASSortStudentPosterList", 1 );
		}
		public function onSortBtn2()
		{
			ExternalInterface.call("ASSortStudentPosterList", 2 );
		}
		public function onSortBtn3()
		{
			ExternalInterface.call("ASSortStudentPosterList", 3 );
		}
		
		public function onAcceptApplicate()
		{
			ExternalInterface.call("ASApplyStudentPosterList",nSelectedID);
		}

		public function onDenyApplicate()
		{
			ExternalInterface.call("ASCancelStudentPosterList",nSelectedID);
		}
		
		public function onClearAll()
		{
			ExternalInterface.call("ASRefreshStudentPosterList");
		}
		public function RefreshControlState()
		{
			btn_StudentApply.visible = false;
			btn_DenyApply.visible = false;
			nSelectedID = 0;
		}

		public function updateData( data:Array ):void
		{
			RefreshControlState();
			var nIndex = StudentPoster_list_mc.selectedIndex;
             _page.maximum=Math.ceil(data.length/this.PAGESIZE);
			StudentPoster_list_mc.dataProvider = new DataProvider(data);
			StudentPoster_list_mc.validateNow();
			StudentPoster_list_mc.invalidateData();
			
			if(nIndex >= data.length)
				nIndex = data.length - 1;
				
			if(nIndex >= 0 && nIndex < data.length)
			{
				StudentPoster_list_mc.selectedIndex = nIndex;
				var StData:StudentData = data[nIndex] as StudentData;
				if(StData)
				{
					btn_StudentApply.visible = StData.bCanApply;
					btn_DenyApply.visible = !StData.bCanApply;
					nSelectedID = StData.Id;
				}
			}
		}

		public function onClickItem(e:ListEvent)
		{
			var item:StudentPosterListItem = e.itemRenderer as StudentPosterListItem;
			ExternalInterface.call("ASClickStudentPosterList", item.Student_data.Id);
			
			btn_StudentApply.visible = item.Student_data.bCanApply;
			btn_DenyApply.visible = !item.Student_data.bCanApply;
			nSelectedID = item.Student_data.Id;
		}
	}
}