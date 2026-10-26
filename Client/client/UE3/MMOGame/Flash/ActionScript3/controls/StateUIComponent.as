
package ActionScript3.controls
{
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;

	public class StateUIComponent extends UIComponent
	{
		protected var _selected:Boolean = false;
		protected var _mouseOver:Boolean = false;
		protected var _mouseDown:Boolean = false;

		/** Reference to the UIComponent that generated this Button, if applicatable (eg. ButtonGroup). */
		protected var _owner:UIComponent = null;


		/** Reference to the owner of this Button (generally, a subclass of CoreList). */
		public function get owner():UIComponent
		{
			return _owner;
		}
		public function set owner(value:UIComponent):void
		{
			_owner = value;
		}

		public function get selected():Boolean
		{
			return _selected;
		}

		public function set selected(value:Boolean):void
		{
			if (_selected == value)
			{
				return;
			}

			_selected = value;
			updateState();
		}

		public function updateState():void
		{
			var typeStr:String = "";
			var typeState:String = "";
			
			if (_mouseOver)
			{
				typeState = "over";
			}
			else
			{
				typeState = "up";
			}

			if (_mouseDown)
			{
				typeState = "down";
			}

			if (_selected)
			{
				typeStr = "selected_";
			}
			
			gotoAndPlay(typeStr + typeState);
		}

		override public function toString():String
		{
			return "[StateUIComponent " + name + "]";
		}

		// Protected Methods:
		override protected function configUI():void
		{

			super.configUI();

			addEventListener(MouseEvent.ROLL_OVER, onRollOver);
			addEventListener(MouseEvent.ROLL_OUT, onRollOut);
			addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
		}

		function onMouseDown(e:MouseEvent)
		{
			_mouseDown = true;
			updateState();
		}

		function onMouseUp(e:MouseEvent)
		{
			_mouseDown = false;
			updateState();
		}

		function onRollOver()
		{
			_mouseOver = true;
			updateState();
		}

		function onRollOut()
		{
			_mouseOver = false;
			updateState();
		}

	}
}