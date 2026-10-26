package UI_FBTask.FBTaskAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	
	import UI_FBTask.FBTaskAS3.FBTaskListItemData;

	public class FBTaskListItemMainProgress extends UIComponent
	{
		public var MainProgressTitleTf:TextField;
		
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
			
			MainProgressTitleTf.text = displayText;
			
			if( listItemData.CurInt >= listItemData.TargetInt ){
				MainProgressTitleTf.textColor = 0x00ff00;
			}
			else{
				MainProgressTitleTf.textColor = 0xffffff;
			}
		}
	}
}