package ActionScript3.Guild {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.events.ButtonEvent;
	
	
	public class GuildActiveListItem extends ListItemTreeRenderer {
		
		public var active_name:TextField;
		public var active_timer:TextField;
		//public var active_map:TextField;
		public var active_content:TextField;
		public var active_target:TextField;
		public var active_state:TextField;
		public var btn_play:Button;
		public var ActiveId:int;
		override protected function configUI():void
		{
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
			btn_play.addEventListener(ButtonEvent.CLICK,clickHandler);
		}
		
		private function clickHandler(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASGuildActivityClickOpen",ActiveId);
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				visible = true;
				var obj:GuildActiveData=data as GuildActiveData;
				//trace("data========================",obj,obj.ID,obj.active_name,obj.active_timer,obj.active_content)
				ActiveId=obj.ID;
				active_name.text = obj.active_name;
				active_timer.text = obj.active_timer;
				if(obj.active_timer == "待定")
				{
					active_timer.textColor = 0x84ec60;
				}
				else
				{
					active_timer.textColor = 0xebc96a;
				}
				//active_map.text = obj.active_map;
				active_content.htmlText = obj.active_content;
				active_target.text=obj.current+"/"+obj.max;
				active_state.htmlText=getStateName(obj.active_state);
			}
			else
			{
				visible = false;
			}	
		}
		
		public function getStateName(dat:int):String
		{
			var str:String="";
			btn_play.visible=false;
			switch(dat)
			{
				case 0:
				{
					btn_play.visible=true;
					str="";
					break;
				}
				case 1:
				{
					str="<font color='#84ec60'>已开启</font>";
					break;
				}
				case 2:
				{
					str="<font color='#84ec60'>已结束</font>";
					break;
				}
				case 3:
				{
					str="<font color='#fb4e1a'>无权开启</font>";
					break;
				}
			}
			return str;
		}
	}
	
}
