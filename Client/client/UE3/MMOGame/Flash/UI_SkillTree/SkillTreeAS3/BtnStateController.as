
package UI_SkillTree.SkillTreeAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;

	public class BtnStateController extends UIComponent
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

		public function updateState()
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
			
			trace("---------updateState", typeStr, typeState);
		}

		override public function toString():String
		{
			return "[StateUIComponent " + name + "]";
		}

		// Protected Methods:
		override protected function configUI():void
		{

			super.configUI();
		}


		public function onThisMouseDown(e:MouseEvent)
		{
			_mouseDown = true;
			updateState();
		}

		public function onThisMouseUp(e:MouseEvent)
		{
			_mouseDown = false;
			updateState();
		}

		public function onThisRollOver()
		{
			_mouseOver = true;
			updateState();
		}

		public function onThisRollOut()
		{
			_mouseOver = false;
			updateState();
		}

	}
}