
package UI_KillRecord.killrecordAS
{
	import ActionScript3.fla.MoviePlayerBase;
	import UI_KillRecord.killrecordAS.KillCountPanel;
	import UI_KillRecord.killrecordAS.KillRecordPanel;
	
	public class MoviePlayer_KillRecord extends MoviePlayerBase
	{
		public var killRecordPanel_mc:KillRecordPanel;
		public var killCountPanel_mc:KillCountPanel;
		
		override protected function configUI():void
		{
			trace("----------------MoviePlayer_KillRecord::configUI");
			
			super.configUI();
		}		
	}
}