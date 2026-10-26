
package ActionScript3 {

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;

	//import flash.external.ExternalInterface;
	//import flash.utils.Timer;
	//import flash.events.TimerEvent;
	
	public class NumUi extends UIComponent
	{
		public var Cnt:int = 1;
		public var SingleWidth:int = 20;
		public var AlignLeft:Boolean;
		//
		public function Init( cnt:int, singleWidth:int, alignLeft:Boolean )
		{
			//trace("------NumUi  Init:", cnt);
			if( cnt < 1 ){
				return;
			}
			
			Cnt = cnt;
			SingleWidth = singleWidth;
			AlignLeft = alignLeft;
		}
		//
		public function SetNumber( num:int )
		{
			var i:int = 0;
			var maskNum:int = 1;
			var lastIdx:int = Cnt - 1;
			for( i = lastIdx; i > 0; --i )
			{
				maskNum *= 10;
			}
			
			var notZero:Boolean = false;
			var idx = 0;
			var singleNum:int;
			var num_mc:MovieClip;
			
			
			for( i = 0; i < Cnt; ++i )
			{
				num_mc = getChildByName( "num_mc" + i ) as MovieClip;
				
				singleNum = num / maskNum;
				notZero = ( notZero || ( singleNum > 0 ? true : false ) );
				idx = notZero ? idx : i;

				num_mc.visible = ( notZero || ( i == lastIdx ) );
				if( AlignLeft ){
					num_mc.x = SingleWidth * ( i - idx );
				}
				
				trace( "Score", notZero, i - idx, num_mc.x );
				
				num_mc.gotoAndStop( singleNum > 0 ? singleNum : 10 );
				
				num = ( num - singleNum * maskNum );
				maskNum = maskNum / 10;
			}
		}
		//
	}
}