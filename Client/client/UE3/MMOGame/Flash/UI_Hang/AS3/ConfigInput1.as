package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	
	public class ConfigInput1 extends UIComponent {
		
		public var btn_default:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_apply:Button;
		public var bar_item1:BarKey;
		public var bar_item2:BarKey;
		public var bar_item3:BarKey;
		public var bar_item4:BarKey;
		public var bar_item5:BarKey;
		public var bar_item6:BarKey;
		public var bar_item7:BarKey;
		public var bar_item8:BarKey;
		public var bar_item9:BarKey;
		public var bar_item10:BarKey;
		public var bar_item11:BarKey;
		public var bar_item12:BarKey;

		public var tf_tips:TextField;
		public var tf_warning:TextField;
		public var mc_title:MovieClip;
		
		override protected function configUI():void
		{
			super.configUI();
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			var i:int=1;
			for(i=1;i<13;i++){
				var bar:BarKey=(this.getChildByName("bar_item"+i) as BarKey);
				bar.itemid=i;
				bar.removeEvent();
				bar.addEventListener(MouseEvent.CLICK,clickBarItem);
			}
			tf_warning.text = "";
			this.mc_title.visible=false;
		}
		
		private function clickBarItem(evt:MouseEvent):void
		{
			var bar:BarKey=evt.target as BarKey;
			bar.selected=true;
			clear(bar.itemid);
			ExternalInterface.call("ASMdfFunction", bar.type_id);
		}

		public function ShowWarning(warning:String)
		{
			tf_warning.text = warning;
			this.mc_title.visible=true;
			if(warning==""){
				mc_title.visible=false;
			}
		}		
		public function OnDefault(evt:MouseEvent):void
		{
			ExternalInterface.call("ASDefaultInput", 1);
			tf_warning.text="";
			this.mc_title.visible=false;
			clear(0);
		}
		public function OnOK(evt:MouseEvent):void
		{
			OnApply(null);
			OnCancel(null);	
		}
		public function OnCancel(evt:MouseEvent):void
		{
			clear(0);
			ExternalInterface.call( "ASOnPanelClose" , "Assist");
			tf_warning.text ="";
			this.mc_title.visible=false;
		}
		public function OnApply(evt:MouseEvent):void
		{
			var dat:ConfigGameData = new ConfigGameData();
			dat.input1_enable = true;
			tf_warning.text ="";
			this.mc_title.visible=false;
			clear(0);
			ExternalInterface.call("ASApplyGameConfig", dat);
		}
		public function setConfigData(dat:ConfigGameData):void
		{			
			if (!dat.input1_enable || dat.SlotKeyList.length==0)
				return;
			var i:int=1;
			for(i=1;i<13;i++){
				var bar:BarKey=(this.getChildByName("bar_item"+i) as BarKey);
				var obj:Object=dat.SlotKeyList[i-1];
				bar.update(obj.KeyName,obj.ComKeyName,obj.KeyEnum);
			}
			ShowWarning("");
		}
		public function clear(type:int):void
		{
			var i:int=1;
			for (i = 1; i < 13; i++) 
			{
				var bar:BarKey=this.getChildByName("bar_item"+i) as BarKey;
				if(bar && i==type){
					bar.show();
				}else{
					bar.clear();
				}
			}
			
		}
	}
	
}
