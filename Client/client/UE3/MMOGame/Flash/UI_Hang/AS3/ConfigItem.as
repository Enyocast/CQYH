package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.DropdownMenu;
	import UI_ChatWidget.AS3.ChatTextField;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import flash.events.Event;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import flash.utils.Dictionary;
	
	
	public class ConfigItem extends UIComponent {
		
		public var list:ScrollingList;
		public var dropMenu:DropdownMenu;
		public var input_item:ChatTextField;
		public var all_pick:CheckBox;
		public var all_show:CheckBox;
		public var btn_apply:Button;
		public var btn_confirm:Button;
		public var btn_cancel:Button;
		public var btn_default:Button;
		public var itemConfigArr:Array;//正常显示的列表项
		public var dic:Dictionary;//存放不需要显示的列表数组
		override protected function configUI():void
		{
			super.configUI();
			itemConfigArr=[];
			dic=new Dictionary();
			btn_apply.addEventListener(MouseEvent.CLICK,OnApply);
			btn_confirm.addEventListener(MouseEvent.CLICK,OnOK);
			btn_cancel.addEventListener(MouseEvent.CLICK,OnCancel);
			btn_default.addEventListener(MouseEvent.CLICK,OnDefault);
			list.addEventListener(ListEvent.ITEM_CLICK,itemclickHandler);
			all_pick.addEventListener(ButtonEvent.CLICK,pickHandler);
			all_show.addEventListener(ButtonEvent.CLICK,showHandler);
			dropMenu.addEventListener(ListEvent.INDEX_CHANGE, onClickItemType);
			input_item.addEventListener(Event.CHANGE,textChange);
			input_item.maxChars=10;
			input_item.addEventListener( "inputcopy",inputcopy);
			if(1)
			{
				testMenuData()
			}
            //this.testData();
		}
		
		private function updateData(arr:Array):void
		{
			list.dataProvider = new  DataProvider(arr);
			list.validateNow();
			list.invalidateData();
		}
		
		public function setItemData(dat:Array):void
		{
			updateArr(dat);
			//itemConfigArr=dat;
			if(dropMenu && dropMenu.selectedIndex>0)
			{
				var type:int=0;
				var index:int=dropMenu.selectedIndex;
				var dropMenuArr:Array=dropMenu.dataProvider as Array;
				if(dropMenuArr && dropMenuArr[index])
				{
					type=dropMenuArr[index].index;
				}
				filterItemType(type);
			}
			else
			{
				updateData(itemConfigArr);
			}
		}
		
		public function setMenuData(menuArr:Array):void
		{
			var dp:DataProvider = new DataProvider(menuArr);
            dropMenu.dataProvider = dp;
            dropMenu.invalidateData();
            dropMenu.selectedIndex = 0;
            dropMenu.validateNow();
		}
		
		//模糊匹配文本
		private function textChange(evt:Event):void
		{
			var searchStr:String = evt.target.text;
			filterData(searchStr);
		}
		
		private function inputcopy(evt:Event):void
		{
			var searchStr:String=input_item.textField.text;
			filterData(searchStr);
		}

		private function filterData(dat:String):void
		{
			if(dat=="")
			{
				updateData(itemConfigArr);
				return;
			}
			var arr:Array=[];
			var dl:uint = itemConfigArr.length;
			var info:HangItemData;
            for (var i:uint = 0; i < dl; i++) {
				info = itemConfigArr[i] as HangItemData;
				if(info.itemName.indexOf( dat ) >= 0 )
				{
					arr.push(info);
				}
            }
			updateData(arr);
		}
		
		private function onClickItemType(evt:ListEvent):void
		{
			var item:Object=evt.itemData;
			var type:int=item.index;
			if(itemConfigArr)
			{
				filterItemType(type);
			}
		}
		//根据道具类型查找数据
		private function filterItemType(type:int):void
		{
			if(type==0)
			{
				updateData(itemConfigArr);
				return;
			}
			var l:int=itemConfigArr.length;
			var i:int=0;
			var arr:Array=[];
			for(i=0;i<l;i++)
			{
				var dat:HangItemData=itemConfigArr[i];
				if(dat.itemType==type)
				{
					arr.push(dat);
				}
			}
			updateData(arr);
		}
		
		public function updateArr(dat:Array):void
		{//找出相同的名称的元素放在
			if(dat)
			{
				var vList:Array=dat.filter(noVisible);//过滤不需要显示的元素
				function noVisible(item:Object,index:int,arr:Array):Boolean
				{
					if(item.visible==true)
					{
						return true;
					}
					return false;
				}
				itemConfigArr=vList;
				var ls:Array=[];
				var nt:String="";
				var id:int=0;
				for each(var obj:HangItemData in vList)
				{
					nt=obj.itemName;
					id=obj.itemID;
					if(dic[nt]==null || dic[nt]==undefined)
					{
						ls=dat.filter(noName);
						dic[nt]=ls;
					}
				}
				function noName(item:Object,index:int,arr:Array):Boolean
				{
					if(item.itemName==nt && item.itemID !=id)
					{
						return true;
					}
					return false;
				}
			}

		}
		
		private function pickHandler(evt:ButtonEvent):void
		{
			updateCheckSelect(0);
		}
		
		private function showHandler(evt:ButtonEvent):void
		{
			updateCheckSelect(1);
		}
		
		private function updateCheckSelect(type:int):void
		{
			var dp_List1:Array = list.dataProvider as Array;
			var i:int=0;
			var l:int=dp_List1.length;
			for(i=0;i<l;i++)
			{
				var dat:HangItemData=dp_List1[i];
				if(type==0)
				{
					dat.isAuto=all_pick.selected;
				}
				else
				{
					dat.isShowName=all_show.selected;
				}
				if(dic && dic[dat.itemName])
				{
					var arr:Array=dic[dat.itemName] as Array;
					for each(var j:HangItemData in arr)
					{
						j.isAuto=dat.isAuto;
						j.isShowName=dat.isShowName;
					}
				}
				
			}
			updateData(dp_List1);
		}
		
		private function itemclickHandler(evt:ListEvent):void
		{
			var item:ListItem_HangItem = evt.itemRenderer as ListItem_HangItem;
			if(item.showName==true)
			{
				all_show.selected=false;
			}
			if(item.auto==true)
			{
				all_pick.selected=false;
			}
			
			var list:ScrollingList = evt.target as ScrollingList;
			if (list != null){
				list.invalidateData();
			}
		}
		
		//请求读取 道具默认配置
		private function OnDefault(evt:MouseEvent):void
		{
			clear();
			var dp_List1:Array = getList(1);
			ExternalInterface.call("ASHangConfigItemData", dp_List1);
		}
		private function OnOK(evt:MouseEvent):void
		{
			OnApply(null);
			OnCancel(null);	
		}
		private function OnCancel(evt:MouseEvent):void
		{ 
		    hide();
			ExternalInterface.call( "ASOnPanelClose" , "Assist");
		}
		private function OnApply(evt:MouseEvent):void
		{
			var dp_List1:Array = getList(0);
			ExternalInterface.call("ASApplyHangItemConfig",dp_List1);//请求外挂道具配置
		}
		//获取列表数组
		private function getList(_type:int):Array
		{
			var dp_List1:Array = list.dataProvider as Array;
			var arr:Array=[];
			var arr1:Array=[];
			if(dp_List1)
			{
				var i:int=0;
				var l:int=dp_List1.length;
				for(i=0;i<l;i++)
				{
					var obj:HangItemData=dp_List1[i];
					if(obj)
					{
						if(_type==1)
						{
							arr.push(obj.itemID);
						    if(dic && dic[obj.itemName])
						    {
							    arr1=dic[obj.itemName] as Array;
								for each(var j:HangItemData in arr1)
								{
									arr.push(j.itemID);
								}
						    }
						}
						else
						{
							arr.push(obj);
						    if(dic && dic[obj.itemName])
						    {
							    arr1=dic[obj.itemName] as Array;
							    arr=arr.concat(arr1);
						    }
						}
					}
				}
			}
			return arr;
		}
		public function hide():void
		{
		    clear();
			input_item.text="";
			dropMenu.selectedIndex=0;
			dropMenu.close();
		}
		
		private function clear():void
		{
		    all_pick.selected=false;
			all_show.selected=false;
		}
		
		private function testMenuData():void
		{
			var itemsData:Array = new Array();
            for (var i:int = 0; i < 4; i++) {
                itemsData.push({label:"全部分类 " + i, index:i});
            }
			setMenuData(itemsData);
		}

/*		private function testData():void
		{
			var arr:Array=[];
			for(var i:int=0;i<20;i++){
			   var item:HangItemData=new HangItemData();
			   item.isAuto=true;
			   item.isBest=false;
			   item.itemID=i;
			   
			   item.isShowName=true;
			   item.itemType=i;
			   if(i%2==0)
			   {
				   item.itemName="道具0";
				   if(i==0)
				   {
					  item.visible=true; 
				   }
				   else
				   {
					   item.visible=false;
				   }
				    
			   }
			   else
			   {
				   item.itemName="道具1";
				   	if(i==1)
				   {
					  item.visible=true; 
				   }
				   else
				   {
					   item.visible=false;
				   }
			   }
			   arr.push(item);
			}
			setItemData(arr);
		}*/
	}
	
}
