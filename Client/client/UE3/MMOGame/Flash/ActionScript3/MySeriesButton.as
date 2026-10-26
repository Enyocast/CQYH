package ActionScript3
{
	import scaleform.clik.controls.Button;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.display.MovieClip;
	
	public class MySeriesButton extends Button
	{
		var _CurSeriesIdx:int;
		public var numTF:TextField;
		public var msgNumBg:MovieClip;

        override protected function getStatePrefixes():Vector.<String> {
			var prefixesResult:Vector.<String> = new Vector.<String>;
			
			var prefixes:Vector.<String> = super.getStatePrefixes();
            var l:uint = prefixes.length;
			
            for (var i:uint=0; i<l; i++) {
                prefixesResult.push( ( CurSeriesIdx > 0 ? CurSeriesIdx : "" ) + prefixes[i] );
            }
			
			return ( l > 0 ? prefixesResult : prefixes );
        }
		
		//
		[Inspectable(defaultValue="0")]
		public function get CurSeriesIdx():int {
            return _CurSeriesIdx;
        }
		public function set CurSeriesIdx( idx:int ):void {
            _CurSeriesIdx = idx;
			var initState = "up";

            setState(initState);
			//ExternalInterface.call( "ASTrace" , initState );
        }
	}
}