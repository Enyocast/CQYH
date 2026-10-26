package ActionScript3.Mail
{

	import ActionScript3.MyPanel;

	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import ActionScript3.MyTipButton;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import flash.text.TextField;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.controls.RadioButton;
	import ActionScript3.Common.CustomPage;
	import ActionScript3.Common.Utils.Page;
	import ActionScript3.Common.Events.ParamEvent;

	public class MailListPage extends UIComponent
	{
		public var mail_list_control_mc:ScrollingList;

		public var mail_sender_txt:TextField;
		public var mail_cost_txt:TextField;
		public var mail_title_txt:TextField;
		public var mail_content_txt:TextField;

		public var btn_read_all:Button;
		public var btn_select_all:Button;
		public var btn_delete:Button;
		public var nomail:MovieClip;
		
		public var all_mail_radio:RadioButton;
		public var player_mail_radio:RadioButton;
		public var system_mail_radio:RadioButton;
		
		public var _customPage:CustomPage;
		public var _page:Page;
		public var currentPage = 1;
		public var tf_dec:TextField;
		
		override protected function configUI():void
		{
			super.configUI();

			btn_read_all.addEventListener(MouseEvent.CLICK, onReadAll);
			btn_select_all.addEventListener(MouseEvent.CLICK, onSelectAll);
			btn_delete.addEventListener(MouseEvent.CLICK, onDeleteSelected);
			mail_list_control_mc.addEventListener(ListEvent.INDEX_CHANGE,indexChange);

			all_mail_radio.addEventListener(MouseEvent.CLICK, OnAllMail);
			player_mail_radio.addEventListener(MouseEvent.CLICK, OnPlayerMail);
			system_mail_radio.addEventListener(MouseEvent.CLICK, OnSystemMail);
			
			all_mail_radio.selected = true;
			_page=new Page(5);
			_customPage.addEventListener(ParamEvent.PAGE_CHANGE,pageHandler);
			ExternalInterface.call("ASSelectMailType", -1);
			//mail_list_control_mc.addEventListener(ListEvent.ITEM_DOUBLE_CLICK, onClickItem);
            updateMailData(null);
			//testData();
		}
		
		public function pageHandler(e:ParamEvent):void
		{
			var p:int=e.param as int;
			currentPage = p;
			//update(p);
			btn_select_all.selected = false;
			ExternalInterface.call("ASMailPageChange",currentPage);
		}

		public function updateMailData( dat:Array ):void
		{
			if((dat==null) || (dat.length==0))
			{
				nomail.visible=true;
				mail_list_control_mc.visible=false;
				tf_dec.visible=false
			}
			else
			{
				if(dat.length>=50)
				{
					tf_dec.visible=true;
				}
				else
				{
					tf_dec.visible=false;
				}
				nomail.visible=false;
				_page.datas=dat;
				_customPage.maximum=this._page.getTotalPages();
				if(currentPage > this._page.getTotalPages())
				{
					currentPage = this._page.getTotalPages();
					_customPage.value = currentPage;
				}
				update(currentPage);
			}
		}
		
		private function update(p:int):void
		{
			currentPage = p;
			var arr:Array=this._page.getPageData(p);
			mail_list_control_mc.visible=true;
			mail_list_control_mc.dataProvider = new DataProvider(arr);
			mail_list_control_mc.validateNow();
			mail_list_control_mc.invalidateData();
			ExternalInterface.call("ASSetCurrentPageNum",currentPage, arr.length);
		}
		
		public function OnAllMail()
		{
			_customPage.value = currentPage = 1;
			btn_select_all.selected = false;
			ExternalInterface.call("ASSelectMailType", -1,_customPage.value);
		}
		public function OnPlayerMail()
		{
			_customPage.value  = currentPage = 1;
			btn_select_all.selected = false;
			ExternalInterface.call("ASSelectMailType", 0 , _customPage.value);
		}
		public function OnSystemMail()
		{
			_customPage.value  = currentPage = 1;
			btn_select_all.selected = false;
			ExternalInterface.call("ASSelectMailType", 1, _customPage.value);
		}
		private function indexChange(evt:ListEvent):void
		{
		    var targetList:ScrollingList = evt.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
		
/*		private function testData():void
		{
			if(1){
				var itemsData:Array = [];
				for (var i:int = 1; i < 100; i++)
				{
					var mailData:MailData = new MailData  ;
					mailData.mail_id = 1;
					mailData.mail_from_txt = "God" + i;
					mailData.mail_icon = i % 4;
					mailData.mail_title_txt = "Hello Paladin!" + i;
					mailData.mail_has_items_mc = Boolean(i % 2);
					mailData.mail_valid_days_txt = String(i + 1);
					itemsData.push(mailData);
				}
				updateMailData(itemsData);
			}
		}*/

		public function onReadAll()
		{
			ExternalInterface.call("ASReadAll");
		}

		public function onSelectAll()
		{
			//ExternalInterface.call("ASSelectAll");
			ExternalInterface.call("ASSelectCurrentPageMail",!btn_select_all.selected,currentPage);
			
		}

		public function onDeleteSelected()
		{
			ExternalInterface.call("ASDeleteSelected");
		}

		public function  UpdateSelectAllState(v:Boolean):void
		{
			btn_select_all.selected = v;
		}
		
/*		public function onClickItem(e:ListEvent):void
		{
			var item:MailListItem = e.itemRenderer as MailListItem;
			//item.mouseChildren = true;
			//item.mouseEnabled = true;
			//item.mail_select_checkbox.selected = !item.mail_select_checkbox.selected;
			ExternalInterface.call("ASReadMail", item.mail_data.mail_id);
		}*/

	}

}