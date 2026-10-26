
package ActionScript3.Mall
{
	import ActionScript3.fla.MoviePlayerBase;
	
	public class MoviePlayer_Mall extends MoviePlayerBase
	{
		public var mallPanel_mc:MallPanel;
		public var mallFriend_mc:MallFriendPanel;
		public var mallGoodsBuy_mc:MallGoodsBuyPanel;
		public var mallEquiprole_mc:MallEquipRolePanel;
		
		override protected function configUI():void
		{
			trace("----------------MoviePlayer_Mall::configUI");
			super.configUI();
		}		
	}
}