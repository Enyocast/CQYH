package UI_SkillTree.SkillTreeAS3
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButtonNew;
	
	import UI_SkillTree.SkillTreeAS3.HeavenBloodPanel;
	import UI_SkillTree.SkillTreeAS3.HeavenGasMainPanel;
	import UI_SkillTree.SkillTreeAS3.HeavenMainPanel;
	import UI_SkillTree.SkillTreeAS3.SpecialSkillListPanel;
	
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.core.UIComponent;
	
	public class SkillTreePanel extends MyPanel
	{
		public var ActiveSkillListPanelMc:ActiveSkillListPanel;
		public var SpecialSkillListPanelMc:SpecialSkillListPanel;
		
		public var HeavenMainPanelMc:HeavenMainPanel;
		public var gasMainPanel_mc:HeavenGasMainPanel;
		public var bloodPanel_mc:HeavenBloodPanel;
		
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		public var tab3_mc:RadioButton;
		public var tab4_mc:RadioButton;
		
		public var XiuLianValue_tf:TextField;
		public var xiulianTipsMc:MovieClip;
		
		//skill tree panel is individual in version CQ, set _skillPanelAvaliable to false
		protected var _skillPanelAvaliable:Boolean = false;
		
		override protected function configUI():void
		{
			super.configUI();
			ShowMode="BC";
			ExternalInterface.call( "RegisterSkillTree", this);
			
			ExternalInterface.call( "ASTrace", "RegisterSkillTree.configUI");
			
			ExternalInterface.call( "RegisterHeavenGasMain", gasMainPanel_mc);
			ExternalInterface.call( "RegisterHeavenMain", HeavenMainPanelMc);
			ExternalInterface.call( "RegisterHeavenBlood", bloodPanel_mc);
			//
			
			trace(">>>>>>>>>>>>>>> HeavenBloodTabPanel::configUI  end 1");
			//ActiveSkillTreeTab.addEventListener(MouseEvent.CLICK, onTabClickAchievementPersonal);
			tab0_mc.addEventListener(MouseEvent.CLICK, ClickPanelTab0);
			tab1_mc.addEventListener(MouseEvent.CLICK, ClickPanelTab1);
			tab2_mc.addEventListener(MouseEvent.CLICK, ClickPanelTab2);
			tab3_mc.addEventListener(MouseEvent.CLICK, ClickPanelTab3);
			tab4_mc.addEventListener(MouseEvent.CLICK, ClickPanelTab4);
			
			//tab0_mc.loadPic( "img://MMO_UIImg.img_tab_skilltree_0" );
			//tab1_mc.loadPic( "img://MMO_UIImg.img_tab_skilltree_1" );
			//tab3_mc.loadPic( "img://MMO_UIImg.img_tab_skilltree_2" );
			//tab4_mc.loadPic( "img://MMO_UIImg.img_tab_shop_3" );
			
			trace(">>>>>>>>>>>>>>> HeavenBloodTabPanel::configUI  end 2");
			ActiveSkillListPanelMc.visible = false;
			HeavenMainPanelMc.visible = true;
			gasMainPanel_mc.visible = false;
			bloodPanel_mc.visible = false;
			SpecialSkillListPanelMc.visible = false;
			
			tab1_mc.visible = _skillPanelAvaliable;
			
			//var btnMovie1:MovieClip = tab0_mc.getChildByName("icon_mc") as MovieClip;
			//if(btnMovie1)
			//btnMovie1.gotoAndStop("skilltree0");
			
			//var btnMovie2:MovieClip = tab1_mc.getChildByName("icon_mc") as MovieClip;
			//if(btnMovie2)
			//btnMovie2.gotoAndStop("skilltree2");
			
			//var btnMovie3:MovieClip = tab3_mc.getChildByName("icon_mc") as MovieClip;
			//if(btnMovie3)
			//btnMovie3.gotoAndStop("skilltree1");
			trace(">>>>>>>>>>>>>>> HeavenBloodTabPanel::configUI  end 3");
			//gasPractisePanel_mc.visible = false;
		}
		
		//----------------------------------------------------------------------------------------
		public function UCSetActiveSkillList( skillsData:Array ):void
		{
			_skillPanelAvaliable && ActiveSkillListPanelMc.UpdateMainSkillList( skillsData );
		}
		
		//
		public function UCSetDetailActiveSkillList( skillsData:Array ):void
		{
			_skillPanelAvaliable && ActiveSkillListPanelMc.UpdateDetailSkillList( skillsData );
		}
		
		//---------------------------------------------------------------------------------------
		public function UCSetSpecialSkillList( skillsData:Array ):void
		{
			SpecialSkillListPanelMc.UpdateSpecialSkillList( skillsData );
		}
		
		//---------------------------------------------------------------------------------------
		
		public function UCSetXiuLianValue( data:int ):void
		{
			XiuLianValue_tf.text = data.toString();
		}
		
		public function ClickPanelTab0()
		{
			ShowPanelByIndex(0);
		}
		public function ClickPanelTab1()
		{
			ShowPanelByIndex(1);
		}
		public function ClickPanelTab2()
		{
			ShowPanelByIndex(2);
		}
		public function ClickPanelTab3()
		{
			ShowPanelByIndex(3);
		}
		public function ClickPanelTab4()
		{
			ShowPanelByIndex(4);
		}
		function ShowPanelByIndex( nIndex:int)
		{
			HeavenMainPanelMc.visible = (nIndex == 0);
			if(_skillPanelAvaliable)
			{
				ActiveSkillListPanelMc.visible = (nIndex == 1);
			}
			SpecialSkillListPanelMc.visible = (nIndex == 2);
			gasMainPanel_mc.visible = (nIndex == 3);
			bloodPanel_mc.visible = (nIndex == 4);
			ExternalInterface.call( "ASClickTab", nIndex);
		}
		public function UCSetSkillTabState(nIndex:int)
		{
			tab0_mc.selected = (nIndex == 0);
			tab1_mc.selected = (nIndex == 1);
			tab2_mc.selected = (nIndex == 2);
			tab3_mc.selected = (nIndex == 3);
			tab4_mc.selected = (nIndex == 4);
			
			HeavenMainPanelMc.visible = (nIndex == 0);
			if(_skillPanelAvaliable)
			{
				ActiveSkillListPanelMc.visible = (nIndex == 1);
			}
			SpecialSkillListPanelMc.visible = (nIndex == 2);
			gasMainPanel_mc.visible = (nIndex == 3);
			bloodPanel_mc.visible = (nIndex == 4);
		}
		public function UCSetSkillTabVisibleState(skillPanel:Boolean,heavenMain:Boolean,gasMain:Boolean,bloodPanel:Boolean)
		{
			tab0_mc.visible = heavenMain;
			tab1_mc.visible = _skillPanelAvaliable && skillPanel;
			tab2_mc.visible = false;
			tab3_mc.visible = gasMain;
			tab4_mc.visible = bloodPanel;
		}
	}
}
