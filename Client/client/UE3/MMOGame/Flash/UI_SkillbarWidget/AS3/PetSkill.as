package UI_SkillbarWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	
	public class PetSkill extends UIComponent {
		
		public var stand:PetSkillIcon;
		public var attack:PetSkillIcon;
		public var type:int;
		override protected function configUI():void
		{
			super.configUI();
			initEvent(stand,0);
			initEvent(attack,1);
			updatePetSkill(0);
		}
		
		private function initEvent(mc:PetSkillIcon,i:int):void
		{
			mc.itemid=i;
		}
		
		//更新
		public function updatePetSkill(statue:int):void
		{
			type=statue;
			if(statue==0)
			{
				stand.updateState(true);
				attack.updateState(false);
			}
			else
			{
				stand.updateState(false);
				attack.updateState(true);
			}
		}
	}
	
}
