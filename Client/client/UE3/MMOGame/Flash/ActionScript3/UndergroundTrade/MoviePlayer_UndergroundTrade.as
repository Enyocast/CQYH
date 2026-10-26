package ActionScript3.UndergroundTrade
{
	import ActionScript3.fla.MoviePlayerBase;
	public class MoviePlayer_UndergroundTrade extends MoviePlayerBase
	{
		public var undergroundTrade_panel_mc:UndergroundTradePanel;
		public var sell_panel_mc:UTSellPanel;
		public var bid_panel_mc:UTBidPanel;
		public var bidmysign_panel_mc:UTBidMySignPanel;
		
		public function MoviePlayer_UndergroundTrade() 
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			trace("----------------MoviePlayer_UndergroundTrade::configUI");
			
			super.configUI();
		}		

	}
	
}
