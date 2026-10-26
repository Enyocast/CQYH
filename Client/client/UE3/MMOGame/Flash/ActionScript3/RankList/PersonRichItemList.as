package ActionScript3.RankList
{
	import ActionScript3.Common.MoneyInputNew;
	
	public class PersonRichItemList extends BaseRankItemList 
	{
		public var found_txt_mc:MoneyInputNew;
		public var obj:PersonRichItemListData;

		override protected function configUI():void
		{
			super.configUI();
			found_txt_mc.moneyIconType = 2;
			found_txt_mc.moneyIconTypeW = 0;
			setUpdateDataCallBack(UpdateData);
		}

		protected function UpdateData(dat:Object):void
		{
			obj = dat as PersonRichItemListData;
			if (obj)
			{
				this.UpdateBaseData(obj);
				found_txt_mc.setMoney(obj.Found);
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
