package ActionScript3.Widget
{
	import flash.external.ExternalInterface;
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import ActionScript3.MyWindowsFrame;
	
	public class WareHousePanel extends MyPanel
	{
		public var BtnLock_mc:Button;
		public var BtnSort_mc:Button;
		
		//public var bg:MyWindowsFrame;
		public var TabGroup_mc:MovieClip;
		
		override protected  function configUI():void
		{
//			if(bg)
//			{
//				btn_close = bg.btn_close;
//				InfoDragButton_mc = bg.InfoDragButton_mc;
//			}
			
			super.configUI();
			
			if( TabGroup_mc!=null)
			{
				TabGroup_mc["tab0_mc"].BagBtnIcon_mc.gotoAndStop(1);
				TabGroup_mc["tab1_mc"].BagBtnIcon_mc.gotoAndStop(2);
				TabGroup_mc["tab2_mc"].BagBtnIcon_mc.gotoAndStop(3);
				TabGroup_mc["tab3_mc"].BagBtnIcon_mc.gotoAndStop(4);
				TabGroup_mc["tab4_mc"].BagBtnIcon_mc.gotoAndStop(5);
			}
			
			BtnSort_mc.addEventListener(MouseEvent.CLICK, onSort);
			
			ExternalInterface.call( "RegisterWarehouse", this );
			
			//SetPanelText( { panelName:"cangku" } );
		}
		
		public function SetPanelText( data:Object )
		{
			/*var tabArray:Array = data.tabData as Array;
			var i:int = 0;
			for( i = 0 ; i < tabArray.length ; i++ )
			{
							
				var tab:RadioButton = this.getChildByName( "tab"+i+"_mc" ) as RadioButton;
				if(tab)
				{
					tab.itemid = tabArray[i].typeId;
					tab.label = tabArray[i].text;
					tab.addEventListener( ButtonEvent.CLICK , clickTab );
				}			
			}
			
			var labelArray:Array = data.labelData as Array;
			for( i = 0 ; i < labelArray.length ; i++ )
			{
							
				var labelButton:RadioButton = this.getChildByName( "label"+i+"_mc" ) as RadioButton;
				if(labelButton)
				{
					labelButton.itemid = labelArray[i].typeId;
					labelButton.label = labelArray[i].text;
					labelButton.addEventListener( ButtonEvent.CLICK , clickLabel );
				}			
			}*/
			if( MyWindowsFrame_mc && MyWindowsFrame_mc.tF_windowTitle )
			{
				MyWindowsFrame_mc.tF_windowTitle.text = data.panelName;
			}
			if( BtnSort_mc )
			{
				BtnSort_mc.label = data.button1;
			}
		}
		
		public function onSort()
		{
			BtnSort_mc.enabled = false;
			ExternalInterface.call("ASSortWarehouse");
		}
		
		public function UCUpdateSortTimer(secondsLeft:int)
		{
			BtnSort_mc.label =  secondsLeft.toString();
		}
		
		public function UCEnableSort(e:Boolean, str:String)
		{
			BtnSort_mc.enabled = e;
			BtnSort_mc.label = str;
		}
		
		override public function UCGetWidth():int
		{
			var modifiedWidth:int;
			if( MyWindowsFrame_mc ){
				modifiedWidth = MyWindowsFrame_mc.width;//( super.UCGetWidth() - 22 );
			}
			
			return modifiedWidth;//剪掉的是TabBtn�点的宽度
		}
	}
}