package UI_LoginWidget.AS3.AppearanceModule
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Rectangle;
	
	import ActionScript3.Common.CustomScrollBar;
	
	import UI_LoginWidget.AS3.InputNameMC;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.core.UIComponent;
	
	public class OperationPanel extends UIComponent
	{
		public var scroll_bar_mc:CustomScrollBar;
		public var scrolling_view_mc:ScrollingView;
		public var display_mc:OperationList;
		
		public var btn_ReturnRole:Button;
		public var btn_create:Button;
		
		public var btn_reset:Button;
		public var btn_random:Button;
		
		public var input_mc:InputNameMC;
		
		public function OperationPanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			btn_create.addEventListener(MouseEvent.CLICK,ClickCreate );
			
			btn_reset.addEventListener(MouseEvent.CLICK, OnRestAll);
			btn_random.addEventListener(MouseEvent.CLICK, OnRandomCreate );
		}
		
		private function ClickCreate():void
		{
			if(input_mc.bSaveRole){
				var createName:String = input_mc.input_Name.text;
				ExternalInterface.call( "CreateRole", createName );
			}
		}
		
		private function OnRestAll():void
		{
			ExternalInterface.call( "ASCallResetAll" );
			display_mc.resetData();
		}
		
		private function OnRandomCreate():void
		{
			var randomResult:Array = display_mc.getRandomResult();
			ExternalInterface.call( "ASCallRandomCreate",  randomResult);
		}
		
		public function UCSetAppearanceData(data:Array):void
		{
		//	data = getTestData();//test 
			display_mc.updateData(data);
		}
		
		public function updateScrollingView(focusRec:Rectangle = null):void
		{
			scrolling_view_mc.displayMc = display_mc;
			scrolling_view_mc.scrollBar = scroll_bar_mc;
			if(focusRec != null){
				if(focusRec.y + focusRec.height > scrolling_view_mc.height)
				{
					scroll_bar_mc.position = focusRec.y + focusRec.height - scrolling_view_mc.height;
				}
			}
		}
		
		//test code
		private static const VALUE_FOR_TPYE:Array = [0,1,2,3];
		private static const TITLE_FOR_TYPE:Array = ["发型","发色","脸型","肤色"];
		private static const NUM_FOR_TYPE:Array = [2,2,8,8];
		
		private function getTestData():Array
		{
			var result:Array = [];
			var group:GroupData_Appearance;
			var itemsNum:int;
			var itemData:ItemData_Appearance;
			for(var i:int = 0; i < NUM_FOR_TYPE.length; i++)
			{
				group = new GroupData_Appearance();
				group.type = VALUE_FOR_TPYE[i];
				group.title = TITLE_FOR_TYPE[i];
				group.selectedIndex = 0;
				itemsNum = NUM_FOR_TYPE[i];
				group.itemsData = [];
				for(var j:int = 0; j < itemsNum; j++ )
				{
					itemData = new ItemData_Appearance();
					itemData.id = j;
					itemData.imageSrc = ( j % 2 > 0 ? "0.tga" : "1.tga" );
					group.itemsData.push(itemData);
				}
				result.push(group);
			}
			return result;
		}
		//test
	}
}