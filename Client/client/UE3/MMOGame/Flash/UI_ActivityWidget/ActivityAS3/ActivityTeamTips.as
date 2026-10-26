package UI_ActivityWidget.ActivityAS3{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import UI_ActivityWidget.ActivityAS3.ActivityTeamMemberItem;

	public class ActivityTeamTips extends UIComponent
	{
		public var activity_title:TextField;
		public var title_0:TextField;
		public var title_1:TextField;
		public var title_2:TextField;
		public var title_3:TextField;
		
		public var level_limit_title:TextField;
		public var level_limit_content:TextField;
		public var guild_limit_title:TextField;
		public var guild_limit_content:TextField;
		public var class_limit_title:TextField;
		public var class_limit_content:TextField;
		
		public var member_item0:ActivityTeamMemberItem;
		public var member_item1:ActivityTeamMemberItem;
		public var member_item2:ActivityTeamMemberItem;
		public var member_item3:ActivityTeamMemberItem;
		public var member_item4:ActivityTeamMemberItem;
		
		override protected  function configUI():void 
		{		
			super.configUI();			
			//ExternalInterface.call("ASRegisterActivityTeamTipsPanel", this);
			level_limit_title.visible = false;
			guild_limit_title.visible = false;
			class_limit_title.visible = false;
			level_limit_content.visible = false;
			guild_limit_content.visible = false;
			class_limit_content.visible = false;
			title_1.visible = false;
		}
		
		
		public function UCUpdatePanel(data:Object)
		{
			activity_title.text = data.ActivityName;
			
			title_0.text = data.title_0;
			title_1.text = data.title_1;
			title_2.text = data.title_2;
			title_3.text = data.title_3;
			
			level_limit_title.text = data.level_limit_title;
			guild_limit_title.text = data.guild_limit_title;
			class_limit_title.text = data.class_limit_title;
			
			level_limit_content.text = data.level_limit_content;
			guild_limit_content.text = data.guild_limit_content;
			class_limit_content.text = data.class_limit_content;
			
			var teamMemberArray:Array = data.MemberArray as Array;
			if(!teamMemberArray)
			{
				return;
			}
			
			var type:int = data.TipsType;
			var i:int = 0;
			var item:ActivityTeamMemberItem = null;
			if(type == 0)
			{
				//活动
				for(i = 0; i < 5; ++i)
				{
					item = getChildByName("member_item" + i) as ActivityTeamMemberItem;
					if(item)
					{
						if(i < teamMemberArray.length)
						{
							item.UpdateDataAsActivity(teamMemberArray[i]);
						}
						else
						{
							item.visible = false;
						}
					}
				}
			}
			else
			{
				//副本
				for(i = 0; i < 5; ++i)
				{
					item = getChildByName("member_item" + i) as ActivityTeamMemberItem;
					if(item)
					{
						if(i < teamMemberArray.length)
						{
							item.UpdateDataAsFB(teamMemberArray[i]);
						}
						else
						{
							item.visible = false;
						}
					}
				}
			}
		}
	}
}