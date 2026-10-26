package ActionScript3.Friend
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import ActionScript3.Friend.ContactWidget;
	import flash.utils.getDefinitionByName;
	import flash.utils.getQualifiedClassName;
	
	public class ContactLevel extends MyPanel
	{
		public var _ClassRef:Class;
		//public var bbb:ContactWidget;
		
		override protected  function configUI():void
		{
			
			super.configUI();
			
			//_ClassRef = getDefinitionByName( getQualifiedClassName(ActionScript3.Widget.ContactWidget)) as Class;
			_ClassRef = getDefinitionByName( "ContactDialog") as Class;
			
			
			
			//AddWindow("1111");
			//( this.getChildByName( "1111") as ContactWidget).WindowId = 5;
		}
		
		public function AddWindow( Windowname:String )
		{
			//trace(_ClassRef);
			
			/*var ContactMc = new _ClassRef;
			
			//trace(0);
			addChild(ContactMc);
			
			ContactMc.name = Windowname;
			ContactMc.x = 0;
			ContactMc.y = 0;
			
			*/
		}
		
		public function RemoveWindow( Windowname:String)
		{/*
			var ContactMc = this.getChildByName( Windowname);
			ExternalInterface.call( "ASTrace",ContactMc );
			if( ContactMc)
			removeChild(ContactMc);*/
		}
	}
}