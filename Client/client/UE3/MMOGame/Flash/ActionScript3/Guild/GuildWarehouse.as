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

	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import scaleform.clik.controls.RadioButton;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.MyWindowsFrame;
	import ActionScript3.ItemSlot.MyItemSlot;


	public class GuildWarehouse extends MyPanel
	{
		const WareNum:int = 6;
		public var UpdateButton:Button;
		public var LogButton:Button;
		public var OperateInfo:TextField;

		public var Ware0:RadioButton;
		public var Ware1:RadioButton;
		public var Ware2:RadioButton;
		public var Ware3:RadioButton;
		public var Ware4:RadioButton;
		public var Ware5:RadioButton;

		public var log:MovieClip;
		public var LogClose:Button;

		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI(); 
			
			//ExternalInterface.call( "RegisterGuildWarehouse" , this );
			var j:int=0;
			for(j=0;j< 70;j++){
				var slot:MyItemSlot=this.getChildByName("ItemSlot"+j) as MyItemSlot;
				slot.itemSlotBg.visible=false;
				if(j>55){
					slot.mouseChildren=false;
				    slot.mouseEnabled=false;
				    slot.visible=false;
				}
			}

			for (var i:int = 0; i < WareNum; i++)
			{
				var wareTab:RadioButton = this.getChildByName( "Ware"+i ) as RadioButton;
				wareTab.itemid = i;
				wareTab.addEventListener( ButtonEvent.CLICK , clickWareTab , false , 0 , true );
			}

			if(UpdateButton)
				UpdateButton.addEventListener( MouseEvent.CLICK , clickUpdateButton  );
				
			if(LogButton)
			{
				LogButton.label = "仓库信息";
				LogButton.addEventListener( MouseEvent.CLICK , clickLogButton  );
			}

			if(log)
			{
				var logBg = log.getChildByName("MyWindowsFrame_mc") as MovieClip;
				if( logBg )
				{
					logBg.tF_windowTitle.text="仓库信息";
					LogClose = logBg.getChildByName("btn_close");
				}
				
				if(LogClose)
				{
					LogClose.visible = true;
					LogClose.addEventListener(MouseEvent.CLICK,CloseLog,false,0,true);
				}
				
				log.visible = false;
			}
			//SetTabEnable(3);
			//SetPanelText( { titleName:"gg" ,updateButton:"bb",moreButton:"cc" } );
			//SetAccessInfoText( "gggg\n\n\n\n\n\n\n\ngggg\n\n\n\ngggg\n\n\n\ngggg\ngggg\ngggg\ngggg\ngggg\ngggg\ngggg" );
		}
		
		function CloseLog()
		{
			if(log)
			{
				log.visible = false;
			}
		}
		
		public function SetTabEnable( num:int )
		{
			for (var i:int = 0; i < WareNum; i++)
			{
				var wareTab:RadioButton = this.getChildByName( "Ware"+i ) as RadioButton;
				
				if( wareTab && i < num )
				{
					wareTab.enabled = true;
				}
				else
				{
					wareTab.enabled = false;
				}
				
				//wareTab.groupName = "tabGroup";
				//wareTab["newHint"].visible = false;
			}
		}
		
		public function SetAccessInfoText( txt:String ):void
		{
			if(log)
			{
				log.updateData(txt);
			}
		}

		public function SetPanelText( data:Object )
		{
			this.SetWindowTitle(data.titleName);
			var tabList:Array = data.tabList;
			if (tabList)
			{
				for (var i:int = 0; i < tabList.length; i++)
				{
					var wareTab:RadioButton = this.getChildByName( "Ware"+i ) as RadioButton;
					if (wareTab)
					{
						wareTab.label = tabList[i];
					}
				}
			}

			if (UpdateButton)
			{
				UpdateButton.label = data.updateButton;
			}
		}

		function clickWareTab( e:Event )
		{
			if (e.currentTarget is RadioButton)
			{
				ExternalInterface.call( "ASGuildWarehouseTab" , ( e.currentTarget as RadioButton ).itemid );
			}
		}

		function clickUpdateButton( e:Event )
		{
			ExternalInterface.call( "ASGuildWarehouseUpdate" );
		}
		
		function clickLogButton( e:Event )
		{
			if(log)
			{
				log.visible = !log.visible;
				ExternalInterface.call( "ASViewGuildLog", log.visible );
			}
		}

/*		function clickMoreButton( e:Event )
		{
			ExternalInterface.call( "ASGuildWarehouseMore" );
		}*/
	}
}