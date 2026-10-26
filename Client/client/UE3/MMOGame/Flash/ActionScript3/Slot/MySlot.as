
package ActionScript3.Slot
{

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import ActionScript3.Slot.MySlotData;
	import ActionScript3.Slot.MySlotRender;
	import ActionScript3.Slot.MySlotContral;
	import flash.external.ExternalInterface;

	import ActionScript3.Slot.ItemSlotRender;
	import flash.utils.getDefinitionByName;

	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.Slot.MySlotCompatible;


	public class MySlot extends MySlotCompatible
	{
		[Inspectable(type = "String",name = "DefaultSlotRenderClass")]
		public var CurrentSlotRenderClass:String = "";

		[Inspectable(type = "Boolean",name = "CanDrag",defaultValue = "true")]
		public var CanDrag:Boolean = true;

		override protected function configUI():void
		{
			super.configUI();
			SlotContral = new MySlotContral();//初始化控制器
			mouseChildren = false;
			doubleClickEnabled = true;
			//this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			if (SlotContral!=null)
			{
				SlotContral.Init(this);
			}
			_UpdateData();
		}

		public function onRmoved(e:Event)
		{
			if (SlotContral!=null)
			{
				SlotContral.UnInit();
				SlotContral = null;
			}

			if (SlotRender!=null)
			{
				removeChild(SlotRender);
				SlotRender = null;
			}

			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
		}

		public function SetSlotType( type:int )
		{
			slotType = type;
		}

		public function SetSlotIndex( index:int )
		{
			slotIndex = index;
		}

		public function SetCD(leftMiniSec:int , tolMiniSec:int)
		{
			if (SlotRender!=null)
			{
				SlotRender.SetCD(leftMiniSec , tolMiniSec);
			}
		}

		public function CancelCD()
		{
			if (SlotRender!=null)
			{
				SlotRender.SetCD(0 , 0);
			}
		}

		public function SetDataObj( obj:Object )
		{
			SlotData = obj as MySlotData;
			_UpdateData();
		}
		
		public function set State(frameName:String):void
		{
			SetState(frameName);
		}		
		
		public function SetState( frameName:String ):void
		{
			if (SlotRender!=null)
			{
				SlotRender.gotoAndPlay(frameName);
			}
		}

		public function CanSlotDrag():Boolean
		{
			if (SlotData==null)
			{
				return false;
			}
			if (CanDrag && SlotData.isLocked==false)
			{
				return true;
			}
			return false;
		}

		public function UpdateData():void
		{
			_UpdateData();
		}

		override protected function _UpdateData()
		{
			super._UpdateData();

			//动态创建
			_CreateRenderClass();

			if(SlotData)
			{
				SlotData.slotWidth = width;
				SlotData.slotHeight = height;
			}
			//传递数据
			if (SlotRender!=null)
			{
				SlotRender.SetDataObj(SlotData);
			}
		}


		function _CreateRenderClass()
		{
			var _bCreateRenderFlag:Boolean = false;
			if (SlotRender==null && CurrentSlotRenderClass.length>0)
			{
				_bCreateRenderFlag = true;
			}
			else if (SlotData!=null && SlotData.SlotRenderClassName.length > 0 && CurrentSlotRenderClass != SlotData.SlotRenderClassName)
			{
				CurrentSlotRenderClass = SlotData.SlotRenderClassName;
				_bCreateRenderFlag = true;
			}
			
			if (_bCreateRenderFlag==true)
			{
				var _SlotRenderClass:Class = getDefinitionByName(CurrentSlotRenderClass) as Class;
				if (_SlotRenderClass!=null)
				{
					if (SlotRender!=null)
					{
						removeChild(SlotRender);
						SlotRender = null;
					}

					SlotRender = new _SlotRenderClass   as MySlotRender;
					if (SlotRender)
					{
						_bCreateRenderFlag = false;
						SlotRender.visible = true;
						addChild( SlotRender );
					}
				}
			}			
		}
	}
}