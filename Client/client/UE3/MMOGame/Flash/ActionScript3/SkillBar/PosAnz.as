package ActionScript3.SkillBar
{


	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyActivePanel;
	import ActionScript3.MyMenuSlot;
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.SkillBar.SkillSettingPanel.SkillSettingShortcutPanel;
	import ActionScript3.Slot.MySlot;
	import ActionScript3.Widget.MyTipsText;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;


	public class PosAnz extends Object
	{
		var PosX0:Number;
		var PosX1:Number;
		var PosX2:Number;
		var PosX3:Number;
		var PosX4:Number;
		var PosX5:Number;

		var PosY0:Number;
		var PosY1:Number;
		var PosY2:Number;
		var PosY3:Number;
		var PosY4:Number;
		var PosY5:Number;

		var Object0:MovieClip;
		var Object1:MovieClip;
		var Object2:MovieClip;
		var Object3:MovieClip;
		var Object4:MovieClip;
		var Object5:MovieClip;
		
		public function InitObject(Obj0:MovieClip,Obj1:MovieClip,Obj2:MovieClip,Obj3:MovieClip,Obj4:MovieClip,Obj5:MovieClip):void
		{
			//设计原图格局
			Object0=Obj0;
			Object1=Obj1;
			Object2=Obj2;
			Object3=Obj3;
			Object4=Obj4;
			Object5=Obj5;
			
			PosX0 = Object0.x;
			PosX1 = Object1.x;
			PosX2 = Object2.x;			
			PosX3 = Object3.x;
			PosX4 = Object4.x;
			PosX5 = Object5.x;			
			
			PosY0 = Object0.y;
			PosY1 = Object1.y;
			PosY2 = Object2.y;			
			PosY3 = Object3.y;
			PosY4 = Object4.y;
			PosY5 = Object5.y;			
		}
		
		public function SetCtrlType(type:int):void
		{
			if(type==0)
			{
				Object0.x = PosX0;
				Object0.y = PosY0;				
				Object1.x = PosX1;
				Object1.y = PosY1;				
				Object2.x = PosX2;
				Object2.y = PosY2;				
				Object3.x = PosX3;
				Object3.y = PosY3;				
				Object4.x = PosX4;
				Object4.y = PosY4;				
				Object5.x = PosX5;
				Object5.y = PosY5;								
			}
			else
			{
				Object0.x = PosX1;
				Object0.y = PosY1;				
				Object1.x = PosX2;
				Object1.y = PosY2;				
				Object2.x = PosX3;
				Object2.y = PosY3;				
				Object3.x = PosX4;
				Object3.y = PosY4;				
				Object4.x = PosX5;
				Object4.y = PosY5;				
				Object5.x = PosX0;
				Object5.y = PosY0;												
			}
			
		}
	}
}


