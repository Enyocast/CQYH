package ActionScript3.Common
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.utils.getDefinitionByName;
	
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.interfaces.IDataProvider;
	import scaleform.clik.interfaces.IListItemRenderer;
	import scaleform.gfx.MouseEventEx;
	
	/**
	 * Implement Grid list, base on CoreList
	 * @author wangpenghe.phil
	 * 
	 */	
	public class ItemGrid extends UIComponent
	{
		//First item start position x
		protected var _startPosX:Number = 0;
		//First item start position y
		protected var _startPosY:Number = 0;
		//Vetical number of Items
		protected var _numV:Number = 1; 
		//Horizonal number of Items
		protected var _numH:Number = 1; 
		//Vetical offset between Items
		protected var _marginV:Number = 0; 
		//Horizonal offset between Items
		protected var _marginH:Number = 0; 
		//The index of selected item in the group
		protected var _selectedIndex:Number = -1; 
		// The latest internal selectedIndex. Will be pushed to _selectedIndex next time updateSelectedIndex() is called.
		protected var _newSelectedIndex:int = -1; 
		//The renderer of grid item
		protected var _gridItemRenderer:String;
		//itemRenderer must implement IListItemRenderer
		protected var _itemRenderer:Class;
		// The dataProvider for the List.
		protected var _dataProvider:IDataProvider;
		
		protected var _data:Array;
		protected var _itemRendererGroup:Vector.<ListItemRenderer>;
		
		public var frame_mc:MovieClip;
		
		public function ItemGrid()
		{
			super();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
		}
		
		public function setData(data:Array):void
		{
			_data = data;
			if(_data == null)
			{
				visible = false;
				return;
			}

			visible = true;
			var dataLen:int = _data.length;
			validItemRendererInstance(dataLen);
			if(dataLen > 0)
			{
				var offsetH:Number = _marginH + _itemRendererGroup[0].width;
				var offsetV:Number = _marginV + _itemRendererGroup[0].height;
								
				for(var i:int = 0; i < dataLen; i++)
				{
					_itemRendererGroup[i].setData(_data[i]);
					_itemRendererGroup[i].visible = true;
					_itemRendererGroup[i].x = _startPosX + offsetH * int(i % numH);
					_itemRendererGroup[i].y = _startPosY + offsetV * int(i / numH);
				}
				_width = frame_mc.width = startPosX + offsetH * numH - _marginH;
				_height = frame_mc.height = startPosY + offsetV * Math.ceil(dataLen / numH) - _marginV;	//the end of last item without margin
			}
			invalidateSize();
		}
		
		private function validItemRendererInstance(dataLen:int):void
		{
			if(_itemRendererGroup == null){
				_itemRendererGroup = new Vector.<ListItemRenderer>();
			}
			var numOfGroup:int = _itemRendererGroup.length;
			if(numOfGroup < dataLen)
			{
				_itemRendererGroup.length = numOfGroup;
				for(var i:int = numOfGroup; i < dataLen; i++)
				{
					_itemRendererGroup[i] = new itemRenderer;
					_itemRendererGroup[i].index = i;
					setupRenderer(_itemRendererGroup[i]);
					addChild(_itemRendererGroup[i]);
				}
			}
			else if(numOfGroup > dataLen)
			{
				for(i = dataLen; i < numOfGroup; i++)
				{
					_itemRendererGroup[i].visible = false;
				}
			}
		}
		
		protected function setupRenderer(renderer:IListItemRenderer):void {
		//	renderer.owner = this;
		//	renderer.focusTarget = this;
		//	renderer.tabEnabled = false; // Children can still be tabEnabled, or the renderer could re-enable this. //LM: There is an issue with this. Setting disabled could automatically re-enable. Consider alternatives. 
		//	renderer.doubleClickEnabled = true;
			renderer.addEventListener(ButtonEvent.CLICK, handleItemClick, false, 0, true);
			renderer.validateNow();
		}
		
		protected function handleItemClick(event:ButtonEvent):void {
			var index:Number = (event.currentTarget as IListItemRenderer).index;
			if (isNaN(index)) { return; } // If the data has not been populated, but the listItemRenderer is clicked, it will have no index.
			if (dispatchItemEvent(event)) {
				selectedIndex = index;
			}
		}
		
		//only activeated ButtonEvent.CLICK now
		protected function dispatchItemEvent(event:Event):Boolean {
			var type:String;
			switch (event.type) {
				case ButtonEvent.PRESS:
					type = ListEvent.ITEM_PRESS; 
					break;
				case ButtonEvent.CLICK:
					type = ListEvent.ITEM_CLICK; 
					break;
				case MouseEvent.ROLL_OVER:
					type = ListEvent.ITEM_ROLL_OVER;
					break;
				case MouseEvent.ROLL_OUT:
					type = ListEvent.ITEM_ROLL_OUT; 
					break;
				case MouseEvent.DOUBLE_CLICK:
					type = ListEvent.ITEM_DOUBLE_CLICK; 
					break;
				default:
					return true;
			}
			
			var renderer:IListItemRenderer = event.currentTarget as IListItemRenderer;
			
			// Propogate the controller / mouse index.
			var controllerIdx:uint = 0;
			if (event is ButtonEvent) { controllerIdx = (event as ButtonEvent).controllerIdx; }
			else if (event is MouseEventEx) { controllerIdx = (event as MouseEventEx).mouseIdx; }
			
			var buttonIdx:uint = 0;
			if (event is ButtonEvent) { buttonIdx = (event as ButtonEvent).buttonIdx; }
			else if (event is MouseEventEx) { buttonIdx = (event as MouseEventEx).buttonIdx; }
			
			// Propogate whether the keyboard / gamepad generated this event.
			var isKeyboard:Boolean = false;
			if (event is ButtonEvent) { isKeyboard = (event as ButtonEvent).isKeyboard; }
			
			//var newEvent:ListEvent = new ListEvent(type, false, true, renderer.index, 0, renderer.index, renderer, dataProvider[renderer.index], controllerIdx, buttonIdx, isKeyboard);
			var newEvent:ListEvent = new ListEvent(type, false, true, renderer.index, 0, renderer.index, renderer, _data[renderer.index], controllerIdx, buttonIdx, isKeyboard);
			return dispatchEvent(newEvent);
		}

		[Inspectable(type="String", name="gridItemRenderer")]
		public function get gridItemRenderer():String
		{
			return _gridItemRenderer;
		}

		public function set gridItemRenderer(value:String):void
		{
			_gridItemRenderer = value;
			
			if ((_inspector && value == "") || value == "") { return; }
			var classRef:Class = getDefinitionByName(value) as Class;
			if (classRef != null) {
				itemRenderer = classRef;
			} else {
				trace("Error: " + this + ", The class " + value + " cannot be found in your library. Please ensure it is there.");
			}
		}
	
		/** Set the itemRenderer class. */
		public function get itemRenderer():Class { return _itemRenderer; }
		public function set itemRenderer(value:Class):void {
			_itemRenderer = value;
			invalidateRenderers();
		}
		
		/** Mark the item renderers as invalid and schedule a draw() on next Stage.INVALIDATE event. */
		public function invalidateRenderers():void {
			invalidate(InvalidationType.RENDERERS);
		}

		[Inspectable(type="Number", defaultValue="-1", name="selectedIndex")]
		public function get selectedIndex():Number
		{
			return _selectedIndex;
		}

		public function set selectedIndex(value:Number):void
		{
			if (value == _selectedIndex || value == _newSelectedIndex)
			{
				return;
			}
			_newSelectedIndex = value;
			invalidateSelectedIndex();
		}
		
		/** Mark the selectedIndex as invalid and schedule a draw() on next Stage.INVALIDATE event. */
		public function invalidateSelectedIndex():void {
			invalidate(InvalidationType.SELECTED_INDEX);
		}
		
		override protected function draw():void
		{
			super.draw();
			if (isInvalid(InvalidationType.SELECTED_INDEX)) {
				updateSelectedIndex();
			}
			
			if (isInvalid(InvalidationType.DATA)) {
				refreshData(); // Renderers get invalidated here.
				//TODO: For variable-height, we would reflow at this point.
			}
		}
		
		protected function updateSelectedIndex():void
		{
			if (_selectedIndex == _newSelectedIndex)
			{
				return;
			}
			if(_data == null)//when the selectedIndex set in fla file
			{
				return;
			}
			var renderer:IListItemRenderer = getRendererAt(_selectedIndex);
			if (renderer != null)
			{
				renderer.selected = false;// Only reset items in range
				renderer.validateNow();
			}
			
			_selectedIndex = _newSelectedIndex;// Reset the new selected index value if we found a renderer instance
			if (_selectedIndex < 0 ||　_selectedIndex >= _data.length)
			{
				return;
			}
			
			renderer = getRendererAt(_selectedIndex);
			if (renderer != null)
			{
				renderer.selected = true;// Item is in range. Just set it.
				renderer.validateNow();
			}
		}
		
		protected function refreshData():void
		{
			updateSelectedIndex();
			//_dataProvider.requestItemRange(GetPosIndex(_scrollPosition), Math.min(_dataProvider.length - 1, GetPosIndex(_scrollPosition) + _totalRenderers - 1), populateData);
		}

		/** 
		 * Retrieve a reference to an IListItemRenderer of the List.
		 * @param index The index of the renderer.
		 * @param offset An offset from the original scrollPosition (normally, the scrollPosition itself).
		 */
		public function getRendererAt(index:uint, offset:int=0):ListItemRenderer {
			if (_itemRendererGroup == null) { return null; }
			var newIndex:uint = index - offset;
			if (newIndex < 0 ||　newIndex >= _itemRendererGroup.length) { return null; }
			return _itemRendererGroup[newIndex];
		}
		
		[Inspectable(type="Number", defaultValue="0", name="startPosX")]
		public function get startPosX():Number
		{
			return _startPosX;
		}
		
		public function set startPosX(value:Number):void
		{
			_startPosX = value;
		}
		
		[Inspectable(type="Number", defaultValue="0", name="startPosY")]
		public function get startPosY():Number
		{
			return _startPosY;
		}
		
		public function set startPosY(value:Number):void
		{
			_startPosY = value;
		}

		[Inspectable(type="Number", defaultValue="1", name="marginV")]
		public function get marginV():Number
		{
			return _marginV;
		}

		public function set marginV(value:Number):void
		{
			_marginV = value;
		}

		[Inspectable(type="Number", defaultValue="1", name="marginH")]
		public function get marginH():Number
		{
			return _marginH;
		}

		public function set marginH(value:Number):void
		{
			_marginH = value;
		}
		[Inspectable(type="Number", defaultValue="0", name="numH")]
		public function get numH():Number
		{
			return _numH;
		}

		public function set numH(value:Number):void
		{
			_numH = value;
		}

		[Inspectable(type="Number", defaultValue="0", name="numV")]
		public function get numV():Number
		{
			return _numV;
		}

		public function set numV(value:Number):void
		{
			_numV = value;
		}


	}
}