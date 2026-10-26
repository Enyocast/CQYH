package UI_SkillTree.SkillTreeAS3
{
	//import ActionScript3.TreeListData;
	
	public class ActiveSkillListItemSingleData extends Object
	{
		public var ItemIdx:int;
		
		public var IsNew:Boolean;
		public var IsCurrent:Boolean;
		public var IsMaxLv:Boolean;
		public var CanLvUp:Boolean;
		
		public var SkillName:String;
		public var SkillLv:int;
		public var SkillExp:String;
		public var SkillRequireLv:int;
		public var IsDisabled:Boolean;
		
		public var SkillInscriptionType:String;
		public var RuneSkillID:int;
		public var SkillID:int;
		public var SkillIconName:String;
		
		//for MyItemSlot::_SlotType
		public var SlotType:int;
	}
}