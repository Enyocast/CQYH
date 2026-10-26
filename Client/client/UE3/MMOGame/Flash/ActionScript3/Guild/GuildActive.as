package ActionScript3.Guild {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	
	public class GuildActive extends UIComponent {
		
		public var active_list_mc:ScrollingList;
		public var tabTitle:MovieClip;
		public var openActive:GuildOpenActive;
		override protected function configUI():void
		{
			super.configUI();
			updateGuildActiveList([]);
			openActive.visible = false;
			//testData();
		}
		
		public function updateGuildActiveList(dat:Array):void
		{
			active_list_mc.dataProvider = new DataProvider(dat);
			active_list_mc.invalidateData();
			active_list_mc.validateNow();
		}
		
		public function ShowGuildActiveConfirm(dat:Object):void
		{
			openActive.visible = true;
			openActive.updateData(dat);
		}
		
		public function HideGuildActiveConfirm():void
		{
			openActive.visible = false;
		}
		
/*		private function testData():void
		{
			var i:int=0;
			var arr:Array=[];
			for(i;i<15;i++)
			{
				var obj:GuildActiveData=new GuildActiveData();
				obj.ID=i;
				obj.active_content="ddddddddd"+i;
				obj.active_map="盟主"+i
				obj.active_name="test"+i;
				obj.active_state=i;
				obj.active_timer="2010";
				obj.current=0;
				obj.max=i+1;
				arr.push(obj);
			}
			updateGuildActiveList(arr);
		}*/
	}
	
}
