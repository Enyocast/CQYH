package ActionScript3.Friend
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyScrollPanel;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.SliderEvent;
	import scaleform.gfx.Extensions;
	import scaleform.gfx.MouseEventEx;

	//
	public class ContactListBase extends MyScrollPanel
	{
		protected var _classItemRef:Class;
		protected var frameBg:Object;
		
	    protected var _ListArray:Array;		
		protected var _ListContentHeight:int;
		
		public function get scrollEnable():Boolean
		{
			if(frameBg && (_ListContentHeight > frameBg.height))
			{
				return true;
			}
			return false;
		}

		override protected function configUI():void
		{
			Extensions.enabled = true;
			initListArray();
			this.addEventListener( SliderEvent.VALUE_CHANGE , ScrollChangeHandler );
			
		}
		
		private function initListArray():void
		{
			if(_ListArray==null)
			{
			   _ListArray =[];
			   frameBg = ContactListStatic.frameBg;
			}
			if(_classItemRef==null)
			{
				_classItemRef = getDefinitionByName("ContactListRender") as Class;
			}
		}
		
		protected function ScrollChangeHandler(evt:SliderEvent):void
		{
			var percent:int = evt.value;
			if ( _ListContentHeight - frameBg.height > 0 )
			{
				y = frameBg.y - percent * (_ListContentHeight - frameBg.height) / 100;
			}
			else
			{
				y = frameBg.y;
			}
		}
		
		protected function SetListData( dat:Array,_groupName:String ,render:String,doubleClick:Boolean,GroupConst:int):void
		{//设置数据
			initListArray();
			var size:int = dat.length;
			setListNum(size,_groupName,render,doubleClick,GroupConst);
            var i:int=0;
			if(_ListArray)
			{
				for (i=0; i < size; i++)
			    {
				    var item:RadioButton = _ListArray[i] as RadioButton;

				    var itemData:Object= dat[i];
				    ContactListStatic.SetItemValue( item,itemData.name,itemData.lv,itemData.classTxt,itemData.location,itemData.sign,itemData.roleId,itemData.stats,itemData.iconPath );
			     }
			}
		}
		
		protected  function setListNum(num:int,_groupName:String ,render:String,doubleClick:Boolean,GroupConst:int):void
		{//设置列表数量
		    if(_ListArray)
			{
				var l:int=_ListArray.length;
				var dec:int=0;
				var j:int=0;
				var i:int=0;
				if (l > num)
				{
					for (j = num; j < l; j++)
					{
						removeChild( _ListArray[j] );
					}
					_ListArray.splice( num );
				}
				else if ( _ListArray.length < num )
				{
					dec= num - l;
					for (i = 0; i < dec; i++)
					{
						var Item = new _classItemRef  ;
					    addChild( Item );
						l=_ListArray.length;
					    Item.x = 0;
					    Item.y = l * Item.height;
					    Item.focusable = false;
					    Item.groupName = _groupName;
					    Item.name = render + l;
					    Item.itemid = l;
					    Item.itemdataid = GroupConst;//这个值右键菜单要用，区别好友groupid
					    Item.addEventListener( MouseEvent.CLICK , ClickFriendItem ); //ClickNearContactItem
					    Item.doubleClickEnabled = doubleClick;
						if(doubleClick)
						{
						   Item.addEventListener( MouseEvent.DOUBLE_CLICK , DClickNearContactItem );
						}
					    _ListArray.push(Item);
					}
				}
				if (_ListArray.length == 0)
				{
					_ListContentHeight = 0;
				}
				else
				{
					l = _ListArray.length;
				    _ListContentHeight = _ListArray[l - 1].y + _ListArray[l - 1].height;
				}
			}
		}
		
		protected function DClickNearContactItem(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNearContactDClick", evt.target as Button );
		}
		
		protected function ClickFriendItem(e:MouseEvent):void
		{
			if ((e as MouseEventEx).buttonIdx == 1)
			{
				var Item = e.target as _classItemRef;
				if (Item)
				{
					var pos:Point = new Point();
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