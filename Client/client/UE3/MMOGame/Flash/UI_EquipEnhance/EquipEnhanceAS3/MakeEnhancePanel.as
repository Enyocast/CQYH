package  UI_EquipEnhance.EquipEnhanceAS3
{
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.MyItemSlotShow;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	//import scaleform.clik.events.ButtonEvent;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	
	public class MakeEnhancePanel extends UIComponent
	{
		public var MakeEnhanceSuccessAnim_mc:MovieClip;
		//
		public var MakeEnhanceItem_mc:MyItemSlot;
		//所需材料Icon
		public var MakeEnhanceMatCsm_mc1:MyItemSlotShow;
		public var MakeEnhanceMatCsm_mc2:MyItemSlotShow;
		public var MakeEnhanceMatCsm_mc3:MyItemSlotShow;
		//强化费
		public var MakeEnhanceMnyType_mc:MovieClip;
		public var MakeEnhanceMnyCsm_tf:TextField;
		//当前强化等级
		public var MakeEnhanceCurDgr_tf:TextField;
		//最大强化等级
		public var MakeEnhanceMaxDgr_tf:TextField;
		//强化按钮
		public var MakeEnhance_btn:Button;
		//取消
		public var ExitEnhance_btn:Button;
		//当前强化装备属性
		public var CurEnhanceProp_tf0:TextField;
		//public var CurEnhancePropValue_tf0:TextField;
		public var CurEnhanceProp_tf1:TextField;
		//public var CurEnhancePropValue_tf1:TextField;
		public var CurEnhanceProp_tf2:TextField;
		//public var CurEnhancePropValue_tf2:TextField;
		//下一级强化装备属性
		public var MakeEnhanceProp_tf0:TextField;
		//public var MakeEnhancePropValue_tf0:TextField;
		public var MakeEnhanceProp_tf1:TextField;
		//public var MakeEnhancePropValue_tf1:TextField;
		public var MakeEnhanceProp_tf2:TextField;
		//public var MakeEnhancePropValue_tf2:TextField;
		//
		override protected function configUI():void
		{
			super.configUI();
			MakeEnhanceItem_mc.itemSlotBg.visible = false;
		/*	MakeEnhanceMatCsm_mc1.itemSlotBg.visible = false;
			MakeEnhanceMatCsm_mc2.itemSlotBg.visible = false;
			MakeEnhanceMatCsm_mc3.itemSlotBg.visible = false;*/
			MakeEnhanceSuccessAnim_mc.visible = false;
			
			MakeEnhance_btn.addEventListener( "click", EnhanceItem );
			
			ExitEnhance_btn.addEventListener( "click", CloseThisPanel );
		}
		function EnhanceItem( e:Event )
		{
			ExternalInterface.call( "ASMakeEnhanceItem" );
			
			//test
			//MakeEnhanceSuccessAnim_mc.visible = true;
			//MakeEnhanceSuccessAnim_mc.gotoAndPlay( 1 );
		}
		//
		function CloseThisPanel( e:Event ):void
		{
			ExternalInterface.call( "ASHideEquipEnhance" );
		}
	}
}