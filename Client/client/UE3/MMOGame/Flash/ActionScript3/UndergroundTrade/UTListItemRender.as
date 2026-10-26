package ActionScript3.UndergroundTrade
{
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextField;
	
	import ActionScript3.UndergroundTrade.UTListItemData;
	
	public class UTListItemRender extends ListItemTreeRenderer
	{
		public var search_uiloader_mc:UILoader;
		public var equipname_txt_mc:TextField;
		public var level_txt_mc:TextField;
		public var signer_txt_mc:TextField;
		public var all_txt_mc:TextField;
		public var lefttime_txt_mc:TextField;
		
		public var itemData:UTListItemData;
		
		public function UTListItemRender() 
		{
			// constructor code
		}
		
		override protected function configUI():void 
		{
			super.configUI();
			
			setUpdateDataCallBack(UpdateData);
		}
		
		function UpdateData(data:Object):void
		{
			itemData = data as UTListItemData;
			if(null != itemData)
			{
				if(0 < itemData.iconName.length)
					search_uiloader_mc.source = "img://" + itemData.iconName;
				if(equipname_txt_mc.text != itemData.equipName)
					equipname_txt_mc.text = itemData.equipName;
				if(level_txt_mc.text != itemData.level)
					level_txt_mc.text = itemData.level;
				if(signer_txt_mc.text != itemData.signer)
					signer_txt_mc.text = itemData.signer;
				if(all_txt_mc.text != itemData.all)
					all_txt_mc.text = itemData.all;
				if(lefttime_txt_mc.text != itemData.leftTime)
					lefttime_txt_mc.text = itemData.leftTime;
			}
		}
	}
	
}
