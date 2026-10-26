package UI_LoginWidget.AS3 {
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.utils.Dictionary;
	import scaleform.clik.controls.RadioButton;
	
	public class FindPanel extends MyPanel {

        public var role_0:FindRole;
		public var role_1:FindRole;
		public var role_2:FindRole;
		public var role_3:FindRole;
		public var btn_find:Button;
		public var btn_del:Button;
		public var ListBtn:Dictionary;
		private var index:int=-1;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			ListBtn=new Dictionary();
			this.SetWindowTitle("找回角色");
			hide();
			btn_find.addEventListener(MouseEvent.CLICK,findHandler);
			btn_del.addEventListener(MouseEvent.CLICK,delHandler);
		}
		
		
		private function hide():void
		{
			var i:int=0;
			for(i=0;i<4;i++){
				var role:FindRole=this.getChildByName("role_"+i) as FindRole;
				ListBtn[i]=role;
				role.addEventListener(MouseEvent.CLICK,clickHandler);
				role.itemid=i;
				role.visible=false;
			}
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			var btn:FindRole=evt.target as FindRole;
			index=btn.RoleID;
		}
		
		public function UCUpdateDelRoleList( dat:Array ):void
		{
			if(dat==null){
				return;
			}
			var i:int=0;
			var l:int=dat.length;
			if(l>0){
			    for(i=0;i<4;i++){
				   var info:RoleInfoData=dat[i];
				   var role:FindRole=this.getChildByName("role_"+i) as FindRole;
				   if(dat){
					   role.updateData(info);
					   if(i == 0)
					   {
						   index=role.RoleID;
						   role.selected = true;
					   }
				   }else{
					   role.visible=false;
				   }
		        }
			}else{
				hide();
			}

		}
		
		private function findHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASRequestFindRoleID",index);
		}
		
		private function delHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASRequestDelectRole",index);
		}
		
/*		private function testData():void
		{
			var arr:Array=new Array();
			var i:int=0;
			for(i=0;i<4;i++){
				var dat:RoleInfoData=new RoleInfoData();
				dat.HasRole=true;
				dat.Career=i;
				dat.CareerName="刺客"+i;
				dat.Level=i+"";
				dat.OverTime=0;
				dat.RoleID=i+5;
				dat.RoleName="法海"+i;
				dat.Sex=0;
				arr.push(dat);
			}
			trace("++++++++++++++++++UCUpdateDelRoleList+++++++++++++++++++++++++",arr);
			UCUpdateDelRoleList(arr);
		}*/

	}
	
}
