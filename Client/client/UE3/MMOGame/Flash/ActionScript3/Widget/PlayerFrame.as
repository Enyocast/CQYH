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
	import ActionScript3.Widget.BuffComponent;
	import flash.filters.ColorMatrixFilter;
	import ActionScript3.Common.Events.ParamEvent;
	import UI_HudInfoWidget.AS3.PkOptionPanel;
	import scaleform.clik.managers.PopUpManager;

	public class PlayerFrame extends MyPanel
	{
		public var PlayerBuffPanel_mc:BuffComponent;
		public var playerProIcon:Button;
		
		var tipsHtml:String = "";
		var mPkMode:int = 0;
		public var pkOption:PkOptionPanel
		public var PlayerName_mc:TextField;
		public var leveltext:TextField;
		//public var hpFill_mc:MovieClip;
		public var teamLeader:MovieClip;
		public var btnPkFlagOption:MovieClip;
		//public var playerProIcon:Button;
		public var btn_vip:MovieClip;
        public var pkList:Array=["和平攻击","公会攻击","组队攻击","全体攻击","善恶对攻"];
		override protected function configUI():void
		{
			ShowMode="HUD";
			super.configUI();
			if(playerProIcon)
			{
				playerProIcon.addEventListener( MouseEvent.CLICK , MouseRightClick );
			}
			if(btnPkFlagOption)
			{
				btnPkFlagOption.addEventListener(MouseEvent.CLICK ,ShowPanel);
				btnPkFlagOption.addEventListener(MouseEvent.ROLL_OVER ,function _showTips(e:Event){ playSound("menu_highlight"); ShowTips(e,0);});
				btnPkFlagOption.addEventListener(MouseEvent.ROLL_OUT,RollOut);
			}
			if(PlayerBuffPanel_mc)
			{
				PlayerBuffPanel_mc.visible=true;
				this.removeChild(PlayerBuffPanel_mc);
				PopUpManager.show(PlayerBuffPanel_mc,PlayerBuffPanel_mc.x,PlayerBuffPanel_mc.y,null, 3);
			}

			if(pkOption)
			{
				pkOption.visible = false;
				this.removeChild(pkOption);
			}
			UCVipShow(3);
			SetPkMode(0);
			btn_vip.addEventListener(MouseEvent.CLICK,vipClickHandler);
			btn_vip.addEventListener(MouseEvent.ROLL_OVER,vipOverHandler);
			btn_vip.addEventListener(MouseEvent.ROLL_OUT,vipOutHandler);
			stageChangeHandler(null);
		}
		public function UCVipShow(dat:int):void
		{
			if(dat>0){
				btn_vip.filters=[];
				btn_vip.visible=true;
			    btn_vip.gotoAndStop(dat);
			}else{
				btn_vip.filters=[ new ColorMatrixFilter([0.33,0.33,0.33,0,0,0.33,0.33,0.33,0,0,0.33,0.33,0.33,0,0,0,0,0,1,0])];
			}
            btn_vip.visible=false;
		}
		protected function vipClickHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASVIPRightClick");
		}
		
		protected function vipOverHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASVIPShowTips",e.target);
		}
		
		protected function vipOutHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASVIPHideTips");
		}

		function MouseRightClick( e:Event )
		{
			if ((e as MouseEventEx).buttonIdx == 1)
			{
				if (e.target is Button)
				{
					ExternalInterface.call( "ASMyInfoRightClick", root.mouseX , root.mouseY );
				}
			}
		}

		public function ShowBuff( buffSlotID:uint, buffIcon:String,  buffMaxTime:Number,  buffCurTime:Number, stackCount:uint , OwnerID:uint, buffID:uint, bShowTimeUp:uint, debuff:Boolean)
		{
			PlayerBuffPanel_mc.ShowBuff( buffSlotID, buffIcon,  buffMaxTime,  buffCurTime, stackCount ,OwnerID, buffID, bShowTimeUp, debuff);
		}
		public function HideBuff( buffSlotID:uint)
		{
			PlayerBuffPanel_mc.HideBuff( buffSlotID);
		}
		public function HideAllBuff()
		{
			PlayerBuffPanel_mc.visible = false;
		}


		public function SetHp(curHp:Number, maxHp:Number):void
		{
/*			
			if (maxHp>=curHp && maxHp>0)
			{
				( hpFill_mc.hpMask as MovieClip ).scaleX = curHp/maxHp;
			}
			else
			{
				( hpFill_mc.hpMask as MovieClip ).scaleX = 1.0;
			}*/
		}

		public function SetPkMode(PkMode:int):void
		{
			mPkMode = PkMode;
			btnPkFlagOption.gotoAndStop(PkMode+1);
		   (btnPkFlagOption.pkName as TextField).text=this.pkList[PkMode];
		}

		private function ShowTips(e:Event,slot:Number):void
		{
			ExternalInterface.call("ASGetStringByID",this,"tipsHtml","MMOGame.PkMode.PkTips"+mPkMode );

			ExternalInterface.call("ASShowTips_PlainText",this );
		}


		private function HideTips():void
		{
			ExternalInterface.call("ASHideTips_PlainText",this );

		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.y=cavasHeight-168;
			pkOption.y=this.y-35;
			PlayerBuffPanel_mc.y=this.y-30;
		}

		private function ShowPanel(evt:MouseEvent=null):void
		{
			pkOption.visible=!pkOption.visible;
			pkOption.UCShow(pkOption.visible,pkOption.x,pkOption.y,4);
			playSound("menu_click");
			RollOut(null);
		}

		private function RollOut(e:MouseEvent):void
		{
			HideTips();
		}

	}
}