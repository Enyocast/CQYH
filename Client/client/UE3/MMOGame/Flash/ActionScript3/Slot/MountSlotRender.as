
package ActionScript3.Slot {

	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.UILoader;
	import flash.display.MovieClip;
	import flash.text.TextField;	
	import ActionScript3.Slot.MySlotData;
	import ActionScript3.Mount.MountSlotData;
	import ActionScript3.Slot.MySlotRender;
	import ActionScript3.Slot.CoolDown;
	import ActionScript3.Common.Utils.StyleType;

	public class MountSlotRender extends MySlotRender
	{	
		public var mountData:MountSlotData;
		public var IconLoader_mc:UILoader;
		public var IconBackGround_mc:MovieClip;
		
		public var newHint:MovieClip;
		public var unusable_mc:MovieClip;
        public var lock_mc:MovieClip;		
		public var selected_mc:MovieClip;


		override public function Init():void
		{
			trace("WWWWWWWWWWWW ItemSlotRender::init");
			super.Init();

			UpdateData();
		}
		
		override public function UnInit():void
		{
			super.UnInit();

			mountData = null;
		}				
		
		
		override public function SetDataObj( SlotData:MySlotData ):void
		{
			mountData = SlotData as MountSlotData;
			UpdateData();
		}

		override public function UpdateData():void
		{
			UpdateLightData();
			if(mountData!=null && mountData.HaveData==true )
			{
				IconLoader_mc.source = mountData.iconName;
				if(mountData.IsGray==true)
				{
					filters = [ StyleType.getInstance().getBlackFilter()];
				}
				else
				{
					filters = null;
				}				
			}
			else
			{
				IconLoader_mc.source = "";
			}
		}
		
		override public function UpdateLightData():void 
		{
			if(mountData!=null && mountData.HaveData==true)
			{
				if(IconBackGround_mc){
					IconBackGround_mc.visible = true;
					IconBackGround_mc.gotoAndStop(mountData.classesQuality+1);
				}				
				if(lock_mc)
				{
					lock_mc.visible = mountData.isLocked;
				}
            	if( unusable_mc )
            	{
                	unusable_mc.visible = mountData.isUnusable;
            	}
				if( selected_mc )
				{
					selected_mc.visible = mountData.isSelected;
				}
			}
			else
			{
				if(IconBackGround_mc){
					IconBackGround_mc.visible = false;
				}				
				if(lock_mc)
				{
					lock_mc.visible = false;
				}
            	if( unusable_mc )
            	{
                	unusable_mc.visible = false;
            	}
				if( selected_mc )
				{
					selected_mc.visible = false;
				}				
			}
		}

		
		
		

	};
}





