
package ActionScript3.Mall
{
	import ActionScript3.MyPanel;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	
	public class MallFriendPanel extends MyPanel
	{
		public var friendList_mc:ScrollingList;
		public var btnConfirmGive_mc:Button;
		public var btnHead0_mc:Button;
		public var btnHead1_mc:Button;
		public var btnHead2_mc:Button;
		
		public var ItemID:int = 0;
		public var ItemNum:int = 0;
		
		public var selData:MallFriendListItemData = null;
		
		override protected  function configUI():void 
		{		
			trace("------MallFriendPanel  super.configUI:");
			super.configUI();			
			
			btnConfirmGive_mc.addEventListener(MouseEvent.CLICK, 	OnClickGive);
			friendList_mc.addEventListener(ListEvent.ITEM_CLICK,    onClickItem);
			
			ExternalInterface.call("RegisterFriendPanel", this);
			
			ExternalInterface.call( "ASTrace", "MallFriendPanel");
			testFriend();
			SetWindowTitle("");
		}

		public function UCSetGoodsInfo(nID:int,nNum:int)
		{
			ItemID = nID;
			ItemNum = nNum;
			selData = null;
		}
		public function UCUpdateFriendList( data:Array ):void
		{
			trace("------UCUpdateFriendList",friendList_mc);
			friendList_mc.dataProvider = new DataProvider(data);
			friendList_mc.validateNow();
			friendList_mc.invalidateData();
		}		
		
		public function onClickItem(e:ListEvent)
		{
			var itemData:MallFriendListItem = e.itemRenderer as MallFriendListItem;
			trace("------onClickItem 1",itemData);
			
			if(itemData && itemData.friendData)
				selData = itemData.friendData as MallFriendListItemData;
				
			trace("------onClickItem 2",selData);
		}
		
		public function OnClickGive()
		{
			trace("------OnClickGive",selData);
			if(selData)
				ExternalInterface.call("ASClickGiveFriendGoods",selData.RoleName, ItemID,ItemNum);
		}
		
		function testFriend()
		{
			var tArrData = new Array;
			for(var n:int = 0; n < 36; ++n)
			{
				var data:MallFriendListItemData = new MallFriendListItemData;
				data.RoleID = n +1;
				data.RoleName = "firend name" + n;
				data.RoleJob = "killer";
				data.RoleLevel = "10";
				tArrData.push(data);
			}
			UCUpdateFriendList(tArrData);
		}
	}
}