
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	
	public class HandbookStonePage extends UIComponent
	{
		public var frame_mc:MovieClip;
		public var stone_icon_mc:MovieClip;
		public var stone_level_mc:DropdownMenu;
		public var stone_effect_tf:TextField;
		public var stone_get_tf:TextField;
		public var stone_desc_tf:TextField;
		
		public var handbook_data:HandbookData;
		
		public function HandbookStonePage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			stone_level_mc.dataProvider = new DataProvider();
			stone_level_mc.addEventListener(Event.CHANGE, onChangeSelect);
			stone_level_mc.selectedIndex = 0;
		}
		
		public function hideDropdownList():void
		{
			if(stone_level_mc.selected){
				stone_level_mc.close();
			}
		}
		
		public function onChangeSelect()
		{
			if (handbook_data)
			{
				var stone_list:Array = handbook_data.handbook_data0;
				if (stone_list.length > 0)
				{
					var stone_data:Object = stone_list[stone_level_mc.selectedIndex] as Object;
					stone_icon_mc.SetData(0, stone_data.stone_icon, stone_data.stone_id, "", 0, -1, -1);
		       	 	stone_effect_tf.htmlText = stone_data.stone_effect;
				}
			}
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
		       	stone_get_tf.text = handbook_data.handbook_text0;
					
				stone_level_mc.dataList = handbook_data.handbook_data1;
				stone_level_mc.SplitData();
				stone_level_mc.selectedIndex = 0;
				
				updateDescription(handbook_data.handbook_text2);
			}
		}
		
		private function updateDescription(info:String):void
		{
			info = "\t" + info;
			stone_desc_tf.text = info;
			var bottom:Number = (stone_desc_tf.getCharBoundaries(info.length - 1)).bottom;
			stone_desc_tf.height = bottom + 13;
			_height = frame_mc.height = stone_desc_tf.y + stone_desc_tf.height;
		}
	}
}
























