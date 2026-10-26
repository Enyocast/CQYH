package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	
	public class ArenaConfigItemList extends ListItemTreeRenderer 
	{
		public var name_txt_mc:TextField;
		public var level_txt_mc:TextField;
		public var job_txt_mc:TextField;
		public var ConfigData:ConfigItemListData;
		
		public function ArenaConfigItemList()
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
			ConfigData = data as ConfigItemListData;
			if(null != ConfigData)
			{
				visible = true;
				name_txt_mc.text = ConfigData.Name;
				level_txt_mc.text = ConfigData.Level;
				job_txt_mc.text = ConfigData.Job;
			}
			else
				visible = false;
		}
		
		
	}
	
}
