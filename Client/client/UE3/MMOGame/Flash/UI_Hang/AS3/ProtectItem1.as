package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.TextInput;
	import flash.events.Event;
	
	
	public class ProtectItem1 extends BaseProtectItem {
		
		override protected function configUI():void
		{
			super.configUI();
			txt_num.textField.restrict="0-9";
			txt_timer.maxChars=4;
			txt_timer.textField.restrict="0-9";
		}

		override public function getProtectData():ProtectData
		{
			var dat:ProtectData=new ProtectData();
			dat.id=this.id;
			dat.isSelect=this.checkBox.selected;
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
			id=dat.id;//绑定道具id
		}
		public function setCheckBoxTxt(bl:Boolean=false):void
		{
			if(bl)
			{
				checkBox.label="魔法药";
			}
			else
			{
				checkBox.label="体力药";
			}
		}
	}
	
}
