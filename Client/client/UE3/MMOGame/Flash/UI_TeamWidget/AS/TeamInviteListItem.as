package UI_TeamWidget.AS{
	
	import ActionScript3.MyPanel;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.events.TextEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.text.TextField;
	
	public class TeamInviteListItem extends ListItemTreeRenderer
	{
		public var select_chk:Button;
		public var item_text_0:TextField;
		public var item_text_1:TextField;
		public var item_text_2:TextField;

		public var playerId:int = -1;
		
		override protected function configUI():void
		{
			super.configUI();
			select_chk.addEventListener(MouseEvent.CLICK, ClickInviteItem);
			setUpdateDataCallBack( updateData );
			visible = false;
		}

		private function ClickInviteItem(e:Event):void
		{
			var btn:Button = e.target as Button;
			if(btn)
			{
				if(!btn.selected)
				{
					ExternalInterface.call("ASClickSelectPlayer", playerId);
				}
				else
				{
					ExternalInterface.call("ASClickUnSelectPlayer", playerId);
				}
			}
		}

		public function updateData(data:Object):void
		{
			if (data)
			{
				visible = true;
				select_chk.selected = data.PlayerSelected;
				select_chk.label = "";
				item_text_0.text = data.Name;
				//item_text_1.text = String(data.HuoYue);
				
				//item_text_1.text = String(data.Level) + "级";
				item_text_2.text = data.ClassName;
				//item_text_4.text = data.Position;
				playerId = data.playerId;
			}
			else
			{
				visible = false;
				playerId = -1;
			}
		}
	}
}