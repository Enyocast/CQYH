package UI_ChatWidget.AS3
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.CheckBox;
	import flash.events.FocusEvent;
	import scaleform.clik.events.ButtonEvent;
	
	public class ChatOptionPanel extends MyPanel
	{
		public var btnChannelDelete:Button;
		public var btnChannelAdd:Button;
		public var btn_Reset:Button;
		public var btn_Apply:Button;
		
		public var channelNameInput:TextInput;
		
		public var ChatFilter0:CheckBox;
		public var ChatFilter1:CheckBox;
		public var ChatFilter2:CheckBox;
		public var ChatFilter3:CheckBox;
		public var ChatFilter4:CheckBox;
		public var ChatFilter5:CheckBox;
		public var ChatFilter6:CheckBox;
		public var ChatFilter7:CheckBox;
		
		override protected function configUI():void 
		{
			ShowMode="BC";
			super.configUI();
			btnChannelDelete.addEventListener(MouseEvent.CLICK,DeleteChannel );
			btnChannelAdd.addEventListener(MouseEvent.CLICK,AddChannel );
			btn_Reset.addEventListener(MouseEvent.CLICK,Reset );
			btn_Apply.addEventListener(MouseEvent.CLICK,Apply );
			
			var i:int = 0;
			for( i = 0 ; i < 6 ; i++ )
			{
				var channelBut:RadioButton = this.getChildByName("btnChannelText"+i) as RadioButton;
				if( channelBut )
				{
					channelBut.itemid = i;
					channelBut.addEventListener( ButtonEvent.CLICK , clickChannel );
				}
			}
			
			for( i = 0 ; i < 8 ; i++ )
			{
				var filterBut:CheckBox = this.getChildByName("ChatFilter"+i) as CheckBox;
				if( filterBut )
				{
					filterBut.itemid = i;
					filterBut.addEventListener( ButtonEvent.CLICK , clickFilter );
				}
			}
			if(channelNameInput)
				channelNameInput.addEventListener(FocusEvent.FOCUS_OUT , focusOutInput);
		}
		
		public function SetPanelText( data:Object )
		{
			this.SetWindowTitle(data.panelName);
			if( btnChannelAdd )
			{
				btnChannelAdd.label = data.button0;
			}
			if( btnChannelDelete )
			{
				btnChannelDelete.label = data.button1;
			}
			if( btn_Reset )
			{
				btn_Reset.label = data.button2;
			}
			if( btn_Apply )
			{
				btn_Apply.label = data.button3;
			}
		}
		
		function focusOutInput(evt:FocusEvent):void
		{
			ExternalInterface.call( "ASChatOptionChannelNameChanged" , channelNameInput.text );
		}
		
		function clickFilter(e:ButtonEvent):void
		{
			if( e.currentTarget is CheckBox)
			{
				ExternalInterface.call( "ASChatOptionClickFilter" , (e.currentTarget as CheckBox).itemid , (e.currentTarget as CheckBox).selected );
			}
		}

		private function clickChannel( e:ButtonEvent ):void
		{
			if( e.currentTarget is RadioButton)
			{
				ExternalInterface.call( "ASChatOptionClickChannel" , (e.currentTarget as RadioButton).itemid );
			}
		}



		function DeleteChannel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASChatOptionDeleteChannel");
		}

		function AddChannel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASChatOptionAddChannel");
		}

		function Reset(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASChatOptionReset");
		}

		function Apply(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASChatOptionApply");
		}
	}
}