package ActionScript3.Common.DynamicComponent
{
	import flash.display.DisplayObject;
	import flash.utils.Dictionary;
	/**
	 *  动态创建组件的通用入口，缓存创建的对象，不再重复创建和销毁，减少垃圾回收次数。
	 * @author wangpenghe.phil
	 * 
	 */	
	public class DynamicComponentFactory
	{
		private static var _instance:DynamicComponentFactory;
		private var _poolDic:Dictionary;
		
		public function DynamicComponentFactory()
		{
			_poolDic = new Dictionary();
		}
		
		public static function getInstance():DynamicComponentFactory
		{
			if(_instance == null)
			{
				_instance = new DynamicComponentFactory();
			}
			return _instance;
		}
		
		public function getComponentByClassName(className:String):Object
		{
			if(_poolDic[className] == null)
			{
				_poolDic[className] = new DynamicComponentPool(className);
			}
			return _poolDic[className].getFreeComponent();
		}
		
		public function releaseUsedComponent(instance:Object):void
		{
			var targetPool:DynamicComponentPool = instance["pool"] as DynamicComponentPool;
			if(targetPool != null)
			{
				targetPool.releaseUsedComponent(instance);
			}
			else
			{
				trace("[ERROR] The component is not belong to any pool.");
			}
		}
		
		public function disposePool(className:String):void
		{
			var pool:DynamicComponentPool = _poolDic[className] as DynamicComponentPool;
			if(pool != null)
			{
				pool.destroy();
				pool = _poolDic[className] = null;
				delete _poolDic[className];
			}
		}
	}
}