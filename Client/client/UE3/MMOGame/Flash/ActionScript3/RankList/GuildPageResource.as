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


	public class GuildPageResource extends BaseGuildPage
	{
		private const rlGuild_Resource_Herb:int = 33;
		
		override protected function configUI():void
		{
			super.configUI();
			updateTitle(0);
		}
		
		override public function UpdateGuildListData( dat:Array ):void
		{
			var type:int = dat[0] as int;
			if(rlGuild_Resource_Herb == type)
			{
				dat.shift();
				visible = true;
			}
			else
			{
				visible = false;
			}
			super.UpdateGuildListData(dat);
		}
		
		override protected function OnCategoryClick(evt:MouseEvent):void
		{
			var mc:Button=evt.target as Button;
			if(mc)
			{
				var index:int=int(mc.itemid);
				updateTitle(index);
				ExternalInterface.call("ASCategoryClick", index);
			}
		}
		
		private function updateTitle(idx:int):void
		{
			switch(idx)
			{
				case 0:
				{
					(tabTitle.getChildByName("tf_foods") as TextField).text="粮食储备";
					break;
				}
				case 1:
				{
					(tabTitle.getChildByName("tf_foods") as TextField).text="木材储备";
					break;
				}
				case 2:
				{
					(tabTitle.getChildByName("tf_foods") as TextField).text="石料储备";
					break;
				}
				case 3:
				{
					(tabTitle.getChildByName("tf_foods") as TextField).text="铁矿储备";
					break;
				}
			}
		}

	}

}