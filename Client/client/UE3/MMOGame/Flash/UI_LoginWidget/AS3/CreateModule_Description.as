package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	
	public class CreateModule_Description extends MovieClip {
		
		//public var tF_Description:TextField;
		public function CreateModule_Description() {
			// constructor code
		}
		
		public function SetCareer(roleCareer:int):void
		{
			//ExternalInterface.call("SetTextByID",tF_Description,"MMOGame.SchoolDescribe.SchoolDescribe"+roleCareer );
	        switch ( roleCareer )
	        {
                case 0 :
			    gotoAndPlay("warrior");
			    break;
			   	case 1 :
				gotoAndPlay("mage");
				break;
			    case 2 :
				gotoAndPlay("assassin");
				break;
				case 3 :
				gotoAndPlay("archer");
				break;
				default:
				gotoAndPlay("taoist");
				break;
			}
		}
		
/*		public function update(dat:String):void
		{
			tF_Description.text=dat;
		}*/
	
	}
	
}
