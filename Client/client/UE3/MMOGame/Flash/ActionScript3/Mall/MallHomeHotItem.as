
package ActionScript3.Mall
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.events.TextEvent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.display.Shape;

	public class  MallHomeHotItem extends UIComponent
	{
		public var ItemIcon_mc:MyItemSlot;
		public var ItemName_mc:TextField;
		public var ItemCost0_mc:TextField;
		public var ItemCost1_mc:TextField;
		public var nowPrice_mc:TextField;
		public var oldPrice_mc:TextField;
		public var hotGoodsIndex_mc:MovieClip;
		public var ItemTag_mc:MovieClip;
		protected var _shape:Shape;
		
		public var goodsData:MallGoodsData;

		override protected function configUI():void
		{
			trace("------MallGoodsListItem  configUI:");
			super.configUI();
			_shape=new Shape();
			_shape.x=96;
			_shape.y=58;
			_shape.visible=false;
			//_shape.graphics.lineStyle(1,0xffffff);
			//_shape.graphics.lineTo(80,0);
			//_shape.visible=false;
			this.addChild(_shape);
			this.addEventListener(MouseEvent.CLICK, 		onClickGoods);
			this.addEventListener(MouseEvent.MOUSE_DOWN, 	onMouseDownGoods);
			this.addEventListener(MouseEvent.ROLL_OVER, 	onRollOverGoodsItem);
			this.addEventListener(MouseEvent.ROLL_OUT, 		onRollOutGoodsItem);
		}
		
		public function updateData(data:Object):void
		{
			goodsData = data as MallGoodsData;

			trace("=======MallGoodsListItem::updateData", data);

			if (goodsData)
			{
				visible = true;
				ItemName_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				ItemName_mc.wordWrap 	= 			true;
				ItemName_mc.htmlText 	= 			goodsData.ItemName;
				ItemName_mc.height 	= 				ItemName_mc.textHeight;
				
				
				ItemCost0_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				ItemCost0_mc.wordWrap 	= 			true;
				ItemCost0_mc.htmlText 	= 			goodsData.ItemCost0;
				ItemCost0_mc.height 	= 			ItemCost0_mc.textHeight;
				
				ItemCost1_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				ItemCost1_mc.wordWrap 	= 			true;
				ItemCost1_mc.htmlText 	= 			goodsData.ItemCost1;
				ItemCost1_mc.height 	= 			ItemCost1_mc.textHeight;
				_shape.graphics.clear();
				if(goodsData.ItemCost0!="" && goodsData.ItemCost1 != "" && goodsData.ItemCost1!=goodsData.ItemCost0){
					_shape.visible=true;
			       _shape.graphics.lineStyle(1,0xffffff);
			       _shape.graphics.lineTo(this.ItemCost0_mc.textWidth,0);
				}
				ItemCost0_mc.visible=oldPrice_mc.visible = (goodsData.ItemCost0 != "");
				ItemCost1_mc.visible=nowPrice_mc.visible = (goodsData.ItemCost1 != "");
					
				if(goodsData.ItemIndex>0 && goodsData.ItemIndex < 6)
					hotGoodsIndex_mc.gotoAndStop(goodsData.ItemIndex);
				if(goodsData.ItemType > 0 && goodsData.ItemType < 4)
					ItemTag_mc.gotoAndStop(goodsData.ItemType);
			}
			else
			{
				visible = false;
			}
		}
		public function onClickGoods()
		{
			if(goodsData)
			{
				this.gotoAndStop("over");
				ExternalInterface.call("ASClickMallGoods", goodsData.ItemID);
			}
		}
		
		function onMouseDownGoods( e:Event )
		{
			if( !goodsData ){
				return;
			}
			this.gotoAndStop("selected_up");
		}
		
		function onRollOverGoodsItem( e:Event )
		{
			if( !goodsData ){
				return;
			}
			this.gotoAndStop("over");
		}

		function onRollOutGoodsItem( e:Event )
		{
			if( !goodsData ){
				return;
			}
			this.gotoAndStop("up");
		}
	}
}