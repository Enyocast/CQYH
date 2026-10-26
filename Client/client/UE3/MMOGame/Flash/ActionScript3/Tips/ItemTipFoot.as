/********************************************************************
Created:2013/06
Filename: ItemTipFoot
file ext:as
Author:hemu@snda
Purpose:Tips系统View ItemTipFoot控件
*********************************************************************/

package ActionScript3.Tips
{

	import ActionScript3.MyPanel;

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextFieldEx;
	import ActionScript3.Tips.CommonTipData;
	import scaleform.clik.controls.UILoader;

	public class ItemTipFoot extends MovieClip
	{
		public var tF_Duration:TextField;
		public var tF_Price:TextField;
		public var tF_ForbidSell:TextField;
		public var tF_ForbidTrade:TextField;
		public var tF_ForbidDecompose:TextField;

		public var TipHeight:int = 0;

		public const nSpacing:int = 25;


		public function ItemTipFoot()
		{

		}
		public function ReSize(startY:int, Spacing:int):int
		{
			this.y = startY;
			if(!tF_ForbidDecompose.visible && !tF_ForbidTrade.visible)
			{
				tF_Price.y = 12;
				tF_ForbidSell.y = 12;
				tF_Duration.y = 12;
			}
			else
			{
				tF_Price.y = 32;
				tF_ForbidSell.y = 32;
				tF_Duration.y = 32;
			}
			var nHeight:int = (tF_ForbidDecompose.visible || tF_ForbidTrade.visible) ? 20 : 0;
			return this.y + nHeight + nSpacing + Spacing;
		}
		public function SetData(TipData:ItemTipData):void
		{
			if((TipData.Duration==null ||TipData.Duration=="") && (TipData.ForbidDecompose=="" || TipData.ForbidDecompose==null) && (TipData.ForbidTrade=="" || TipData.ForbidTrade==null) && (TipData.Money=="" || TipData.Money==null) && (TipData.ForbidSell=="" || TipData.ForbidSell == null)){
				this.visible=false;
				return;
			}else{
				this.visible=true;
			}
			if("" == TipData.ForbidSell || TipData.ForbidSell == null)
			{
				tF_Price.visible = true;
				tF_Price.htmlText = TipData.Money;
				tF_ForbidSell.visible = false;
			}
			else
			{
				tF_Price.visible = false;
				tF_ForbidSell.visible = true;
				tF_ForbidSell.htmlText = TipData.ForbidSell;
			}
			ExternalInterface.call("ASTrace", "TipData.ForbidSell " + TipData.ForbidSell );

			if("" == TipData.ForbidTrade || TipData.ForbidTrade == null)
			{
				tF_ForbidTrade.visible = false;
			}
			else
			{
				tF_ForbidTrade.visible = true;
				tF_ForbidTrade.htmlText = TipData.ForbidTrade;
			}
			
			if("" == TipData.ForbidDecompose || TipData.ForbidDecompose == null)
			{
				tF_ForbidDecompose.visible = false;
			}
			else
			{
				tF_ForbidDecompose.visible = true;
				tF_ForbidDecompose.htmlText = TipData.ForbidDecompose;
			}
			
			
			if (null == TipData.Duration || TipData.Duration == "")
			{
				tF_Duration.visible = false;
			}
			else
			{
				tF_Duration.visible = true;
				tF_Duration.htmlText = TipData.Duration;
			}

		}
	}

}