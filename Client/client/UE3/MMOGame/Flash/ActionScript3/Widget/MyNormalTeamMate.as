package ActionScript3.Widget{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	
	public class MyNormalTeamMate extends MyPanel
	{
		override protected  function configUI():void {

			super.configUI();
			var i:int;
			for( i = 0 ; i < 4 ; i ++)
			{
				var Teammate:MovieClip = this.getChildByName( "teamMate"+i ) as MovieClip;
				var TeammateHeadIcon:Button = Teammate.getChildByName( "playerHeadIcon" ) as Button;
				Teammate.mouseChildren = true;
				if( TeammateHeadIcon )
				{
					//var playerIcon:IconLoader = TeammateHeadIcon.getChildByName( "RoleIcon" ) as IconLoader;
					//playerIcon.source = "img://0.TGA";
					TeammateHeadIcon.addEventListener( MouseEvent.CLICK , MouseRightClick );
					TeammateHeadIcon.addEventListener( MouseEvent.MOUSE_OVER , onMouseOverTeammate  );
					TeammateHeadIcon.addEventListener( MouseEvent.MOUSE_OUT , onMouseOutTeammate );
					
					TeammateHeadIcon.itemid = i;
				}
			}
			
			this.MaskUI = false;
		}
		
		function MouseRightClick( e:Event )
		{
			if( (e as MouseEventEx).buttonIdx == 1) 
			{
				if( e.target is Button )
				{
					ExternalInterface.call( "ASTeamMemberRightClick", root.mouseX , root.mouseY , (e.target as Button).itemid );
				}

				
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