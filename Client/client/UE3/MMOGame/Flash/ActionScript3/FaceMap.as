package ActionScript3 {
	
	

	public class FaceMap
	{
		static public var faceMap:Array;
		static var mapText:String ;
		static var enableUse:Boolean = false;
		
		static public function enable():void
		{
			mapText = "#am,#bs,#dj,#zh,#dx,#gx,#hx,#jy,#ka,#ks,#kz,#ku,#ld,#lh,#ll,#lc,#qiang,#sq,#sl,#sj";
			faceMap = mapText.split(",");
			
			enableUse = true;
		}
		
		static public function getFaceMapCount() : int
		{
			if(!enableUse)
			{
				enable();
			}
			return faceMap.length;
		}

		 static public function getFaceString( id:int ) : String 
		 { 		 	
			if(!enableUse)
			{
				enable();
			}
			//trace("!!!"+faceMap.length);
			
			 if( faceMap.length > id )
			 {
				
				return faceMap[id];
			 }
			 else
			 {
				 return "";
			 }
		 }
		
		 
		
	}
	

}