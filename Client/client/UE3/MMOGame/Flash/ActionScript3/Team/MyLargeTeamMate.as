package ActionScript3.Team{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	public class MyLargeTeamMate extends MyPanel
	{
		override protected  function configUI():void {

			super.configUI();
			
			var i:int;
			for( i = 0 ; i < 10 ; i ++)
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
				if( e.target is Button )
				{
					ExternalInterface.call( "ASTeamMemberRightClick", root.mouseX , root.mouseY , (e.target as Button).itemid );
				}
			}
			else if((e as MouseEventEx).buttonIdx == 0)
			{
				if( e.target is Button )
				{
					ExternalInterface.call( "ASTeamMemberLeftClick", root.mouseX , root.mouseY , (e.target as Button).itemid );
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
		
		public function UCUpdateTeamMenber(data:Array):void
		{
			var length:int = data.length;
			
			for(var i:int =0; i< data.length; i++)
			{
				var obj:MyTeamMateData = data[i];
				var TeamMate:Button = this.getChildByName( "teamMate"+i) as Button;
				if( TeamMate )
				{
					var txtName:TextField = TeamMate.getChildByName("tf_name") as TextField ;
					if(txtName)
						txtName.text = obj.Name;
					
					//在线
					if(obj.OnLine)
					{
						TeamMate.gotoAndStop("normal");
						
						//HP
						if(obj.HP <= 0)
						{
							TeamMate.gotoAndStop("3");
							txtName.textColor =  0x62605C ;
						}
						else
						{
							TeamMate.gotoAndStop("1");
							txtName.textColor =  0xFFF5DE ;
						}
						
						//血量条
						var fill_mc:MovieClip = TeamMate.getChildByName("fill_mc") as MovieClip;
						if(fill_mc)
							fill_mc.width = obj.HPPecent*110;
						
					}
					else
					{
						TeamMate.gotoAndStop("2");
						txtName.textColor = 0x62605C;
					}
					
					//队长
					var leader:MovieClip = TeamMate.getChildByName("tag_teamleader") as MovieClip;
					if(leader)
						leader.visible = obj.IsLeader;
					
				}
				
			}
		}
	}
}