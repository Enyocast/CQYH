package UI_SkillbarWidget.AS3 {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.UILoader;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	
	public class PetSkillIcon extends UIComponent {
		
		public var loop:MovieClip;
		public var _status:Boolean=false;
		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(MouseEvent.CLICK,clickHandler);
			this.addEventListener(MouseEvent.ROLL_OUT,outHandler);
			this.addEventListener(MouseEvent.ROLL_OVER,overHandler);
			updateState(false);
		}

		private function clickHandler(evt:MouseEvent):void
		{
			if(_status==false)
			{
				ExternalInterface.call("ASChangePetState",this.itemid );
				PetSkill(parent).updatePetSkill(this.itemid);
			}
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_PlainText",this );
		}
		
		private function overHandler(evt:MouseEvent):void
		{
			ExternalInterface.call("ASGetStringByID",this,"tipsHtml","MMOGame.PetSkill.PetSkillIcon"+this.itemid );
			ExternalInterface.call("ASShowTips_PlainText",this );
		}

		public function updateState(bl:Boolean):void
		{
			_status=bl;
			if(bl)
			{
				loop.gotoAndPlay(1);
			    loop.visible=true;
			}
			else
			{
				loop.gotoAndStop(1);
			    loop.visible=false;
			}
		}
	}
	
}
