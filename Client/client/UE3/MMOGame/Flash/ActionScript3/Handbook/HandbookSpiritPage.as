
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
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class HandbookSpiritPage extends UIComponent
	{
		public var frame_mc:MovieClip;
		public var spirit_icon_mc:MovieClip;
		public var spirit_level_mc:DropdownMenu;
		public var spirit_effect_tf:TextField;
		public var spirit_get_tf:TextField;
		public var spirit_desc_tf:TextField;
		
		public var handbook_data:HandbookData;
		
		public function HandbookSpiritPage()
		{
			// constructor code
			
		}
		
		override protected function configUI():void
		{
			super.configUI();
			spirit_level_mc.dataProvider = new DataProvider();
			spirit_level_mc.addEventListener(Event.CHANGE, onChangeSelect);
			spirit_level_mc.selectedIndex = 0;
			
			spirit_icon_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
			spirit_icon_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
		}
		
		public function hideDropdownList():void
		{
			if(spirit_level_mc.selected){
				spirit_level_mc.close();
			}
		}
		
		public function onChangeSelect()
		{
			if (handbook_data)
			{
				var spirit_list:Array = handbook_data.handbook_data0;
				if (spirit_list.length > 0)
				{
					var spirit_data:Object = spirit_list[spirit_level_mc.selectedIndex] as Object;
					spirit_icon_mc.source = spirit_data.spirit_icon;
		       	 	spirit_effect_tf.htmlText = spirit_data.spirit_effect;
				}
			}
		}
		
		function onRollOverHeavenGasSlot( e:Event )
		{
			if (handbook_data)
			{
				var spirit_list:Array = handbook_data.handbook_data0;
				if (spirit_list.length > 0)
				{
					var spirit_data:Object = spirit_list[spirit_level_mc.selectedIndex] as Object;
					ExternalInterface.call("ASShowTips_HeavenGasExchangeSlot", this, spirit_data.spirit_id);
				}
			}
		}

		function onRollOutHeavenGasSlot( e:Event )
		{
			if (handbook_data)
			{
				ExternalInterface.call("ASHideTips_HeavenExchangeGasSlot" );
			}
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
		       	spirit_get_tf.htmlText = handbook_data.handbook_text0;
				updateDescription(handbook_data.handbook_text1);
				
				spirit_level_mc.dataList = handbook_data.handbook_data1;
				spirit_level_mc.SplitData();
				spirit_level_mc.selectedIndex = 0;
			}
		}
		
		private function updateDescription(info:String):void
		{
			info = "\t" + info;
			spirit_desc_tf.htmlText = info;
			var bottom:Number = (spirit_desc_tf.getCharBoundaries(info.length - 1)).bottom;
			spirit_desc_tf.height = bottom + 13;
			_height = frame_mc.height = spirit_desc_tf.y + spirit_desc_tf.height;
		}
	}
}
























