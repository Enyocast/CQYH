package ActionScript3.Master{
	
	import ActionScript3.MyPanel;

	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButtonNew;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ScrollingList;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;

	public class MasterPanel extends MyPanel
	{
		public var MasterInfo:MasterInfoPage;
		public var MasterApplyList_mc:MasterApplyListPage;
		public var MasterPosterList_mc:MasterPosterListPage;
		public var StudentApplyList_mc:StudentApplyListPage;
		public var StudentPosterList_mc:StudentPosterListPage;
		
		public var tF_mastervalue:TextField;
		public var tF_studentnum:TextField;
		public var tF_static0:TextField;
		public var tF_static1:TextField;
		public var btn_StopRecruit:Button;
		public var btn_StartRecruit:Button;
		
		public var tab0_mc:RadioButton;//师门
		public var tab1_mc:RadioButton;//拜师名册
		public var tab2_mc:RadioButton;//拜师管理
		public var tab3_mc:RadioButton;//收徒名册
		public var tab4_mc:RadioButton;//收徒管理
		
		public var _bg2:MovieClip;
		public var _bg1:MovieClip;
		public var _listbg2:MovieClip;
		public var _listbg1:MovieClip;
		/**/
		public var MasterState:int;
  
		override protected  function configUI():void 
		{	
			ShowMode="BC";
			super.configUI();			
			MasterState = 0;
			this.hideBG2();
			tab0_mc.selected = true;
			//师门
			tab0_mc.addEventListener(MouseEvent.CLICK, onShowMasterInfoPage);
			tab1_mc.addEventListener(MouseEvent.CLICK, onShowMasterPosterListPage);
			tab2_mc.addEventListener(MouseEvent.CLICK, onShowMasterApplyListPage);
			tab3_mc.addEventListener(MouseEvent.CLICK, onShowStudentPosterListPage);
			tab4_mc.addEventListener(MouseEvent.CLICK, onShowStudentApplyListPage);
			
			btn_StartRecruit.addEventListener(MouseEvent.CLICK, onClickStartRecruit);
			btn_StopRecruit.addEventListener(MouseEvent.CLICK, onClickStopRecruit);
			btn_StartRecruit.visible = false;
			btn_StopRecruit.visible = false;
			UCUpdateStateChange(0,0);
		}
		
		public function onClickMasterTap(nTap:int)
		{
			if(nTap == 0)
				SetWindowTitle("师门信息");
			else if(nTap == 1)
				SetWindowTitle("拜师名册");
			else if(nTap == 2)
				SetWindowTitle("待定师父");
			else if(nTap == 3)
				SetWindowTitle("收徒名册");
			else if(nTap == 4)
				SetWindowTitle("待定徒弟");
				
			ExternalInterface.call("ASClickMasterTap",nTap);
		}
		public function UCsetMasterInfoCheckBox(bl:Boolean,isshow:Boolean):void
		{
			MasterInfo.setMasterInfoCheckBox(bl,isshow);
		}
		public function UCUpdateMasterExp(nExp:int):void
		{
			tF_mastervalue.text = nExp.toString();
		}
		
		public function UCUpdateStudentNum(nNum:int,nMax:int):void
		{
			tF_studentnum.text = nNum.toString() + "/" + nMax.toString();
		}
		public function UCClickMasterTap(nTab:int):void
		{
			if(nTab==0)
			{
				this.hideBG1();
			}
			else
			{
				this.hideBG2();
			}
			if(nTab == 0)
			{
				if(tab0_mc.visible)
				{
					tab0_mc.selected = true;
					onClickMasterTap(0);
				}
			}
			else if(nTab == 1)
			{
				if(tab1_mc.visible)
				{
					tab1_mc.selected = true;
					onClickMasterTap(1);
				}
			}
			else if(nTab == 2)
			{
				if(tab2_mc.visible)
				{
					tab2_mc.selected = true;
					onClickMasterTap(2);
				}
			}
			else if(nTab == 3)
			{
				if(tab3_mc.visible)
				{
					tab3_mc.selected = true;
					onClickMasterTap(3);
				}
			}
			else if(nTab == 4)
			{
				if(tab4_mc.visible)
				{
					tab4_mc.selected = true;
					onClickMasterTap(4);
				}
			}
			MasterInfo.visible 				= tab0_mc.selected;
			MasterPosterList_mc.visible 	= tab1_mc.selected;
			MasterApplyList_mc.visible 		= tab2_mc.selected;
			StudentPosterList_mc.visible 	= tab3_mc.selected;
			StudentApplyList_mc.visible 	= tab4_mc.selected;
		}
		public function UCUpdateStateChange( newState:int ,nSelfState:int):void
		{
			MasterState = newState;
			MasterInfo.UpdateMasterState(newState,nSelfState);
			
			tab0_mc.visible = false;
			tab1_mc.visible = false;
			tab2_mc.visible = false;
			tab3_mc.visible = false;
			tab4_mc.visible = false;
			
			tF_static1.visible = false;
			tF_static0.visible = false;
			tF_mastervalue.visible = false;
			tF_studentnum.visible = false;
			
			if(MasterState == 0)
			{
				tab0_mc.visible = true;
				tab0_mc.selected = true;
				tab1_mc.visible = true;
				tab2_mc.visible = true;
				btn_StartRecruit.visible = false;
				btn_StopRecruit.visible = false;
				if(!tab2_mc.selected&&!tab1_mc.selected)
				{
					tab0_mc.selected = true;
				}
			}
			else if(MasterState == 1)
			{
				tab0_mc.visible = true;
				tab0_mc.selected = true;
				btn_StartRecruit.visible = false;
				btn_StopRecruit.visible = false;
			}
			else if(MasterState == 2)
			{
				tab0_mc.visible = true;
				tab3_mc.visible = true;
				tab4_mc.visible = true;

				if(!tab3_mc.selected&&!tab4_mc.selected)
				{
					tab0_mc.selected = true;
				}
				
				tF_static1.visible = true;
				tF_static0.visible = true;
				tF_mastervalue.visible = true;
				tF_studentnum.visible = true;
			}
			if(tab0_mc.selected==true)
			{
				onShowMasterInfoPage();
			}
			else if(tab1_mc.selected==true)
			{
				onShowMasterPosterListPage();
			}
			else if(tab2_mc.selected==true)
			{
				onShowMasterApplyListPage();
			}
			else if(tab3_mc.selected==true)
			{
				onShowStudentPosterListPage();
			}
			else
			{
				onShowStudentApplyListPage();
			}
		}
		
		public function onClickStartRecruit()
		{
			ExternalInterface.call("ASClickStartRecruit");
		}
		public function onClickStopRecruit()
		{
			ExternalInterface.call("ASClickStopRecruit");
		}
		
		private function hideBG2():void
		{
			_listbg1.visible=true;
			_bg1.visible=true;
			_listbg2.visible=false;
			_bg2.visible=false;
		}
		
		private function hideBG1():void
		{
			_listbg1.visible=false;
			_bg1.visible=false;
			_listbg2.visible=true;
			_bg2.visible=true;
		}
		
		public function onShowMasterInfoPage(evt:MouseEvent=null):void
		{
			hideBG1();
			MasterInfo.visible = true;
			MasterPosterList_mc.visible = false;
			MasterApplyList_mc.visible = false;
			StudentPosterList_mc.visible = false;
			StudentApplyList_mc.visible = false;
			onClickMasterTap(0);
		}
		
		public function onShowMasterPosterListPage(evt:MouseEvent=null):void
		{
			hideBG2();
			MasterInfo.visible = false;
			MasterPosterList_mc.visible = true;
			MasterApplyList_mc.visible = false;
			StudentPosterList_mc.visible = false;
			StudentApplyList_mc.visible = false;
			onClickMasterTap(1);
		}
		
		public function onShowMasterApplyListPage(evt:MouseEvent=null):void
		{
			hideBG2();
			MasterInfo.visible = false;
			MasterPosterList_mc.visible = false;
			MasterApplyList_mc.visible = true;
			StudentPosterList_mc.visible = false;
			StudentApplyList_mc.visible = false;
			onClickMasterTap(2);
		}
		
		public function onShowStudentPosterListPage(evt:MouseEvent=null):void
		{
			hideBG2();
			MasterInfo.visible = false;
			MasterPosterList_mc.visible = false;
			MasterApplyList_mc.visible = false;
			StudentPosterList_mc.visible = true;
			StudentApplyList_mc.visible = false;
			onClickMasterTap(3);
		}
		
		public function onShowStudentApplyListPage(evt:MouseEvent=null):void
		{
			hideBG2();
			MasterInfo.visible = false;
			MasterPosterList_mc.visible = false;
			MasterApplyList_mc.visible = false;
			StudentPosterList_mc.visible = false;
			StudentApplyList_mc.visible = true;
			onClickMasterTap(4);
		}
		
		public function UCUpdateRecruitState( nState:int )
		{
			if(MasterState == 2)
			{
				//btn_StartRecruit.visible = (nState == 0);
				//btn_StopRecruit.visible = !(nState == 0);
			}
		}
		public function UCUpdateMasterApplyListData( MasterData:Array ):void
		{
			MasterApplyList_mc.updateData( MasterData );
		}		
		public function UCUpdateMasterPosterListData( MasterData:Array ):void
		{
			MasterPosterList_mc.updateData( MasterData );
		}		
		
		public function UCUpdateStudentApplyListData( MasterData:Array ):void
		{
			StudentApplyList_mc.updateData( MasterData );
		}		
		public function UCUpdateStudentPosterListData( MasterData:Array ):void
		{
			StudentPosterList_mc.updateData( MasterData );
		}		
		public function UCUpdateMasterInfoListData( StudentDetailData:Array ):void
		{
			MasterInfo.updateData( StudentDetailData );
		}		
		
		public function UCUpdateMasterApplyListDataOnSelected(index:int,id:int)
		{
			MasterApplyList_mc.selectItem(index,id);
		}
		public function UCUpdateStudentApplyListDataOnSelected(index:int,id:int)
		{
			StudentApplyList_mc.selectItem(index,id);
		}

	}
}