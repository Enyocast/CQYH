package UI_DynamicUIWidget.AS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import ActionScript3.MyPanel;
	import flash.utils.clearTimeout;
	import flash.utils.setTimeout;
	import ActionScript3.Common.Events.ParamEvent;

	public class RenownUnlockAOG extends MyPanel
	{
		public var Detail_mc:MovieClip;
		protected var _detailText:TextField;

		override protected  function configUI():void 
		{			
		    ShowMode="BCB";
			super.configUI();
			if(Detail_mc){
				_detailText = Detail_mc.getChildByName('tF_Text') as TextField;
			}
			stop();
			this.visible = false;
			stageChangeHandler(null);
			//UCSetRenownUnlockAOGString("神龙护卫队");
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{ 
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-this.width)>>1;
			this.y=140;
		}

		public function UCSetRenownUnlockAOGString(content:String):void
		{
			if( _detailText != null ){
				_detailText.text = content;
			}
			this.visible = true;
			this.gotoAndPlay("Play");
		}
		
		public function UCPlayHideAnimation():void
		{
			this.gotoAndPlay("Hide");
		}
		
		public function OnShowAnimationEnd():void
		{ 
			stop();
			ExternalInterface.call( "ASRenownUnlockAOGShowEnd");
			var delayToHide:int = setTimeout(function(){
				clearTimeout(delayToHide),
				UCPlayHideAnimation();
			}, 2000);
		}
		
		public function OnHideAnimationEnd():void
		{
			this.visible = false;
			stop();
			ExternalInterface.call( "ASRenownUnlockAOGHideEnd");
		}
	}
}