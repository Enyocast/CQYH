package ActionScript3.RankList
{
	import flash.text.TextField;
	
	public class GuildPowerItemList extends BaseGuildItemList 
	{
		public var pow_txt_mc:TextField;

		public var PowData:GuildPowerItemListData;

		override protected function configUI():void
		{
			super.configUI();
			setUpdateDataCallBack(UpdateData);
		}
		
		protected function UpdateData(dat:Object):void
		{
			PowData = dat as GuildPowerItemListData;
			if(null != PowData)
			{
				this.UpdateBaseData(PowData);
				var pow:int = PowData.Pow;
				pow_txt_mc.text = pow.toString();
			}
			else
			{
				visible = false;
			}
		}
	}
	
}
