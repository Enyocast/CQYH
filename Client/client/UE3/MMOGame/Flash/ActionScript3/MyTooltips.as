package ActionScript3
{
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import flash.external.ExternalInterface;
	import ActionScript3.Tips.ItemTip;

	public class MyTooltips extends UIComponent
	{
		//public var tips_item_text:TextField;
		//public var TipsBg:MovieClip;
		public var itemTip:ItemTip;
		
		override protected function configUI():void 
		{
			//trace("MyTooltips configUI() ");
			super.configUI();
			
			//ExternalInterface.call( "RegisterTips" , this );

		}
		
		
		public function ShowTips( Item:MovieClip , TipsType:int , TipsIdx:int )
		{
			if( Item.parent )
			{
				//trace(Item.parent);
				var pos:Point = new Point;
				pos.x = Item.x + Item.width;
				pos.y = Item.y;

				trace(pos.x+"/"+pos.y);
				pos = Item.parent.localToGlobal( pos);
				x = pos.x;
				y = pos.y;
				trace(pos.x+"/"+pos.y);

			}
			
			visible =true;
			ExternalInterface.call("ShowTips",TipsType,TipsIdx ,Item );//代码里把tips.visible设true
		}
	}
}