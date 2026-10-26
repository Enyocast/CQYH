package ActionScript3.RankList
{
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.gfx.MouseEventEx;
	
	public class TournamentCorpsItemList extends ListItemTreeRenderer 
	{
		public var rankindex_txt_mc:TextField;
		public var corpsname_txt_mc:TextField;
		public var captain_txt_mc:TextField;
		public var grades_txt_mc:TextField;
		public var config_btn_mc:Button;
		public var CorpsData:TournamentCorpsItemListData;
		
		public function TournamentCorpsItemList()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			visible = false;
			//this.mouseChildren = true;
			this.mouseEnabled = true;
			grades_txt_mc.textColor = 0xffd100;
			config_btn_mc.addEventListener(MouseEvent.CLICK, OnTournamentConfigClick);
			setUpdateDataCallBack(UpdateData);
		}
		
		public function OnTournamentConfigClick(e:Event)
		{
			if (1 == (e as MouseEventEx).buttonIdx)
			{
				ExternalInterface.call("ASTournamentConfigClick", CorpsData.Id);
			}
		}
		
		function UpdateData(data:Object):void
		{
			CorpsData = data as TournamentCorpsItemListData;
			if(null != CorpsData)
			{
				visible = true;
				rankindex_txt_mc.text = CorpsData.RankIndex;
				corpsname_txt_mc.text = CorpsData.CorpsName;
				captain_txt_mc.text = CorpsData.Captain;
				grades_txt_mc.text = CorpsData.Grades;
			}
			else
				visible = false;
		}
		
		
	}
	
}
