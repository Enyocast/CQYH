package UI_VIP.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ScrollBar;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	import flash.filters.ColorMatrixFilter;
	
	public class VIPPanel extends MyPanel {
		
		public var _treeList:ScrollingList;
		public var btn_gold:Button;
		public var tf_title:TextField;
		public var txtGold:TextField;
		private var _vipItem:VIPItem;
		public var item1:ItemGrid;
		public var item2:ItemGrid;
		public var item3:ItemGrid;
		public var btn_vip:MovieClip;

		public var vipPageShop:VIPPage_Shop;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			this._caption="VIP";
			super.configUI();
			_vipItem = new VIPItem(_treeList);
			btn_gold.addEventListener(MouseEvent.CLICK,clickHandler);
			UCVipShow(0);
			btn_vip.addEventListener(MouseEvent.ROLL_OVER,overHandler);
			btn_vip.addEventListener(MouseEvent.ROLL_OUT,outHandler);
			//testData();
		}
		
		protected function overHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASVIPTips", e.target);
		}
		
		protected function outHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASHideVIPTips");
		}
		
		public function UCVipShow(dat:int):void
		{
			if(dat>0){
				btn_vip.filters=[];
				btn_vip.visible=true;
			    btn_vip.gotoAndPlay(dat);
			}else{
				
				btn_vip.filters=[ new ColorMatrixFilter([0.33,0.33,0.33,0,0,0.33,0.33,0.33,0,0,0.33,0.33,0.33,0,0,0,0,0,1,0])];
				//btn_vip.visible=false;
			}
			vipPageShop.updateShopBtnState(dat);
		}
		
		public function UCupdateVIPShop(dat:int)
		{
			vipPageShop.updateShopBtnState(dat);
		}
		
		//设置VIP道具
		public function UCSetVipItem(dat:Array):void
		{
			var i:int=0;
			var l:int=dat.length;
			for(i;i<l;i++){
				var goodsData:VipGoods=dat[i];
				(this.getChildByName("item"+i) as ItemGrid).updateData(goodsData);
			}
		}
		
		//设置VIP描述内容
	    public function UCSetVIPPanelPage_Data(dat:Array):void
		{
			_vipItem.updateListData(dat);
		}
		
		public function UCSetVipTip(dat:String):void
		{
			btn_vip.label=dat;
		}
		
		//更新VIP时间
		public function UCupdateVIPTitle(dat:String):void
		{
			tf_title.htmlText=dat;
		}
		
		//更新玩家背包金币数量
		public function UCupdateMoney(dat:String):void
		{
			txtGold.htmlText=dat;
		}

		private function clickHandler(e:MouseEvent):void
		{
			ExternalInterface.call("ASBugYuanBao");
		}
		
/*		private function testData():void
		{
		    var i:int=0;
			var arr:Array=[];
			for(i;i<3;i++){
				var goods:VipGoods=new VipGoods();
				goods.ItemID=i;
				goods.ItemCost=i+100+"";
				goods.ItemName="道具名称"+i;
				goods.ItemIcon="<IMG SRC='img://MMO_UIIcon.MoneyIcon.MoneyBullion'>";
				arr.push(goods);
			}
			UCSetVipItem(arr);
		}*/
	}
	
}
