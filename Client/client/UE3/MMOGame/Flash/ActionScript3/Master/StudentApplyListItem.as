
package ActionScript3.Master
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	
	public class StudentApplyListItem extends ListItemTreeRenderer
	{
		public var tF_name_master:TextField;
		//public var tF_level:TextField;
		public var tF_profession:TextField;

		public var Student_data:StudentData;

		public function StudentListItem()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			visible = false;
			
			this.mouseEnabled = true;
			addEventListener(MouseEvent.CLICK, onRightMenuClick);

			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}


		function updateData(data:Object):void
		{
			Student_data = data as StudentData;
			if ( Student_data  )
			{
				visible = true;
				tF_name_master.text = Student_data.Name;
				//tF_level.text = String( Student_data.Level );
				tF_profession.text = String( Student_data.Profession );
				//this.selected = Student_data.IsSelected;
			}
			else
			{
				visible = false;
			}
		}
		function onRightMenuClick(e:Event)
		{
			if (1 == (e as MouseEventEx).buttonIdx)
			{
				if(Student_data != null)
				{
					ExternalInterface.call("ASRightMenuStudentApplyList", Student_data.Id);
				}
			}
		}
	}
}