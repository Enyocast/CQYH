package ActionScript3
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import ActionScript3.MyCloseButton;
	import ActionScript3.MyHelperButton;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;

	public class MyWindowsFrame extends UIComponent
	{
		public var tF_windowTitle:TextField;
		public var btn_close:MyCloseButton;
		public var btn_help:MyHelperButton;
		public var InfoDragButton_mc:Button;
		public var content:TextField;
		public var textInput:TextInput;
		public var closeBtnBg:MovieClip;
		
		public function MyWindowsFrame():void
		{
			if(tF_windowTitle)
			{
				tF_windowTitle.text="";
			}
		}
		override protected function configUI():void
		{
			super.configUI();
		}
		
		//return InfoDragButton_mc's width and height because the windows bg have set a mask, the boundary is more big than the visible area
		override public function get width():Number
		{
			if(InfoDragButton_mc){
				return InfoDragButton_mc.width;// + 2 * InfoDragButton_mc.x;// offset in windows frame
			}
			return super.width;
		}
		
		override public function get height():Number
		{
			if(InfoDragButton_mc){
				return InfoDragButton_mc.height + 2 * InfoDragButton_mc.y;// offset in windows frame
			}
			return super.height;
		}
	}
}