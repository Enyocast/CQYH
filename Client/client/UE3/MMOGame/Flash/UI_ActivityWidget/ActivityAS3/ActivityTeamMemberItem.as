package UI_ActivityWidget.ActivityAS3{
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	
	public class ActivityTeamMemberItem extends UIComponent
	{
		public var MemberLable0:TextField;
		public var MemberLable1:TextField;
		public var MemberLable2:TextField;
		public var MemberLable3:TextField;
		
		public function UpdateDataAsActivity(data:Object):void
		{
			MemberLable1.visible = false;
			if(data)
			{
				this.visible = true;
				MemberLable0.text = data.Name;
				MemberLable1.text = String(data.CurTimes) + "/" + String(data.MaxTimes);
				MemberLable2.text = data.ClassName;
				MemberLable3.text = String(data.Level) + "级";
			}
			else
			{
				this.visible = false;
			}
		}
		
		public function UpdateDataAsFB(data:Object):void
		{
			MemberLable1.visible = false;
			if(data)
			{
				this.visible = true;
				MemberLable0.text = data.Name;
				MemberLable1.text = String(data.HuoYue);
				MemberLable2.text = data.ClassName;
				MemberLable3.text = String(data.Level) + "级";
			}
			else
			{
				this.visible = false;
			}
		}
	}
}