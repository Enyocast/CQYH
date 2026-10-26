package ActionScript3.Friend{
	
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import ActionScript3.Friend.FriendChatListPanel;
	import flash.external.ExternalInterface;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import flash.display.MovieClip;
	import ActionScript3.Common.FalshEffect;
	import scaleform.clik.motion.Tween;
	import fl.transitions.easing.Strong;
	
	public class FriendChatHintPanel extends MyPanel
	{
		public var FriendChatList:FriendChatListPanel;
		public var FriendChatHintButton:Btn_MinizedPanel;
		override protected  function configUI():void
		{
			ShowMode="FriendChatHint";
			super.configUI();
			if( FriendChatHintButton )
			{
				FriendChatHintButton.addEventListener( MouseEvent.CLICK , ClickFriendChatHint );
			}
			if( FriendChatList )
			{
				FriendChatList.CallBackUpdateChatList = UpdateChatListPos;
				
				FriendChatList.visible = false;
			}
			UpdateChatListPos();
			stageChangeHandler(null);
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-306;
			this.y=cavasHeight-80;
		}
		
		//设置显示聊天对象头像
		public function setHead(Career:int,Sex:int):void
		{
			setHintBtnImg(Career,Sex);
			this.x=0;
			var buttonTween:Tween = new Tween( 1000 ,this ,{ x:cavasWidth-300} , {paused:true,ease:Strong.easeOut,onComplete:null,loop:false});
			buttonTween.reset();
			buttonTween.paused = false;
		}
		
		public function setHeadByMinimize(Career:int,Sex:int):void
		{
			setHintBtnImg(Career,Sex);
		}
		
		public function setHintBtnImg(Career:int,Sex:int):void
		{
			var frame:int=0;
			if(Sex==1)
			{
				frame=Career+1;
			}
			else
			{
				frame=Career+6;
			}
			FriendChatHintButton.setHeadImg(frame);
		}
		public function AddNewItem():Button
		{
			if( FriendChatList )
			{
				return FriendChatList.AddNewItem();
			}
			return null;
		}
		
		public function RemoveItem( Index:int ):Object
		{
			if( FriendChatList )
			{
				return FriendChatList.RemoveItem(Index);
			}
			return null;
		}
		
		private function ClickFriendChatHint(evt:MouseEvent):void
		{
			if(FriendChatList && FriendChatList.ChatListItem)
			{
				var ListItem:Button;
				if(FriendChatList.ChatListItem.length==1)
				{
					ListItem =  FriendChatList.ChatListItem[0] as Button;
					ExternalInterface.call( "ASFriendChatList" , ListItem.itemid );
				}
				else if(FriendChatList.ChatListItem.length==0)
				{
					ExternalInterface.call( "ASShowFriendChatList");
				}
				else
				{
					FriendChatList.visible = !FriendChatList.visible;
				}
			}
			else
			{
				FriendChatList.visible = !FriendChatList.visible;
			}
		}
		
		//在List更新后执行回调到这里
		private function UpdateChatListPos():void
		{
			if( FriendChatList && FriendChatHintButton )
			{
				FriendChatList.y = FriendChatHintButton.y - FriendChatList.height+12;
			}
			
		}
	}
}