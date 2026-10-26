package ActionScript3.Master
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.core.UIComponent;
	
	public class CongratulateComponet extends UIComponent
	{
		public var icon_mc:MovieClip;
		public var tf_Title:TextField;
		public var tF_name_master:TextField;
		public var congratulation_mc:Button;
		
		public var  dataCong:MasterCongratulationData;
		
		override protected function configUI():void
		{
			super.configUI();
			icon_mc.addEventListener(MouseEvent.ROLL_OVER, onRollOverInfo);
			icon_mc.addEventListener(MouseEvent.ROLL_OUT, onRollOutInfo);
		}
		function onRollOverInfo( e:Event )
		{
			if(dataCong)
				ExternalInterface.call("ASShowTips_MasterGift",this,dataCong.nMailID);
		}

		function onRollOutInfo( e:Event )
		{
			ExternalInterface.call("ASHideTips_MasterGift" );
		}
		public function SetData(data:Object)
		{
			dataCong = data as MasterCongratulationData;
			if(dataCong != null)
			{
				tF_name_master.text = dataCong.Name;
				tf_Title.text = dataCong.Title;
				
				if(dataCong.nType == 1)
					icon_mc.gotoAndStop("_1");
				else if(dataCong.nType == 2)
					icon_mc.gotoAndStop("_2");
				else
					icon_mc.gotoAndStop("_3");
			}
		}
	}
}
