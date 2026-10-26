package UI_GuildTerritoryWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.utils.setInterval;
	import flash.utils.clearInterval;
	import flash.external.ExternalInterface;
	
	public class TerritoryListItem extends ListItemTreeRenderer {
		
		public var btn_ok:Button;
		public var guild_name:TextField;
		public var guild_level:TextField;
		public var tf_num:TextField;
		public var tf_time:TextField;
		public var Id:int=0;
/*		private var tg:uint;
		private var total:int;*/
		override protected function configUI():void
		{
			super.configUI();
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateItemData);
			btn_ok.addEventListener(MouseEvent.CLICK,clickHandler);
		}
		
		//点击进入属地
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASEnterTerritory",Id);
		}
		
		public function updateItemData(dat:Object):void
		{
			if (dat != null)
			{
				visible = true;
				Id=dat.Id;
				guild_name.text=dat.guild_name;
				guild_level.text=String(dat.guild_level);
				btn_ok.enabled=dat.status;
				tf_num.text=String(dat.Num);
				tf_time.text=dat.timer;
/*				clearInterval(tg);
				total=dat.timer;
				updateTimer();*/
			}
			else
			{
				visible = false;
			}	
		}
		
/*		private function updateTimer():void
		{
			if(total>0)
			{
				tf_time.text=timerConvert(total);
				tg=setInterval(step,1000);
			}
		}
		
		private function timerConvert(sceond:int):String
		{
			var h:int=Math.floor(sceond/3600);
			var sec:int=sceond-(3600*h);
			var m:int=0;
			if(sec>0)
			{
				m=Math.floor(sec/60);
			}
			var s:int=sec-(60*m);
			var hh:String="";
			var mm:String="";
			var ss:String="";
			if(h<10)
			{
				hh="0"+h;
			}
			else
			{
				hh=h.toString();
			}
			if(m<10)
			{
				mm="0"+m;
			}
			else
			{
				mm=m.toString();
			}
			if(s<10)
			{
				ss="0"+s;
			}
			else
			{
				ss=s.toString();
			}
            return hh+":"+mm+":"+ss;
		}
		
		private function step():void
		{
			total--;
			if(total<=0)
			{
				clearInterval(tg);
				tf_time.text="00:00:00";
			}
			else
			{
				tf_time.text=timerConvert(total);
			}
		}*/
	}
	
}
