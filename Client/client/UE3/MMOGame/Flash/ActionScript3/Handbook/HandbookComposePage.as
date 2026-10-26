
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.net.URLLoader;
	import flash.text.TextField;
	
	import ActionScript3.Handbook.HandbookData;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.core.UIComponent;
	
	public class HandbookComposePage extends UIComponent
	{
		public var comp_equip_mc:MovieClip;
		public var comp_item_0_mc:MovieClip;
		public var comp_item_1_mc:MovieClip;
		public var comp_item_2_mc:MovieClip;
		public var comp_item_3_mc:MovieClip;
		public var comp_item_4_mc:MovieClip;
		public var comp_item_5_mc:MovieClip;
		
		public var comp_equip_tf:TextField;
		public var comp_item_0_tf:TextField;
		public var comp_item_1_tf:TextField;
		public var comp_item_2_tf:TextField;
		public var comp_item_3_tf:TextField;
		public var comp_item_4_tf:TextField;
		public var comp_item_5_tf:TextField;
		public var compose_cost_tf:TextField;
		public static const comp_item_max_count = 6;
		
		public var handbook_data:HandbookData;
		
		public function HandbookComposePage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				var compose_item_list:Array = handbook_data.handbook_data0;
				comp_equip_mc.SetData(0, compose_item_list[0].item_icon, compose_item_list[0].item_id, "", 0, -1, -1);
				comp_equip_tf.text = compose_item_list[0].item_name;
				
				var i:int = 0;
				for (i = 0; i < comp_item_max_count; i ++)
				{
					var item_mc:MyItemSlot = this["comp_item_" + i + "_mc"] as MyItemSlot;
					if (i + 1 < compose_item_list.length)
					{
						item_mc.SetData(0, compose_item_list[i + 1].item_icon, compose_item_list[i + 1].item_id, "", 0, -1, -1);
						(this["comp_item_" + i + "_tf"] as TextField).htmlText = compose_item_list[i + 1].item_info;
					}
					else
					{
						item_mc.SetData(0, "", 0, "", 0, -1, -1);
						(this["comp_item_" + i + "_tf"] as TextField).text = "";
						(this["comp_item_" + i + "_tf"] as TextField).htmlText = "";
					}
				}
				compose_cost_tf.text = handbook_data.handbook_text0;
			}
		}
	}
}
























