package UI_DailySignIn.AS3
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.filters.BevelFilter;
	import flash.filters.ColorMatrixFilter;
	import flash.filters.GlowFilter;
	import flash.text.TextField;
	
	import ActionScript3.MyIconConponent;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.utils.Constraints;
	
	public class DailySignInRewardItem extends ListItemRenderer
	{
		public var slot_mc:MyItemSlot;
		public var new_hint_mc:MovieClip;
		public var obtain_sign_mc:MovieClip;
		
		private var _grayFilter:ColorMatrixFilter;
		private var _textBevelFilter:BevelFilter;
		private var _textGlowFilter:GlowFilter;
		
		private var _isGotten:Boolean = false;
		
		public function DailySignInRewardItem()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren = this.mouseEnabled = true;
			slot_mc.DisableDrag = true;
			new_hint_mc.visible = false;
			new_hint_mc.gotoAndStop(1);
			new_hint_mc.mouseChildren = new_hint_mc.mouseEnabled = false;
			obtain_sign_mc.visible = false;
			obtain_sign_mc.mouseChildren = obtain_sign_mc.mouseEnabled = false;
			_grayFilter = StyleType.getInstance().getGrayFilter();
			_textBevelFilter = textField.filters[0];
			_textGlowFilter = textField.filters[1];
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			var itemData:DailySignInRewardItemData = data as DailySignInRewardItemData;
			if(itemData != null)
			{
				this.label = itemData.SignInIdx.toString() + "天";
				this.selected = itemData.IsCurSignInDay;
				if(itemData.IsCurSignInDay)
				{
					new_hint_mc.visible = true;
					new_hint_mc.gotoAndPlay(1);
				}
				else
				{
					new_hint_mc.visible = false;
					new_hint_mc.gotoAndStop(1);
				}
				slot_mc.SetSlotType(itemData.SlotType);
				slot_mc.SetData(itemData.ItemNum, itemData.IconName, itemData.ItemID, "", 0, -1, -1);
				if(_isGotten != itemData.IsGotten)
				{
					_isGotten = itemData.IsGotten;
					setIconGray(slot_mc, _isGotten);
					if(_isGotten)
					{
						_textBevelFilter.shadowColor = 0xdddddd;
						_textBevelFilter.highlightColor = 0x9a9a9a;
						textField.filters = [_textBevelFilter, _textGlowFilter];
					}
					else
					{
						_textBevelFilter.shadowColor = 0xfff5cd;
						_textBevelFilter.highlightColor = 0xffb73a;
						textField.filters = [_textBevelFilter, _textGlowFilter];
					}
					obtain_sign_mc.visible = _isGotten;
				}
			}
		}
		
		public function setIconGray(displayObj:DisplayObject, gray:Boolean):void
		{
			if(! displayObj)
			{
				return;
			}
			
			if(gray)
			{
				displayObj.filters = [_grayFilter];
			}
			else
			{
				displayObj.filters = null;
			}
		}
	}
}