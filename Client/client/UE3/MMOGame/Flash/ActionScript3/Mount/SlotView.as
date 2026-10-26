package ActionScript3.Mount
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.ItemSlotData;
	import ActionScript3.MyPanel;
	import ActionScript3.TreeListData;
	import ActionScript3.Mount.MountSlot;
	import ActionScript3.Mount.MountSlotData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.interfaces.IDataProvider;


	public class SlotView extends UIComponent
	{
		private static const SLOT_WIDTH:Number = 88;
		private static const SLOT_HEIGHT:Number = 96;
		private static const SLOT_OFFSET_X:Number = 10;
		
		private var m_cType:int = 0;
		private var m_classesQualityMin:int=0;
		private var m_classesQualityMax:int=0;
		private var m_classesLevelMin:int=0;
		private var m_classesLevelMax:int=99;
		
		public var selectSlot:int = -1;
		public var curEquipedSlot:int = -1;
		public var slotList:Array = new Array;
		public function SlotView()
		{
			super();
			// constructor code
		}

		override protected function configUI():void
		{

			super.configUI();
		}
		
		public function SelectMount(slotID:int):void
		{
			ExternalInterface.call("ASTrace","SelectMount1:slotID="+slotID);
			selectSlot = -1;
			for ( var i:int =0; i<slotList.length; i++)
			{
				var SlotData:MountSlotData = slotList[i].BaseSlot_mc.SlotData as MountSlotData;
				
				if (SlotData && SlotData.slotID == slotID )
				{
					if(SlotData.isLocked==false && SlotData.isUnusable==false)
					{
						ExternalInterface.call("ASTrace","SelectMount2:slotID="+slotID);
						slotList[i].BaseSlot_mc.selected = true;
						selectSlot = slotID;
					}
					else
					{
						slotList[i].BaseSlot_mc.selected = false;						
					}
				}
				else{
					slotList[i].BaseSlot_mc.selected = false;
				}
			}			
		}
		
		
		public function UpdateMount(data:Array ):void
		{
			var i:int = 0;
			var w:int = SLOT_WIDTH;
			var h:int = SLOT_HEIGHT;
			var LineNum = 4;
			width 	= SLOT_OFFSET_X + LineNum*w;
			height 	= (Math.ceil(data.length/LineNum) - 1) * h;			
			for ( i=0; i<slotList.length; i++)
			{
				var dataAdd:MountSlot = slotList[i] as MountSlot;
				if (dataAdd)
				{
					removeChild(dataAdd);
				}
			}
			if(slotList.length>0)slotList.splice(0);
			trace("SlotView data.length="+data.length);			
			for ( i=0; i<data.length; i++)
			{
			//	trace("SlotView UpdateMount="+data[i]);
				var MountData:MountSlotData = data[i];
				if (MountData)
				{					
					var SlotAdd:MountSlot = new MountSlot();
					if(SlotAdd)
					{
						SlotAdd.x = Math.floor(i%LineNum)*w + SLOT_OFFSET_X;
						SlotAdd.y = Math.floor(i/LineNum)*h;
				
						SlotAdd.Have		   = MountData.Have;
						SlotAdd.classesLevel   = MountData.classesLevel;
						SlotAdd.classesQuality = MountData.classesQuality;
				
					//	SlotAdd.BaseSlotName_txt.text = MountData.slotName;
						
						SlotAdd.BaseSlot_mc.SetDataObj(MountData);
//						SlotAdd.BaseSlot_mc.tipsHtml = MountData.tipsHtml;
//						
//						SlotAdd.BaseSlot_mc.isSlotLocked = (MountData.Have==0);
//						SlotAdd.BaseSlot_mc.isSlotUnusable = !MountData.IsEnable ;
						
						
						
						
						
						
						
						if(MountData.Have==0)
						{
							SlotAdd.isSlotLocked = true;
							//SlotAdd.BaseSlot_mc.isSlotLocked = true;							
						}
						else if(MountData.IsEnable==false)
						{
							SlotAdd.isSlotUnusable = true;
							//SlotAdd.BaseSlot_mc.isSlotUnusable = true;
						}
						else{
							SlotAdd.isSlotLocked = false;
							SlotAdd.isSlotUnusable = false;
							//SlotAdd.BaseSlot_mc.isSlotLocked = false;														
							//SlotAdd.BaseSlot_mc.isSlotUnusable = false;							
						}						
						
						slotList.push(SlotAdd);
						addChild(SlotAdd);
						SlotAdd.visible = true;

					}
				}
			}
			
			RefreshClass();
		}

		public function RefreshClass():void
		{
			UpdateClass(m_cType,m_classesQualityMin,m_classesQualityMax,m_classesLevelMin,m_classesLevelMax );
		}
		
		public function UpdateClass( cType:int,classesQualityMin:int,classesQualityMax:int,classesLevelMin:int,classesLevelMax:int ):void
		{
			m_cType = cType;
			m_classesQualityMin = classesQualityMin;
			m_classesQualityMax = classesQualityMax;
			m_classesLevelMin	= classesLevelMin;
			m_classesLevelMax	= classesLevelMax;

		
			var w:int = SLOT_WIDTH;
			var h:int = SLOT_HEIGHT;			
			var index:int =0;
			var LineNum:int = 4;
			if(classesQualityMax==0)
			{
				classesQualityMin = 0;
				classesQualityMax = 4;
			}
			for (var i:int=0; i<slotList.length; i++)
			{
				var dataAdd:MountSlot = slotList[i] as MountSlot;
				if (dataAdd)
				{
					index = dataAdd.UpdateSlotView( index,cType,classesQualityMin,classesQualityMax,classesLevelMin,classesLevelMax );
					
					//dataAdd.BaseSlot_mc.isSlotLocked = true;														
					//dataAdd.BaseSlot_mc.isSlotUnusable = true;							
				}
			}

			width 	= SLOT_OFFSET_X + LineNum*w;
			height 	= (Math.ceil(index/LineNum) - 1) * h;	

		}

	}

}