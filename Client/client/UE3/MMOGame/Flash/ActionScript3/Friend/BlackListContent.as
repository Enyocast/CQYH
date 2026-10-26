package ActionScript3.Friend
{
	import flash.events.MouseEvent;
	import scaleform.gfx.MouseEventEx;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.external.ExternalInterface;

	public class BlackListContent extends ContactListBase
	{
		protected const BlackGroupConst:int = 2000;
		override protected function configUI():void
		{
			super.configUI();
			//var data:Object = { name:"黑单",lv:20,classTxt:"ass",location:"?",sign:"hehe",roleId:11,stats:1,iconPath:""};
			//SetBlackListData( [data,data,data,data,data,data] );
		}
		
		public function SetBlackListData( dat:Array ):void
		{
			SetListData(dat,"BlackListGroup","BlackListRender",false,BlackGroupConst);
		}

/*		private function _SetBlackListNum( num:int ):void
		{
			if (_ListArray.length > num)
			{
				for (var j:int = num; j < _ListArray.length; j++)
				{
					removeChild( _ListArray[j] );
				}
				_ListArray.splice( num );
			}
			else if ( _ListArray.length < num )
			{
				var dec = num - _ListArray.length;
				var i:int = 0;
				for (i = 0; i < dec; i++)
				{
					var Item = new _classItemRef  ;
					var Lenth:int = _ListArray.length;
					addChild( Item);
					Item.x = 0;
					Item.y = Lenth * Item.height;
					Item.focusable = false;
					Item.groupName = "BlackListGroup";
					Item.name = "BlackListRender" + Lenth;
					Item.itemid = Lenth;
					Item.itemdataid = BlackGroupConst;//这个值右键菜单要用，区别好友groupid
					var LvText:TextField = Item.getChildByName("tF_playerLv") as TextField;
					if (LvText)
					{
						LvText.visible = false;
					}
					Item.addEventListener( MouseEvent.CLICK , ClickBlackItem );
					_ListArray.push(Item);
				}
			}
			if (_ListArray.length == 0)
			{
				_ListContentHeight = 0;
			}
			else
			{
				var lenth:int = _ListArray.length;
				_ListContentHeight = _ListArray[lenth - 1].y + _ListArray[lenth - 1].height;
			}
		}*/
		
		override protected function ClickFriendItem(e:MouseEvent):void
		{
			if ((e as MouseEventEx).buttonIdx == 1)
			{
				var Item = e.target as _classItemRef;
				if (Item)
				{
					var pos:Point = new Point  ;

					pos.x = Item.x + Item.width;

					pos.y = Item.y;
					pos = Item.parent.localToGlobal(pos);
					var NameText:TextField = Item.getChildByName("tF_playerName") as TextField;
					ExternalInterface.call( "ASFriendItemRightClick",pos.x, pos.y,Item , Item.itemid,NameText.text);
				}

			}
		}

	}
}