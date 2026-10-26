package ActionScript3.Tips 
{
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	public class ItemCompare extends MovieClip 
	{
		public var tF_Damage:TextField;
		public var tF_Life:TextField;
		public function ItemCompare()
		{
			// constructor code
		}
		
		public function SetData(nDamage:int, nLife:int)
		{
			tF_Damage.htmlText = nDamage.toString();
			tF_Life.htmlText = nLife.toString();
		}
		
		public function ReSize(startY:int):int
		{
			y = startY;
			return y + height;
		}
		
	}
	
}
