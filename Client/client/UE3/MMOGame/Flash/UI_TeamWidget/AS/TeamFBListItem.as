package UI_TeamWidget.AS
{

	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.events.TextEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.text.TextField;

	public class TeamFBListItem extends ListItemTreeRenderer
	{
		public var TitleItem_Red:TeamFBListItemTitle;
		public var TitleItem_Yellow:TeamFBListItemTitle;
		public var TitleItem_Green:TeamFBListItemTitle;

		//public var FBItem_Detail:TeamFBListItemDetail;
		public var targetId:int = -1;
		public var targetType:int = -1;
		
		public var bSelectedItem:Boolean = false;

		override protected function configUI():void
		{
			super.configUI();
			visible = false;
			setUpdateDataCallBack(updateData);
		}

		public function SetSelected(bSel:Boolean):void
		{
			bSelectedItem = bSel;

			if(TitleItem_Red.visible)
			{
				TitleItem_Red.selected=bSel;
			}
			if(TitleItem_Yellow.visible)
			{
				TitleItem_Yellow.selected=bSel;
			}
			if(TitleItem_Green.visible)
			{
				TitleItem_Green.selected=bSel;
			}
		}

		public function updateData(data:Object):void
		{
			if (data)
			{
				SetSelected(this.selected);
				visible = true;
				if (data.difficulty == 0)
				{
					TitleItem_Red.visible = false;
					TitleItem_Green.visible = true;
					TitleItem_Yellow.visible = false;
					TitleItem_Green.setDataObject(data);
				}
				else if (data.difficulty == 1)
				{
					TitleItem_Red.visible = false;
					TitleItem_Green.visible = false;
					TitleItem_Yellow.visible = true;
					TitleItem_Yellow.setDataObject(data);
				}
				else if (data.difficulty == 2)
				{
					TitleItem_Red.visible = false;
					TitleItem_Green.visible = false;
					TitleItem_Yellow.visible = true;
					TitleItem_Yellow.setDataObject(data);
				}
				else
				{
					TitleItem_Red.visible = true;
					TitleItem_Green.visible = false;
					TitleItem_Yellow.visible = false;
					TitleItem_Red.setDataObject(data);
				}
				targetId = data.TargetId;
				targetType = data.TargetType;
			}
			else
			{
				visible = false;
				targetId = -1;
				targetType = -1;
			}


		}

		public function testFunc():void
		{
			var hy:int = TitleItem_Red.height;
			var ty:int = height;

			//var height_old = height;
			//height = hy;
			//scaleY = 1;
			//invalidateSize();
			//TitleItem_Red.height = ty;
			//TitleItem_Red.scaleY = 1;
			//trace("TY = ", ty);
			//height = hy;
		}
	}

}