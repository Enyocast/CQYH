package UI_JourneyView.AS3 {
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.display.Sprite;
	import scaleform.clik.motion.Tween;
	import flash.filters.BlurFilter;
	import flash.filters.GlowFilter;
	import fl.transitions.easing.Strong;
	import fl.transitions.easing.Bounce;
	import fl.transitions.easing.Regular;
	import flash.utils.clearTimeout;
	import flash.utils.setTimeout;
	
	public class JourneyCompleteContent extends MovieClip {
		
		public var _txt:MovieClip;
		//public var lbtxt:TextField;
		public var bg2:MovieClip;
		public var i:int;
		public var l:int;
		public var arr:Array=[];
        var blur:BlurFilter=new BlurFilter(20,20,3);
		public var txt_mc:MovieClip;
		var speed:int=250;
		var tt:uint
		
		public function JourneyCompleteContent() 
		{
			clear();
		}
		
		public function updateTxt(str:String):void
		{
			clear();
			this.visible=true;
			l=str.length;
			arr=str.split("");
			TxtEffecf();
		}
		
		private function onComplete():void
		{
			txt_mc.txt.appendText(_txt.lbtxt.text);
			_txt.lbtxt.text="";
			if(i==l){
				tt=setTimeout(step,350);
			}else{
				TxtEffecf();
			}
		}
		
	    private function step():void
		{
			clearTimeout(tt);
			bg2.gotoAndPlay(1);
			bg2.visible=true;
			//bg2.scaleX=2.2;
			//bg2.scaleY=2.2;
			//var tween1:Tween=new Tween(150,bg2,{scaleX:1,scaleY:1,ease:Regular.easeIn});
		}
		
		public function TxtEffecf():void
		{
			speed-=30;
			_txt.scaleX=3.5;
			_txt.scaleY=3.5;
			_txt.lbtxt.text=arr[i];
			_txt.y=-48;
			
			var _x:int=txt_mc.x+(i*45.7);
		    var tween2:Tween=new Tween(speed,_txt,{x:_x,y:txt_mc.y,scaleX:1,scaleY:1},{ease:Regular.easeOut,onComplete:onComplete});
			i++;
		}
		
		public function clearEffect():void
		{
			txt_mc.filters=[blur];
            bg2.filters=[blur];
			var tween1:Tween=new Tween(150,txt_mc,{alpha:0.8,visible:false},{ease:Strong.easeIn,onChange:onChange});
			var tween2:Tween=new Tween(150,bg2,{scaleX:2,scaleY:2,alpha:0.5,visible:false},{ease:Strong.easeIn,onComplete:onCompleteEnd});
		}
		private function onChange():void
		{
			blur.blurX=blur.blurY+=6;
		    txt_mc.filters= bg2.filters=[blur];
			bg2.y-=55;
		}
		
		private function onCompleteEnd():void
		{
			JourneyCompletePanel(parent).playEffect();
		}
		
		public function clear():void
		{
			speed=250;
			i=0;
			blur.blurX=blur.blurY=1;
			txt_mc.filters=bg2.filters=null;
			txt_mc.x=3;
			txt_mc.y=5;
			txt_mc.visible=true;
			
			bg2.x=52;
			bg2.y=-121;
			bg2.alpha=1;
			bg2.scaleX=bg2.scaleY=1;
			bg2.visible=false;
			bg2.gotoAndStop(1);
			
			this.visible=false;

			_txt.x=3;
			_txt.y=-48;
			_txt.lbtxt.text=txt_mc.txt.text="";
			
		}
	}
	
}
