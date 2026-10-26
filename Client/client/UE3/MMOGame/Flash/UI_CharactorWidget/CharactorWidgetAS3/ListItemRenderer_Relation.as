package UI_CharactorWidget.CharactorWidgetAS3
{

	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import flash.events.MouseEvent;


	public class ListItemRenderer_Relation extends ListItemTreeRenderer
	{

		public var mc_1st:ListItemRenderer_Relation1st;
		public var mc_2nd:ListItemRenderer_Relation2nd;
		public var itemState:Number = 0;
		public function ListItemRenderer_Relation()
		{
			if (this && this.updateDataCallBack == null)
			{
				this.updateDataCallBack = updateData;
			}
		}

		public function updateData(data:Object):void
		{
			mc_1st.updateData(data);
			mc_2nd.updateData(data);
		}
		
		
		override protected function setState(state:String):void {
			super.setState(state);
			var selectedFlag:String = "";
			var stateName:String = state;
			
			if(selected){	
			    selectedFlag="selected_";	
				mc_1st.titleName.textColor=0xEADBBF;
				mc_2nd.titleName.textColor=0xF3F0E8;
			}else{
				mc_1st.titleName.textColor=0xBFDAE8;
				mc_2nd.titleName.textColor=0xC2A98A;
			}
			
			if(stateName == "toggle")stateName =  "up";
			else if(stateName == "out")stateName =  "up";
			
			mc_1st.gotoAndPlay(selectedFlag +stateName);
			mc_2nd.gotoAndPlay(selectedFlag +stateName);

		}

	}

}