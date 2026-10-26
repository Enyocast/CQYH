package ActionScript3.RankList {
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.Button;
	import ActionScript3.TreeListData;
	import scaleform.clik.data.DataProvider;
	import flash.external.ExternalInterface;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.data.TreeDataProvider;
	
	public class ActiveContent extends UIComponent  {

		public var menu_list_mc:ScrollingList;
		public var ItemData:TreeListData;
		
		public var updateRank_txt_mc:TextField;
		public var myrank_mc:MyRankTxt;
		public var pagectrl_mc:MovieClip;

		public var active_cqbs:ActivePageBZ;
		public var active_tgbd:ActivePageTG;
		//树节点类型
		public const SUBNODE:int = 0;                                   	//子节点
		public const PARENTNODE_EX:int = 1;							//可展开的父节点
		public const PARENTNODE:int = 2;						//不可展开的父节点
		public var IsShowRank:Boolean=false;//是否显示排名
		override protected function configUI():void
		{
			super.configUI();
			active_tgbd.visible=false;
			active_cqbs.visible=false;

			/*this.Test();
			this.TestData(0);*/
			
			var prevPage:Button = pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != prevPage)
				prevPage.addEventListener(MouseEvent.CLICK, OnPrevPageClick);
			var nextPage:Button = pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != nextPage)
				nextPage.addEventListener(MouseEvent.CLICK, OnNextPageClick);
				
			menu_list_mc.addEventListener(ListEvent.ITEM_CLICK, OnTreeItemClick);
			menu_list_mc.addEventListener(ListEvent.INDEX_CHANGE, onCategoryListChange);
		}
		
		 protected function onCategoryListChange( event:ListEvent ):void
		{
			var targetList:ScrollingList = event.target as ScrollingList;
			if (targetList != null)
			{
				targetList.invalidateData();
			}
		}
		
		private function OnTreeItemClick(e:ListEvent):void
		{
			
			if(IsShowRank==true)
			{
				var targetList:ScrollingList = e.target as ScrollingList;
			    if (targetList != null)
			    {
				    var Provider:TreeDataProvider= targetList.dataProvider as TreeDataProvider;
				    if( Provider != null )
				    {
					    Provider.handleListItemClick( e );
					    ItemData = Provider.requestItemAt(e.index) as TreeListData;
					
					    if( ItemData.type == SUBNODE )
					    {
						    ExternalInterface.call( "ASActiveTreeItemClick", ItemData.index );
					     }
					     else
					     {
						     targetList.invalidateData();
					     }
				    }
			     }
			}
		}
		
		public function hide(bl:Boolean):void
		{
			IsShowRank=bl;
			active_tgbd.IsShowRank=bl;
			updateRank_txt_mc.visible=bl;
			myrank_mc.visible=bl;
			pagectrl_mc.visible=bl;
		}

		public function UpdateActiveListData( dat:Array ):void
		{
			if(dat){
				var type:int = dat[0] as int;
				dat.shift();
			}
			if(visible && null != dat)
			{
				if(type==17)
			    {
				   active_cqbs.visible=true;
				   active_cqbs.UpdateData(dat);
				   active_tgbd.visible=false;
			
			    }
			    else
			    {
				   active_tgbd.visible=true;
				   active_cqbs.visible=false;
				   active_tgbd.UpdateData(dat);
			    }
			}
		}
		
		public function UpdatePage(data:Object):void
		{
			var tF_pageNum:TextField = pagectrl_mc.getChildByName("tF_pageNum") as TextField;
			if(null != tF_pageNum)
				tF_pageNum.text = data.PageNumTxt;
						
			var btn_prev:Button =  pagectrl_mc.getChildByName("btn_prev") as Button;
			if(null != btn_prev)
				btn_prev.enabled = data.preEnable;
						
			var btn_next:Button =  pagectrl_mc.getChildByName("btn_next") as Button;
			if(null != btn_next)
				btn_next.enabled = data.nextEnable;
		}
		
		public function UpdateMyRank(Rank:String , CurrentRank:int, LastRank:int):void
		{
			myrank_mc.updateData(Rank,CurrentRank,LastRank);
		}
		
		public function LoadActiveMenuData( dat:Array ):void
		{
			if(null != dat && menu_list_mc != null)
			{
				menu_list_mc.dataProvider = new DataProvider(dat);
				menu_list_mc.validateNow();
				menu_list_mc.invalidateData();
				menu_list_mc.selectedIndex=0;
			}
		}
		
		public function onTabClick():void
		{
			menu_list_mc.selectedIndex=0;//每次打开选中第一个
		}
		
/*	
		public function Test()
		{
			var itemsData:Array = new Array();
			for (var idx:int = 0; idx < 7; idx++)
			{
				var fbnMarkData:TreeListData = new TreeListData ;
				fbnMarkData.index = idx;
				fbnMarkData.type = SUBNODE;
				fbnMarkData.deepth =0;
				fbnMarkData.visible = true;
				fbnMarkData.label = "副本名字" + idx;
				
				itemsData.push(fbnMarkData);
			}
			itemsData[1].type = SUBNODE;
			itemsData[1].deepth = 0;
			itemsData[2].type = SUBNODE;
			itemsData[2].deepth = 1;
			itemsData[3].type = SUBNODE;
			itemsData[3].deepth = 1;
			LoadActiveMenuData(itemsData);
		}*/
		
/*		function TestData(index:int)
		{
				var personLevelData:Array = new Array();
				personLevelData.push(18);
				for(var index0:int = 1; index0 < 9; ++index0)
				{
					var data0:Object = new Object();
					data0.Id = index0+1;
					data0.RankIndex = index0.toString();
					data0.OnLine = false;
					data0.RoleName = "饿狼传说";
					data0.Job = "2/1";
					data0.Layer = index0;
					data0.TextTimer="1天";
					data0.Level = "20000" + index0;
					personLevelData.push(data0);
				}
				UpdateActiveListData(personLevelData);
			
		}*/
		
		public function setRdo(idx:int):void
		{
			active_tgbd.setRdo(idx);
		}
		
		public function clear():void
		{//还原数据
		    active_tgbd.clear();
			//super.clear();
		}
		
		private function OnPrevPageClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASPrevPageClick");
		}
		
		private function OnNextPageClick(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASNextPageClick");
		}		

	}
	
}
