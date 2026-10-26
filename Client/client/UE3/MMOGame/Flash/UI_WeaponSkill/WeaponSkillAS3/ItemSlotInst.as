package UI_WeaponSkill.WeaponSkillAS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextField;
	import ActionScript3.MyIconConponent;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.ItemSlotData;
	
	public class ItemSlotInst extends Button {
		
		public var itemSlotIcon:MyIconConponent;
		public var itemNum:TextField;
		private var iconName:String="";
		private var itemColor:int;
		public var ItemTemplateID:int;
		public var slotType:int;
		override protected  function configUI():void 
		{
			super.configUI();
			this.addEventListener(MouseEvent.MOUSE_OVER,overHandler);
			this.addEventListener(MouseEvent.MOUSE_OUT,outHandler);
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_ConsumeItem", this);
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_ConsumeItem");
		}
		//minItemNum 需要道具数量 ,myItemNum 我的道具数量
		public function SetData(inItemTemplateID:int,iniconName:String,initemColor:int,inslotType:int):void
		{
			iconName = iniconName;
			itemColor = initemColor;
			ItemTemplateID = inItemTemplateID;
			slotType=inslotType;
			UpdateData();
		}
		
		public function updateItemData(minItemNum:int,myItemNum:int):void
		{
			itemNum.text=minItemNum+"/"+myItemNum;
			if(minItemNum>myItemNum){
				itemNum.textColor=0xFF0000;
			}else{
				itemNum.textColor=0xFFFFFF;
			}
			if(myItemNum==0 && itemSlotIcon){
				this.filters=[StyleType.getInstance().getBlackFilter()];			
			}else{
				this.filters=null;
			}
		}
		
		private function UpdateData():void
		{
			if(itemSlotIcon != null && itemSlotIcon.IconLoader_mc)
			{
				itemSlotIcon.slotIcon_bg_mc.gotoAndStop(1); 
				if( iconName == "" )
			    {
			        itemSlotIcon.IconLoader_mc.source = "img://MMO_UIIcon.icon.blank";
			    }
				else
				{
					itemSlotIcon.IconLoader_mc.source = "img://"+iconName;
					if(itemColor > 0)
					{
						itemSlotIcon.slotIcon_bg_mc.gotoAndStop(itemColor + 1);
					}
				}
			}
		}
	}
	
}
