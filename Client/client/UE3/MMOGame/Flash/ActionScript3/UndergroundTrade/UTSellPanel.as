package  ActionScript3.UndergroundTrade
{
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.TextInput;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	
	public class UTSellPanel extends MyPanel 
	{
		public var sell_itemslot_mc:MyItemSlot;
		public var sellprice_inputtxt_mc:TextInput;
		public var realbidprice_txt_mc:TextField;
		public var mintax_txt_mc:TextField;
		public var selltimelimit_txt_mc:TextField;
		public var tradetax_txt_mc:TextField;
		public var desc_txt_mc:TextField;
		public var ok_btn_mc:Button;
		
		public function UTSellPanel()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("----------------UTSellPanel::configUI");
			
			super.configUI();
			
			InitData();
			
			ExternalInterface.call("ASRegisterUTSellPanel", this);
		}		
		
		private function InitData():void
		{
			if(null != sellprice_inputtxt_mc)
				sellprice_inputtxt_mc.text = "0";
				
			if(null != ok_btn_mc)
			{
				ok_btn_mc.label = "确定";
				ok_btn_mc.addEventListener(MouseEvent.CLICK, OnOKClick);
			}
			
			if(null != desc_txt_mc)
				desc_txt_mc.text = "1、在出售价格栏位中输入价格开始拍卖，交易成功之后将会收取一定比例的交易税\
												2、实际的竞标价格大于出售价格，多余的部分由买方承担\
												3、装备一旦上架后将无法修改价格也无法取消，请慎重填写价格\
												4、拍卖时限到后，出价最高者获得装备，成交金币（扣除交易税）通过邮件发放，如无人竞\
												     拍则退回装备";
		}
		
		function OnOKClick():void
		{
			
		}
	}
	
}
