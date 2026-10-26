package UI_LoginWidget.AS3 {
	
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.utils.Dictionary;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Events.ParamEvent;
	
	import UI_LoginWidget.AS3.AppearanceModule.OperationPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ButtonGroup;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.motion.Tween;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.core.CLIK;
	import scaleform.clik.managers.FocusHandler;
	import ActionScript3.GameDispathcher;
	
	public class CreateModule extends MyPanel {
		
		public var decBottom_mc:MovieClip;
		public var decTop_mc:MovieClip;
		public var input_mc:InputNameMC;

		public var mc_RoleSex:BtnRoleSex_Panel;
		public var mc_Description:CreateModule_Description;
		
		public var createMc:CreateBottomMc;
		public var roleBtns:Dictionary;
		public const roleBtnCount:int=4;
		public var CreateRoleGrp:ButtonGroup;
		public var career:int;
		private var shape:MovieClip;
		public var IsFirst:Boolean=false;
		
		public var appearance_mc:OperationPanel;
		private var _curState:int = -1;
		
		private static const APPEARANCE_ACTIVATED:Boolean = true;//true || false;
		
		public var btn_rote:Button;
		protected var offestX = 0;
		protected var offestY = 0;
		
		public function CreateModule() {
			// constructor code
		}
		override protected function configUI():void
		{
			super.configUI();
			//ExternalInterface.call("ASRegisterCreateModule", this);
			mc_RoleSex=createMc.mc_sex;
			createMc.btn_ReturnList.addEventListener(MouseEvent.CLICK,ClickReturn);
			createMc.btn_SaveRole.addEventListener(MouseEvent.CLICK,ClickCreate );
			CreateRoleGrp = ButtonGroup.getGroup("CreateRoleGrp",createMc);
			CreateRoleGrp.addEventListener(Event.CHANGE, handleCreateGrpChange, false, 0, true);
			roleBtns=new Dictionary();
			var i:int;
			//for( i = 0 ; i < roleBtnCount;i++ )
				roleBtns[0] = createMc.getChildByName( "role"+0 ); 
				roleBtns[1] = createMc.getChildByName( "role"+3 ); 
				roleBtns[2] = createMc.getChildByName( "role"+1 ); 
				roleBtns[3] = createMc.getChildByName( "role"+2 ); 
				roleBtns[4] = createMc.getChildByName( "role"+4 ); 
			if(APPEARANCE_ACTIVATED)
			{
				input_mc=appearance_mc.input_mc;
				appearance_mc.btn_ReturnRole.addEventListener(MouseEvent.CLICK,ClickReturn);//update state
				appearance_mc.btn_create.addEventListener(MouseEvent.CLICK,ClickCreate );//set career
				//switchState(ConstantsDefine.STATE_SELECT_CAREER);
				//test appearance
			//	UCSetAppearanceData(null);
			//	switchState(ConstantsDefine.STATE_SELECT_APPEARANCE);
			}
			else
			{
				appearance_mc.visible = false;
			}
			btn_rote.addEventListener(MouseEvent.MOUSE_DOWN,downHandler);
			stageChangeHandler(null);
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
			ExternalInterface.call("ASRoleMove_Create",offX,offY);
		}
		
		private function DragOut(e:MouseEvent):void
		{
			btn_rote.removeEventListener( MouseEvent.MOUSE_UP,DragOut );
			btn_rote.removeEventListener( MouseEvent.MOUSE_MOVE,OnDrag );
		}
		public function switchState(state:int):void
		{
			_curState = state;
			//createMc.updataState(_curState);//invisible now, no need update any more.
		//	mc_RoleSex.visible = mc_Description.visible = (_curState == ConstantsDefine.STATE_SELECT_CAREER);
			createMc.visible = (_curState == ConstantsDefine.STATE_SELECT_CAREER)
			appearance_mc.visible = (_curState == ConstantsDefine.STATE_SELECT_APPEARANCE);
		}
		
		public function SetRoleEnable(roleIndex:int, enable:Boolean):void
		{
			createMc.SetRoleEnable(roleIndex, enable);
		}
		
		public function ShowCreateModule(id:int):void
		{
			switchState(id);
		}
		
		//创建角色
		public function ClickCreate(e:MouseEvent):void
		{
			if(APPEARANCE_ACTIVATED){
				if(_curState == ConstantsDefine.STATE_SELECT_CAREER)
				{
					if(input_mc){
						input_mc.reset();
					}
					ExternalInterface.call( "ASCallUCGetAppearanceData");
					//test
					//UCSetAppearanceData(null);
					//switchState(ConstantsDefine.STATE_SELECT_APPEARANCE);
				}
				else if(_curState == ConstantsDefine.STATE_SELECT_APPEARANCE)
				{
					career=0;
				}
			}
			else
			{
				var createName:String = input_mc.input_Name.text;
				//var sex:int=mc_RoleSex.CreateSexGrp.selectedIndex;
				ExternalInterface.call( "CreateRole", createName );
				career=0;
			}
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			decTop_mc.x=(cavasWidth-decTop_mc.width)>>1;
			decBottom_mc.x=cavasWidth+10;
			decBottom_mc.y=cavasHeight;
			
			btn_rote.width=cavasWidth;
			btn_rote.height=cavasHeight;
			btn_rote.x=0;
			btn_rote.y=0;

			createMc.x=cavasWidth-createMc.width-40;
			appearance_mc.x = cavasWidth - appearance_mc.width - 30;
		}
		
		public function ClickReturn(e:MouseEvent):void
		{
			if(APPEARANCE_ACTIVATED){
				if(_curState == ConstantsDefine.STATE_SELECT_CAREER){
					Effecthide();
					ExternalInterface.call( "ASRequestReturnRoleList" );
				}else if(_curState == ConstantsDefine.STATE_SELECT_APPEARANCE){
					//switchState(ConstantsDefine.STATE_SELECT_CAREER);
					ExternalInterface.call( "ASReturnCreatePanel" );
				}
			}else{
				Effecthide();
				ExternalInterface.call( "ASRequestReturnRoleList" );
			}
		}
		
		protected function handleCreateGrpChange( event:Event ):void
		{
			var button:RadioButton = CreateRoleGrp.selectedButton as RadioButton;
			career=button.itemid;
			CreateGrpChange( button.itemid );
		}
		
		public function CreateGrpChange( roleCareer:int ):void
		{//选中了哪个角色
			ExternalInterface.call( "CreateRoleChanged", roleCareer );
			mc_Description.SetCareer( roleCareer );
			
			createMc.selectedRole(roleCareer);
		}
		
		public function ResetFocus():void
		{
			if(input_mc && input_mc.input_Name)
			{
				FocusHandler.getInstance().setFocus(input_mc.input_Name.textField);
			    input_mc.input_Name.textField.setSelection(200,200);
			    //changeFocus();
			}
		}
		
		public function Effectshow():void
		{
			createMc.x=cavasWidth;
			mc_Description.x=-mc_Description.width;
			ExternalInterface.call("ASCheckFirstOnCreate", this);
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
			var l:int=cavasWidth-createMc.width-40;
			var tween:Tween=new Tween(300,createMc,{x:l});
			var tween1:Tween=new Tween(300,mc_Description,{x:36});
		}
		public function Effecthide():void
		{
			ExternalInterface.call( "CreateRoleCancel" );
			if(shape && this.contains(shape)){
				this.removeChild(shape);
				shape=null;
			}
			var tween:Tween=new Tween(300,createMc,{x:cavasWidth});
			var tween1:Tween=new Tween(300,mc_Description,{x:-mc_Description.width});
			career=0;
		}

		public function UCSetRoleName(roleName:String):void
		{
			input_mc.UCSetRoleName(roleName);
		}
		public function UCUpdateInput(bSaveRole:Boolean, strScript:String):void
		{
			appearance_mc.btn_create.enabled=bSaveRole;
			input_mc.UCUpdateInput(bSaveRole, strScript);
		}
		public function UCSetCreateInfo(sex:int , classID:int)
		{
			if(classID>=0 && classID<roleBtnCount){
				roleBtns[classID].selected = true; 
			}
			mc_RoleSex.setCreateSexGrp(sex);
		}		
		public function UCSetCreateSexGrpEx(sex:int , isEx:Boolean)
		{
			if(isEx)
			{
				mc_RoleSex.setCreateSexGrpEx(sex);
			}
			else{
				mc_RoleSex.setCreateSexGrp(sex);
			}
		}
		
		//-------------interface for UC set appearance data
		public function UCSetAppearanceData(data:Array):void
		{
			appearance_mc.UCSetAppearanceData(data);
		}
	}
	
}
