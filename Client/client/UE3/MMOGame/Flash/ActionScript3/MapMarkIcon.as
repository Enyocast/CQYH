package ActionScript3
{
	import flash.display.MovieClip;
	import UI_Minimap.MinimapAS3.MapConst;
	import flash.text.TextField;
	import flash.text.TextFormat;

	public class MapMarkIcon extends MovieClip
	{
		public var quest_mark_twinkle_mc:MovieClip;
		public var Type:int = 0;
		public var ID:int = 0;
		public var frameName:String;
		
		private static const FRAME_OF_TWINKLE_TYPE:Array = ['taskStart'];
		
		public function InitType( id:int, type:int, _frameName:String,fontSize:uint=16):void
		{
			ID = id;
			Type = type;
			frameName=_frameName;
			if(type==MapConst.NavPoint)
			{
				this.gotoAndStop("NavPoint");
				this.mouseChildren=false;
				this.mouseEnabled=false;
				var txt:TextField=this.getChildByName("txt_dec") as TextField;
				if(txt)
				{
					if(fontSize!=14)
					{
						var size:int=int(_frameName.substr(0,1));
					    if(size==1)
					    {
						   fontSize=14;
					    }else if(size==2){
						   fontSize=16;
					    }else{
						   fontSize=18;
					    }
					}
					_frameName=_frameName.substring(1,_frameName.length);
					var format:TextFormat=txt.defaultTextFormat;
					format.letterSpacing=-2;
					format.size=fontSize;
					txt.setTextFormat(format);
					txt.text=_frameName;
				}
			}
			else if(type==MapConst.QuestZone)
			{
				this.mouseChildren=true;
				this.mouseEnabled=true;
				this.gotoAndStop("questZone");
			}
			else
			{
				this.mouseChildren=true;
				this.mouseEnabled=true;
				this.gotoAndStop( frameName );
			}
			if(FRAME_OF_TWINKLE_TYPE.indexOf(frameName) != -1)
			{
				quest_mark_twinkle_mc.mouseEnabled=false;
				quest_mark_twinkle_mc.mouseChildren=false;
				quest_mark_twinkle_mc.gotoAndPlay(1);
				quest_mark_twinkle_mc.visible = true;
			}
			else
			{
				quest_mark_twinkle_mc.gotoAndStop(1);
				quest_mark_twinkle_mc.visible = false;
			}
		}
	}
}