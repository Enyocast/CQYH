package ActionScript3.Widget
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	
	import flash.utils.getDefinitionByName;
	import flash.utils.getQualifiedClassName;
	import flash.display.DisplayObject;
	import scaleform.clik.managers.FocusHandler;
	
	public class MyMessageboxZone extends MyPanel
	{
		public var _inputClassRef:Class;
		public var _modalClassRef:Class;
		public var _modelessClassRef:Class;
		public var _modalInputClassRef:Class;
		public var _checkBoxClassRef:Class;
		public var _modelessExtrClassRef:Class;

		override protected  function configUI():void
		{
			super.configUI();
			_inputClassRef = getDefinitionByName( "MyInputMsgBox" ) as Class;
			_modalClassRef = getDefinitionByName( "ModalMessageBox" ) as Class;
			_modelessClassRef = getDefinitionByName( "ModelessMsgBox" ) as Class;
			_modalInputClassRef = getDefinitionByName( "ModalInputMsgBox" ) as Class;
			_checkBoxClassRef   = getDefinitionByName( "CheckMessageBox" ) as Class;
			_modelessExtrClassRef = getDefinitionByName( "MsgboxExtr" ) as Class;
			ExternalInterface.call( "RegisterMessageboxZone" , this );
			
			//AddModalInputMsgbox("",false);			
			//AddInputMsgbox("",false);
			//ClearAllMsgbox();
			//AddModalMsgbox("",true);
			//AddMsgboxWithCheckBox("",false);
			
			
		}
		
		public function ClearAllMsgbox()
		{
			while( this.numChildren > 0 )
			{
				removeChildAt(0);
			}
		}
		
		public function GetFirstChild():MovieClip
		{
			for( var i:int = 0 ; i < this.numChildren ; i++ )
			{
				if( ( this.getChildAt(i) as MovieClip ) )
				{
					return this.getChildAt(i) as MovieClip;
				}
				
			}

			
			return null;
		}
		

		
		public function AddModalMsgbox( msgbox:String , twoButton:Boolean ):MovieClip
		{
			if( _modalClassRef != null )
			{
				var win = new _modalClassRef;
				win.name = msgbox;
				this.addChild( win );
				
				if( !twoButton )
				{
					win.SetOneButton();
				}
				
				return win;
			}
			return null;
			
		}
		
		public function AddInputMsgbox( msgbox:String , twoButton:Boolean ):MovieClip
		{
			if( _inputClassRef != null )
			{
				var win = new _inputClassRef;
				win.name = msgbox;
				this.addChild( win );
				
				if( !twoButton )
				{
					win.SetOneButton();
				}
				
				if(win && win.textInput)
				{
					FocusHandler.getInstance().setFocus(win.textInput.textField);
				}
				
				return win;
			}
			return null;
		}
		
		public function AddModelessMsgbox( msgbox:String , twoButton:Boolean ):MovieClip
		{
			if( _modelessClassRef != null )
			{
				var win = new _modelessClassRef;
				win.name = msgbox;
				this.addChild( win );
				
				if( !twoButton )
				{
					win.SetOneButton();
				}
				return win;
			}
			return null;
		}
		
		public function AddModalInputMsgbox( msgbox:String , twoButton:Boolean ):MovieClip
		{
			if( _modalInputClassRef != null )
			{
				var win = new _modalInputClassRef;
				win.name = msgbox;
				this.addChild( win );
				
				if( !twoButton )
				{
					win.SetOneButton();
				}
				
				if(stage && win.textInput)
				{
					win.SetTextInputFocus();
				}
				
				return win;
			}
			return null;
		}
		public function AddMsgboxWithCheckBox( msgbox:String , twoButton:Boolean ):MovieClip
		{
			if( _checkBoxClassRef != null )
			{
				var win = new _checkBoxClassRef;
				win.name = msgbox;
				win.InitCheckMessage("",false);
				this.addChild( win );
				
				if( !twoButton )
				{
					win.SetOneButton();
				}
			
				return win;
			}
			return null;
		}
		
		public function AddModelessExtrMsgbox( msgbox:String , twoButton:Boolean ):MovieClip
		{
			if( _modelessExtrClassRef != null )
			{
				var win = new _modelessExtrClassRef;
				win.name = msgbox;
				this.addChild( win );
				
				if( !twoButton )
				{
					win.SetOneButton();
				}
				return win;
			}
			return null;
		}
		
				
	}
}