package UI_EquipRemake.AS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.clearTimeout;
	import flash.utils.setTimeout;
	
	import ActionScript3.ItemSlotData;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import fl.transitions.easing.Strong;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.motion.Tween;
	
	public class EquipRemakePanel extends MyPanel
	{
		public var equipPart_weapon_btn:RadioButton;
		public var equipPart_helmet_btn:RadioButton;
		public var equipPart_coat_btn:RadioButton;
		public var equipPart_necklace_btn:RadioButton;
		public var equipPart_bracelet_btn:RadioButton;
		public var equipPart_ring_btn:RadioButton;
		
		public var hint_text_mc:MovieClip;
		public var txt_remake_info:TextField;
		public var remake_slot_mc:MyItemSlot;
		public var slot_FX_mc:MovieClip;
		public var btn_remake:Button;
		
		private static const SLOT_SHOW_DURATION:int = 250;
		
		private var _textShowTween:Tween;
		private var _slotShowTween:Tween;
		private var _textHideTween:Tween;
		private var _slotHideTween:Tween;
		
		private var _equipIdx:int;
		private var _remakeNeedFragments:Array;
		private var _canRemake:Boolean = false;
		private var _resultShowing:Boolean = false;
		private var _curMaterialSlotData:ItemSlotData;
		private var _resultSlotData:ItemSlotData;
		private var _isPlaying:Boolean = false;
		
		private static const LOCAL_TEST:Boolean = false;
		
		public function EquipRemakePanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
			ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			SetWindowTitle("装备重铸");
			equipPart_weapon_btn.addEventListener(ButtonEvent.CLICK, onSelectEquipPart);
			equipPart_helmet_btn.addEventListener(ButtonEvent.CLICK, onSelectEquipPart);
			equipPart_coat_btn.addEventListener(ButtonEvent.CLICK, onSelectEquipPart);
			equipPart_necklace_btn.addEventListener(ButtonEvent.CLICK, onSelectEquipPart);
			equipPart_bracelet_btn.addEventListener(ButtonEvent.CLICK, onSelectEquipPart);
			equipPart_ring_btn.addEventListener(ButtonEvent.CLICK, onSelectEquipPart);
			
			btn_remake.addEventListener(ButtonEvent.CLICK, onEquipRemake);
			btn_remake.enabled = false;
			
			hint_text_mc.visible = false;
			txt_remake_info = hint_text_mc['txt_remake_info'];
			txt_remake_info.text = "";
			//hint text
			_textShowTween = new Tween(3 * SLOT_SHOW_DURATION, 
									hint_text_mc, 
									{alpha:1},
									{ease:Strong.easeInOut, onComplete:onTextShowComplete});
			_textHideTween = new Tween(2 * SLOT_SHOW_DURATION, 
									hint_text_mc, 
									{alpha:0},
									{ease:Strong.easeInOut, onComplete:onTextHideComplete});
			//result
			_slotShowTween = new Tween(SLOT_SHOW_DURATION, 
									remake_slot_mc, 
									{alpha:1},
									{ease:Strong.easeIn, onComplete:onSlotShowComplete});
			_slotHideTween = new Tween(SLOT_SHOW_DURATION, 
									remake_slot_mc, 
									{alpha:0},
									{ease:Strong.easeIn, onComplete:onSlotHideComplete});
			_textShowTween.paused = true;
			_textHideTween.paused = true;
			_slotShowTween.paused = true;
			_slotHideTween.paused = true;
			
			slot_FX_mc.gotoAndStop(1);
			slot_FX_mc.addFrameScript(slot_FX_mc.totalFrames - 1, onAnimationEnd);
			slot_FX_mc.visible = false;
			
			defaultSelectEquipPart();
			
			if(LOCAL_TEST)
			{
				_materialSlotData = new ItemSlotData();
				_materialSlotData.iconName = "1.tga";
				_materialSlotData.quantity = 200;
			}
		}
		
		private function defaultSelectEquipPart():void
		{
			equipPart_weapon_btn.selected = true;
			_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_WEAPON;
			ExternalInterface.call("ASOnSelectEquipType", _equipIdx);
			//
			if(LOCAL_TEST)
			{
				UCUpdateMaterialInfo(_materialSlotData, 10);
			}
		}
		
		//test code
		private var _materialSlotData:ItemSlotData;
		//test code
		
		private function onSelectEquipPart(evt:ButtonEvent):void
		{
			var btn:RadioButton = evt.currentTarget as RadioButton;
			switch(btn)
			{
				case equipPart_weapon_btn:
				{
					_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_WEAPON;
					break;
				}
				case equipPart_helmet_btn:
				{
					_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_HAT;
					break;
				}
				case equipPart_coat_btn:
				{
					_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_CHEST_ARMOR;
					break;
				}
				case equipPart_necklace_btn:
				{
					_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_NECKLACE;
					break;
				}
				case equipPart_bracelet_btn:
				{
					_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_BRACELET;
					break;
				}
				case equipPart_ring_btn:
				{
					_equipIdx = ConfigConstants.ITEMSUBTYPE_EQUIP_RING;
					break;
				}
				default:
				{
					break;
				}
			}
			if(!_isPlaying)
			{
				ExternalInterface.call("ASOnSelectEquipType", _equipIdx);
				//
				if(LOCAL_TEST)
				{
					UCUpdateMaterialInfo(_materialSlotData, 10);
				}
			}
		}
		
		public function UCUpdateMaterialInfo(itemData:Object, needFragmentsCnt:int):void
		{
			_curMaterialSlotData = itemData as ItemSlotData;
			remake_slot_mc.SetDataObj(itemData);
			var curFragmentsCnt:int = remake_slot_mc.quantity;
			_canRemake = (curFragmentsCnt >= needFragmentsCnt);
			var curCntColor:String = _canRemake ? "'#84ec60'" : "'#ff0000'";
			remake_slot_mc.valueAmount.htmlText = "<font color=" + curCntColor + ">"+ needFragmentsCnt.toString() +  "/" + curFragmentsCnt.toString() + "</font>";
			btn_remake.enabled = (!_isPlaying && _canRemake);
		}
		
		public function UCEquipRemakeResult(resultData:Object):void
		{
			_resultSlotData = resultData['itemSlotData'];
			var itemName:String  = resultData['itemName'];
			txt_remake_info.htmlText = itemName;
			_resultShowing = true;
		}
		
		public function onEquipRemake(evt:ButtonEvent):void
		{
			_slotHideTween.duration = SLOT_SHOW_DURATION;
			_slotHideTween.paused = false;
			_slotShowTween.paused = true;
			ExternalInterface.call("ASOnEquipRemake", _equipIdx);
			_isPlaying = true;
			btn_remake.enabled = false;
			//
			if(LOCAL_TEST)
			{
				_resultSlotData = new ItemSlotData();
				_resultSlotData.iconName = "0.tga";
				UCEquipRemakeResult({itemSlotData:_resultSlotData, itemName:"装备" + _equipIdx});
			}
		}
		
		private function onTextShowComplete(t:Tween):void
		{
			//Todo:delay hide result
			var delay:int = setTimeout(
				function delayHideResult():void
				{
					clearTimeout(delay);
					_textShowTween.paused = true;
					_textHideTween.paused = false;
					
					_slotHideTween.duration = SLOT_SHOW_DURATION;
					_slotHideTween.paused = false;
				}, SLOT_SHOW_DURATION);
		}
		
		private function onTextHideComplete(t:Tween):void
		{
			hint_text_mc.visible = false;
			_textHideTween.paused = true;
		}
		
		private function onSlotShowComplete():void
		{
			_slotShowTween.paused = true;
			if(_resultShowing)
			{
				_resultShowing = false;
				hint_text_mc.alpha = 0.1;
				hint_text_mc.visible = true;
				_textShowTween.paused = false;
				_textHideTween.paused = true;
			}
			else
			{
				_slotHideTween.paused = true;
				_isPlaying = false;
				btn_remake.enabled = _canRemake;
			}
		}
		
		private function onSlotHideComplete():void
		{
			if(!_resultShowing)//hide result slot complete
			{
				_slotShowTween.duration = SLOT_SHOW_DURATION;
				_slotShowTween.paused = false;
				_slotHideTween.paused = true;
				ExternalInterface.call("ASOnSelectEquipType", _equipIdx);
				//
				if(LOCAL_TEST)
				{
					_materialSlotData.quantity = _materialSlotData.quantity - 10;
					UCUpdateMaterialInfo(_materialSlotData, 10);
				}
			}
			else//to show result slot
			{
				remake_slot_mc.SetDataObj(_resultSlotData);
				remake_slot_mc.invalidate();
				_slotHideTween.paused = true;
				_slotShowTween.duration = 0.5 * SLOT_SHOW_DURATION;
				_slotShowTween.paused = false;
				slot_FX_mc.gotoAndPlay(1);
				slot_FX_mc.visible = true;
				//sound
				playSound("EquipRemakeSuccess_FX");
			}
		}
		
		private function onAnimationEnd():void
		{
			slot_FX_mc.stop();
			slot_FX_mc.visible = false;
		}
	}
}