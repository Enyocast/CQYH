package ActionScript3.RankList
{

	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.events.MouseEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import ActionScript3.TreeListData;
	import flash.text.TextField;
	import scaleform.clik.controls.RadioButton;


	public class TournamentPageCrops extends BasePersonPage
	{
		public var corps_list_mc:ScrollingList;

		public var category5v5_btn_mc:Button;
		
		public var myrank_txt_mc:TextField;
		
		private const rlArenaScore:int = 33;

		override protected function configUI():void
		{
			super.configUI();

			(tabTitle.getChildByName("tf_dec") as TextField).text="队伍配置";
		}
		
		public function UpdateTournamentListData( data:Array ):void
		{
			if(visible && null != data)
			{
				corps_list_mc.dataProvider = new DataProvider(data);
				corps_list_mc.validateNow();
				corps_list_mc.invalidateData();
			}
		}
	}

}