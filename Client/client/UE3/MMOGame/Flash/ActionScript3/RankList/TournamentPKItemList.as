package ActionScript3.RankList
{
	public class TournamentPKItemList extends BaseRankItemList
	{
		public var obj:TournamentPKItemListData;

		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}

		protected function UpdateData(dat:Object):void
		{
			obj = dat as TournamentPKItemListData;
			if (obj)
			{
				UpdateBaseData(obj);
				txt_num.text = obj.PKValue;
			}
			else
			{
				visible = false;
			}
		}

	}

}