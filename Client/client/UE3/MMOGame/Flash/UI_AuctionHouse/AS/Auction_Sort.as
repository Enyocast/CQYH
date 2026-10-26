package UI_AuctionHouse.AS
{
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.RadioButton;
	
	public class Auction_Sort extends UIComponent 
	{
		public var rdo_sortAuction:RadioButton;
		public var rdo_sortFixed:RadioButton;
		
	//	public var btn_showSort:Button;

	//	var _isShowSort:Boolean = false;
		
		public function Auction_Sort()
		{
			
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
/*		function setButton(btn:Button):void
		{
			btn_showSort = btn;
			btn_showSort.addEventListener(MouseEvent.CLICK,onShowSort, false, 0, true );
		}
		
		function onShowSort():void
		{
			if(_isShowSort)
			{
				_isShowSort = false;
				showSort(false);
			}
			else
			{
				_isShowSort = true;
				showSort(true);
			}
		}
		
		function showSort(isShow:Boolean):void
		{
			this.visible = isShow;
			btn_showSort.visible = true;
		}
		
		function hideSort():void
		{
			this.visible = false;
			_isShowSort = false;
		}*/
		
		function resetSort():void
		{
			//showSort(false);
			//_isShowSort = false;
			rdo_sortAuction.selected = true;
			rdo_sortFixed.selected = false;
		}
	}
		
}
