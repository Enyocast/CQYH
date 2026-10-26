package UI_Hang.AS3 {
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.CheckBox;
	
	public class ConfigGame1 extends UIComponent {

        public var btn_default:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_apply:Button;
		public var hide_name_my:CheckBox;
		public var hide_name_hero:CheckBox;
		public var hide_name_other_my:CheckBox;
		public var hide_name_other_hero:CheckBox;
		public var hint_mark_self:CheckBox;
		
		public var hide_name_family_my:CheckBox;
		public var hide_name_family_other:CheckBox;
		public var hide_name_monster:CheckBox;
		public var hide_name_drop:CheckBox;
		
		public var draw_blood_my:CheckBox;
		public var draw_blood_other:CheckBox;
		public var draw_blood_monster:CheckBox;
		public var hide_hurt_number_my:CheckBox;
		public var hide_hurt_number_other:CheckBox;
		public var hide_skill_effect_my:CheckBox;
		public var hide_skill_effect_other:CheckBox;
		
		public var draw_guide:CheckBox;
		public var draw_chat_bubble:CheckBox;
		public var draw_blood_number:CheckBox;
		public var draw_hurt:CheckBox;
		public var draw_game_frame:CheckBox;
		public var hint_friend_online:CheckBox;
		public var hint_hide_Player:CheckBox;
		public var hide_CameraShake:CheckBox;
		
	    override protected function configUI():void
		{
			super.configUI();
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			
			DefaultValue();
		}
		
		public function DefaultValue():void
		{
			hide_name_my.selected = true;//false;
			hide_name_hero.selected = true;//true;
			hide_name_other_my.selected = true;//false;
			hide_name_other_hero.selected = true;//true;
			
			hide_name_family_my.selected = true;//false;
			hide_name_family_other.selected = true;//false;
			hide_name_monster.selected = true;//false;
			hide_name_drop.selected = true;//false;
			hint_mark_self.selected = true;
			hide_CameraShake.selected=true;
			
			draw_blood_my.selected = true;
			draw_blood_other.selected=true;
			draw_blood_monster.selected = true;
			hide_hurt_number_my.selected = true;//false;
			//hide_hurt_number_other.selected = true;//false;
			hide_skill_effect_my.selected = true;//false;
			hide_skill_effect_other.selected = true;//false;
			draw_guide.selected = true;
			draw_chat_bubble.selected = true;
			draw_blood_number.selected = true;
			draw_hurt.selected = false;
			draw_game_frame.selected = true;
			hint_friend_online.selected = true;
			hint_hide_Player.selected = true;
		}
		public function OnDefault(evt:MouseEvent):void
		{
			DefaultValue();
		}
		public function OnOK(evt:MouseEvent):void
		{
			OnApply(null);
			OnCancel(null);	
		}
		public function OnCancel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASOnPanelClose" , "Assist");
		}
		public function OnApply(evt:MouseEvent):void
		{
			var dat:ConfigGameData = new ConfigGameData();
			
			dat.game1_enable = true;
			
			dat.HideName_my = !hide_name_my.selected;
			dat.HideName_hero = !hide_name_hero.selected;
			dat.HideNameOther_my = !hide_name_other_my.selected;
			dat.HideNameOther_hero = !hide_name_other_hero.selected;
			
			dat.HideNameFamily_my = !hide_name_family_my.selected;
			dat.HideNameFamily_other = !hide_name_family_other.selected;
			dat.HideNameMonster = !hide_name_monster.selected;
			dat.HideNameDrop = !hide_name_drop.selected;
			dat.HintMarkSelf = hint_mark_self.selected;
			
			dat.DrawBlood_my = draw_blood_my.selected;
			dat.DrawBlood_other=draw_blood_other.selected;
			dat.DrawBlood_monster = draw_blood_monster.selected;
			dat.HideHurtNumber_my = !hide_hurt_number_my.selected;
			//dat.HideHurtNumber_other = !hide_hurt_number_other.selected;
			dat.HideSkillEffect_my = !hide_skill_effect_my.selected;
			dat.HideSkillEffect_other = !hide_skill_effect_other.selected;
			dat.HideSkillEffect_CameraShake = !hide_CameraShake.selected;
			
			dat.DrawGuide = draw_guide.selected;
			dat.DrawChatBubble = draw_chat_bubble.selected;
			dat.DrawBloodNumber = draw_blood_number.selected;
			dat.DrawHurt = draw_hurt.selected;
			dat.DrawGameFrame = draw_game_frame.selected;
			dat.HintFriendOnline = hint_friend_online.selected;
			dat.HintHidePlayer  = hint_hide_Player.selected;
			
			ExternalInterface.call("ASApplyGameConfig", dat);
		}
		
		public function setConfigData(dat:ConfigGameData):void
		{
			if (!dat.game1_enable)
				return;
			hide_name_my.selected = !dat.HideName_my;
			hide_name_hero.selected = !dat.HideName_hero;
			hide_name_other_my.selected = !dat.HideNameOther_my;
			hide_name_other_hero.selected = !dat.HideNameOther_hero;
			
			hide_name_family_my.selected = !dat.HideNameFamily_my;
			hide_name_family_other.selected = !dat.HideNameFamily_other;
			hide_name_monster.selected = !dat.HideNameMonster;
			hide_name_drop.selected = !dat.HideNameDrop;
			hint_mark_self.selected = dat.HintMarkSelf;
			
			draw_blood_my.selected = dat.DrawBlood_my;
			draw_blood_other.selected=dat.DrawBlood_other;
			draw_blood_monster.selected = dat.DrawBlood_monster;
			hide_hurt_number_my.selected = !dat.HideHurtNumber_my;
			hide_skill_effect_my.selected = !dat.HideSkillEffect_my;
			hide_skill_effect_other.selected = !dat.HideSkillEffect_other;
			hide_CameraShake.selected = !dat.HideSkillEffect_CameraShake;
			
			draw_guide.selected = dat.DrawGuide;
			draw_chat_bubble.selected = dat.DrawChatBubble;
			draw_blood_number.selected = dat.DrawBloodNumber;
			draw_hurt.selected = dat.DrawHurt;
			draw_game_frame.selected = dat.DrawGameFrame;
			hint_friend_online.selected = dat.HintFriendOnline;
			hint_hide_Player.selected = dat.HintHidePlayer;
		}

	}
	
}
