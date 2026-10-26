package UI_ChatWidget.AS3 {
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	public class ChatTabButton extends UIComponent {
		
		public var tipsHtml:String;
		override protected function configUI():void
		{
			super.configUI();
		}
		
		//更新复选框选中状态(默认全部选中)
		public function updateTAbCheckBox(dat:Array):void
		{
			var i:int=0;
			for(i=0;i<7;i++)
			{
				var btn:CheckBox=this.getChildByName("radioBtn_"+i) as CheckBox;
				var obj:Boolean=dat[i];
				if(btn)
				{
					btn.addEventListener(MouseEvent.ROLL_OVER,overHandler);
				    btn.addEventListener(MouseEvent.ROLL_OUT,outHandler);
					btn.selected=obj;
				}
			}
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			var btn:CheckBox=evt.currentTarget as CheckBox;
			var str:String="MMOGame.Chat.ShowChannel";
			if(btn && btn.selected==true)
			{
				str="MMOGame.Chat.HideChannel";
			}
			ExternalInterface.call("ASGetStringByID",this,"tipsHtml",str);
			ExternalInterface.call("ASShowTips_PlainText",this );
		}
		
	    private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_PlainText",this );
		}
		
		public function clear():void
		{//清空特效
			
		}
	}
	
}
