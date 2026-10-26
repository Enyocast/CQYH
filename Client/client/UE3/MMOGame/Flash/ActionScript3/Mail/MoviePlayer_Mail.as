package ActionScript3.Mail
{

	import ActionScript3.fla.MoviePlayerBase;
	import ActionScript3.Mail.MailPanel;
	import ActionScript3.Mail.ReadMailPanel;
	
	public class MoviePlayer_Mail extends MoviePlayerBase
	{
		public var mail_panel_mc:MailPanel;
		public var read_mail_panel:ReadMailPanel;
		override protected function configUI():void
		{
			super.configUI();
		}		
	}
}