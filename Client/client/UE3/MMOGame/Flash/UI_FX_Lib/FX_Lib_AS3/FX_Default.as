package UI_FX_Lib.FX_Lib_AS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	import scaleform.clik.core.UIComponent;
	import flashx.textLayout.formats.Float;
	import scaleform.clik.controls.UILoader;
//	import UI_FX_Lib.FX_Lib_AS3.loaderFX;
	
	public class FX_Default extends UIComponent
	{
		/*public var par_star1:UILoaderFX;
		public var par_star2:UILoaderFX;
		public var par_ripple1:UILoaderFX;
		public var par_ripple2:UILoaderFX;*/
		
		public var par_star1:MovieClip;
		public var par_star2:MovieClip;
		public var par_ripple1:MovieClip;
		public var par_ripple2:MovieClip;
		
		public var g_time:Number;
		
		public var g_MainType:int = 0;
		public var g_SubType:int = 0;
		
		public var g_Level:int = 10;
		
		public var g_Color:ColorTransform;
		
		public var initScaleX:Number = 1.0;
		public var initScaleY:Number = 1.0;
		public var initScaleXX:Number = 1.0;
		public var initScaleYY:Number = 1.0;

		override protected function configUI():void
		{
			
			super.configUI();
			g_time = 0;
			
			stage.addEventListener(Event.ENTER_FRAME, onPreRender);
			
			trace("=======FX_Default", par_star1 , par_star1.x);
			
			//par_star1.redMultiplier = 0;
			//par_star1.redOffset = -200;
			
			//g_Color = new ColorTransform(0.3,0.9,0.2,1,0,0,0,0);
			
			//transform.colorTransform = g_Color;
			
			//SetIconType(4);
			
			//SetFxPic("42.png","41.png");

			//SetFxLevel(1);
		}

		public function SetMouseEnabled(e:Boolean)
		{
			par_star1.SetMouseEnabled(e);
			par_star2.SetMouseEnabled(e);
			par_ripple1.SetMouseEnabled(e);
			par_ripple2.SetMouseEnabled(e);
			mouseEnabled = e;
		}
		
		public function SetFxType(nMain:int,nSub:int)
		{
			g_MainType = nMain;
			g_SubType  = nSub;
		}
		
		public function SetFxLevel(nLevel:int)
		{
			g_Level = nLevel;
			
			if(nLevel < 4)
				nLevel = 4;
			par_star1.scaleX =initScaleX*nLevel/10.0;
			par_star1.scaleY = initScaleY*nLevel/10.0;
			
			par_star2.scaleX = initScaleXX*nLevel/10.0;
			par_star2.scaleY =initScaleYY*nLevel/10.0;
			
			trace("=======SetFxLevel",par_star1.scaleX,par_star1.scaleY);
		}
		
		public function SetFxPic(nMainPic:String,nSubPic:String)
		{
			par_star1.source = nSubPic;
			par_star2.source = nSubPic;
			
			par_ripple1.source = nMainPic;
			par_ripple2.source = nMainPic;
			
			initScaleX =  par_star1.scaleX;
			initScaleY =  par_star1.scaleY;
			
			initScaleXX =  par_star2.scaleX;
			initScaleYY =  par_star2.scaleY;
			
			ExternalInterface.call("ASTrace", "2  GasIcon0 " + nMainPic +  "  GasIcon1 " + nSubPic);
		}
		public function SetColor(redM:Number,greenM:Number,blueM:Number,alphaM:Number)
		{
			g_Color = new ColorTransform(redM,greenM,blueM,alphaM,0,0,0,0);
			
			transform.colorTransform = g_Color;
		}
		
		public function SetIconType(nType:int)
		{
			g_MainType = nType;
			if(nType == 0)
			{
				g_Color = new ColorTransform(0.7,0.7,0.7,1,0,0,0,0);
				trace("=======0");
			}
			else if(nType == 1)
			{
				g_Color = new ColorTransform(0.2,1,0,1,0,0,0,0);
				trace("=======1");
			}
			else if(nType == 2)
			{
				g_Color = new ColorTransform(0,0.4,0.7,1,0,0,0,0);
				trace("=======2");
			}
			else if(nType == 3)
			{
				g_Color = new ColorTransform(0.6,0.3,1,1,0,0,0,0);
				trace("=======3");
			}
			else
			{
				g_Color = new ColorTransform(1,0.5,0,1,0,0,0,0);
				trace("=======4");
			}
			transform.colorTransform = g_Color;
		}
		public function onPreRender(evt:Event):void
		{
			//g_time +=  1.0 / 24.0;
			//par_star1.scaleX = Math.sin(g_time);
			//par_star1.scaleY = par_star1.scaleX;

			//par_star2.scaleX = Math.sin(g_time);
			//par_star2.scaleY = par_star2.scaleX;

			
			par_ripple1.rotationZ +=  11;
			par_ripple2.rotationZ -=  4;
			
			par_star1.rotationZ +=  (g_Level + g_MainType + 3);
			par_star2.rotationZ -=  (g_Level + 2 + g_MainType);
		}
	}
}