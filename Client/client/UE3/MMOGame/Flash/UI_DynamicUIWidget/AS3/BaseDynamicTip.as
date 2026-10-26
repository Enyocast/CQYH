package AS3
{
	import flash.filters.BevelFilter;
	import flash.filters.DropShadowFilter;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.StyleType;
	import flash.text.TextFormat;

	/**
	 * 基础Tip 
	 * @author kongxiangwen.robey
	 * 
	 */	
	public class BaseDynamicTip extends MyPanel
	{
		public var tF_ItemName:TextField;
		private var _format:TextFormat;
		public var bevel:BevelFilter= StyleType.getInstance().getBevel();
		public var shade:DropShadowFilter=StyleType.getInstance().getDropShadow();
		
		override protected  function configUI():void 
		{			
			super.configUI();
			this.mouseChildren=this.mouseEnabled=false;
		}
		public function BaseDynamicTip()
		{
			
		}
		
		public function setTxt(ColorName:String,ItemName:String):void
		{
			tF_ItemName.filters=null;
			switch(ColorName)
			{
				case "lv1":
				{
					//tF_ItemName.textColor=0x84ec60;
					bevel.shadowColor=0x84ec60;
					bevel.highlightColor=0xa6ed8d;
					break;
				}
				case "lv2":
				{
					//tF_ItemName.textColor=0x399bff;
					bevel.shadowColor=0x399bff;
					bevel.highlightColor=0x63b0fe;
					break;
				}
				case "lv3":
				{
					//tF_ItemName.textColor=0xc43cfc;
					bevel.shadowColor=0xc43cfc;
					bevel.highlightColor=0xcb6af3;
					break;
				}
				case "lv4":
				{
					//tF_ItemName.textColor=0xf9a410;
					bevel.shadowColor=0xf9a410;
					bevel.highlightColor=0xf9b43c;
					break;
				}
				default:
				{
					bevel.shadowColor=0xffffff;
					bevel.highlightColor=0xFFF9F2;
					break;
				}
			}
			tF_ItemName.textColor=0xffffff;
			tF_ItemName.text = ItemName;
			shade.blurX=shade.blurY=2;
			shade.distance=1;
			tF_ItemName.filters=[shade,bevel];
		}
	}
}