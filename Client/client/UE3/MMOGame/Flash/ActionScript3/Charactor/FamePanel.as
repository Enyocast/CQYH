package ActionScript3.Charactor
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.Timer;
	
	import UI_CharactorWidget.CharactorWidgetAS3.ListItemRenderer_Fame;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;

	public class FamePanel extends UIComponent
	{
		private static const DESCRIPTION_PREFIX_HTML_TEXT:String 		= "<font color='#FFEDC5' size='14'>称号描述：</font>";
		private static const RESTRICTION_PREFIX_HTML_TEXT:String 		= "<font color='#FFEDC5' size='14'>限制条件：</font>";

		private static const TEXT_SINGLE_LINE_HEIGHT:Number = 22;
		private static const MARGIN_DIVIDE:Number = 2;
		
		public var list_mc:ScrollingList;
		public var fameImgLoader_mc:FameImgLoader;
		public var star_mc:MovieClip;
		public var star_mc2:MovieClip;
		
		public var tF_description_mc:MovieClip;
		public var tF_ability_mc:MovieClip;
		public var tF_restriction_mc:MovieClip;
		public var tF_timeLeft_mc:MovieClip;
		
		//public var tF_currentFame:TextField;
		//public var tF_currentFame2:TextField;
		public var current_fame_loader_mc:UILoader;
		public var no_fame_image_mc:MovieClip;
		public var tf_current_fame_title:TextField;
		public var data_divide_mc:MovieClip;
		
		public var btn_UseCurrentTitle:Button;
		public var btn_ClearCurrentTitle:Button;
		public var selectTitleID:Number = 0;
		public var TitleTabBtn1:RadioButton;
		public var TitleTabBtn2:RadioButton;
		public var TitleTabBtn3:RadioButton;
		public var TitleTabBtn4:RadioButton;
		public var TitleTabBtn5:RadioButton;
		public var TitleTabIndex:Number = 1;
		public var TitleData:Array = null;
		var timerCountDown:Timer;
		
		private var tF_description:TextField;
		private var tF_ability:TextField;
		private var tF_restriction:TextField;
		private var tF_timeLeft:TextField;

		override protected function configUI():void
		{
			super.configUI();
			
			tF_description  = tF_description_mc['textField'];
			tF_ability 		= tF_ability_mc['textField'];
			tF_restriction 	= tF_restriction_mc['textField'];
			tF_timeLeft 	= tF_timeLeft_mc['textField'];
            
			timerCountDown = new Timer(1000);
			timerCountDown.addEventListener(TimerEvent.TIMER, timerHandle);
			timerCountDown.start();		
			
//			var tf:TextFormat = tF_currentFame.getTextFormat();
//			tf.align = TextFormatAlign.CENTER;
//			tF_currentFame.defaultTextFormat = tf;

			//star_mc.visible = false;


			list_mc.selectedIndex = 0;
			trace("list_mc.pixelScrollBar(true);");
			//list_mc.pixelScrollBar(true);
			list_mc.addEventListener(ListEvent.INDEX_CHANGE, handleListChange, false, 0, true);
			list_mc.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
	//		list_mc.addEventListener(ListEvent.ITEM_ROLL_OVER, handleListItemRollOver, false, 0, true);
	//		list_mc.addEventListener(ListEvent.ITEM_ROLL_OUT, handleListItemRollOut, false, 0, true);
			
			TitleTabBtn1.selected = true;
			TitleTabBtn1.addEventListener(MouseEvent.CLICK, onClickTitleTabBtn1 );
			TitleTabBtn2.addEventListener(MouseEvent.CLICK, onClickTitleTabBtn2 );
			TitleTabBtn3.addEventListener(MouseEvent.CLICK, onClickTitleTabBtn3 );
			TitleTabBtn4.addEventListener(MouseEvent.CLICK, onClickTitleTabBtn4 );
			TitleTabBtn5.addEventListener(MouseEvent.CLICK, onClickTitleTabBtn5 );
			
			//disable Button For Current Version
			disableButton();
			

			btn_UseCurrentTitle.addEventListener("click", UseCurrentTitle, false ,0, true);
			btn_ClearCurrentTitle.addEventListener("click", ClearCurrentTitle, false ,0, true);
			ExternalInterface.call( "SetLabelByID",btn_UseCurrentTitle,"MMOGame.Title.UseTitleBtn");
			ExternalInterface.call( "SetLabelByID",btn_ClearCurrentTitle,"MMOGame.Title.ClearTitleBtn");
			
			ExternalInterface.call( "SetLabelByID",TitleTabBtn1,"MMOGame.CharacterUI.Title1");
			ExternalInterface.call( "SetLabelByID",TitleTabBtn2,"MMOGame.CharacterUI.Title2");
			ExternalInterface.call( "SetLabelByID",TitleTabBtn3,"MMOGame.CharacterUI.Title3");
			ExternalInterface.call( "SetLabelByID",TitleTabBtn4,"MMOGame.CharacterUI.Title4");
			ExternalInterface.call( "SetLabelByID",TitleTabBtn5,"MMOGame.CharacterUI.Title5");
			btn_UseCurrentTitle.enabled = false;
		}
		
		//temp code
		protected function disableButton():void
		{
			TitleTabBtn3.mouseEnabled = TitleTabBtn4.mouseEnabled = false;
			TitleTabBtn3.visible = TitleTabBtn4.visible = false;
		}	
		
		function timerHandle()
		{
			updateClickByTime();
		}		
		
		public function updateTitleListData():void
		{
			if(TitleTabIndex==1){
				for (var i=0; i<TitleData.length; i++)
				{
					TitleData[i].visible = TitleData[i].obtained;
				}
			}
			else
			{
				for (var j=0; j<TitleData.length; j++)
				{
					TitleData[j].visible = (TitleData[j].TitleType == TitleTabIndex-2);
				}
			}
		}
		
		private function resetFameData():void
		{
			TitleTabBtn1.selected = true;
			TitleTabIndex = 1;
			selectTitleID=0;
			list_mc.selectedIndex = selectTitleID;
			
		}
		
		public function updateItemsData( data:Array , bReset:Boolean ):void
		{
			if(data==null){
				//updateClick(null);
				return;
			}
			
			TitleData = data;
			if(bReset)
			{
				resetFameData();
			}			
			updateTitleListData();

			
			list_mc.dataProvider = new TreeDataProvider(data);
			list_mc.validateNow();
			list_mc.invalidateData();
			//star_mc.visible = false;
			star_mc2.visible = false;
			btn_ClearCurrentTitle.visible = false;

			var currentFameIcon:String = null;
			var bFirst:Boolean = true;
			for (var i=0; i<data.length; i++)
			{
				if (data[i].isCurrent)
				{
					currentFameIcon = data[i].IconName;
					//currentFame = data[i].label;
					//star_mc.gotoAndStop(data[i].numStar);
					//star_mc.visible = true;
					btn_ClearCurrentTitle.visible = true;
				}

				if (selectTitleID>0)
				{
					if (data[i].ID == selectTitleID)
					{
						bFirst = false;
						updateClick(data[i]);
					}
				}
				else
				{
					if ( bFirst && data[i].visible )
					{
						bFirst = false;
						updateClick(data[i]);
					}
				}
			}
			
			if(bFirst == true)
			{
				updateClick(null);
			}

			if (data.length == 0)
			{
				//tF_currentFame2.text = "";
				tF_timeLeft.text="";
			}
			
			if (currentFameIcon == null)
			{
				current_fame_loader_mc.visible = false;
				no_fame_image_mc.visible = true;
				btn_ClearCurrentTitle.visible = tf_current_fame_title.visible = false;
			}
			else
			{
				current_fame_loader_mc.visible = true;
				current_fame_loader_mc.source = currentFameIcon;
				no_fame_image_mc.visible = false;
				btn_ClearCurrentTitle.visible = tf_current_fame_title.visible = true;
			}

/*			if (tF_currentFame.text != currentFame)
			{
				tF_currentFame.text = currentFame;
			}*/
		}

		public function updateClickByTime():void
		{
			if(TitleData==null)return;
			if(visible==false)return;
			
			for (var i=0; i<TitleData.length; i++)
			{
				if (selectTitleID == TitleData[i].ID && TitleData[i].ValidTime>0 )
				{
					updateClick(TitleData[i]);
					return;
				}
			}
		}
		
		public function updateClick(data:Object):void
		{
			if (data)
			{
				//ExternalInterface.call( "SetTextByID",tF_description,"MMOGame.Title.TitleScript"+data.ID);
				ExternalInterface.call( "TimeDisplay",tF_timeLeft,data.ValidTime);
				tF_description.htmlText =  DESCRIPTION_PREFIX_HTML_TEXT + data.titleScript;
				tF_ability.htmlText 	= data.AttrString;//需要你确认附加属性数据是否会造成多余换行
				tF_restriction.htmlText =  RESTRICTION_PREFIX_HTML_TEXT + data.ConditionString;
				tF_description_mc.visible 	  = (data.titleScript != "");
				tF_ability_mc.visible 		  = (data.AttrString != "");
				tF_restriction_mc.visible 	  = (data.ConditionString != "");
				tF_timeLeft_mc.visible 		  = (tF_timeLeft.text != "");
				updateLayout();
				selectTitleID = data.ID;

				fameImgLoader_mc.source = data.IconName;
				if (fameImgLoader_mc.source != null)
				{
					fameImgLoader_mc.visible = true;
					//tF_currentFame2.text = "";
				}
				else
				{
					fameImgLoader_mc.visible = false;
					//tF_currentFame2.text = data.label;
				}

				star_mc2.gotoAndStop(data.numStar);
				star_mc2.visible = true;
				
				if(TitleTabIndex ==1)
				{
					btn_UseCurrentTitle.visible = true;
					btn_UseCurrentTitle.enabled = true;
				}
				else
				{
					btn_UseCurrentTitle.visible = false;
				}
				//btn_UseCurrentTitle.enabled = (data.obtained && data.isCurrent==false);
				data_divide_mc.visible = true;
			}
			else
			{
				star_mc2.visible = false;
				fameImgLoader_mc.visible = false;
				btn_UseCurrentTitle.enabled = false;
				data_divide_mc.visible = false;
				tF_description_mc.visible = tF_ability_mc.visible = tF_restriction_mc.visible = tF_timeLeft_mc.visible = false;
//				tF_description.htmlText =  DESCRIPTION_PREFIX_HTML_TEXT + "称号描述详细内容123";
//				tF_ability.htmlText 	= "力量+2";
//				tF_restriction.htmlText =  RESTRICTION_PREFIX_HTML_TEXT + "PK值不能超过150";
//				tF_description_mc.visible 	  = true;
//				tF_ability_mc.visible 		  = true;
//				tF_restriction_mc.visible 	  = false;
//				updateLayout();
			}
		}
		
		private function updateLayout():void
		{
			tF_description.height = tF_description.numLines * TEXT_SINGLE_LINE_HEIGHT;
			var tF_description_mc_height:Number = tF_description_mc.visible ? (tF_description.y + tF_description.height) : MARGIN_DIVIDE;
			
			tF_ability.height = tF_ability.numLines * TEXT_SINGLE_LINE_HEIGHT;
			var tF_ability_mc_height:Number = tF_ability_mc.visible ? (tF_ability.y + tF_ability.height) : MARGIN_DIVIDE;
			tF_ability_mc.y = tF_description_mc.y + tF_description_mc_height - MARGIN_DIVIDE;
			
			tF_restriction.height = tF_restriction.numLines * TEXT_SINGLE_LINE_HEIGHT;
			var tF_restriction_mc_height:Number = tF_restriction_mc.visible ? (tF_restriction.y + tF_restriction.height) : MARGIN_DIVIDE;
			tF_restriction_mc.y = tF_ability_mc.y + tF_ability_mc_height - MARGIN_DIVIDE;
			
			tF_timeLeft_mc.y = tF_restriction_mc.y + tF_restriction_mc_height - MARGIN_DIVIDE;
		}

		public function handleListChange( event:Event ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}

		public function handleListItemClick( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider = targetList.dataProvider as TreeDataProvider;
				if (Provider!=null)
				{
					Provider.handleListItemClick( event );
					Provider.requestItemAt( event.index, updateClick );
				}
				targetList.invalidateData();
			}
			
			var itemRenderer:ListItemRenderer_Fame = event.itemRenderer as ListItemRenderer_Fame;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemClick(TitleTabIndex);
			}

			if (selectTitleID>0)
			{
				ExternalInterface.call( "ASClickTitle", selectTitleID );
			}
		}

		public function handleListItemRollOver(event:ListEvent ):void
		{
			var itemRenderer:ListItemRenderer_Fame = event.itemRenderer as ListItemRenderer_Fame;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemRollOver(event);
			}
		}

		public function handleListItemRollOut(event:ListEvent ):void
		{
			var itemRenderer:ListItemRenderer_Fame = event.itemRenderer as ListItemRenderer_Fame;
			if (itemRenderer != null)
			{
				itemRenderer.handleListItemRollOut(event);
			}
		}

		public function UseCurrentTitle( e:Event ):void
		{
			if (selectTitleID>0)
			{
				ExternalInterface.call( "ASUseCurrentTitle", selectTitleID );
			}
		}

		public function ClearCurrentTitle( e:Event ):void
		{
			ExternalInterface.call( "ASUseCurrentTitle", 0 );
		}

		
		public function onClickTitleTabBtn1(e:MouseEvent):void
		{
			TitleTabIndex = 1;
			selectTitleID=0;
			list_mc.selectedIndex = selectTitleID;
			updateItemsData(TitleData,false);
		}
		public function onClickTitleTabBtn2(e:MouseEvent):void
		{
			TitleTabIndex = 2;
			selectTitleID=0;
			list_mc.selectedIndex = selectTitleID;
			updateItemsData(TitleData,false);
		}
		public function onClickTitleTabBtn3(e:MouseEvent):void
		{
			TitleTabIndex = 3;
			selectTitleID=0;
			list_mc.selectedIndex = selectTitleID;
			updateItemsData(TitleData,false);
		}
		public function onClickTitleTabBtn4(e:MouseEvent):void
		{
			TitleTabIndex = 4;
			selectTitleID=0;
			list_mc.selectedIndex = selectTitleID;
			updateItemsData(TitleData,false);
		}
		public function onClickTitleTabBtn5(e:MouseEvent):void
		{
			TitleTabIndex = 5;
			selectTitleID=0;
			list_mc.selectedIndex = selectTitleID;
			updateItemsData(TitleData,false);
		}		
		
	}
}//testList();