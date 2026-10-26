package ActionScript3.RankList
{
	import ActionScript3.Common.MoneyInputNew;
	
	public class GuildFoundItemList extends BaseGuildItemList 
	{
		public var FoundData:GuildFoundItemListData;
		public var found_txt_mc:MoneyInputNew;
		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		protected function UpdateData(dat:Object):void
		{
			FoundData = dat as GuildFoundItemListData;
			if(null != FoundData)
			{
                this.UpdateBaseData(FoundData);
				found_txt_mc.setMoney(FoundData.Found);
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
