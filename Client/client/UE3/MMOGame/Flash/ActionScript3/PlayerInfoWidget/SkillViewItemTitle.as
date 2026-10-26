package ActionScript3.PlayerInfoWidget
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import scaleform.clik.core.UIComponent;
	
	
	public class SkillViewItemTitle extends UIComponent
	{
		private const KEY_NAME_MOUSE_LEFT:String = "左";
		private const KEY_NAME_MOUSE_RIGHT:String = "右";
		
		private const KEYFRAME_LABEL_TYPE_SMALL:String = "type_small";
		private const KEYFRAME_LABEL_TYPE_BIG:String   = "type_big";
		private var _viewType:String;
		
		public var KeyTypeMc:MovieClip;
		public var KeyTypeTf:TextField;
		public var KeyTypeTf_change:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
		}

		function UpdateData(keyType:int, keyTypeString:String, isBigType:Boolean ):void
		{
			updateViewType(isBigType ? KEYFRAME_LABEL_TYPE_BIG :KEYFRAME_LABEL_TYPE_SMALL);
			if(keyTypeString == null){
				keyTypeString = "";
			}
			if(keyTypeString == KEY_NAME_MOUSE_LEFT){
				KeyTypeMc.visible = true;
				KeyTypeTf_change.visible = false;
				KeyTypeMc.gotoAndStop( 0 * 10 + 1 );
			}
			else if(keyTypeString == KEY_NAME_MOUSE_RIGHT){
				KeyTypeMc.visible = true;
				KeyTypeTf_change.visible = false;
				KeyTypeMc.gotoAndStop( 1 * 10 + 1 );
			}
			else{
				KeyTypeMc.visible = false; 
				KeyTypeTf_change.visible = true;
				KeyTypeTf_change.text = keyTypeString;
			}
		}
		
		private function updateViewType(viewType:String):void
		{
			if(_viewType != viewType){
				_viewType = viewType;
				gotoAndStop(_viewType);
			}
		}
	}
}