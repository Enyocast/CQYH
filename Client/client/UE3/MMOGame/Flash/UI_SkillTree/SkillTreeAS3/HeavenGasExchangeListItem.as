package UI_SkillTree.SkillTreeAS3
{
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import ActionScript3.ItemSlot.MyItemSlot;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import UI_FX_Lib.FX_Lib_AS3.FX_Default;
	
	public class HeavenGasExchangeListItem extends ListItemTreeRenderer
	{
		public var gasIcon_mc:MyItemSlot;
		public var gasEchange00:FX_Default;
		public var gasName_mc:TextField;
		public var costGas_mc:TextField;
		public var gasDescrible_mc:TextField;
		
		public var ItemData:HeavenGasExchangeData;
		
		
		override protected function configUI():void
		{
			super.configUI();
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			
			/*width = 544;
			height = 70;*/
			visible = false;
			//trace("=======HeavenGasExchangeListPanel::updateData", gasEchange00);
			gasIcon_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenGasSlot);
			gasIcon_mc.addEventListener(MouseEvent.ROLL_OUT,  onRollOutHeavenGasSlot);
			gasEchange00.visible = false;
			gasIcon_mc.itemSlotIcon.IconLoader_mc.source = "";
			//autoSize = TextFieldAutoSize.CENTER;
		}
		
		
		function updateData(data:Object):void
		{
			ItemData = data as HeavenGasExchangeData;

			trace("=======HeavenGasExchangeListPanel::updateData", data , ItemData);

			if (ItemData)
			{
				/*width = 544;
				height = 70;*/
				visible = true;
				gasName_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				gasName_mc.wordWrap 	= 			true;
				gasName_mc.htmlText 	= 			ItemData.GasName;
				gasName_mc.height 	= 				gasName_mc.textHeight;
				costGas_mc.text = String(ItemData.GasCost);
				gasDescrible_mc.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				gasDescrible_mc.wordWrap 	= 			true;
				gasDescrible_mc.htmlText 	= 			ItemData.GasDescrible;
				gasDescrible_mc.height 	= 				gasDescrible_mc.textHeight;
				
				gasIcon_mc.itemSlotIcon.IconLoader_mc.visible = true;
				gasIcon_mc.itemSlotIcon.IconLoader_mc.source  = ItemData.IconName0;
				
				//gasEchange00.SetFxPic(ItemData.IconName0,ItemData.IconName1);
				//gasEchange00.SetIconType(ItemData.GasColor);
			}
		}
		
		function onRollOverHeavenGasSlot( e:Event )
		{
			if(ItemData)
				ExternalInterface.call("ASShowTips_HeavenGasExchangeSlot",this,ItemData.GasID);
		}

		function onRollOutHeavenGasSlot( e:Event )
		{
			if(ItemData)
				ExternalInterface.call("ASHideTips_HeavenExchangeGasSlot" );
		}
		
		override public function setActualSize(newWidth:Number, newHeight:Number):void {
			// If the clip is rotated, setting super.width and super.height can reset/unexpectedly affect one another. Seems to be
			// a bug in Flash Player.
			/*if (super.width != newWidth || _width != newWidth) {
				super.width = _width = newWidth;
			}

			if (super.height != newHeight || _height != newHeight) {
				super.height = _height = newHeight;
			}*/
		}
		
	}
}


























