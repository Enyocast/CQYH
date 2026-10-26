package UI_Soul.SoulAS3
{
	//import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class SoulEmbedPanel extends UIComponent
	{
		public var ToEmbedEquipMc:MyItemSlot;
		
		public var EmbedSoulSlot0:MyItemSlot;
		public var EmbedSoulSlot1:MyItemSlot;
		public var EmbedSoulSlot2:MyItemSlot;
		
		public var EmbedSoulBgMc0:MovieClip;
		public var EmbedSoulBgMc1:MovieClip;
		public var EmbedSoulBgMc2:MovieClip;
		
		public var FX_equip:MovieClip;
		public var FX_soul_0:MovieClip;
		public var FX_soul_1:MovieClip;
		public var FX_soul_2:MovieClip;
		
		public var OriginalPropTf:TextField;
		public var ResultPropTf:TextField;
		public var TotalSoulPropTf:TextField;
		
	//	public var SoulEmbedHintTf:TextField;
		
		public var ConfirmBtn:Button;
		public var ResetBtn:Button;
		
		private static const NUMBER_OF_SLOT:int = 3;
		
		override protected function configUI():void
		{
			super.configUI();
			
			ConfirmBtn.addEventListener( MouseEvent.CLICK, onClickConfirmBtn );
			ResetBtn.addEventListener( MouseEvent.CLICK, onClickResetBtn );
			FX_equip.visible = FX_soul_0.visible = FX_soul_1.visible = FX_soul_2.visible = false;
			FX_equip.addFrameScript(FX_equip.totalFrames - 1, onFXAnimationComplete)
		}
		
		private function onFXAnimationComplete():void
		{
			FX_equip.visible = FX_soul_0.visible = FX_soul_1.visible = FX_soul_2.visible = false;
		}
		
		//
		function onClickConfirmBtn( evt:Event )
		{
			ExternalInterface.call( "ASConfirmSoulEmbed" );
		//	UCSetEmbedResult(1<<0);
		}
		
		//
		function onClickResetBtn( evt:Event )
		{
			ExternalInterface.call( "ASResetSoulEmbed" );
		}
		
		public function UCSetEmbedResult(value:int):void
		{
			if(value == 0)
			{
				return;
			}
			for(var i:int = 0; i < NUMBER_OF_SLOT; i++)
			{
				if((value & (1 << i)) != 0)
				{
					(this['FX_soul_' + i] as MovieClip).visible = true;
					(this['FX_soul_' + i] as MovieClip).gotoAndPlay(1);
				}
			}
			FX_equip.visible = true;
			FX_equip.gotoAndPlay(1);
			//sound
			playSound("SoulEmbed_FX");
		}
	}
}