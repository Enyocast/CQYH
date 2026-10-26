package ActionScript3.fla
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import ActionScript3.MyItemSlot;
	import ActionScript3.MyItemSlotShow;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Label;
	import ActionScript3.Widget.CharactorPanel;
	import ActionScript3.MyPanel;
	import ActionScript3.MyTooltips;
	import ActionScript3.Widget.SystemPanel;
	import ActionScript3.MyShopMessage;
	import ActionScript3.Widget.TargetInfo;
	import ActionScript3.Widget.ActionBar;
	import ActionScript3.Widget.FBSelectPanel;
	import ActionScript3.Widget.FBSummaryPanel;
	import ActionScript3.Widget.FBAwardPanel;
	import ActionScript3.Widget.FBBattleComfirmPanel;
	import ActionScript3.Widget.ChatOptionPanel;
	//import ActionScript3.Widget.OptionPanel;
	import ActionScript3.Widget.TeamPanel;
	import ActionScript3.Widget.WareHousePanel;
	import ActionScript3.Widget.ChatPanel;
	import ActionScript3.Widget.QuestPanel;
	import ActionScript3.MyTaskTracerWidget;
	import ActionScript3.Widget.EquipEnhancePanel;
	import ActionScript3.Widget.BagPanel;
	import ActionScript3.Widget.MapPanel;
	import ActionScript3.Widget.MySkillPanel
	//import ActionScript3.Widget.MessageDeathWidget;
		
	//import ActionScript3.Widget.ProgressBarWidget;
	//import ActionScript3.Widget.ProgressBarStrengthWidget;
	//import ActionScript3.Widget.ProgressBarQTEWidget;
	//import ActionScript3.Widget.BuffPanel;
	
	//import ActionScript3.Widget.HintLevelUpWidget;
	//import ActionScript3.Widget.HintSceneWidget;

	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	//import flash.utils.tim
	import ActionScript3.DropIcon;
	import ActionScript3.Widget.ContactWidget;
	import ActionScript3.Widget.ContactLevel;
	import ActionScript3.Widget.ContactListWidget;
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyActivePanel;
	import ActionScript3.Widget.MyRClickMenu;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Widget.MyDamageLevel;
        import scaleform.clik.controls.Button;
        import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	import ActionScript3.Widget.FriendChatHintPanel;
	import ActionScript3.Widget.ShopPanel;

	public class GameHud extends UIComponent
	{
		public var prev:Number = 0;
		public var newtime:Number = 0;
		public var frametime:Number = 0;
		public var bMouseOnUI:Boolean = false;
		public var QuestFollow_mc:Label;
		public var myinfo_panel_mc:CharactorPanel;
		public var Dialog_mc:MovieClip;
		public var tooltips_mc:MyTooltips;
		//public var tooltips_mc_new:MyTooltips;
		public var MessageInfo_mc:MyPanel;
		//public var system_mc:SystemPanel;
		public var NPCShop_mc:ShopPanel;
		public var WarningTrap_mc:MyPanel;
		public var ShopMsg_mc:MyShopMessage;
		public var mouse_mc:MovieClip;
		public var TeamMate:MyPanel;
		public var PlayerInfo_mc:MyPanel;
		public var enemyinfo_mc:TargetInfo;
		public var Skillbar_mc:ActionBar;
		public var fb_mc:FBSelectPanel;
		public var FbSummary_mc:FBSummaryPanel;
		public var FbAward_mc:FBAwardPanel;
		public var FbComfirm_mc:FBBattleComfirmPanel;
		public var ChatOption:ChatOptionPanel;
		//public var systemVideo_mc:OptionPanel;
		public var MsgSceneHint_mc:MyPanel;
		public var TransducerInfo_mc:MyPanel;
		public var Team_mc:TeamPanel;
		public var Warehouse_mc:WareHousePanel;
		public var DropIcon_mc:MyIconConponent;
		public var MenuIcon:MovieClip;
		public var Hint_mc:MovieClip;
		public var PackagePanel_mc:BagPanel;
		public var EquipEnhance_mc:EquipEnhancePanel;
		public var Combo_mc:MovieClip;
		public var Minimap_mc:MyPanel;
		//public var MessageDeath:MessageDeathWidget;

//		public var AbilityCastbarEnerge_mc:ProgressBarWidget;
//		public var AbilityCastbarStrength_mc:ProgressBarStrengthWidget;
//		public var QteTopHint_mc:ProgressBarQTEWidget;
//		public var BuffPanel_mc:BuffPanel;
//		
//		public var HintScene:HintSceneWidget;
//		public var HintLevelUp:HintLevelUpWidget;
						

		public var DropItemTips_mc:MovieClip;
		public var Map_mc:MapPanel;
		public var RClickMenu_mc:MyRClickMenu;
		public var RClickMenuChild_mc:MyRClickMenu;
		public var SceneHint:MyPanel;
		public var ChatPanel_mc:ChatPanel;
		
		//public var mouse_mc:mouse;
		public var UnlockMsgBoxZone_mc:MyPanel;
		//public var SkillPanel_mc:MySkillPanel;
		public var Contactlevel:ContactLevel;
		public var ContactWidget:ContactListWidget;
		public var durationAlert:MyPanel;
		public var PickTip:Button;
		public var DamageNumberLevel:MyDamageLevel;
		public var FriendChatHintPanel_mc:FriendChatHintPanel;
		
		var inited:Boolean = false;
		
		function initStage()
		{
			
			//trace(Hint_mc);
			
			if( Hint_mc )
				Hint_mc.visible = false;
			if( DropIcon_mc)
			DropIcon_mc.visible = false;
			
			//DropSkill_mc.visible = false;
			//Quest_mc.visible = false;
			//if( Dialog_mc)
			//Dialog_mc.visible = false;
			if( tooltips_mc )
			{
				tooltips_mc.visible = false;
				tooltips_mc.mouseEnabled = false;
				tooltips_mc.mouseChildren = false;
			}
			
			if( MessageInfo_mc)
			MessageInfo_mc.visible = false;
			//if( system_mc)
			//system_mc.visible = false;
			if( WarningTrap_mc )
			WarningTrap_mc.visible = false;
			//if( systemVideo_mc)
			//systemVideo_mc.visible = false;
			//if( NPCShop_mc)
			//NPCShop_mc.visible = false;

			
			if( Team_mc)
				Team_mc.visible = false;
			if( Warehouse_mc)
				Warehouse_mc.visible = false;
			if( Map_mc)
			Map_mc.visible = false;
			if( ShopMsg_mc)
			ShopMsg_mc.visible = false;
			if( TransducerInfo_mc)
			TransducerInfo_mc.visible=false;
			if( MenuIcon )
			MenuIcon.visible = false;
			//if( Dialog_mc )
			//Dialog_mc.visible = false;
//			if( MessageDeath )
//				MessageDeath.visible = false;
//			if( AbilityCastbarEnerge_mc )
//				AbilityCastbarEnerge_mc.visible = false;
//			if( AbilityCastbarStrength_mc )
//				AbilityCastbarStrength_mc.visible = false;
//			if( QteTopHint_mc )
//				QteTopHint_mc.visible = false;
//			if( BuffPanel_mc )
//			{
//				BuffPanel_mc.visible = true;
//				BuffPanel_mc.ShowBuff(0,"",18000,30000);
//			}
			if(FbSummary_mc)
				FbSummary_mc.visible = false;
			if(FbAward_mc)
				FbAward_mc.visible = false;
			if(FbComfirm_mc)
				FbComfirm_mc.visible = false;
			if( EquipEnhance_mc ){
				EquipEnhance_mc.visible = false;
			}
//			if(HintScene)HintScene.visible = false;
//			if(HintLevelUp)HintLevelUp.visible = false;

			if( QuestFollow_mc )
				QuestFollow_mc.visible = false;
			/*if( SkillPanel_mc )
				SkillPanel_mc.visible = false;*/

			if( MsgSceneHint_mc != null)
				MsgSceneHint_mc.visible=false;
			if( durationAlert != null)
				durationAlert.visible=false;
				
			if(mouse_mc)
			{
			Mouse.hide();
			
			//mouse_mc.startDrag(true);
			mouse_mc.mouseEnabled = false;
			mouse_mc.mouseChildren = false;
			}


			if( Skillbar_mc != null)
			{
				//Skillbar_mc.SkillBarSwitch_mc.addEventListener("click",arrow2);
				//Skillbar_mc.MenuSlot0_mc.addEventListener("click",arrow1);
				Skillbar_mc.x= 0;
				//留底的有5pixel  全部干掉
				//Skillbar_mc.y= this.y-Skillbar_mc.height+5;
			}
			if( Combo_mc )
			Combo_mc.visible = false;


			//mouse_mc.swapDepths( root.getNextHighestDepth()+10000);
	

			//if( PackagePanel_mc)
			//ExternalInterface.call( "RegisterBag",PackagePanel_mc,"Bag");
			if( EquipEnhance_mc ){
				ExternalInterface.call( "RegisterEquipEnhance",EquipEnhance_mc,"EquipEnhance");
				}
			/*if( SkillPanel_mc )
				ExternalInterface.call( "RegisterSkillPanel",SkillPanel_mc,"SkillPanel");*/
			//ExternalInterface.call( "RegisterSkillPopUpWindow",SkillPopUpWindow_mc,"SkillPopUpWindow");
			
//			if( TransducerInfo_mc)
//			ExternalInterface.call( "RegisterTransducerInfo",TransducerInfo_mc,"TransducerInfo");	
			
//			if(tooltips_mc)
//			ExternalInterface.call( "RegisterTips",tooltips_mc,"Tips");
			
			if( QuestFollow_mc)
			ExternalInterface.call( "RegisterQuestFollow",QuestFollow_mc,"QuestFollow");
//			if( DropItemTips_mc)
//			ExternalInterface.call( "RegisterDropItemTips",DropItemTips_mc,"DropItemTips");
			//if( NPCShop_mc)
			//ExternalInterface.call( "RegisterNPCShop",NPCShop_mc,"NPCShop");
			if( fb_mc)
			ExternalInterface.call( "registerInstanceMap",fb_mc,"FB");
			if( FbSummary_mc )
			ExternalInterface.call( "registerFBSummary",FbSummary_mc,"FBSummary");
			if( FbAward_mc )
			ExternalInterface.call( "registerFBAward",FbAward_mc,"FbAward_mc");
			if( FbComfirm_mc )
			ExternalInterface.call( "registerFBBattleComfirm",FbComfirm_mc,"FbComfirm_mc");
			if( Minimap_mc)
			ExternalInterface.call( "RegisterMiniMap",Minimap_mc,"MiniMap");
			if( Map_mc)
			ExternalInterface.call( "RegisterMap",	Map_mc,"Map");

			//if( RClickMenu_mc)
			//ExternalInterface.call( "RegisterRClickMenu",RClickMenu_mc,"RClickMenu" );

			if( ChatOption)
			ExternalInterface.call( "RegisterChatOption",ChatOption, "ChatOption");
			if( MessageInfo_mc)
			ExternalInterface.call( "RegisterMessageInfo",MessageInfo_mc,"MessageInfo");


			//if( system_mc)
			//ExternalInterface.call( "RegisterInGameMenu",system_mc,"InGameMenu" );
			//if( systemVideo_mc)
			//ExternalInterface.call( "RegisterSystemSetting",systemVideo_mc,"SystemSetting");
			if( SceneHint)
			ExternalInterface.call( "RegisterSceneHint",SceneHint,"SceneHint");
			
			if( DamageNumberLevel )
			{
				ExternalInterface.call( "RegisterDamageNumberLevel",DamageNumberLevel,"DamageNumberLevel");
			}


//			if( AbilityCastbarEnerge_mc)
//				ExternalInterface.call( "RegisterProgressBarWidget",AbilityCastbarEnerge_mc,"CastbarEnerge");
//			if( AbilityCastbarStrength_mc )
//				ExternalInterface.call( "RegisteProgressBarStrengthWidget",AbilityCastbarStrength_mc,"CastbarStrength");
//			if( QteTopHint_mc )
//				ExternalInterface.call( "RegisteProgressBarQTEWidget",QteTopHint_mc,"QteTopHint");
//			if( BuffPanel_mc )
//				ExternalInterface.call( "RegisterBuffPanel",BuffPanel_mc,"BuffPanel");
//								
//			if( HintScene )
//				ExternalInterface.call( "RegisteHintSceneWidget",HintScene,"HintScene");
//			if( HintLevelUp )
//				ExternalInterface.call( "RegisteHintLevelUpWidget",HintLevelUp,"HintLevelUp");	

			if(Contactlevel)
			ExternalInterface.call( "RegisterContactLevel",Contactlevel,"ContactLevel");
			if( ContactWidget)
			ExternalInterface.call( "RegisterContactWidget",ContactWidget,"ContactWidget");
			
			 
			
			//ExternalInterface.call( "RegisterEnd");
			
			
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.align = "TL";
			stage.addEventListener( Event.RESIZE , ReSizeStage );
			ReSizeStage();
			
			/*tooltips_mc.swapDepths(mouse_mc.getDepth()-1);
			DropIcon_mc.swapDepths(mouse_mc.getDepth()-2);
			MenuIcon.swapDepths(mouse_mc.getDepth()-3);
			ShopMsg_mc.disablePriority = true;
			ShopMsg_mc.swapDepths(mouse_mc.getDepth()-4);
			RClickMenu_mc.disablePriority = true;
			RClickMenu_mc.swapDepths(mouse_mc.getDepth()-6);
			UnlockMsgBoxZone_mc.disablePriority = true;
			UnlockMsgBoxZone_mc.swapDepths(mouse_mc.getDepth()-5);
			
			MessageDeath.disablePriority = true;
			MessageDeath.swapDepths(mouse_mc.getDepth()-7);
			TeamMate.disablePriority = true;
			SceneHint = true;*/
		}
		
		function ReSizeStage()
		{
			var i:int;
			for( i = 0 ; i< this.numChildren ; i++)
			{
				var Panel:MyPanel = this.getChildAt(i) as MyPanel;
				trace( Panel );
				if( Panel)
				{
					Panel.UpdatePos(stage.stageWidth,stage.stageHeight);
				}
			}
			//trace( stage.stageHeight );
			//trace( stage.stageWidth );
		}
		
		override protected  function configUI():void 
		{
			//var obj:TeamMatePanel = new TeamMatePanel;
			//obj.name = 'TeamMate';
			//this.addChild(obj);
			
			super.configUI();
			
			stage.scaleMode="exactFit";

			this.addEventListener( Event.ENTER_FRAME ,UpdateFrame );
			//this.addEventListener( MouseEvent.MOUSE_MOVE ,OnMouseMove ); mousemove必须在控件之上

			//PackagePanel_mc.itemslot_11_mc.ItemButton_mc.addEventListener("click",this,"PressItem");
			initStage();
			
			//FriendChatHintPanel_mc.AddNewItem();
		}
		
		function arrow1()
		{
			//SetItemData( myinfo_panel_mc.roleContent_Gear["slot_14"] , 1,"101" ,101,"head", 0 )
			//trace("arrow1");
			//trace(DamageNumberLevel);
			DamageNumberLevel.AddNewExp( 100 , 300 , 23 );
			DamageNumberLevel.AddNewMoney( 300 , 300 , 34 );
			DamageNumberLevel.AddNewRestore( 500 , 500 , 56 );
			
			//RemoveChildWidget( Skillbar_mc, Skillbar_mc.MenuSlot0_mc );

			//Contactlevel.RemoveWindow("sss");
			//enemyinfo_mc.HPTail( 1 ,true );
			//Skillbar_mc.HPBar_mc.HPTail( 1 ,true );
			//Skillbar_mc.MpBar_mc.MPTail( 1 ,true );
			
			//Skillbar_mc.skill_0_mc.SetPublicCD(5000);
			//trace(SceneHint);
			
			//SceneHint.attachMovie( "Attack","eee_mc",111 );
			//SceneHint.attachMovie( "SceneHintText","eee_mc",SceneHint.getNextHighestDepth() );

			//ShowAttack( 100, 100, 100 ,false,0);
		//	Hint_mc._visible = true;
		//	Hint_mc.gotoAndStop("FinAttack");
		//	Hint_mc.HintLabel_mc.gotoAndPlay(1);
			//_root.ChatPanel_mc.InputBlock_mc.TextInput_mc.AddItemText("如意金箍棒",11);
			//ActiveChatBox(true);
			//trace( mouse_mc.getDepth());

		}

		

		function WidgetDispatchEvent( mc:MovieClip ,mouseevent:String )
		{
			mc.dispatchEvent( new MouseEvent(mouseevent) );
		}

		function arrow2()
		{
			//AddContactWindow("aaa");
			
			trace(1);
			//ContactLevel.AddWindow("sss");
			//Dialog_mc.visible = true;
			//Dialog_mc.gotoAndPlay(1);
			//Skillbar_mc.skill_0_mc.SetCD(1800000);
			//enemyinfo_mc.HPTail( 0.5 ,true );
			//Quest_mc._visible = !Quest_mc._visible;
			//ShowAttack(888,200,200,true,4);
			//ActiveChatBox(false);
			//Skillbar_mc.HPBar_mc.HPTail( 0.5 ,true );
			//Skillbar_mc.MpBar_mc.MPTail( 0.5 ,true );
			//WidgetDispatchEvent( myinfo_panel_mc["closebtn"],"click");
			//UnlockMsgBoxZone_mc.attachMovie("UnlockMsgBox","UnlockMsgBox0",UnlockMsgBoxZone_mc.getNextHighestDepth());
		}
		
		public function RemoveChildWidget( ParentMc:MovieClip , ChildMc:DisplayObject )
		{
			//trace(ParentMc);
			//trace(ChildMc);
			if( ParentMc && ChildMc )
			{
				ExternalInterface.call( "ASTrace",ParentMc+ChildMc );
				ParentMc.removeChild( ChildMc );
			}
			
		}

		public function AddContactWindow( Windowname:String)
		{
			var _ClassRef:Class = getDefinitionByName( "ContactDialog") as Class;
			//ExternalInterface.call( "ASTrace",Windowname );
			var ContactMc = new _ClassRef;
			//ExternalInterface.call( "ASTrace",ContactMc );
			
			Contactlevel.addChild(ContactMc);
			ContactMc.name = Windowname;
		}


//temp_mc._visible = false;

//	public function SetItemData( mc:MyItemSlot, quantity:int,iconname:String ,itemindex:int,type:String, itemColor:int )
//	{
//		//ExternalInterface.call( "ASTrace",mc.name );
//		if( mc)
//			mc.SetData(quantity,iconname,itemindex,type,itemColor);
//	}
//
//	public function SetItemShowData( mc:MyItemSlotShow, quantity:int,iconname:String ,itemindex:int,type:String, itemColor:int )
//	{
//		if( mc)
//			mc.SetData(quantity,iconname,itemindex,type,itemColor);
//	}



function SetCombo( count:Number)
{
	
	Combo_mc.Combo_mc.count = count;
	Combo_mc.Combo_mc.bNeedUpdate = true;
	Combo_mc.gotoAndPlay(1);
	Combo_mc.visible = true;
}


//var lev = 1;
//critical_mc.gotoAndStop("none");
//var CriticalTextList:Array = new Array;
var CriticalCount = 0;
var MissCount = 0;
var AttackCount = 0;


/*function ShowAttack(  count:Number,Posx,Posy ,bBlock:Boolean,blockcount:Number )
{
	var tempMc:Attack = new Attack();
	tempMc.name="attack_mc"+AttackCount;
	//root.attachMovie("Attack","attack_mc"+AttackCount, root.getNextHighestDepth());
	addChild( tempMc );
	//critical_mc.duplicateMovieClip( "critical_mc0",1);
	//var tempMc = root["attack_mc"+AttackCount];
	trace(AttackCount);
	if(tempMc)
	{
		tempMc.x = Posx;
		tempMc.y = Posy;
		
		tempMc.visible = false;
		tempMc.attack_mc.count = count;
		if(bBlock)
		{
			tempMc.attack_mc.blockcount = blockcount;
		}
		tempMc.attack_mc.bNeedUpdate = true;
		//Combo_mc._visible = true;
		tempMc.gotoAndPlay(1);
		
		if(bBlock)
		{
			tempMc.attack_mc.gotoAndStop("block");
		}
		else
		{
			tempMc.attack_mc.gotoAndStop("1");
		}
		
		AttackCount++;
		
		tempMc.visible = true;
	//CriticalTextList.push(tempMc);
	}
	
	if(AttackCount >1000)
	{AttackCount = 0;}
	
}
function ShowCritical(  count:Number,Posx,Posy )
{
	var tempMc:Critical = new Critical();
	tempMc.name = "critical_mc"+CriticalCount
	addChild( tempMc );
	
	//root.attachMovie("Critical","critical_mc"+CriticalCount, root.getNextHighestDepth());
	
	//critical_mc.duplicateMovieClip( "critical_mc0",1);
	//var tempMc = root["critical_mc"+CriticalCount];
	trace(CriticalCount);
	if(tempMc)
	{
	tempMc.x = Posx;
	tempMc.y = Posy;
	
	tempMc.visible = false;
	tempMc.critical_mc.count = count;
	tempMc.critical_mc.bNeedUpdate = true;
	//Combo_mc._visible = true;
	tempMc.gotoAndPlay(1);
	
	CriticalCount++;
	
	tempMc.visible = true;
	//CriticalTextList.push(tempMc);
	}
	
		if(CriticalCount >1000)
	{CriticalCount = 0;}
	
}
function ShowMiss( Posx,Posy )
{
	//root.attachMovie("Miss","miss_mc"+MissCount,root.getNextHighestDepth());
	//var tempMc = root["miss_mc"+MissCount];
	var tempMc:Miss = new Miss();
	tempMc.name = "miss_mc" + MissCount;
	addChild( tempMc );
	
	//trace(MissCount);
	if(tempMc)
	{
	tempMc.x = Posx;
	tempMc.y = Posy;
	
	tempMc.visible = false;
	
	tempMc.miss_mc.bNeedUpdate = true;
	

		tempMc.miss_mc.gotoAndStop("miss");
	
	//Combo_mc._visible = true;
	tempMc.gotoAndPlay(1);
	
	MissCount++;
	
	tempMc.visible = true;
	//CriticalTextList.push(tempMc);
	}
	
		if(MissCount >1000)
	{MissCount = 0;}
	
}*/

function ShotText( sText,colorFont,colorfilter, Posx,Posy,TextSize,speedx,speedy,Lenthx,Lenthy )
{
	
	/*root.createTextField("HP_txt"+TextList.length,root.getNextHighestDepth(),Posx,Posy,200,50);

	//注意！一个层只能有一个
	
	var HP_txt = root["HP_txt"+TextList.length];
	
	HP_txt.multiline = false;
	HP_txt.wordWrap = false;//自动换行
	HP_txt.border = false;
	HP_txt.embedFonts = true;	
	HP_txt.type = "dynamic";
	HP_txt.selectable = false;
	
	
	temp = new TextInfo;
	
	temp.nSpeedx = speedx;
	temp.nSpeedy = speedy;
	temp.nLenthx = Lenthx;
	temp.nLenthy = Lenthy;
	temp.OrignX = Posx;
	temp.OrignY = Posy;
	
	
	//var suc = delete temp;
	//trace(suc);

	myformat = new TextFormat();
	myformat.color = colorFont;
	myformat.bullet = false;
	myformat.bold = true;
	myformat.size = TextSize;
	myformat.font = "$TitleFont";

	HP_txt.text = sText;
	HP_txt.setTextFormat(myformat);
	
	HP_txt.filters = [new GlowFilter(colorfilter,1,1,1,800,1)];
	
	TextInfoList.push(temp);
	
	TextList.push(HP_txt);*/
	
	
	
	
};

		function FindChild( obj:Object )
		{
			if( obj is TextField )
			{
				trace( (obj as TextField).defaultTextFormat.font +":"+   (obj as TextField).name  );
			}
			else if ( obj is MovieClip )
			{
				var i:int ;
				
				for( i = 0 ;i< (  obj as MovieClip ).numChildren ; i++ )
				{
					FindChild( (  obj as MovieClip ).getChildAt( i ) );
				}
				
			}
		}

//处理右键响应
/*_global.gfxExtensions = true;
var mouseHandle:Object = {};
mouseHandle.onMouseDown = function ( button:Number,targetPath:String,mouseIdx:Number,x:Number,y:Number,dblclick:Boolean)
{
	
	if( button == 2)//右键
	{
		
		//trace("bb");
		var  dropDir = mouse_mc._droptarget;
		
		var  dropItem:MyItemSlot = MyItemSlot( eval(dropDir));//判断鼠标下的是否是myitemslot
		if( dropItem == null)
		{
			dropItem = MyItemSlot( eval(dropDir)._parent._parent);
		}
		trace(dropDir);
		if(dropItem!=null)
		{
			//_root.tooltips_mc._visible =false;
			dropItem.HideTips();
		}
		if ( dropItem!=null && (dropItem.SlotType == 4 ||dropItem.SlotType == 0) )
		{
			//_root.tooltips_mc._visible =false;
			ExternalInterface.call( "MouseRightClickItem",dropItem );
			return;
		}
		var RightClickButton:MyRightClickButton = MyRightClickButton( eval(dropDir) );
		if( RightClickButton != null )
		{
			ExternalInterface.call( RightClickButton.EventFunction );
			return;
		}
	}
}
Mouse.addListener(mouseHandle);
*/


public function ActiveChatBox( active:Boolean )
{
	if( active )
	{
		ChatPanel_mc.InputBlock_mc.visible = true;
		//Selection.setFocus( ChatPanel_mc.InputBlock_mc.TextInput_mc.textField );
	}
	else
	{
		ChatPanel_mc.InputBlock_mc.visible = false;
		//ChatPanel_mc.InputBlock_mc.TextInput_mc.ClearText();
	}
}

function OnMouseMove()
{
	//trace("OnMouseMove:"+ mouse_mc.dropTarget );

}

	function GetLastTopUIComponent( mc:DisplayObject ):UIComponent
	{
		if( mc is UIComponent )
		{
			return ( mc as UIComponent);
		}
		else if( mc.parent )
		{
			return GetLastTopUIComponent( mc.parent );
		}

		return null;
		
	}

function UpdateFrame()
{
	if( mouse_mc )
	{
		mouse_mc.x = root.mouseX;
		mouse_mc.y = root.mouseY;
	}
	 
	var UC:UIComponent;
	if( (mouse_mc.dropTarget == null ||  !mouse_mc.dropTarget.visible ) && bMouseOnUI )
	{
		bMouseOnUI = false;
		ExternalInterface.call( "ASOnUI" , bMouseOnUI , "" );
	}
	else if( bMouseOnUI && mouse_mc.dropTarget != null && mouse_mc.dropTarget.visible )
	{
		UC = GetLastTopUIComponent( mouse_mc.dropTarget );
		if( UC != null && !UC.MaskUI )
		{
			bMouseOnUI = false;
			ExternalInterface.call( "ASOnUI" , bMouseOnUI , "" );
		}
	}
	else if(  mouse_mc.dropTarget != null && !bMouseOnUI && mouse_mc.dropTarget.visible )
	{
		UC = GetLastTopUIComponent( mouse_mc.dropTarget ); //这个检测有点耗啊
		if( UC != null && UC.MaskUI )
		{
			bMouseOnUI = true;
			ExternalInterface.call( "ASOnUI" , bMouseOnUI , UC.name );
		}
	}
	
	/*newtime = getTimer();
	//trace(_root.frametime);
	frametime =  newtime-prev ;
	prev = newtime;*/
	
	if( DropIcon_mc && MenuIcon )
		UpdateDrag();
	
	//if(tooltips_mc && tooltips_mc.visible)
	//{
	//	UpdateTips();
	//}

	//if(tooltips_mc_new && tooltips_mc_new.visible)
	//{
		
	//}
	
/*	if(TextList.length > 0)
	{
		for(var i = TextInfoList.length-1;i>=0;i--)
		{
			//trace(TextList[i]);
									
			var IsOver = UpdateText(TextList[i],TextInfoList[i]);
			
			if(IsOver)
			{
				TextList[i].removeTextField();
				TextList.splice(i,1);
				delete TextInfoList[i];
				TextInfoList.splice(i,1);
				
			}			
		}
	}	
*/
}

public function ChangeTips() //最好别用这个
{
	UpdateTips();
	tooltips_mc.visible = true;
}

function UpdateTips()//最好别用这个
{
	tooltips_mc.x = root.mouseX - 1;
	tooltips_mc.x = Math.max( 0,tooltips_mc.x);
	tooltips_mc.y = root.mouseY - tooltips_mc.height - 1;
	tooltips_mc.y = Math.max( 0,tooltips_mc.y);
}

function UpdateDrag()
{
	//ExternalInterface.call("ASTrace", "UpdateDrag0:"+DropIcon_mc._visible );
	if( DropIcon_mc.bNeedVisible || DropIcon_mc.visible )
	{
		
		DropIcon_mc.bNeedVisible = false;
		DropIcon_mc.x = root.mouseX-18;
		DropIcon_mc.y = root.mouseY-18;
		
		DropIcon_mc.visible = true;
		//ExternalInterface.call("ASTrace", "UpdateDrag1:"+DropIcon_mc._visible );
	}
	if( MenuIcon.bNeedVisible || MenuIcon.visible)
	{
		MenuIcon.bNeedVisible = false;
		MenuIcon.x = root.mouseX-16;
		MenuIcon.y = root.mouseY-16;
		
		MenuIcon.visible = true;
	}
	
}

//init();



/*function UpdateText ( blood_txt:TextField,Info:TextInfo ):Boolean
{
	//stage.mouseX
	
		var nSpeedx = Info.nSpeedx;			
		var nSpeedy = Info.nSpeedy;
		var nLenthx = Info.nLenthx;
		var nLenthy = Info.nLenthy;
		var OrignX = Info.OrignX;
		var OrignY = Info.OrignY;
		
		
	
		if(nSpeedx > 0)
		{
			if(blood_txt._x < OrignX + nLenthx )
			{
				blood_txt._x +=nSpeedx;
				blood_txt._alpha = 100-Number(blood_txt._x-OrignX)/nLenthx*100;
				
			}
			else 
			{
				nSpeedx = 0;
				
			}
		}
		if(nSpeedx < 0)
		{
			if(blood_txt._x > OrignX + nLenthx )
			{
				blood_txt._x +=nSpeedx;
				blood_txt._alpha = 100-Number(blood_txt._x-OrignX)/nLenthx*100;
				
			}
			else 
			{
				nSpeedx = 0;
				
			}
		}
		
		if(nSpeedy > 0)
		{
			if(blood_txt._y < OrignY + nLenthy )
			{
				blood_txt._y +=nSpeedy;
				blood_txt._alpha = 100-Number(blood_txt._y-OrignY)/nLenthy*100;
				
			}
			else 
			{
				nSpeedy = 0;
				
			}
		}
		if(nSpeedy < 0)
		{
			if(blood_txt._y > OrignY + nLenthy )
			{
				blood_txt._y +=nSpeedy;
				blood_txt._alpha = 100-Number(blood_txt._y-OrignY)/nLenthy*100;
				
			}
			else 
			{
				nSpeedy = 0;
				
			}
		}
		
		if( nSpeedx == 0 && nSpeedy == 0)
		{
			return true;
		}
		else
			return false;
}*/

	}
}