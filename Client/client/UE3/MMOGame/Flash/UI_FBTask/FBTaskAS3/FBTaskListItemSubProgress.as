package UI_FBTask.FBTaskAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	
	import UI_FBTask.FBTaskAS3.FBTaskListItemData;

	public class FBTaskListItemSubProgress extends UIComponent
	{
		public var SubProgressTitleTf:TextField;
		public var SubProgressTitlePreTf:TextField;
		
		public function UpdateItem( listItemData:FBTaskListItemData ):void
		{
			var displayText:String;
			displayText = listItemData.TaskTitle;
			
			if( listItemData.TargetInt > 0 ){
				displayText += "    ";
				displayText += listItemData.CurInt;
				displayText += "/";
				displayText += listItemData.TargetInt;
			}
			
			SubProgressTitleTf.text = displayText;
			
			if( listItemData.CurInt >= listItemData.TargetInt ){
				SubProgressTitleTf.textColor = 0x00ff00;
				SubProgressTitlePreTf.textColor = 0x00ff00;
			}
			else{
				SubProgressTitleTf.textColor = 0xffffff;
				SubProgressTitlePreTf.textColor = 0xffffff;
			}
		}
	}
}