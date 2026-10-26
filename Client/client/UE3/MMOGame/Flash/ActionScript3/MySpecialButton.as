//package ActionScript3
//{
//	import scaleform.clik.controls.Button;
//	import flash.external.ExternalInterface;
//	import flash.text.TextField;
//	import flash.display.MovieClip;
//	
//	public class MySpecialButton extends Button
//	{
//		
//		//
//		[Inspectable(defaultValue="0")]
//		public function get CurSeriesIdx():int {
//            return 1;
//        }
//		public function set CurSeriesIdx( idx:int ):void {
//            
//        }
//	}
//}

package ActionScript3
{
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.display.DisplayObject;

	public class MySpecialButton extends Button
	{
		protected var _effectObject:MovieClip;
		
		[Inspectable(type = "String")]
		public function get effectObject():Object
		{
			return _effectObject as Object;
		}
		public function set effectObject(value:Object):void
		{
			if (value is String)
			{
				if (parent != null)
				{
					_effectObject = parent.getChildByName(value.toString()) as MovieClip;
				}
			}
		}
		
		override protected function setState(state:String):void {
            _state = state;
			
			
            var prefixes:Vector.<String> = getStatePrefixes();
            var states:Array = _stateMap[state];
            if (states == null || states.length == 0) { return; }
            var l:uint = prefixes.length;
            for (var i:uint=0; i<l; i++) {
                var prefix:String = prefixes[i];
                var sl:uint = states.length;
                for (var j:uint=0; j<sl; j++) {
                    var thisLabel:String = prefix + states[j];
                    if (_labelHash[thisLabel]) {
                        _newFrame = thisLabel;
						if(_effectObject)
						{
							_effectObject.gotoAndPlay(_newFrame);
						}
                        super.invalidateState();
                        return;
                    }
                }
            }
        }
	}
}