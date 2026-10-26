package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.CheckBox;
	import flash.events.MouseEvent;
	import scaleform.clik.core.UIComponent;
	
	
	public class ConfigGame2 extends UIComponent {

		public var btn_default:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_apply:Button;
		public var decline_strange_chat:CheckBox;
		public var decline_invite_team:CheckBox;
		public var decline_invite_family:CheckBox;
		public var decline_invite_disciple:CheckBox;
		public var decline_invite_master:CheckBox;
		public var decline_ShowEnemy:CheckBox;
		public var chk_shift:CheckBox;
		
		override protected function configUI():void
		{
			super.configUI();
			
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			
			decline_invite_disciple.enabled = true;
			decline_invite_master.enabled = true;

			DefaultValue();
		}
		public function DefaultValue()
		{
			decline_strange_chat.selected = false;
			decline_invite_team.selected = false;
			decline_invite_family.selected = false;
			decline_invite_disciple.selected = false;
			decline_invite_master.selected = false;
			decline_ShowEnemy.selected =false;
			chk_shift.selected=false;
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
			
			dat.game2_enable = true;
			
			dat.DeclineStrangeChat = decline_strange_chat.selected;
			dat.DeclineInviteTeam = decline_invite_team.selected;
			dat.DeclineInviteFamily = decline_invite_family.selected;
			dat.DeclineInviteDisciple = decline_invite_disciple.selected;
			dat.DeclineInviteMaster = decline_invite_master.selected;
			dat.DefaultShift=chk_shift.selected;
			dat.DeclineShowEnemy=decline_ShowEnemy.selected;
			
			ExternalInterface.call("ASApplyGameConfig", dat);
		}
		public function setConfigData(dat:ConfigGameData):void
		{
			if (!dat.game2_enable)
				return;
			decline_strange_chat.selected = dat.DeclineStrangeChat;
			decline_invite_team.selected = dat.DeclineInviteTeam;
			decline_invite_family.selected = dat.DeclineInviteFamily;
			decline_invite_disciple.selected = dat.DeclineInviteDisciple;
			decline_invite_master.selected = dat.DeclineInviteMaster;
			chk_shift.selected=dat.DefaultShift;
			decline_ShowEnemy.selected=dat.DeclineShowEnemy;
		}
	}
	
}
