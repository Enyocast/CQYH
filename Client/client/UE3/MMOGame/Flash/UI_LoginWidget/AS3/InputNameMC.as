package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import UI_ChatWidget.AS3.ChatTextField;
	
	
	public class InputNameMC extends UIComponent {
		
		public var input_Name:ChatTextField;
		public var DecTextInput_mc:MovieClip;
		
		protected var _bSaveRole:Boolean;

		override protected function configUI():void
		{
			super.configUI();
			input_Name.addEventListener(Event.CHANGE,inputHandler);
			input_Name.addEventListener("inputcopy",inputHandler);
			reset();
			//input_Name.maxChars=12;
		}
		
		public function get bSaveRole():Boolean
		{
			return _bSaveRole;
		}
		
		public function reset():void
		{
			input_Name.maxChars=8;
			UCUpdateInput(false,"");
		}

		public function inputHandler(e:Event):void
		{
			if ( 1 )
			{
				ExternalInterface.call("ASOnCreateRoleNameInput",input_Name.text);
			}
		}
		
		public function UCSetRoleName(roleName:String):void
		{
			input_Name.text = roleName;
			
		}		
		public function UCUpdateInput(bSaveRole:Boolean, strScript:String):void
		{
			_bSaveRole = bSaveRole;
			if(strScript.length>0){
				DecTextInput_mc.visible = true;
				var Script_txt:TextField = DecTextInput_mc.getChildByName( "Script_txt" ) as TextField; 
				if(Script_txt){
					Script_txt.text = strScript;
				}
			}
			else
			{
				DecTextInput_mc.visible = false;
			}
		}				
	}
	
}
