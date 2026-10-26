package ActionScript3 {

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;

	import flash.external.ExternalInterface;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.MouseEvent;

	public class MyButtonDrag extends Button
	{
		public var Drag:Boolean = false;
		public var StartMouseX = 0;
		public var StartMouseY = 0;
		
		override protected  function configUI():void {		
			super.configUI();
			
			//_disableFocus = true;
			this.addEventListener( ButtonEvent.PRESS ,DragIn );
			this.addEventListener( ButtonEvent.RELEASE_OUTSIDE ,DragOut);
			this.addEventListener( ButtonEvent.CLICK ,DragOutInsize);
			
			this.addEventListener( MouseEvent.MOUSE_MOVE , MouseMove );
			//Mouse.removeListener (this);
		}
		
		function DragIn()
		{
			Drag = true;
			//Mouse.addListener(this);
			StartMouseX = mouseX;
			//StartMouseY = _ymouse;
		}
		
		function DragOut()
		{
			Drag = false;
			//Mouse.removeListener (this);
		}
		
		function DragOutInsize()
		{
			DragOut();
		}
		
		//Ëƺõmovieclip¾ͻáµ÷ÓÃ
		function MouseMove()
		{
			if(Drag)
			{
				ExternalInterface.call( "ButtonDrag" , mouseX - StartMouseX );
				StartMouseX = mouseX;
			}
		
		}

	}
}