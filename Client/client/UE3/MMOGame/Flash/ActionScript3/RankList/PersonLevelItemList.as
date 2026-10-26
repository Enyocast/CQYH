package ActionScript3.RankList
{
	public class PersonLevelItemList extends BaseRankItemList 
	{
		public var obj:PersonLevelItemListData;
		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
        protected function UpdateData(dat:Object):void
		{
			obj = dat as PersonLevelItemListData;
			
			if (obj)
			{
				this.UpdateBaseData(obj);
				txt_num.text = obj.Level;
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
