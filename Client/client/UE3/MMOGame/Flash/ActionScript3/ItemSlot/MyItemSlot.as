
package ActionScript3.ItemSlot
{

	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.display.Stage;
	import flash.display.Scene;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.Label;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.ItemSlotData;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.MyIconConponent;
	import ActionScript3.ItemSlotData;
	import flash.external.ExternalInterface;
	import flash.utils.Timer;
	import flash.utils.getTimer;
	import flash.events.TimerEvent;
	import ActionScript3.Tips.MyTooltips;


	import flash.events.FocusEvent;
	import scaleform.gfx.FocusEventEx;
	import scaleform.gfx.FocusManager;
	import scaleform.gfx.Extensions;
	import scaleform.clik.events.FocusHandlerEvent;
	import flashx.textLayout.conversion.ITextExporter;
	import flash.display.DisplayObject;
	import ActionScript3.ItemSlot.MyItemSlotComponent;
	import flash.ui.MouseCursor;
	import scaleform.clik.events.InputEvent;

	public class MyItemSlot extends Button
	{
		[Inspectable(type = "Boolean",name = "_bDisableDrag")]
		var bDisableDrag = false;//不能拖动

		/** Determines if the button dispatches "click" events when pressed down and held. */
		[Inspectable(defaultValue = "false")]
		public function get DisableDrag():Boolean
		{
			return bDisableDrag;
		}
		public function set DisableDrag(value:Boolean):void
		{
			bDisableDrag = value;
		}

		[Inspectable(type = "Boolean",name = "_bWithBG")]
		var bWithBG = false;//显示背景

		[Inspectable(type = "Boolean",name = "_isHotBar")]
		var isHotBar = false;//是快捷热面板

		//[Inspectable(type="Number", name="_EquipID")]
		public var SlotType:int = -1;//ESlotPanelType  0:包裹 1:技能快捷栏 2:人物装备 3:技能面板。4：NPC商店 5,仓库  6, Stall 所处的面板大类 7，符文Tip 非常规
		//public var PanelType:int = -1; // TipsFromType
		public var itemtype:String;
		public var useLargeIcon:Boolean = false;

		public var ItemTemplateID:int;
		public var quantity:Number = 1;
		public var iconIndex:Number = -1;
		public var itemIndex:Number = -1;
		public var iconName:String = "";
		public var iconNameLast:String = "none";
		public var itemColorLast:Number = 0;
		public var itemColor:Number = 0;
		public var containerID:int = -1;
		public var slotID:int = -1;
		public var EquipID = 0;//装备栏的几号洞 0:无 1:武器，2：上衣 3：裤子 4：鞋子 5：头盔头发
		public var SoulCount:int = 0;
		public var SoulInfo:Array;
		public var _select_border:MovieClip;

		public var newHint:MovieClip;
		public var unusable_mc:MovieClip;
		public var lock_mc:MovieClip;
		public var colorFrame:MovieClip;

		var isLocked:Boolean = false;//是否锁定(还没学到的技能，未解锁的格子)，禁止移动操作
		var isUnusable:Boolean = false;
		var Mode = 0;
		var _dragStarted = false;
		var bOver = false;
		var bPressed = false;

		//cd计时
		var bCDing = false;
		var cdTimer:Timer;
		var cdTotalMiniSec:uint = 0;
		var startMiniSec:uint = 0;
		var curMiniSec:uint = 0;

		public var abnormity_mc:UILoader;
		public var Veins_mc:MovieClip;
		public var itemSlotIcon:MyIconConponent;
		public var CDNum:TextField;//定义外部使用或摆放的控件，用public
		public var CDUnit:TextField;
		public var keyBind:TextField;
		public var valueAmount:TextField;
		public var coolDown:MovieClip;
		public var slotUse:MovieClip;
		public var itemSlotBg:MovieClip;
		public var tipsHtml:String;
		public var mc_star:MovieClip;
		var itemSlotComponentArray:Array;
		public var canChangeSize:Boolean = false;
		public var CRC32:int=0;
		public var isToGray:Boolean=false;

		override protected function preInitialize():void
		{
			constraintsDisabled = true;
			super.preInitialize();
		}

		override protected function configUI():void
		{
			super.configUI();
			this.removeEventListener(InputEvent.INPUT, handleInput);
			// 移除键盘监听事件;
			this.addEventListener( ButtonEvent.PRESS, OnMouseDown );
			this.addEventListener( ButtonEvent.RELEASE_OUTSIDE, OnDragRelease );
			this.addEventListener( ButtonEvent.CLICK, OnDragInSlot );
			this.addEventListener( ButtonEvent.DRAG_OVER, DragOver );
			this.addEventListener( ButtonEvent.DRAG_OUT, DragOut );
			this.addEventListener( MouseEvent.ROLL_OVER, RollOver );//mouse in
			this.addEventListener( MouseEvent.ROLL_OUT, RollOut );//mouse out
			doubleClickEnabled = true;
			this.addEventListener( MouseEvent.DOUBLE_CLICK ,MouseDBClick );
			this.addEventListener(MouseEvent.CLICK , MouseRightClick );
			if ( CDUnit != null)
			{
				CDUnit.visible = false;
			}
			if ( CDNum != null)
			{
				CDNum.visible = false;
			}

			if (lock_mc)
			{
				lock_mc.visible = isLocked;
			}
			if (unusable_mc)
			{
				unusable_mc.visible = isUnusable;
			}
			if (newHint)
			{
				newHint.visible = false;
			}
			if (mc_star)
			{
				mc_star.visible = false;
			}

			if ( SlotType == 1 && Veins_mc != null )
			{
				Veins_mc.visible = false;
			}
			if ( SlotType == 0 && Veins_mc != null )
			{
				Veins_mc.gotoAndStop(19);
			}

			itemtype = "itemslot";

			cdTimer = new Timer(33);
			//timer.addEventListener( TimerEvent.TIMER , OnTimer );

			if (colorFrame)
			{
				colorFrame.visible = false;
			}
			this.selected = false;
		}

		public function ClearComponent():void
		{
			itemSlotComponentArray.splice(0,itemSlotComponentArray.length);
		}

		public function AddComponent( slotComponent:MyItemSlotComponent ):void
		{
			if ( slotComponent != null )
			{
				itemSlotComponentArray.push( slotComponent );
			}
		}

		public function SetData( inquantity:Number, iniconName:String , initemIndex:int, initemtype:String, initemColor:int, incontainerID:int, inslotID:int ):void
		{
			quantity = inquantity;
			//iconIndex = iconIndex;
			//itemtype = initemtype;
			itemIndex = initemIndex;
			iconName = iniconName;
			itemColor = initemColor;
			containerID = incontainerID;
			slotID = inslotID;

			for (var i:int = 0; i < itemSlotComponentArray.length; i++)
			{
				var tComponent:MyItemSlotComponent = itemSlotComponentArray[i] as MyItemSlotComponent;

				if (tComponent)
				{
					tComponent.SetData( inquantity , iniconName , initemIndex, initemtype, initemColor, incontainerID, inslotID );
				}
			}

			UpdateData();
		}

		public function SetDataObj( obj:Object ):void
		{
			var slotData:ItemSlotData = obj as ItemSlotData;
			if (slotData!=null)
			{
				//iconIndex= slotData.iconIndex;
				iconName = slotData.iconName;
				itemColor = slotData.itemColor;
				itemIndex = slotData.itemIndex;
				//itemtype  = slotData.itemtype;
				quantity = slotData.quantity;

				if (slotData.containerID >= 0)
				{
					containerID = slotData.containerID;
				}
				if (slotData.slotID >= 0)
				{
					slotID = slotData.slotID;
				}
				if (slotData.slotType >= 0)
				{
					SlotType = slotData.slotType;
				}
				if (slotData.equipID > 0)
				{
					EquipID = slotData.equipID;
				}
				UpdateData();
			}
			else
			{
				trace( "@@@@@@@@@@@@@@@@@@@@================",SetDataObj);
			}
		}

		public function SetSlotType( nType:int )
		{
			SlotType = nType;
		}

		public function set _SlotType(nType)
		{
			SlotType = nType;
		}

		public function MyItemSlot()
		{
			super();
			visible = true;
			itemSlotComponentArray = new Array  ;
		}


		override public function set width( v:Number ):void
		{
			super.width = v;
			if (unusable_mc)
			{
				if (this.scaleX >= 1)
				{
					unusable_mc.scaleX = 1 / this.scaleX;

					//居中
					unusable_mc.x = ( width/scaleX - unusable_mc.width )/2 ;
				}

			}
		}

		override public function set height( v:Number ):void
		{
			super.height = v;
			if (unusable_mc)
			{
				if (this.scaleY >= 1)
				{
					unusable_mc.scaleY = 1 / this.scaleY;
					//居中
					unusable_mc.y = ( height/scaleY - unusable_mc.height )/2 ;
				}
			}
		}

		public function MouseRightClick(evt:MouseEvent):void
		{
			if ((evt as MouseEventEx).buttonIdx == 1)
			{
				//没必要这里判断 全部提交到US里去 需要处理的再处理 
				ExternalInterface.call("MouseRightClickItem", this, this.SlotType, this.containerID, this.slotID );
				ExternalInterface.call("ASHideTips");
			}
		}

		private function MouseDBClick(evt:MouseEvent):void
		{
			ExternalInterface.call("ASDoubleClickSlot",this, this.SlotType, this.containerID, this.slotID );
		}

		public function OnMouseDown(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASHideTips");
			ExternalInterface.call("MouseLeftPressItem", this, this.SlotType, this.containerID, this.slotID );
			if (bDisableDrag)
			{
				return;
			}
			bPressed = true;
		}

		public function OnDragInSlot(evt:ButtonEvent):void
		{
			if (! _dragStarted)
			{
				bPressed = false;
				ExternalInterface.call("MouseLeftClickItem", this, this.SlotType, this.containerID, this.slotID );
			}
			else
			{
				DragRelease();
			}
		}


		public function DragOver(e:ButtonEvent):void
		{
			ExternalInterface.call("ASDragOver", this, this.SlotType, this.containerID, this.slotID);
		}


		public function DragOut(e:ButtonEvent):void
		{
			ExternalInterface.call("ASDragOut", this, this.SlotType, this.containerID, this.slotID);
			ExternalInterface.call("ASHideTips");

			if (bPressed)
			{
				if (itemSlotIcon != null)
				{
					itemSlotIcon.alpha = 0.3;
				}
				_dragStarted = true;
				ExternalInterface.call("ASStartDrag", this, this.SlotType, this.containerID, this.slotID);
			}
		}

		public function OnDragRelease(e:ButtonEvent):void
		{
			DragRelease();
		}

		private function DragRelease():void
		{
			if (itemSlotIcon != null)
			{
				itemSlotIcon.alpha = 1;
			}
			if (! _dragStarted)
			{
				return;
			}

			ExternalInterface.call("ASTrace", "DragRelease" );
			_dragStarted = false;
			bPressed = false;

			ExternalInterface.call("ASDragRelease", this, this.SlotType, this.containerID, this.slotID );

		}

		protected function RollOver(evt:MouseEvent):void
		{
			if ( itemIndex >= 0 )
			{
				ExternalInterface.call("ASRollOverItemSlot", this, this.SlotType, this.containerID, this.slotID );
				//sound;
				playSound("menu_highlight_adv");
			}
			else if ( isLocked )
			{
				ExternalInterface.call("ASRollOverItemSlot", this, this.SlotType, this.containerID, this.slotID );
			}
		}

		protected function RollOut(evt:MouseEvent):void
		{
			bOver = true;
			ExternalInterface.call("ASRollOutItemSlot",this );
			ExternalInterface.call("ASHideTips");
		}

		//===============================================================================================;
		function OnTimer( e:Event )
		{
			curMiniSec = getTimer();
			var passedMiniSec:int = curMiniSec - startMiniSec;
			var leftSec:int = (int)( ((int)(cdTotalMiniSec - passedMiniSec) + 999) / 1000 );
			//trace( "CD update: leftSec:", leftSec );
			if (leftSec <= 0 )
			{
				coolDown.gotoAndStop(2);
				slotUse.gotoAndStop(1);
				slotUse.visible = false;

				CDNum.visible = false;
				CDUnit.visible = false;

				//
				cdTotalMiniSec = 0;
				StopCDTimer();

				playSound("iCooldown");
				return;
			}

			//
			var nframe:uint = passedMiniSec / cdTotalMiniSec * 240;//240为动画总帧数
			coolDown.gotoAndStop(nframe);

			//
			if ( leftSec >= 60 )
			{
				CDUnit.text = "m";
				CDNum.text = String(  Math.floor(leftSec/60) );
			}
			else
			{
				CDUnit.text = "s";
				CDNum.text = String(leftSec);
			}
		}

		//==================================================================================================
		public function SetCD( leftMiniSec:int, totalMiniSec:int )
		{
			if ( cdTotalMiniSec > 0 )
			{
				//已有倒计时在运行，先停掉
				StopCDTimer();
			}

			//
			StartCDTimer( totalMiniSec - leftMiniSec, totalMiniSec );

			//
			coolDown.gotoAndStop(2);
			slotUse.gotoAndStop(1);
			slotUse.visible = false;

			//
			//var CDSpare = Math.floor((cdTotalMiniSec)/1000);
			var CDSpareSec:uint = (cdTotalMiniSec + 999) / 1000;
			if ( CDSpareSec >= 60 )
			{
				CDUnit.text = "m";
				CDNum.text = String( Math.floor(CDSpareSec/60) );
			}
			else
			{
				CDUnit.text = "s";
				CDNum.text = String(CDSpareSec);
			}

			CDUnit.visible = true;
			CDNum.visible = true;

		}

		//
		public function SetPublicCD( leftMiniSec:int, totalMiniSec:int )
		{
			SetCD( leftMiniSec, totalMiniSec );
		}

		//-------------------------------------------------------------------------------------------------------
		public function StopCDTimer()
		{
			if ( cdTimer && bCDing )
			{
				cdTimer.stop();
				cdTimer.removeEventListener( TimerEvent.TIMER , OnTimer );
			}

			bCDing = false;
			startMiniSec = 0;
			curMiniSec = 0;
		}
		//-----------------------------------------------------------------------------------------------------
		public function StartCDTimer( passedMiniSec:int, totalMiniSec:int )
		{
			bCDing = true;
			cdTotalMiniSec = totalMiniSec;
			curMiniSec = getTimer();

			if ( curMiniSec > passedMiniSec )
			{
				startMiniSec = curMiniSec - passedMiniSec;
			}
			else
			{
				cdTotalMiniSec = totalMiniSec - passedMiniSec;
				startMiniSec = curMiniSec;
			}

			if (cdTimer)
			{
				cdTimer.addEventListener( TimerEvent.TIMER , OnTimer );
				cdTimer.start();
			}

			//ExternalInterface.call( "ASTrace", "StartCDTimer bCDing:" + bCDing + " cdTotalMiniSec:" + cdTotalMiniSec + " curMiniSec:" + curMiniSec );
		}
		//-----------------------------------------------------------------------------------------------------
		public function CancelCD()
		{
			coolDown.gotoAndStop(2);

			CDNum.visible = false;
			CDUnit.visible = false;

			//
			ExternalInterface.call( "ASTrace", "CancelCD cdTotalMiniSec:" + cdTotalMiniSec );
			cdTotalMiniSec = 0;
			StopCDTimer();
		}

		//======================================================================================================
		private function UpdateData():void
		{
			if ( iconName == "" )
			{
				if (itemSlotIcon != null && itemSlotIcon.IconLoader_mc && iconName!=iconNameLast)
				{
					itemSlotIcon.IconLoader_mc.source = "img://MMO_UIIcon.icon.blank";
					iconNameLast = iconName;
				}
			}
			else
			{
				if (itemSlotIcon != null && itemSlotIcon.IconLoader_mc && iconName!=iconNameLast)
				{
					itemSlotIcon.IconLoader_mc.source = "img://" + iconName;
					iconNameLast = iconName;
				}
			}

			if (itemSlotIcon && itemColorLast!=itemColor)
			{
				itemSlotIcon.slotIcon_bg_mc.gotoAndStop(itemColor + 1);
				itemColorLast = itemColor;
			}

			if (valueAmount)
			{
				valueAmount.text = ( (quantity == 1||quantity == 0) ? "" : String(quantity) );
			}
		}

		public function set MarkLocked( isToMarkLocked:Boolean )
		{
			if (mc_star)
			{
				mc_star.visible = isToMarkLocked;
				ExternalInterface.call( "ASTrace", "MarkLocked: " + mc_star.visible + ":" + isToMarkLocked );
			}

		}
		public function get MarkLocked():Boolean
		{
			return lock_mc.visible;
		}

		public function set isSlotLocked( isToLock:Boolean )
		{
			isLocked = isToLock;
			if (lock_mc)
			{
				lock_mc.visible = isLocked;
			}
		}

		public function get isSlotLocked():Boolean
		{
			return isLocked;
		}

		public function set isSlotUnusable( unusable:Boolean )
		{
			isUnusable = unusable;
			if (unusable_mc)
			{
				unusable_mc.visible = isUnusable;
			}
		}

		public function get isSlotUnusable():Boolean
		{
			return isUnusable;
		}

		override public function set selected(value:Boolean):void
		{
			//super.selected = value;// 这行代码会导致选中后显示不对
			if (_select_border==null)
			{
				_select_border = (getChildByName("_select_border") as MovieClip);
			}
			if (_select_border)
			{
				_select_border.visible = value;
			}
		}


		// Ablility to set actual metric size, since we override it.
		override public function setActualSize(newWidth:Number, newHeight:Number):void
		{
			if (canChangeSize)
			{
				super.setActualSize( newWidth , newHeight );
			}
			else
			{
				if (super.width != newWidth || _width != newWidth)
				{
					super.width = _width = newWidth;
				}

				if (super.height != newHeight || _height != newHeight)
				{
					super.height = _height = newHeight;
				}
			}


		}


	}
}