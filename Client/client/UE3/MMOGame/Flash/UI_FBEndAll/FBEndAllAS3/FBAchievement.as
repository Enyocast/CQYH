package UI_FBEndAll.FBEndAllAS3
{
	import flash.text.TextField;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	public class FBAchievement extends UIComponent
	{
		public var contentTf:TextField;
		public var typeIconMc:MovieClip;
		public var bgMc:MovieClip;
		
		public var tipsHtml:String;
		
		override protected function configUI():void
		{
			super.configUI();
			
			addEventListener( MouseEvent.MOUSE_OVER, MouseRollOverFBAchievement );
			addEventListener( MouseEvent.MOUSE_OUT, MouseRollOutFBAchievement );
		}
		//
		public function SetContentValue( achievementName:String, achievementDesc:String, achivType:int ):void
		{
			if( achivType > 0 ){
				contentTf.textColor = 0xFFE0A6;
				bgMc.gotoAndStop( 1 );
			}
			else{
				contentTf.textColor = 0x505152;
				bgMc.gotoAndStop( 0 );
			}
			
			contentTf.text = achievementName;
			tipsHtml = achievementDesc;
			typeIconMc.gotoAndStop( 10*achivType + 1 );
		}
		//--------------------------------------------------------------------------------------------
		public function MouseRollOverFBAchievement( e:Event )
		{
			ExternalInterface.call("ASShowTips_PlainText", this );
		}
		//--------------------------------------------------------------------------------------------
		public function MouseRollOutFBAchievement( e:Event )
		{
			ExternalInterface.call("ASHideTips_PlainText", this );
		}
	}
}