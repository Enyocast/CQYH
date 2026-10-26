package ActionScript3
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import flash.utils.getDefinitionByName;
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import ActionScript3.MyDamageNumber;
	import flash.text.TextField;
	import flash.external.ExternalInterface;

	public class GravityObj extends Object
	{
		public var isEnable:Boolean = false;
		public var isVisible:Boolean = false;		
		
		//单位厘米,秒
		public var sx:Number = 400;
		public var sy:Number = 300;
		public var sz:Number = 0;

		public var vx:Number = 0;
		public var vy:Number = 0;
		public var vz:Number = 200;

		public var ax:Number = 0;
		public var ay:Number = 98;
		public var az:Number = 0;

		public var sxRange:Number = 0;
		public var syRange:Number = 0;
		public var szRange:Number = 0;

		public var vxRange:Number = 0;
		public var vyRange:Number = 0;
		public var vzRange:Number = 0;

		public var axRange:Number = 0;
		public var ayRange:Number = 0;
		public var azRange:Number = 0;

		public var scaleStart:Number = 0.4;
		public var scaleBomb:Number = 1.4;
		public var scaleEnd:Number = 0.2;


		public var scaleStartRange:Number = 0;
		public var scaleBombRange:Number = 0;
		public var scaleEndRange:Number = 0;

		public var durTime:Number = 0.8;
		public var bombTime:Number = 0.2;
		public var dumping:Number = 0.003;

		public var alphaStart:Number = 0.6;
		public var alphaBomb:Number = 1.0;
		public var alphaEnd:Number = 0.1;
		public var alphaPow:Number = 1;

		//内部使用
		public var alphaCur:Number = 1;
		public var scaleCur:Number = 1;
		public var curTime:Number = 0;
		public var isOver:Boolean = false;
		public var uiObj:UIComponent;


		public function Init(ui:UIComponent)
		{
			uiObj = ui;
			isOver = false;
			curTime = 0;
			durTime = 0.8;
		}

		public function InitData()
		{
			isOver = false;
			curTime = 0;

			sx = sx + Math.random() * sxRange;
			sy = sy + Math.random() * syRange;
			sz = sz + Math.random() * szRange;

			vx = vx + Math.random() * vxRange;
			vy = vy + Math.random() * vyRange;
			vz = vz + Math.random() * vzRange;

			ax = ax + Math.random() * axRange;
			ay = ay + Math.random() * ayRange;
			az = az + Math.random() * azRange;

			scaleStart = scaleStart + Math.random() * scaleStartRange;
			scaleBomb = scaleBomb + Math.random() * scaleBombRange;
			scaleEnd = scaleEnd + Math.random() * scaleEndRange;
			scaleCur = scaleStart;

			alphaCur = alphaStart;
		}


		public function UpdateTween(DeltaTime:Number)
		{
			var lv1:Number = 0;
			var lv2:Number = 0;
			var lastTime:Number = curTime;
			curTime +=  DeltaTime;
			if (curTime>durTime)
			{
				curTime = durTime;
				isOver = true;
			}
			

			//表现层
			if (curTime<bombTime)
			{
				lv1 = Math.pow( curTime / bombTime ,  0.5);
				scaleCur = scaleStart + (scaleBomb - scaleStart) * lv1;
				alphaCur = alphaStart + (alphaBomb - alphaStart) * lv1;
			}
			else
			{
				lv2 = Math.pow(   (curTime-bombTime)/durTime   ,  alphaPow);
				scaleCur = scaleBomb + (scaleEnd - scaleBomb) * lv2;
				alphaCur = alphaBomb + (alphaEnd - alphaBomb) * lv2;
			}


//			//物理层
			var pt = Math.pow(curTime/durTime,dumping) - Math.pow(lastTime/durTime,dumping);
			sx = sx + vx*0.02*pt;
			sy = sy + vy*0.02*pt;
			sz = sz + vz*0.02*pt + 0.5*az*(curTime-lastTime)*(curTime+lastTime);

			
			
//			var dumpSpeed2 = vx * vx + vy * vy + vz * vz;
//			var dumpSpeed = Math.sqrt(dumpSpeed2);
//			var process = DeltaTime * dumpSpeed;
//			var deltaNum:int = int(process/50)+1;
//			var deltaT = DeltaTime / Number(deltaNum);
//			for (var i:Number=0; i<deltaNum; i++)
//			{
//				var dumpa = dumpSpeed * dumping * deltaT;//dumpSpeedLv*dumpSpeedLv*dumpSpeedLv*DeltaTime;
//
//				vx = vx - vx * dumpa + ax * deltaT;
//				vy = vy - vy * dumpa + ay * deltaT;
//				vz = vz - vz * dumpa + az * deltaT;
//
//				sx = sx + vx * deltaT;
//				sy = sy + vy * deltaT;
//				sz = sz + vz * deltaT;
//
//				dumpSpeed2 = vx * vx + vy * vy + vz * vz;
//				dumpSpeed = Math.sqrt(dumpSpeed2);
//
//			}

		}
	}
}