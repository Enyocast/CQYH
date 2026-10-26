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

	public class MyRuneActiveButton extends Button
	{
		public var RuneSlot:int;
		public var tF_runeDuration:TextField;
		public var btn_rune:Button;
		public var sActive:String;
		public var tf_text:TextField;
		public var ActiveId:int;

		override protected function configUI():void 
		{
			super.configUI();
			trace("ActiveRune 0==========================");


			//this.addEventListener( "rollOver",OnThisHover );
			//this.addEventListener( "rollOut",OnThisOver );
			this.addEventListener( "click",ActivateRune );
			trace("ActiveRune 1==========================");


			RuneSlot = int ( name.substring( name.length-1 ) );
			sActive ="btn_rune"+RuneSlot;
			btn_rune = parent[sActive];
			tF_runeDuration = btn_rune['tF_runeDuration'];

			trace("ActiveRune 2==========================");

			trace("ActiveRune Setted==========================");
		}

		public function SetEnable( bEnable:Boolean )
		{
			enabled = bEnable;
			mouseEnabled = true;
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

		public function ActivateRune()
		{
			//按钮enable有问题
			if( !enabled )
				return;
			RuneSlot = int ( name.substring( name.length-1 ) );
			trace("ActivateRune()::"+RuneSlot);
			ExternalInterface.call("ASActivateRune",RuneSlot);
		}

		//激活按钮默认不显示 除非
		function OnThisHover()
		{
			tF_runeDuration.visible =false;
			visible = true;
			//ExternalInterface.call( "ShowTips",6,RuneSlot,this );
      ExternalInterface.call("ASShowTips_RuneActive", this );//代码里把tips.visible设true	
			
		}

		function OnThisOver()
		{       
			var Dur:int;
			Dur = btn_rune['CurDur'];
			if( Dur > 0 )
			{
				tF_runeDuration.visible =true;
				visible = false;
			}
			else
			{
				tF_runeDuration.visible = false;
				visible = true ;
			}
			//ExternalInterface.call( "HideTips",this );
      ExternalInterface.call("ASHideTips_RuneActive",this );
			ExternalInterface.call("ASHideTips");
		}

	}
}