package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.utils.Dictionary;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Events.ParamEvent;
	
	import UI_LoginWidget.AS3.RoleInfoData;
	import UI_LoginWidget.AS3.RoleSelectMC;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ButtonGroup;
	import scaleform.clik.motion.Tween;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.GameDispathcher;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class SelectRoleModule extends MyPanel {
		
		public var decBottom_mc:MovieClip;
		public var decTop_mc:MovieClip;
		public var decTop2_mc:MovieClip;
		//public var btn_Rotate_left:Button;
		//public var btn_Rotate_right:Button;
		public var role0:RoleSelectMC;
		public var role1:RoleSelectMC;
		public var role2:RoleSelectMC;
		public var role3:RoleSelectMC;
		public var btn_Delete:Button;
		public var ListRoleGrp:ButtonGroup;
		public var roleBtns:Dictionary;
		public const roleBtnCount:int=4; 
		//public var btn_mc:MovieClip;
		public var btn_Find:Button;
		public var btn_ReturnLogin:Button;
		public var shape:MovieClip;
		public var IsFirst:Boolean=false;
		public var btn_rote:Button;
		protected var offestX = 0;
		protected var offestY = 0;
		public var mc_roletimer:MovieClip;
		private var _title:String="";
		public function SelectRoleModule() {
			// constructor code
		}
		override protected function configUI():void
		{
			super.configUI();
			mc_roletimer.visible=false;
			role0=decTop2_mc.role0;
			role1=decTop2_mc.role1;
			role2=decTop2_mc.role2;
			role3=decTop2_mc.role3;
			decTop2_mc.btn_EnterGame.addEventListener(MouseEvent.CLICK,PushEnter );
			btn_ReturnLogin.addEventListener(MouseEvent.CLICK,RequestReturnLogin );
			btn_Delete.addEventListener(MouseEvent.CLICK,DeleteRole );
			btn_rote.addEventListener(MouseEvent.MOUSE_DOWN,downHandler);
			//btn_Rotate_left.addEventListener( MouseEvent.MOUSE_DOWN,RotateLeftPress );
			//btn_Rotate_right.addEventListener( MouseEvent.MOUSE_DOWN,RotateRightPress );
			//btn_Rotate_left.addEventListener(MouseEvent.CLICK,ListTurnUp );
			//btn_Rotate_right.addEventListener(MouseEvent.CLICK,ListTurnUp );
			btn_Find.addEventListener(MouseEvent.CLICK,findHandler);
			setGroupButton();
			role3.SetData(null);
			stageChangeHandler(null);
			//SetLeftGameTime("剩余时间：",10000000);
		}

		private function downHandler(evt:MouseEvent):void
		{
			btn_rote.addEventListener( MouseEvent.MOUSE_UP,DragOut );
			btn_rote.addEventListener( MouseEvent.MOUSE_MOVE,OnDrag );
			offestX = root.mouseX;
			offestY = root.mouseY;
		}
		
		private function OnDrag(e:MouseEvent):void
		{
			var offX = root.mouseX - offestX;
			var offY = root.mouseY - offestY;
			offestX = root.mouseX;
			offestY = root.mouseY;
			ExternalInterface.call("ASRoleMove",offX,offY);
		}
		
		private function DragOut(e:MouseEvent):void
		{
			btn_rote.removeEventListener( MouseEvent.MOUSE_UP,DragOut );
			btn_rote.removeEventListener( MouseEvent.MOUSE_MOVE,OnDrag );
		}
		
		public function UCSetSelectRole( selectIndex:int ):void
		{
			if( selectIndex < 0 || selectIndex >= roleBtnCount )
			 return;
			var i:int;
			for( i = 0 ; i < roleBtnCount;++i )
				roleBtns[i].selected = false; 
			roleBtns[selectIndex].selected = true; 
			
			//ListRoleGrp.setSelectedButtonByIndex(selectIndex);
			//ListRoleGrp.selectedIndex = selectIndex;
		}
		
		public function setGroupButton():void
		{
			ListRoleGrp = ButtonGroup.getGroup("ListRoleGrp",this);
			roleBtns = new Dictionary();
			var i:int;
			for( i = 0 ; i < roleBtnCount;i++ )
			{
				var btn:BaseSelectBtn=(decTop2_mc.getChildByName("role"+i) as RoleSelectMC).role.mc_head;
				ListRoleGrp.addButton(btn);
				btn.itemid=i;
				roleBtns[i]= btn;
			}
			ListRoleGrp.removeEventListener(Event.CHANGE, handleListRoleGrpChange, false);
			ListRoleGrp.addEventListener(Event.CHANGE, handleListRoleGrpChange, false, 0, true);
		}
		
		private function selectHandler(evt:Event):void
		{
			if(evt.type=="JumpCreateRole"){
				(root as LoginMoviePlayer).Jump2Create();
			}
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			decTop_mc.x=cavasWidth+10;
			decTop_mc.y=12;
			decTop2_mc.x=cavasWidth-347;
			decBottom_mc.x=(cavasWidth-decTop_mc.width)>>1;
			decBottom_mc.y=cavasHeight-decBottom_mc.height+4;
			btn_ReturnLogin.y=cavasHeight-65;
			btn_ReturnLogin.x=cavasWidth-btn_ReturnLogin.width-24;
			btn_Find.y=btn_ReturnLogin.y-btn_Find.height-10;
			btn_Delete.y=btn_Find.y-btn_Delete.height-10;
			btn_Find.x=btn_Delete.x=btn_ReturnLogin.x;
			btn_rote.width=cavasWidth;
			btn_rote.height=cavasHeight;
			btn_rote.x=0;
			btn_rote.y=0;
		}
		
		protected function handleListRoleGrpChange( evt:Event ):void
		{
			var button:BaseSelectBtn = ListRoleGrp.selectedButton as BaseSelectBtn;
			var i:int=0;
			if(button.parent){
				for (i = 0; i < roleBtnCount; i++) 
				{
					roleBtns[i].parent.update(false);
				}
				(button.parent as RoleListBtn).update(true);
			}
			ListRoleGrpChange( button.itemid );
		}
		
		public function ListRoleGrpChange( id:int ):void
		{
			ExternalInterface.call("ASSelectRole",id );
		}
		
		public function Effectshow():void
		{
             //ExternalInterface.call("EnterCharactorSelect");
			decTop2_mc.x=cavasWidth;
			ExternalInterface.call("ASCheckFirstOnSelect", this);
			if(IsFirst==true){
				CompleteTween();
			}else{
				shape=new (getDefinitionByName("SelectBack") as Class);
				shape.width=this.cavasWidth;
				shape.height=this.cavasHeight;
				this.addChild(shape);
				var tween:Tween=new Tween(1000,shape,{alpha:0},{onComplete:CompleteTween});
			}

		}
		
		public function CompleteTween():void
		{
			if(shape && this.contains(shape)){
				this.removeChild(shape);
				shape=null;
			}
			var l:int=cavasWidth-347;
			var tween:Tween=new Tween(300,decTop2_mc,{x:l});
		}
		
		public function Effecthide():void
		{
			if(shape && this.contains(shape)){
				this.removeChild(shape);
				shape=null;
			}
			var tween:Tween=new Tween(300,decTop2_mc,{x:cavasWidth});
		}
			
		
		public function UCUpdateRoleList( dataArray:Array ):void
		{
			if(dataArray.length>0){
				if(dataArray[0].HasRole){
					btn_Delete.enabled = true;
					decTop2_mc.btn_EnterGame.enabled = true;
				}
				else
				{
					btn_Delete.enabled = false;				
					decTop2_mc.btn_EnterGame.enabled = false;					
				}
			}
			else
			{
				btn_Delete.enabled = false;				
				decTop2_mc.btn_EnterGame.enabled = false;
			}
			var i:int=0;
			var l:int=dataArray.length;
			for(i=0;i<l;i++){
				var dat:RoleInfoData=dataArray[i];
				(decTop2_mc.getChildByName("role"+i) as RoleSelectMC).SetData(dat);
			}
			setGroupButton();
			//Effectshow();
		}

		public function findHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASRequestFindRole");
		}

		public function RequestReturnLogin(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASRequestReturnLogin" );
		}
		
		public function DeleteRole(evt:MouseEvent):void
		{
			ExternalInterface.call("ASDeleteRole");
		}

		public function RotateLeftPress(evt:MouseEvent):void
		{

			ExternalInterface.call("ASSelectTurnLeftPress");

		}

		public function RotateRightPress(evt:MouseEvent):void
		{

			ExternalInterface.call("ASSelectTurnRightPress");

		}

		public function ListTurnUp(evt:MouseEvent):void
		{
			ExternalInterface.call("ASTurnBtnUp");

		}
        //进入游戏
		public function PushEnter(evt:MouseEvent):void
		{
			ExternalInterface.call("ASEnterGame",ListRoleGrp.selectedIndex);
		}
		
		public function SetLeftGameTime( title:String,leftSec:int):void
		{
			if(mc_roletimer && mc_roletimer.txt_timer)
			{
				mc_roletimer.visible=true;
				mc_roletimer.txt_timer.text=title+timerConvert(leftSec);
			}
		}
		
		//时间转换成秒分时
		private function timerConvert(sceond:int):String
		{
			var h:int=Math.floor(sceond/3600);
			var sec:int=sceond-(3600*h);
			var m:int=0;
			if(sec>0)
			{
				m=Math.floor(sec/60);
			}
			if(h>0)
			{
				return h+"小时"+m+"分钟";
			}
			else
			{
				return m+"分钟";
			}
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
				dat.RoleID=i;
				dat.RoleName="法海"+i;
				dat.Sex=0;
				arr.push(dat);
			}
			UCUpdateRoleList(arr);
		}*/
	}
	
}
