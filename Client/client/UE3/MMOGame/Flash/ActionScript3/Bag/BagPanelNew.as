package ActionScript3.Bag
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import ActionScript3.Widget.UWindow;
	import ActionScript3.MyTipButton;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.MyCloseButton;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.filters.ColorMatrixFilter;
	import flash.display.MovieClip;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	import flash.utils.getDefinitionByName;
	import ActionScript3.Widget.MyTipsText;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.GameDispathcher;
	import ActionScript3.Common.Events.ParamEvent;
	import UI_GoldStore.AS.GoldStoreUltils;

	public class BagPanelNew extends MyPanel
	{
		public var money0_gold:TextField;
		public var money0_Silver:TextField;
		public var money1_gold:TextField;
		public var money1_Silver:TextField;
		public var tf_weight:TextField;
		public var txt_Weight:TextField;

		public var SplitButton_mc:MyTipButton;
		public var SortButton_mc:MyTipButton;
		public var SignButton_mc:MyTipButton;
		public var StallButton_mc:MyTipButton;
		//public var IdentifyButton_mc:MyTipButton;

		//public var ExchangeButton:Button;
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		public var tab3_mc:RadioButton;
		public var tab4_mc:RadioButton;
		public var btn_identify:Button;

/*		public var label0_mc:RadioButton;
		public var label1_mc:RadioButton;*/
		public var MoneyChainButton:Button;

		var _sortTimer:Timer;
		var _sortTimeCounter:int;
		
		var money0_mc:MovieClip;
		var money1_mc:MovieClip;
		var money2_mc:MovieClip;
		var money3_mc:MovieClip;

		public var money0tips:MyTipsText;
		public var money1tips:MyTipsText;
		public var weight2tips:MovieClip;
		public var BagGroup_mc:MovieClip;
		public var ExpContainerPanelMc:ExpView;
		public var btn_extend:Button;
		
		var _classSlotRef:Class;

		override protected function configUI():void
		{
			_classSlotRef = getDefinitionByName("ItemSlot") as Class;
            ShowMode="BC";
			super.configUI();

			if (StallButton_mc)
			{
				StallButton_mc.addEventListener(MouseEvent.CLICK,OpenStall );
			}
			if (SortButton_mc)
			{
				SortButton_mc.addEventListener(MouseEvent.CLICK, onSort);
			}
			if (SplitButton_mc)
			{
				SplitButton_mc.addEventListener(MouseEvent.CLICK, onSplitItem);
			}
			if (SignButton_mc)
			{
				SignButton_mc.addEventListener(MouseEvent.CLICK, onSignItem);
			}
			btn_extend.addEventListener(MouseEvent.CLICK,clickHandler);
			ExpContainerPanelMc.visible=false;
			//UCSetExpContainerProgress(100,200);
/*			
			ExchangeButton.addEventListener(MouseEvent.CLICK, onExchange );
			SignButton_mc.addEventListener(MouseEvent.CLICK, onSignItem);
			
			IdentifyButton_mc.addEventListener(MouseEvent.CLICK, onEvaluate );
			MoneyChainButton.addEventListener(MouseEvent.CLICK, onClickMoneyChain );
			MoneyChainButton.toggle = true;
			//ExternalInterface.call( "RegisterBag", this );

			//var slot = new _classSlotRef;
			//slot.x = 28;
			//slot.y = 88;
			//stage.addChild( slot );

			//test;
			//SetPanelText( { tabData:[] , labelData:[ {typeId:0 , text:"a" } ,{typeId:1 , text:"b" } ] } );
			//(this.getChildByName("BagGroup_mc") as Object).slot0_mc.itemSlotIcon.IconLoader_mc.source = "img://back.png";
			//(this.getChildByName("BagGroup_mc") as Object).slot1_mc.itemSlotIcon.IconLoader_mc.source = "img://back.png";
			//
			//UCGraySlot( (this.getChildByName("BagGroup_mc") as Object).slot0_mc , true );
			//UCGraySlot( (this.getChildByName("BagGroup_mc") as Object).slot1_mc , false );
			
			//
			
			//UCHintSlot( 1 , true , false );
/*			var i:int=0;
			var arr:Array=[];
			for(i=0;i<64;i++)
			{
				var obj:BagItemData=new BagItemData();
				obj.containerID=i;
				obj.iconname="1.tga";
				obj.itemColor=1;
				obj.itemindex=1;
				obj.quantity=i;
				obj.slotID=i;
				obj.slotType=1;
				obj.type="slot";
				arr.push(obj);
			}
			updateBagItemData(arr);*/
			
			var guide_mc:MovieClip = BagGroup_mc.getChildByName("_guide_location") as MovieClip;
			if (guide_mc)
			{
				guide_mc.visible = true;
				guide_mc.mouseChildren = false;
				guide_mc.mouseEnabled = false;
			}
			
			weight2tips.addEventListener(MouseEvent.ROLL_OVER, ShowWeightTips);
			weight2tips.addEventListener(MouseEvent.ROLL_OUT,  HideWeightTips);
			
		}
		public function SetPanelText( data:Object )
		{
			if (! data)
			{
				return;
			}
			this.SetWindowTitle(data.titleName);
			var tabArray:Array = data.tabData as Array;
			var i:int = 0;
			for (i = 0; i < tabArray.length; i++)
			{
				var tab:RadioButton = this.getChildByName( "tab"+i+"_mc" ) as RadioButton;
				if (tab)
				{
					tab.itemid = tabArray[i].typeId;
					tab.label = tabArray[i].text;
					tab.addEventListener( ButtonEvent.CLICK , clickTab );
				}
			}

/*			var labelArray:Array = data.labelData as Array;
			for (i = 0; i < labelArray.length; i++)
			{
				var labelButton:RadioButton = this.getChildByName( "label"+i+"_mc" ) as RadioButton;
				if (labelButton)
				{
					labelButton.itemid = labelArray[i].typeId;
					labelButton.label = labelArray[i].text;
					labelButton.addEventListener( ButtonEvent.CLICK , clickLabel );
				}
			}*/

			if (SignButton_mc)
			{
				SignButton_mc.tabCaption = data.signButton;
			}
			/*if (IdentifyButton_mc)
			{
				IdentifyButton_mc.tabCaption = data.identifyButton;
			}*/
			if (SortButton_mc)
			{
				SortButton_mc.tabCaption = data.sortButton;
			}
			if (SplitButton_mc)
			{
				SplitButton_mc.tabCaption = data.splitButton;
			}
			if (StallButton_mc)
			{
				StallButton_mc.tabCaption = data.stallButton;
			}
			if (money0tips)
			{
				money0tips.text = data.tipsMoney0;
			}
			if (money1tips)
			{
				money1tips.text = data.tipsMoney1;
			}
			if(weight2tips)
			{
				weight2tips.text=data.tipsWeight;
			}
		}

		public function SetMoney( data:Object )
		{
			if (money0_gold)
			{
				money0_gold.htmlText = data.moneyString0;
			}
			if (money1_gold)
			{
				var realMoney:String = GoldStoreUltils.couponToGold(data.moneyString1, false);
				var img:String = "<IMG  SRC='img://MMO_UIIcon.MoneyIcon.MoneyBullion'/>";
				money1_gold.htmlText = realMoney + img;
			}
			//if(tf_weight)
			//{
				//tf_weight.htmlText=data.weightString;//设置负重数据
			//}
		}
		
		public function UCSetBagWeight(currentW:int,allW)
		{
			tf_weight.htmlText=currentW + "/" + allW;
			if(currentW > allW)
			{
				tf_weight.textColor = 0xff0000;
				txt_Weight.textColor =  0xff0000;
			}
			else
			{
				tf_weight.textColor = 0xFFEDC5;
				txt_Weight.textColor = 0xFFEDC5;
			}
		}

		function onPageButtonNext():void
		{
			ExternalInterface.call( "ASBagPageNext" );
		}

		function onPageButtonPre():void
		{
			ExternalInterface.call( "ASBagPagePre" );
		}

		override public function UCGetWidth():int
		{
			return this.InfoDragButton_mc.width;
		}

		override public function UCGetHeight():int
		{
			return this.InfoDragButton_mc.height;
		}

		private function clickBagPageTab( e:MouseEvent ):void
		{
			if (e.currentTarget is Button)
			{
				ExternalInterface.call( "ASBagPageChange", ( e.currentTarget as Button ).itemid );
			}
		}

		private function OpenStall(e:MouseEvent):void
		{
			ExternalInterface.call("RequireOpenStall",0);
		}
		
/*		private function clickLabel( e:ButtonEvent):void
		{
			if ( e is ButtonEvent && ( e as ButtonEvent ).buttonIdx == 0 )
			{
				var tab:Button = e.currentTarget as Button;
				if (tab)
				{
					ExternalInterface.call( "ASBagLabelChange" , tab.itemid );
				}
				if ( tab == label0_mc )
				{
					tab0_mc.visible = true;
					tab1_mc.visible = true;
					tab2_mc.visible = true;
					tab3_mc.visible = true;
				}
				else
				{
					tab0_mc.visible = false;
					tab1_mc.visible = false;
					tab2_mc.visible = false;
					tab3_mc.visible = false;
				}

			}
		}*/

		private function clickTab(e:ButtonEvent):void
		{
			if ( e is ButtonEvent && ( e as ButtonEvent ).buttonIdx == 0 )
			{
				var tab:RadioButton = e.currentTarget as RadioButton;
				if (tab)
				{
					ExternalInterface.call( "ASBagTabChange" , tab.itemid );
				}
			}
		}

        private function onSplitItem(evt:MouseEvent):void
		{
			ExternalInterface.call("ASSplitItem");
		}

		private function onSignItem():void
		{
			ExternalInterface.call("ASSignatureItem");
		}

		private function onSort(evt:MouseEvent):void
		{
			ExternalInterface.call("ASSortBag");
			//sound
			playSound("Bag_arrange");
		}

		private function onSortTimer(e:TimerEvent):void
		{
			--_sortTimeCounter;
			updateSortBtnLable();
		}

		function updateSortBtnLable()
		{
			if (_sortTimeCounter <= 0)
			{
				SortButton_mc.label = "整理";
				SortButton_mc.enabled = true;
				_sortTimer.stop();
			}
			else
			{
				SortButton_mc.label = _sortTimeCounter.toString() ;
			}
		}

		//
/*		function onEvaluate():void
		{
			ExternalInterface.call("ASEvaluteItem");
		}*/

		public function UCUpdateSortTimer(secondsLeft:int):void
		{
			SortButton_mc.label =   secondsLeft.toString();
		}

		public function UCEnableSort(e:Boolean, str:String):void
		{
			SortButton_mc.enabled = e;
			SortButton_mc.label = str;
		}

		public function UCGraySlot( mc:MyItemSlot , gray:Boolean ):void
		{
			if (! mc)
			{
				return;
			}
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter()];
			}
			else
			{
				mc.filters = null;
			}
		}
		//
		public function UCHintSlot( slotID:int, isHint:Boolean , isNew:Boolean )
		{
			var slotPanel:MovieClip = this.getChildByName("BagGroup_mc") as MovieClip;
			if( slotPanel == null )
			{
				return;
			}
			var slotAnim:BagSlotAnim = slotPanel.getChildByName("slotAnim" + slotID + "_mc") as BagSlotAnim;
			if( isHint )
			{
				if( slotAnim == null )
				{
					var slotMc:MyItemSlot = slotPanel.getChildByName("slot" + slotID + "_mc") as MyItemSlot;
					if( slotMc == null )
					{
						return;
					}
					slotAnim = new BagSlotAnim;
					
					if( slotAnim == null )
					{
						return;
					}
					
					slotAnim.name = "slotAnim" + slotID + "_mc";
					slotAnim.x = slotMc.x + slotMc.width / 2;
					slotAnim.y = slotMc.y + slotMc.height / 2;
					slotAnim.mouseChildren = false;
					slotAnim.mouseEnabled = false;
					slotPanel.addChild( slotAnim );
				}
				
				//
				slotAnim.visible = true;
				if(isNew)
				{
					slotAnim.powerHint.visible = false;					
					slotAnim.newHint.visible = true;
					slotAnim.newHint.gotoAndPlay( 1 );
				}
				else
				{
					slotAnim.powerHint.visible = true;					
					slotAnim.powerHint.gotoAndPlay( 1 );
					slotAnim.newHint.visible = false;					
				}
				
			}
			else
			{
				if( slotAnim != null )
				{
					slotAnim.visible = false;
				}
			}
		}
		
		public function updateBagItemData(dat:Array):void
		{
			if(dat && dat.length>0)
			{
				var i:int=0;
				for(i=0;i<64;i++)
				{
					var slot:MyItemSlot=BagGroup_mc.getChildByName("slot"+i+"_mc") as MyItemSlot;
					var obj:BagItemData=dat[i];
					if(obj && slot)
					{
						slot.SetSlotType(obj.slotType);
						slot.SetData(obj.quantity,obj.iconname,obj.itemindex,obj.type,obj.itemColor,obj.containerID,obj.slotID);
					}
				}
			}
		}
		public function UCSetExpContainerProgress(min:int,max:int):void
		{
			ExpContainerPanelMc.updateProgress(min,max);
		}
		
		public function UCShowExpContainer(isToShow:Boolean):void
		{
           ExpContainerPanelMc.visible=isToShow;
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExpContainerPanelMc.visible=!ExpContainerPanelMc.visible;
		}
		
		private function ShowWeightTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowBagWeightTips", evt.target);
		}
		
		private function HideWeightTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideBagWeightTips", evt.target);
		}
		
		
	}
}