package UI_SkillTree.SkillTreeAS3
{
	import scaleform.clik.core.UIComponent;
	
	public class ActiveSkillsListItemInscription extends UIComponent
	{
		private var _UniqueSkillID:int;
		
		public function ActiveSkillsListItemInscription()
		{
			super();
		}

		public function get UniqueSkillID():int
		{
			return _UniqueSkillID;
		}
		
		public function updateData(RuneSkillID:int, SkillInscriptionType:String):void
		{
			_UniqueSkillID = RuneSkillID;
			gotoAndStop("type_" + SkillInscriptionType);//to do: load type image
		}

	}
}