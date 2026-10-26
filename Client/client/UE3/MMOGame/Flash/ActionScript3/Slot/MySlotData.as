
package ActionScript3.Slot {

	public class MySlotData extends Object
	{
		public var HaveData:Boolean = false;
		public var SlotRenderClassName:String = "";
		public var containerID:int 	= -1;
        public var slotID:int 		= -1;		
        public var isLocked:Boolean = false;//是否锁定(还没学到的技能，未解锁的格子)，禁止移动操作
        public var isUnusable:Boolean = false;
		public var isSelected:Boolean = false;
		public var iconName:String= "";
		public var tipsHtml:String= "";
		public var itemTemplateID:int = -1;
		
		public var EquipID:int = -1;
		public var slotType:int = -1;
		public var slotIndex:int = -1;
		
		//外观性质
		public var slotWidth:int = 0;
		public var slotHeight:int = 0;		
		
		//是否变灰
		public var IsGray:Boolean = false;
		
	};
}