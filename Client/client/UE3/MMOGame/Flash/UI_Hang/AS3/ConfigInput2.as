package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import flash.text.TextField;
	
	
	public class ConfigInput2 extends UIComponent {
		
		public var btn_default:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_apply:Button;
		public var tf_warning:TextField;
		public var mc_title:MovieClip;

		public var input_list:ScrollingList;
        public var team:InputKeyItem;
		override protected function configUI():void
		{
			super.configUI();
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			input_list.addEventListener(ListEvent.ITEM_CLICK,clickHandler);
/*
			var dat:ConfigGameData = new ConfigGameData()  ;
			dat.input2_enable = true;
			for(var i:int=0;i<20;i++){
			var obj:InputKeyItemData = new InputKeyItemData();
			obj.ktype = 1;
			obj.kkey = "ssss"+i;
			obj.kdesc = "kkkk"+i;
            obj.isSelect=false;
			dat.KeyList.push(obj);
			}

			FillToUI(dat);*/
		}
		public function ShowWarning(warning:String):void
		{
			tf_warning.text = warning;
			this.mc_title.visible=true;
			if(warning==""){
				mc_title.visible=false;
			}
		}			
		public function clickHandler(e:ListEvent):void
		{
			var list:ScrollingList = e.target as ScrollingList;
			if (list != null){
				list.invalidateData();
			}
			
		}
		public function OnDefault(evt:MouseEvent):void
		{
			ExternalInterface.call("ASDefaultInput", 2);
		}
		public function OnOK(evt:MouseEvent):void
		{
			OnApply(null);
			OnCancel(null);
		}
		public function OnCancel(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASOnPanelClose" , "Assist");
		}
		public function OnApply(evt:MouseEvent):void
		{
			var dat:ConfigGameData = new ConfigGameData();
			dat.input2_enable = true;
			ExternalInterface.call("ASApplyGameConfig", dat);
		}
		public function setConfigData(dat:ConfigGameData):void
		{
			if (! dat.input2_enable)
				return;
			for (var i:int = 0; i < dat.KeyList.length; i++)
			{
				var itd:InputKeyItemData = dat.KeyList[i];
				itd.index = i;
				itd.type = 0;
				itd.deepth = 0;
				itd.visible = true;
				itd.label = "";
			}
			input_list.dataProvider = new TreeDataProvider(dat.KeyList);
			input_list.validateNow();
			input_list.invalidateData();
			ShowWarning("");
		}
	}
	
}
