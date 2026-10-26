package UI_Soul.SoulAS3
{
	//import ActionScript3.MyPanel;
	import scaleform.clik.core.UIComponent;
	
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.display.MovieClip;
	
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class SoulLevelUpPanel extends UIComponent
	{
		public var ToLvUpSoulMc:MyItemSlot;
		public var SacrificeSoulMc0:MyItemSlot;
		public var SacrificeSoulMc1:MyItemSlot;
		public var SacrificeSoulMc2:MyItemSlot;
		public var SacrificeSoulMc3:MyItemSlot;
		public var SacrificeSoulMc4:MyItemSlot;
		public var HelpLvUpSoulItemMc:MyItemSlot;
		
		public var SuccessRitoTf:TextField;
		public var CurLevelSoulPropTf:TextField;
		public var NextLevelSoulPropTf:TextField;
		
		public var ConfirmLevelUpBtn:Button;
		public var ResetLevelUpBtn:Button;
		
		override protected function configUI():void
		{
			super.configUI();
			
			ConfirmLevelUpBtn.addEventListener( MouseEvent.CLICK, onClickConfirmLevelUpBtn );
			ResetLevelUpBtn.addEventListener( MouseEvent.CLICK, onClickResetBtn );
			
			//ExternalInterface.call( "RegisterSoulLevelUp", this );
		}
		
		//
		function onClickConfirmLevelUpBtn( evt:Event )
		{
			ExternalInterface.call( "ASConfirmSoulLevelUp" );
		}
		
		//
		function onClickResetBtn( evt:Event )
		{
			ExternalInterface.call( "ASResetSoulLevelUp" );
		}
		
	}
}