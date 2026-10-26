package ActionScript3
{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.controls.UILoader;

	import flash.external.ExternalInterface;

	//这里用直接寻址，间接寻址有点怪问题
	public class MyTipButton extends scaleform.clik.controls.RadioButton
	{
		[Inspectable(type = "String",name = "TabType")]
		public var TabType:String = "role0";
		
		public var icon_mc:MovieClip;
		public var tabCaption:String;
		
		override protected function configUI():void 
		{
			//trace("====== MyTipButton configUI");
			
			super.configUI();
			
			//trace("====== MyTipButton configUI 2");
			
			//button的tips先停用
			this.addEventListener( MouseEvent.ROLL_OVER, ShowTips);
			this.addEventListener( MouseEvent.ROLL_OUT, HideTips);
			
			if( icon_mc != null ){
				icon_mc.gotoAndStop(TabType);
			}
		}
		
		/*public function MyTipButton() {
			super();
		}*/
		
		//override public function toString():String {
		//	return "[ MyTipButton " + name + "]";
		//}
		
	/*	override public function stop()
		{
			super.stop();
		}*/
		
		function ShowTips(e:MouseEvent)
		{
			ExternalInterface.call("ASShowTips_Tab", this);
			//this["root"].ChangeTips();
		}
		
		function HideTips(e:MouseEvent)
		{
			ExternalInterface.call("ASHideTips_Tab", this);
			//trace("hidetips");
			//this["root"].tooltips_mc.visible =false;
			
		}
	}

}