package UI_Hang.AS3 {
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	
	public class InputKeyItem extends ListItemTreeRenderer {
		
		public var item_type:int;
		public var item_text:TextField;
		public var item_button:TextField;
		override protected function configUI():void
		{
			super.configUI();
			
			setUpdateDataCallBack(UpdateData);
			
			item_button.addEventListener(MouseEvent.CLICK,OnClick);
			
			item_type = -1;
		}
		
		public function UpdateData(data:Object):void
		{
			if (data)
			{
				item_type = data.ktype;
				item_text.text = data.kdesc;
				item_button.text = data.kkey;
				if(this.selected==true){
					item_button.textColor=0xFBD671;
				}else{
					item_button.textColor=0xFFFFFF;
				}
				visible = true;
			}
			else
			{
				visible = false;
			}
		}
		public function OnClick(evt:MouseEvent):void
		{ 
			ExternalInterface.call("ASMdfFunction", item_type);
		}
	}
	
}
