package UI_Hurt.HurtAS3{
	
	import ActionScript3.MyPanel;
	
	import flash.events.Event;
	import flash.events.MouseEvent;

	import scaleform.clik.controls.Button;
	import ActionScript3.MyTipButton;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import ActionScript3.MyTipButton
	import ActionScript3.MyCloseButton;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;

	public class HurtPopUp extends MyPanel {
		
		public var hurt_count:TextField;
		public var hurt_clear:Button;
		public var hurt_close:MyCloseButton;
		public var btn_down:Button;
		private var bool:Boolean=false;
		
		private var HurtFlag:Number = 10000;
		private var hurtAll_Text:String = "";
		private var hurt_Second:String = "";
			
		
		override protected function configUI():void
		{
			ShowMode = "TRB";
			super.configUI();
			hurt_clear.addEventListener(MouseEvent.CLICK,clickHandler);
			btn_down.addEventListener(MouseEvent.ROLL_OVER,overHandler);
			btn_down.addEventListener(MouseEvent.ROLL_OUT,outHandler);
			hurt_close.CloseTargetPanel = this;
			hurt_close.addEventListener(MouseEvent.CLICK,closeHandler);
			hurt_count.mouseEnabled=false;
			
			stageChangeHandler(null);
			
		}
		
		override protected function stageChangeHandler(e:ParamEvent):void
		{
			this.cavasWidth=GameDispathcher.getInstance().StageWidth;
			this.cavasHeight=GameDispathcher.getInstance().StageHeight;
			this.x=cavasWidth-306;
			this.y=cavasHeight-140;
		}
		
		//关闭提示
		private function closeHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASCloseHurtTips");
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowHurtTips",evt.target);
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideHurtTips");
		}
		
		private function downHandler(e:MouseEvent):void
		{//显示详细数据
			bool=!bool;
			this.parent.getChildByName("hurt_tips").visible=bool;
			ExternalInterface.call("ASViewPage_ClickHurtTips");
		}
		
		
		private function clickHandler(e:MouseEvent):void 
		{//清空伤害数据
			ExternalInterface.call("ASViewPage_ClickHurtClear");
		}
		
		public function UCSetHurtViewPage_AllData(dat:String,time:Number):void
		{
			var hurts:Number = 0;
			var hurt:Number = 0;
			
			if(!Number(dat))
			{
				hurts = 0;
			}
			else
			{
				hurts = Number(dat);
			}
			if (time <= 0)
			{
				time = 1;
			}
			else
			{
				hurt = hurts / time ;
			}
			
			
			hurt_Second = getHurtText(hurt);
			
			hurtAll_Text = getHurtText(hurts);

			
			hurt_count.text = hurtAll_Text + "("+ hurt_Second + "/" + "秒" + ")";
		}
		
		public function getHurtText(hurt:Number):String
		{
			var hurt_text:String = "";
			
			if(hurt >= HurtFlag)
			{
				hurt = hurt / HurtFlag;
				hurt_text =  hurt.toFixed(1) + "w";
			}
			else
			{
				hurt_text = hurt.toFixed(1);
				
			}
			return hurt_text;
		}
		

		
	}
	
}
