package ActionScript3.PlayerInfoWidget
{

	import ActionScript3.MyPanel;
	import ActionScript3.MyActivePanel;
	import flash.external.ExternalInterface;

	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	//import ActionScript3.MyTipButton;
	import ActionScript3.Widget.CharEquipPanel;
	import scaleform.clik.events.ButtonEvent;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import ActionScript3.ItemSlot.MyItemSlotComponentQuality;
	import ActionScript3.ItemSlot.MyItemSlotComponentIcon;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	import scaleform.clik.data.DataBinding;
	import ActionScript3.MyScrollPanel;
	import scaleform.clik.events.SliderEvent;
	import ActionScript3.Widget.MyTipsText;
	import ActionScript3.MyTipButtonNew;
	import UI_SkillTree.SkillTreeAS3.ActiveSkillListPanel;
	import UI_EquipEnhance.EquipEnhanceAS3.EquipEnhanceNewPanel;
	import UI_EquipEnhance.EquipEnhanceAS3.EquipSlotIconData;
	import ActionScript3.PlayerInfoWidget.HeavenGasViewPanel;
	import ActionScript3.Common.CustomScrollBar;
	import scaleform.clik.controls.RadioButton;

	public class PlayerInfoWidget extends MyPanel
	{
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		public var tab3_mc:RadioButton;
		public var tab4_mc:RadioButton;
		
		public var showPanel_mc:MovieClip;
		public var refinePanel_mc:EnhanceViewPanel;
		public var ActiveSkillListPanelMc:SkillViewPanel;
		public var HeavenGasPanel:HeavenGasViewPanel;
		public var bloodPanel_mc:HeavenBloodViewPanel;
		
		const slotNum:int = 14;
		const maskHeight:int = 300;

		var itemSlot:Array;
		var itemQuality:Array;
		var itemIcon:Array;
		
		public var Class_txt:TextField;
		
		//public var EquipSlotEnhanceInfoMc:MovieClip;
		
		public var nomalInfo:MovieClip;

		const EnumMale:int = 1;
		const EnumFemale:int = 2;
		
		const EnumWarrior:int = 0;
		const EnumMage:int = 1;
		const EnumAss:int = 2;
		const EnumArch:int = 3;
		
		public var panelId:int = 0;
		
		var skillItemList:Array;

		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			tab0_mc.addEventListener( ButtonEvent.CLICK, ClickTab );
			tab1_mc.addEventListener( ButtonEvent.CLICK ,ClickTab );
			tab1_mc.visible=false;
			tab2_mc.addEventListener( ButtonEvent.CLICK ,ClickTab);
			tab3_mc.addEventListener( ButtonEvent.CLICK ,ClickTab);
			tab4_mc.addEventListener( ButtonEvent.CLICK ,ClickTab);

			tab0_mc.selected = true;
			ClickTab();
			
			ActiveSkillListPanelMc.visible = tab0_mc.visible = tab2_mc.visible = false;//skill panel have big change in CQ version, hiding tab2_mc and ActiveSkillListPanelMc now.
			tab3_mc.visible = false;
			tab4_mc.visible = false;
			
			HeavenGasPanel.visible = false;
			bloodPanel_mc.visible = false;
			
			skillItemList = new Array;

			if (showPanel_mc)
			{
				nomalInfo=showPanel_mc.getChildByName("nomalInfo") as MovieClip;
				Class_txt = showPanel_mc.getChildByName("Class_txt") as TextField;

				itemSlot = new Array  ;
				itemQuality = new Array  ;
				itemIcon = new Array  ;

				//品质列表
				var qualityMc:MyItemSlotComponentQuality;
				for (var i:int = 0; i < slotNum; i++)
				{
					qualityMc = showPanel_mc.getChildByName( "itemQuality_"+i ) as MyItemSlotComponentQuality;
					if (qualityMc)
					{
						itemQuality.push( qualityMc );
					}
				}
				//icon列表
				var iconMc:MyItemSlotComponentIcon;
				for (i = 0; i < slotNum; i++)
				{
					iconMc = showPanel_mc.getChildByName( "itemIcon_"+i ) as MyItemSlotComponentIcon;

					if (iconMc)
					{
						itemIcon.push( iconMc );
						//根据fla的尺寸把内部uiloader调整了下
						iconMc.initSize();
					}
				}

				//slot列表
				for (i = 0; i < slotNum; i++)
				{
					var slot:MyItemSlot = showPanel_mc.getChildByName( "itemSlot_"+i ) as MyItemSlot;
					
					if (slot)
					{
						slot.canChangeSize = true;
						itemSlot.push( slot );
						if (itemQuality.length > i)
						{
							qualityMc = itemQuality[i] as MyItemSlotComponentQuality;

							if (qualityMc)
							{
								slot.width = qualityMc.width;
								slot.height = qualityMc.height;
								slot.AddComponent( qualityMc );
							}
						}
						
						slot.useLargeIcon = true;

						if (itemIcon.length > i)
						{
							iconMc = itemIcon[i] as MyItemSlotComponentIcon;
							iconMc.x-=0.5;

							if (iconMc)
							{
								slot.AddComponent( iconMc );
							}
						}
					}
				}

			}
		}


		public function onHoverTotalEnhanceProp( e:Event )
		{
			ExternalInterface.call( "ASShowTotalEnhancProp" );
		}
		
		//
		public function onMouseOutTotalEnhanceProp( e:Event )
		{
			ExternalInterface.call( "ASHideTotalEnhancProp" );
		}
		
		
		public function SetAttributeItem( attriData:Object )
		{

		}

		public function SetAttributeData( attriData:Array )
		{

		}

		function hideAttributeTips( e:Event )
		{
			ExternalInterface.call( "ASHideTips_Attribute" );
		}

		public function UpdateBaseInfo( tData:Object )
		{
			if ( tData && Class_txt)
			{
				Class_txt.text = tData.classText;
				this.SetWindowTitle(tData.name);//设置玩家标题名称
				/*				var frame:int= tData.classId +1;
				charactorBg.gotoAndStop( frame );*/
			}
		}
		//更新信息状态
		public function UCUpdateInfoState(type:Boolean=false):void
		{
			this.nomalInfo.visible=true;
		}

		public function SetPanelText( tData:Object )
		{
			panelId = tData.panelId;
		}


		public function UpdateBattlePoint( tData:Object )
		{

		}
		
		public function UpdateRefineData( refineData:Object )
		{
			if( refineData )
			{
				refinePanel_mc.UpdateSummaryPanel( refineData as EquipSlotIconData );
			}
		}
		
		public function UpdateSkillData( skillData:Array )
		{
			if( skillData )
			{
				ActiveSkillListPanelMc.UpdateMainSkillList(skillData);
			}
		}
		
		public function UCSetHeavenViewGasData(dataPro:Array)
		{
			HeavenGasPanel.UpdateEquipGasView(dataPro);
		}

		public function UCSetHeavenViewBloodData(dataPro:Array)
		{
			bloodPanel_mc.UpdateHeavenBloodInfo(dataPro);
		}
		function TurnLeft()
		{
			ExternalInterface.call("TurnPress",true);
		}
		function TurnRight()
		{
			ExternalInterface.call("TurnPress",false);
		}
		function TurnRelease()
		{
			ExternalInterface.call("TurnRelease");
		}

		function ClickTab()
		{
			showPanel_mc.visible = tab0_mc.selected;
			refinePanel_mc.visible = tab1_mc.selected;
			ActiveSkillListPanelMc.visible = tab2_mc.selected;
			//HeavenGasPanel.visible = tab3_mc.selected;
			//bloodPanel_mc.visible = tab4_mc.selected;
			
			/*if(tab0_mc.selected)
				SetWindowTitle(playerName);
			else if(tab1_mc.selected)
				SetWindowTitle("查看强化");
			else if(tab2_mc.selected)
				SetWindowTitle("查看技能");
			else if(tab3_mc.selected)
				SetWindowTitle("查看气息");
			else if(tab4_mc.selected)
				SetWindowTitle("查看灵性");*/
		}

	}
}