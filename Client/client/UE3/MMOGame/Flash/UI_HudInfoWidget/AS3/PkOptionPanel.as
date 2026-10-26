package UI_HudInfoWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.clik.events.ComponentEvent;
	
	
	public class PkOptionPanel extends MovieClip {
		
		public var btn_pkOption0:Button;
		public var btn_pkOption1:Button;
		public var btn_pkOption2:Button;
		public var btn_pkOption3:Button;
		public var btn_pkOption4:Button;
		
		public function PkOptionPanel():void
		{
			var i:int=0;
			for(i=0;i<5;i++)
			{
				var btn:Button=this.getChildByName("btn_pkOption"+i) as Button;
				if(btn)
				{
					btn.itemid=i;
					ExternalInterface.call( "SetTextByID",btn_pkOption0.textField,"MMOGame.PkMode.PkMode0");
				    btn.addEventListener(MouseEvent.CLICK,clickHandler);
					var mc:MovieClip=btn.getChildByName("iconPkType_mc") as MovieClip;
					if(mc)
				      mc.gotoAndStop(i+1);
					
				}
			}
		}
		
		private function clickHandler(evt:MouseEvent):void
		{
			var btn:Button=evt.currentTarget as Button;
			ExternalInterface.call( "ASSetPkMode",btn.itemid);
			this.visible=false;
	        Hide();
		}
		
		public function UCShow(v:Boolean,_x:int,_y:int,priority:int):void
		{
			if(v==true)
			{
				ExternalInterface.call( "SetTextByID",btn_pkOption0.textField,"MMOGame.PkMode.PkMode0");
			    ExternalInterface.call( "SetTextByID",btn_pkOption1.textField,"MMOGame.PkMode.PkMode1");
			    ExternalInterface.call( "SetTextByID",btn_pkOption2.textField,"MMOGame.PkMode.PkMode2");
			    ExternalInterface.call( "SetTextByID",btn_pkOption3.textField,"MMOGame.PkMode.PkMode3");
			    ExternalInterface.call( "SetTextByID",btn_pkOption4.textField,"MMOGame.PkMode.PkMode4");
			    PopUpManager.show(this,_x,_y,null,5);
                this.dispatchEvent(new ComponentEvent(ComponentEvent.SHOW));
			}
			else
			{
				Hide();
			}
		}
		
		public function Hide():void
		{
			if(this.parent)
			{
				this.parent.removeChild(this);
			}
			this.dispatchEvent(new ComponentEvent(ComponentEvent.HIDE));
		}

	}
	
}
