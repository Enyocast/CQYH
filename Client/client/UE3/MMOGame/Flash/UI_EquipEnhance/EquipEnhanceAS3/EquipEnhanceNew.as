package UI_EquipEnhance.EquipEnhanceAS3
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;

	import UI_EquipEnhance.EquipEnhanceAS3.EquipSlotIconData;

	public class EquipEnhanceNew extends MyPanel
	{
		public var showPanel_mc:EnhanceShowPanel;
		//public var btn_close:Button;
		//public var MyWindowsFrame_mc:MyWindowsFrame;
		
		override protected function configUI():void
		{
			super.configUI();
			MyWindowsFrame_mc.ctrlBg_mc.visible = false;
			if(showPanel_mc)
			{
				//showPanel_mc.configUI();
			}
			//btn_close.addEventListener( ButtonEvent.CLICK, Close );
			//SetWindowTitle("强化");
			ExternalInterface.call( "ASRegisterEquipSlotEnhance", this );
		}
		
	
		public function UpdateDetailPanel( tData:Object )
		{
			showPanel_mc.UpdateDetailPanel( tData );
		}
	
		public function UpdateSummaryPanel( tData:Object )
		{
			if ( tData is EquipSlotIconData )
			{
				var ParamData:EquipSlotIconData = tData as EquipSlotIconData;
				SetWindowTitle(ParamData.WindowTitle);
				showPanel_mc.UpdateSummaryPanel( ParamData );
			}
		}
	
		public function UpdateTips( tData:Object )
		{
		
		}
	
		public function UpdateActiveTips( tData:Object )
		{
		
		}
	}
	
	
}