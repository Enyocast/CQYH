
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	
	import ActionScript3.Handbook.Common.Description;
	import ActionScript3.Handbook.MapPage.BossList_Map;
	import ActionScript3.Handbook.MapPage.HandbookBossItem;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	
	public class HandbookMapPage extends UIComponent
	{
		public var map_icon_mc:MovieClip;
		
		public var map_item_title_tf:TextField;
		public var map_item_0_mc:MyItemSlot;
		public var map_item_1_mc:MyItemSlot;
		public var map_item_2_mc:MyItemSlot;
		public var map_item_3_mc:MyItemSlot;
		public var map_item_4_mc:MyItemSlot;
		public static const map_item_max_count = 5;
		
		public var map_boss_title_tf:TextField;
		public var map_boss_0_mc:MovieClip;
		public var map_boss_1_mc:MovieClip;
		public var map_boss_2_mc:MovieClip;
		public var map_boss_3_mc:MovieClip;
		public static const map_boss_max_count = 4;
		
		public var goto_position_tf:TextField;
		public var btn_gotoMap:Button;
		public var description_mc:Description;
		public var boss_list_mc:BossList_Map;
		
		public var frame_mc:MovieClip;
		
		public var handbook_data:HandbookData;
		
		private static const MARGIN:Number = 13;
		
		public function HandbookMapPage()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			map_boss_title_tf = boss_list_mc.map_boss_title_tf;
			map_boss_0_mc = boss_list_mc.map_boss_0_mc;
			map_boss_1_mc = boss_list_mc.map_boss_1_mc;
			map_boss_2_mc = boss_list_mc.map_boss_2_mc;
			map_boss_3_mc = boss_list_mc.map_boss_3_mc;
			goto_position_tf.htmlText = "<u>立即前往<u>";
			goto_position_tf.addEventListener(MouseEvent.CLICK, onGotoPositionClick, false, 0, true);
			btn_gotoMap.addEventListener(MouseEvent.CLICK, onGotoMapClick, false, 0, true);
			
			goto_position_tf.visible = false;
			//btn_gotoMap.visible = false;
		}
		
		private function onGotoMapClick(evt:MouseEvent):void
		{
			if (handbook_data)
			{
				if (handbook_data.handbook_temp > 0)
				{
					ExternalInterface.call(ConstansDefine.ASOpenWorldMap, handbook_data.handbook_temp);
				}
			}
		}
		
		private function onGotoPositionClick(evt:MouseEvent):void
		{
			if (handbook_data)
			{
				if (handbook_data.handbook_temp > 0)
				{
					ExternalInterface.call(ConstansDefine.ASGotoPosition, handbook_data.handbook_temp);
				}
			}
		}
		
		public function updateHandbookData(data:HandbookData)
		{
			handbook_data = data;
			if (handbook_data)
			{
				map_icon_mc.source = String(handbook_data.handbook_text0);
				//sound avaliable
				description_mc.soundAvaliable = Boolean(handbook_data.handbook_sound);
				description_mc.updateDescription(handbook_data.handbook_text2);
				
				var i:int = 0;
				var map_item_list:Array = handbook_data.handbook_data0;
				map_item_title_tf.visible = map_item_list.length > 0;
				for (i = 0; i < map_item_max_count; i ++)
				{
					var item_mc:MyItemSlot = this["map_item_" + i + "_mc"] as MyItemSlot;
					if (i < map_item_list.length)
					{
						item_mc.SetData(0, map_item_list[i].item_icon, map_item_list[i].item_id, "", 0, -1, -1);
						item_mc.visible = true;
					}
					else
					{
						item_mc.visible = false;
					}
				}
				boss_list_mc.y = description_mc.y + description_mc.height;
				var map_boss_list:Array = handbook_data.handbook_data1;
				boss_list_mc.frame_mc.height = 1;
				boss_list_mc.visible = map_boss_list.length > 0;
				for (i = 0; i < map_boss_max_count; i ++)
				{
					var boss_mc:HandbookBossItem = this["map_boss_" + i + "_mc"] as HandbookBossItem;
					if (i < map_boss_list.length)
					{
						boss_mc.icon_mc.source = map_boss_list[i].npc_icon;
						boss_mc.name_tf.text = map_boss_list[i].npc_name;
						
						boss_mc.visible = true;
						boss_list_mc.frame_mc.height = boss_mc.y + boss_mc.height;
					}
					else
					{
						boss_mc.visible = false;
					}
				}
				boss_list_mc.height = boss_list_mc.frame_mc.height;
			}
			_height = frame_mc.height = boss_list_mc.y + boss_list_mc.height + MARGIN;
		}
	}
}
























