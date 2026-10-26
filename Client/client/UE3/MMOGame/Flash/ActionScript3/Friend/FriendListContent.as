package ActionScript3.Friend
{

	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyActivePanel;
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyScrollPanel;
	import ActionScript3.Friend.ContactListStatic;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ButtonBar;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ButtonBarEvent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.SliderEvent;
	import scaleform.gfx.Extensions;
	import scaleform.gfx.MouseEventEx;

	//
	public class FriendListContent extends ContactListBase
	{
		var _classTitleRef:Class;
		//var _ListArray:Array;		
		var MaxGroup:int;
		
		//好友组的三位一体模式，因为as中没有struct
		//好友列表组的组，SetFriendNum
		//var _GroupFriendListArray:Array;
		//好友分组的标题组
		//var _GroupFriendTitleArray:Array;
		//好友分组的内容组
		//var _GroupFriendContentArray:Array;
		
		private var titleDic:Dictionary;//标题
		private var listDic:Dictionary;//列表
		private var contentDic:Dictionary;//内容
		
		public var PlayerTips:MovieClip;

		override protected function configUI():void
		{
			super.configUI();
			initData();
		}
		
		private function initData():void
		{//初始化数据
			MaxGroup = ContactListStatic.MaxGroup;
			if(titleDic==null)
			{
				titleDic=new Dictionary()
				listDic=new Dictionary();
				contentDic=new Dictionary();
			}
			if(_classTitleRef==null)
			{
				_classTitleRef = getDefinitionByName("ContactListTitle") as Class;
			}
			if(_classItemRef==null)
			{
				_classItemRef = getDefinitionByName("ContactListRender") as Class;
			}
		}
		
		public function SetFriendGroupListData( data:Object ):void
		{
			initData();
			if(titleDic[data.groupId])
			{
				titleDic[data.groupId].onlineNum = data.onlineNum;
				titleDic[data.groupId].totalNum = data.memberNum;
				_SetFriendGroupNum( data.groupId  );
				var list:Array = data.memberList;
				if(list)
				{
					var size:int = list.length;
					var i:int=0;
					for( i = 0 ; i < size; i++ )
					{
						var itemData = list[i];
						var GroupFriendContent = contentDic[ data.groupId ];
						if ( GroupFriendContent == null || GroupFriendContent == undefined )
						{
							return;
						}
						var GroupFriendList:Array = listDic[ data.groupId ];
						if( GroupFriendList && GroupFriendList.length > i )
						{
							ContactListStatic.SetItemValue( GroupFriendList[i] , itemData.name , itemData.lv , itemData.classTxt , itemData.location , itemData.sign , itemData.roleId , itemData.stats , itemData.iconPath );
						}
						
					}
				}
			}
		}
		
		private function _SetFriendGroupNum( GroupId:int  ):void
		{
			var i:int = 0;
			var j:int = 0;
			var dec:int = 0;
            
			if (listDic[GroupId] == null || listDic[GroupId] == undefined )
			{
				var newList:Array = [] ;
				listDic[GroupId] = newList;
			}
			var Num:int = titleDic[GroupId].totalNum;
			var title = titleDic[GroupId].titleMc ;
			if (title)
			{
				title.label = titleDic[GroupId].titleName + "  (" + titleDic[GroupId].onlineNum + "/" + titleDic[GroupId].totalNum + ")";
			}
			var FriendList:Array = listDic[GroupId];
			var GroupFriendContent = contentDic[GroupId];
			if ( GroupFriendContent == null || GroupFriendContent == undefined )
			{
				return;
			}
			if (FriendList.length > Num)
			{
				dec = FriendList.length - Num;
				for (i = 0; i< dec; i++)
				{
					GroupFriendContent.removeChild( FriendList.pop() );
				}
			}
			else if ( FriendList.length < Num )
			{
				dec = Num - FriendList.length;
				for (i = 0; i< dec; i++)
				{
					AddFriend( GroupId );
				}
			}
			UpdateFriendGroup();
			//UpdateFriendHeight();
		}

/*		private function UpdateFriendHeight():void
		{
			var item:MovieClip;
			_ListContentHeight = 0;
			var i:int = 0;
			for (i = 0; i < MaxGroup; i++)
			{
				if (contentDic[i] == null || contentDic[i] == undefined)
				{
					continue;
				}				
				var ListArray:Array = listDic[i];
                var l:int=ListArray.length;
				if (l > 0)
				{
					item = ListArray[l - 1];
					if (item.parent.visible)
					{
						_ListContentHeight += (item.y + item.height + item.parent.y);
					}
					else
					{
						_ListContentHeight += 29;
					}
				}
				else
				{
					_ListContentHeight += 29;
				}
			}
		}*/
		
		private function UpdateFriendGroup():void
		{
			var contentMc:MovieClip;
			var yy:int=0;
			_ListContentHeight=0;
			var i:int=0;
			for (i = 0; i < MaxGroup; i++)
			{
				if (titleDic[i] == null || titleDic[i] == undefined)
				{
					continue;
				}
				var tile:Object=titleDic[i];
				if(tile.titleMc == null)
				{
					continue;
				}
				var Title:MovieClip = tile.titleMc;
				_ListContentHeight+=Title.height;
				Title.y=yy;
				contentMc = contentDic[i];//自己的内容
				contentMc.y=Title.y+Title.height;
				if (contentMc.visible)
				{
					_ListContentHeight+=contentMc.height;
					yy = contentMc.y + contentMc.height;
				}
				else
				{
					yy = contentMc.y;
				}
			}
			(parent as ContactListContent).onFriendGroupUpdated();
		}
		
		private function FolderList( evt:MouseEvent ):void
		{
			if (evt is MouseEventEx )
			{
				var Item:Button = evt.target as Button;
				if( !Item )
				{
					return;
				}
				var GroupId:int = Item.itemid;
				if((evt as MouseEventEx).buttonIdx == 0)
				{//左键
					if (evt.target is Button)
					{
						contentDic[GroupId].visible = ! contentDic[GroupId].visible;
						UpdateFriendGroup();
						//UpdateFriendHeight();
					}
				}
				else
				{
					var pos:Point = new Point  ;
					pos.x = Item.x + Item.width;
					pos.y = Item.y;
					pos = Item.parent.localToGlobal(pos);
					var titleText = titleDic[GroupId].titleName;
					ExternalInterface.call( "ASFriendFolderRightClick",pos.x, pos.y,Item , Item.itemid,titleText);
				}
			}
		}
		
		//生成新的，如果已有就只是改个名
		public function CreateNewGroup( GroupName:String , GroupId:int ):void
		{
			initData();
			var NewGroupTitle:Button = null;
			var NewGroupContent = null;
			var i:int;

			if ( GroupId <0 || GroupId > MaxGroup )
			{
				return;
			}

			if (titleDic[GroupId] != null && titleDic[GroupId] != undefined)
			{//已有,改个名
				titleDic[GroupId].titleName = GroupName;
				_SetFriendGroupNum( GroupId );
				return;
			}

			//创建默认的“好友group”Title
			if (! NewGroupTitle)
			{
				NewGroupTitle = new _classTitleRef  ;
				NewGroupTitle.name = "Title" + GroupId;
				NewGroupTitle.label = GroupName;
				NewGroupTitle.toggle = true;
				NewGroupTitle.x = 0;
				NewGroupTitle.y = _ListContentHeight;
				this.addChild( NewGroupTitle );

				NewGroupTitle.addEventListener( MouseEvent.CLICK , FolderList,false,0,true);
				NewGroupTitle.selected = true;
				titleDic[GroupId] = { titleMc:NewGroupTitle , titleName:GroupName , onlineNum:0 , totalNum:0 };
				NewGroupTitle.itemid = GroupId;
			}

			//创建默认的“好友group”Content
			if (! NewGroupContent)
			{
				NewGroupContent = new MovieClip  ;
				NewGroupContent.name = "Content" + GroupId;
				NewGroupContent.x = NewGroupTitle.x;
				NewGroupContent.y = NewGroupTitle.y + NewGroupTitle.height;
				this.addChild(NewGroupContent);
				contentDic[GroupId] = NewGroupContent;
				//num = _GroupFriendContentArray.push( NewGroupContent );
				NewGroupContent.itemid = GroupId;
			}

			//初始化名单内容
			_SetFriendGroupNum( GroupId );
		}
		
		public function DeleteGroup( GroupId:int ):void
		{
			initData();
			//初始化名单内容
			if(titleDic[GroupId])
			{
				titleDic[GroupId].onlineNum = 0;
				titleDic[GroupId].totalNum = 0;
				_SetFriendGroupNum( GroupId );
				
				var Title = titleDic[GroupId].titleMc;
				
				if ( Title != null && Title != undefined )
				{
					removeChild(Title);
				}
				titleDic[GroupId].titleMc = null;
				titleDic[GroupId] = null;
				
				var Content = contentDic[GroupId];
				
				if ( Content != null && Title != undefined )
				{
					removeChild(Content);
				}
				contentDic[GroupId] = null;
				UpdateFriendGroup();
				//UpdateFriendHeight();
			}
		}

		private function DClickFriendItem(e:MouseEvent):void
		{
			ExternalInterface.call( "ASFriendItemDClick", e.target as Button );
		}

		private function OverFriendItem(e:MouseEvent):void
		{
			var Item = e.target as _classItemRef;
			
			if ( PlayerTips && Item )
			{
				PlayerTips.visible = true;
				PlayerTips.y = Item.y + Item.parent.y + Item.parent.parent.y;

				ExternalInterface.call( "ASFriendOverItem" , Item.itemdataid , Item.itemid );

				PlayerTips.tF_playerName.text = Item.tF_playerName.text;
				PlayerTips.tF_playerCarrer.text = Item.tF_playerCarrer.text;
				PlayerTips.tF_playerLv.text = Item.tF_playerLocation.text;
				
				if(Item.ContactStatus.currentFrame == 4)
				{
					PlayerTips.tF_playerLv.textColor=0x9d9d9d;
				}
				else
				{
					PlayerTips.tF_playerLv.textColor=0xffffff;
				}
				
				
			}
			
		}

		private function OutFriendItem(e:MouseEvent):void
		{
			if (PlayerTips)
			{
				PlayerTips.visible = false;
			}
		}
		
		private function AddFriend( GroupId:int):int
		{
			if(listDic && contentDic)
			{
				var GroupFriendList:Array = listDic[GroupId];
				var GroupFriendContent:MovieClip = contentDic[GroupId];
				if ( GroupFriendContent && GroupFriendList )
				{
					var Item = new _classItemRef;
					var Lenth:int = GroupFriendList.length;
					GroupFriendContent.addChild( Item);
					Item.x = 0;
					Item.y = Lenth * Item.height;
					Item.focusable = false;
					Item.groupName = "FriendItemGroup";
					Item.name = "ContactListRender" + Lenth;
					Item.itemid = Lenth;
					Item.itemdataid = GroupId;
					Item.addEventListener( MouseEvent.DOUBLE_CLICK , DClickFriendItem );
					Item.addEventListener( MouseEvent.MOUSE_OVER , OverFriendItem );
					Item.addEventListener( MouseEvent.MOUSE_OUT , OutFriendItem );
					Item.addEventListener( MouseEvent.CLICK , ClickFriendItem );
					Item.doubleClickEnabled = true;
					GroupFriendContent.width = Item.width;
					
				    GroupFriendContent.height = Item.y + Item.height;
					return GroupFriendList.push( Item);
				}
			}
            return 0;
		}

	}
}