package ActionScript3.Widget
{
	import ActionScript3.MyProgressBarPanel;
	import flash.external.ExternalInterface;
	
	public class FBSummaryProgressBar extends MyProgressBarPanel
	{
		override protected function configUI():void
		{
			super.configUI();
			
			tF_title.text = "测试测试";
			tF_title.x = ( width - tF_title.width ) / 2;
			//trace( "FBSummaryProgressBar:  "+castbar_mc.fill_mc.width );
			
			//ExternalInterface.call( "RegisterFBSummaryProgressBar", this);
		}
		override public function TimeUpCallback()
		{
			ExternalInterface.call( "FBSummaryProgressBarTimeUpCallback" );
		}
		//
		override public function SetTitle( strTitle:String )
		{
			tF_title.text = strTitle;
			tF_title.x = ( width - tF_title.width ) / 2;
		}
		
		public function UCSetX( screenWidth:int, offset:int )
		{
			x = ( screenWidth - width ) / 2 + offset;
		}
		//
		public function UCSetY( screenHeightt:int, offset:int )
		{
			y = ( screenHeightt - height ) / 2 + offset;
		}
	}
}