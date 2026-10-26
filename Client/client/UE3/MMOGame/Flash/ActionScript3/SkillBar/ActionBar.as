package ActionScript3.SkillBar
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;

	import ActionScript3.MyMenuSlot;
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.SkillBar.SkillSettingPanel.SkillSettingShortcutPanel;
	import ActionScript3.Slot.MySlot;
	import ActionScript3.Widget.MyTipsText;
	
	import scaleform.clik.controls.Button;
	import ActionScript3.Slot.SkillSlotData;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import UI_SkillbarWidget.AS3.PetSkill;

	public class ActionBar extends MyPanel
	{
		public var NewSkillHintBtn:Button;

		public var slot_bg_0:MovieClip;
		public var slot_bg_1:MovieClip;
		public var slot_bg_2:MovieClip;
		public var slot_bg_3:MovieClip;
		public var slot_bg_4:MovieClip;
		public var slot_bg_5:MovieClip;
		public var slot_bg_6:MovieClip;
		public var slot_bg_7:MovieClip;
		public var slot_bg_8:MovieClip;
		public var slot_bg_9:MovieClip;
		public var slot_bg_10:MovieClip;
		public var slot_bg_11:MovieClip;
		
		public var slot_0:MySlot;
		public var slot_1:MySlot;
		public var slot_2:MySlot;
		public var slot_3:MySlot;
		public var slot_4:MySlot;
		public var slot_5:MySlot;
	    public var slot_6:MySlot;
		public var slot_7:MySlot;
		public var slot_8:MySlot;
		public var slot_9:MySlot;
		public var slot_10:MySlot;
		public var slot_11:MySlot;

		public var ExpHover:Button;
		public var exp_txt:TextField;

		//public var glass_bg_mc:MovieClip;
		public var HpBar_mc:MovieClip;
		public var MpBar_mc:MovieClip;
		public var glass_mc:MovieClip;
		public var ExpBar:MovieClip;
		public var ActionBarFx_mc:MovieClip;
		public var assassinBallSpliter:MovieClip;
		public var Exp_Extra:MovieClip;
		public var exp_light:MovieClip;
		public var HpTip:MyTipsText;
		public var MpTip:MyTipsText;
		
		public var ExpBar_Mask_mc:MovieClip;
		public var ExpPercent_txt:TextField;
		public var barBg_mc:MovieClip;
		
		public var expStartPos:int = 208;
		public var expMaskWidth:int = 420;
		public var _petSkill:PetSkill;

		override protected function configUI():void
		{
			ShowMode = "SkillBar";
			super.configUI();

			if (exp_txt)
			{
				exp_txt.visible = false;
			}
			if (ExpHover)
			{
				ExpHover.addEventListener( "rollOver" ,RollOverExp ,false,0,true);
				ExpHover.addEventListener( "rollOut" ,RollOutExp ,false,0,true);
			}
            assassinBallSpliter.mouseChildren=false;
			assassinBallSpliter.mouseEnabled=false;
			
			ActionBarFx_mc.gotoAndStop("end");
			//
			NewSkillHintBtn.addEventListener( MouseEvent.CLICK, onClickNewSkillHintBtn, false, 0, true );
			NewSkillHintBtn.addEventListener( MouseEvent.MOUSE_OVER, onMouseOverNewSkillHintBtn, false, 0, true );
			NewSkillHintBtn.addEventListener( MouseEvent.MOUSE_OUT, onMouseOutNewSkillHintBtn, false, 0, true );
			//
			ShowNewSkillHintBtn( false );
			
			ExpBar_Mask_mc = ExpBar.getChildByName("ExpBar_Mask_mc") as MovieClip;
			ExpPercent_txt = ExpBar.getChildByName("ExpPercent_txt") as TextField;
			barBg_mc = ExpBar.getChildByName("barBg_mc") as MovieClip;

			var j:int=1;
			for (var i:int = 0; i < 12; i++) 
			{
				var mc2:MovieClip=this.getChildByName("slot_bg_"+i) as MovieClip;
				mc2.mouseEnabled=false;
				mc2.mouseChildren=false;
				mc2.gotoAndStop(1);
				var txt:TextField=mc2.keyBind as TextField;
				txt.mouseEnabled=false;
				if(i<6)
				{
					txt.text="F"+j;
				}
				else
				{
					txt.text=j+"";
				}
				
				j++;
				if(j==7)
				{
					j=1;
				}
				var mc1:MovieClip=mc2.hitLight as MovieClip;
				mc1.visible=false;
				mc1.gotoAndStop(1);
				var mc3:MovieClip=mc2.mc_loop as MovieClip;
				mc3.visible=false;
				mc3.gotoAndStop(1);
				var mc4:MovieClip=mc2.mc_effect as MovieClip;
				mc4.visible=false;
				mc4.gotoAndStop(1);
			}

			hideExp();
			UCShowExpBuff(false);
			_petSkill.visible=false;
			stageChangeHandler(null);
			//TimerManager.getInstance().add(2000,step);
			//skill_2_mc.SetCD(20000,100000);
			//skill_2_mc.SetData( 0, "0.TGA", 1111, "", 1, -1, -1 );
			//GraySlotIcon( skill_2_mc, true );
			//GrayChildMc( skill_2_mc, true );
			//测试刺客职业
			//MpBar_mc.SetCareer( 2 );
			//MpBar_mc.MPTail( 0.30 ,false, 30 );
			//UCSetExpText( { expPercentText:"24%" ,maskWidth:240 , curExpBarX:4 , frameText:"full" } );
			//UCSetCareer( {Career:2 ,HpTip:"hp",MpTip:"mp"  });
			//MpBar_mc.MPTail( 0.30 ,true, 30 );

			//ExpBar_Mask_mc.width = 40;
			//UCSetExpExtra(1);
			//UCHintForItemSlot(true);
			//testData();
		}
		
/*		private function overMovieClipHandler(evt:MouseEvent):void
		{
			trace("overMovieClipHandler");
		}
		*/
		override protected function stageChangeHandler(evt:ParamEvent):void
		{ 
			super.stageChangeHandler(evt);
			this.y=cavasHeight;
			this.x=(cavasWidth-976>>1)+58;
		}
		
/*		private function testData():void
		{
			var DataObj:SkillSlotData = new SkillSlotData();
DataObj.isLocked = false;
DataObj.HaveData=true;
DataObj.slotID=10000;
DataObj.slotType=4;
DataObj.isUnusable = false;
DataObj.quantity = 3;
DataObj.totleCDMS = 10000;
DataObj.passedCDMS = 0;
DataObj.iconName = "1.TGA";
slot_0.SetDataObj(DataObj);
		}*/
		var ttt:int=2;
		private function step():void
		{
			UCSkillActivate(ttt,1,true);
			ttt++;
			if(ttt==6){
				ttt=2;
			}
		}
		
		/**
		 * 技能激活播放特效 
		 * index播放的技能类型ID，
		 */		
		public function UCSkillActivate(index:int,type:int,loop:Boolean):void
		{
			var mc:MovieClip;
			var mc1:MovieClip;
			if(type==0){
/*				mc=(this.getChildByName("skill_mc_"+index) as MovieClip).mc_effect as MovieClip;
				if(mc.visible==false){
					mc.gotoAndStop(1);
				}else{
					mc.gotoAndPlay(1);
				}
				mc.visible=loop;*/
			}else{
				mc1=this.getChildByName("slot_bg_"+index) as MovieClip;
				if(mc1.mc_loop.visible==loop){
					return;
				}
				if(loop==false){
					mc1.mc_loop.gotoAndStop(1);
				}else{
					mc1.mc_loop.gotoAndPlay(1);
				}
				mc1.mc_loop.visible=loop;
			}
		}
		
		//===============================================================================================================
		public function ShowNewSkillHintBtn( isShow:Boolean )
		{
			NewSkillHintBtn.visible = isShow;
			var animMc:MovieClip = NewSkillHintBtn.getChildByName( "AnimMc" ) as MovieClip;
			if( animMc ){
				animMc.visible = isShow;
				if( isShow ){
					animMc.gotoAndPlay( 1 );
				}
				else{
					animMc.gotoAndStop( 1 );
				}
			}
		}
		//传奇版本不显示
		public function UCSetSkillShortcutButtonsVisible(bVisible:Boolean):void
		{

		}
		
		public function UCSetSkillShortcutPanelVisible(bVisible:Boolean):void
		{
			
		}

		//-------------------------------------------------------------------------------------------------------------------------
		public function UCSetSkillShortcutPanelData(skillListType:int, titleString:String, skillData:Array):void
		{
			
		}
		//===============================================================================================================
		function onClickNewSkillHintBtn( evt:Event )
		{
			ExternalInterface.call("ASOnClickNewSkillLearnedBtn");
		}
		//-------------------------------------------------------------------------------------------------------------------------
		function onMouseOverNewSkillHintBtn( evt:Event )
		{
			var animMc:MovieClip = NewSkillHintBtn.getChildByName( "AnimMc" ) as MovieClip;
			if( animMc ){
				animMc.visible = false;
			}
		}
		//-------------------------------------------------------------------------------------------------------------------------
		function onMouseOutNewSkillHintBtn( evt:Event )
		{
			var animMc:MovieClip = NewSkillHintBtn.getChildByName( "AnimMc" ) as MovieClip;
			if( animMc ){
				animMc.visible = true;
			}
		}
		//===============================================================================================================
		public function UCSetCtrlType( type:int)
		{
		}
		
		//更新loop布局位置
		public function UCupdateLayou():void
		{
			var i:int=0;
			for(i=0;i<12;i++){
				var mc:MovieClip=this.getChildByName("slot_"+i) as MovieClip;
/*				var mc1:MovieClip= this.getChildByName("mc_loop"+i) as MovieClip; 
				var mc2:MovieClip=this.getChildByName("skill_bg_"+i) as MovieClip;
			    mc2.x=mc.x+5;
				mc2.y=mc.y+6;
				mc1.x=mc.x+1;
				mc1.y=mc.y+2;*/
			}
		}
		
		
		public function UCSetCareer( career:Object )
		{
			MpBar_mc.SetCareer( career.Career );
			HpTip.text = career.HpTip;
			MpTip.text = career.MpTip;
		}
		
		public function UCSetExpText( exp:Object )
		{
			if(exp_txt)
			{
				exp_txt.text = exp.expText;
			}
			if( ExpBar_Mask_mc )
			{
				ExpBar_Mask_mc.width = exp.maskWidth;
			}
			if( ExpPercent_txt )
			{
				ExpPercent_txt.text = exp.expPercentText;
			}
			if( barBg_mc )
			{
				barBg_mc.x = exp.curExpBarX;
				barBg_mc.gotoAndStop( exp.frameText );
			}
		}

		public function RollOverExp()
		{
			exp_txt.visible = true;
		}

		public function RollOutExp()
		{
			exp_txt.visible = false;
		}

		//开启/关闭对应的skillSlot动画
		public function UCHintForSkillSlot( slotIdx:int, isToShow:Boolean )
		{
/*			var mc:MovieClip=this.getChildByName("skill_bg_"+slotIdx) as MovieClip;
			mc.visible=isToShow;*/
		}
		
		//高级功能,自动显示可以拖的物品对应格子
		public function UCHintForItemSlot( isToShow:Boolean ):void
		{
			var j:int=0;
			for(j=0;j<12;j++){
				var mc2:MovieClip=(this.getChildByName("slot_bg_"+j) as MovieClip).hitLight as MovieClip;
		         mc2.visible=isToShow;
			}
		}
		
		public function UCGetBloodGlobeDrawX():Number
		{
			return this.HpBar_mc.HpMask.x + this.x;
		}
		
		public function UCGetBloodGlobeDrawY():Number
		{
			return this.HpBar_mc.HpMask.y + this.y;
		}
		
		public function UCGetEnergyGlobeDrawX():Number
		{
			return  UCGetBloodGlobeDrawX();
		}
		
		public function UCGetEnergyGlobeDrawY():Number
		{
			return UCGetBloodGlobeDrawY(); // 目前是在材质上进行了半球处理
		}
		
		public function UCShowGlobe(inShow:Boolean):void
		{
			//this.HpBar_mc.visible = inShow;
			//this.MpBar_mc.visible = inShow;
			//glass_bg_mc.visible = inShow;
			//glass_mc.visible = inShow;
			//return this.MpBar_mc.y;
		}
		//不显示道标
		public function UCSetExpExtra(percent:int)
		{
			if( percent <= 0 || percent>=100)
			{
				hideExp();
				return;
			}
			var posAdd:int =  432 * ( percent / 100 );
			Exp_Extra.x = expStartPos + posAdd;
			Exp_Extra.visible = true;
		}
		
		public function hideExp():void
		{
			Exp_Extra.visible = false;
		}
		
		public function UCShowExpBuff(v:Boolean):void
		{
			if(v)
			{
				exp_light.gotoAndPlay(1);
				exp_light.visible=true;
			}
			else
			{
				exp_light.gotoAndStop(1);
				exp_light.visible=false;
			}
		}
		
		public function GraySlotIcon( mc:MovieClip, gray:Boolean )
		{
			var slotIcon: MovieClip = mc.getChildByName( "itemSlotIcon" ) as MovieClip;
			GrayChildMc( slotIcon, gray );
		}
		
		//更新
		public function UCupdatePetSkill(statue:int):void
		{
			if(statue==-1)
			{
				_petSkill.visible=false;
			}
			else
			{
			   _petSkill.visible=true;
			   _petSkill.updatePetSkill(statue);
			}
		}
	}
}
