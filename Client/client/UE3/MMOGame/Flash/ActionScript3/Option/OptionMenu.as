package ActionScript3.Option
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	
	import ActionScript3.MyPanel;
	
	import scaleform.clik.controls.Button;
	import UI_Minimap.MinimapAS3.SceneLinesDropDownListData;
	import flash.events.MouseEvent;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import scaleform.clik.core.UIComponent;
	
	public class OptionMenu extends MyPanel
	{
		public var system_config:Button;
		public var return_select:Button;
		public var return_login:Button;
		public var exit_game:Button;
		public var exit_duplicate:Button;
		public var return_game:Button;
		public var assist:Button;
		public var menubg:MovieClip;
		public var lineMenu:LineMenu;
		public var _bg:MovieClip;
		override protected  function configUI():void
		{
			super.configUI();
			//ExternalInterface.call( "ASRegisterOptionMenu", this);
            if(menubg){
				system_config=menubg.system_config;
				return_select=menubg.return_select;
				return_login=menubg.return_login;
				exit_game=menubg.exit_game;
				exit_duplicate=menubg.exit_duplicate;
				return_game=menubg.return_game;
				assist=menubg.assist;
			}
			system_config.addEventListener("click",OnOptionConfig);
			return_select.addEventListener("click",OnReturnSelRole);
			return_login.addEventListener("click",OnReturnLogin);
			exit_game.addEventListener("click",OnLeaveGame);
			exit_duplicate.addEventListener("click",OnExitDuplicateMap);
			return_game.addEventListener("click",OnReturnGame);
			assist.addEventListener(MouseEvent.CLICK,onClickAssist);
			//UCShowExitDuplicateButton(true,"测试");
			lineMenu.visible=false;
			stageChangeHandler(null);
/*			var linesDatas:Array = new Array();
			for (var j:int = 1; j <3; j++)
			{
				var singleLineData:SceneLinesDropDownListData = new SceneLinesDropDownListData ;
				singleLineData.lineID = j*10;
				singleLineData.label = singleLineData.lineID + "线";
				linesDatas.push(singleLineData);
			}
			UCUpdateLine("矿洞一区",linesDatas);*/
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth=GameDispathcher.getInstance().StageWidth;
			this.cavasHeight=GameDispathcher.getInstance().StageHeight;
			menubg.x=cavasWidth-menubg.width>>1;
			menubg.y=cavasHeight-menubg.height>>1;
			lineMenu.x=menubg.x+menubg.width;
			lineMenu.y=menubg.y+59;
			
		}
		
		public function UCUpdateLine(mapName:String,dat:Array):void
		{
			lineMenu.visible=true;
			lineMenu.updateLine(mapName,dat);
		}

		private function OnOptionConfig(evt:MouseEvent):void
		{
			ExternalInterface.call("ASOptionConfig");
			//ExternalInterface.call("ASOnPanelClose", PanelName);
			//visible = false;
			//parent.getChildByName("_opConfig").visible = true;
		}
		private function OnReturnSelRole(evt:MouseEvent):void
		{
			ExternalInterface.call("ASReturnSelect");
		}
		private function OnReturnLogin(evt:MouseEvent):void
		{
			ExternalInterface.call("ASReturnLogin");
		}
		private function OnLeaveGame(evt:MouseEvent):void
		{
			ExternalInterface.call("ASReqExitGame");
		}
		private function OnExitDuplicateMap(evt:MouseEvent):void
		{
			ExternalInterface.call("ASExitDuplicate");
		}
		private function OnReturnGame(evt:MouseEvent):void
		{
			ExternalInterface.call("ASOnPanelClose", PanelName);
		}
		
		private function onClickAssist(evt:MouseEvent):void
		{
			ExternalInterface.call("ASOpenAssist");
		}
		public function UCShowExitDuplicateButton( isShow:Boolean, btnStr:String ):void
		{
			exit_duplicate.label = btnStr;
			exit_duplicate.visible = isShow;
			lineMenu.visible=false;
			updateUI(isShow);
		}
		
		private function updateUI(isShow:Boolean):void
		{
			if(isShow==true){
				menubg.bg_1.visible=true;
				menubg.bg_2.y=219;
				return_login.y=return_select.y+37;
				exit_game.y=return_login.y+37;
				exit_duplicate.y=exit_game.y+37;
				return_game.y=310;
			}else{
				menubg.bg_1.visible=false;
				menubg.bg_2.y=182;
				return_login.y=return_select.y+37;
				exit_game.y=return_login.y+37;
				return_game.y=310-37;
			}
		}
	}
}