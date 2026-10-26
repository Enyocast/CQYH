package ActionScript3.Friend
{
	//
	public class EnemyListContent extends ContactListBase
	{
		//仇人
		protected const EnemyGroupConst:int = 3000;
		override protected function configUI():void
		{
			super.configUI();
			//test
			//var data:Object = { name:"仇人",lv:20,classTxt:"ass",location:"?",sign:"hehe",roleId:11,stats:1,iconPath:""};
			//SetEnemyListData( [data,data,data,data,data,data,data,data,data,data,data,data] );
		}
		
		public function SetEnemyListData( dat:Array ):void
		{
/*			var size:int = dat.length;
			_SetEnemyListNum(size);*/
			SetListData(dat,"EnemyListGroup","EnemyListRender",false,EnemyGroupConst);
		}
		

/*		private function _SetEnemyListNum( num:int ):void
		{
			if (_ListArray && _ListArray.length > num)
			{
				for (var j:int = num; j < _ListArray.length; j++)
				{
					removeChild( _ListArray[j] );
				}
				_ListArray.splice( num );
			}
			else if (_ListArray &&  _ListArray.length < num )
			{
				var dec = num - _ListArray.length;
				var i:int = 0;
				trace("_ListArray",dec);
				for (i = 0; i < dec; i++)
				{
					var Item = new _classItemRef  ;
					var Lenth = _ListArray.length;
					addChild( Item);
					Item.x = 0;
					Item.y = Lenth * Item.height;
					trace("EnemyListGroup",Lenth,Item.height);
					Item.focusable = false;
					Item.groupName = "EnemyListGroup";
					Item.addEventListener( MouseEvent.CLICK , ClickFriendItem );
					Item.name = "EnemyListRender" + Lenth;
					Item.itemid = Lenth;
					Item.itemdataid = EnemyGroupConst;
					_ListArray.push(Item);
				}
			}

			if (_ListArray && _ListArray.length == 0)
			{
				_ListContentHeight = 0;
			}
			else
			{
				if(_ListArray)
				{
					var lenth:int = _ListArray.length;
				    _ListContentHeight = _ListArray[lenth - 1].y + _ListArray[lenth - 1].height;
				}
			}
		}*/

	}
}