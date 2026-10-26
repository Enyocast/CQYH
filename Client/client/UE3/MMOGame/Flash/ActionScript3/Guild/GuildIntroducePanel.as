//
// 家族介绍
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;

	public class GuildIntroducePanel extends UIComponent
	{
		public var guild_view_mc : MovieClip;
		public var guild_introduce_tf:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			guild_view_mc.addEventListener(MouseEvent.CLICK, onBtClickView);
		}
		
		public function updateGuildIntroduce(intro:String):void
		{
			guild_introduce_tf.htmlText = intro;
		}
		
		public function onBtClickView(evt:MouseEvent):void
		{
			ExternalInterface.call("ASViewGuild");
		}
	}
}


























