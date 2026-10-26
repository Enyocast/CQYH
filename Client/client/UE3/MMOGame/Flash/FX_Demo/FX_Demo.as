import flash.display.MovieClip;
import flash.display3D.IndexBuffer3D;
import ActionScript3.FX.Firework.*;

var maxCnt:int = 32;
var circleCnt:int = 3;
var startRadius = 100;
var centerX:Number = 640;
var centerY:Number = 320;
var scaleRange:Number = 0.5;
var minScale:Number = 0.1;
var radiusAddScale:Number = 100;

var rootObj:MovieClip = new MovieClip;

for(var i:int = 0; i < maxCnt; ++i)
{
	var percent:Number = i / maxCnt;
	var stepAng:Number = Math.PI * 2 * circleCnt;
	
	var inst:MovieClip = new Test_ParClass;
	
	var ang:Number = percent * stepAng;
	
	var radius:Number = percent * radiusAddScale + startRadius;
	var sinVal:Number = Math.sin(ang);
	
	inst.x = 0 + sinVal * radius;
	inst.y = 0 + Math.cos(ang) * radius;
	
	inst.scaleX = percent * scaleRange + minScale;
	inst.scaleY = inst.scaleX;
	
	rootObj.addChild(inst);
}

this.addChild(rootObj);
rootObj.x = centerX;
rootObj.y = centerY;

stage.addEventListener(Event.ENTER_FRAME, onPreRender)
//var g_time:Number;


// 添加测试用的Firework
var testFx:MainPlus = new ActionScript3.FX.Firework.MainPlus();
this.addChild(testFx);


function onPreRender(evt:Event):void
{
	//g_time += 1.0/24.0;	
	rootObj.rotation += 1;//Math.sin(g_time) * Math.PI * 2;
}
