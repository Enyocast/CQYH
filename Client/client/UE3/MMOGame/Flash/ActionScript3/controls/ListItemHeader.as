package ActionScript3.controls
{
	import scaleform.clik.controls.Button;
	
	public class ListItemHeader extends Button
	{		
		public var _headerIndex:int = 0;
		
		[Inspectable(defaultValue="")]
		public function get headerIndex():int
		{
			return _headerIndex;
		}
		public function set headerIndex(val:int):void
		{
			if(_headerIndex == val)
			{
				return;
			}
			
			_headerIndex = val;
		}

		override protected function configUI():void 
		{
			super.configUI();
		}
	}
}