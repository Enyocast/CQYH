package ActionScript3.Option
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Rectangle;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Option.ConfigAudio;
	import ActionScript3.Option.ConfigVideo;
	import ActionScript3.Option.OptionData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.data.DataProvider;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import scaleform.clik.events.ComponentEvent;
	
	public class OptionConfig extends MyPanel
	{
		public var tab_video:RadioButton;
		public var tab_sound:RadioButton;
		public var tab_game:RadioButton;
		public var tab_input:RadioButton;
		
		public var page_video:ConfigVideo;
		public var page_sound:ConfigAudio;
		
		public var frame_max_mc:MovieClip;
		
		override protected  function configUI():void
		{
			ShowMode="OPTION";
			super.configUI();

			tab_video.addEventListener("click",OpenVideo);
			tab_sound.addEventListener("click",OpenSound);
			this.addEventListener(ComponentEvent.SHOW,hideViewHandler);
			page_video.advanced_mc.addEventListener("click", advancedPanelShowHandler);
			OpenVideo();
			tab_video.selected = true;
		}
		
		override public function UCShow(v:Boolean, priority:int):void
		{
			super.UCShow(v, priority);
			if(page_video)
			{
				page_video.setDropdownMenuDisplayPriority(priority);
			}
		}
		
		private function hideViewHandler(evt:Event):void
		{
			page_video.closeDropList();
		}
		private function advancedPanelShowHandler(evt:MouseEvent):void
		{
			page_video.advanced_panel.visible = !page_video.advanced_panel.visible;
			stageChangeHandler(null);
		}
		
		public function DisiableAll()
		{
			page_video.visible = false;
			page_sound.visible = false;
		}
		public function OpenVideo()
		{
			DisiableAll();
			page_video.visible = true;
			stageChangeHandler(null);
		}
		public function OpenSound()
		{
			DisiableAll();
			page_sound.visible = true;
			stageChangeHandler(null);
		}
/*		private function testData():void
		{
			var dat:OptionData=new OptionData();
			dat.input1_enable=true;
			var i:int=0;
			for(i=0;i<12;i++){
				var obj:Object={};
				obj.KeyName="F"+i;
				obj.ComKeyName="ALT";
				obj.KeyEnum=1;
				dat.SlotKeyList.push(obj);
			}
			page_input.FillToUI(dat);
		}*/
		public function UCFillToUI(dat:OptionData)
		{
			SetWindowTitle(dat.wnd_title);
			
			page_video.FillToUI(dat);
			page_sound.FillToUI(dat);
		}
		public function UCVideoLevelReq(dat:OptionData)
		{
			page_video.VideoLevelReq(dat);
		}
		
		public function UCVideoAdvanceLevelReq(dataList:Array)
		{
			page_video.VideoAdvanceLevel(dataList);
		}
		override public function set visible(value:Boolean):void
		{
			super.visible=value;
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth=GameDispathcher.getInstance().StageWidth;
			this.cavasHeight=GameDispathcher.getInstance().StageHeight;
			if(page_video.visible && page_video.advanced_panel.visible){
				this.x = (cavasWidth-  frame_max_mc.width)>>1; 
			    this.y = (cavasHeight - frame_max_mc.height)>>1;
			}else{
				this.x=(cavasWidth-MyWindowsFrame_mc.width)>>1;
			    this.y=(cavasHeight-MyWindowsFrame_mc.height)>>1;
			}
		}
	}
}