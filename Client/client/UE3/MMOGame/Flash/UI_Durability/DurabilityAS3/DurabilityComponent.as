package UI_Durability.DurabilityAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	
	public class DurabilityComponent extends UIComponent 
	{
		private var _ComponentState:int;
		
		/*
		override protected function configUI():void 
		{
			super.configUI();

		}
		*/
		//==========================================================================================
		public function get ComponentState():int
		{
			return _ComponentState;
		}
		public function set ComponentState( curState:int):void
		{
			_ComponentState = curState;
			switch( _ComponentState )
			{
				case 1:
				gotoAndStop( "yellow" );
				break;
				case 2:
				gotoAndStop( "red" );
				break;
				default:
				gotoAndStop( "gray" );
				break;
			}
		}
		//==========================================================================================
		public function RePlayCurAnimi():void
		{
			var animObj:MovieClip = getChildByName( "animMc" ) as MovieClip;
			if( animObj == null ){
				return;
			}
			animObj.gotoAndPlay( 1 );
		}
	}
}

