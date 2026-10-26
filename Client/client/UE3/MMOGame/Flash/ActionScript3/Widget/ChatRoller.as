package ActionScript3.Widget{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	import scaleform.clik.core.UIComponent;

	public class ChatRoller extends UIComponent
	{
		public var AlphaBk_mc:MovieClip;
		public var MaxItem:int = 100;
		public var ListItem:Array=[];
		public var ListIndex:int =-1;
		public var bRoller:Boolean =false;
		
		override protected function configUI():void
		{
			super.configUI();
			this.focusable = false;
			//this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
/*			var dat1:Object = new Object();
			dat1.htmlText = "<a href='event:,3,10340141,34CA71,1,3,E00,E00,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8I'><u><font color='#A335EE' >&lt;精铁法刃&gt;</font></u></a><br>";
						var dat2:Object = new Object();
			dat2.htmlText = "<a href='event:,3,10340142,34CA71,1,3,E00,E00,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,95'><u><font color='#00CC00' >&lt;法师武器&gt;</font></u></a><br>";
						var dat3:Object = new Object();
			dat3.htmlText = "<img src='img://MMO_UIIcon.ChatChannelIcon.ChatChannelWorld'/><FONT COLOR='#ff8000'> <a href='event:,4,4769,1231s'><u><FONT COLOR='#6ae6fc'>[1231s]</FONT></u></a> :   <a href='event:,3,99910113,1B48F5D,1,3,B00,B00,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26'><u><font color='#ffffff' >&lt;短斧&gt;</font></u></a>  </FONT><br>";*/
			
			for(var i=0;i<MaxItem;i++)
			{
				var item:ChatListItem = new ChatListItem();
				item.visible = false;
				item.x = 0;
				item.y = i*20;
				ListItem.push(item);
				addChild(item);
			}
			
			ClearItem();
/*			AddItem(dat1);
			AddItem(dat2);
			AddItem(dat3);*/
			UpdateView();
			
		}
		
/*		public function onRmoved(e:Event)
		{
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			
			for(var i=0;i<ListItem.length;i++)
			{
				if(ListItem[i])
				{
					removeChild( ListItem[i] );
					ListItem[i] = null;
				}
			}			
		}*/
		
		//清除环形循环器显示数据，不清理item控件
		public function ClearItem():void
		{
			ListIndex = -1;
			bRoller = false;
			if(ListItem.length>0){
			    for(var i=0;i<MaxItem;i++)
			    {
				   if(ListItem[i]){
					   ListItem[i].y = 0;
				       ListItem[i].visible = false;
				   }
			    }			
			}
		}
		
		//环形循环器，最多MaxItem个，ListIndex会一直累加
		public function AddItem(data:Object):void
		{
			ListIndex++;
			bRoller = (ListIndex>=MaxItem);
			var i:int=ListIndex%MaxItem;
			if(ListItem[i]){
				ListItem[i].UpdateData(data);
			}
		}
		
		//获取在显示队列里的项，最多MaxItem个，超过MaxItem会取余数
		public function GetItem(index:int):ChatListItem
		{
			if(index>=0 && index<=ListIndex){
				if(bRoller)
				{
					return ListItem[(ListIndex+index+1)%MaxItem];
				}
				else
				{
					return ListItem[index%MaxItem];
				}
			}
			return null;
		}
		
		public function UpdateView():void
		{
			var posY:int = 0;//y;// benchmark;
			var posH:int=0;
			var item:ChatListItem = null;
			var indexStart:int = ListIndex;
			for(var i=0;i<MaxItem;i++)
			{
				item = GetItem(i);
				if(item){
					item.y = posY;
					item.visible = true;
					if(item.blFace==false)
					{
						posH+=item.height;
                        posH-=item.line*2;
					    posY+=item.line*20;
					}
					else
					{
						posH+=item.height;
					    posY+=item.height;
					}
				}
				else
				{
					break;
				}
			}
			AlphaBk_mc.height = posH;
			height = AlphaBk_mc.height;
		}
		
	}
}