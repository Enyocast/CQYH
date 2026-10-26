
package ActionScript3.Achievement
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.MyIconConponent;
	import scaleform.clik.controls.UILoader;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	import scaleform.clik.controls.ListItemTreeRenderer;	

	public class AchievementCompListItem extends UIComponent
	{
		public var achievement_item_bg_mc:MovieClip;
		public var achievement_item_bg_gray_mc:MovieClip;
		public var achievement_item_lock_mc:MovieClip;
		public var achievement_icon_mc:MovieClip;
		public var achievement_point_mc:MovieClip;
		public var achievement_date_tf:TextField;
		public var achievement_item_parent:Object;
		
		protected var _point_tf:TextField;
		
		private var _achievement_is_obtain_comp:Boolean;

		public function AchievementCompListItem()
		{

		}

		override protected function configUI():void
		{
			super.configUI();
			achievement_item_lock_mc.visible = false;
			_point_tf = achievement_point_mc.getChildByName("point_tf") as TextField;
			updateViewAsObtain(false);
			
			achievement_point_mc.addEventListener("rollOver", function _showTips(e:Event){ showTips(e);});
			achievement_point_mc.addEventListener("rollOut", onItemRollOut);
			
			achievement_item_parent = null;
			//trace("<<<<<<<<<<<<<<< AchievementCompListItem::configUI");
		}
		
		function showTips(e:Event)
		{
			ExternalInterface.call("ASShowTips_PlainText_WithString", this, "成就点数");
		}
		
		public function onItemRollOut(e:Event)
		{
			ExternalInterface.call("ASRollOutItemSlot", this);
		}
		
		public function setIconGray(mc:MovieClip, gray:Boolean)
		{
			if (!mc)
			{
				return;
			}

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
			else
			{
				mc.filters = null;
			}
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				visible = true;
				achievement_icon_mc.source = String(data.achievement_icon_comp);
				//setIconGray(achievement_icon_mc, !data.achievement_is_obtain_comp);
				if(data.achievement_is_obtain_comp != _achievement_is_obtain_comp)
				{
					updateViewAsObtain(data.achievement_is_obtain_comp);
				}
				_point_tf.text = String(data.achievement_point);
				achievement_date_tf.text = String(data.achievement_date_comp);
				
			}
			else
			{
				visible = false;
			}
		}
		
		//set component gray out
		protected function updateViewAsObtain(isObtain:Boolean):void
		{
			_achievement_is_obtain_comp = isObtain;
			achievement_item_bg_mc.visible = isObtain;
			achievement_item_lock_mc.visible = achievement_item_bg_gray_mc.visible = !isObtain;
			//setIconGray(achievement_point_mc,!isObtain);
		}
		
		public function getItemWidth():int
		{
			return this.width;
		}

		public function getItemHeight():int
		{
			return (achievement_item_bg_mc.height + 4);
		}
	}
}