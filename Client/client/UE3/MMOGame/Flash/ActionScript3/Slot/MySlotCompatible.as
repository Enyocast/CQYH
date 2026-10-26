
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


	public class MySlotCompatible extends UIComponent
	{
		public var SlotData:MySlotData = null;
		public var SlotRender:MySlotRender = null;
		public var SlotContral:MySlotContral = null;
		
		public var HaveData:Boolean = false;
		private var _selected:Boolean = false;
		

		//兼容旧的数据
		//这个功能很奇特，且是固定的，用于在代码中ASDragRelease 判定是slot类型的控件还是普通控件，用于拖拽辨认
		public var itemtype:String = "itemslot";
		
		public var EquipID:int = -1;
		public var slotType:int  = -1;
		public var SlotType:int= -1;
		public var slotIndex:int = -1;//两者相同

		//public var SlotType:int= -1;//用于与老的兼容
		public var containerID:int = -1;
		public var slotID:int = -1;
		public var ItemTemplateID:int = -1;

        public var isLocked:Boolean = false;//是否锁定(还没学到的技能，未解锁的格子)，禁止移动操作
        public var isUnusable:Boolean = false;

		public var iconName:String= "";
		public var tipsHtml:String= "";
		
		public var itemIndex:int = -1;
		public var UniqueSkillID:int = -1;
		protected function _UpdateData()
		{
			if (SlotData)
			{
				HaveData		= SlotData.HaveData;
				containerID 	= SlotData.containerID;
				slotID 			= SlotData.slotID;
				ItemTemplateID 	= SlotData.itemTemplateID;
				isLocked		= SlotData.isLocked;
				isUnusable		= SlotData.isUnusable;
				iconName		= SlotData.iconName;
				tipsHtml		= SlotData.tipsHtml;
				
				EquipID			= SlotData.EquipID;
				slotType		= SlotData.slotType;
				SlotType		= SlotData.slotType;
				slotIndex		= SlotData.slotIndex;
				
				itemIndex		= SlotData.itemTemplateID;
				UniqueSkillID	= SlotData.itemTemplateID;
			}
		}
		
		public function get selected():Boolean
		{
			return _selected;
		}
		public function set selected(value:Boolean):void
		{
			if (_selected == value)
			{
				return;
			}
			_selected = value;
			if (SlotData)
			{
				SlotData.isSelected = selected;
				if (SlotRender!=null)
				{
					SlotRender.UpdateLightData();
				}
			}
		}		








	}
}