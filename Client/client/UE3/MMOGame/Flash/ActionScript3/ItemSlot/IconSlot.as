package ActionScript3.ItemSlot
{
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextField;
	//import flash.display.MovieClip;
	import ActionScript3.MyIconConponent;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	public class IconSlot extends UIComponent
	{
		public var _ItemSlot:UILoader;
		public var tf_name:TextField;
		public var ItemTemplateID:int;
		public var SlotType:int;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//
			var showSlotMc:MovieClip;
			showSlotMc = this.getChildByName( "ItemSlot" ) as MovieClip;
			if( showSlotMc is MyIconConponent ){
				_ItemSlot = showSlotMc.getChildByName( "IconLoader_mc" ) as UILoader;
			}
			else if( showSlotMc is UILoader ){
				_ItemSlot = showSlotMc as UILoader;
			}
			//
			addEventListener( MouseEvent.MOUSE_OVER, MouseRollOver );
			addEventListener( MouseEvent.MOUSE_OUT, MouseRollOut );
		}
		//
		public function SetData( iconData:int, slotType:int, iconSource:String, iconName:String )
		{
			ItemTemplateID = iconData;
			SlotType = slotType;
			//
			if( _ItemSlot ){
				if( iconSource ){
					_ItemSlot.source = "img://" + iconSource;
				}
				else{
					_ItemSlot.source = "img://MMO_UIIcon.icon.blank";
				}
			}
			
			//
			if( tf_name ){
				tf_name.text = iconName;
			}
		}
		//
		public function MouseRollOver( evt:Event )
		{
			ExternalInterface.call("ASRollOverItemSlot", this, SlotType, -1, -1 );
		}
		//
		public function MouseRollOut( evt:Event )
		{
			ExternalInterface.call("ASRollOutItemSlot", this );
		}
	}
}