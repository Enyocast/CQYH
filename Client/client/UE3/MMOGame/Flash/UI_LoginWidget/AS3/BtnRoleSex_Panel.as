package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.RadioButton;
    import scaleform.clik.controls.ButtonGroup;
    import flash.events.Event;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	
	public class BtnRoleSex_Panel extends UIComponent {
		
		public var male:RadioButton;
        public var female:RadioButton;
        public var CreateSexGrp:ButtonGroup;
        
		override protected function configUI():void
		{
			super.configUI();
			CreateSexGrp = ButtonGroup.getGroup("CreateSexGrp",this);
            CreateSexGrp.addEventListener(Event.CHANGE, handleCreateSexGrpChange, false, 0, true);
		}

		public function setCreateSexGrp(sex:int):void
		{
			if(sex==1) //男
			{
				male.selected =true;
			}
			else
			{
				female.selected =true;	
			}
		}
		
		public function setCreateSexGrpEx(sex:int):void
		{
			if(sex==1) //男
			{
				male.selected =true;
				male.enabled = true;
				female.enabled = false;
			}
			else
			{
				female.selected =true;	
				male.enabled = false;
				female.enabled = true;				
			}
		}
		
		public function handleCreateSexGrpChange(e:Event):void
		{
			ExternalInterface.call( "CreateSexChanged", CreateSexGrp.selectedIndex );
		}
	}
	
}
