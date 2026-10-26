package UI_ActivityWidget.ActivityAS3{
	
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
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

	public class ActivityTeamView extends UIComponent
	{
		public var ActivityTeamList:ScrollingList;
		public var tabTitle:MovieClip;
		public var teamBg:MovieClip;
		public var pagectrl_mc:MovieClip;
		
		public var noTeamActivity_tf:TextField;

		public var btn_join:Button;
		public var btn_team:Button;
		public var btn_FastJoin:Button;
		
		public  var nSelIndex = -1;
		
		public var prevPage:Button;
		public var nextPage:Button;
		public var bInTeam:Boolean = false;
		
		override protected  function configUI():void 
		{		
			super.configUI();			

			ActivityTeamList.addEventListener(ListEvent.INDEX_CHANGE, onDefaultClickTeamItem);
			ActivityTeamList.addEventListener(ListEvent.ITEM_ROLL_OVER, onRollOverTeamItem);
			ActivityTeamList.addEventListener(ListEvent.ITEM_ROLL_OUT, onRollOutTeamItem);
			ActivityTeamList.addEventListener(ListEvent.ITEM_CLICK, onClickTeamItem);

			btn_join.addEventListener(MouseEvent.CLICK, onClickJoinTeam);
			btn_team.addEventListener(MouseEvent.CLICK, onClickTeamInfo);
			btn_FastJoin.addEventListener(MouseEvent.CLICK, onBtnFastJoinTeam );
			
			prevPage = pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != prevPage)
				prevPage.addEventListener(MouseEvent.CLICK, OnPrevPageClick);
			nextPage = pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != nextPage)
				nextPage.addEventListener(MouseEvent.CLICK, OnNextPageClick);
			noTeamActivity_tf.visible = false;
			UpdateActivityTeamListData([]);
		}
		
		public function onDefaultClickTeamItem(e:ListEvent)
		{
			if(e.itemRenderer == null)
				return;
			var item:ActivityTeamListItem = e.itemRenderer as ActivityTeamListItem;
			if(item.TeamId > 0)
				ExternalInterface.call("ASClickActivityTeamList", item.TeamId);
		}

		public function onClickTeamItem(e:ListEvent):void
		{
			var item:ActivityTeamListItem = e.itemRenderer as ActivityTeamListItem;
			item.setColor(2);
			if(item.TeamId > 0)
				ExternalInterface.call("ASClickActivityTeamList", item.TeamId);
		}
		
		public function ChangeSelectedTeamIndex():void
		{
			ExternalInterface.call("ASClickActivityTeamList", nSelIndex);
		}
		
		
		public function UpdateActivityTeamListData( data:Array ):void
		{
			tabTitle.visible = true;
			teamBg.visible=true;
			pagectrl_mc.visible = true;
			btn_join.visible = !bInTeam;
			btn_team.visible = bInTeam;
			btn_FastJoin.visible =! bInTeam;
			
			noTeamActivity_tf.visible = false;
			
			nSelIndex = ActivityTeamList.selectedIndex;
			if(data != null)
			{
				if(nSelIndex >= data.length)
					nSelIndex = 0;
				if(nextPage)
				   nextPage.enabled = (data.length >= 10);
				if(data.length >= 1)
				{
					var activityData:Object = data[0] as Object;
					if(activityData && activityData.TeamId < 0)
					{
						tabTitle.visible = false;
						pagectrl_mc.visible = false;
						btn_join.visible = false;
						teamBg.visible=false;
						btn_team.visible = false;
						btn_FastJoin.visible = false;
						noTeamActivity_tf.visible = true;
					}
				}
				ActivityTeamList.dataProvider = new DataProvider(data);
				ActivityTeamList.validateNow();
				ActivityTeamList.invalidateData();
				SetSelectedIndex();
			}
		}		
		
		public function SetSelectedIndex()
		{
			if(nSelIndex < 0|| nSelIndex >= ActivityTeamList.rowCount)
				nSelIndex = 0;
			ActivityTeamList.selectedIndex = nSelIndex;
			
			//ChangeSelectedTeamIndex();
		}
		
		public function onRollOverTeamItem(e:ListEvent)
		{
			var item:ActivityTeamListItem = e.itemRenderer as ActivityTeamListItem;
			item.setColor(1);
			if(item.TeamId > 0)
				ExternalInterface.call("ASRollOverActivityTeamList", item.TeamId);
		}
		
		public function onRollOutTeamItem(e:ListEvent)
		{
			var item:ActivityTeamListItem = e.itemRenderer as ActivityTeamListItem;
			item.setColor(0);
			ExternalInterface.call("ASRollOutActivityTeamList", item.TeamId);
		}
		
		public function onClickJoinTeam()
		{
			ExternalInterface.call("ASClickEnterTeam");
		}
		
		public function onClickTeamInfo()
		{
			ExternalInterface.call("ASClickTeamManager");
		}
		
		public function OnPrevPageClick()
		{
			ExternalInterface.call("ASTrace","ASPrevTeamPageClick");
			ExternalInterface.call( "ASPrevTeamPageClick");
		}
		
		public function OnNextPageClick()
		{
			ExternalInterface.call("ASTrace","ASNextTeamPageClick");
			ExternalInterface.call( "ASNextTeamPageClick");
		}
		
		public function UpdateButtonState(bTeam:Boolean):void
		{
			bInTeam = bTeam;
			if(bTeam)
			{
				btn_join.visible = false;
				btn_team.visible = true;
				btn_FastJoin.visible = false;
			}
			else
			{
				btn_join.visible = true;
				btn_team.visible = false;
				btn_FastJoin.visible = true;
			}
			if(noTeamActivity_tf.visible)
			{
				btn_join.visible = false;
				btn_team.visible = false;
				btn_FastJoin.visible = false;
			}
		}
		
		public function UpdateActivityTeamPageText(totalPage:int, curPage:int):void
		{
			var pageText:TextField = pagectrl_mc.getChildByName("tF_pageNum") as TextField;
			if(pageText)
			{
				pageText.text = String(curPage);// + "/" + String(totalPage);
				prevPage.enabled = (curPage > 1);
			}
		}
		public function onBtnFastJoinTeam()
		{
			ExternalInterface.call("ASClickFastJoinTeam");
		}
	}
}