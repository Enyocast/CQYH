
package ActionScript3.Friend
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ListEvent;

	public class  FriendNameListItem extends ListItemTreeRenderer
	{
		public var ContactStatus:MovieClip;
		
		public var tF_playerName:TextField;
		public var tabclose0:MovieClip;
		public var msg_num:MovieClip;
		public var mc_effect:MovieClip;
		public var tipsHtml:String;
		
		public var friendData:FriendNameListItemData;
		
		override protected function configUI():void
		{
			super.configUI();
			tabclose0.visible=false;
			msg_num.visible=false;
			mc_effect.visible=false;
			mc_effect.gotoAndStop(1);
			this.addEventListener(MouseEvent.ROLL_OVER,overHandler);
			this.addEventListener(MouseEvent.ROLL_OUT,outHandler);
			tabclose0.addEventListener(MouseEvent.CLICK, OnCloseChatWindow);
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			visible = false;
		}

		private function overHandler(e:MouseEvent):void
		{
			msg_num.visible=false;
			tabclose0.visible=true;
			tF_playerName.width=60;
			if(friendData)
			  tipsHtml=friendData.RoleName;
			ExternalInterface.call("ASShowTips_PlainText",this );
		}
		private function outHandler(e:MouseEvent):void
		{
			tabclose0.visible=false;
			if(friendData && friendData.MsgNum>0){
				msg_num.visible=true;
				tF_playerName.width=60;
			}
			else
			{
				tF_playerName.width=86;
			}
			ExternalInterface.call("ASHideTips_PlainText",this );
		}
		private function OnCloseChatWindow(e:MouseEvent):void
		{
			if(friendData)
				ExternalInterface.call( "ASCloseRoleChatWnd" ,friendData.RoleID );
			outHandler(null);
		}
		
		public function updateData(data:Object):void
		{
			friendData = data as FriendNameListItemData;
			if(friendData)
			{
				visible = true;
				tabclose0.visible=false;
				tF_playerName.width=86;
				tF_playerName.text = friendData.RoleName;
/*				if(tF_playerName.textWidth>tF_playerName.width)
				{
					var str:String=friendData.RoleName.substr(0,5);
					str+="...";
					tF_playerName.text=str;
				}*/
				if( friendData.OnLine == 0)
				{
					ContactStatus.gotoAndStop("online");
				}
				else 
				{
					ContactStatus.gotoAndStop(friendData.OnLine + 1);
				}
				
			}
			else
				visible = false;
		}
		public function clear():void
		{
			msg_num.visible=false;
			mc_effect.visible=false;
			mc_effect.gotoAndStop(1);
			friendData.MsgNum=0;
			if(tabclose0.visible==true)
			{
				tF_playerName.width=60;
			}
			else
			{
				tF_playerName.width=86;
			}
		}
		
		public function UCShowEffect():void
		{
			friendData.MsgNum+=1;
			if(friendData.MsgNum==0)
			{
				clear();
			}
			else
			{
			    msg_num.visible=true;
				msg_num.txtNum.text=friendData.MsgNum.toString();
				tF_playerName.width=60;
				mc_effect.visible=true
				mc_effect.gotoAndPlay(1);
			}
		}
		
		override protected function setState(state:String):void {
			super.setState(state);
			if(selected){	
				tF_playerName.textColor=0xFfeac5;
			}else{
				tF_playerName.textColor=0xBFDAE8;
			}
		}
	}
}