package ActionScript3 {
	
import flash.display.MovieClip;
	


	public class MyDictionary
	{
		public var _valueArray:Array;
		public var _keyArray:Array;
		public var _value:Object;
		
		public function MyDictionary() {
            _valueArray = new Array; // 
			_keyArray = new Array;
			_value = null;
        }
		
		public function setValue( key:int, value:Object ):void 
		{
			/*_valueArray.splice( 0 );
			_keyArray.splice( 0 );
			
			_valueArray.push( value );
			_keyArray.push( key );*/
			_value = value;
		}
		
		public function getValue( key:Object ):Object 
		{
			return _value;
		}

		//public var bNeedVisible:Boolean = false;

		//public var IconUILoader:UILoader;
	}
}