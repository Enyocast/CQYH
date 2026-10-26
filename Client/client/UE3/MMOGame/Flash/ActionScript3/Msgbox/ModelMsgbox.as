package ActionScript3.Msgbox
{
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import scaleform.clik.controls.TextInput;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.MyPanel;

	import flash.external.ExternalInterface;

	//¡ä????
	public class ModelMsgbox extends Msgbox
	{
		public var _bg_MessageBox:MovieClip;
		override protected function configUI():void 
		{
			super.configUI();
			MyWindowsFrame_mc.InfoDragButton_mc.visible = false;


		}		
		
		override public function setCenter():void
		{
			super.setCenter();
			if(ShowMode == "BC")
			{
				_bg_MessageBox.x = -x;
				_bg_MessageBox.y = -y;			
			}
		}		
		
	}

}