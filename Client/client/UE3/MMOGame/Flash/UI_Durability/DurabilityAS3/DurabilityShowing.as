package UI_Durability.DurabilityAS3
{
	import scaleform.clik.core.UIComponent;
	import UI_Durability.DurabilityAS3.DurabilityComponent;
	import flash.external.ExternalInterface;
	import flash.display.DisplayObject;
	
	public class DurabilityShowing extends UIComponent 
	{
		public var DurabilityComponentMc0:DurabilityComponent;
		public var DurabilityComponentMc1:DurabilityComponent;
		public var DurabilityComponentMc2:DurabilityComponent;
		public var DurabilityComponentMc3:DurabilityComponent;
		public var DurabilityComponentMc4:DurabilityComponent;
		public var DurabilityComponentMc5:DurabilityComponent;
		public var DurabilityComponentMc6:DurabilityComponent;
		public var DurabilityComponentMc7:DurabilityComponent;
		public var DurabilityComponentMc8:DurabilityComponent;
		public var DurabilityComponentMc10:DurabilityComponent;
		public var DurabilityComponentMc11:DurabilityComponent;
		public var DurabilityComponentMc12:DurabilityComponent;

		override protected function configUI():void 
		{
			super.configUI();
		}

		//==========================================================================================
		public function InitAllComponents():void
		{
			SetAllComponents( 0 );
		}
		//==========================================================================================
		public function SetComponentState( componentID:int, curState:int ):void
		{
			var setObj:DurabilityComponent = null;
			var dis:DisplayObject=this.getChildByName("DurabilityComponentMc"+componentID);
			if(dis)
			{
				setObj =dis as DurabilityComponent;
			}
			if( setObj == null ){
				return;
			}
			setObj.ComponentState = curState;
			//同步动画
			setObj.RePlayCurAnimi();
			//ResetAllComponentsAnim();
		}
		//==========================================================================================
		private function SetAllComponents( testValue:int ):void
		{
			SetComponentState( 0, testValue );
			SetComponentState( 1, testValue );
			SetComponentState( 2, testValue );
			SetComponentState( 3, testValue );
			SetComponentState( 4, testValue );
			SetComponentState( 5, testValue );
			SetComponentState( 6, testValue );
			SetComponentState( 7, testValue );
			SetComponentState( 8, testValue );
			SetComponentState( 10, testValue );
			SetComponentState( 11, testValue );
			SetComponentState( 12, testValue );
		}
		//
		//==========================================================================================
/*		private function ResetAllComponentsAnim():void
		{
			DurabilityComponentMc0.RePlayCurAnimi();
			DurabilityComponentMc1.RePlayCurAnimi();
			DurabilityComponentMc2.RePlayCurAnimi();
			DurabilityComponentMc3.RePlayCurAnimi();
			DurabilityComponentMc4.RePlayCurAnimi();
			DurabilityComponentMc5.RePlayCurAnimi();
			DurabilityComponentMc6.RePlayCurAnimi();
			DurabilityComponentMc7.RePlayCurAnimi();
			DurabilityComponentMc8.RePlayCurAnimi();
			DurabilityComponentMc10.RePlayCurAnimi();
			DurabilityComponentMc11.RePlayCurAnimi();
			DurabilityComponentMc12.RePlayCurAnimi();
		}*/
	}
}

