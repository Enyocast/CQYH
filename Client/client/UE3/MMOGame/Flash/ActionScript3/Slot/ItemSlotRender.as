
package ActionScript3.Slot {

	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.UILoader;
	import flash.display.MovieClip;
	import flash.text.TextField;	
	import ActionScript3.Slot.MySlotData;
	import ActionScript3.Slot.ItemSlotData;
	import ActionScript3.Slot.MySlotRender;
	import ActionScript3.Slot.CoolDown;
	import ActionScript3.Common.Utils.StyleType;
	
	public class ItemSlotRender extends MySlotRender
	{	
		public var ItemData:ItemSlotData = null;
		public var IconLoader_mc:UILoader;
		public var IconBackGround_mc:MovieClip;
		
		public var newHint:MovieClip;
		public var unusable_mc:MovieClip;
        public var lock_mc:MovieClip;		
		public var coolDown_mc:MovieClip;
		public var selected_mc:MovieClip;
		
		public var coolDown_tf:TextField; //定义外部使用或摆放的控件，用public
		public var keyBind:TextField;
		public var valueAmount:TextField;		
		public var valueAmount_big:TextField;
		
        public var cd:CoolDown;
		private var _ItemID:Number;
		private var _IsGray:Boolean;
		private var _IconName:String;

		override public function Init():void
		{
			//trace("WWWWWWWWWWWW ItemSlotRender::init");
			super.Init();
			cd = new CoolDown;
			cd.Init();
			_ItemID=0;
			_IsGray=false;
			_IconName="";
			UpdateData();
		}
		
		override public function UnInit():void
		{
			super.UnInit();
			cd.UnInit();
			cd = null;
			_ItemID=0;
			_IsGray=false;
			_IconName="";
			ItemData = null;
		}				
		
		override public function SetDataObj( SlotData:MySlotData ):void
		{
			ItemData = SlotData as ItemSlotData;
			UpdateData();
		}
		
		override public function SetCD(leftMiniSec:int , tolMiniSec:int):void
		{
			if(ItemData)
			{
				ItemData.passedCDMS = tolMiniSec - leftMiniSec;
				ItemData.totleCDMS	= tolMiniSec;
				
				if( cd && ItemData.totleCDMS>0 )
				{
					cd.startCD( ItemData.passedCDMS, ItemData.totleCDMS, renderCD);
				}
				else if(cd && ItemData.totleCDMS==0)
				{
					cd.stopCD(renderCD);
				}
				else
				{
					renderCD();
				}				
			}
		}
		
		override public function UpdateData():void
		{

			UpdateLightData();
		
			if(ItemData!=null && ItemData.HaveData==true )
			{
				if(_IconName !=ItemData.iconName)
				{
					IconLoader_mc.source = ItemData.iconName;
					_IconName = ItemData.iconName;
				}
				
				if(_ItemID != ItemData.itemTemplateID)
				{
					if(ItemData.slotHeight<42)
					{	
						valueAmount.visible = false;
						valueAmount_big.visible = true;
					}
					else
					{
						valueAmount.visible = true;
						valueAmount_big.visible = false;
					}					
					_ItemID = ItemData.itemTemplateID;
				}
				
				if(_IsGray!=ItemData.IsGray)
				{
					if(ItemData.IsGray==true)
					{
						filters = [ StyleType.getInstance().getBlackFilter()];
					}
					else
					{
						filters = null;
					}
					_IsGray=ItemData.IsGray;
				}
				
		
				if( cd && ItemData.totleCDMS>0 )
				{
					cd.startCD( ItemData.passedCDMS, ItemData.totleCDMS, renderCD);
				}
				else
				{
					renderCD();
				}
			}
			else
			{
				filters = null;
				valueAmount.visible = false;
				valueAmount_big.visible = false;
				IconLoader_mc.source = "";
				_ItemID=0;
				_IsGray=false;
				_IconName="";
				if(cd!=null)
				{
					cd.stopCD(renderCD);
				}
				else
				{
					renderCD();
				}
			}

		}
		override public function UpdateLightData():void 
		{
			if(ItemData!=null && ItemData.HaveData==true)
			{
				if(IconBackGround_mc){
					IconBackGround_mc.visible = true;
					IconBackGround_mc.gotoAndStop(ItemData.itemColor+1);
				}
				if(lock_mc)
				{
					lock_mc.visible = ItemData.isLocked;
				}
            	if( unusable_mc )
            	{
                	unusable_mc.visible = ItemData.isUnusable;
            	}
				if( selected_mc )
				{
					selected_mc.visible = ItemData.isSelected;
				}
				if( valueAmount )
				{
					if(ItemData.quantity>0){
						
						
						if(ItemData.quantity>1)
						{
							valueAmount.text = ""+ItemData.quantity;
							valueAmount_big.text = ""+ItemData.quantity;							
						}
						else if(ItemData.quantity==1 && ItemData.maxStackNum>1 )
						{
							valueAmount.text = ""+ItemData.quantity;
							valueAmount_big.text = ""+ItemData.quantity;							
						}
						else
						{
							valueAmount.text = "";
							valueAmount_big.text = "";
						}
					}
					else
					{
						valueAmount.text = "";
						valueAmount_big.text = ""
					}
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
				if( valueAmount )
				{
					valueAmount.text = "";
				}
				if(valueAmount_big )
				{
					valueAmount_big.text = "";
				}
			}			
		}		
		
		
		public function renderCD()		
		{
			if(cd && cd.isCDing())
			{
				var denominator = 237;//遮挡帧数用作分母
				var process = cd.getProcess(denominator);				
				
				coolDown_mc.gotoAndStop(1+process);
				coolDown_mc.visible = true;				
				
				var countDownSec:int = cd.getCountDownSec();
				countDownSec+=1;
				coolDown_tf.visible = true;
				if(countDownSec>=60){
					coolDown_tf.text = String(  Math.floor(countDownSec/60) );
				}
				else
				{
					coolDown_tf.text = String( countDownSec );
				}
				
				//自测试
				if(process==denominator){
					cd.stopCD(renderCD);
				}
			}
			else
			{
				if(coolDown_mc.visible)
				{
					coolDown_mc.gotoAndStop(1);
					coolDown_mc.visible = false;
					coolDown_tf.visible = false;
				}
			}			
		}
		
		
		

	};
}





