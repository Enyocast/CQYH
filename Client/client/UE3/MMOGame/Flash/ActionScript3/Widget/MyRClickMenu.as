package ActionScript3.Widget
{
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.clik.events.ComponentEvent;

	public class MyRClickMenu extends UIComponent //ActionScript.MyPanel
	{
		var RClicklistItem0:Button;
		var RClicklistItem1:Button;
		var RClicklistItem2:Button;
		var RClicklistItem3:Button;
		var RClicklistItem4:Button;
		var RClicklistItem5:Button;
		var RClicklistItem6:Button;
		var RClicklistItem7:Button;
		var RClicklistItem8:Button;
		var RClicklistItem9:Button;
		var RClicklistItem10:Button;
		var RClicklistItem11:Button;
		var RClicklistItem12:Button;
		var RClicklistItem13:Button;
		var RClicklistItem14:Button;
		var RClicklistItem15:Button;
		var RClicklistItem16:Button;
		var RClicklistItem17:Button;
		var RClicklistItem18:Button;
		var RClicklistItem19:Button;
		
		var tF_menuOwner:TextField;
		public var MenuLevel:int = 0 ;//右键菜单级别
		
		var MaxLimit:int = 20;
	
		protected var _displayPriority:int = 2;
		public var CurPriority:int=0;
		
		override protected  function configUI():void 
		{
			super.configUI();
			var i:int;
			for( i = 0 ; i< MaxLimit ; i++)
			{
				var itembutton:Button = this.getChildByName( "RClicklistItem"+i ) as Button;
				itembutton.itemid = i;
				itembutton.isHtmlLabel = true;
				itembutton.addEventListener( MouseEvent.CLICK , ClickItemButton );
			}
		}
		
		public function ResetChildMenuButton():void
		{
			//子菜单的标题栏被去掉了，所以要调用下这个函数
			var splitLine:MovieClip = this.getChildByName( "splitLine" ) as MovieClip;
			if( splitLine )
			{
				splitLine.visible = false;
			}
			if( tF_menuOwner )
			{
				tF_menuOwner.visible = false;
			}
			var i:int;
			for( i = 0 ; i< MaxLimit ; i++)
			{
				var itembutton:Button = this.getChildByName( "RClicklistItem"+i ) as Button;
				if(itembutton)
				{
					itembutton.y = i*itembutton.height + 7;
				}
			}
		}
		
		private function ClickItemButton(e:MouseEvent):void
		{
			if( e.target is Button)
			{
				ExternalInterface.call("ASClickRightMenuItem", MenuLevel, (e.target as Button).itemid );
			}
		}
		
		public function UCShowMode():void
		{
			scaleform.clik.managers.PopUpManager.showModal(this);
			dispatchEvent(new ComponentEvent(ComponentEvent.SHOW));
		}
		
		public function UCDismissMode():void
		{
			scaleform.clik.managers.PopUpManager.showModal(null);
		}
		
		public function UCShow(v:Boolean, priority:int):void
		{
			if(v)
			{
				_displayPriority = priority;
				PopUpManager.show(this, -1, -1, null, priority);
				dispatchEvent(new ComponentEvent(ComponentEvent.SHOW));
			}
			else
			{
				if(this.parent)
				{
					this.parent.removeChild(this);
				}
				dispatchEvent(new ComponentEvent(ComponentEvent.HIDE));
			}
		}
	}
}