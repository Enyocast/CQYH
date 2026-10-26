package UI_LoginWidget.AS3 {
	
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	
	public class FindRole extends RadioButton {
		
		public var mc_head:MovieClip;
		public var tF_Name:TextField;
		public var tF_Level:TextField;
		public var RoleID:int;
		override protected function configUI():void{
			super.configUI();
			mc_head.mouseEnabled=false;
			mc_head.mouseChildren=false;
		}
		
		public function updateData( dat:RoleInfoData ):void
		{
			visible = dat.HasRole;
			var frame:int=0;
			if(dat.Sex==0)
			{
				frame=dat.Career+1;
			}
			else
			{
				frame=dat.Career+6;
			}
			mc_head.gotoAndStop(frame);
			tF_Name.text=dat.RoleName;
			tF_Level.text=dat.Level;
			RoleID=dat.RoleID;
				
		}
		
		override public function setActualSize(newWidth:Number, newHeight:Number):void {
		      if (super.width != newWidth || _width != newWidth) {
					super.width = _width = newWidth;
				}

				if (super.height != newHeight || _height != newHeight) {
					super.height = _height = newHeight;
				}
		}
	}
	
}
