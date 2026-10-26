package UI_SplitCompound.SplitCompoundAS3
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import scaleform.clik.controls.Button;
	
	public class ComposePanel extends MyPanel
	{
		public var ComposeBtn:Button;
		//public var ComposeBtn2:Button;
		
		public var EquipSlot:MyItemSlot;
		
		public var MatConsume_0:MyItemSlot;
		public var MatConsume_1:MyItemSlot;
		public var MatConsume_2:MyItemSlot;
		public var MatConsume_3:MyItemSlot;
		public var MatConsume_4:MyItemSlot;
		public var MatConsume_5:MyItemSlot;
		
		public var CostText:TextField;
		
		public var MatConsumeTf_0:TextField;
		public var MatConsumeTf_1:TextField;
		public var MatConsumeTf_2:TextField;
		public var MatConsumeTf_3:TextField;
		public var MatConsumeTf_4:TextField;
		public var MatConsumeTf_5:TextField;
		public var tf_name:TextField;
		
		public var effect0:MovieClip;
		public var effect1:MovieClip;
		public var effect2:MovieClip;
		public var effect3:MovieClip;
		public var effect4:MovieClip;
		public var effect5:MovieClip;
		public var effect6:MovieClip;
		public var crit_animation:MovieClip;
		
		override protected function configUI():void
		{
			super.configUI();
			
			if(ComposeBtn){
				ComposeBtn.addEventListener(MouseEvent.CLICK, OnClickCompose);
				CostText.text = "0";
			}
			clear();
			crit_animation.visible = false;
		}
		
		public function UCSetItemName(dat:String):void
		{
			tf_name.text=dat;
		}
		
		public function UCShowCritAnimation():void
		{
			crit_animation.visible = true;
			if(crit_animation.currentFrame == 1)//don't play the animation if the last one hasn't finised.
			{
				crit_animation.gotoAndPlay(1);
			}
		}
		
		//called by script on crit_animation frame
		public function onCritAnimationComplete():void
		{
			crit_animation.visible = false;
			crit_animation.gotoAndStop(1);
			ExternalInterface.call("ASNotifyComposeBounsAnimPlayedOver");
		}
		
		public function OnClickCompose(e:MouseEvent):void
		{
			var i:int=1;
			for(i=1;i<6;i++)
			{
				var txt:TextField=this.getChildByName("MatConsumeTf_"+i) as TextField;
				var l:int=txt.text.indexOf("/");
				if(txt.text.length>0){
					var str:String=txt.text.substr(l+1);
					var num:int=parseInt(str);
					var maxNum:int=parseInt(str);
					if(num>0 && txt.textColor==65280){
						var mc:MovieClip=this.getChildByName("effect"+i) as MovieClip;
						mc.visible=true;
						mc.gotoAndPlay(1);
						if(i==1){
							mc.addFrameScript(16,handlerEffect);
							mc.addFrameScript(24,handerCommplete);
						}
					}
				}
			}
			ExternalInterface.call("ASCompose");
			//sound
			playSound("EquipCompose_FX");
		}
		
		private function handlerEffect():void
		{
			effect0.visible=true;
			effect0.gotoAndPlay(1);
		}
		
		private function handerCommplete():void
		{
			effect6.visible=true;
			effect6.gotoAndPlay(1);
			effect6.addFrameScript(69,handerEnd);
		}
		
		private function handerEnd():void
		{
			clear();
		}
		
		private function clear():void
		{
		    var i:int=0;
			for(i=0;i<7;i++){
				var mc:MovieClip=this.getChildByName("effect"+i) as MovieClip;
				mc.visible=false;
				mc.gotoAndStop(1);
			}
		}
	}
}