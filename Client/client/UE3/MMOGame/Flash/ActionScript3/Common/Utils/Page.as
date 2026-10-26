package ActionScript3.Common.Utils
{
	public class Page
	{
		public var _datas:Array;
		private var _totalCount:int=-1;
		
		public var _pageNo:int=1;
		public var _pageSize:int=1;
		
		public function Page(pageSize:int,datas:Array=null)
		{
			this._pageSize=pageSize;
			this._datas=datas;
		}
		
		public function get totalCount():int
		{
			return _totalCount;
		}

		public function set totalCount(value:int):void
		{
			_totalCount = value;
		}

		public function get PageNo():int
		{
			return this._pageNo;
		}
		
		public function get PageSize():int
		{
			return this._pageSize;
		}
		
		public function getPageFirst():int
		{
			return (this._pageNo-1)*_pageSize;
		}
		
		public function getPageData(value:int):Array
		{
			PageNo=value;
			var start:int=this.getPageFirst();
			var end:int=value==this.getTotalPages()?-1:start+_pageSize;
			return end==-1?_datas.slice(start):_datas.slice(start,end);
		}
		
		public function getLastPageSize():int
		{
			var num:int=_totalCount%_pageSize;
			return num==0?_pageSize:num;
		}
		
		public function set datas(value:Array):void
		{
			this._datas=value;
			_datas==null?_totalCount=-1:_totalCount=_datas.length;
		}
		
		public function set PageNo(value:int):void
		{
			this._pageNo=value;
			value<1?_pageNo==1:_pageNo=value;
		}
		
		public function getTotalPages():int
		{
			if(_totalCount<0){
				return -1;
			}
			var count:int=_totalCount/_pageSize;
			if(_totalCount%_pageSize>0){
				count++;
			}
			return count;
			
		}
		
		public function hasPre():Boolean
		{
			return ((_pageNo-1)>=1);
		}
		
		public function hasNext():Boolean
		{
			return ((_pageNo+1)>=1);
		}
		public function reset():void
		{
			this._datas=null;
			this._totalCount=-1;
			this._pageNo=1;
		}
	}
}