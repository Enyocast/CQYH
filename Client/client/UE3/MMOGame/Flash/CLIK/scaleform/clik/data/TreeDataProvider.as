/**
 * A data provider for many of the Tree CLIK components, often generated from an Array of data. Provides extra functionality and events for data changes.
 * JimZhang@sdna.com 2013.3.1
 */

package scaleform.clik.data
{

	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import ActionScript3.TreeListData;

	dynamic public class TreeDataProvider extends DataProvider
	{
		private var root:Array = [];
		private var len:uint = 0;
		
		public function TreeDataProvider(source:Array = null)
		{
			super();
			//trace("TreeDataProvider:" + source.length)
			root = source;
			//trace("TreeDataProvider:root" + root.length)
			validateLength();
			//trace("TreeDataProvider:root2" + root.length)
						
			// oscar@snda
			//trace("!!!!===========TreeDataProvider:", root);
			// oscar@snda
		}
		
		public override function toString():String {
            return "[CLIK TreeDataProvider " + this.join(",") + "]";
        }
		
		public function getRoot():Array
		{
			return root;
		}

		override public function get length():uint
		{
			return len;
		}

		override public function requestItemAt(index:uint, callBack:Function=null):Object
		{
			var items:Array = [];
			findObjectByIndex(index,index,items);
			if (callBack != null)
			{
				callBack(items[0]);
			}
			return items[0];
		}

		override public function requestItemRange(startPosition:int, endPosition:int, callBack:Function=null):Array
		{
			// oscar@snda
			//trace("===========TreeDataProvider::requestItemRange:", callBack, startPosition, endPosition, this.length, root);
			// oscar@snda			
			
			var items:Array = [];
			findObjectByIndex(startPosition,endPosition,items);
			
			// oscar@snda
			//trace("===========TreeDataProvider::after findObjectByIndex:");
			// oscar@snda			
			
			if (callBack != null)
			{
				callBack(items);
			}		
			
			// oscar@snda
			//trace("===========TreeDataProvider::requestItemRange:", items);
			// oscar@snda			
			
			return items;
		}

		public function validateLength():void
		{
			len = computeLength(root);
		}

		private function computeLength(ary:Array):uint
		{
			var index:uint = 0;
			var deepth:uint = 0;
			var openFg:Boolean = true;
			for (var i:uint=0; i<ary.length; i++)
			{
				if (ary[i].deepth <= deepth)
				{
					deepth = ary[i].deepth;
					openFg = true;
				}

				if (openFg && ary[i].visible )
				{
					deepth = ary[i].deepth;
					index++;
					if (ary[i].type == TreeListData.C_Type_Branch_Closed)
					{
						openFg = false;
					}
				}
			}
			return index;
		}

		private function findObjectByIndex(indexStart:int, indexEnd:int, outArray:Array)
		{
			// oscar@snda
			//trace("===========TreeDataProvider::findObjectByIndex");
			// oscar@snda			
			
			var index:uint = 0;
			var deepth:uint = 0;
			var openFg:Boolean = true;
			var ary:Array = root;
			for (var i:uint=0; i<ary.length; i++)
			{
				if (ary[i].deepth <= deepth)
				{
					deepth = ary[i].deepth;
					openFg = true;
				}

				if (openFg && ary[i].visible)
				{
					if (index > indexEnd )
					{						
						return;
					}
					
					if (index  >= indexStart)
					{
						outArray.push(ary[i]);
					}
					
					deepth = ary[i].deepth;
					index++;
					if (ary[i].type == TreeListData.C_Type_Branch_Closed)
					{
						openFg = false;
					}
				}
			}
			
			
			
			
			
//			var index:int = 0;
//			var deepth:int = 0;
//			var openFg:Boolean = true;
//			for (var i:int=0; i<root.length; i++)
//			{
//				if (root[i].deepth <= deepth)
//				{
//					deepth = root[i].type;
//					openFg = true;
//				}
//				if (openFg)
//				{
//					if (index > indexEnd)
//					{
//						return;
//					}
//					else if (index >= indexStart)
//					{
//						outArray.push(root[i]);
//					}
//					index++;
//				}
//				if (root[i].type > 1)
//				{
//					deepth = root[i].deepth;
//					openFg = false;
//				}
//
//			}
		}

		public function handleListItemClick( event:ListEvent ):void
		{
			var Obj:Object = requestItemAt(event.index); 
			if (Obj!=null)
			{
				if (Obj.type > TreeListData.C_Type_Leaf)
				{
					if (Obj.type == TreeListData.C_Type_Branch_Closed)
					{
						trace("★★★ handleListItemClick Expand to 2");
						Obj.type = TreeListData.C_Type_Branch_Opened;
					}
					else
					{
						trace("★★★ handleListItemClick Collapse to 1");
						Obj.type = TreeListData.C_Type_Branch_Closed;
					}
					validateLength();
				}
				else
				{
					trace("★★★ handleListItemClick on Leaf");
				}
			}
		}

	}
}