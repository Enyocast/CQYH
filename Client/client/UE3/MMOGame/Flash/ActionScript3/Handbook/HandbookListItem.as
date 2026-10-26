
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	import flash.trace.Trace;
	
	import ActionScript3.Common.Utils.StyleType;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ListEvent;

	public class HandbookListItem extends ListItemTreeRenderer
	{	
		public var handbook_item_0_mc:HandbookItem;
		public var handbook_item_1_mc:HandbookItem;
		public var handbook_item_2_mc:HandbookItem;
		public var handbook_item_3_mc:HandbookItem;
		public var handbook_item_4_mc:MapListItem_MainPage;
		
		private const VIEW_TYPE_NORMAL:int 	= 0;
		private const VIEW_TYPE_MAP:int 	= 1;
		
		private var _selectedIndex:int = -1;
		private var _globalSelectedItemIndex:int = -1;
		
		
		public function HandbookListItem()
		{
			// constructor code
		}
		
		public function set globalSelectedItemIndex(value:int):void
		{
			_globalSelectedItemIndex = value;
		}

		override protected function configUI():void
		{
			super.configUI();
			var i:int = 0;
			for (i = 0; i < ConstansDefine.NUM_OF_SINGLE_ITEM; ++ i)
			{
				var item_mc:HandbookItem = this["handbook_item_" + i + "_mc"] as HandbookItem;
				if(item_mc != null){
					item_mc.index = i;
					item_mc.addEventListener(MouseEvent.CLICK, onItemClick);
					item_mc.addEventListener("rollOver", onItemRollOver);
					item_mc.addEventListener("rollOut", onItemRollOut);
					item_mc.visible = false;
				}
			}
			setUpdateDataCallBack(updateItemData);
		}
		
		public function onItemRollOver(e:Event)
		{
			playSound("menu_highlight_adv");
			var cur_item_mc:HandbookItem = e.currentTarget as HandbookItem;
			if (cur_item_mc)
			{
				cur_item_mc.hover = true;
				var handbook_data:HandbookData = cur_item_mc.handbook_data;
				ExternalInterface.call("ASShowTips_PlainText_WithString", cur_item_mc, handbook_data.handbook_name);
			}
		}
		
		public function onItemRollOut(e:Event)
		{
			var cur_item_mc:HandbookItem = e.currentTarget as HandbookItem;
			if (cur_item_mc)
			{
				cur_item_mc.hover = false;
				ExternalInterface.call("ASHideTips_Text", cur_item_mc);
			}
		}
		
		public function onItemClick(e:Event)
		{
			playSound("menu_click");
			var cur_item_mc:HandbookItem = e.currentTarget as HandbookItem;
			if (cur_item_mc != null)
			{
				var list_mc:ScrollingList = this.parent.parent as ScrollingList;
				var i:int = 0;
				var curIndex:int = cur_item_mc.index;
				var rowCount:int = list_mc.rowCount;
				for (i = 0; i < rowCount; i ++)
				{
					var list_item:HandbookListItem = list_mc.getRendererAt(i) as HandbookListItem;
					if (list_item){
						list_item.itemSelected = false;//will set all _selectedIndex to -1
						list_item.globalSelectedItemIndex = curIndex;
					}
				}
				cur_item_mc.select = true;
				_selectedIndex = curIndex;
				var handbook_data:HandbookData = cur_item_mc.handbook_data;
				ExternalInterface.call("ASClickHandbookItem", handbook_data.handbook_type, handbook_data.handbook_index);
			}
		}
		
		override public function set selected(value:Boolean):void 
		{
			itemSelected = super.selected = value;
		}
		
		protected function set itemSelected(value:Boolean):void
		{
			if(value){
				_selectedIndex = _globalSelectedItemIndex;
				if(_selectedIndex != -1){
					var selectedItem:HandbookItem = this["handbook_item_" + _selectedIndex + "_mc"] as HandbookItem;
					selectedItem.select = true;
				}
			}else{
				if(_selectedIndex != -1){
					var unSelectedItem:HandbookItem = this["handbook_item_" + _selectedIndex + "_mc"] as HandbookItem;
					unSelectedItem.select = false;
				}
				_selectedIndex = -1;
			}
		}
		
		public function updateItemData(data:Object):void
		{
			if (data)
			{
				this.visible = true;
				var handbook_data:HandbookData = data.handbook_item_data0 as HandbookData;
				if(handbook_data.handbook_ui_type == ConstansDefine.handbook_map){
					updateViewType(VIEW_TYPE_MAP);
					handbook_item_4_mc.updateItemData(handbook_data);
				}else{
					updateViewType(VIEW_TYPE_NORMAL);
					handbook_item_0_mc.updateItemData(handbook_data);
					
					handbook_data = data.handbook_item_data1 as HandbookData;
					handbook_item_1_mc.updateItemData(handbook_data);
					
					handbook_data = data.handbook_item_data2 as HandbookData;
					handbook_item_2_mc.updateItemData(handbook_data);
					
					handbook_data = data.handbook_item_data3 as HandbookData;
					handbook_item_3_mc.updateItemData(handbook_data);
				}
			}
			else
			{
				this.visible = false;
			}
		}
		
		private function updateViewType(viewType:int):void
		{
			if(viewType == VIEW_TYPE_MAP){
				handbook_item_4_mc.visible = true;
				handbook_item_0_mc.visible  = handbook_item_1_mc.visible  = handbook_item_2_mc.visible  = handbook_item_3_mc.visible = false;
			}else if(viewType == VIEW_TYPE_NORMAL){
				handbook_item_4_mc.visible = false;
				handbook_item_0_mc.visible  = handbook_item_1_mc.visible  = handbook_item_2_mc.visible  = handbook_item_3_mc.visible = true;
			}
		}
	}
}
























