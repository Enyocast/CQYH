package ActionScript3.ItemSlot
{
	import flash.display.MovieClip;
	
	public class MyItemSlotComponentQuality extends MyItemSlotComponent
	{
		override public function SetDataObj( data:Object )
		{
			
		}
		
		override public function SetData( inquantity:Number, iniconName:String , initemIndex:int, initemtype:String, initemColor:int, incontainerID:int, inslotID:int )
		{
			trace("setQuality!!");
			switch( initemColor )
			{
				case 0:
				case 1:
				gotoAndStop( "normal" );
				break;
				case 2:
				gotoAndStop( "green" );
				break;
				case 3:
				gotoAndStop( "blue" );
				break;
				case 4:
				gotoAndStop( "purple" );
				break;
				case 5:
				gotoAndStop( "golden" );
				break;
				default:
				gotoAndStop( "normal" );
				break;
			}
			//gotoAndStop( inquantity*10+1 );
		}
	}
}