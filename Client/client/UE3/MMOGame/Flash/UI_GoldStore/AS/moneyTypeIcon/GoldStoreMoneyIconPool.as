package UI_GoldStore.AS.moneyTypeIcon
{
	public class GoldStoreMoneyIconPool
	{
		private static var _instance:GoldStoreMoneyIconPool;
		
		private static var _moneyIconPool:Array = [];
		
		public static function getInstance():GoldStoreMoneyIconPool
		{
			if(_instance == null)
			{
				_instance = new GoldStoreMoneyIconPool();
			}
			return _instance;
		}
		
		public function addToMoneyIconPool(icon:GoldStoreMoneyIcon):void
		{
			if(_moneyIconPool && _moneyIconPool.indexOf(icon) == -1)
			{
				_moneyIconPool.push(icon);
			}
		}
		
		public function switchMoneyIconType(moneyType:int):void
		{
			if(_moneyIconPool && _moneyIconPool.length)
			{
				for(var i:int = 0; i < _moneyIconPool.length; i++)
				{
					(_moneyIconPool[i] as GoldStoreMoneyIcon).onMoneyTypeChanged(moneyType);
				}
			}
		}
	}
}