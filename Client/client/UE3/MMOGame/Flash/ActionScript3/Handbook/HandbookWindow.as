package ActionScript3.Handbook
{
	import flash.text.TextField;
	
	import ActionScript3.MyWindowsFrame;
	
	public class HandbookWindow extends MyWindowsFrame
	{
		public var tF_windowTitle_rune:TextField;
		// rune name is too long to display with noraml text format
		private var _isRunePage:Boolean;
		
		public function HandbookWindow()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			tF_windowTitle_rune.visible = false;
		}
		
		public function setViewType(uiType:int):void
		{
			_isRunePage = (uiType == ConstansDefine.handbook_rune);
			tF_windowTitle_rune.visible = _isRunePage;
			tF_windowTitle.visible = !_isRunePage;
		}
		
		public function SetWindowTitle(title:String):void
		{
			if(_isRunePage)
			{
				tF_windowTitle_rune.text = title;
			}
			else
			{
				tF_windowTitle.text = title;
			}
			
		}
	}
}