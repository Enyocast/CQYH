package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import flash.events.MouseEvent;
	import flash.events.Event;

	public class ProtectItem2 extends BaseProtectItem {
		
		public var dropMenu:DropdownMenu;
		override protected function configUI():void
		{
			super.configUI();
			txt_num.textField.restrict="0-9";
			txt_timer.maxChars=4;
			txt_timer.textField.restrict="0-9";
			dropMenu.addEventListener(ListEvent.ITEM_CLICK, onClickChange);
		}

		private function onClickChange(evt:ListEvent):void
		{
			var obj:Object=evt.itemData;
			if(obj && obj.index)
			{
				id=obj.index;
			}
		}

		override public function getProtectData():ProtectData
		{
			var dat:ProtectData=new ProtectData();
			dat.isSelect=this.checkBox.selected;
			dat.id=this.id;
			if(dat.isSelect && dat.id==0)
			{
				var arr:Array=dropMenu.dataProvider as Array;
				if(arr)
				{
					dat.id= arr[dropMenu.selectedIndex].index;
				}
			}
			dat.num=int(txt_num.text);
			dat.timer=int(txt_timer.text);
			if(dat.timer<1)
			{
				dat.timer=1;
				txt_timer.text=dat.timer.toString();
			}
			return dat;
		}
		
		override public function updateData(dat:ProtectData):void
		{
			checkBox.selected=dat.isSelect;
			txt_num.text=dat.num.toString();
			txt_timer.text=dat.timer.toString();
			itemid=dat.id;//绑定道具id
		}
		
		override public function updateMenuData(dat:Array):void
		{
			if(dat==null)
			{
				return;
			}
			 
			var i:int=0;
			var l:int=dat.length;
			var index:int;
			for(i=0;i<l;i++)
			{
				var obj:ItemData=dat[i];
				if(obj.index==id)
				{
					index=i;
					break;
				}
			}
			if(dat.length>1){
				dropMenu.menuRowCount=4;
			}
			var dp:DataProvider=new  DataProvider(dat);
			dropMenu.dataProvider=dp;
			dropMenu.invalidateData();
            dropMenu.selectedIndex = index;
            dropMenu.validateNow();
		}
		
		public function clear():void
		{
			dropMenu.close();
		}
	}
	
}
