package UI_CharactorWidget.CharactorWidgetAS3 {
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import scaleform.gfx.Extensions;
	
	
	public class ListItemRenderer_Relation1st extends MovieClip {
		
		public var titleName:TextField;
        public var lastType:Number = -1;
        //public var sign_mc:MovieClip;
		public function ListItemRenderer_Relation1st() {
			// constructor code
		}
		public function updateData(data:Object):void
        {
				if (data && data.deepth ==0)
				{
					 visible = true;
		             titleName.text = data.label;
				}else{
					visible = false;
				}

        }
		
		public function playSound(soundEventName:String, soundTheme:String = ""):void {        
		    if (Extensions.gfxProcessSound == null) { return; }
            if (soundTheme == "") { soundTheme = "default"; }	    	    
		    Extensions.gfxProcessSound(this, soundTheme, soundEventName);
        }
	}
	
}
