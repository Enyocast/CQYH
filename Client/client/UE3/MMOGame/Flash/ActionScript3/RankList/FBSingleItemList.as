package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;

	public class FBSingleItemList extends ListItemTreeRenderer
	{
		public var rankindex_txt_mc:TextField;
		public var rolename_txt_mc:TextField;
		public var job_txt_mc:TextField;
		public var grades_txt_mc:TextField;
		public var level_txt_mc:TextField;
		public var FBSingleData:FBSingleItemListData;

		public function FBSingleItemList()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			visible = false;
			//this.mouseChildren = true;
			//this.mouseEnabled = true;
			grades_txt_mc.textColor = 0xffd100;
			setUpdateDataCallBack(UpdateData);
		}

		function UpdateData(data:Object):void
		{
			FBSingleData = data as FBSingleItemListData;
			if (null != FBSingleData)
			{
				visible = true;
				rankindex_txt_mc.text = FBSingleData.RankIndex;
				rolename_txt_mc.text = FBSingleData.RoleName;
				job_txt_mc.text = FBSingleData.Job;
				grades_txt_mc.text = FBSingleData.Grade;
				level_txt_mc.text = FBSingleData.Level;
			}
			else
				visible = false;
		}


	}

}