
package UI_ActivityWidget.ActivityAS3
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import scaleform.clik.events.ComponentEvent;

	public class ActivityListItem extends ListItemTreeRenderer
	{
		public var Item_Name:TextField;
		public var Item_Time:TextField;
		public var Item_Person:TextField;
		public var Item_huoyue:TextField;
		public var Item_State:TextField;
		public var Item_CompleteState:TextField;
		public var Item_vips:MovieClip;
		public var Item_StarNum:MovieClip;

		public var Activity_data:ActivityData;

		public var activityID:int = 0;
		override protected function configUI():void
		{
			super.configUI();
			Item_vips.visible =false;
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			visible = false;
		}

		public function setColor(type:int):void
		{
			if(type==1){
				Item_Name.textColor = 0xFFF5DD;
				Item_Person.textColor = 0xFFF5DD;
				Item_Time.textColor = 0xFFF5DD;
				Item_huoyue.textColor = 0xFFF5DD;
				Item_State.textColor = 0xFFF5DD;
				Item_CompleteState.textColor=0xFFF5DD;
			}
			else if(type==2){
				Item_Name.textColor = 0xFBD671;
				Item_Person.textColor = 0xFBD671;
				Item_Time.textColor = 0xFBD671;
				Item_huoyue.textColor = 0xFBD671;
				Item_State.textColor = 0xFBD671;
				Item_CompleteState.textColor=0xFBD671;
			}else{
				Item_Name.textColor = 0xFFFFFF;
				Item_Person.textColor = 0xFFFFFF;
				Item_Time.textColor = 0xFFFFFF;
				Item_huoyue.textColor = 0xFFFFFF;
				Item_State.textColor = 0xFFFFFF;
				Item_CompleteState.textColor=0xFFFFFF;
			}
		}
		
		function updateData(data:Object):void
		{
			Activity_data = data as ActivityData;
			if (Activity_data)
			{
				activityID = Activity_data.Id;
				visible = true;
				Item_Name.text = Activity_data.Name;
				Item_Time.text = Activity_data.Time;
				Item_Person.text = Activity_data.PersonNum;
				Item_huoyue.text = String(Activity_data.Activity);
				Item_State.text = Activity_data.State;
				Item_CompleteState.text = Activity_data.CompleteState;
				Item_vips.visible = Activity_data.IsVip;
				Item_vips.visible =false;
				if(this.selected==true)
				{
					setColor(2);
				}
				else
				{
					setColor(0);
				}
				Item_StarNum.gotoAndStop(Activity_data.StarNum);
			}
			else
			{
				activityID = -1;
				visible = false;
			}
		}
	}

}