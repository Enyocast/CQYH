package ActionScript3.Bag {
	
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	
	public class ExpView extends MovieClip {
		
		public var ExpContainerSlot:MyItemSlot;
		public var exp_bar:MovieClip;
		public var txt_num:TextField;
		public function ExpView() {
			updateProgress(0,0);
		}
		
		public function updateProgress(min:int,max:int):void
		{
			var bfb:Number=(min/max);
			if(min==0 && max==0)
			{
				exp_bar._m.width=0;
			    txt_num.text="0%";  
			}
			else
			{
				exp_bar._m.width=bfb*184;
				txt_num.text=int(bfb*100)+"%";
			}
			
		}
	}
	
}
