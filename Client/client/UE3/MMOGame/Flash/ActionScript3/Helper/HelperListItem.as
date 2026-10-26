package ActionScript3.Helper
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import fl.motion.easing.Back;
	import scaleform.clik.core.CLIK;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import ActionScript3.controls.StateUIComponent;

	public class HelperListItem extends ListItemTreeRenderer
	{
		public var helper_list_item_group_mc:HelperListItemGroup;
		public var helper_list_item_title_mc:HelperListItemTitle;

		public function HelperListItem()
		{
		}

		override protected function configUI():void
		{
			trace(">>>>>>>>>>>>>>> HelperListItem::configUI");
			super.configUI();

			// 这里一定要注意设置回调处理函数;
			setUpdateDataCallBack(updateData);
			trace("<<<<<<<<<<<<<<< HelperListItem::configUI");
		}

		function updateData(data:Object):void
		{
			if (data)
			{
				visible = true;
				this.enabled = true;

				helper_list_item_group_mc.visible = false;
				helper_list_item_title_mc.visible = false;
				
				if (data.deepth == 0)
				{
					helper_list_item_group_mc.visible = true;
					helper_list_item_group_mc.updateData(data);
					helper_list_item_group_mc.selected = data.helper_is_select;
				}
				else
				{
					helper_list_item_title_mc.visible = true;
					helper_list_item_title_mc.updateData(data);
					helper_list_item_title_mc.selected = data.helper_is_select;
				}
			}
			else
			{
				visible = false;
			}
		}

		protected override function handleMouseRollOver(event:MouseEvent):void
		{
			super.handleMouseRollOver(event);
		}

		protected override function handleMouseRollOut(event:MouseEvent):void
		{
			super.handleMouseRollOut(event);
		}

		protected override function handleMousePress(event:MouseEvent):void
		{
			super.handleMousePress(event);
		}

		protected override function handleMouseRelease(event:MouseEvent):void
		{
			super.handleMouseRelease(event);
		}

		protected override function handleReleaseOutside(event:MouseEvent):void
		{
			super.handleReleaseOutside(event);
		}


		function onMouseClick(event:MouseEvent)
		{
		}

		function onTraceOver(event:MouseEvent)
		{
		}

		function onTraceOut(event:MouseEvent)
		{
		}

		function onMouseRollOver(event:MouseEvent)
		{
		}

		function onMouseRollOut(event:MouseEvent)
		{
		}

		override public function set selected(value:Boolean):void
		{
			super.selected = value;
			helper_list_item_group_mc.selected = value;
		}
	}
}