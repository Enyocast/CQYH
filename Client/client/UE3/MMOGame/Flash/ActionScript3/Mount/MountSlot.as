package ActionScript3.Mount
{
	import flash.display.MovieClip;
	
	import ActionScript3.Slot.MySlot;
	
	import scaleform.clik.core.UIComponent;


	public class MountSlot extends UIComponent
	{
		private static const SLOT_WIDTH:Number = 88;
		private static const SLOT_HEIGHT:Number = 96;
		private static const SLOT_OFFSET_X:Number = 10;
		
		private static const NORMAL_FRAME_LABEL:String = "normal";
		private static const UNUSABLE_FRAME_LABEL:String = "unusable";		
		
		public var BaseSlot_mc:MySlot;
		public var item_slot_frame_mc:MovieClip;
	//	public var BaseSlotName_txt:TextField;
		public var Have:int;
		public var classesLevel:int;
		public var classesQuality:int;
		
		public function MountSlot()
		{
			classesLevel 	= 0;
			classesQuality	= 0;
			Have 			= 0;
		}

		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function UpdateSlotView( index:int,cType:int,classesQualityMin:int,classesQualityMax:int,classesLevelMin:int,classesLevelMax:int ):int
		{
			var bVisible:Boolean = false;
			
			if(classesQuality>=classesQualityMin && classesQuality<=classesQualityMax)
			{
				if(classesLevel>=classesLevelMin && classesLevel<=classesLevelMax)
				{
					if(cType==0)//全部
					{
						bVisible = true;						
					}			
					else if(cType==1 && Have)//可用
					{
						bVisible = true;						
					}
					else if(cType==2 && Have)//已有
					{
						bVisible = true;						
					}
					else if(cType==3 && !Have)
					{
						bVisible = true;					
					}
				}
			}
			//已得到，但是不可用的例子
			if(cType==1 && BaseSlot_mc.SlotData.isUnusable)
			{
				bVisible = false;					
			}
			
			

			if(visible != bVisible)
			{
				visible = bVisible;
			}
			if(bVisible){
				x = Math.floor(index%4) * SLOT_WIDTH + SLOT_OFFSET_X;
				y = Math.floor(index/4) * SLOT_HEIGHT;				
				index++;
			}
			else
			{
				x = 0;
				y = 0;								
			}
			
			
			
			//BaseSlot_mc.isSlotUnusable = BaseSlot_mc.isSlotUnusable;
			//BaseSlot_mc.isSlotLocked = BaseSlot_mc.isSlotLocked;

			
			return index;
		}
		
		//to do show locked image
		public function set isSlotLocked(value):void
		{
			
		}
		
		public function set isSlotUnusable(value):void
		{
			if(value){
				item_slot_frame_mc.gotoAndStop(UNUSABLE_FRAME_LABEL);
			}else{
				item_slot_frame_mc.gotoAndStop(NORMAL_FRAME_LABEL);
			}
		}

	}
}