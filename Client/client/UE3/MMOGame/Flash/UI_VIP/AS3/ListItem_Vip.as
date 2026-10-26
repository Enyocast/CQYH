package UI_VIP.AS3 {
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.text.TextField;
	import flash.display.MovieClip;
	
	
	public class ListItem_Vip extends ListItemTreeRenderer {
		
		public var tf_diamond:TextField;
		public var tf_gold:TextField;
		public var tf_silver:TextField;
		public var tf_name:TextField;
		public var sp1:MovieClip;
		public var sp2:MovieClip;
		public var sp3:MovieClip;
		
		public function ListItem_Vip() {
			
		}
		override protected function configUI():void
		{
			super.configUI();
			show(false);
			setUpdateDataCallBack(updateData);
		}
		
		function updateData(dat:Object):void
		{	
		    var itemData:VipItemData = dat as VipItemData;
			if(itemData != null)
			{
				visible = true;
				tf_name.text = itemData.Vipname;
				tf_silver.htmlText =itemData.silver;
				tf_diamond.htmlText = itemData.diamond;
				tf_gold.htmlText=itemData.gold;
				if(itemData.silver==""){
					show(true);
				}else{
					show(false);
				}
			}
			else
			{
				visible = false;
			}
			
		}
		
		private function show(bool:Boolean):void
		{
			if(bool==true){
					tf_silver.visible=tf_gold.visible=tf_diamond.visible=false;
					sp1.visible=sp2.visible=sp3.visible=true;
			}else{
					tf_silver.visible=tf_gold.visible=tf_diamond.visible=true;
					sp1.visible=sp2.visible=sp3.visible=false;
			}
		}
	}
	
}
