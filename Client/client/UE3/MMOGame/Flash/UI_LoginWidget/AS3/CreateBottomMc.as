package UI_LoginWidget.AS3 {
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.core.UIComponent;
	
	public class CreateBottomMc extends UIComponent {
		
		public var btn_ReturnList:Button;
		public var btn_SaveRole:Button;
        public var mc_sex:BtnRoleSex_Panel;
		public var role0:RadioButton;
		public var role1:RadioButton;
		public var role2:RadioButton;
		public var role3:RadioButton;
		public var role4:RadioButton;
		protected var _selectedRoleIndex:int;
		protected var _curState:int = -1;
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function SetRoleEnable(roleIndex:int, enable:Boolean):void
		{
			if(roleIndex==0){
				role0.enabled = enable;
			}
			else if(roleIndex==1){
				role3.enabled = enable;
			}
			else if(roleIndex==2){
				role1.enabled = enable;
			}
			else if(roleIndex==3){
				role2.enabled = enable;
			}else if(roleIndex==4){
				role4.enabled=enable;
			}
		}
		
		public function selectedRole(roleIndex:int):void
		{
			_selectedRoleIndex = roleIndex;
		}
		

	}
	
}
