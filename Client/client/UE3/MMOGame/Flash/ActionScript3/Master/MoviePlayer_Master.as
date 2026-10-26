/********************************************************************
	Created:	2013/03/27
	Filename: 	MoviePlayer_Master
	file ext:	as
	Author:		hemu@snda
	Purpose:	师徒系统View MoviePlayer_Master
*********************************************************************/

package ActionScript3.Master
{

	import ActionScript3.fla.MoviePlayerBase;

	public class MoviePlayer_Master extends MoviePlayerBase
	{
		public var MyMasterPanel:MasterPanel;
		public var congratulationSub_mc:AlertPanel;
		public var congratulationMain_mc:CongratulatePanel;
		
		override protected function configUI():void
		{
			super.configUI();
		}		
	}
}