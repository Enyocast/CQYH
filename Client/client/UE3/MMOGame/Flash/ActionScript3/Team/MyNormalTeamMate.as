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
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Mail.MailData;
	
	
	
	public class MyNormalTeamMate extends MyPanel
	{
		public var maskHPWidth:int = 144;
		
		override protected  function configUI():void {

			super.configUI();
			var i:int;
			for( i = 0 ; i < 4 ; i ++)
			{
				//var Teammate:MovieClip = this.getChildByName( "teamMate"+i ) as MovieClip;
				//var TeammateHeadIcon:Button = Teammate.getChildByName( "playerHeadIcon" ) as Button;
				var Teammate:Button = this.getChildByName( "teamMate"+i ) as Button;
				//Teammate.mouseChildren = true;
				if( Teammate )
				{
					//var playerIcon:IconLoader = TeammateHeadIcon.getChildByName( "RoleIcon" ) as IconLoader;
					//playerIcon.source = "img://0.TGA";
					Teammate.addEventListener( MouseEvent.CLICK , MouseRightClick );
					Teammate.addEventListener( MouseEvent.MOUSE_OVER , onMouseOverTeammate  );
					Teammate.addEventListener( MouseEvent.MOUSE_OUT , onMouseOutTeammate );
					
					Teammate.itemid = i;
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

			for(var i:int =0; i< data.length; i++)
			{
				var obj:MyTeamMateData = data[i];
				var TeamMate:Button = this.getChildByName( "teamMate"+i) as Button;
				if( TeamMate )
				{
					var txtName:TextField = TeamMate.getChildByName("tf_name") as TextField ;
					if(txtName)
						txtName.text = obj.Name;
					
					//职业
					var chapter:MovieClip = TeamMate.getChildByName("chapter") as MovieClip ;
					if(chapter)
					{
						var classID:String = "_" + obj.ClassId;
						chapter.gotoAndStop(classID);
					}
					
					var deadTag:MovieClip = TeamMate.getChildByName("deadTag") as MovieClip;
					if(deadTag)
						deadTag.visible = obj.HP <= 0;
						
					var maskHp:MovieClip = TeamMate.getChildByName("maskHp") as MovieClip;
					if(maskHp)
						maskHp.width = obj.HPPecent * maskHPWidth;
					
					var offLineTag:MovieClip = TeamMate.getChildByName("OfflineTag") as MovieClip;
					if(offLineTag)
						offLineTag.visible = !obj.OnLine;
						
					//在线
					if(obj.OnLine)
					{
						//HP
						if(obj.HP <= 0)
						{
							txtName.textColor =  0x62605C ;
						}
						else
						{
							txtName.textColor =  0xFFF5DE ;
						}
					}
					else
					{
						txtName.textColor = 0xFFF5DE;
						maskHp.width = 0.001 * maskHPWidth;
					}
					
					//队长
					var leader:MovieClip = TeamMate.getChildByName("tag_teamleader") as MovieClip;
					if(leader)
						leader.visible = obj.IsLeader;
					
					//头像
					var res:String = "img://MMOUIFaceIcon.Player.class";
					var headIcon:Button = TeamMate.getChildByName("playerHeadIcon") as Button;
					if(headIcon)
					{
						res += String(obj.ClassId);
						
						var playerIcon:UILoader = headIcon.getChildByName("RoleIcon") as UILoader;
						if(playerIcon)
						{
							if(obj.Sex == 1)
							{
								res += "man";
							}
							else
							{
								res += "fe";
							}
							if(!obj.OnLine || obj.HP <= 0)
							{
								res += "_g";
							}
						}
						
						var originPath:String = playerIcon.source;
						if(res != originPath)
							playerIcon.source = res;
						
					}
					
				}
				
			}
		}
		
		
		
		
	}
}