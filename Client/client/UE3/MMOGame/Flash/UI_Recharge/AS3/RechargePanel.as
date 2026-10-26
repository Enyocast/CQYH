package UI_Recharge.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.TextInput_Advanced;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.events.ComponentEvent;
	import flash.text.TextFieldAutoSize;
	
	public class RechargePanel extends MyPanel 
	{
		public var btn_recharge:Button;
		public var txt_gold:TextField;
		public var btn_exchange:Button;
		public var item0:RechargeItem;
		public var item1:RechargeItem;
		public var item2:RechargeItem;
		public var input:TextInput_Advanced;
		private var itemList:Array=[3,12,36];
		private var gold:Number;
		public var tf_num:TextField;
		override protected  function configUI():void 
		{
			ShowMode="BC";
			super.configUI();
			this.SetWindowTitle("点卡交易");
			var i:int=0;
			for(i=0;i<3;i++)
			{
				var rech:RechargeItem=this.getChildByName("item"+i) as RechargeItem;
				rech.addEventListener(MouseEvent.CLICK,rechHandler);
				rech.idx=itemList[i];
			}
			item0.selected=true;
			gold=item0.idx;
			btn_recharge.addEventListener(MouseEvent.CLICK,clickHandler);
			btn_exchange.addEventListener(MouseEvent.CLICK,exchangeHandler);
			input.textField.restrict="0-9";
			input.textField.maxChars=8;
			tf_num.autoSize=TextFieldAutoSize.LEFT;
			input.defaultText="自定义购买其他金额";
			tf_num.visible=false;
			input.addEventListener(FocusEvent.FOCUS_IN,focusinHandler);
			input.addEventListener(FocusEvent.FOCUS_OUT,focusoutHandler);
			input.addEventListener(Event.CHANGE,changeHandler);
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
		}
		
		private function hideHandler(evt:Event):void
		{
			clear();
			item0.selected=true;
			gold=item0.idx;
			input.text="";
			tf_num.text="";
		}
		
		private function changeHandler(evt:Event):void
		{
			var num:Number=Number(input.text)*100;
			var ts:int=Math.floor(num/60);
			var sy:int=num-(60*ts);
			if(sy>0)
			{
				tf_num.text="充值量："+ts+"小时"+sy+"分钟";
			}
			else
			{
				tf_num.text="充值量："+ts+"小时";
			}
			
			tf_num.visible=true;
		}
		
		private function focusinHandler(evt:FocusEvent):void
		{
			clear();
		}
		
		private function focusoutHandler(evt:FocusEvent):void
		{
			if(input.text=="")
			{
				tf_num.visible=false;
			}
			else
			{
				tf_num.visible=true;
			}
		}

		private function exchangeHandler(evt:MouseEvent):void
		{
			if(input.text.length>0)
			{
				gold=Number(input.text);
			}
			ExternalInterface.call("ASTryRecharge",gold);
		}
		
		private function rechHandler(evt:MouseEvent):void
		{
			var rech:RechargeItem=evt.target as RechargeItem;
			gold=rech.idx;
			input.text="";
			tf_num.visible=false;
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASRechargeForYuanBao");
		}
		public function UCEneableRecharge(idx:int,isEnabled:Boolean):void
		{
			btn_exchange.enabled=isEnabled;
/*			var rech:RechargeItem=this.getChildByName("item"+idx) as RechargeItem;
			if(rech)
			{
				rech.BtnEneable(isEnabled);
			}*/
		}
		public function UCSetRechargeType(idx:int,dat:Object):void
		{
/*			var rech:RechargeItem=this.getChildByName("item"+idx) as RechargeItem;
			if(rech)
			{
				rech.updateData(idx,dat);
			}*/
		}
		//这个更新元宝，html的字符串
		public function UCupdateMoney(curYuanBao:int):void
		{
			var num:Number=curYuanBao/100;
			num=Math.floor(num/.1)*.1;
			txt_gold.text=num.toFixed(1);
		}
		
		private function clear():void
		{
			var i:int=0;
			for(i=0;i<3;i++)
			{
				var rech:RechargeItem=this.getChildByName("item"+i) as RechargeItem;
				rech.selected=false;
			}
		}
	}
	
}
