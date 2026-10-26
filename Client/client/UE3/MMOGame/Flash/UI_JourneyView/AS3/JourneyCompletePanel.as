package UI_JourneyView.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import scaleform.clik.motion.Tween;
	import ActionScript3.Common.TimerManager;
	import flash.utils.setTimeout;
	import flash.utils.clearTimeout;
	import fl.transitions.easing.Strong;
	import flash.external.ExternalInterface;
	import ActionScript3.Common.Events.ParamEvent;
	
	public class JourneyCompletePanel extends MyPanel {
		
		
		public var upbg:MovieClip;
		public var downbg:MovieClip;
		public var mid_bg:MovieClip;
		public var bg1:MovieClip;
		public var mc_dec:JourneyCompleteContent;
		public var t:uint;
		public var cont:String;
		private var rt:uint;
		override protected function configUI():void
		{
			ShowMode="TCC";
			super.configUI();
			mid_bg.alpha=0;
			bg1.alpha=0;
			upbg.y=-upbg.height;
			downbg.y=cavasHeight;
			this.visible=false;
			stageChangeHandler(null);
			//TimerManager.getInstance().add(7000,step);
		}
		
/*		private function step():void
		{
			UCShowEffect("边界村章节");
		}*/
		
		public function UCShowEffect(str:String):void
		{
			this.visible=true;
			cont=str;
			upbg.alpha=0.2;
			downbg.alpha=0.2;
			upbg.y=-upbg.height;
			downbg.y=cavasHeight;
			var tween1:Tween=new Tween(1000,upbg,{y:0,alpha:1},{ease:Strong.easeIn});
			var tween2:Tween=new Tween(1000,downbg,{y:cavasHeight-downbg.height,alpha:1},{onChange:onChange,ease:Strong.easeIn});
			mid_bg.alpha=0;
			var tween3:Tween=new Tween(1000,mid_bg,{alpha:0.7},{ease:Strong.easeIn});
			bg1.alpha=0;
			rt=setTimeout(onComplete1,1300);
			t=setTimeout(clearEffect,4500);
		}
		
		private function onComplete1():void
		{
			clearTimeout(rt);
			var tween4:Tween=new Tween(200,bg1,{alpha:1},{ease:Strong.easeIn});
			mc_dec.updateTxt(cont);
		}
		
		//播放完成
		public function clearEffect():void
		{
			clearTimeout(t);
			var tween3:Tween=new Tween(100,mid_bg,{alpha:0});
			var tween1:Tween=new Tween(120,upbg,{y:-upbg.height,alpha:0},{onChange:onChange,ease:Strong.easeIn});
			var tween2:Tween=new Tween(120,downbg,{y:cavasHeight,alpha:0},{ease:Strong.easeIn});
			mc_dec.clearEffect();
			//var tween4:Tween=new Tween(200,mc_dec,{scaleX:2.5,scaleY:2.5},{onComplete:onComplete,onChange:onChange1});
			
			ExternalInterface.call("ASJourneyComplete");
		}
		
		public function playEffect():void
		{
			var tween5:Tween=new Tween(180,bg1,{alpha:0,onComplete:onComplete});
		}

		private function onChange():void
		{
			upbg.alpha-=0.2;
			downbg.alpha-=0.2;
		}
		
		public function onComplete():void
		{
			this.visible=false;
			cont="";
			bg1.alpha=0;
			mc_dec.clear();
			mc_dec.x=bg1.x+69;
			mc_dec.y=bg1.y+72;
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			mid_bg.width=cavasWidth;
			mid_bg.height=cavasHeight;
			upbg.width=cavasWidth;
			downbg.width=cavasWidth;
			bg1.x=cavasWidth-bg1.width>>1;
			bg1.y=cavasHeight-bg1.height>>1;
			mc_dec.x=bg1.x+69;
			mc_dec.y=bg1.y+72;
		}
	}
	
}
