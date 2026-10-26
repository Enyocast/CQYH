
package ActionScript3.Slot {

	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import ActionScript3.Slot.MySlotData;

	public class MySlotRender extends UIComponent
	{		
		public function Init():void {}
		public function UnInit():void {}
		public function SetDataObj( SlotData:MySlotData ):void {}
		public function SetCD(leftMiniSec:int , tolMiniSec:int):void{}
		public function CancelCD():void{SetCD(0,0);}
		public function UpdateData():void {}
		public function UpdateLightData():void {}
		
		override protected function configUI():void
		{
			super.configUI();
			Init();
			this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
		}
		
		public function onRmoved(e:Event)
		{
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			UnInit();
		}
		
		
	};
}