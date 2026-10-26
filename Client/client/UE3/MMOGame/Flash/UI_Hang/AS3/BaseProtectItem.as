package UI_Hang.AS3 {
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.TextInput;
	import flash.events.Event;
	
	public class BaseProtectItem extends UIComponent {

        public var type:int;
		public var ProtectType:int=0;//生命
		public var id:int;
		public var maxHp:int=0;
		public var maxMp:int=0;
		public var checkBox:CheckBox;
		public var txt_num:TextInput;
		public var txt_timer:TextInput;
		override protected function configUI():void
		{
			super.configUI();
			txt_num.addEventListener(Event.CHANGE,changeHandler);
			txt_timer.addEventListener(Event.CHANGE,timerHandler);
		}
		
		private function timerHandler(evt:Event):void
		{
			var num:int=int(txt_timer.text);
			if(num>255)
			{
				txt_timer.text=255+"";
			}
		}
		
		private function changeHandler(evt:Event):void
		{
			var num:int=int(txt_num.text);
			if(ProtectType==1)
			{
				if(num>maxMp)
				{
					txt_num.text=maxMp.toString();
				}
			}
			else
			{
				if(num>maxHp)
				{
					txt_num.text=maxHp.toString();
				}
			}
		}
        
		public function updateData(dat:ProtectData):void
		{
			
		}
		
		public function updateTxt(_maxHp:int,_maxMp:int):void
		{
			maxHp=_maxHp;
			maxMp=_maxMp;
			if(ProtectType==1)
			{
				txt_num.maxChars=maxMp.toString().length+1;
			}
			else
			{
				txt_num.maxChars=maxHp.toString().length+1;
			}
			
		}
		
		public function getProtectData():ProtectData
		{
			return null;

		}
		public function updateMenuData(dat:Array):void
		{
			

		}
	}
	
}
