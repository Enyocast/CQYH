package ActionScript3.Friend
{
	public class NearContactListContent extends ContactListBase
	{
		protected const NearGroupConst:int = 1000;
		override protected function configUI():void
		{
			super.configUI();
			//test
			//var data:Object = { name:"最近联系人",lv:20,classTxt:"ass",location:"?",sign:"hehe",roleId:11,stats:1,iconPath:""};
			//SetNearListData( [data,data,data,data,data,data] );
			//addEventListener( SliderEvent.VALUE_CHANGE , ScrollChangeHandler );
		}
		
		public function SetNearListData( dat:Array ):void
		{
/*			var size:int = dat.length;
			_SetNearListNum(size);*/
            SetListData(dat,"nearContactListGroup","nearContactListRender",true,NearGroupConst);
		}

/*		private function DClickNearContactItem(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNearContactDClick", e.target as Button );
		}
*/

/*		private function _SetNearListNum( num:int ):void
		{
			var Lenth:int=0;
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
				var dec:int = num - _ListArray.length;
				var i:int = 0;
				for (i = 0; i < dec; i++)
				{
					var Item = new _classItemRef  ;
					Lenth= _ListArray.length;
					addChild( Item );
					Item.x = 0;
					Item.y = Lenth * Item.height;
					Item.focusable = false;
					Item.groupName = "nearContactListGroup";
					Item.name = "nearContactListRender" + Lenth;
					Item.itemid = Lenth;

					Item.itemdataid = NearGroupConst;//这个值右键菜单要用，区别好友groupid
					Item.addEventListener( MouseEvent.CLICK , ClickFriendItem ); //ClickNearContactItem
					Item.addEventListener( MouseEvent.DOUBLE_CLICK , DClickNearContactItem );
					Item.doubleClickEnabled = true;
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

	}
}