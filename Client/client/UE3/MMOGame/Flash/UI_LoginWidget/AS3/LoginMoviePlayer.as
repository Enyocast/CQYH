package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	import ActionScript3.fla.MoviePlayerBase;
	
	import UI_LoginWidget.AS3.CreateModule;
	import UI_LoginWidget.AS3.LoginModule;
	import UI_LoginWidget.AS3.SelectRoleModule;	

	public class LoginMoviePlayer extends MoviePlayerBase {
		
		public var User:LoginModule;
		public var Select:SelectRoleModule;
		public var Create:CreateModule;
		public var Revert:FindPanel;

		public var Loginstatus:int;//登录状态控制 0播放logo登录2创建角色3选择角色

		override protected function configUI():void
		{
			super.configUI();
			//Jump2List();		
			//Jump2Login();
			//Jump2ListOut();
			//Jump2Create();
			Revert.visible = false;
		}
		
		public function ResetFocus():void
		{
			if(Loginstatus==1)
			{
				User.ResetFocus();
			}
			else if(Loginstatus==2)
			{
				Create.ResetFocus();
			}
		}
		
		public function Jump2Login():void
		{ 
			Loginstatus=1;
			User.visible = true;
			Select.visible = false;
			Create.visible = false;
			User.PlayLogo();
		}
		
		public function Jump2List():void
		{ 
			Loginstatus=3;		
			User.visible = false;
			Select.visible = true;
			Create.visible = false;
			Select.Effectshow();
		}

		public function Jump2ListOut():void
		{ 
			Loginstatus=4;
			User.visible = false;
			Select.visible = true;
			Create.visible = false;
			Select.Effecthide();
		}

		public function Jump2Create():void
		{ 
		    Loginstatus=2;
			User.visible = false;
			Select.visible = false;
			Create.visible = true;
			Create.Effectshow();
		}
	}
	
}
