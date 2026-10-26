
package ActionScript3 {

	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.Label;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.ItemSlotData;
	import scaleform.gfx.MouseEventEx;
	import scaleform.clik.events.ButtonEvent;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Tips.MyTooltips;
	import flash.external.ExternalInterface;

	public class MyItemSlotShow extends Button
	{

		//public var ItemText:Label;
		public var itemSlotIcon:MyIconConponent;
		//Data
		[Inspectable(type="Number", name="_SlotType")]
		public var SlotType = 8;
		//
		public var EquipID = 0;
		//
		public var ItemQuantity:Number = 1;
		public var ItemTemplateID:Number = -1;
		public var ItemIconName:String = "";
		public var ItemColor:Number = 0;
		public var ItemContainerID:Number = -1;
		public var ItemContainerSlotID:Number = -1;
		
		
		var bOver = false;
		//function
		override protected function configUI():void
		{

			super.configUI();

			this.addEventListener("rollOver",RollOver ); //mouse in
			this.addEventListener("rollOut",RollOut );	//mouse out
			//
			//this.addEventListener(MouseEvent.CLICK , MouseRightClick );

		}
		//tips
		public function RollOver( e:Event  )
		{
			//var targIcon:MyItemSlot = Extensions.getMouseTopMostEntity() as MyItemSlotShow;
			
			if( ItemTemplateID >= 0 )
			{
				//ExternalInterface.call("ASTrace", "============== Mouse RollOver" + this + " -> " + Extensions.getMouseTopMostEntity() + " ==== " + targIcon );			
				ExternalInterface.call("ASShowTips_AwardIcon", this );//代码里把tips.visible设true
			
			}
			
			return;
		}
		//
		public function RollOut( e:Event  )
		{
			ExternalInterface.call("ASTrace", "============== Mouse RollOut" + this);
			
			bOver = true;
			ExternalInterface.call("ASHideTips_AwardIcon",this );
			ExternalInterface.call("ASHideTips");
		}
		//
		public function SetData( quantity:Number , iconName:String , itemID:int, itemColor:int, containerID:int, slotID:int )
		{		
			ItemQuantity 			= quantity;
			ItemTemplateID 			= itemID;
			ItemIconName 			= iconName;
			ItemColor 				= itemColor;
			ItemContainerID 		= containerID;
			ItemContainerSlotID 	= slotID;
			
			UpdateData();
		}
		//
		private function UpdateData():void
		{
			itemSlotIcon.slotIcon_bg_mc.gotoAndStop(1); //reset default frame
			if( ItemIconName == "" ){
				if(itemSlotIcon != null && itemSlotIcon.IconLoader_mc)
					itemSlotIcon.IconLoader_mc.source = "img://MMO_UIIcon.icon.blank";
			}
			else{
				if(itemSlotIcon != null && itemSlotIcon.IconLoader_mc){
					itemSlotIcon.IconLoader_mc.source = "img://"+ItemIconName;
					
					if( ItemColor > 0 ){
						itemSlotIcon.slotIcon_bg_mc.gotoAndStop(ItemIconName);
					}//
				}//if
			}//else
		}
		/*
		public function SetData( quantity:Number , iconName:String , itemID:int, itemColor:int, containerID:int, slotID:int )
		{		
			if( !_ItemData ){
				_ItemData = new ItemSlotData;
			}
			_ItemData.quantity = quantity;
			//_ItemData.itemtype = itemtype;
			_ItemData.itemIndex = itemID;
			_ItemData.iconName = iconName;
			_ItemData.itemColor = itemColor;
			_ItemData.containerID = containerID;
			_ItemData.slotID = slotID;
			
			UpdateData();
		}
		//
		private function UpdateData():void
		{
			itemSlotIcon.slotIcon_bg_mc.gotoAndStop(1); //reset default frame
			if( !_ItemData ){
				_ItemData = new ItemSlotData;
			}
			if( _ItemData.iconName == "" ){
				if(itemSlotIcon != null && itemSlotIcon.IconLoader_mc)
					itemSlotIcon.IconLoader_mc.source = "img://MMO_UIIcon.icon.blank";
			}
			else if(_ItemData.itemtype == "skill" || SlotType == 3){
				//SkillPanel 只有技能
				if(itemSlotIcon != null && itemSlotIcon.IconLoader_mc)
					itemSlotIcon.IconLoader_mc.source = "img://"+_ItemData.iconName;
			}
			else{
				if(itemSlotIcon != null && itemSlotIcon.IconLoader_mc){
					itemSlotIcon.IconLoader_mc.source = "img://"+_ItemData.iconName;
					
					//ExternalInterface.call( "ASTrace", "SlotShow func Update"+itemSlotIcon.IconLoader_mc.source );
					
					if(_ItemData.itemColor > 0){
						itemSlotIcon.slotIcon_bg_mc.gotoAndStop(_ItemData.itemColor);
					}//
				}//if
			}//else
			//ItemText.text = ( (_ItemData.quantity == 1||_ItemData.quantity == 0) ? "" : String(_ItemData.quantity) );	
		}
		//
		public function set ItemData( value:ItemSlotData ):void {
			_ItemData = value;

			UpdateData();
		}
		*/
	};//end of class
}