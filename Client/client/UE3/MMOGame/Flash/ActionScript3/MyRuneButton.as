package ActionScript3 
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import flash.sampler.Sample;
	import ActionScript3.ItemSlotData;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.MyRuneActiveButton;

	public class MyRuneButton extends RadioButton
	{
		//public var runeLoader_mc:UILoader;
		public var btn_active:MyRuneActiveButton;
		public var RuneIconName:String;
		public var ActiveId:int;
		public var RuneSlot:int;
		public var CurDur:int;
		public var DurMax:int;
		public var CanActive:Boolean;
		public var tF_runeDuration:TextField;
		public var tF_runeName:TextField;
		public var _ItemData:ItemSlotData;
		public var OwnEnable:Boolean;
		
		public var rune_up_mc:MovieClip;
		public var rune_selected_mc:MovieClip;
		public var rune_over_mc:MovieClip;
		public var rune_down_mc:MovieClip;
		public var rune_disabled_mc:MovieClip;
		
		
		override protected function configUI():void 
		{
			var sActive:String;
			//非基础数据 则必须New出来
			_ItemData = new ItemSlotData;

			super.configUI();
			trace("Rune 0==========================");
			
			//this.addEventListener( "rollOver",OnThisHover );
			//this.addEventListener( "rollOut",OnThisOver );
			this.addEventListener( "click",EquipRune );
			trace("Rune 1==========================");
		

			RuneSlot = int ( name.substring( name.length-1 ) );
			sActive ="btn_active"+RuneSlot;
			btn_active = parent[sActive];
			trace("Rune 2==========================");

			

			SetRuneIcon(2,"魂淡");
			//SetCurDur(2003,1,20,true);

			trace("Rune 3==========================");
			
			_ItemData.itemtype = "skill";
			trace("Rune 4==========================");

			trace("Rune Setted==========================");
		}

		public function SetRuneIcon( skillRuneID:int,sRune:String )
		{
			trace("SetRuneIcon=========================="+skillRuneID +sRune );
			//RuneIconName = sName;
			tF_runeName.text = sRune;
			//先清一遍 上一次空图刷不出会导致LoaderContent为空
			//runeLoader_mc.unload();
			//runeLoader_mc.visible = true;
			//runeLoader_mc.source = RuneIconName+"1";
			//runeLoader_mc.visible = true;
			rune_up_mc.gotoAndStop( skillRuneID );
			rune_selected_mc.gotoAndStop( skillRuneID );
			rune_over_mc.gotoAndStop( skillRuneID );
			rune_down_mc.gotoAndStop( skillRuneID );
			rune_disabled_mc.gotoAndStop( skillRuneID );
			
			//ExternalInterface.call( "ASTrace", "SetRuneIcon ::  "+runeLoader_mc.source );
		}

		public function SetCurDur( inActiveId:int,Dur:int,Max:int,bCan:Boolean )
		{
			ActiveId = inActiveId;
			CurDur = Dur;
			DurMax = Max;
			CanActive = bCan;
			
			tF_runeDuration.text= Dur+"/"+Max;
			btn_active.SetEnable( CanActive );
			btn_active.ActiveId = inActiveId;

			if( CurDur > 0 )
				SetEnable( true );
			else
				SetEnable( false );
			ExternalInterface.call( "ASTrace", "Btn_Rune:: Slot"+RuneSlot +"Dur"+Dur );
		}

		override protected function handleMouseRollOver(event:MouseEvent):void 
		{
			super.handleMouseRollOver( event );
			OnThisHover();
		}

		override protected function handleMouseRollOut(event:MouseEvent):void 
		{
			super.handleMouseRollOut( event );
			OnThisOver();
		}


		//激活按钮默认不显示 除非
		function OnThisHover()
		{
			if(  CurDur < DurMax )
			{   
				btn_active.visible = true;
				tF_runeDuration.visible = false;
			}
			else 
			{
				btn_active.visible = false ;
				tF_runeDuration.visible = true ;
				//没法激活 或者不用激活
				//btn_active.enabled = false;
			}

			if( enabled )
			{
				//runeLoader_mc.visible = true;
				//runeLoader_mc.source = RuneIconName+"1";
				//runeLoader_mc.visible = true;
				//ExternalInterface.call( "ASTrace", "Set runeLoader_mc IMG Up Source::  "+runeLoader_mc.source );
			}
      		//ExternalInterface.call("ASTrace", "============== Mouse RollOver" + this + " -> " + Extensions.getMouseTopMostEntity() + " ==== " + targSlot );			
			ExternalInterface.call("ASShowTips_RuneButton", this );//代码里把tips.visible设true	
			
			//ExternalInterface.call( "ShowTips",7,ActiveId,this );
			//OnHover();
		}
		
		function OnThisOver()
		{
			SetEnable( enabled );
			//ExternalInterface.call( "ASTrace", "Set runeLoader_mc IMG Over Source::  "+runeLoader_mc.source );
			//ExternalInterface.call( "HideTips",this );
      		ExternalInterface.call("ASHideTips_RuneButton",this );
			ExternalInterface.call("ASHideTips");
			//OnRollOut();
		}

		public function SetEnable( bEnable:Boolean )
		{
			enabled = bEnable;
			mouseEnabled = true;
			if( bEnable )
			{
				btn_active.visible = false;
				tF_runeDuration.visible = true;

				//runeLoader_mc.visible = true;
				//runeLoader_mc.source = RuneIconName+"1";
				//runeLoader_mc.visible = true;
				//ExternalInterface.call( "ASTrace", "Set runeLoader_mc IMG Enable Source::  "+runeLoader_mc.source );
			}
			else
			{
				btn_active.visible = true;
				tF_runeDuration.visible = false;

				//runeLoader_mc.visible = true;
				//runeLoader_mc.source = RuneIconName+"0";
				//runeLoader_mc.visible = true;
				//ExternalInterface.call( "ASTrace", "Set runeLoader_mc IMG Disable Source::  "+runeLoader_mc.source );
			}
		}

		public function EquipRune()
		{
			//{
				//runeLoader_mc.visible = true;
				//runeLoader_mc.source = RuneIconName+"2";
				//runeLoader_mc.visible = true;
				//ExternalInterface.call( "ASTrace", "Set runeLoader_mc IMG MouseUp Source::  "+runeLoader_mc.source );
			//}
			trace("EquipRune()::"+RuneSlot);
			//还需要在UnrealScript中设置ItemSlot
			ExternalInterface.call("ASEquipRune",RuneSlot);
		}
	}

}