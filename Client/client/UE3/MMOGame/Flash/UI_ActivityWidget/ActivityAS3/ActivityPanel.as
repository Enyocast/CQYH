
package UI_ActivityWidget.ActivityAS3{
	
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	
	import flash.display.MovieClip;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import flash.events.Event;

	public class ActivityPanel extends MyPanel
	{
		public var  ListFBPanel_mc:List_FB;
		public var  ListActivityPanel_mc:ActivityContentListPanel;
		
/*		public var  typeRadio_Hot:RadioButton;
		public var  typeRadio_Copy:RadioButton;
		public var  typeRadio_Out:RadioButton;*/
		public var  rewardCheck_Exp:CheckBox;
		public var  rewardCheck_Money:CheckBox;
		public var  rewardCheck_Treasure:CheckBox;
//		public var  btnGotReward:Button;
		public var  btnEnterTeam:Button;
		
//		public var  btn_RandJoin:Button;
//		public var 	btn_create:Button;
		public var	activity_info_radio:RadioButton;
		public var	activity_team_radio:RadioButton;
		
		public var activity_info_movie:ActivityFBView;
		public var activity_team_movie:ActivityTeamView;
		
		public var activity_team_tips:ActivityTeamTips;
		
		public var rewardBar_mc:activityBarItem;
		
		public var rewardType:int = 7;
		
		public var typeRadio_Hot:RadioButton;
		public var typeRadio_Out:RadioButton;
		public var typeRadio_Copy:RadioButton;

		override protected  function configUI():void 
		{		
			ShowMode="BC";
			super.configUI();			
			typeRadio_Hot.addEventListener(Event.SELECT, onBtnFilterType0 );
			typeRadio_Out.addEventListener(Event.SELECT, onBtnFilterType1 );
			typeRadio_Copy.addEventListener(Event.SELECT, onBtnFilterType2 );
			typeRadio_Hot.visible=false;
			typeRadio_Copy.visible=false;
			typeRadio_Out.selected=true;
			rewardCheck_Exp.selected = true;
			rewardCheck_Money.selected = true;
			rewardCheck_Treasure.selected = true;
			rewardCheck_Exp.addEventListener(Event.SELECT, onBtnFilterRewardType );
			rewardCheck_Money.addEventListener(Event.SELECT, onBtnFilterRewardType );
			rewardCheck_Treasure.addEventListener(Event.SELECT, onBtnFilterRewardType );

//			btnGotReward.enabled=false;
//			btnGotReward.addEventListener(MouseEvent.CLICK, onBtnGetReward );
			btnEnterTeam.addEventListener(MouseEvent.CLICK, onBtnEnterTeamHome );
//			btn_RandJoin.addEventListener(MouseEvent.CLICK, onBtnRandJoinTeam );
//			btn_create.addEventListener(MouseEvent.CLICK, onClickCreateTeam);
			activity_info_radio.addEventListener(Event.SELECT, onBtnFilterViewFB);
			activity_team_radio.addEventListener(Event.SELECT, onBtnFilterViewTeam);

			ListFBPanel_mc.visible = false;
			ListActivityPanel_mc.visible = true;
			
			activity_info_movie.visible = true;
			activity_team_movie.visible = false;
			
			activity_team_tips.visible = false;
			//activity_info_radio.selected = true;
			activity_info_radio.visible = false;//当前版本只有活动信息，不需要显示此选项
			activity_team_radio.visible = false;
			//CQ_OB version 
//			btn_RandJoin.enabled = btn_create.enabled = false;

			/*
			if(1)
			{
				var dataR:Array = new Array;
				//for(var n:int = 0; n < 5; ++n)
				{
					var da:Object = new Object;
					da.TeamId = -1;

					dataR.push(da);
				}
				UCUpdateActivityTeamListData(dataR);
			}*/
			
		}

		public function UCUpdateActivityListData( data:Array ):void
		{
			if(ListFBPanel_mc.visible)
				ListFBPanel_mc.UCUpdateActivityFBListData(data);
			if(ListActivityPanel_mc.visible)
				ListActivityPanel_mc.UCUpdateActivityContentListData(data);
		}		
		
		public function UCUpdateActivityTeamListData( data:Array ):void
		{
			if(activity_team_movie.visible)
			{
				activity_team_radio.visible = true;
				if (data.length == 1)
				{
					var dataItem:Object = data[0] as Object;
					if (dataItem && dataItem.TeamId == -1)
					{
						activity_team_radio.visible = false;
					}
				}
				activity_team_movie.UpdateActivityTeamListData(data);
			}
		}
		
		public function UCUpdateButtonState(bTeam:Boolean):void
		{
			if(activity_team_movie)
			{
				activity_team_movie.UpdateButtonState(bTeam);
//				btn_create.visible = !bTeam;
			}
		}
		
		public function UCUpdateActivityTeamTips(data:Object):void
		{
			if(activity_team_tips.visible)
			{
				activity_team_tips.UCUpdatePanel(data);
			}
		}
		
		public function UCShowActivityTeamTips(bShow:Boolean)
		{
			activity_team_tips.visible = bShow;
		}
		
		public function UCUpdateRewardBarInfo(data:Array)
		{
			if(rewardBar_mc)
			{
				rewardBar_mc.UpdateRewardBarInfo(data);
			///	btnGotReward.enabled = rewardBar_mc.IsBtnEnable;
			}
		}
		public function onBtnEnterTeamHome()
		{
			ExternalInterface.call("ASClickEnterTeamHome");
		}
		public function onBtnGetReward()
		{
			ExternalInterface.call("ASClickGetReward");
		}
		
		public function onBtnRandJoinTeam()
		{
			ExternalInterface.call("ASClickRandJoinTeam");
		}
		public function onClickCreateTeam()
		{
			ExternalInterface.call("ASClickCreateTeam");
		}
		
		public function onBtnFilterType0()
		{
			if(!typeRadio_Hot.selected)
				return;
			ListFBPanel_mc.visible = false;
			ListActivityPanel_mc.visible = true;
			ExternalInterface.call("ASShowActivityFilterType", 0 );
		}
		public function onBtnFilterType1()
		{
			if(!typeRadio_Out.selected)
				return;
			ListFBPanel_mc.visible = false;
			ListActivityPanel_mc.visible = true;
			ExternalInterface.call("ASShowActivityFilterType", 1 );
		}
		public function onBtnFilterType2()
		{
			if(!typeRadio_Copy.selected)
				return;
			ListFBPanel_mc.visible = true;
			ListActivityPanel_mc.visible = false;
			ExternalInterface.call("ASShowActivityFilterType", 2 );
		}
		
		public function onBtnFilterViewFB()
		{
			if(!activity_info_radio.selected)
				return;
			activity_info_movie.visible = true;
			activity_team_movie.visible = false;
			ExternalInterface.call("ASShowActivityFBView");
		}
		
		public function onBtnFilterViewTeam()
		{
			if(!activity_team_radio.selected)
				return;
			activity_info_movie.visible = false;
			activity_team_movie.visible = true;
			ExternalInterface.call("ASShowActivityTeamView");
		}
		
		public function onBtnFilterRewardType(evt:Event):void
		{
			getTypeValue();
			ExternalInterface.call("ASShowActivityFilterRewardType", rewardType );
		}
		
		public function UCUpdateHuoyueValue(nCurValue:int,nMaxValue:int)
		{
			if(rewardBar_mc)
				rewardBar_mc.UpdateHuoyueValue(nCurValue,nMaxValue);
		}
		
		public function getTypeValue():void
		{
			var Value:int;
			Value = 0;
			if(rewardCheck_Exp.selected)
				Value += 1;
			if(rewardCheck_Money.selected)
				Value += 2;
			if(rewardCheck_Treasure.selected)
				Value += 4;
			rewardType = Value;
		}
		
		public function UCUpdateActivityTeamPageText(totalPage:int, curPage:int):void
		{
			if(activity_team_movie.visible)
			{
				activity_team_movie.UpdateActivityTeamPageText(totalPage, curPage);
			}
		}

		public function UCUpdateActivityDetailInfo(data:ActivityDetailInfo):void
		{
			if(activity_info_movie)
			{
				activity_info_movie.UpdateActivityDetailInfo(data);
			}
		}

	}
}