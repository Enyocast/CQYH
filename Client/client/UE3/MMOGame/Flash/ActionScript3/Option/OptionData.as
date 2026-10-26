package ActionScript3.Option
{
	import flashx.textLayout.formats.Float;
	
	public class OptionData extends Object
	{
		public var auto_adjust_perf:Boolean;
		public var notice_auto_adjust:Boolean;
		
		//每隔多久
		public var adjust_interval_check:Number = 30;
		public var adjust_interval_check_Min:Number = 0;
		public var adjust_interval_check_Max:Number = 0;
		public var adjust_interval_check_Step:Number = 0;
		//自动调节的临界帧率
		public var adjust_FPS_check:Number = 25;
		public var adjust_FPS_check_Min:Number = 0;
		public var adjust_FPS_check_Max:Number = 0;
		public var adjust_FPS_check_Step:Number = 0;
		//后台帧率限制
		public var backend_FPS_limit:Number = 10;
		public var backend_FPS_limit_Min:Number = 0;
		public var backend_FPS_limit_Max:Number = 0;
		public var backend_FPS_limit_Step:Number = 0;
		//cpu使用率限制
		public var CPU_usage_limit:Number = 1;
		public var CPU_usage_limit_Min:Number = 0;
		public var CPU_usage_limit_Max:Number = 0;
		public var CPU_usage_limit_Step:Number = 0;
		
		public var wnd_title:String;
		public var video_enable:Boolean;
		public var GPU_List:Array;
		public var GPU_List_Selected_Idx:int;
		public var WndFullscreen:int;
		public var WndSize:Array;
		public var WndSizeIdx:int;
		public var WndSizeFixed:Boolean;
		public var DrawEffectLevel:int;
		public var RecommandLevel:int;
		
		public var TextureLevel:int;
    	public var ShadowLevel:int;
    	public var WaterLeval:int;
    	public var ParticleLevel:int;
    	public var PlayersLevel:int;
    	public var MaterialLevel:int;
		public var MSAA:Boolean;
		public var VerticalSync:Boolean;
		public var EnableMatinee:Boolean;
		public var CoverTransparent:Boolean;
		public var RolePhys:Boolean;
		public var EnvDOF:Boolean;
		public var HDR:Boolean;
		public var MotionBlur:Boolean;
		public var Stroke:Boolean;
		
		public var advancedOptionData:Array;
		
		public var sound_enable:Boolean;
		public var SoundAll:Boolean;
		public var SoundBack:Boolean;
		public var SoundEnv:Boolean;//removed
		public var SoundVoice:Boolean;
		public var SoundSfx:Boolean;
		public var SoundAllVL:int;
		public var SoundBackVL:int;
		public var SoundEnvVL:int;
		public var SoundVoiceVL:int;
		public var SoundSfxVL:int;
		
		public var game1_enable:Boolean;
		public var HideName_my:Boolean;
		public var HideName_hero:Boolean;
		public var HideNameOther_my:Boolean;
		public var HideNameOther_hero:Boolean;
		public var HideNameFamily_my:Boolean;
		public var HideNameFamily_other:Boolean;
		public var HideNameMonster:Boolean;
		public var HideNameDrop:Boolean;
		public var DrawBlood_my:Boolean;
		public var DrawBlood_monster:Boolean;
		public var HideHurtNumber_my:Boolean;
		public var HideHurtNumber_other:Boolean;
		public var HideSkillEffect_my:Boolean;
		public var HideSkillEffect_other:Boolean;
		public var DrawGuide:Boolean;
		public var DrawChatBubble:Boolean;
		public var DrawAITip:Boolean;
		public var DrawWeather:Boolean;
		public var DrawBloodNumber:Boolean;
		public var DrawHurt:Boolean;
		public var DrawGameFrame:Boolean;
		public var HintFriendOnline:Boolean;
		public var HintHidePlayer:Boolean;
		public var HintMarkSelf:Boolean;
		
		public var game2_enable:Boolean;
		public var DeclineStrangeChat:Boolean;
		public var DeclineInviteTeam:Boolean;
		public var DeclineInviteFamily:Boolean;
		public var DeclineInviteDisciple:Boolean;
		public var DeclineInviteMaster:Boolean;
		
		public var input1_enable:Boolean;
		public var SlotKeyList:Array;
		
		public var input2_enable:Boolean;
		public var KeyList:Array;

		public function OptionData()
		{
			video_enable = false;
			sound_enable = false;
			game1_enable = false;
			game2_enable = false;
			input1_enable = false;
			input2_enable = false;
			WndSizeFixed = false;
			SlotKeyList=new Array();
			KeyList = new Array();
		}
	}
}