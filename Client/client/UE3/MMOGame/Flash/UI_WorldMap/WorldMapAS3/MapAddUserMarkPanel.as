package UI_WorldMap.WorldMapAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	
	import scaleform.clik.controls.TextInput;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.events.ListEvent;
	
	import flash.external.ExternalInterface;
	
	import scaleform.clik.data.DataProvider;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.MyPanel;
	import flash.events.FocusEvent;
	import flash.text.TextField;
	import scaleform.clik.managers.FocusHandler;
	
	public class MapAddUserMarkPanel extends MyPanel
	{
		public var UserMarkNameTf:TextInput;
		public var AddUserMarkBtn:Button;
		public var DelUserMarkBtn:Button;
		public var ChooseUserMarkTypeBtn0:Button;
		public var ChooseUserMarkTypeBtn1:Button;
		public var ChooseUserMarkTypeBtn2:Button;
		public var ChooseUserMarkTypeBtn3:Button;
		public var ChooseUserMarkTypeBtn4:Button;
		public var ChooseUserMarkTypeBtn5:Button;
		
		public var ShareUserMarkList:DropdownMenu;
		public var ShareUserMarkBtn:Button;
		public var defaultTxt:TextField;

		public function init():void
		{
			visible = false;
			UserMarkNameTf.text="";
			UserMarkNameTf.textField.restrict="^ ";
			UserMarkNameTf.textField.condenseWhite=true;
			UserMarkNameTf.defaultText="";
			defaultTxt.mouseEnabled=false;
			ShareUserMarkBtn.addEventListener( MouseEvent.CLICK, onClickShareUserMark );
			UserMarkNameTf.textField.addEventListener(FocusEvent.FOCUS_IN,focusInHandler);
			UserMarkNameTf.textField.addEventListener(FocusEvent.FOCUS_OUT,focusOutHandler);
			ShareUserMarkList.addEventListener(ListEvent.ITEM_CLICK, onClickChangeShareUserMarkTarget);
			
			AddUserMarkBtn.addEventListener( MouseEvent.CLICK, ConfirmAddUserMark );
			DelUserMarkBtn.addEventListener( MouseEvent.CLICK, ConfirmDelUserMark );
			MyWindowsFrame_mc.btn_close.RemoveAddedEventListener();
			MyWindowsFrame_mc.btn_close.addEventListener( MouseEvent.CLICK, CloseUserMarkPanel );
			
/*			var shareTargetDatas:Array = new Array();
			for (var i:int = 0; i < 2; i++)
			{
				var shareTargetData:MapDropDownListData = new MapDropDownListData ;
				shareTargetData.inputedID1 = i;
				shareTargetData.label = "对象" + i;
				shareTargetDatas.push(shareTargetData);
			}
			UpdateWorldMapShareUserMarkkList(shareTargetDatas);*/
		}
		
		private function focusInHandler(evt:FocusEvent):void
		{
			defaultTxt.visible=false;
		}
		
		private function focusOutHandler(evt:FocusEvent):void
		{
			hide();
		}

		//===========================================================================================
		private function ConfirmAddUserMark(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASConfirmAddUserMark" );
		}
		//===========================================================================================
		private function ConfirmDelUserMark(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASConfirmDelUserMark" );
		}
		//===========================================================================================
		private function CloseUserMarkPanel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASCloseUserMarkPanel" );
		}
		//===========================================================================================
		private function onClickShareUserMark(evt:MouseEvent):void
		{
			var itemData:MapDropDownListData = ShareUserMarkList.dataProvider.requestItemAt( ShareUserMarkList.selectedIndex ) as MapDropDownListData;
			
			if( itemData != null )
			{
				ExternalInterface.call( "ASShareUserMark", itemData.inputedID1 );
			}
		}
		//===========================================================================================
		private function onClickChangeShareUserMarkTarget( e:ListEvent ):void
		{
			var itemData:MapDropDownListData = ShareUserMarkList.dataProvider.requestItemAt( e.index ) as MapDropDownListData;
			
			if( itemData != null )
			{
				ExternalInterface.call( "ASChangeShareUserMarkTarget", e.index, itemData.inputedID1 );
			}
			
			//var itemData:MapDropDownListData = e.itemData as MapDropDownListData;
			//if( itemData != null ){
				//ExternalInterface.call( "ASChangeShareUserMarkTarget",  itemData.inputedID1 );
			//}
		}
		//===========================================================================================
		public function UpdateWorldMapShareUserMarkkList( data:Array ):void
		{
			//UserMarkNameTf.defaultText="";
			ShareUserMarkList.dataProvider = new DataProvider(data);
            ShareUserMarkList.invalidateData();
            ShareUserMarkList.selectedIndex = 0;
            ShareUserMarkList.validateNow();
			ShareUserMarkList.menuRowCount=2;
			hide();
		}

		public function SetUserMarkPanelIconName(dat:String):void
		{
			if(dat==" ")
			{
				dat="";
			}
			UserMarkNameTf.text=dat;
			UserMarkNameTf.textField.text=dat;
		}
		public function close():void
		{
			FocusHandler.getInstance().setFocus(null);//关闭焦点
		}
		private function hide():void
		{
			if(UserMarkNameTf.length==0)
			  defaultTxt.visible=true;
			else
			  defaultTxt.visible=false;
		}
	}
}