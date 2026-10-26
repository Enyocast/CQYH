package ActionScript3.Widget{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	
	public class MyLargeTeamMate extends MyPanel
	{
		override protected  function configUI():void {

			super.configUI();
			
			var i:int;
			for( i = 0 ; i < 20 ; i ++)
			{
				var TeamMate:Button = this.getChildByName( "teamMate"+i) as Button;
				if( TeamMate )
				{
					TeamMate.addEventListener( MouseEvent.CLICK , MouseRightClick );
					TeamMate.addEventListener( MouseEvent.MOUSE_OVER , onMouseOverTeammate  );
					TeamMate.addEventListener( MouseEvent.MOUSE_OUT , onMouseOutTeammate );
					TeamMate.itemid = i;
				}
				
			}
			
			this.MaskUI = false;
		}
		
		function MouseRightClick( e:Event )
		{
			if( (e as MouseEventEx).buttonIdx == 1) 
			{
				//trace(e.target);
				if( e.target is Button )
				{
					ExternalInterface.call( "ASTeamMemberRightClick",root.mouseX , root.mouseY , (e.target as Button).itemid );
				}
				//( int x , int y , int index )
				
				
			}
		}
		//
		function onMouseOverTeammate( evt:Event )
		{
			ExternalInterface.call( "ASShowTeammateHint", evt.target, (evt.target as Button).itemid );
		}
		//
		function onMouseOutTeammate( evt:Event )
		{
			ExternalInterface.call( "ASHideTeammateHint" );
		}
	}
}