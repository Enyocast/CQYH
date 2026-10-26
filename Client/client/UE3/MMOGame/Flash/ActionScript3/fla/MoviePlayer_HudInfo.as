package ActionScript3.fla
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Label;

	import ActionScript3.Widget.TeamPanel;


	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	//import flash.utils.tim
	import ActionScript3.DropIcon;

	import flash.utils.getDefinitionByName;
	import ActionScript3.MyActivePanel;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Widget.MyDamageLevel;
	import scaleform.clik.controls.Button;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	import ActionScript3.Widget.HeroFrameWidget;

	import ActionScript3.fla.MoviePlayerBase;
	import ActionScript3.MyPanel;
	import ActionScript3.Widget.PlayerFrame;
	import ActionScript3.Widget.TargetInfo;
	import ActionScript3.Widget.BuffPanel;

	public class MoviePlayer_HudInfo extends MoviePlayerBase
	{
		public var TeamMate_mc:MyPanel;
		public var HeroInfo_mc:MyPanel;
		public var DeathFx_mc:MovieClip;
		private var bDeathFx:Boolean = false;
		public var PlayerInfo_mc:PlayerFrame;
		public var PlayerBuffPanel_mc:BuffPanel;
		public var EnemyInfo_mc:TargetInfo;

		override function initStage()
		{
			if (TeamMate_mc)
			{
				ExternalInterface.call( "RegisterTeamMate" , TeamMate_mc );
			}
			//{
			//if (PlayerInfo_mc);
			//{;
			//ExternalInterface.call( "RegisterPlayerInfo",PlayerInfo_mc);
			//}
			if(DeathFx_mc)
			{
				DeathFx_mc.gotoAndPlay("off");
				DeathFx_mc.visible=false;
				DeathFx_mc.enabled=false;
				DeathFx_mc.mouseEnabled=false;
				DeathFx_mc.mouseChildren = false;
			}

			super.initStage();
		}

		public function SetHp(curHp:Number, maxHp:Number)
		{
			ExternalInterface.call( "ASTrace" , "+++++++++++++++++public function SetHp(curHp:Number, maxHp:Number)" );
			if(DeathFx_mc)
			{
				var bNewDeathFx:Boolean = false;
				if(curHp*10<=maxHp && curHp>0 )
				{
					bNewDeathFx = true;
				}
				
				if(bNewDeathFx!=bDeathFx){
					bDeathFx = bNewDeathFx;
					if(bDeathFx){
						DeathFx_mc.gotoAndPlay("on");
						DeathFx_mc.visible = true;
						ExternalInterface.call( "ASTrace" , "+++++++++++++++++public function SetHp(curHp:Number, maxHp:Number)2222" );
					}
					else
					{
						DeathFx_mc.gotoAndPlay("off");
					}
				}
			}
		}
	}
}