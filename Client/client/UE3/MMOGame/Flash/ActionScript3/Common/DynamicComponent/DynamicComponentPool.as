package ActionScript3.Common.DynamicComponent
{
	import flash.display.DisplayObject;
	import flash.utils.getDefinitionByName;

	public class DynamicComponentPool
	{
		private var _className:String;
		private var _protype:Class;
		private var _allComponent:Array;
		private var _freeCompsBox:Array
		
		public function DynamicComponentPool(className:String)
		{
			_className 		= className;
			_protype 		= getDefinitionByName(className) as Class;
			_allComponent 	= [];
			_freeCompsBox 	= [];
		}
		
		public function getFreeComponent():Object
		{
			var comp:Object;
			if(_freeCompsBox.length == 0)
			{
				//create new component;
				comp = new _protype;
				comp['pool'] = this;
				_allComponent.push(comp);
			}
			else
			{
				//the last component in the box
				comp = _freeCompsBox.pop();
			}
			return comp;
		}
		
		public function releaseUsedComponent(comp:Object):void
		{
			if(_allComponent.indexOf(comp) != -1 && _freeCompsBox.indexOf(comp)== -1)
			{
				_freeCompsBox.push(comp);
			}
		}
		
		public function destroy():void
		{
			_freeCompsBox.length = 0;
			_freeCompsBox = null;
			var len:int = _allComponent.length;
			var doComp:DisplayObject;
			for(var i:int = 0; i < len; ++i)
			{
				if(_allComponent[i] is DisplayObject)
				{
					doComp = _allComponent[i] as DisplayObject;
					if(doComp.parent)
					{
						doComp.parent.removeChild(doComp);
						doComp = null;
					}
				}
				_allComponent[i] = null;
			}
			_allComponent.length = 0;
			_allComponent = null;
			_protype = null;
		}
	}
}