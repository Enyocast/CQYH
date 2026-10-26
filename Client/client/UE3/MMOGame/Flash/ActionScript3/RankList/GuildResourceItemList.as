package ActionScript3.RankList
{
	import flash.text.TextField;
	
	public class GuildResourceItemList extends BaseGuildItemList 
	{
		public var food_txt_mc:TextField;
		public var ResourceData:Object;

		override protected function configUI():void
		{
			super.configUI();
			food_txt_mc.textColor = 0xffd100;
			setUpdateDataCallBack(UpdateData);
		}

		protected function UpdateData(dat:Object):void
		{
			ResourceData = dat as Object;
			if(null != ResourceData)
			{
				this.UpdateBaseData(ResourceData);
				food_txt_mc.text = ResourceData.Food;
			}
			else
			{
				visible = false;
			}
		}
		
	}
	
}
