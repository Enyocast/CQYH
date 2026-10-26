package ActionScript3.ItemSlot
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.UILoader;
	import flash.external.ExternalInterface;
	
	public class MyItemSlotComponentIcon extends MyItemSlotComponent
	{
		public var UILoader_mc:UILoader;
        
		const E_NES_MAIN_HAND:int =0;
		const E_NES_BODY:int=1;
		const E_NES_BACK:int=2;
		const E_NES_HEAD :int =3;
		const E_NES_SHOULDER:int  =4;
		const E_NES_ARM:int=5;
		const E_NES_WAIST:int =6;
		const E_NES_FOOT:int =7;
		const E_NES_NECK:int=8;
		const E_NES_FINGER_L:int =9;
		const E_NES_FINGER_R:int =10;
		const E_NES_WRIST_L:int =11;
		const E_NES_WRIST_R:int=12;
		const E_NES_STONE:int =13;

		function getDefaultBg( slotId:int ):String
		{
			switch( slotId )
			{
					case E_NES_MAIN_HAND://武器
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Weapon";
					break;
/*					case E_NES_LEG:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Trouser";
					break;*/
					case E_NES_SHOULDER:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Shoulder";
					break;
					case E_NES_ARM:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Cuff";
					break;					
					case E_NES_FOOT:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Shoe";
					break;
					case E_NES_BACK:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Back";
					break;
					case E_NES_FINGER_L:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_RingL";
					break;
					case E_NES_FINGER_R:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_RingR";
					break;
					case E_NES_WRIST_L:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_BraceletL";
					break;
					case E_NES_WRIST_R:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_BraceletR";
					break;
					case E_NES_NECK:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Necklace";
					break;
					case E_NES_BODY:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Body";
					break;
					case E_NES_HEAD:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Head";
					break;
					case E_NES_WAIST:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Waist";
					break;
					case E_NES_STONE:
					return "img://MMO_UIIcon.DefaultEquipBg.IconBg_Stone";
					break;
					default:
					return "img://MMO_UIIcon.icon.blank";
					break;
			}
		}
		
		override public function set width(value:Number):void 
		{ 
			this.scaleX = 1;			
			UILoader_mc.width = value;
			//trace("width:"+value);
		}
		
		override public function set height(value:Number):void
		{ 
			this.scaleY = 1;
			UILoader_mc.height = value; 
		}
		
		public function initSize()
		{
			UILoader_mc.width *= this.scaleX;
			UILoader_mc.height *= this.scaleY;
			this.scaleX = 1;
			this.scaleY = 1;
		}
		
		override public function SetDataObj( data:Object )
		{
			
		}
		
		override public function SetData( inquantity:Number, iniconName:String , initemIndex:int, initemtype:String, initemColor:int, incontainerID:int, inslotID:int )
		{
			//去掉缩放，拉伸控件本身
			if( UILoader_mc && iniconName == "" )
			{
				if(incontainerID==6){
					UILoader_mc.source="img://MMO_UIIcon.DefaultEquipBg.IconBg_Stone";
				}else{
					UILoader_mc.source = getDefaultBg(inslotID);
				}
			}
			if( UILoader_mc && iniconName != "" )
			{
				UILoader_mc.source = "imgps://"+iniconName;
				//UILoader_mc.source = "img://weapon.png";
			}
			
			ExternalInterface.call("ASTrace", "============== ItemSlot SetData " + iniconName );
		}
	}
}