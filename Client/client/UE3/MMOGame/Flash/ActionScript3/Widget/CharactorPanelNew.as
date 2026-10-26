package ActionScript3.Widget
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.MyTipButtonNew;
	import ActionScript3.Charactor.FamePanel;
	import ActionScript3.Charactor.MoneyPanel;
	import ActionScript3.Charactor.ReputationInfoBox;
	import ActionScript3.Common.CustomScrollBar;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.ItemSlot.MyItemSlotComponentIcon;
	import ActionScript3.ItemSlot.MyItemSlotComponentQuality;

	import UI_EquipEnhance.EquipEnhanceAS3.EquipEnhanceNewPanel;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonBarEvent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.IndexEvent;
	import scaleform.clik.events.SliderEvent;
	import UI_CharactorWidget.CharactorWidgetAS3.DetailProperty;
	import scaleform.clik.controls.Button;
	import UI_CharactorWidget.CharactorWidgetAS3.ShowPanel;
	import scaleform.clik.controls.RadioButton;
	
	public class CharactorPanelNew extends MyPanel
	{
		public var tab0_mc:RadioButton;
		public var tab1_mc:RadioButton;
		public var tab2_mc:RadioButton;
		public var tab3_mc:RadioButton;
		public var tab4_mc:RadioButton;

		public var showPanel_mc:ShowPanel;
		public var famePanel_mc:FamePanel;
		public var moneyPanel_mc:MoneyPanel;
		public var EnhancePanel_mc:EquipEnhanceNewPanel;

		const slotNum:int = 14;

		var itemSlot:Array;
		var itemQuality:Array;
		var itemIcon:Array;
		
		public var btn_detail:Button;
		public var panelId:int = 0;

		public var EquipSlotEnhanceInfoMc:MovieClip;

		//战斗力信息
		public var AttributePanel:MovieClip;
		
		const EnumMale:int = 1;
		const EnumFemale:int = 2;
		const EnumWarrior:int = 0;
		const EnumMage:int = 1;
		const EnumAss:int = 2;
		const EnumArch:int = 3;
		const EnumTaoist:int = 4;
		
		var _attributePanelHeight:int;
		var _classTitleRef:Class;
		var _classItemRef:Class;
		var _classTitleRef1:Class;
		var _classItemRef1:Class;

		var mouseItem:MovieClip;
		
		public function updateFameData(Data:Array, bReset:Boolean):void
		{
			famePanel_mc.updateItemsData(Data,bReset);
		}
		
		public function updateMoneyData(Data:Array):void
		{
			moneyPanel_mc.updateMoneyData(Data);
		}		

		private function initAttributePanel():void
		{
			AttributePanel = showPanel_mc.AttributePanel;
			_classTitleRef = getDefinitionByName("AttributeTitle") as Class;
			_classItemRef = getDefinitionByName("AttributeItem") as Class;
			_classTitleRef1=getDefinitionByName("AttributeTitle1") as Class;
			_classItemRef1=getDefinitionByName("AttributeItem1") as Class;
		}
		
		override public function UCGetWidth():int
		{
			return MyWindowsFrame_mc.width;
		}

		override public function UCGetHeight():int
		{
			return super.UCGetHeight();
		}
		
		override protected function configUI():void
		{
			this.ShowMode="BC";
			super.configUI();
			tab0_mc.addEventListener( ButtonEvent.CLICK, ClickTab0 );
			tab1_mc.addEventListener( ButtonEvent.CLICK ,ClickTab1 );
			tab2_mc.addEventListener( ButtonEvent.CLICK ,ClickTab2 );
			tab3_mc.addEventListener( ButtonEvent.CLICK ,ClickTab3 );
			tab4_mc.addEventListener( ButtonEvent.CLICK ,ClickTab4 );
			ClickTab0();

			if (showPanel_mc)
			{
				initAttributePanel();
				showPanel_mc.btn_detail.addEventListener(MouseEvent.CLICK,detailHandler);
				//
				EquipSlotEnhanceInfoMc = showPanel_mc.EquipSlotEnhanceInfoMc;
				if (EquipSlotEnhanceInfoMc)
				{
					showPanel_mc.EquipSlotEnhanceInfoMc.addEventListener( MouseEvent.MOUSE_OVER, onHoverTotalEnhanceProp );
					showPanel_mc.EquipSlotEnhanceInfoMc.addEventListener( MouseEvent.MOUSE_OUT, onMouseOutTotalEnhanceProp );
				}
			
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
			//ExternalInterface.call( "RegisterCharactor", this );
			//test;
			//( itemSlot[6] as MyItemSlot ).SetData( 1 , "Bracelet.png" , 0 , "bb" , 4 , 1 , 1);
			//( itemSlot[14] as MyItemSlot ).SetData( 1 , "Bracelet.png" , 0 , "bb" , 3 , 1 , 1);
//			UpdateBaseInfo( { classText:"职业", levelText:"XX级" , name:"东方不败" , classId:3 , sex:1 } );
//			UpdateBattlePoint( { battlePoint:888,lifePoint:777,damagePoint:666 } );
			//var obj0 = { titleName:"攻击属性", attriList:[{ itemName:"攻击", itemValue:"1"}] };
			//var obj1 = { titleName:"防御属性", attriList:[{ itemName:"防御", itemValue:"1"},{ itemName:"魔法", itemValue:"999"}] };
			//var dat:Array = [obj0,obj0,obj0,obj0,obj0,obj0,obj0,obj0];

			//SetAttributeData(dat);
		}
		
		private function detailHandler(evt:MouseEvent):void
		{
			showPanel_mc.attributeView.visible=!showPanel_mc.attributeView.visible;
			//showPanel_mc.attributeView
		}

        //基础属性
		public function SetAttributeItem( attriData:Object ):void
		{
			if ( AttributePanel && attriData )
			{
				var groupId = attriData.groupId;
				var indexId = attriData.indexId;

				var attrItem:UIComponent = AttributePanel.getChildByName("attriItem"+groupId+":"+indexId) as UIComponent;
				if (attrItem)
				{
					var itemNameTxt:TextField = attrItem.getChildByName("attriName_txt") as TextField;
					if (itemNameTxt)
					{
						itemNameTxt.text = attriData.itemName;
					}
					var itemValueTxt:TextField = attrItem.getChildByName("attriValue_txt") as TextField;
					if (itemValueTxt)
					{
						itemValueTxt.text = attriData.itemValue;
					}
				}

			}
		}
		
		public function updatePlayerHPMP(type:int,v:int, max:int)
		{
			var attrItem:UIComponent;
			
			if(type == 1)
			{
				attrItem = AttributePanel.getChildByName("attriItem"+0+":"+5) as UIComponent;
			}
			else
			{
				attrItem = AttributePanel.getChildByName("attriItem"+0+":"+6) as UIComponent;
			}
			
			if(attrItem)
			{
				var itemValueTxt:TextField = attrItem.getChildByName("attriValue_txt") as TextField;
				if (itemValueTxt)
				{
					itemValueTxt.text = v.toString() + "/" + max.toString();
					
					if(mouseItem)
					{
						ExternalInterface.call( "ASShowTips_Attribute" , mouseItem );
					}
				}
				
			}
			
		}

		public function SetAttributeData( attriData:Array ):void
		{
			var i:int=0;
			var j:int=0;
			var l:int=attriData.length;
			if (AttributePanel)
			{
				_attributePanelHeight=0;
				updateBaseAttribute(attriData[0],AttributePanel);//基础属性
//				clearAttributePanel();
//				_attributePanelHeight=0;
//				updateAttribute(attriData[0],0,AttributePanel);//攻击属性 数组第一条为攻击属性
			}
			if(showPanel_mc.attributeView.list.AttributeContent){
				_attributePanelHeight=0;
				//showPanel_mc.attributeView.list.AttributeContent.clear();
				for (i= 1; i < l; i++){
					updateDetailAttribute(attriData[i],i,showPanel_mc.attributeView.list.AttributeContent);
					//updateAttribute(attriData[i],i,showPanel_mc.attributeView.list.AttributeContent);
				}
				//if(_attributePanelHeight>0){
					showPanel_mc.attributeView.list.AttributeContent.height = _attributePanelHeight;
					showPanel_mc.attributeView.list.update();
				//}
			}
		}
		
		private function clearAttributePanel():void
		{
			var i:int=0;
			var l:int=l;
			while(AttributePanel.numChildren > 0 )
			{
				AttributePanel.removeChildAt(0);
			}
			//for(i=0;i<l;i++){
				//AttributePanel.removeChildAt(0);
			//}
		}
		
		private function updateBaseAttribute(obj:Object,mc:MovieClip):void
		{
			var titleName:String = obj.titleName;
			var attrTitle:MovieClip = mc.getChildByName("MtitleName") as MovieClip;
			if(attrTitle==null)
			{
				attrTitle =new _classTitleRef;//new AttributeTitle;
				attrTitle.name = "MtitleName";
				mc.addChild( attrTitle );
				attrTitle.x = 0;
				attrTitle.y = _attributePanelHeight;
			}
			
			_attributePanelHeight +=  attrTitle.height;
			var titleNameTxt:TextField = attrTitle.getChildByName("name_txt") as TextField;
			titleNameTxt.text = titleName;							
			var attriList:Array = obj.attriList;
			var l:int=attriList.length;
			var j:int=0;
			for(j=0;j<l;j++)
			{
				var itemName:String = attriList[j].itemName;
				var attrItem:MovieClip =  mc.getChildByName("MClassItemName"+j) as MovieClip;
				if(attrItem==null)
				{
					attrItem= new _classItemRef;//new AttributeItem;
					attrItem.name = "MClassItemName"+j;
					attrItem.addEventListener( MouseEvent.MOUSE_OVER , showAttributeTips );
					attrItem.addEventListener( MouseEvent.MOUSE_OUT, hideAttributeTips);					
					mc.addChild( attrItem );
					attrItem.x = 0;					
				}
				attrItem.itemdataid = 0;
				attrItem.itemid = j;
				attrItem.iteminfoid = panelId;	
				attrItem.y = _attributePanelHeight;
				_attributePanelHeight +=  attrItem.height;
				var itemNameTxt:TextField = attrItem.getChildByName("attriName_txt") as TextField;
				itemNameTxt.mouseEnabled=false;
				itemNameTxt.htmlText = itemName;
				var itemValueTxt:TextField = attrItem.getChildByName("attriValue_txt") as TextField;
				itemValueTxt.mouseEnabled=false;
				itemValueTxt.htmlText = attriList[j].itemValue;					
			}
		}		
		
		
		private function updateDetailAttribute(obj:Object,i:int,mc:MovieClip):void
		{
			var titleName:String = obj.titleName;
			var attrTitle:MovieClip = mc.getChildByName("titleName"+i) as MovieClip;
			if(attrTitle==null)
			{
				attrTitle = new _classTitleRef1;//new AttributeTitle1;
				attrTitle.name = "titleName"+i;
				mc.addChild( attrTitle );
				attrTitle.x = 0;
				attrTitle.y = _attributePanelHeight;
			}
			var titleNameTxt:TextField = attrTitle.getChildByName("name_txt") as TextField;
			titleNameTxt.text = titleName;							
			_attributePanelHeight +=  attrTitle.height;
			var attriList:Array = obj.attriList;
			var l:int=attriList.length;
			var j:int=0;
			for(j=0;j<l;j++)
			{
				var itemName:String = attriList[j].itemName;
				var attrItem:MovieClip =  mc.getChildByName("attributeItem_"+i.toString()+j) as MovieClip;
				if(attrItem==null)
				{
					attrItem= new _classItemRef1; //new AttributeItem1;
					attrItem.name = "attributeItem_"+i.toString()+j;
					attrItem.addEventListener( MouseEvent.MOUSE_OVER , showAttributeTips );
					attrItem.addEventListener( MouseEvent.MOUSE_OUT, hideAttributeTips);					
					mc.addChild( attrItem );
					attrItem.x = 0;
				}
				attrItem.itemdataid = i;
				attrItem.itemid = j;
				attrItem.iteminfoid = panelId;	
				attrItem.y = _attributePanelHeight;
				var itemNameTxt:TextField = attrItem.getChildByName("attriName_txt") as TextField;
				itemNameTxt.mouseEnabled=false;
				itemNameTxt.htmlText = itemName;
				_attributePanelHeight +=  21;
				
				var itemValueTxt:TextField = attrItem.getChildByName("attriValue_txt") as TextField;
				itemValueTxt.mouseEnabled=false;
				itemValueTxt.htmlText = attriList[j].itemValue;
			}
			_attributePanelHeight+=8;
		}				
		
		private function updateAttribute(obj:Object,i:int,mc:MovieClip):void
		{
			showPanel_mc.attributeView.list.clear();
			var attrTitle:MovieClip;
			if(i==0){
				attrTitle= new _classTitleRef ;
			}else{
				attrTitle= new _classTitleRef1;
			}
			attrTitle.name = "attriTitle" + i;
			mc.addChild( attrTitle );
			attrTitle.x = 0;
			attrTitle.y = _attributePanelHeight;
			if(i==0){
				_attributePanelHeight +=  attrTitle.height;
			}else{
				_attributePanelHeight +=  28;
			}
			
			var titleNameTxt:TextField = attrTitle.getChildByName("name_txt") as TextField;
			titleNameTxt.text = obj.titleName;
			
			var attriList:Array = obj.attriList;
			var l:int=attriList.length;
			var j:int=0;
			for(j=0;j<l;j++){
				var attrItem:MovieClip;
				if(i==0){
					attrItem= new _classItemRef;
					attrItem.y = _attributePanelHeight;
					_attributePanelHeight +=  attrItem.height;
				}else{
					attrItem= new _classItemRef1;
					attrItem.y = _attributePanelHeight;
					_attributePanelHeight +=  21;
					if(j==(l-1)){
						_attributePanelHeight+=8;
					}
				}
				attrItem.name = "attriItem" + i + ":" + j;
				attrItem.addEventListener( MouseEvent.MOUSE_OVER , showAttributeTips );
				attrItem.addEventListener( MouseEvent.MOUSE_OUT, hideAttributeTips);
				mc.addChild( attrItem );
				attrItem.x = 0;
				//attrItem.y = _attributePanelHeight;
				
				attrItem.itemdataid = i;
				attrItem.itemid = j;
				attrItem.iteminfoid = panelId;
				var itemNameTxt:TextField = attrItem.getChildByName("attriName_txt") as TextField;
				itemNameTxt.mouseEnabled=false;
				itemNameTxt.htmlText = attriList[j].itemName;
				
				var itemValueTxt:TextField = attrItem.getChildByName("attriValue_txt") as TextField;
				itemValueTxt.mouseEnabled=false;
				itemValueTxt.htmlText = attriList[j].itemValue;
			}
		}

		private function showAttributeTips( e:MouseEvent ):void
		{
			var item:MovieClip = e.target as MovieClip;
			mouseItem = item;
			if (item)
			{
				ExternalInterface.call( "ASShowTips_Attribute" , item );
			}

		}

		private function hideAttributeTips( e:MouseEvent ):void
		{
			mouseItem = null;
			ExternalInterface.call( "ASHideTips_Attribute" );
		}

		public function UpdateBaseInfo( tData:Object ):void
		{
			if ( tData)
			{
				SetWindowTitle(tData.name);
				var frame:int= tData.classId +1;
				showPanel_mc.UpdateBaseInfo(tData.classText,tData.levelText,frame);
			}
		}

		public function SetPanelText( tData:Object ):void
		{
			if ( tData){
				showPanel_mc.SetPanelText(tData.battlePointTips);
	            panelId = tData.panelId;
			}
		}
		
		public function UpdateBattlePoint( tData:Object ):void
		{
			if ( tData)
			{
				showPanel_mc.UpdateBattlePoint(tData.battlePoint);
			}
		}

		function TurnLeft():void
		{
			ExternalInterface.call("TurnPress",true);
		}
		function TurnRight():void
		{
			ExternalInterface.call("TurnPress",false);
		}
		function TurnRelease():void
		{
			ExternalInterface.call("TurnRelease");
		}

		override public function set visible(value:Boolean):void
		{
			super.visible = value;
			showPanel_mc.attributeView.list.clear();
		}
		
		private function hide():void
		{
			showPanel_mc.visible = false;
			famePanel_mc.visible = false;
			moneyPanel_mc.visible = false;
			EnhancePanel_mc.visible = false;
		}

		public function ClickTab0():void
		{
			tab0_mc.selected = true;
			hide();
			showPanel_mc.visible = true;
			ExternalInterface.call("ASCharactorTab",0 );
		}
		public function ClickTab1():void
		{
			tab1_mc.selected = true;
			hide();
			ExternalInterface.call("ASCharactorTab",1 );
			ExternalInterface.call("ASShowTraceReputationInfoPanel");
			
		}
		public function ClickTab2():void
		{
			tab2_mc.selected = true;
			hide();
			famePanel_mc.visible = true;
			invalidateSize();
			ExternalInterface.call("ASCharactorTab",2 );
		}
		public function ClickTab3():void
		{
			tab3_mc.selected = true;
			hide();
			moneyPanel_mc.visible = true;
			ExternalInterface.call("ASCharactorTab",3 );
		}
		public function ClickTab4():void
		{
			tab4_mc.selected = true;
			hide();
			EnhancePanel_mc.visible = true;
			ExternalInterface.call("ASCharactorTab",4 );
		}
		//
		public function onHoverTotalEnhanceProp( e:Event ):void
		{
			if(EnhancePanel_mc.visible)
				ExternalInterface.call( "ASShowTotalEnhancProp" );
		}
		
		//
		public function onMouseOutTotalEnhanceProp( e:Event ):void
		{
			if(EnhancePanel_mc.visible)
				ExternalInterface.call( "ASHideTotalEnhancProp" );
		}
		
		public function UpdateDetailPanel( tData:Object ):void
		{
			if( EnhancePanel_mc )
			{
				EnhancePanel_mc.UpdateDetailPanel( tData );
			}
			
		}
		public function UpdateSummaryPanel( tData:Object ):void
		{
			if( EnhancePanel_mc )
			{
				EnhancePanel_mc.UpdateSummaryPanel( tData );
			}
		}
		
		public function UCUpdateTabClicked():void
		{
			tab0_mc.selected = true;
		}
		
	    public function UCUpdateCheckBoxSelect(bool:Boolean):void
		{
			showPanel_mc.UpdateCheckBoxSelect(bool);
		}
	}
}