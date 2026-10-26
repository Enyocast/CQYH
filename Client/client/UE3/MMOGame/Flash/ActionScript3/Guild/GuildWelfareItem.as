//
// 家族福利
//
package ActionScript3.Guild
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	
	public class GuildWelfareItem extends UIComponent
	{	
		public var guild_welfare_select_mc:MovieClip;
		public var guild_welfare_icon_mc:MovieClip;
		public var guild_welfare_level_tf:TextField;
		//public var guild_welfare_name_tf:TextField;
		public var guild_welfare_hover_mc:MovieClip;
		
		public var curBuffSlotID:int;
		public var BuffOwnerID:int;
		public var curBuffID:int;
		public var curBuffLevel:int;
		
		public var guild_welfare_id:int;
	
		public function GuildWelfareItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			guild_welfare_id = 0;
					
			curBuffSlotID = -1;
			BuffOwnerID = 0;
			curBuffID = 0;
			curBuffLevel = 0;
				
			guild_welfare_select_mc.visible = false;
			guild_welfare_hover_mc.visible = false;
			guild_welfare_icon_mc.source = null;
			guild_welfare_level_tf.text = "0/0";
			//guild_welfare_name_tf.text = "";
			//guild_welfare_name_tf.visible = true;
		}
		
		public function showTips()
		{
			ExternalInterface.call("ASShowTips_BuffSlot", this);
			guild_welfare_hover_mc.visible = true;
		}
		
		public function hideTips()
		{
			ExternalInterface.call("ASRollOutItemSlot", this);
			guild_welfare_hover_mc.visible = false;
		}
		
		public function set select(select:Boolean)
		{
			guild_welfare_select_mc.visible = select;
		}

		public function get select():Boolean
		{
			return guild_welfare_select_mc.visible;
		}
		
		public function setIconGray(mc:MovieClip, gray:Boolean)
		{
			if (! mc)
			{
				return;
			}

			mc.filters = null;
			if (gray)
			{
				var matrix:Array = new Array;

				var colorMatrix:ColorMatrix = new ColorMatrix;

				matrix = matrix.concat([0.3086,0.6094,0.082,0,0]);
				matrix = matrix.concat([0.3086,0.6094,0.082,0,0]);
				matrix = matrix.concat([0.3086,0.6094,0.082,0,0]);
				matrix = matrix.concat([0,0,0,1,0]);

				var filter:ColorMatrixFilter = new ColorMatrixFilter(matrix);

				var filters:Array = new Array;
				filters.push( filter );
				mc.filters = [ filter ];
			}
		}
		
		public function updateItemData(data:Object):void
		{
			guild_welfare_id = 0;
			
			curBuffSlotID = -1;
			BuffOwnerID = 0;
			curBuffID = 0;
			curBuffLevel = 0;
				
			guild_welfare_icon_mc.source = null;
			guild_welfare_level_tf.text = "0/0";
			//guild_welfare_name_tf.text = "";
					
			if (data != null)
			{
				visible = true;
				
				guild_welfare_id = data.guild_wel_id;
				curBuffID = data.guild_wel_buff;
		
				guild_welfare_icon_mc.source = "img://" + String(data.guild_wel_icon_name);
				setIconGray(guild_welfare_icon_mc, data.guild_wel_level < 1);
				
				guild_welfare_level_tf.text = String(data.guild_wel_level) + "/" + String(data.guild_wel_max_level);
				//guild_welfare_name_tf.text = String(data.guild_wel_name);
			}
			else
			{
				visible = false;
			}	
		}
	}
}
























