package UI_LoginWidget.AS3
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Events.ParamEvent;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.data.DataProvider;
	import ActionScript3.GameDispathcher;

	public class LoginModule extends MyPanel
	{
		public var loginBottomBar:MovieClip;
		//public var logo_mc:MovieClip;
		public var btn_mc:MovieClip;
		//public var loginbg:MovieClip;
		public var LoginField_mc:LoginTextField;

		//public var IsFirstOpenGame:Boolean = false;
		public var KeyBoard:Button;
		public var startLogo:MovieClip;
		public var notice:MovieClip;
		override protected function configUI():void
		{
			super.configUI();
			//ExternalInterface.call("ASRegisterLoginModule", this);
			startLogo.addEventListener("LogoMovieEnd",logoMovieEndHandler);
			startLogo.gotoAndStop(1);
			//ExternalInterface.call("SetFirstOpenGame",this,"IsFirstOpenGame" );//可以删除的
			btn_mc.btn_Settings.addEventListener(MouseEvent.CLICK,clickSetting );
			btn_mc.btn_Quit.addEventListener(MouseEvent.CLICK,clickQuit );
			btn_mc.btn_mainpage.addEventListener(MouseEvent.CLICK,clickMain);
			btn_mc.btn_pwd.addEventListener(MouseEvent.CLICK,clickEditPwd);
			btn_mc.btn_Recharge.addEventListener(MouseEvent.CLICK,clickRecharge);
			btn_mc.btn_PlayBik.addEventListener(MouseEvent.CLICK,clickPlayBik);
			GameDispathcher.getInstance().addEventListener(ParamEvent.STAGECHANGE,stageChangeHandler);
			stageChangeHandler(null);
			//ShowLoginInputBoxes(false);
			//updateNotice("亲爱的玩家，您好： ");
		}
		
		public function logoMovieEndHandler(evt:Event):void
		{
			startLogo.visible=false;
			ExternalInterface.call("ASLogoEnd");
		}
		
		public function PlayLogo():void
		{
			startLogo.gotoAndPlay(1);
		}
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			loginBottomBar.y = cavasHeight - loginBottomBar.height;
			loginBottomBar._version.x = cavasWidth - loginBottomBar._version.width;
			loginBottomBar.loginbg.width=cavasWidth;
			LoginField_mc.y = ((cavasHeight - LoginField_mc.height) >> 1 )  + 95;
			LoginField_mc.x = (cavasWidth - LoginField_mc.width) >> 1;
			startLogo.x=(cavasWidth - startLogo.width) >> 1;
			startLogo.y=(cavasHeight - startLogo.height)>>1;
			btn_mc.x = cavasWidth - 181;
			btn_mc.y = cavasHeight - 253;
			
			//loginbg.width=stageW;
			//loginbg.height=stageH;
		}
		public function UCupdateNotice(str:String):void
		{
			notice.textField.htmlText=str;
		}
		public function  SetStartLogo( Logo:MovieClip )
		{
			startLogo = Logo;
		}
		
		public function Effectshow():void
		{
			//logo_mc.gotoAndPlay('show');
			//ResetFocus();
		}
		
		public function Effecthide():void
		{
			//logo_mc.gotoAndPlay('hide');
		}
		
		public function ShowLoginInputBoxes(v:Boolean):void
		{
			this.LoginField_mc.visible = v;
			ResetFocus();
			ExternalInterface.call("ASTrace", "Show Input:" + v.toString());
		}
		
		public function ShowLoginSetup(v:Boolean):void
		{
			this.btn_mc.visible = v;
		}				
		
		public function ResetFocus():void
		{
			//trace("===== LoginPanel::ResetFocus");
			LoginField_mc.ResetFocus();
			//changeFocus();
		}
	  	
		public function UpdateUser(user:String):void
	   	{
			LoginField_mc.UpdateUser(user);
		}
		
		public function SplitData( ServerName:String ):void
		{
			LoginField_mc.updateServer(ServerName);
		}
		
		private function clickPlayBik(e:MouseEvent):void
		{
			ExternalInterface.call("ASPlayCGBik");
		}
		private function clickRecharge(e:MouseEvent):void
		{//充值
			ExternalInterface.call("ASGameRecharge");
		}

		private function clickSetting(e:MouseEvent):void
		{
			ExternalInterface.call("ASOpenSystemSetting");
		}

		private function clickQuit(e:MouseEvent):void
		{
			ExternalInterface.call("ASQuitGame");
		}

		private function clickMain(e:MouseEvent):void
		{//注册账号
			ExternalInterface.call("ASLoginMainHome");
		}

		private function clickEditPwd(e:MouseEvent):void
		{//修改密码
			ExternalInterface.call("ASLoginEditPwd");
		}

	}

}