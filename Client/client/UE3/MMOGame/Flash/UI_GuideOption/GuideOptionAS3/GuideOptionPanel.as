package UI_GuideOption.GuideOptionAS3
{
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.managers.FocusHandler;
	import flash.text.TextField;
	
	public class GuideOptionPanel extends MyPanel
	{
		public var btn_cq:RadioButton;
		public var btn_cqyh:RadioButton;
		public var btn_ok:Button;
		public var _default:MovieClip;
		//public var tf_dec1:TextField;
		//public var tf_dec2:TextField;
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			_default.mouseChildren=false;
			_default.mouseEnabled=false;
			btn_cqyh.selected=true;
			//ExternalInterface.call( "SetTextByID",tf_dec1,"MMOGame.GuideOptionPanel.TaskModeCQYH");
			//ExternalInterface.call( "SetTextByID",tf_dec2,"MMOGame.GuideOptionPanel.TaskModeCQ");
			this.MyWindowsFrame_mc.btn_close.RemoveAddedEventListener();
			this.MyWindowsFrame_mc.btn_close.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_ok.addEventListener(MouseEvent.CLICK,okHandler);
		}
		
		private function okHandler(evt:MouseEvent):void
		{
			var type:int=0;
			if(btn_cq.selected)
			{
				type=1;
			}
			ExternalInterface.call("ASApplyGuideOption", type);
			OnCancel(null);
		}

		private function OnCancel(evt:MouseEvent):void
		{
			if(FocusHandler.getInstance().getFocus(0) !=null)
			{
				FocusHandler.getInstance().setFocus(null);
			}
			ExternalInterface.call("ASGuideOptionPanelClose");
		}
	}

}