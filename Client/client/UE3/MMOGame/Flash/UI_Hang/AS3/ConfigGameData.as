package UI_Hang.AS3 {
	
	public class ConfigGameData extends Object{

		public var game1_enable:Boolean = false;
		public var game2_enable:Boolean=false;
		public var game3_enable:Boolean=false;
		public var HideName_my:Boolean = false;
			
		public var HideName_hero:Boolean = false;
		public var HideNameOther_my:Boolean = false;
		public var HideNameOther_hero:Boolean = false;
			
		public var HideNameFamily_my:Boolean = false;
		public var HideNameFamily_other:Boolean = false;
		public var HideNameMonster:Boolean = false;
		public var HideNameDrop:Boolean = false;

		public var DrawBlood_my:Boolean = true;
		public var DrawBlood_other:Boolean=true;
		public var DrawBlood_monster:Boolean = true;
		public var HideHurtNumber_my:Boolean = false;
		public var HideSkillEffect_my:Boolean = false;
		public var HideSkillEffect_other:Boolean = false;
			
		public var DrawGuide:Boolean = true;
		public var DrawChatBubble:Boolean = true;
		public var DrawBloodNumber:Boolean = true;
		public var DrawHurt:Boolean = false;
		public var DrawGameFrame:Boolean = true;
		public var HintFriendOnline:Boolean = true;
		public var HintHidePlayer:Boolean = true;
			
		public var DeclineStrangeChat:Boolean=false;
		public var DeclineInviteTeam:Boolean=false;
		public var DeclineInviteFamily:Boolean=false;
		public var DeclineInviteDisciple:Boolean=false;
		public var DeclineInviteMaster:Boolean=false;
		public var DefaultShift:Boolean=false;//
		public var DeclineShowEnemy:Boolean=false;
		
		public var input1_enable:Boolean=false;
		public var SlotKeyList:Array=[];
		public var input2_enable:Boolean=false;
		public var KeyList:Array;
		
		public var DrawAITip:Boolean=false;
		public var DrawWeather:Boolean=false;
		public var HideHurtNumber_other:Boolean=false;
		public var HintMarkSelf:Boolean=true;
		public var HideSkillEffect_CameraShake:Boolean=true;
		
		public var taskModeType:int=0;//任务模式类型

	}
	
}
