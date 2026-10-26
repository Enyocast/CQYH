
package UI_ActivityWidget.ActivityAS3
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.Event;
	import scaleform.clik.events.ComponentEvent;
	
	public class ActivityTeamListItem extends ListItemTreeRenderer
	{
		public var TeamName:TextField;
		public var TeamLevel:TextField;
		public var MemberCount:TextField;
		
		public var TeamName_self:TextField;
		public var TeamLevel_self:TextField;
		public var MemberCount_self:TextField;
		
		

		//public var  activityData:ActivityData;
		
		public var  TeamId:int = -1;
		
		override protected  function configUI():void 
		{		
			super.configUI();			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			visible = false;
		}
		public function setColor(type:int):void
		{
			if(type==1){
				TeamName_self.textColor = 0xFFF5DD;
				TeamLevel_self.textColor = 0xFFF5DD;
				MemberCount_self.textColor=0xFFF5DD;
			}else if(type==2){
				TeamName_self.textColor = 0xFBD671;
				TeamLevel_self.textColor = 0xFBD671;
				MemberCount_self.textColor=0xFBD671;
			}else{
				TeamName_self.textColor = 0xFFFFFF;
				TeamLevel_self.textColor = 0xFFFFFF;
				MemberCount_self.textColor=0xFFFFFF;
			}
		}
		
		function updateData(data:Object):void
		{
			//activityData = data as ActivityData;
			TeamId = -1;
			visible = false;
			if (data)
			{
				TeamId = data.TeamId;
				visible = (TeamId > 0);
				TeamName_self.visible = data.bMyTeam;
				TeamLevel_self.visible = data.bMyTeam;
				MemberCount_self.visible = data.bMyTeam;
				
				TeamName.visible = !data.bMyTeam;
				TeamLevel.visible = !data.bMyTeam;
				MemberCount.visible = !data.bMyTeam;
				
				if(data.bMyTeam)
				{
					TeamName_self.text = data.TeamName;
					TeamLevel_self.text = String(data.TeamLevel) + "级";
					MemberCount_self.text = String(data.MemberCount);
				}
				else
				{
					TeamName.text = data.TeamName;
					TeamLevel.text = String(data.TeamLevel) + "级";
					MemberCount.text = String(data.MemberCount);
				}
			}
			else
			{
				TeamId = -1;
				visible = false;
			}
		}
	}
}