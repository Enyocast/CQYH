package ActionScript3
{
	import scaleform.clik.core.UIComponent;
	
	public class ExpandIcon extends UIComponent
	{		
		protected var _isExpanded:Boolean = false;
		
		public function ExpandIcon()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			invalidateData();
		}
		
		[Inspectable(defaultValue="")]
		public function get isExpanded():Boolean
		{
			return _isExpanded;
		}
		public function set isExpanded(val:Boolean):void
		{
			if(_isExpanded == val)
			{
				return;
			}
			
			_isExpanded = val;
			invalidateData();
		}
		
		public override function invalidateData():void
		{
			super.invalidateData();
			
			if(_isExpanded)
			{
				this.gotoAndPlay("collapse");
			}
			else
			{
				gotoAndPlay("expand");
			}
		}
	}
	
}
