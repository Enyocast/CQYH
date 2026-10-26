//
// 家族介绍
//
package ActionScript3.Guild
{
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.CustomScrollBar;

	public class GuildInstructionsPanel extends MyPanel
	{
		public var guild_instru_tf:TextField;
		public var bar:CustomScrollBar;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			guild_instru_tf.htmlText = "";
		}
		
		public function UCSetContent(text:String)
		{
			bar.position=0;
			guild_instru_tf.htmlText = text;
		}
		
		public function UCSetWindowTitle(title:String)
		{
			SetWindowTitle(title);
		}
	}
}


























