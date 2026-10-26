package ActionScript3.Slot {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextField;
	import ActionScript3.Common.Utils.StyleType;
	
	
	public class SkillSlotRender extends MySlotRender {
		
		public var skillData:SkillSlotData = null;
		public var IconLoader_mc:UILoader;
		public var IconBackGround_mc:MovieClip;
		
		public var newHint:MovieClip;
		public var unusable_mc:MovieClip;
        public var lock_mc:MovieClip;		
		public var coolDown_mc:MovieClip;
		public var selected_mc:MovieClip;
		
		public var coolDown_tf:TextField; //定义外部使用或摆放的控件，用public
		public var keyBind:TextField;
		
        public var cd:CoolDown;
		
		override public function Init():void
		{
			super.Init();
			cd = new CoolDown;
			cd.Init();
			UpdateData();
		}
		
		override public function UnInit():void
		{
			super.UnInit();
			cd.UnInit();
			cd = null;
			skillData = null;
		}				
		
		override public function SetDataObj( SlotData:MySlotData ):void
		{
			skillData = SlotData as SkillSlotData;
			UpdateData();
		}
		
		override public function SetCD(leftMiniSec:int , tolMiniSec:int):void
		{
			if(skillData)
			{
				skillData.passedCDMS = tolMiniSec - leftMiniSec;
				skillData.totleCDMS	= tolMiniSec;
				
				if( cd && skillData.totleCDMS>0 )
				{
					cd.startCD( skillData.passedCDMS, skillData.totleCDMS, renderCD);
				}
				else if(cd && skillData.totleCDMS==0)
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
			
			if(skillData!=null && skillData.HaveData==true )
			{

				IconLoader_mc.source = skillData.iconName;
				if(skillData.IsGray==true)
				{
					filters = [ StyleType.getInstance().getBlackFilter()];
				}
				else
				{
					filters = null;
				}

				if( cd && skillData.totleCDMS>0 )
				{
					cd.startCD( skillData.passedCDMS, skillData.totleCDMS, renderCD);
				}
				else
				{
					renderCD();
				}
			}
			else
			{
				IconLoader_mc.source = "";
				if(cd!=null){
					cd.stopCD(renderCD);
				}
				else{
					renderCD();
				}
			}

		}
		override public function UpdateLightData():void 
		{
			if(skillData!=null && skillData.HaveData==true)
			{
				if(IconBackGround_mc){
					IconBackGround_mc.visible = true;
					IconBackGround_mc.gotoAndStop(skillData.itemColor+1);
				}
				if(lock_mc)
				{
					lock_mc.visible = skillData.isLocked;
				}
            	if( unusable_mc )
            	{
                	unusable_mc.visible = skillData.isUnusable;
            	}
				if( selected_mc )
				{
					selected_mc.visible = skillData.isSelected;
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
		
		
		public function renderCD():void
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
				coolDown_mc.gotoAndStop(1);
				coolDown_mc.visible = false;
				coolDown_tf.visible = false;
			}			
		}
	}
	
}
