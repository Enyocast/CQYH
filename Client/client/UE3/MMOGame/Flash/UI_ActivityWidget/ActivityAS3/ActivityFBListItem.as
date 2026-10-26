
package UI_ActivityWidget.ActivityAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import scaleform.gfx.TextFieldEx;
	import flash.events.TextEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import scaleform.clik.events.ComponentEvent;
	import flash.events.Event;
	
	public class ActivityFBListItem extends ListItemTreeRenderer
	{
		public var Item_Name:TextField;
		public var Item_Person:TextField;
		public var Item_Level:TextField;
		public var Item_costhuoyue:TextField;
		public var Item_CompleteState:TextField;

		public var  activityData:ActivityData;
		
		public var  activityID:int = 0;
		override protected  function configUI():void 
		{		
			super.configUI();			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			visible = false;
		}
		
		public function setColor(type:int):void
		{	if(type==1){
				Item_Name.textColor = 0xFFF5DD;
				Item_Person.textColor = 0xFFF5DD;
				Item_Level.textColor = 0xFFF5DD;
				Item_costhuoyue.textColor = 0xFFF5DD;
				Item_CompleteState.textColor = 0xFFF5DD;
			}
			else if(type==2){
				Item_Name.textColor = 0xFBD671;
				Item_Person.textColor = 0xFBD671;
				Item_Level.textColor = 0xFBD671;
				Item_costhuoyue.textColor = 0xFBD671;
				Item_CompleteState.textColor = 0xFBD671;
			}else{
				Item_Name.textColor = 0xFFFFFF;
				Item_Person.textColor = 0xFFFFFF;
				Item_Level.textColor = 0xFFFFFF;
				Item_costhuoyue.textColor = 0xFFFFFF;
				Item_CompleteState.textColor = 0xFFFFFF;
			}
		}

		function updateData(data:Object):void
		{
			activityData = data as ActivityData;
			if (activityData)
			{
				activityID   = activityData.Id;
				visible = true;
				Item_Name.text = activityData.Name;
				Item_Person.text = activityData.PersonNum;
				Item_Level.text = activityData.Level;
				Item_costhuoyue.text = String(activityData.Activity);
				Item_CompleteState.text = activityData.CompleteState;
/*				if(this.selected==true){
					setColor(2);
				}else{
					setColor(0);
				}*/
			}
			else
			{
				activityID = -1;
				visible = false;
			}
		}
	}
}