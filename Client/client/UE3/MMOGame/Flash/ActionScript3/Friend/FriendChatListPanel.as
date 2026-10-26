package ActionScript3.Friend{
	
	import flash.utils.getDefinitionByName;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	
	public class FriendChatListPanel extends UIComponent
	{
		var _ListItemClassRef:Class;
		public var ChatListItem:Array;
		public var MsgBg:MovieClip;
		
		const OffsetX:int = 0;
		const OffsetY:int = 6;
		var ListHeight:int=8;
		
		public var CallBackUpdateChatList:Function;

		override protected  function configUI():void
		{
			super.configUI();	
			
			ChatListItem = [];
			_ListItemClassRef = getDefinitionByName( "Btn_ChatLine") as Class;
			ListHeight = OffsetY;
		}

		public function AddNewItem():Button
		{
			var NewListItem:Button = new _ListItemClassRef as Button;
			if( NewListItem )
			{
				NewListItem.x = OffsetX;
				NewListItem.y = ListHeight;
				NewListItem.itemid = ChatListItem.length;
				NewListItem.addEventListener( MouseEvent.CLICK , ClickChatListItem );
				ChatListItem.push( NewListItem );
				this.addChild(NewListItem);
				UpdateHeight();
			}
			
			return NewListItem;
		}
		
		private function ClickChatListItem( e:MouseEvent ):void
		{
			if( e.target is Button )
			{
				ExternalInterface.call( "ASFriendChatList" , (e.target as Button).itemid );
			}
		}
		
		public function RemoveItem( Index:int ):Button
		{
			if(ChatListItem)
			{
				if( Index >= 0 && Index < ChatListItem.length )
			    {
				    var btn:Button=( ChatListItem[Index] as Button);
				    this.removeChild( btn );
				  
				    ChatListItem.splice( Index , 1 );
								
				    UpdateChatList( Index );
				    UpdateHeight();
				    return btn;
			    }
			}
			return null;
		}
		
		//从第n项刷新位置
		private function UpdateChatList( Index:int ):void
		{
			if(ChatListItem==null)
			{
				return;
			}
			if( Index >= 0 && Index < ChatListItem.length )
			{
				var i:int = 0;
				for( i = Index ; i < ChatListItem.length ; i++)
				{
					var Item:Button = ChatListItem[i] as Button;
					if( Item )
					{
						if( i == 0 )
						{
							Item.y = OffsetY;
						}
						else
						{
							var LastItem:Button = ChatListItem[i-1] as Button;
							Item.y = LastItem.y + LastItem.height;
						}
						Item.itemid = i;
					}
				}
				UpdateHeight();
			}
		}
		
		private function UpdateHeight():void
		{
			var Num:int=0;
			if(ChatListItem)
			{
				Num = ChatListItem.length;
			}
			if( Num == 0 )
			{
				ListHeight = OffsetY;
			}
			else
			{
				if(ChatListItem &&  ChatListItem[Num-1])
				{
					var ListItem:Button =  ChatListItem[Num-1] as Button;
					if( ListItem )
				    {
					    ListHeight = ListItem.y + ListItem.height;
				    }
					else
					{
						ListHeight = OffsetY;
					}
				}
			}
			if( MsgBg )
			{
				MsgBg.height = ListHeight;
				height = ListHeight;
			}
			if( CallBackUpdateChatList != null )
			{
				CallBackUpdateChatList();
			}
			
		}
	}
}