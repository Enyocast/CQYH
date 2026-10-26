package UI_BattleSummary.BattleSummaryAS3
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import UI_BattleSummary.BattleSummaryAS3.BtlScoreListTitleData;

	public class BtlScoreListTitle extends MovieClip 
	{
		public var Title_mc:MovieClip;
		public var ColTitle_tf1:TextField;
		public var ColTitle_tf2:TextField;
		public var ColTitle_tf3:TextField;
		public var ColTitle_tf4:TextField;
		public var ColTitle_tf5:TextField;
		public var ColTitle_tf6:TextField;
		
		public var titleData:BtlScoreListTitleData;

		//
		public function updateData(data:Object):void
		{
			titleData = data as BtlScoreListTitleData;
			
			if( titleData ){
				visible = true;
				
				//
				if( titleData.TeamID == 1 ){
					Title_mc.gotoAndStop( 1 );
				}
				else{
					Title_mc.gotoAndStop( 2 );
				}
				var teamName:TextField = Title_mc.getChildByName("textTf") as TextField;
				if( teamName != null ){
					teamName.text = titleData.TeamName;
				}
			}
			else{
				visible = false;
			}
		}
		//
	}

}