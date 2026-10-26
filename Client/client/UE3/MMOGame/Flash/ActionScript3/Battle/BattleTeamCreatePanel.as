package ActionScript3.Battle{
	import ActionScript3.MyPanel;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	//import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.controls.TextInput;
	import ActionScript3.MyScrollPanel;
	import flash.utils.getDefinitionByName;

	
	public class BattleTeamCreatePanel extends MyPanel
	{
		public var ConfirmButton:Button;
		public var CancelButton:Button;
		public var CheckName:Button;
		
		public var TeamNameInput:TextInput;
		
		
		public var SelectFlagBgLevel:MyScrollPanel;
		public var SelectFlagIconLevel:MyScrollPanel;
		
		public var FlagBgClass:Class;
		public var FlagIconClass:Class;
		
		public var FlagBgList:Array;
		
		//一行4个
		const CountPerline = 4; 
		//旗子背景间隔的宽度 高度
		const FlagBgSpaceWidth = 60;
		const FlagBgSpaceHeight = 64;
		//旗子前标识间隔的宽度 高度
		const FlagIconSpaceWidth = 60;
		const FlagIconSpaceHeight = 44;
		
		override protected function configUI():void
		{
			super.configUI();
			
			FlagBgClass = getDefinitionByName( "Btn_FlagBg") as Class;
			FlagIconClass = getDefinitionByName( "Btn_FlagPrint") as Class;
			FlagBgList = new Array;
			
			createFlagBg(1);
			createFlagIcon(1);
			
			ExternalInterface.call( "RegisterBattleTeamCreate", this );
			
			if(CheckName)
			{
				CheckName.addEventListener(MouseEvent.CLICK , clickCheckName , false , 0 , true );
			}
			if(ConfirmButton)
			{
				ConfirmButton.addEventListener(MouseEvent.CLICK , clickConfirmButton , false , 0 , true );
			}
			if(CancelButton)
			{
				CancelButton.addEventListener(MouseEvent.CLICK , clickCancelButton , false , 0 , true );
			}
			
		}
		
		function clickCheckName()
		{
			ExternalInterface.call( "ASBattleTeamCheckName", TeamNameInput.text );
		}
		
		function clickConfirmButton()
		{
			ExternalInterface.call( "ASBattleTeamCreateOk" );
		}
		
		function clickCancelButton( e:Event )
		{
			btn_close.dispatchEvent(e);
		}
		
		public function createFlagBg( number:int )
		{
			
			if( FlagBgClass && SelectFlagBgLevel && ( CountPerline != 0 ) )
			{
				
				
				for( var i:int = 0 ; i < number ; i++ )
				{
					
					var lineNum:int = i/CountPerline;
					var columnNum:int = i%CountPerline;
					var flagBgButton:RadioButton = new FlagBgClass as RadioButton;
					flagBgButton.x = columnNum * FlagBgSpaceWidth;
					flagBgButton.y = lineNum * FlagBgSpaceHeight;
					flagBgButton.name = "flagBgButton"+i;
					flagBgButton.addEventListener( MouseEvent.CLICK , ClickFlagBg , false , 0 , true );
					flagBgButton.itemid = i;
										
					if( i == 0 )
					{
						flagBgButton.selected = true;
					}
					
					SelectFlagBgLevel.addChild( flagBgButton );
				}
				

			}
		}
		
		function ClickFlagBg( e:Event )
		{
			if( e.target is RadioButton )
			{
				ExternalInterface.call( "ASBattleTeamClickFlagBg" , ( e.target as RadioButton ).itemid );
			}
		}
		
		public function createFlagIcon( number:int )
		{
			
			if( FlagIconClass && ( CountPerline != 0 ) )
			{
				
				for( var i:int = 0 ; i < number ; i++ )
				{
					
					var lineNum:int = i/CountPerline;
					var columnNum:int = i%CountPerline;
					var flagIconButton:RadioButton = new FlagIconClass as RadioButton;
					flagIconButton.x = columnNum * FlagIconSpaceWidth;
					flagIconButton.y = lineNum * FlagIconSpaceHeight;
					flagIconButton.name = "flagIconButton"+i;
					flagIconButton.itemid = i;
					flagIconButton.addEventListener( MouseEvent.CLICK , ClickFlagIcon , false , 0 , true );
					
					if( i == 0 )
					{
						flagIconButton.selected = true;
					}
					
					SelectFlagIconLevel.addChild( flagIconButton );
				}
				

			}
		}
		
		function ClickFlagIcon( e:Event )
		{
			if( e.target is RadioButton )
			{
				ExternalInterface.call( "ASBattleTeamClickFlagIcon" , ( e.target as RadioButton ).itemid );
			}
		}

	}
}