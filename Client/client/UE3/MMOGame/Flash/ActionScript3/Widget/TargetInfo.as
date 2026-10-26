package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import flash.geom.Point;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import ActionScript3.Widget.BuffComponent;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	
	public class TargetInfo extends MyPanel
	{
		var delaytime:Number ;
		var StartPos:Number = 0;
		var bStartTail:Boolean ;
		
		public var HPBarTail_mc:MovieClip;
		public var NPCHP_Text:TextField;
		public var HPBar_mc:MovieClip;
		public var AvatarButton_mc:Button;
		public var enemyname_mc:TextField;
		public var BuffComponent_mc:BuffComponent2;
		
		//var oriHPMask
		
		override protected function configUI():void 
		{
			super.configUI();
			this.visible=false;
			AvatarButton_mc.addEventListener( MouseEvent.CLICK , ClickAvtarButton );
			stageChangeHandler(null);
			//ShowBuff(1, "MMO_UIIcon.Formal_SkillIcon.Mage_MagicArmor" , 10000, 1000, 3);
			//HPTail(0.282599,false,20,200,true);
			//SetTargetInfo( {lvText:"52",frameText:"npc" ,targetName:"dash" ,typeText:"type" , avatarIconSource:"img://magic_girl.png" , textColor:235 } );
		}
		
		function ClickAvtarButton( e:Event )
		{
			if( (e as MouseEventEx).buttonIdx == 1)
			{
				var pos:Point = new Point;
					
				pos.x = root.mouseX;
					
				pos.y = root.mouseY ;
				
				enemyname_mc = getChildByName("enemyname_mc") as TextField;
				ExternalInterface.call( "ASRightClickTargetInfo2" , pos.x , pos.y , enemyname_mc.text);
				
			}
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=((cavasWidth-240)>>1)+119;
		}
		public function SetAlpha( inAlpha:Number ):void
		{
			alpha = inAlpha;	
		}
		
		public function SetTargetInfo( data:Object )
		{
			var enemyname_mc:TextField = this.getChildByName( "enemyname_mc" ) as TextField;
			if( enemyname_mc )
			{
				enemyname_mc.autoSize=TextFieldAutoSize.LEFT;
				enemyname_mc.text = data.targetName;
/*				if(data.lvText==0){
				    enemyname_mc.text = data.targetName;
				}else{
					enemyname_mc.text = data.targetName+"("+data.lvText+"级)";
				}*/
				if( data.textColor >= 0 )
				{
					enemyname_mc.textColor = data.textColor;
				}
			}
			if(data.targetName!="")
			{
				this.visible=true;
			}
			var IconSource:String = data.avatarIconSource as String;
			if( IconSource.length>0 ){
				var AvatarButton_mc:MovieClip = this.getChildByName( "AvatarButton_mc" ) as MovieClip;
				if( AvatarButton_mc )
				{				
					var RoleIcon:UILoader = AvatarButton_mc.getChildByName( "RoleIcon" ) as UILoader;
					if( RoleIcon )
					{
					RoleIcon.source = data.avatarIconSource as String;
					}
				}
			}
			var TypeTf:TextField = getChildByName( "tf_type" ) as TextField;
			if( TypeTf )
			{
				TypeTf.text = data.typeText;
			}
			
			
		}

		public function HPTail( newPercent:Number ,startTail:Boolean, curHp:Number, maxHp:Number,showPercent:Boolean ):void
		{
			startTail = false;
			if( startTail )//开始拖尾
			{
				HPBarTail_mc.hpTailMask.x = HPBar_mc.hpMask.x;
				bStartTail = true;
				delaytime = 100;
			}
			( HPBar_mc.hpMask as MovieClip ).scaleX = newPercent;
			HPBar_mc.shine.x = HPBar_mc.hpMask.x + HPBar_mc.hpMask.width-7;//闪光的位置不大对
			if(showPercent)
			{
				var percentN:Number = Math.ceil(newPercent*100);
				NPCHP_Text.text = percentN + "%";
			}
			else if(maxHp>0 && curHp>0)
			{
				NPCHP_Text.text = curHp + "/" + maxHp;
			}
			else
			{
				NPCHP_Text.text = "";
			}
		}
		public function ShowBuff( buffSlotID:uint, buffIcon:String,  buffMaxTime:Number,  buffCurTime:Number, stackCount:uint , OwnerID:uint, buffID:uint, bShowTimeUp:uint, debuff:Boolean)
		{
			BuffComponent_mc.ShowBuff( buffSlotID, buffIcon,  buffMaxTime,  buffCurTime, stackCount ,OwnerID, buffID, bShowTimeUp, debuff);
			BuffComponent_mc.visible = true;
		}
		public function HideBuff( buffSlotID:uint)
		{
			BuffComponent_mc.HideBuff( buffSlotID);
		}
		public function HideAllBuff()
		{
			BuffComponent_mc.visible = false;
		}		
		function UpdateFrame():void
		{
			var frametime =  this["root"].frametime;//newtime-prev ;
			
			if(bStartTail)
			{
				delaytime -= frametime;
				if( delaytime >0 )
					return;
				HPBarTail_mc.hpTailMask.x -= frametime*0.4;
				if( HPBarTail_mc.hpTailMask.x < HPBar_mc.hpMask.x)
				{	
					bStartTail = false;
				}
			
			}
				
		}
	}
}