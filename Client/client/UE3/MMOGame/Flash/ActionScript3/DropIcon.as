package ActionScript3
{

	import flash.display.MovieClip;
	import scaleform.clik.controls.UILoader;


	public class DropIcon extends MovieClip
	{
		public var bNeedVisible:Boolean = false;
		public var IconLoader_mc:UILoader;
		public var gasIcon_mc:MovieClip;
		public var arrow_mc:MovieClip;
		protected var slotType:int =0;
		protected var halfWidth:int =20;
		
		public function DropIcon():void
		{
			this.mouseChildren=false;
			IconLoader_mc.mouseEnabled=false;
			IconLoader_mc.mouseChildren=false;
			arrow_mc.mouseChildren=false;
			arrow_mc.mouseEnabled=false;
			gasIcon_mc.mouseChildren=false;
			gasIcon_mc.mouseEnabled=false;
		}
		
		public function set IconType( type:int ):void
		{
			trace("DropIcon=========================",type);
			slotType = type;
			if(slotType==0)
			{
				arrow_mc.visible =true;
				IconLoader_mc.x = 0;
				IconLoader_mc.y = 0;
				gasIcon_mc.x = 0+20;				
				gasIcon_mc.y = 0+20;
			}
			else if(slotType==1)
			{
				arrow_mc.visible =true;
				IconLoader_mc.x = -halfWidth;
				IconLoader_mc.y = -halfWidth;
				gasIcon_mc.x = -halfWidth+20;
				gasIcon_mc.y = -halfWidth+20;
			}
			else if(slotType==2)
			{
				arrow_mc.visible =false;
				IconLoader_mc.x = -halfWidth;
				IconLoader_mc.y = -halfWidth;
				gasIcon_mc.x = -halfWidth+20;
				gasIcon_mc.y = -halfWidth+20;
			}
			else if(slotType==3)
			{
				arrow_mc.visible =true;
				IconLoader_mc.x = -halfWidth*3/2;
				IconLoader_mc.y = -halfWidth*3/2;
				gasIcon_mc.x = -halfWidth*3/2+20;								
				gasIcon_mc.y = -halfWidth*3/2+20;				
			}
		}
		
	}
	
}