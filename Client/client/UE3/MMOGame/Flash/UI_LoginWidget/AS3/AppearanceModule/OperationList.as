package UI_LoginWidget.AS3.AppearanceModule
{
	import flash.display.MovieClip;
	import flash.geom.Rectangle;
	
	import scaleform.clik.core.UIComponent;
	
	public class OperationList extends UIComponent
	{
		public var frame_mc:MovieClip;
		private var _itemGroup:Vector.<ItemGroup_Appearance>;
		private var _numOfGroup:int;
		
		private var _focusRect:Rectangle = new Rectangle();
		
		public function OperationList()
		{
			super();
		}

		override protected function configUI():void
		{
			super.configUI();
		}
		
		internal function resetPosition(foucusIndex:int = 0):void
		{
			var posY:Number = 0;
			for(var i:int = 0; i < _numOfGroup; i++)
			{
				if(i != foucusIndex){
					_itemGroup[i].activated = false;
				}
				_itemGroup[i].y = posY;
				_itemGroup[i].index = i;
				posY += _itemGroup[i].height;
			}
			frame_mc.height 	=  height = posY;
			_focusRect.y 		= _itemGroup[foucusIndex].y;
			_focusRect.height 	= _itemGroup[foucusIndex].height;
			//item will auto fold if deactivated, grid list can show enough after expand, no need set focus area now.
			(parent as OperationPanel).updateScrollingView();
		}
		
		public function resetData():void
		{
			for(var i:int = 0; i < _numOfGroup; i++)
			{
				_itemGroup[i].resetData();
			}
		}
		
		public function getRandomResult():Array
		{
			var listResult:Array = [];
			for(var i:int = 0; i < _numOfGroup; i++)
			{
				listResult.push(_itemGroup[i].getRandomResult());
			}
			return listResult;
		}
		
		internal function updateData($data:Array):void
		{
			if($data == null){
				visible = false;
				frame_mc.height =  height = 0;
				(parent as OperationPanel).updateScrollingView();
				return;
			}
			visible = true;
			var posY:Number = 0;
			var dataLen:int = _numOfGroup = $data.length;
			validItemGroupInstance(dataLen);
			var groupData:GroupData_Appearance;
			
			for(var i:int = 0; i < dataLen; i++)
			{
				groupData = $data[i] as GroupData_Appearance;
				//just activate the first item group
				_itemGroup[i].updateData(groupData);
				_itemGroup[i].y = posY;
				_itemGroup[i].index = i;
				_itemGroup[i].activated = (i == 0);
				posY += _itemGroup[i].height;
			}
			frame_mc.height =  height = posY;
			_focusRect.y 		= _itemGroup[0].y;
			_focusRect.height 	= _itemGroup[0].height;
			(parent as OperationPanel).updateScrollingView();
		}
		
		private function validItemGroupInstance(dataLen:int):void
		{
			if(_itemGroup == null){
				_itemGroup = new Vector.<ItemGroup_Appearance>();
			}
			var numOfGroup:int = _itemGroup.length;
			if(numOfGroup < dataLen){
				_itemGroup.length = numOfGroup;
				for(var i:int = numOfGroup; i < dataLen; i++)
				{
					_itemGroup[i] = new ItemGroup_Appearance();
					_itemGroup[i].validateNow();//configUI
					addChild(_itemGroup[i]);
				}
			}else if(numOfGroup > dataLen){
				for(i = dataLen; i < numOfGroup; i++)
				{
					_itemGroup[i].visible = false;
				}
			}
		}
	}
}