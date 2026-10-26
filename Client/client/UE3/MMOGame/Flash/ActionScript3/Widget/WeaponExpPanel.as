package ActionScript3.Widget{
	
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import ActionScript3.Widget.UWindow;
	import ActionScript3.MyTipButton;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.MyCloseButton;
	import flash.events.MouseEvent;
	import ActionScript3.MyItemSlot;
	import flash.events.Event;
	
	public class WeaponExpPanel extends MyPanel
	{
		public var weaponSlot:MyItemSlot;
		public var CostType0:RadioButton;
		public var CostType1:RadioButton;
		public var CostType2:RadioButton;
		
		public var confirmButton:Button;
		public var cancelButton:Button;
				
		override protected  function configUI():void 
		{
			
			super.configUI();
			
			if( confirmButton )
			{
				confirmButton.addEventListener( "click" , clickConfirm );
			}
			
			if( cancelButton )
			{
				cancelButton.addEventListener( "click" , cancelConfirm );
			}
			
/*			if(tab0_mc)
			{
				tab0_mc.MWTabIcon_mc.gotoAndStop("shop2");
				tab0_mc.addEventListener( "click",clickTab0);
			}
			if(tab1_mc)
			{
				tab1_mc.MWTabIcon_mc.gotoAndStop("shop1");
				tab1_mc.addEventListener( "click",clickTab1);
			}
			
			if(tab2_mc)
			{
				tab2_mc.MWTabIcon_mc.gotoAndStop("shop4");
				tab2_mc.addEventListener( "click",clickTab2);
			}
			
			if(tab3_mc)
			{
				tab3_mc.MWTabIcon_mc.gotoAndStop("shop5");
				tab3_mc.addEventListener( "click",clickTab3);
			}
			
			if(BtnStall_mc)
				BtnStall_mc.addEventListener( "click",OpenStall );
					
			btnFuc1_mc.addEventListener(MouseEvent.CLICK, onLockItem);
			btnFuc2_mc.addEventListener(MouseEvent.CLICK, onSplitItem);
			btnFuc3_mc.addEventListener(MouseEvent.CLICK, onSort);
*/
			ExternalInterface.call( "RegisterWeaponExpPanel", this);			
			
		}
		
		function clickConfirm()
		{
			ExternalInterface.call( "ASGetWeaponExp");
		}
		
		function cancelConfirm( e:Event )
		{
			if(btn_close)
			{
				btn_close.dispatchEvent( e );
			}
		}

	
	}

}