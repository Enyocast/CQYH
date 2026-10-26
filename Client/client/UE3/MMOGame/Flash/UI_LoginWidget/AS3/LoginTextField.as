package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.DropdownMenu;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.core.CLIK;
	import scaleform.clik.managers.FocusHandler;
	
	public class LoginTextField extends UIComponent {

		public var textInput_Name:TextInput ;
        public var textInput_Pwd:TextInput;
		public var logo_mc:MovieClip;
		public var ServeIP_mc:DropdownMenu;
		public var btn_Login:Button;
		public var groupNumb:TextInput;
		
		override protected function configUI():void
		{
			super.configUI();
			
			btn_Login.addEventListener(MouseEvent.CLICK,PushEnter);
			ResetFocus();
		}
		
		public function PushEnter(e:MouseEvent):void
		{
			var dat:Object={};
			dat.name=textInput_Name.text;
			dat.pwd=textInput_Pwd.text;
			dat.ip=ServeIP_mc.textField.text;
			dat.groupNumb = groupNumb.text;
			ExternalInterface.call("ASLoginGame",dat);
		}
		public function ResetFocus():void
        {
	        if(textInput_Name && textInput_Name.textField.text=="")
			{
				FocusHandler.getInstance().setFocus(textInput_Name.textField);
				//FocusHandler.getInstance().setFocus(textInput_Name); 
			 }
			 else
			 {
				 if(textInput_Pwd)
				 {
					 FocusHandler.getInstance().setFocus(textInput_Pwd.textField);
					 //FocusHandler.getInstance().setFocus(textInput_Pwd);
				 }
	          }
       	}
	
	  	public function UpdateUser(user:String):void
	   	{
			textInput_Name.text = user;
		}
		
	  	 public function updateServer(dat:String):void
	   	{
           	ServeIP_mc.dataProvider =new DataProvider( dat.split( "=" ) );
		   	ServeIP_mc.invalidateData();
           	ServeIP_mc.selectedIndex = 0;	
        	ServeIP_mc.validateNow();
	   	}
	      
	}
	
}
