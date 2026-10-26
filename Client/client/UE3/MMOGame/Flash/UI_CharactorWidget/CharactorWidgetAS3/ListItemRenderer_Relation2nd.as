package UI_CharactorWidget.CharactorWidgetAS3 {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	
	
	public class ListItemRenderer_Relation2nd extends MovieClip {
		
		public var dataBuf:Object=null;
        //public var sign_mc:MovieClip;
        public var titleName:TextField;
        //public var bar:levelBar;
        public var lastType:Number = -1;
        //public var TrackCheck_mc:CheckBox;
        //public var btn_ShowInfo:Button;
		public var TipsObj:Object = {title:"object", text:"objectTips" };
		public function ListItemRenderer_Relation2nd() {
			//TrackCheck_mc.addEventListener("click", TrackClick);
			//btn_ShowInfo.addEventListener("click", ShowInfoClick);
		}
		
		function updateData(data:Object):void
		{
			dataBuf = data;
			if (data && data.deepth ==1)
			{
				visible = true;
				//更新文字
				titleName.text 	= data.label;
				TipsObj.title 	= data.label;
				TipsObj.text  	= data.tips;
				if(data.trackForceID == data.forceID)
				{
					//TrackCheck_mc.selected = true;
				}
				else{
					//TrackCheck_mc.selected = false;
				}		
			}
			else
			{
				visible = false;
			}
		}
		
		function TrackClick(e:MouseEvent):void
		{
			if(visible){
				ExternalInterface.call( "ASSelectTrackForceID",dataBuf.forceID );
				ExternalInterface.call( "ASShowInfoBox",dataBuf );
			}	
		}
		
		function ShowInfoClick(e:MouseEvent):void
		{
			if(visible){
				ExternalInterface.call( "ASRefreshInfoBox",dataBuf );
			}		
		}
		

	}
	
}
