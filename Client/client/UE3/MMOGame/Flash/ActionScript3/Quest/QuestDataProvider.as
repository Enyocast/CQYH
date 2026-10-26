/**
 * A data provider for many of the Tree CLIK components, often generated from an Array of data. Provides extra functionality and events for data changes.
 * JimZhang@sdna.com 2013.3.1
 */

package ActionScript3.Quest
{

	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import flash.external.ExternalInterface;

	dynamic public class QuestDataProvider extends DataProvider
	{
		private var root:Array = [];
		private var len:uint = 0;
		
		public function QuestDataProvider(source:Array = null):void
		{
			super();
			root = source;
			validateLength();
		}
		
		public override function toString():String {
            return "[CLIK QuestDataProvider " + this.join(",") + "]";
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
			var items:Array = [];
			findObjectByIndex(startPosition,endPosition,items);
			if (callBack != null)
			{
				callBack(items);
			}		
			return items;
		}

		public function validateLength():void
		{
			len = computeLength(root);
		}

		private function computeLength(ary:Array):uint
		{
			var index:uint = 0;
			var addToLen:Boolean = false;
			var ary:Array = root;
			
			for (var i:uint = 0; i < ary.length; ++i)
			{
				// 如果有ItemGroup展开时，将其后面的数据也一同显示，直到遇到下一个ItemGroup再判定
				var dat:QuestData = ary[i] as QuestData;
				if(dat.quest_item_type == QuestData.quest_item_type_group && dat.quest_is_expanded)
				{
					addToLen = true;
					++index;
				}
				else
				{
					addToLen = false;
					++index;
				}
				
				if(dat.quest_item_type == QuestData.quest_item_type_item && addToLen)
				{
					++index;
				}
			}
			return index;
		}

		private function findObjectByIndex(indexStart:int, indexEnd:int, outArray:Array):void
		{
			var index:uint = 0;
			var addToLen:Boolean = false;
			var ary:Array = root;
			
			for (var i:uint = 0; i < ary.length; ++i)
			{
				var dat:QuestData = ary[i] as QuestData;				
					
				// 如果有ItemGroup展开时，将其后面的数据也一同显示，直到遇到下一个ItemGroup再判定
				
				if(dat.quest_item_type == QuestData.quest_item_type_group)
				{
					if(index >= indexStart && index <= indexEnd)
					{
						outArray.push(dat);
					}
					addToLen = dat.quest_is_expanded;
					
					++index;
				}
				
				if(addToLen && dat.quest_item_type == QuestData.quest_item_type_item)
				{
					if(index >= indexStart && index <= indexEnd)
					{
						outArray.push(dat);
					}
					
					++index;
				}
				
				if(index > indexEnd)
				{
					return;
				}
			}
		}
	}
}