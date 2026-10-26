//
// 家族查看
//
package ActionScript3.Guild
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.MyCloseButton;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.Utils.Page;
	import ActionScript3.Common.Events.ParamEvent;
	import scaleform.clik.events.ComponentEvent;

	public class GuildViewPanel extends MyPanel
	{
		public var guild_view_list_mc : ScrollingList;
		public var tabTitle:MovieClip;
		public var guild_create_name_mc : MovieClip;
		//public var guild_view_page_up_mc : MovieClip;
		//public var guild_view_page_down_mc : MovieClip;
		//public var guild_view_page_num_tf : TextField;
		
		public var guild_view_find_mc:Button;
		public var guild_view_apply_mc : Button;
		public var guild_view_war_mc : Button;
		
		public var war:GuildOpenWar;//宣战请求
		
		public var guild_view_name_tf : TextField;
		public var guild_view_leader_tf : TextField;
		public var guild_view_creator_tf : TextField;
		public var guild_view_create_time_tf : TextField;
		public var guild_view_enounce_tf : TextField;
		
		public var guild_info_panel_mc : MovieClip;
		public var guild_find_panel_mc : GuildFindPanel;
		
		public var guild_select_id:int;
		
		public var guild_view_page_mc:MovieClip;
		public var tf_dec:TextField;
		
		public var _pages:Page;
		public static const MAX_BUILDING_COUNT = 16;

		
		override protected function configUI():void
		{
			ShowMode="BC";

			super.configUI();
			_pages=new Page(MAX_BUILDING_COUNT);
			guild_view_list_mc.selectedIndex = 0;
			//guild_view_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onListItemChange, false, 0, true);
			guild_view_list_mc.addEventListener(ListEvent.ITEM_CLICK, onListItemClick ); //, false, 0 ,false);
			
			var page_up_mc:Button = guild_view_page_mc.getChildByName("btn_prev") as Button;
			var page_down_mc:Button = guild_view_page_mc.getChildByName("btn_next") as Button;
			var page_num_tf:TextField = guild_view_page_mc.getChildByName("tF_pageNum") as TextField;
			
			page_up_mc.addEventListener(MouseEvent.CLICK, onBtClickPageUp);
			page_down_mc.addEventListener(MouseEvent.CLICK, onBtClickPageDown);
			var page_index:int = 1;
			page_num_tf.text = String("1");
			var info_window_mc:UIComponent = guild_info_panel_mc.getChildByName("MyWindowsFrame_mc") as UIComponent;
			var info_close_mc:MyCloseButton = info_window_mc.getChildByName("btn_close") as MyCloseButton;
			info_close_mc.RemoveAddedEventListener();
			info_close_mc.addEventListener(MouseEvent.CLICK, onBtClickInfoClose);
			this.addEventListener(ComponentEvent.HIDE,hideHandler);
			
			guild_view_find_mc.addEventListener(MouseEvent.CLICK, onBtClickFind);
			guild_view_apply_mc.addEventListener(MouseEvent.CLICK, onBtClickApply);
			guild_view_war_mc.enabled=false;
			guild_view_war_mc.addEventListener(MouseEvent.CLICK, onBtClickChallenge);
			guild_info_panel_mc.visible = false;
			guild_find_panel_mc.visible = false;
			(guild_info_panel_mc.getChildByName("custompage") as CustomPage).addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			var i:int = 0;
			for (i = 1; i <= MAX_BUILDING_COUNT; i++)
			{
				var item_mc:GuildBuildingItem = guild_info_panel_mc.getChildByName("guild_building_" + i + "_mc") as GuildBuildingItem;
				
				item_mc.addEventListener(MouseEvent.ROLL_OVER, onItemRollOver);
				item_mc.addEventListener(MouseEvent.ROLL_OUT, onItemRollOut);
				//item_mc.select = false;
				/*
				// test
				var object_data:GuildBuildingData = new GuildBuildingData;
				object_data.guild_building_icon = "icon.TGA";
				object_data.guild_building_level = 1;
				object_data.guild_building_top_level = 5;
				item_mc.updateItemData(object_data);
				*/
			}
			UCUpdateGuildViewList([],1);
		}
		
		private function pageHandler(e:ParamEvent):void
		{
			var p:int=e.param as int;
			update(p);
		}
		
		private function onItemRollOver(e:MouseEvent):void
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			if (item_mc)
			{
				item_mc.showTips();
				ExternalInterface.call("ASShowTips_Building", item_mc, item_mc.guild_building_type);
			}
		}
		
		private function onItemRollOut(e:MouseEvent):void
		{
			var item_mc:GuildBuildingItem = e.currentTarget as GuildBuildingItem;
			if (item_mc)
			{
				item_mc.hideTips();
				ExternalInterface.call("ASHideTips_Building", item_mc);
			}
		}
		
		private function onBtClickPageUp(e:MouseEvent):void
		{
			ExternalInterface.call("ASPageUp");
		}
		
		private function onBtClickPageDown(e:MouseEvent):void
		{
			ExternalInterface.call("ASPageDown");
		}
		
		private function onBtClickChallenge(e:MouseEvent):void
		{
			ExternalInterface.call("ASChallengeConfirm", guild_select_id);
		}
		
		private function hideHandler(evt:Event):void
		{
			guild_info_panel_mc.visible = false;
			guild_find_panel_mc.visible = false;
		}
		
		private function onBtClickInfoClose(e:MouseEvent):void
		{
			guild_info_panel_mc.visible = false;
		}
		
		public function onBtClickFind(evt:MouseEvent):void
		{
			guild_find_panel_mc.visible = true;
			guild_find_panel_mc.onBtClickName(null);
		}
		
		public function onBtClickApply(evt:MouseEvent):void
		{
			var item:GuildViewListItem=guild_view_list_mc.getRendererAt(guild_view_list_mc.selectedIndex) as GuildViewListItem;
			if(item)
			{
				ExternalInterface.call("ASApplyForJoint", item.data.guild_id);
			}
		}
		
/*		public function onListItemChange( event:ListEvent ):void
		{
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				list.invalidateData();
			}
		}*/
		
		private function onListItemClick(event:ListEvent):void
		{
			//ExternalInterface.call("ASTrace", "rand_test="+rand_test);
			
			var list:ScrollingList = event.target as ScrollingList;
			if (list != null)
			{
				var provider:TreeDataProvider = list.dataProvider as TreeDataProvider;
				if (provider!=null)
				{
					provider.handleListItemClick( event );
					provider.requestItemAt(event.index,updateClick);
				}
				list.invalidateData();
			}
		}
		
		
		public function updateClick(data:Object):void
		{
			if (data)
			{
				ExternalInterface.call("ASUpdateGuildViewInfo", data.guild_id);
			}
		}
		
		public function UCUpdateGuildViewInfo(data:Object):void
		{
			guild_select_id = data.guild_id;
			guild_info_panel_mc.visible = true;
			guild_info_panel_mc.guild_view_name_tf.text = data.guild_name;
			guild_info_panel_mc.guild_view_leader_tf.text = data.guild_leader_name;
			guild_info_panel_mc.guild_view_creator_tf.text = data.guild_creator_name;
			guild_info_panel_mc.guild_view_id_tf.text = String(data.guild_id);
			guild_info_panel_mc.guild_view_enounce_tf.text = data.guild_announce;
		}
		
		public function UCUpdateGuildBuildingList(dat:Array):void
		{
			var list:Array=[];
			if(dat!=null){
					var i:int=0;
					for(i=0;i<dat.length;i++)
					{
					    var obj:Object=dat[i];
						var type:int=int(obj.guild_building_type)
						if (type > 7 && type < 12)
				        {
						   continue;
				        }
				        if(type!=16 && type!=17){
					   list.push(obj);
				    }
				}
			}
			this._pages.datas=list;
			(guild_info_panel_mc.getChildByName("custompage") as CustomPage).maximum=this._pages.getTotalPages();
			update(1);
		}
		
		public function update(p:int):void
		{
		    var arr:Array=this._pages.getPageData(p);
			var i:int = 0;
			for (i = 0; i < MAX_BUILDING_COUNT; i++)
			{
				var item_mc:GuildBuildingItem = guild_info_panel_mc.getChildByName("guild_building_" + (i+1) + "_mc") as GuildBuildingItem;
				if (item_mc && arr[i])
				{
					item_mc.updateItemData(arr[i]);
					item_mc.visible=true;
				}else{
					item_mc.visible=false;
				}
			}
			//guild_info_panel_mc.getChildByName("guild_building_title_tf").visible = false;
			//guild_info_panel_mc.getChildByName("custompage").visible = false;
			//guild_info_panel_mc.getChildByName("guild_info_line_mc").visible = false;
		}
		
		public function UCUpdateGuildViewList(data:Array, page_index:int):void
		{
			guild_view_list_mc.dataProvider = new TreeDataProvider(data);
			guild_view_list_mc.validateNow();
			guild_view_list_mc.invalidateData();
			
			if (data.length > 0)
			{
				guild_view_list_mc.selectedIndex = 0;
				ExternalInterface.call("ASUpdateGuildViewInfo", data[0].guild_id);
			}
			
			var page_num_tf:TextField = guild_view_page_mc.getChildByName("tF_pageNum") as TextField;
			page_num_tf.text = String(page_index);
		}
		
		public function UCSetWindowTitle(title:String):void
		{
			SetWindowTitle(title);
		}
		
		public function UCUpdateGuildLeaveCD(dat:String):void
		{
			tf_dec.htmlText=dat;
		}
		
		public function UCShowChallengeConfirm(dat:Object):void
		{
			war.visible=true;
			war.updateData(dat);
		}
	}
}


























