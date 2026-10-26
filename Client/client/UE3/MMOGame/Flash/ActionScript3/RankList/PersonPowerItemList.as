package ActionScript3.RankList
{
	public class PersonPowerItemList extends BaseRankItemList 
	{
		public var obj:PersonPowerItemListData;
		
		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		protected function UpdateData(dat:Object):void
		{
			obj = dat as PersonPowerItemListData;
			if (obj)
			{
				UpdateBaseData(obj)
				txt_num.text = obj.Power;
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
