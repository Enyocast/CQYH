//
// 家族副本结束
//
package ActionScript3.Guild
{
	import scaleform.clik.controls.Button;
	import ActionScript3.MyPanel;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import ActionScript3.Common.Events.ParamEvent;

	public class GuildDungeonExitPanel extends MyPanel
	{
		public var guild_dungeon_exit_mc:Button;
		
		override protected function configUI():void
		{
			this.ShowMode="GuildExit";
			super.configUI();
			guild_dungeon_exit_mc.addEventListener(MouseEvent.CLICK,onBtClickExit);
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-130;
			this.y=cavasHeight-80;
		}
		
		private function onBtClickExit(evt:MouseEvent):void
		{
			ExternalInterface.call("ASLeaveGuildDungeonEx");
		}
	}
}


























