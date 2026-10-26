package UI_Hang.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.RadioButton;
	
	
	public class GameTab extends UIComponent {
		
		public var config0:ConfigGame1;
		public var config1:ConfigGame2;
		public var config2:ConfigGame3;
		public var tab_0:RadioButton;
		public var tab_1:RadioButton;
		public var tab_2:RadioButton;
		override protected function configUI():void
		{
			super.configUI();
			var i:int=0;
			for(i=0;i<3;i++)
			{
				var btn:RadioButton=(this.getChildByName("tab_"+i) as MovieClip) as RadioButton;
				if(btn)
				{
					btn.itemid=i;
				    btn.addEventListener(MouseEvent.CLICK,clickHandler);
				}
			}
			tab_0.selected=true;
			changeTabPage(0);
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			var btn:RadioButton=evt.target as RadioButton;
			if(btn)
			{
				changeTabPage(btn.itemid);
			}  
		}
		
		private function changeTabPage(id:int):void
		{
			var i:int=0;
			for(i=0;i<3;i++)
			{
				var ui:MovieClip=this.getChildByName("config"+i) as MovieClip;
				if(ui && i==id)
				{
					ui.visible=true;
				}
				else
				{
					ui.visible=false;
				}
			}
		}
	}
	
}
