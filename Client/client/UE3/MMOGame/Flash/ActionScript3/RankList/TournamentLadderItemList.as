package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	
	public class TournamentLadderItemList extends ListItemTreeRenderer 
	{
		public var rankindex_txt_mc:TextField;
		public var rolename_txt_mc:TextField;
		public var job_txt_mc:TextField;
		public var grades_txt_mc:TextField;
		//public var level_txt_mc:TextField;
		public var LadderData:TournamentLadderItemListData;
		
		public function TournamentLadderItemList()
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
			addEventListener(MouseEvent.CLICK, OnRightClick);
			setUpdateDataCallBack(UpdateData);
		}
		
		function OnRightClick(e:Event)
		{
			if (1 == (e as MouseEventEx).buttonIdx)
			{
				ExternalInterface.call("ASRightClick1Menu", LadderData.Id);
			}
		}
		
		function UpdateData(data:Object):void
		{
			LadderData = data as TournamentLadderItemListData;
			if(null != LadderData)
			{
				visible = true;
				rankindex_txt_mc.text = LadderData.RankIndex;
				rolename_txt_mc.text = LadderData.RoleName;
				job_txt_mc.text = LadderData.Job;
				grades_txt_mc.text = LadderData.Grades;
				//level_txt_mc.text = LadderData.Level;
			}
			else
				visible = false;
		}
		
		
	}
	
}
