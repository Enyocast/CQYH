package ActionScript3.Battle{
	
	import ActionScript3.MyItemSlotShow;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	//import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Battle.BattleRandomSelect;
	import ActionScript3.Battle.BattleFreeSelect;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyPanel;
	import ActionScript3.MyWindowsFrame;
	
	public class ArenaPanel extends MyPanel
	{
		public var ConfirmButton:Button;
		public var CancelButton:Button;
		
		public var ArenaMode0:RadioButton;
		public var ArenaMode1:RadioButton;
		//public var ArenaMode2:RadioButton;
		
		public var ArenaSize0:RadioButton;
		public var ArenaSize1:RadioButton;

		public var ArenaModeText:TextField;
		public var ArenaSizeText:TextField;
		public var OpenTimeText:TextField;
		
		public var bg:MyWindowsFrame;
		
		override protected function configUI():void
		{
			if(bg)
			{
				this.btn_close = bg.btn_close;
				this.InfoDragButton_mc = bg.InfoDragButton_mc;
			}
			
			super.configUI();
			
			if(ConfirmButton)
			{
				ConfirmButton.addEventListener(MouseEvent.CLICK , clickConfirm , false , 0 , true );
			}
			
			if( CancelButton )
			{
				CancelButton.addEventListener(MouseEvent.CLICK , clickCancel , false , 0 , true );
			}
			
			ExternalInterface.call( "RegisterArena", this );
			
			//SetPanelText( {titleName:"gg"} );
		}
		
		function clickConfirm()
		{
			ExternalInterface.call("ASArenaEnter");
		}
		
		function clickCancel( e:Event )
		{
			if( parent )
			{
				var CloseButton:Button = parent.getChildByName( "btn_close" ) as Button;
				if( CloseButton )
				{
					CloseButton.dispatchEvent(e);
				}
			}
		}
		
		public function SetPanelText( data:Object )
		{
			if(data)
			{
				if(bg)
				{
					bg.tF_windowTitle.text = data.titleName;
				}
				
				if( ArenaModeText )
				{
					ArenaModeText.text = data.arenaModeText;
				}
				
				if( ArenaSizeText )
				{
					ArenaSizeText.text = data.arenaSizeText;
				}
				
				if( OpenTimeText )
				{
					OpenTimeText.text = data.openTimeText;
				}
		
				if( ConfirmButton )
				{
					ConfirmButton.label = data.confirmButton;
				}
			}
		}
		
	}
}