package UI_AuctionHouse.AS
{
	import flash.events.Event;
	import flash.text.TextField;
	
	import ActionScript3.TreeListData;
	import ActionScript3.controls.StateUIComponent;
	
	public class AuctionListItem_ItemCategory_Lv1 extends StateUIComponent 
	{				
		public var txt_caption:TextField;
		var _dat:AuctionItemCategoryData;
		private var _label:String;
		
		public function AuctionListItem_ItemCategory_Lv1()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			//addEventListener(MouseEvent.CLICK, onClick);			
		}
		
		//txt_caption is not constant, need manually update it when selected state changed
		override public function set selected(value:Boolean):void
		{
			super.selected =  value;
			if(_label != "")
			{
				if(_label != txt_caption.text)
				{
					txt_caption.text = _label;
				}
			}
		}
		
		function onClick(e:Event)
		{
			//_dat.isExpanded = !_dat.isExpanded;
		}
		
		public function updateData(dat:AuctionItemCategoryData):void
		{			
			//visible = dat.visible;
			_dat = dat;
			txt_caption.text = _label = dat.label;
			
			if (dat.type == TreeListData.C_Type_Branch_Closed)
			{
				this.selected = false;
			}
			else
			{
				this.selected = true;
			}
		}
	}
	
}
