package UI_Hang.AS3 {
	
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip;
	import flash.text.TextField;

	public class ConfigGame3 extends UIComponent {
		
		public var btn_default:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_apply:Button;
		public var btn_cq:RadioButton;
		public var btn_cqyh:RadioButton;
		public var _default:MovieClip;
		//public var tf_dec0:TextField;
		//public var tf_dec1:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			_default.mouseChildren=false;
			_default.mouseEnabled=false;
			//ExternalInterface.call( "SetTextByID",tf_dec0,"MMOGame.GuideOptionPanel.TaskModeCQYH");
			//ExternalInterface.call( "SetTextByID",tf_dec1,"MMOGame.GuideOptionPanel.TaskModeCQ");
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
		}
		
		private function OnDefault(evt:MouseEvent):void
		{
			btn_cqyh.selected=true;
		}
		
		public function setConfigData(dat:ConfigGameData):void
		{
			if (!dat.game3_enable)
				return;
				
			if(dat.taskModeType==0)
			{
				btn_cqyh.selected=true;
				updateLayou(98);
			}
			else
			{
				btn_cq.selected=true;
				updateLayou(345);
			}
		}
		
		private function updateLayou(idx:int=98):void
		{
			_default.x=idx;
		}
		
		private function OnOK(evt:MouseEvent):void
		{
			OnApply(null);
			OnCancel(null);	
		}
		
		private function OnCancel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASOnPanelClose" , "Assist");
		}
		
		private function OnApply(evt:MouseEvent):void
		{
		    var dat:ConfigGameData = new ConfigGameData();
			
			dat.game3_enable = true;
			
			var type:int=0;
			if(btn_cq.selected)
			{
				type=1;
				updateLayou(345);
			}
			else
			{
				updateLayou(98);
			}
			dat.taskModeType = type;
			ExternalInterface.call("ASApplyGameConfig", dat);
		}
	}
	
}
