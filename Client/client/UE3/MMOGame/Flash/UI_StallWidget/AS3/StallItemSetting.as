package UI_StallWidget.AS3
{

	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.StyleSheet;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	
	import ActionScript3.MoneyIcon;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.TextInput_Advanced;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import UI_ChatWidget.AS3.ChatTextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextArea;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.managers.FocusHandler;

	public class StallItemSetting extends UIComponent
	{
		public var btn_stall_update:Button;
		public var btn_stall_record:Button;
		public var btn_startStall:Button;
		public var btn_shutStall:Button;
		public var btn_arrange:Button;

		public var tf_stall_name_title:TextField;
		public var tf_stall_name_input:TextInput_Advanced;
		public var tf_stall_name_bg:MovieClip;
		public var tf_stall_name_static:TextField;
		public var stall_name_bg_mc:MovieClip;

		public var slot_mc0:MyItemSlot;
		public var slot_mc1:MyItemSlot;
		public var slot_mc2:MyItemSlot;
		public var slot_mc3:MyItemSlot;
		public var slot_mc4:MyItemSlot;
		public var slot_mc5:MyItemSlot;
		public var slot_mc6:MyItemSlot;
		public var slot_mc7:MyItemSlot;
		public var slot_mc8:MyItemSlot;
		public var slot_mc9:MyItemSlot;
		
	//	public var PageCtrl:CustomPage;
		public var txt_update_time_left:TextField;
		
		public var record_list_mc:StallRecordList;
		
		private static const SLOT_NUM:int = 10;


		override protected function configUI():void
		{
			super.configUI();
			btn_stall_update.addEventListener(ButtonEvent.CLICK, onUpdateStall);
			btn_stall_record.addEventListener(ButtonEvent.CLICK, onViewStallRecord);
			btn_startStall.addEventListener(ButtonEvent.CLICK, onStartStall);
			btn_shutStall.addEventListener(ButtonEvent.CLICK, onShutStall);
			btn_arrange.addEventListener(ButtonEvent.CLICK, onArrangeStall);
			
			//PageCtrl.addEventListener(ParamEvent.PAGE_CHANGE, onTurnPage);
			
			txt_update_time_left.visible = false;
			record_list_mc.visible = false;
			btn_stall_record.label = "交易记录";
			btn_arrange.visible = false;
		}
		
		private function updateStallNameElment(editAble:Boolean):void
		{
			tf_stall_name_bg.visible = editAble;
			tf_stall_name_title.visible = editAble;
			tf_stall_name_input.visible = editAble;
			tf_stall_name_static.visible = !editAble;
			stall_name_bg_mc.visible = !editAble;
		}
		
		public function UpdateMoney(tData:Object)
		{
			var goldTotal:Number = tData.goldTotal;
			var goldOnSale:Number = tData.goldOnSale;
		}
		
		function GetMoneyFormat(nValue:int):String
		{
			var gold_s:String = "";
			if(nValue >= 10000)
			{
				gold_s += Math.floor(nValue / 10000).toString();
				gold_s += "万";
			}
			if(nValue%10000 > 0 || nValue == 0)
				gold_s += (nValue % 10000).toString();
			gold_s += String("<IMG  SRC='img://MMO_UIIcon.MoneyIcon.MoneyCash_S'>");
			return gold_s;
		}
		
		public function UpdateButtonState(tData:Object)
		{
			setAllSlotDisableDrag(tData.startStall);
			btn_stall_update.visible = tData.startStall;
		  	btn_startStall.visible = tData.startStall;
			btn_arrange.visible = tData.arrangeStall;
		  	btn_shutStall.visible  = tData.shutStall;
			tf_stall_name_static.text = tf_stall_name_input.text;
			updateStallNameElment(tData.startStall);
		}
		
		public function UpdateNameAndAdd(tData:Object)
		{
			tf_stall_name_input.text = tData.StallName;
			tf_stall_name_input.enabled = tData.StallNameEnabled;
		}
		
		public function setUpdatIimeLeft(info:String, over:Boolean):void
		{
			if (btn_startStall.visible)
			{
				btn_stall_update.visible = over;
			}
			else
			{
				btn_stall_update.visible = false;
			}
			txt_update_time_left.visible = true;
			txt_update_time_left.text = info;
		}
		
		public function setRecordListData(data:Array):void
		{
			record_list_mc.updateListData(data);
		}
		
		public function checkItemGoldText(slotIndex:int):void
		{
			if(slotIndex >=0 && slotIndex < SLOT_NUM)
			{
				(this['slot_mc' + slotIndex] as StallSettingItem).checkGoldTextBoundary();
			}
		}
		
		private function setAllSlotVisible(value:Boolean):void
		{
			for(var i:int = 0; i < SLOT_NUM; i++)
			{
				(this['slot_mc' + i] as MyItemSlot).visible = value;
			}
		//	PageCtrl.visible = value;
		}
		
		private function setAllSlotDisableDrag(value:Boolean):void
		{
			for(var i:int = 0; i < SLOT_NUM; i++)
			{
				(this['slot_mc' + i] as MyItemSlot).DisableDrag = !value;
			}
		}

		private function onUpdateStall(evt:ButtonEvent):void
		{
			ExternalInterface.call( "ASUpgradeStall" );
		}
		
		private function onViewStallRecord(evt:ButtonEvent):void
		{
			if(record_list_mc.visible == false)//点击显示交易记录
			{
				ExternalInterface.call( "ASViewStallRecord" );
				setAllSlotVisible(false);
				record_list_mc.visible = true;
				btn_stall_record.label = "关闭记录";
			}
			else//点击关闭交易记录
			{
				hideStallRecordList();
			}
		}
		
		private function hideStallRecordList():void
		{
			if(record_list_mc.visible == true)//关闭交易记录
			{
				ExternalInterface.call( "ASHideStallRecord" );
				setAllSlotVisible(true);
				record_list_mc.visible = false;
				btn_stall_record.label = "交易记录";
			}
		}
		
		private function onStartStall(evt:ButtonEvent):void
		{
			var stallName:String = tf_stall_name_input.text;
			ExternalInterface.call("ASOpenStall", stallName);
			hideStallRecordList();
		}
		
		private function onShutStall(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASCloseStall");
			hideStallRecordList();
		}
		
		private function onArrangeStall(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASArrangeStall");
			hideStallRecordList();
		}
		
/*		private function onTurnPage(evt:ParamEvent):void
		{
			var pageValue:int = int(evt.param);
			ExternalInterface.call("ASOnTurnPage", pageValue);
		}*/

		public function setFocus():void
		{
			FocusHandler.getInstance().setFocus(tf_stall_name_input.textField);
		}
	}

}