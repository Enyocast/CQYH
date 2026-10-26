package ActionScript3.RankList
{
	public class PersonPageExpItemList extends BaseRankItemList 
	{
		public var obj:PersonPageExpItemListData;
		

		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		protected function UpdateData(dat:Object):void
		{
			obj = dat as PersonPageExpItemListData;
			if(obj)
			{
				UpdateBaseData(obj);
				var exp = obj.Exp;
				exp = Math.ceil(exp/10000);
				if(exp <= 0)
				{
					exp = 1;
				}
				txt_num.text = exp+"万";
			}
			else
			{
				visible = false;
			}
				
		}
		
	}
	
}
