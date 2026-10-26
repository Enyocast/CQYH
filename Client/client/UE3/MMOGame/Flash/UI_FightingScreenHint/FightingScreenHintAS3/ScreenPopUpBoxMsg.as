package UI_FightingScreenHint.FightingScreenHintAS3
{
	import flash.external.ExternalInterface;

	import UI_FightingScreenHint.FightingScreenHintAS3.ScreenPopUpBoxMsgComponent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;

	public class ScreenPopUpBoxMsg extends UIComponent
	{
		public var SkillLearnedMsgMC:ScreenPopUpBoxMsgComponent;
		
		public var SkillSlotUnlockMsgMC:ScreenPopUpBoxMsgComponent;
		var SkillSlotUnlockMsgUnlockSlotTf:TextField;
		
		public var SkillLevelUpMsgMC:ScreenPopUpBoxMsgComponent;
		
		public var FBAchievementsMC:ScreenPopUpBoxMsgComponent;
		
		public var FBDifficultyUnlockMC:ScreenPopUpBoxMsgComponent;
		
		override protected function configUI():void
		{
			super.configUI();
			
			SkillLearnedMsgMC.visible = false;
			SkillLearnedMsgMC.InfoType = 1;
			var skillLearnedMsgUnlokIconMc:MovieClip = SkillLearnedMsgMC.getChildByName( "UnlockIconMc" ) as MovieClip;
			skillLearnedMsgUnlokIconMc.visible = false;
			var skillLearnedMsgUnlockSlotTf:TextField = SkillLearnedMsgMC.getChildByName( "UnlockSlotTf" ) as TextField;
			skillLearnedMsgUnlockSlotTf.visible = false;
			
			SkillSlotUnlockMsgMC.visible = false;
			SkillSlotUnlockMsgMC.InfoType = 2;
			SkillSlotUnlockMsgUnlockSlotTf = SkillSlotUnlockMsgMC.getChildByName( "UnlockSlotTf" ) as TextField;
				
			SkillLevelUpMsgMC.visible = false;
			SkillLevelUpMsgMC.InfoType = 3;
			
			FBAchievementsMC.visible = false;
			FBAchievementsMC.InfoType = 5;
			
			FBDifficultyUnlockMC.visible = false;
			FBDifficultyUnlockMC.InfoType = 5;
			
		}
		
		public function UCSetMsgInfo( showType:int, titleStr:String, detailStr:String, iconName:String, magicString:String )
		{
			visible = true;
			//SkillLearnedMsgMC.visible = false;
			//SkillSlotUnlockMsgMC.visible = false;
			//SkillLevelUpMsgMC.visible = false;
			//FBAchievementsMC.visible = false;
			//FBDifficultyUnlockMC.visible = false;
			
			switch( showType )
			{
				case 1:
				SkillLearnedMsgMC.visible = true;
				SkillLearnedMsgMC.SetInfo( titleStr, detailStr, iconName );
				//sound
				playSound("Skill_Learned_FX");
				break;
				
				case 2:
				SkillSlotUnlockMsgMC.visible = true;
				SkillSlotUnlockMsgMC.SetInfo( titleStr, detailStr, iconName );
				SkillSlotUnlockMsgUnlockSlotTf.text = magicString;
				break;
				
				case 3:
				SkillLevelUpMsgMC.visible = true;
				SkillLevelUpMsgMC.useImageText(showType);//hard code : show image text of title 
				SkillLevelUpMsgMC.SetInfo( titleStr, detailStr, iconName );
				break;
				
				case 5:
				FBAchievementsMC.visible = true;
				FBAchievementsMC.SetInfo( titleStr, detailStr, iconName );
				break;
				
				case 6:
				FBDifficultyUnlockMC.visible = true;
				FBDifficultyUnlockMC.useImageText(showType);
				FBDifficultyUnlockMC.SetInfo( titleStr, detailStr, iconName );
				break;
			}
			
		}
	}
}