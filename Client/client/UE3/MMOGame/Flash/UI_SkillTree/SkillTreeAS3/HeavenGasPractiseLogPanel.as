package UI_SkillTree.SkillTreeAS3
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataBinding;
	import scaleform.clik.controls.Button;


	public class HeavenGasPractiseLogPanel extends UIComponent
	{
		public var logInfo_tf:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function UpdateHeavenLog(data:Array):void
		{
			logInfo_tf.text = String("");
			var strInfo:String = String("");
			
			var nFirst:int = 0;
			if(data.length > 11)
				nFirst = data.length - 11;
			for(var i:int = nFirst; i < data.length; ++i)
			{
				var str:String = data[i] as String;
				strInfo += str;
				strInfo += "\n";
			}
			logInfo_tf.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
			logInfo_tf.wordWrap 	= 			true;
			logInfo_tf.htmlText 	= 			strInfo;
			logInfo_tf.height 		= 			logInfo_tf.textHeight;
		}
	}
}