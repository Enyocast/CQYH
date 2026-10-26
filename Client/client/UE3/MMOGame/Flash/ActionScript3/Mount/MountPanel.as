package ActionScript3.Mount
{
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.CustomScrollBar;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;

	public class MountPanel extends MyPanel
	{
		//locale
		private static const LABLE_EQUIP:String = "召唤";
		private static const LABLE_UNEQUIP:String = "收起";
		
		public var classes_list_mc:ScrollingList;
		public var SlotView_mc:ScrollingView;
		public var displayPanel_mc:SlotView;
		public var MyScrollBar_mc:CustomScrollBar;
		
		public var equip_btn:Button;

		public function MountPanel()
		{
			super();
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			equip_btn.label = LABLE_EQUIP;
			equip_btn.enabled = false;
			SetWindowTitle("坐骑");//locale
			classes_list_mc.selectedIndex = 0;
			classes_list_mc.addEventListener(ListEvent.INDEX_CHANGE, handleListChange, false, 0, true);
			classes_list_mc.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
			
			equip_btn.addEventListener("click", handleEquip, false ,0, true);
			ShowMode =  ConfigConstants.PANEL_SHOW_MODE_BC;
			ExternalInterface.call( "RegisterMount", this );
			//测试数据;

			InitTestListData();
		//	InitTestMountData(100);
			SlotView_mc.updateScrollBar();
			
		}

		function handleEquip( event:Event ):void
		{
			if(equip_btn.label == LABLE_EQUIP){
				//equip_btn.label = LABLE_UNEQUIP;
				ExternalInterface.call("ASEquipMount",displayPanel_mc.selectSlot);
				//test
				//SetEquipedMount(displayPanel_mc.selectSlot);
			}else if(equip_btn.label == LABLE_UNEQUIP){
				equip_btn.label = LABLE_EQUIP;
				ExternalInterface.call("ASUnEquipMount");
			}
		}

		function handleListChange( event:Event ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}

		function handleListItemClick(event:ListEvent):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				var Provider:TreeDataProvider = targetList.dataProvider as TreeDataProvider;
				if (Provider!=null)
				{
					Provider.handleListItemClick( event );
					var obj:MountClassesListData = Provider.requestItemAt(event.index) as MountClassesListData;
					displayPanel_mc.UpdateClass( obj.colletionType, obj.classesQuality,obj.classesQuality , obj.classesLevelMin ,obj.classesLevelMax );
					
					if (obj.type > 0)
					{
						MyScrollBar_mc.position = 0;
						SlotView_mc.updateScrollBar();
					}

				}
				targetList.invalidateData();
				
			}
		}
		
		public function UpdateMount(data:Array ):void
		{
			trace("=====================UpdateMount(data:Array )");
			if(data && displayPanel_mc !=null)
			{
				displayPanel_mc.UpdateMount(data);
			}
			SlotView_mc.displayMc = displayPanel_mc;
			SlotView_mc.updateScrollBar();
		}

		public function SetEquipedMount(slotID:int):void
		{
			//trace("---------------------------->SetEquipedMount slotID:　", slotID);
			if(displayPanel_mc!=null){
				displayPanel_mc.curEquipedSlot = slotID;
				
				if(slotID>0)
				{
					equip_btn.enabled = true;
					if(displayPanel_mc.curEquipedSlot!=displayPanel_mc.selectSlot)
					{
						equip_btn.label = LABLE_EQUIP;
					}
					else
					{
						equip_btn.label = LABLE_UNEQUIP;
					}
				}
			}
		}
		
		public function SelectMount(slotID:int):void
		{
			if(displayPanel_mc!=null){
				displayPanel_mc.SelectMount(slotID);
				
				if(displayPanel_mc.selectSlot>0)
				{
					equip_btn.enabled = true;
					if(displayPanel_mc.curEquipedSlot!=displayPanel_mc.selectSlot)
					{
						equip_btn.label = LABLE_EQUIP;
					}
					else
					{
						equip_btn.label = LABLE_UNEQUIP;
					}
				}
				else{
					equip_btn.enabled = false;
				}
			}
		}

		public function UpdateClassesData( data:Array ):void
		{
			if (data && classes_list_mc != null)
			{
				classes_list_mc.dataProvider = new TreeDataProvider(data);
				classes_list_mc.validateNow();
				classes_list_mc.invalidateData();
			}
			else
			{
				trace("UpdateClassesData failed!");
			}
		}

		private function AddListData(itemsData:Array,labelStr:String, type:int, deepth:int,index:int,colletionType:int,classesQuality:int,classesLevelMin:int,classesLevelMax:int, visibleFlag:Boolean ):void
		{
			var dataAdd:MountClassesListData = new MountClassesListData  ;
			//var dataAdd:Object = new Object  ;
			dataAdd.index = index;
			dataAdd.type = type;
			dataAdd.deepth = deepth;
			dataAdd.visible = visibleFlag;
			dataAdd.label = labelStr;
			
			dataAdd.colletionType	= colletionType;
			dataAdd.classesQuality 	= classesQuality;
			dataAdd.classesLevelMin = classesLevelMin;
			dataAdd.classesLevelMax = classesLevelMax;
			itemsData.push(dataAdd);
		}

		private function InitTestListData():void
		{
			var itemsData:Array = new Array();
			var i=1;
//			AddListData(itemsData,"全部坐骑", 2, 0,i++, 0, 0, 0, 100,true);
//			AddListData(itemsData,"20级", 0, 1,i++, 0, 0, 0, 20,true);
//			AddListData(itemsData,"30级", 0, 1,i++, 0, 0, 0, 30,true);
//			AddListData(itemsData,"40级", 0, 1,i++, 0, 0, 0, 40,true);
//			
//			AddListData(itemsData,"已有坐骑", 1, 0,i++, 2, 0, 0, 100,true);
//			AddListData(itemsData,"20级", 0, 1,i++, 2, 0, 0, 20,true);
//			AddListData(itemsData,"30级", 0, 1,i++, 2, 0, 0, 30,true);
//			AddListData(itemsData,"40级", 0, 1,i++, 2, 0, 0, 40,true);

			//itemsData:Array,labelStr:String, type:int, deepth:int,index:int,colletionType:int,classesQuality:int,classesLevelMin:int,classesLevelMax:int, visibleFlag:Boolean 
			AddListData(itemsData,"全部坐骑", 2, 0,i++, 0, 0, 0, 100,true);
			AddListData(itemsData,"普通坐骑", 2, 1,i++, 0, 1, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 0, 1, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 0, 1, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 0, 1, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 0, 1, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 0, 1, 0, 60,true);
			AddListData(itemsData,"优秀坐骑", 2, 1,i++, 0, 2, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 0, 2, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 0, 2, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 0, 2, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 0, 2, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 0, 2, 0, 60,true);
			AddListData(itemsData,"珍稀坐骑", 2, 1,i++, 0, 3, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 0, 3, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 0, 3, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 0, 3, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 0, 3, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 0, 3, 0, 60,true);
			AddListData(itemsData,"极品坐骑", 2, 1,i++, 0, 4, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 0, 4, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 0, 4, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 0, 4, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 0, 4, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 0, 4, 0, 60,true);
			
			AddListData(itemsData,"可用坐骑", 1, 0,i++, 1, 0, 0, 100,true);
			AddListData(itemsData,"普通坐骑", 2, 1,i++, 1, 1, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 1, 1, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 1, 1, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 1, 1, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 1, 1, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 1, 1, 0, 60,true);
			AddListData(itemsData,"优秀坐骑", 2, 1,i++, 1, 2, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 1, 2, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 1, 2, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 1, 2, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 1, 2, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 1, 2, 0, 60,true);
			AddListData(itemsData,"珍稀坐骑", 2, 1,i++, 1, 3, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 1, 3, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 1, 3, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 1, 3, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 1, 3, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 1, 3, 0, 60,true);
			AddListData(itemsData,"极品坐骑", 2, 1,i++, 1, 4, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 1, 4, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 1, 4, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 1, 4, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 1, 4, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 1, 4, 0, 60,true);
			
			AddListData(itemsData,"已有坐骑", 1, 0,i++, 2, 0, 0, 100,true);
			AddListData(itemsData,"普通坐骑", 2, 1,i++, 2, 1, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 2, 1, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 2, 1, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 2, 1, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 2, 1, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 2, 1, 0, 60,true);
			AddListData(itemsData,"优秀坐骑", 2, 1,i++, 2, 2, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 2, 2, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 2, 2, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 2, 2, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 2, 2, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 2, 2, 0, 60,true);
			AddListData(itemsData,"珍稀坐骑", 2, 1,i++, 2, 3, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 2, 3, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 2, 3, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 2, 3, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 2, 3, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 2, 3, 0, 60,true);
			AddListData(itemsData,"极品坐骑", 2, 1,i++, 2, 4, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 2, 4, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 2, 4, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 2, 4, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 2, 4, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 2, 4, 0, 60,true);
			
			AddListData(itemsData,"未收集坐骑", 1, 0,i++, 3, 0, 0, 100,true);
			AddListData(itemsData,"普通坐骑", 2, 1,i++, 3, 1, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 3, 1, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 3, 1, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 3, 1, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 3, 1, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 3, 1, 0, 60,true);
			AddListData(itemsData,"优秀坐骑", 2, 1,i++, 3, 2, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 3, 2, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 3, 2, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 3, 2, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 3, 2, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 3, 2, 0, 60,true);
			AddListData(itemsData,"珍稀坐骑", 2, 1,i++, 3, 3, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 3, 3, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 3, 3, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 3, 3, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 3, 3, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 3, 3, 0, 60,true);
			AddListData(itemsData,"极品坐骑", 2, 1,i++, 3, 4, 0, 100,true);
			AddListData(itemsData,"20级", 0, 2,i++, 3, 4, 0, 20,true);
			AddListData(itemsData,"30级", 0, 2,i++, 3, 4, 0, 30,true);
			AddListData(itemsData,"40级", 0, 2,i++, 3, 4, 0, 40,true);
			AddListData(itemsData,"50级", 0, 2,i++, 3, 4, 0, 50,true);
			AddListData(itemsData,"60级", 0, 2,i++, 3, 4, 0, 60,true);

			UpdateClassesData(itemsData);
		}
		
		public function InitTestMountData( num:int ):void
		{
			var w:int = 64;
			var h:int = 96;
			width 	= 6*w;
			height 	= Math.floor(num/6+1)*h;


			var dataList:Array = new Array;
			for (var i:int=0; i<num; i++)
			{
				var MountData:MountSlotData = new MountSlotData();
				
				MountData.posX = Math.floor(i%6)*w;
				MountData.posY = Math.floor(i/6)*h;
				
				MountData.Have		 = i%2;
				MountData.IsEnable    = MountData.Have;
				MountData.isLocked 	  = false;//MountData.Have;	
				MountData.isUnusable  = false;
				MountData.classesLevel   = i;
				MountData.classesQuality = i%4+1;
				MountData.slotName = "ID_" + i+"Q_"+MountData.classesQuality;
				MountData.iconName = "1.TGA";
				
				dataList.push(MountData);
			}

			UpdateMount(dataList);
		}		

	}

}