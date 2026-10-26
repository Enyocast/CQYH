package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.Common.Events.ParamEvent;
	
	import UI_LoginWidget.AS3.RoleDelBubble;
	import UI_LoginWidget.AS3.RoleInfoData;
	import UI_LoginWidget.AS3.RoleListBtn;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ComponentEvent;

	public class RoleSelectMC extends UIComponent {
		
		public var role:RoleListBtn;
		//public var wait_del_0:RoleDelBubble;
		public var btn_Create0:Button;
		public function RoleSelectMC() {
/*			role.doubleClickEnabled = true;
			role.addEventListener(MouseEvent.DOUBLE_CLICK,DoubleClick);*/
			//wait_del_0.visible=false;
			btn_Create0.addEventListener(MouseEvent.CLICK,RequestJump2CreateRole);
		}
		
		public function SetData( roleData:RoleInfoData ):void
		{
			if (roleData != null )
			{	
				role.visible= true;
				role.SetRoleBtn(roleData);
				btn_Create0.visible=!role.visible;
				//wait_del_0.SetOverTime(roleData.OverTime, roleData.RoleID);
				
			}else{
					role.visible=false;
					btn_Create0.visible=true;
					//wait_del_0.SetOverTime(0,0);
				}

		}
		
		
/*		public function DoubleClick(evt:MouseEvent):void
		{
			ExternalInterface.call("DirectSelectRole",evt.target.itemid  );
		}*/
		
		public function RequestJump2CreateRole(evt:MouseEvent):void
		{//进入新建角色界面
		    this.dispatchEvent(new Event("JumpCreateRole"));
			ExternalInterface.call( "ASRequestJump2CreateRole");
			
		}
	}
	
}
