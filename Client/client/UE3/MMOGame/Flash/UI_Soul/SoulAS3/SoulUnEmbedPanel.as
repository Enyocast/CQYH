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
	
	public class SoulUnEmbedPanel extends UIComponent
	{
		public var ToUnEmbedEquipMC:MyItemSlot;
		
		public var UnEmbedSoulSlot0:MyItemSlot;
		public var UnEmbedSoulSlot1:MyItemSlot;
		public var UnEmbedSoulSlot2:MyItemSlot;
		
		public var UnEmbedSoulBgMc0:MovieClip;
		public var UnEmbedSoulBgMc1:MovieClip;
		public var UnEmbedSoulBgMc2:MovieClip;
		
		public var OriginalPropInUnEmbedTf:TextField;
		public var ResultPropInUnEmbedTf:TextField;
		public var TotalSoulPropInUnEmbedTf:TextField;
		
		public var UnEmbedFeeTf:TextField;
		
		public var UnEmbedConfirmBtn:Button;
		public var UnEmbedCancelBtn:Button;
		
		public var FX_UnEmbed_mc:MovieClip;
		
		private static const UNEMBED_FX_POS_X:Array = [30,138,246];
		private static const UNEMBED_FX_POS_Y:Number = 216;
		
		private var _selectedIdx:int = -1;
		
		override protected function configUI():void
		{
			super.configUI();
			
			UnEmbedSoulSlot0.addEventListener( MouseEvent.CLICK, function _onClickSoul(e:Event){ onClickSoulToSelect( 0 );} );
			UnEmbedSoulSlot1.addEventListener( MouseEvent.CLICK, function _onClickSoul(e:Event){ onClickSoulToSelect( 1 );} );
			UnEmbedSoulSlot2.addEventListener( MouseEvent.CLICK, function _onClickSoul(e:Event){ onClickSoulToSelect( 2 );} );
			
			UnEmbedConfirmBtn.addEventListener( MouseEvent.CLICK, onClickConfirmBtn );
			UnEmbedCancelBtn.addEventListener( MouseEvent.CLICK, onClickCancelBtn );
			
			FX_UnEmbed_mc.visible = false;
			FX_UnEmbed_mc.gotoAndStop(1);
			FX_UnEmbed_mc.addFrameScript(FX_UnEmbed_mc.totalFrames - 1, onFXAnimationCompelte);
		}
		
		//
		function onClickSoulToSelect( idx:int )
		{
			ExternalInterface.call( "ASSelectUnEmbedSoul", idx );
			_selectedIdx = idx;
		}
		
		//
		function onClickConfirmBtn( evt:Event )
		{
			ExternalInterface.call( "ASConfirmUnEmbed" );
		}
		
		//
		function onClickCancelBtn( evt:Event )
		{
			ExternalInterface.call( "ASCancelUnEmbed" );
		}
		
		public function UCSetUnEmbedResult(value:int):void
		{
			if(value > 0)
			{
				if(_selectedIdx>=0 && _selectedIdx < UNEMBED_FX_POS_X.length)
				{
					FX_UnEmbed_mc.x = UNEMBED_FX_POS_X[_selectedIdx];
					FX_UnEmbed_mc.y = UNEMBED_FX_POS_Y;
					FX_UnEmbed_mc.visible = true;
					UnEmbedConfirmBtn.enabled = false;
					FX_UnEmbed_mc.gotoAndPlay(1);
				}
			}
		}
		
		private function onFXAnimationCompelte():void
		{
			UnEmbedConfirmBtn.enabled = true;
			FX_UnEmbed_mc.visible = false;
		}
	}
}