package ActionScript3.fla
{
	import flash.external.ExternalInterface;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyPanel;	
	import ActionScript3.fla.MoviePlayerBase;
	import flash.display.MovieClip;
	import ActionScript3.Widget.MyMessageboxZone;
	import ActionScript3.Msgbox.InputMsgbox;

	public class MoviePlayer_MessageBox extends MoviePlayerBase
	{		
		public var UnlockMsgBoxZone_mc:MyMessageboxZone;
		
		override protected  function configUI():void
		{
			//UnlockMsgBoxZone_mc.AddMsgbox( "" );
			super.configUI();
			
			
			
			
			//UnlockMsgBoxZone_mc.AddMsgbox("1");
			
			//trace( UnlockMsgBoxZone_mc.GetFirstChild() );
		}
	}
}