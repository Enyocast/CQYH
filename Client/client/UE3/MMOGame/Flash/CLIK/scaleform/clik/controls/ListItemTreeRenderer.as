/**
 * 
 * JimZhang@sdna.com 2013.3.1
 */

package scaleform.clik.controls
{

	import flash.events.FocusEvent;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.ListData;
	
	public class ListItemTreeRenderer extends ListItemRenderer
	{
		public var updateDataCallBack:Function = null;
		// Initialization:
		public function ListItemTreeRenderer()
		{
			super();
		}

		// Public Methods:
		override public function setData(data:Object):void
		{
			// oscar@snda
			//trace("===========ListItemTreeRenderer::setData:", data, updateDataCallBack);
			// oscar@snda
				
			this.data = data;
			if (updateDataCallBack != null)
			{
				updateDataCallBack(this.data);
			}
		}

		public function setUpdateDataCallBack(callBack:Function=null)
		{
			updateDataCallBack = callBack;
		}

	}
}