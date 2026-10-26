
package ActionScript3.Handbook
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	
	import ActionScript3.Common.Utils.StyleType;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.interfaces.IUIComponent;
	
	public class HandbookItem extends UIComponent
	{	
		public var obtain_mc:MovieClip;
		public var obtain_gray_mc:MovieClip;
		public var hover_mc:MovieClip;
		public var select_mc:MovieClip;
		public var icon_mc:MovieClip;
		
		public var handbook_data:HandbookData;
		
		private var _index:int = -1;
		
		public function HandbookItem()
		{
			// constructor code
		}
		
		public function get index():int
		{
			return _index;
		}

		public function set index(value:int):void
		{
			_index = value;
		}

		override protected function configUI():void
		{
			super.configUI();
			
			icon_mc.source = null;
			obtain_mc.visible = false;
			hover_mc.visible = false;
			select_mc.visible = false;
			obtain_gray_mc.visible = false;
		}
		
		public function set hover(hover:Boolean):void
		{
			hover_mc.visible = hover;
		}
		
		public function set select(select:Boolean):void
		{
			select_mc.visible = select;
		}

		public function setIconGray(mc:MovieClip, gray:Boolean):void
		{
			if (! mc)
			{
				return;
			}

			mc.filters = null;
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter()];
			}
		}
		
		public function updateItemData(data:HandbookData):void
		{
			handbook_data = data;
			if (handbook_data != null)
			{
				visible = true;
				
				icon_mc.source = String(handbook_data.handbook_icon);
				
				obtain_gray_mc.visible = handbook_data.handbook_invalid;
				if (handbook_data.handbook_invalid)
				{
					setIconGray(icon_mc, false);
					obtain_mc.visible = false;
				}
				else
				{
					setIconGray(icon_mc, !handbook_data.handbook_obtain);
					obtain_mc.visible = handbook_data.handbook_obtain;
				}
			}
			else
			{
				visible = false;
			}
		}
	}
}